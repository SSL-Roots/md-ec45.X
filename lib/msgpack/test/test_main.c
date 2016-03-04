/*
 * File:   main.c
 * Ver 1.0.1
 *
 * Author: Ishikura Makito
 *
 * Created on 2012/07/20, 18:13
 */

#define	FCY	39613750

#include	<xc.h>
#include	<libpic30.h>
#include	"PCUnit/PCUnit.h"

_FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH);
_FGS(GWRP_OFF & GSS_OFF);
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSDCMD);
_FWDT(WDTPOST_PS32768 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF);
_FPOR(FPWRT_PWR128 & ALTI2C_OFF);
_FICD(ICS_PGD1 & JTAGEN_OFF);

#include	<uart/uart_dsPIC33F.h>

#define	_DEBUG
/********************************************************/
void	initialize(void);
void	initializeOsc( void );
void	initializeIO( void );
/********************************************************/

/********************************************************/
/********************************************************/
PCU_Suite *pack_test_suite(void);
PCU_Suite *static_zone_test_suite(void);
PCU_Suite *unpack_test_suite(void);
PCU_Suite *endian_test_suite(void);
PCU_Suite *pack_unpack_test_suite(void);

int main(void)
{
	initialize( );
	initializeUart(9, 8, FCY*2, 57600);

	const	PCU_SuiteMethod	suites[] = {
		pack_test_suite,
		static_zone_test_suite,
		unpack_test_suite,
		endian_test_suite,
		pack_unpack_test_suite,
	};
	PCU_set_putchar(putcUart);

	PCU_run(suites, sizeof(suites)/sizeof(suites[0]));

	return	0;
}


/********************************************************/
void	initialize( void )
{
	initializeOsc( );
	initializeIO( );
}


void	initializeOsc( void )
{
	RCONbits.SWDTEN	= 0;

	_PLLPOST	= 0b00; /* N2: PLL出力分周 = 2 */
	_PLLPRE	= 0b0000;  /* N1:PLL入力プリスケーラ = 2*/
	PLLFBD	= 0x0029; /* M : PLL倍率 = 43 */

	while( !OSCCONbits.LOCK ); /* waiting PLL Lock */
}


void	initializeIO( void )
{
	PORTA	= 0x0000;
	TRISA	= 0x0000;

	PORTB	= 0x0000;
	TRISB	= 0x0000;
}