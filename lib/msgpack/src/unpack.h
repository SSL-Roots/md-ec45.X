/* 
 * File:   unpack.h
 * Author: master
 *
 * Created on 2014/01/28, 12:57
 */

#ifndef _UNPACK_H_
#define	_UNPACK_H_

#include	<stddef.h>
#include	<stdbool.h>
#include	"object.h"
#include	"static_zone.h"


#define	INIT_UNPACKER_DATA_SIZE	8
typedef struct {
	StaticZone	zone;
	unsigned char*	data;
	size_t	size;
	size_t	parsed;
} msgpack_unpacker;


typedef struct {
	StaticZone			zone;
	msgpack_object*		data;
} msgpack_unpacked;


/* **************************** */
extern bool	initUnpackerMsgpack(msgpack_unpacker* upk);
extern void	destroyUnpackerMsgPack(msgpack_unpacker* upk);
extern bool	pushByteUnpackerMsgpack(unsigned char byte, msgpack_unpacker* upk);
extern void msgpack_object_print(msgpack_object o);
/* TODO :: staticにする*/
extern bool	deleteReadByteUnpacker(msgpack_unpacker* upk);
/* **************************** */


/* **************************** */
extern bool	initUnpackedMsgpack(msgpack_unpacked* upkd);
/* **************************** */

/* **************************** */
typedef enum Err_unpackerNextMsgpack{
    FAILED_UNPACKER_NEXT_MSGPACK_ ,
    UNPACKING_UNPACKER_NEXT_MSGPACK_ ,
    SUCCEEDED_UNPACKER_NEXT_MSGPACK_
} Err_unpackerNextMsgpack;
extern Err_unpackerNextMsgpack	unpackerNextMsgpack( msgpack_unpacker* upk, msgpack_unpacked* upkd );
/* **************************** */


#endif	/* UNPACK_H */

