#ifndef	_PACK_H_
#define	_PACK_H_

#include	<stdint.h>
#include	<stdbool.h>
#include	"static_zone.h"

typedef struct msgpack_packed {
	StaticZone		zone;
	unsigned char*	data;
	size_t			size;
} msgpack_packed;

extern bool	initPackedMsgpack(msgpack_packed* pk);

extern bool	packUnsignedCharMsgpack(msgpack_packed* pk, unsigned char d);
extern bool	packUnsignedShortMsgpack(msgpack_packed* pk, unsigned short d);
extern bool	packUnsignedLongMsgpack(msgpack_packed* pk, unsigned long d);
extern bool	packUnsignedLongLongMsgpack(msgpack_packed* pk, unsigned long long d);

extern bool	packSignedCharMsgpack(msgpack_packed* pk, signed char d);
extern bool	packSignedShortMsgpack(msgpack_packed* pk, signed short d);
extern bool	packSignedLongMsgpack(msgpack_packed* pk, signed long d);
extern bool	packSignedLongLongMsgpack(msgpack_packed* pk, signed long long d);

extern bool	packArrayMsgpack(msgpack_packed* pk, size_t n);
extern bool	packRawMsgpack(msgpack_packed* pk, size_t n, const unsigned char* raw);

#endif	/* _PACK_H_ */