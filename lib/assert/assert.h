/*
 * ASSERTマクロ
 * Ver 1.0.0
 *
 * Author	: 石倉万希斗
 * Latest	: 2013/01/29 20:17
 */


#ifndef	_ASSERT_H_
#define	_ASSERT_H_


void	doAssert( unsigned int val, unsigned int line_num, const char* file_name );

/* ********************************** */
extern int	(*G_assert_p_puts)(const char*);
#define	defineAssertPuts(p_puts)	G_assert_p_puts = (p_puts)
/* ********************************** */

/* ********************************** */
#ifdef	_DEBUG
#define	ASSERT(val)	doAssert((val),__LINE__,__FILE__)
#else
#define	ASSERT(val)	1=1
#endif

/* ********************************** */

#endif	/* _ASSERT_H_ */
