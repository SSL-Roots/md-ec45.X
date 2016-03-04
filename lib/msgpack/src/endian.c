#include	<stddef.h>
#include	"endian.h"


typedef union Inverter {
	unsigned char	each_byte[sizeof(unsigned long long)];

	unsigned short		t_short;
	unsigned long		t_long;
	unsigned long long	t_long_long;
} Inverter;

extern unsigned long long	htonll(unsigned long long host)
{
	Inverter	inv_before, inv_after;
	size_t	i, size = sizeof(host);

	inv_before.t_long_long	= host;
	for (i=0; i<size; i++) {
		inv_after.each_byte[i]	= inv_before.each_byte[size-1 - i];
	}
	return	inv_after.t_long_long;
}

extern unsigned long	htonl(unsigned long host)
{
	Inverter	inv_before, inv_after;
	size_t	i, size = sizeof(host);

	inv_before.t_long	= host;
	for (i=0; i<size; i++) {
		inv_after.each_byte[i]	= inv_before.each_byte[size-1 - i];
	}
	return	inv_after.t_long;
}

extern unsigned short	htons(unsigned short host)
{
	Inverter	inv_before, inv_after;
	size_t	i, size = sizeof(host);

	inv_before.t_short	= host;
	for (i=0; i<size; i++) {
		inv_after.each_byte[i]	= inv_before.each_byte[size-1 - i];
	}
	return	inv_after.t_short;
}

extern unsigned long long	ntohll(unsigned long long net)
{
	return	htonll(net);
}

extern unsigned long	ntohl(unsigned long net)
{
	return	htonl(net);
}

extern unsigned short	ntohs(unsigned short net)
{
	return	htons(net);
}