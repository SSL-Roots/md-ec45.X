#include	<stddef.h>
#include	<string.h>
#include	"static_zone.h"




extern void	initZone(StaticZone* zone)
{
	zone->num_used	= 0;
}


extern void*	mallocZone(StaticZone* zone, size_t size)
{
	if ((zone->num_used + size) > NUM_ZONE) {
		/* 確保するだけのメモリ空きがありませんよー */
		return	NULL;
	}

	void*	alloc_ptr	= &(zone->zone[zone->num_used]);
	zone->num_used		= zone->num_used + size;

	return	(void*)alloc_ptr;
}

extern void*	callocZone(StaticZone* zone, size_t n, size_t size)
{
	if ((zone->num_used + size*n) > NUM_ZONE) {
		/* 確保するだけのメモリ空きがありませんよー */
		return	NULL;
	}

	void*	alloc_ptr	= &(zone->zone[zone->num_used]);
	zone->num_used		= zone->num_used + size*n;

	return	(void*)alloc_ptr;
}


extern void	cpyZone(StaticZone* z1, StaticZone* z2)
{
	memcpy(z1->zone, z2->zone, NUM_ZONE);
	z1->num_used	= z2->num_used;
}
