/*
 * This definitions of the PIC16F1933 MCU.
 *
 * This file is part of the GNU PIC library for SDCC, originally
 * created by Molnar Karoly <molnarkaroly@users.sf.net> 2016.
 *
 * This file is generated automatically by the cinc2h.pl, 2016-01-09 15:09:10 UTC.
 *
 * SDCC is licensed under the GNU Public license (GPL) v2. Note that
 * this license covers the code to the compiler and other executables,
 * but explicitly does not cover any code or objects generated by sdcc.
 *
 * For pic device libraries and header files which are derived from
 * Microchip header (.inc) and linker script (.lkr) files Microchip
 * requires that "The header files should state that they are only to be
 * used with authentic Microchip devices" which makes them incompatible
 * with the GPL. Pic device libraries and header files are located at
 * non-free/lib and non-free/include directories respectively.
 * Sdcc should be run with the --use-non-free command line option in
 * order to include non-free header files and libraries.
 *
 * See http://sdcc.sourceforge.net/ for the latest information on sdcc.
 */

#include <pic16f1933.h>

//==============================================================================

__at(0x0000) __sfr INDF0;

__at(0x0001) __sfr INDF1;

__at(0x0002) __sfr PCL;

__at(0x0003) __sfr STATUS;
__at(0x0003) volatile __STATUSbits_t STATUSbits;

__at(0x0004) __sfr FSR0;

__at(0x0004) __sfr FSR0L;

__at(0x0005) __sfr FSR0H;

__at(0x0006) __sfr FSR1;

__at(0x0006) __sfr FSR1L;

__at(0x0007) __sfr FSR1H;

__at(0x0008) __sfr BSR;
__at(0x0008) volatile __BSRbits_t BSRbits;

__at(0x0009) __sfr WREG;

__at(0x000A) __sfr PCLATH;

__at(0x000B) __sfr INTCON;
__at(0x000B) volatile __INTCONbits_t INTCONbits;

__at(0x000C) __sfr PORTA;
__at(0x000C) volatile __PORTAbits_t PORTAbits;

__at(0x000D) __sfr PORTB;
__at(0x000D) volatile __PORTBbits_t PORTBbits;

__at(0x000E) __sfr PORTC;
__at(0x000E) volatile __PORTCbits_t PORTCbits;

__at(0x0010) __sfr PORTE;
__at(0x0010) volatile __PORTEbits_t PORTEbits;

__at(0x0011) __sfr PIR1;
__at(0x0011) volatile __PIR1bits_t PIR1bits;

__at(0x0012) __sfr PIR2;
__at(0x0012) volatile __PIR2bits_t PIR2bits;

__at(0x0013) __sfr PIR3;
__at(0x0013) volatile __PIR3bits_t PIR3bits;

__at(0x0015) __sfr TMR0;

__at(0x0016) __sfr TMR1;

__at(0x0016) __sfr TMR1L;

__at(0x0017) __sfr TMR1H;

__at(0x0018) __sfr T1CON;
__at(0x0018) volatile __T1CONbits_t T1CONbits;

__at(0x0019) __sfr T1GCON;
__at(0x0019) volatile __T1GCONbits_t T1GCONbits;

__at(0x001A) __sfr TMR2;

__at(0x001B) __sfr PR2;

__at(0x001C) __sfr T2CON;
__at(0x001C) volatile __T2CONbits_t T2CONbits;

__at(0x001E) __sfr CPSCON0;
__at(0x001E) volatile __CPSCON0bits_t CPSCON0bits;

__at(0x001F) __sfr CPSCON1;
__at(0x001F) volatile __CPSCON1bits_t CPSCON1bits;

__at(0x008C) __sfr TRISA;
__at(0x008C) volatile __TRISAbits_t TRISAbits;

__at(0x008D) __sfr TRISB;
__at(0x008D) volatile __TRISBbits_t TRISBbits;

__at(0x008E) __sfr TRISC;
__at(0x008E) volatile __TRISCbits_t TRISCbits;

__at(0x0090) __sfr TRISE;
__at(0x0090) volatile __TRISEbits_t TRISEbits;

__at(0x0091) __sfr PIE1;
__at(0x0091) volatile __PIE1bits_t PIE1bits;

__at(0x0092) __sfr PIE2;
__at(0x0092) volatile __PIE2bits_t PIE2bits;

__at(0x0093) __sfr PIE3;
__at(0x0093) volatile __PIE3bits_t PIE3bits;

__at(0x0095) __sfr OPTION_REG;
__at(0x0095) volatile __OPTION_REGbits_t OPTION_REGbits;

__at(0x0096) __sfr PCON;
__at(0x0096) volatile __PCONbits_t PCONbits;

__at(0x0097) __sfr WDTCON;
__at(0x0097) volatile __WDTCONbits_t WDTCONbits;

__at(0x0098) __sfr OSCTUNE;
__at(0x0098) volatile __OSCTUNEbits_t OSCTUNEbits;

__at(0x0099) __sfr OSCCON;
__at(0x0099) volatile __OSCCONbits_t OSCCONbits;

__at(0x009A) __sfr OSCSTAT;
__at(0x009A) volatile __OSCSTATbits_t OSCSTATbits;

__at(0x009B) __sfr ADRES;

__at(0x009B) __sfr ADRESL;

__at(0x009C) __sfr ADRESH;

__at(0x009D) __sfr ADCON0;
__at(0x009D) volatile __ADCON0bits_t ADCON0bits;

__at(0x009E) __sfr ADCON1;
__at(0x009E) volatile __ADCON1bits_t ADCON1bits;

__at(0x010C) __sfr LATA;
__at(0x010C) volatile __LATAbits_t LATAbits;

__at(0x010D) __sfr LATB;
__at(0x010D) volatile __LATBbits_t LATBbits;

__at(0x010E) __sfr LATC;
__at(0x010E) volatile __LATCbits_t LATCbits;

__at(0x0110) __sfr LATE;
__at(0x0110) volatile __LATEbits_t LATEbits;

__at(0x0111) __sfr CM1CON0;
__at(0x0111) volatile __CM1CON0bits_t CM1CON0bits;

__at(0x0112) __sfr CM1CON1;
__at(0x0112) volatile __CM1CON1bits_t CM1CON1bits;

__at(0x0113) __sfr CM2CON0;
__at(0x0113) volatile __CM2CON0bits_t CM2CON0bits;

__at(0x0114) __sfr CM2CON1;
__at(0x0114) volatile __CM2CON1bits_t CM2CON1bits;

__at(0x0115) __sfr CMOUT;
__at(0x0115) volatile __CMOUTbits_t CMOUTbits;

__at(0x0116) __sfr BORCON;
__at(0x0116) volatile __BORCONbits_t BORCONbits;

__at(0x0117) __sfr FVRCON;
__at(0x0117) volatile __FVRCONbits_t FVRCONbits;

__at(0x0118) __sfr DACCON0;
__at(0x0118) volatile __DACCON0bits_t DACCON0bits;

__at(0x0119) __sfr DACCON1;
__at(0x0119) volatile __DACCON1bits_t DACCON1bits;

__at(0x011A) __sfr SRCON0;
__at(0x011A) volatile __SRCON0bits_t SRCON0bits;

__at(0x011B) __sfr SRCON1;
__at(0x011B) volatile __SRCON1bits_t SRCON1bits;

__at(0x011D) __sfr APFCON;
__at(0x011D) volatile __APFCONbits_t APFCONbits;

__at(0x018C) __sfr ANSELA;
__at(0x018C) volatile __ANSELAbits_t ANSELAbits;

__at(0x018D) __sfr ANSELB;
__at(0x018D) volatile __ANSELBbits_t ANSELBbits;

__at(0x0191) __sfr EEADR;

__at(0x0191) __sfr EEADRL;

__at(0x0192) __sfr EEADRH;

__at(0x0193) __sfr EEDAT;

__at(0x0193) __sfr EEDATL;

__at(0x0194) __sfr EEDATH;

__at(0x0195) __sfr EECON1;
__at(0x0195) volatile __EECON1bits_t EECON1bits;

__at(0x0196) __sfr EECON2;

__at(0x0199) __sfr RCREG;

__at(0x019A) __sfr TXREG;

__at(0x019B) __sfr SP1BRG;

__at(0x019B) __sfr SP1BRGL;

__at(0x019B) __sfr SPBRG;

__at(0x019B) __sfr SPBRGL;

__at(0x019C) __sfr SP1BRGH;

__at(0x019C) __sfr SPBRGH;

__at(0x019D) __sfr RCSTA;
__at(0x019D) volatile __RCSTAbits_t RCSTAbits;

__at(0x019E) __sfr TXSTA;
__at(0x019E) volatile __TXSTAbits_t TXSTAbits;

__at(0x019F) __sfr BAUDCON;
__at(0x019F) volatile __BAUDCONbits_t BAUDCONbits;

__at(0x020D) __sfr WPUB;
__at(0x020D) volatile __WPUBbits_t WPUBbits;

__at(0x0210) __sfr WPUE;
__at(0x0210) volatile __WPUEbits_t WPUEbits;

__at(0x0211) __sfr SSPBUF;

__at(0x0212) __sfr SSPADD;

__at(0x0213) __sfr SSPMSK;

__at(0x0214) __sfr SSPSTAT;
__at(0x0214) volatile __SSPSTATbits_t SSPSTATbits;

__at(0x0215) __sfr SSPCON;
__at(0x0215) volatile __SSPCONbits_t SSPCONbits;

__at(0x0215) __sfr SSPCON1;
__at(0x0215) volatile __SSPCON1bits_t SSPCON1bits;

__at(0x0216) __sfr SSPCON2;
__at(0x0216) volatile __SSPCON2bits_t SSPCON2bits;

__at(0x0217) __sfr SSPCON3;
__at(0x0217) volatile __SSPCON3bits_t SSPCON3bits;

__at(0x0291) __sfr CCPR1;

__at(0x0291) __sfr CCPR1L;

__at(0x0292) __sfr CCPR1H;

__at(0x0293) __sfr CCP1CON;
__at(0x0293) volatile __CCP1CONbits_t CCP1CONbits;

__at(0x0294) __sfr PWM1CON;
__at(0x0294) volatile __PWM1CONbits_t PWM1CONbits;

__at(0x0295) __sfr CCP1AS;
__at(0x0295) volatile __CCP1ASbits_t CCP1ASbits;

__at(0x0295) __sfr ECCP1AS;
__at(0x0295) volatile __ECCP1ASbits_t ECCP1ASbits;

__at(0x0296) __sfr PSTR1CON;
__at(0x0296) volatile __PSTR1CONbits_t PSTR1CONbits;

__at(0x0298) __sfr CCPR2;

__at(0x0298) __sfr CCPR2L;

__at(0x0299) __sfr CCPR2H;

__at(0x029A) __sfr CCP2CON;
__at(0x029A) volatile __CCP2CONbits_t CCP2CONbits;

__at(0x029B) __sfr PWM2CON;
__at(0x029B) volatile __PWM2CONbits_t PWM2CONbits;

__at(0x029C) __sfr CCP2AS;
__at(0x029C) volatile __CCP2ASbits_t CCP2ASbits;

__at(0x029C) __sfr ECCP2AS;
__at(0x029C) volatile __ECCP2ASbits_t ECCP2ASbits;

__at(0x029D) __sfr PSTR2CON;
__at(0x029D) volatile __PSTR2CONbits_t PSTR2CONbits;

__at(0x029E) __sfr CCPTMRS0;
__at(0x029E) volatile __CCPTMRS0bits_t CCPTMRS0bits;

__at(0x029F) __sfr CCPTMRS1;
__at(0x029F) volatile __CCPTMRS1bits_t CCPTMRS1bits;

__at(0x0311) __sfr CCPR3;

__at(0x0311) __sfr CCPR3L;

__at(0x0312) __sfr CCPR3H;

__at(0x0313) __sfr CCP3CON;
__at(0x0313) volatile __CCP3CONbits_t CCP3CONbits;

__at(0x0314) __sfr PWM3CON;
__at(0x0314) volatile __PWM3CONbits_t PWM3CONbits;

__at(0x0315) __sfr CCP3AS;
__at(0x0315) volatile __CCP3ASbits_t CCP3ASbits;

__at(0x0315) __sfr ECCP3AS;
__at(0x0315) volatile __ECCP3ASbits_t ECCP3ASbits;

__at(0x0316) __sfr PSTR3CON;
__at(0x0316) volatile __PSTR3CONbits_t PSTR3CONbits;

__at(0x0318) __sfr CCPR4;

__at(0x0318) __sfr CCPR4L;

__at(0x0319) __sfr CCPR4H;

__at(0x031A) __sfr CCP4CON;
__at(0x031A) volatile __CCP4CONbits_t CCP4CONbits;

__at(0x031C) __sfr CCPR5;

__at(0x031C) __sfr CCPR5L;

__at(0x031D) __sfr CCPR5H;

__at(0x031E) __sfr CCP5CON;
__at(0x031E) volatile __CCP5CONbits_t CCP5CONbits;

__at(0x0394) __sfr IOCBP;
__at(0x0394) volatile __IOCBPbits_t IOCBPbits;

__at(0x0395) __sfr IOCBN;
__at(0x0395) volatile __IOCBNbits_t IOCBNbits;

__at(0x0396) __sfr IOCBF;
__at(0x0396) volatile __IOCBFbits_t IOCBFbits;

__at(0x0415) __sfr TMR4;

__at(0x0416) __sfr PR4;

__at(0x0417) __sfr T4CON;
__at(0x0417) volatile __T4CONbits_t T4CONbits;

__at(0x041C) __sfr TMR6;

__at(0x041D) __sfr PR6;

__at(0x041E) __sfr T6CON;
__at(0x041E) volatile __T6CONbits_t T6CONbits;

__at(0x0791) __sfr LCDCON;
__at(0x0791) volatile __LCDCONbits_t LCDCONbits;

__at(0x0792) __sfr LCDPS;
__at(0x0792) volatile __LCDPSbits_t LCDPSbits;

__at(0x0793) __sfr LCDREF;
__at(0x0793) volatile __LCDREFbits_t LCDREFbits;

__at(0x0794) __sfr LCDCST;
__at(0x0794) volatile __LCDCSTbits_t LCDCSTbits;

__at(0x0795) __sfr LCDRL;
__at(0x0795) volatile __LCDRLbits_t LCDRLbits;

__at(0x0798) __sfr LCDSE0;
__at(0x0798) volatile __LCDSE0bits_t LCDSE0bits;

__at(0x0799) __sfr LCDSE1;
__at(0x0799) volatile __LCDSE1bits_t LCDSE1bits;

__at(0x07A0) __sfr LCDDATA0;
__at(0x07A0) volatile __LCDDATA0bits_t LCDDATA0bits;

__at(0x07A1) __sfr LCDDATA1;
__at(0x07A1) volatile __LCDDATA1bits_t LCDDATA1bits;

__at(0x07A3) __sfr LCDDATA3;
__at(0x07A3) volatile __LCDDATA3bits_t LCDDATA3bits;

__at(0x07A4) __sfr LCDDATA4;
__at(0x07A4) volatile __LCDDATA4bits_t LCDDATA4bits;

__at(0x07A6) __sfr LCDDATA6;
__at(0x07A6) volatile __LCDDATA6bits_t LCDDATA6bits;

__at(0x07A7) __sfr LCDDATA7;
__at(0x07A7) volatile __LCDDATA7bits_t LCDDATA7bits;

__at(0x07A9) __sfr LCDDATA9;
__at(0x07A9) volatile __LCDDATA9bits_t LCDDATA9bits;

__at(0x07AA) __sfr LCDDATA10;
__at(0x07AA) volatile __LCDDATA10bits_t LCDDATA10bits;

__at(0x0FE4) __sfr STATUS_SHAD;
__at(0x0FE4) volatile __STATUS_SHADbits_t STATUS_SHADbits;

__at(0x0FE5) __sfr WREG_SHAD;

__at(0x0FE6) __sfr BSR_SHAD;

__at(0x0FE7) __sfr PCLATH_SHAD;

__at(0x0FE8) __sfr FSR0L_SHAD;

__at(0x0FE9) __sfr FSR0H_SHAD;

__at(0x0FEA) __sfr FSR1L_SHAD;

__at(0x0FEB) __sfr FSR1H_SHAD;

__at(0x0FED) __sfr STKPTR;

__at(0x0FEE) __sfr TOSL;

__at(0x0FEF) __sfr TOSH;
