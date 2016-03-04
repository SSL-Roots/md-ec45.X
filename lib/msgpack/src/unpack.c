#include	<stdbool.h>
#include	<stdint.h>
#include	<string.h>
#include	"unpack.h"
#include	"object.h"

/* *********************** */

/* *********************** */
static bool	checkObjectType(
	const unsigned char* byte,
	msgpack_object_type* type,
	msgpack_object_union*	val,
	size_t* obj_size
);

static bool	getObjectValue(size_t obj_size, msgpack_object_type type, msgpack_unpacker* pk, msgpack_object_union* val);
static bool	fetchByte(msgpack_unpacker* unpacker, unsigned char* byte);

#define	UNPACK_FAIL			-1
#define	UNPACK_PARSING		0
#define	UNPACK_SUCCEEDED	1
static int	unpackNextTuple(msgpack_unpacker* upk, size_t size, msgpack_object* obj, StaticZone* zone);

void msgpack_object_print(msgpack_object o);
/* *********************** */


extern bool	initUnpackerMsgpack(msgpack_unpacker* upk)
{
	initZone(&upk->zone);
	upk->data	= upk->zone.zone;

	upk->size	= 0;
	upk->parsed	= 0;

	return	true;
}


extern bool	pushByteUnpackerMsgpack(unsigned char byte, msgpack_unpacker* upk)
{
	if (upk->size >= NUM_ZONE) {	return false; }

	*(upk->data + upk->size)	= byte;
	upk->size++;

	return	true;
}


//TODO::staticにする
//static bool	deleteReadByteUnpacker(msgpack_unpacker* upk)
extern bool	deleteReadByteUnpacker(msgpack_unpacker* upk)
{
	size_t	num_bytes = upk->size - upk->parsed;

	memmove(upk->data, upk->data + upk->parsed, num_bytes);
	upk->size	= num_bytes;
	upk->parsed	= 0;

	return	true;
}
/* *********************** */


/* *********************** */
extern bool	initUnpackedMsgpack(msgpack_unpacked* upkd)
{
	initZone(&upkd->zone);
	upkd->data	= (msgpack_object*)mallocZone(&upkd->zone, sizeof(msgpack_object));

	return	true;
}
/* *********************** */


/* *********************** */

extern Err_unpackerNextMsgpack	unpackerNextMsgpack( msgpack_unpacker* upk, msgpack_unpacked* upkd )
{
	int	ret_unpack_next;

	initUnpackedMsgpack(upkd);

	ret_unpack_next	= unpackNextTuple(upk, 1, upkd->data, &upkd->zone);

	if (ret_unpack_next == UNPACK_PARSING) {
		upk->parsed	= 0;
		return	UNPACKING_UNPACKER_NEXT_MSGPACK_;
	}

	deleteReadByteUnpacker(upk);

	if (ret_unpack_next == UNPACK_FAIL) {
		return	FAILED_UNPACKER_NEXT_MSGPACK_;
	}

	return	SUCCEEDED_UNPACKER_NEXT_MSGPACK_;
}



static int	unpackNextTuple(msgpack_unpacker* upk, size_t size, msgpack_object* obj, StaticZone* zone)
{
	size_t	parsed	= 0;

	while (parsed < size) {
		msgpack_object*	obj_parsing = obj + parsed;
		unsigned char	buf;
		size_t			obj_size;
		bool			is_data_fill, is_type;

		//バイト列から型データを取得
		is_data_fill	= fetchByte(upk, &buf);
		if (!is_data_fill) {	return	UNPACK_PARSING; }

		//型判別
		is_type	= checkObjectType(&buf, &(obj_parsing->type), &(obj_parsing->via), &obj_size);
		if (!is_type) {	return	UNPACK_FAIL; }

		//データ取得
		if (obj_size) {	//データ数が0(型情報といっしょに内容が収められている)の場合、スキップ

			if (obj_parsing->type == MSGPACK_OBJECT_ARRAY) {
				//取得した型が配列
				obj_parsing->via.array.size	= obj_size;
				obj_parsing->via.array.ptr	= (msgpack_object*)callocZone(zone, obj_size, sizeof(msgpack_object)) ;
				if (!obj_parsing->via.array.ptr) {	return	UNPACK_FAIL; }	//配列メモリ確保失敗

				int	ret_unpack_next = unpackNextTuple(upk, obj_size, obj_parsing->via.array.ptr, zone);
				if (ret_unpack_next != UNPACK_SUCCEEDED) { return ret_unpack_next; }

			}else if (obj_parsing->type == MSGPACK_OBJECT_RAW) {
				//取得した型がバイナリ
				size_t	i;

				obj_parsing->via.raw.size	= obj_size;
				obj_parsing->via.raw.ptr	= (char*)callocZone(zone, obj_size, sizeof(char));
				if (!obj_parsing->via.raw.ptr) {	return	UNPACK_FAIL; }	//配列メモリ確保失敗

				for (i=0; i<obj_size; i++) {
					is_data_fill	= fetchByte(upk, (unsigned char*)(obj_parsing->via.raw.ptr + i));
					if (!is_data_fill) {	return UNPACK_PARSING; }
				}

			}else if (obj_parsing->type == MSGPACK_OBJECT_MAP) {
				//取得した型がマップ
				//TODO::マップ型の実装
				return	UNPACK_FAIL;

			}else{
				is_data_fill	= getObjectValue(obj_size, obj_parsing->type, upk, &(obj_parsing->via));
				if (!is_data_fill) {	return UNPACK_PARSING; }
			}
		}

		parsed ++;
	}

	return	UNPACK_SUCCEEDED;
}

static bool	checkObjectType(
	const unsigned char* byte,
	msgpack_object_type* type,
	msgpack_object_union*	val,
	size_t* obj_size
)
{
	if (*byte == 0xc0) { 							/* nil */
		*type		= MSGPACK_OBJECT_NIL;
		*obj_size	= 0;

	}else if ((*byte >= 0xc2) && (*byte <= 0xc3)) {	/* boolean */
		*type		= MSGPACK_OBJECT_BOOLEAN;
		val->boolean= *byte & 0x01;
		*obj_size	= 0;

	}else if ((*byte & 0x80) == 0x00) {				/* Pos fixnum*/
		*type		= MSGPACK_OBJECT_POSITIVE_INTEGER;
		val->u64	= *byte;
		*obj_size	= 0;

	}else if ((*byte & 0xe0) == 0xe0) {				/* Neg fixnum*/
		*type		= MSGPACK_OBJECT_NEGATIVE_INTEGER;
		val->i64	= 0xFFFFFFFFFFFFFF00 | *byte;
		*obj_size	= 0;

	}else if ((*byte >= 0xcc) && (*byte <= 0xcf)) {	/* uintX */
		*type		= MSGPACK_OBJECT_POSITIVE_INTEGER;
		*obj_size	= 1 << (*byte & 0x03);

	}else if ((*byte >= 0xd0) && (*byte <= 0xd3)) {	/* intX */
		*type		= MSGPACK_OBJECT_NEGATIVE_INTEGER;
		*obj_size	= 1 << (*byte & 0x03);

	}else if ((*byte >= 0xca) && (*byte <= 0xcb)) {	/* double */
		*type		= MSGPACK_OBJECT_DOUBLE;
		*obj_size	= 2 << (*byte & 0x01);

	}else if ((*byte & 0xe0) == 0xa0) {	/* FixRaw */
		*type		= MSGPACK_OBJECT_RAW;
		*obj_size	= *byte & ~0xe0;

	}else if ((*byte & 0xf0) == 0x90) {	/* FixArray */
		*type		= MSGPACK_OBJECT_ARRAY;
		*obj_size	= *byte & ~0xf0;

	}else if ((*byte & 0xf0) == 0x80) {	/* FixMap */
		*type		= MSGPACK_OBJECT_MAP;
		*obj_size	= *byte & ~0xf0;

	}else{
		return	false;
	}

	return	true;
}


static bool	getObjectValue(size_t obj_size, msgpack_object_type type, msgpack_unpacker* pk, msgpack_object_union* val)
{
	size_t	i;
	unsigned char	buf;

	if (type == MSGPACK_OBJECT_NEGATIVE_INTEGER) {
		val->u64	= 0xFFFFFFFFFFFFFFFF;	//ゼロクリア
	}else{
		val->u64	= 0;					//ゼロクリア
	}

	for (i=0; i<obj_size; i++) {
		if (fetchByte(pk, &buf) == false) { return	false; }
		val->u64	<<= 8;
		val->u64	|= buf;
	}

	return	true;
}

static bool	fetchByte(msgpack_unpacker* unpacker, unsigned char* byte)
{
	if (unpacker->parsed >= unpacker->size) {
		return	false;
	}

	*byte	= *(unpacker->data + unpacker->parsed);
	unpacker->parsed ++;

	return	true;
}



//
//extern void msgpack_object_print(msgpack_object o)
//{
//	switch(o.type) {
//	case MSGPACK_OBJECT_NIL:
//		xprintf("nil");
//		break;
//
//	case MSGPACK_OBJECT_BOOLEAN:
//		xprintf((o.via.boolean ? "true" : "false"));
//		break;
//
//	case MSGPACK_OBJECT_POSITIVE_INTEGER:
//		xprintf("%ld", (unsigned long)o.via.u64);
//		break;
//
//	case MSGPACK_OBJECT_NEGATIVE_INTEGER:
//		xprintf("%ld", (signed long)o.via.i64);
//		break;
//
//	case MSGPACK_OBJECT_DOUBLE:
//		xprintf("(double)");
//		break;
//
//	case MSGPACK_OBJECT_RAW:
//		xprintf("\"");
//		{
//			size_t	i;
//			for (i=0; i<o.via.raw.size; i++){
//				xprintf("%c", *(o.via.raw.ptr+i));
//			}
//		}
//		xprintf("\"");
//		break;
//
//	case MSGPACK_OBJECT_ARRAY:
//		xprintf("[");
//		if(o.via.array.size != 0) {
//			msgpack_object* p = o.via.array.ptr;
//			msgpack_object_print(*p);
//			++p;
//			msgpack_object* const pend = o.via.array.ptr + o.via.array.size;
//			for(; p < pend; ++p) {
//				xprintf(", ");
//				msgpack_object_print(*p);
//			}
//		}
//		xprintf("]");
//		break;
//
//	case MSGPACK_OBJECT_MAP:
//		xprintf("{");
//		if(o.via.map.size != 0) {
//			msgpack_object_kv* p = o.via.map.ptr;
//			msgpack_object_print(p->key);
//			xprintf("=>");
//			msgpack_object_print(p->val);
//			++p;
//			msgpack_object_kv* const pend = o.via.map.ptr + o.via.map.size;
//			for(; p < pend; ++p) {
//				xprintf(", ");
//				msgpack_object_print(p->key);
//				xprintf("=>");
//				msgpack_object_print(p->val);
//			}
//		}
//		xprintf("}");
//		break;
//
//	default:
//		// FIXME
//		//xprintf("#<UNKNOWN %i %"PRIu64">", o.type, o.via.u64);
//		break;
//	}
//}