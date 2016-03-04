/* 
 * File:   static_zone.h
 * Author: master
 *
 * Created on 2014/01/29, 13:18
 */

#ifndef _STATIC_ZONE_H_
#define	_STATIC_ZONE_H_

/* **************** */
#include	<stddef.h>

#define	NUM_ZONE	128

typedef	struct {
	unsigned char	zone[NUM_ZONE];
	size_t	num_used;
}StaticZone;

extern void	initZone(StaticZone* zone);
extern void*	mallocZone(StaticZone* zone, size_t size);
extern void*	callocZone(StaticZone* zone, size_t n, size_t size);
extern void	cpyZone(StaticZone* z1, StaticZone* z2);

/* **************** */

#endif	/* STATIC_ZONE_H */

