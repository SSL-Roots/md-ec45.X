#include	<string.h>
#include	<limits.h>
#include	<stdint.h>
#include	"pack.h"
#include	"object.h"
#include	"endian.h"

/* ********************* */
typedef union Types {
	unsigned char		each_byte[8];

	bool				t_bool;

	signed char			t_signed_char;
	signed short		t_signed_short;
	signed long			t_signed_long;
	signed long long	t_signed_long_long;

	unsigned char		t_unsigned_char;
	unsigned short		t_unsigned_short;
	unsigned long		t_unsigned_long;
	unsigned long long	t_unsigned_long_long;
} Types;
/* ********************* */


/* ********************* */
static bool	writeBytesPacked(msgpack_packed* pk, const unsigned char* buf, size_t n);
static bool	writeUnsignedShort(msgpack_packed* pk, unsigned short d);
static bool	writeUnsignedLong(msgpack_packed* pk, unsigned long d);
static bool	writeUnsignedLongLong(msgpack_packed* pk, unsigned long long d);
/* ********************* */

extern bool	initPackedMsgpack(msgpack_packed* pk)
{
	initZone(&pk->zone);
	pk->data	= (unsigned char*)mallocZone(&pk->zone, NUM_ZONE);
	pk->size	= 0;
	return	true;
}

static bool	writeBytesPacked(msgpack_packed* pk, const unsigned char* buf, size_t n)
{
	if ((pk->size + n) >= pk->zone.num_used) {	return false; }

	memcpy(pk->zone.zone + pk->size, buf, n);
	pk->size	+= n;
	return	true;
}
/* ********************* */



/* ********************* */
extern bool	packUnsignedCharMsgpack(msgpack_packed* pk, unsigned char d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_unsigned_char	= d;

	if (d >= 128 ){
		type	= 0xcc;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packUnsignedShortMsgpack(msgpack_packed* pk, unsigned short d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_unsigned_short		= d;

	if (d > UCHAR_MAX) {
		type	= 0xcd;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedShort(pk, caster.t_unsigned_short);
	}
	if (d >= 128 ){
		type	= 0xcc;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packUnsignedLongMsgpack(msgpack_packed* pk, unsigned long d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_unsigned_long		= d;

	if (d > USHRT_MAX) {
		type	= 0xce;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedLong(pk, caster.t_unsigned_long);
	}
	if (d > UCHAR_MAX) {
		type	= 0xcd;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedShort(pk, caster.t_unsigned_short);
	}
	if (d >= 128 ){
		type	= 0xcc;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packUnsignedLongLongMsgpack(msgpack_packed* pk, unsigned long long d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_unsigned_long_long	= d;

	if (d > ULLONG_MAX) {
		type	= 0xcf;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedLongLong(pk, caster.t_unsigned_long_long);
	}

	if (d > USHRT_MAX) {
		type	= 0xce;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedLong(pk, caster.t_unsigned_long);
	}

	if (d > UCHAR_MAX) {
		type	= 0xcd;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedShort(pk, caster.t_unsigned_short);
	}
	if (d >= 128 ){
		type	= 0xcc;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packSignedCharMsgpack(msgpack_packed* pk, signed char d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_signed_char	= d;

	if (d <= -32 ){
		type	= 0xd0;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packSignedShortMsgpack(msgpack_packed* pk, signed short d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_signed_short		= d;

	if(d >= 0){
		return	packUnsignedShortMsgpack(pk, (unsigned short)d);
	}else if (d < -32 ){
		type	= 0xd1;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedShort(pk, caster.t_unsigned_short);
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packSignedLongMsgpack(msgpack_packed* pk, signed long d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_signed_long		= d;

	if(d >= 0){
		return	packUnsignedLongMsgpack(pk, (unsigned long)d);
	} else if (d < -32 ){
		type	= 0xd2;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedLong(pk, caster.t_unsigned_long);
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}

extern bool	packSignedLongLongMsgpack(msgpack_packed* pk, signed long long d)
{
	Types	caster;
	unsigned char	type;

	caster.t_unsigned_long_long	= 0;	//キャスター初期化
	caster.t_signed_long_long	= d;

	if(d >= 0){
		return packUnsignedLongLongMsgpack(pk, (unsigned long long)d);
	} else if (d < -32 ){
		type	= 0xd3;
		if (!writeBytesPacked(pk, &type, 1)) {	return	false; }
		return	writeUnsignedLongLong(pk, caster.t_unsigned_long_long);
	}

	return	writeBytesPacked(pk, caster.each_byte, sizeof(unsigned char));
}



extern bool	packArrayMsgpack(msgpack_packed* pk, size_t n)
{
	unsigned char	type;
	if (n >= 16) {	return	false;	}
 	type	= 0x90 | (0x0F & (unsigned char)n);
	return	writeBytesPacked(pk, &type, 1);
}

extern bool	packRawMsgpack(msgpack_packed* pk, size_t n, const unsigned char* raw)
{
	unsigned char	type;
	if (n >= 32) {	return false; }
	type	= 0xa0 | (0x1F & (unsigned char)n);
	if (!writeBytesPacked(pk, &type, 1)) {	return false; }
	return	writeBytesPacked(pk, raw, n);
}

/************************* */
static bool	writeUnsignedShort(msgpack_packed* pk, unsigned short d)
{
	Types	caster;
	caster.t_unsigned_short	= htons(d);	//エンディアン変換
	return	writeBytesPacked(pk, caster.each_byte, sizeof(d));
}

static bool	writeUnsignedLong(msgpack_packed* pk, unsigned long d)
{
	Types	caster;
	caster.t_unsigned_long	= htonl(d);	//エンディアン変換
	return	writeBytesPacked(pk, caster.each_byte, sizeof(d));
}

static bool	writeUnsignedLongLong(msgpack_packed* pk, unsigned long long d)
{
	Types	caster;
	caster.t_unsigned_long_long	= htonll(d);	//エンディアン変換
	return	writeBytesPacked(pk, caster.each_byte, sizeof(d));
}
