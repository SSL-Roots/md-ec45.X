/* 
 * File:   endian.h
 * Author: master
 *
 * Created on 2014/01/29, 22:24
 */

#ifndef _ENDIAN_H_
#define	_ENDIAN_H_

extern unsigned long long	htonll(unsigned long long host);
extern unsigned long		htonl(unsigned long host);
extern unsigned short		htons(unsigned short host);
extern unsigned long long	ntohll(unsigned long long net);
extern unsigned long		ntohl(unsigned long net);
extern unsigned short		ntohs(unsigned short net);

#endif	/* ENDIAN_H */

