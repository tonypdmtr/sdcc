/*
 * pic18f66j60.c - device specific definitions
 *
 * This file is part of the GNU PIC library for SDCC,
 * originally devised by Vangelis Rokas <vrokas AT otenet.gr>
 *
 * It has been automatically generated by inc2h-pic16.pl,
 * (c) 2007 by Raphael Neider <rneider AT web.de>
 *
 * SDCC is licensed under the GNU Public license (GPL) v2. Note that
 * this license covers the code to the compiler and other executables,
 * tbut explicitly does not cover any code or objects generated by sdcc.
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

#include <pic18f66j60.h>


__sfr __at (0xE80) MAADR5;

__sfr __at (0xE81) MAADR6;

__sfr __at (0xE82) MAADR3;

__sfr __at (0xE83) MAADR4;

__sfr __at (0xE84) MAADR1;

__sfr __at (0xE85) MAADR2;

__sfr __at (0xE86) EBSTSD;

__sfr __at (0xE87) EBSTCON;
volatile __EBSTCONbits_t __at (0xE87) EBSTCONbits;

__sfr __at (0xE88) EBSTCS;

__sfr __at (0xE88) EBSTCSL;

__sfr __at (0xE89) EBSTCSH;

__sfr __at (0xE8A) MISTAT;
volatile __MISTATbits_t __at (0xE8A) MISTATbits;

__sfr __at (0xE97) EFLOCON;
volatile __EFLOCONbits_t __at (0xE97) EFLOCONbits;

__sfr __at (0xE98) EPAUS;

__sfr __at (0xE98) EPAUSL;

__sfr __at (0xE99) EPAUSH;

__sfr __at (0xEA0) MACON1;
volatile __MACON1bits_t __at (0xEA0) MACON1bits;

__sfr __at (0xEA1) MACON2;
volatile __MACON2bits_t __at (0xEA1) MACON2bits;

__sfr __at (0xEA2) MACON3;
volatile __MACON3bits_t __at (0xEA2) MACON3bits;

__sfr __at (0xEA3) MACON4;
volatile __MACON4bits_t __at (0xEA3) MACON4bits;

__sfr __at (0xEA4) MABBIPG;

__sfr __at (0xEA6) MAIPG;

__sfr __at (0xEA6) MAIPGL;

__sfr __at (0xEA7) MAIPGH;

__sfr __at (0xEA8) MACLCON1;
volatile __MACLCON1bits_t __at (0xEA8) MACLCON1bits;

__sfr __at (0xEA9) MACLCON2;
volatile __MACLCON2bits_t __at (0xEA9) MACLCON2bits;

__sfr __at (0xEAA) MAMXFL;

__sfr __at (0xEAA) MAMXFLL;

__sfr __at (0xEAB) MAMXFLH;

__sfr __at (0xEB1) MICON;
volatile __MICONbits_t __at (0xEB1) MICONbits;

__sfr __at (0xEB2) MICMD;
volatile __MICMDbits_t __at (0xEB2) MICMDbits;

__sfr __at (0xEB4) MIREGADR;

__sfr __at (0xEB6) MIWR;

__sfr __at (0xEB6) MIWRL;

__sfr __at (0xEB7) MIWRH;

__sfr __at (0xEB8) MIRD;

__sfr __at (0xEB8) MIRDL;

__sfr __at (0xEB9) MIRDH;

__sfr __at (0xEC0) EHT0;

__sfr __at (0xEC1) EHT1;

__sfr __at (0xEC2) EHT2;

__sfr __at (0xEC3) EHT3;

__sfr __at (0xEC4) EHT4;

__sfr __at (0xEC5) EHT5;

__sfr __at (0xEC6) EHT6;

__sfr __at (0xEC7) EHT7;

__sfr __at (0xEC8) EPMM0;

__sfr __at (0xEC9) EPMM1;

__sfr __at (0xECA) EPMM2;

__sfr __at (0xECB) EPMM3;

__sfr __at (0xECC) EPMM4;

__sfr __at (0xECD) EPMM5;

__sfr __at (0xECE) EPMM6;

__sfr __at (0xECF) EPMM7;

__sfr __at (0xED0) EPMCS;

__sfr __at (0xED0) EPMCSL;

__sfr __at (0xED1) EPMCSH;

__sfr __at (0xED4) EPMO;

__sfr __at (0xED4) EPMOL;

__sfr __at (0xED5) EPMOH;

__sfr __at (0xED6) EWOLIE;
volatile __EWOLIEbits_t __at (0xED6) EWOLIEbits;

__sfr __at (0xED7) EWOLIR;
volatile __EWOLIRbits_t __at (0xED7) EWOLIRbits;

__sfr __at (0xED8) ERXFCON;
volatile __ERXFCONbits_t __at (0xED8) ERXFCONbits;

__sfr __at (0xED9) EPKTCNT;

__sfr __at (0xEE2) EWRPT;

__sfr __at (0xEE2) EWRPTL;

__sfr __at (0xEE3) EWRPTH;

__sfr __at (0xEE4) ETXST;

__sfr __at (0xEE4) ETXSTL;

__sfr __at (0xEE5) ETXSTH;

__sfr __at (0xEE6) ETXND;

__sfr __at (0xEE6) ETXNDL;

__sfr __at (0xEE7) ETXNDH;

__sfr __at (0xEE8) ERXST;

__sfr __at (0xEE8) ERXSTL;

__sfr __at (0xEE9) ERXSTH;

__sfr __at (0xEEA) ERXND;

__sfr __at (0xEEA) ERXNDL;

__sfr __at (0xEEB) ERXNDH;

__sfr __at (0xEEC) ERXRDPT;

__sfr __at (0xEEC) ERXRDPTL;

__sfr __at (0xEED) ERXRDPTH;

__sfr __at (0xEEE) ERXWRPT;

__sfr __at (0xEEE) ERXWRPTL;

__sfr __at (0xEEF) ERXWRPTH;

__sfr __at (0xEF0) EDMAST;

__sfr __at (0xEF0) EDMASTL;

__sfr __at (0xEF1) EDMASTH;

__sfr __at (0xEF2) EDMAND;

__sfr __at (0xEF2) EDMANDL;

__sfr __at (0xEF3) EDMANDH;

__sfr __at (0xEF4) EDMADST;

__sfr __at (0xEF4) EDMADSTL;

__sfr __at (0xEF5) EDMADSTH;

__sfr __at (0xEF6) EDMACS;

__sfr __at (0xEF6) EDMACSL;

__sfr __at (0xEF7) EDMACSH;

__sfr __at (0xEFB) EIE;
volatile __EIEbits_t __at (0xEFB) EIEbits;

__sfr __at (0xEFD) ESTAT;
volatile __ESTATbits_t __at (0xEFD) ESTATbits;

__sfr __at (0xEFE) ECON2;
volatile __ECON2bits_t __at (0xEFE) ECON2bits;

__sfr __at (0xF60) EIR;
volatile __EIRbits_t __at (0xF60) EIRbits;

__sfr __at (0xF61) EDATA;
volatile __EDATAbits_t __at (0xF61) EDATAbits;

__sfr __at (0xF67) ECCP2DEL;
volatile __ECCP2DELbits_t __at (0xF67) ECCP2DELbits;

__sfr __at (0xF68) ECCP2AS;
volatile __ECCP2ASbits_t __at (0xF68) ECCP2ASbits;

__sfr __at (0xF69) ECCP3DEL;
volatile __ECCP3DELbits_t __at (0xF69) ECCP3DELbits;

__sfr __at (0xF6A) ECCP3AS;
volatile __ECCP3ASbits_t __at (0xF6A) ECCP3ASbits;

__sfr __at (0xF70) CCP5CON;
volatile __CCP5CONbits_t __at (0xF70) CCP5CONbits;

__sfr __at (0xF71) CCPR5;

__sfr __at (0xF71) CCPR5L;

__sfr __at (0xF72) CCPR5H;

__sfr __at (0xF73) CCP4CON;
volatile __CCP4CONbits_t __at (0xF73) CCP4CONbits;

__sfr __at (0xF74) CCPR4;

__sfr __at (0xF74) CCPR4L;

__sfr __at (0xF75) CCPR4H;

__sfr __at (0xF76) T4CON;
volatile __T4CONbits_t __at (0xF76) T4CONbits;

__sfr __at (0xF77) PR4;

__sfr __at (0xF78) TMR4;

__sfr __at (0xF79) ECCP1DEL;
volatile __ECCP1DELbits_t __at (0xF79) ECCP1DELbits;

__sfr __at (0xF7A) ERDPT;

__sfr __at (0xF7A) ERDPTL;

__sfr __at (0xF7B) ERDPTH;

__sfr __at (0xF7E) BAUDCON;
volatile __BAUDCONbits_t __at (0xF7E) BAUDCONbits;

__sfr __at (0xF7E) BAUDCON1;
volatile __BAUDCON1bits_t __at (0xF7E) BAUDCON1bits;

__sfr __at (0xF7E) BAUDCTL;
volatile __BAUDCTLbits_t __at (0xF7E) BAUDCTLbits;

__sfr __at (0xF7E) BAUDCTL1;
volatile __BAUDCTL1bits_t __at (0xF7E) BAUDCTL1bits;

__sfr __at (0xF7F) SPBRGH;

__sfr __at (0xF7F) SPBRGH1;

__sfr __at (0xF80) PORTA;
volatile __PORTAbits_t __at (0xF80) PORTAbits;

__sfr __at (0xF81) PORTB;
volatile __PORTBbits_t __at (0xF81) PORTBbits;

__sfr __at (0xF82) PORTC;
volatile __PORTCbits_t __at (0xF82) PORTCbits;

__sfr __at (0xF83) PORTD;
volatile __PORTDbits_t __at (0xF83) PORTDbits;

__sfr __at (0xF84) PORTE;
volatile __PORTEbits_t __at (0xF84) PORTEbits;

__sfr __at (0xF85) PORTF;
volatile __PORTFbits_t __at (0xF85) PORTFbits;

__sfr __at (0xF86) PORTG;
volatile __PORTGbits_t __at (0xF86) PORTGbits;

__sfr __at (0xF89) LATA;
volatile __LATAbits_t __at (0xF89) LATAbits;

__sfr __at (0xF8A) LATB;
volatile __LATBbits_t __at (0xF8A) LATBbits;

__sfr __at (0xF8B) LATC;
volatile __LATCbits_t __at (0xF8B) LATCbits;

__sfr __at (0xF8C) LATD;
volatile __LATDbits_t __at (0xF8C) LATDbits;

__sfr __at (0xF8D) LATE;
volatile __LATEbits_t __at (0xF8D) LATEbits;

__sfr __at (0xF8E) LATF;
volatile __LATFbits_t __at (0xF8E) LATFbits;

__sfr __at (0xF8F) LATG;
volatile __LATGbits_t __at (0xF8F) LATGbits;

__sfr __at (0xF92) DDRA;
volatile __DDRAbits_t __at (0xF92) DDRAbits;

__sfr __at (0xF92) TRISA;
volatile __TRISAbits_t __at (0xF92) TRISAbits;

__sfr __at (0xF93) DDRB;
volatile __DDRBbits_t __at (0xF93) DDRBbits;

__sfr __at (0xF93) TRISB;
volatile __TRISBbits_t __at (0xF93) TRISBbits;

__sfr __at (0xF94) DDRC;
volatile __DDRCbits_t __at (0xF94) DDRCbits;

__sfr __at (0xF94) TRISC;
volatile __TRISCbits_t __at (0xF94) TRISCbits;

__sfr __at (0xF95) DDRD;
volatile __DDRDbits_t __at (0xF95) DDRDbits;

__sfr __at (0xF95) TRISD;
volatile __TRISDbits_t __at (0xF95) TRISDbits;

__sfr __at (0xF96) DDRE;
volatile __DDREbits_t __at (0xF96) DDREbits;

__sfr __at (0xF96) TRISE;
volatile __TRISEbits_t __at (0xF96) TRISEbits;

__sfr __at (0xF97) DDRF;
volatile __DDRFbits_t __at (0xF97) DDRFbits;

__sfr __at (0xF97) TRISF;
volatile __TRISFbits_t __at (0xF97) TRISFbits;

__sfr __at (0xF98) DDRG;
volatile __DDRGbits_t __at (0xF98) DDRGbits;

__sfr __at (0xF98) TRISG;
volatile __TRISGbits_t __at (0xF98) TRISGbits;

__sfr __at (0xF9B) OSCTUNE;
volatile __OSCTUNEbits_t __at (0xF9B) OSCTUNEbits;

__sfr __at (0xF9D) PIE1;
volatile __PIE1bits_t __at (0xF9D) PIE1bits;

__sfr __at (0xF9E) PIR1;
volatile __PIR1bits_t __at (0xF9E) PIR1bits;

__sfr __at (0xF9F) IPR1;
volatile __IPR1bits_t __at (0xF9F) IPR1bits;

__sfr __at (0xFA0) PIE2;
volatile __PIE2bits_t __at (0xFA0) PIE2bits;

__sfr __at (0xFA1) PIR2;
volatile __PIR2bits_t __at (0xFA1) PIR2bits;

__sfr __at (0xFA2) IPR2;
volatile __IPR2bits_t __at (0xFA2) IPR2bits;

__sfr __at (0xFA3) PIE3;
volatile __PIE3bits_t __at (0xFA3) PIE3bits;

__sfr __at (0xFA4) PIR3;
volatile __PIR3bits_t __at (0xFA4) PIR3bits;

__sfr __at (0xFA5) IPR3;
volatile __IPR3bits_t __at (0xFA5) IPR3bits;

__sfr __at (0xFA6) EECON1;
volatile __EECON1bits_t __at (0xFA6) EECON1bits;

__sfr __at (0xFA7) EECON2;

__sfr __at (0xFAB) RCSTA;
volatile __RCSTAbits_t __at (0xFAB) RCSTAbits;

__sfr __at (0xFAB) RCSTA1;
volatile __RCSTA1bits_t __at (0xFAB) RCSTA1bits;

__sfr __at (0xFAC) TXSTA;
volatile __TXSTAbits_t __at (0xFAC) TXSTAbits;

__sfr __at (0xFAC) TXSTA1;
volatile __TXSTA1bits_t __at (0xFAC) TXSTA1bits;

__sfr __at (0xFAD) TXREG;

__sfr __at (0xFAD) TXREG1;

__sfr __at (0xFAE) RCREG;

__sfr __at (0xFAE) RCREG1;

__sfr __at (0xFAF) SPBRG;

__sfr __at (0xFAF) SPBRG1;

__sfr __at (0xFB1) T3CON;
volatile __T3CONbits_t __at (0xFB1) T3CONbits;

__sfr __at (0xFB2) TMR3L;

__sfr __at (0xFB3) TMR3H;

__sfr __at (0xFB4) CMCON;
volatile __CMCONbits_t __at (0xFB4) CMCONbits;

__sfr __at (0xFB5) CVRCON;
volatile __CVRCONbits_t __at (0xFB5) CVRCONbits;

__sfr __at (0xFB6) ECCP1AS;
volatile __ECCP1ASbits_t __at (0xFB6) ECCP1ASbits;

__sfr __at (0xFB7) CCP3CON;
volatile __CCP3CONbits_t __at (0xFB7) CCP3CONbits;

__sfr __at (0xFB7) ECCP3CON;
volatile __ECCP3CONbits_t __at (0xFB7) ECCP3CONbits;

__sfr __at (0xFB8) CCPR3;

__sfr __at (0xFB8) CCPR3L;

__sfr __at (0xFB9) CCPR3H;

__sfr __at (0xFBA) CCP2CON;
volatile __CCP2CONbits_t __at (0xFBA) CCP2CONbits;

__sfr __at (0xFBA) ECCP2CON;
volatile __ECCP2CONbits_t __at (0xFBA) ECCP2CONbits;

__sfr __at (0xFBB) CCPR2;

__sfr __at (0xFBB) CCPR2L;

__sfr __at (0xFBC) CCPR2H;

__sfr __at (0xFBD) CCP1CON;
volatile __CCP1CONbits_t __at (0xFBD) CCP1CONbits;

__sfr __at (0xFBD) ECCP1CON;
volatile __ECCP1CONbits_t __at (0xFBD) ECCP1CONbits;

__sfr __at (0xFBE) CCPR1;

__sfr __at (0xFBE) CCPR1L;

__sfr __at (0xFBF) CCPR1H;

__sfr __at (0xFC0) ADCON2;
volatile __ADCON2bits_t __at (0xFC0) ADCON2bits;

__sfr __at (0xFC1) ADCON1;
volatile __ADCON1bits_t __at (0xFC1) ADCON1bits;

__sfr __at (0xFC2) ADCON0;
volatile __ADCON0bits_t __at (0xFC2) ADCON0bits;

__sfr __at (0xFC3) ADRES;

__sfr __at (0xFC3) ADRESL;

__sfr __at (0xFC4) ADRESH;

__sfr __at (0xFC5) SSP1CON2;
volatile __SSP1CON2bits_t __at (0xFC5) SSP1CON2bits;

__sfr __at (0xFC5) SSPCON2;
volatile __SSPCON2bits_t __at (0xFC5) SSPCON2bits;

__sfr __at (0xFC6) SSP1CON1;
volatile __SSP1CON1bits_t __at (0xFC6) SSP1CON1bits;

__sfr __at (0xFC6) SSPCON1;
volatile __SSPCON1bits_t __at (0xFC6) SSPCON1bits;

__sfr __at (0xFC7) SSP1STAT;
volatile __SSP1STATbits_t __at (0xFC7) SSP1STATbits;

__sfr __at (0xFC7) SSPSTAT;
volatile __SSPSTATbits_t __at (0xFC7) SSPSTATbits;

__sfr __at (0xFC8) SSP1ADD;

__sfr __at (0xFC8) SSPADD;

__sfr __at (0xFC9) SSP1BUF;

__sfr __at (0xFC9) SSPBUF;

__sfr __at (0xFCA) T2CON;
volatile __T2CONbits_t __at (0xFCA) T2CONbits;

__sfr __at (0xFCB) PR2;

__sfr __at (0xFCC) TMR2;

__sfr __at (0xFCD) T1CON;
volatile __T1CONbits_t __at (0xFCD) T1CONbits;

__sfr __at (0xFCE) TMR1L;

__sfr __at (0xFCF) TMR1H;

__sfr __at (0xFD0) RCON;
volatile __RCONbits_t __at (0xFD0) RCONbits;

__sfr __at (0xFD1) WDTCON;
volatile __WDTCONbits_t __at (0xFD1) WDTCONbits;

__sfr __at (0xFD2) ECON1;
volatile __ECON1bits_t __at (0xFD2) ECON1bits;

__sfr __at (0xFD3) OSCCON;
volatile __OSCCONbits_t __at (0xFD3) OSCCONbits;

__sfr __at (0xFD5) T0CON;
volatile __T0CONbits_t __at (0xFD5) T0CONbits;

__sfr __at (0xFD6) TMR0L;

__sfr __at (0xFD7) TMR0H;

__sfr __at (0xFD8) STATUS;
volatile __STATUSbits_t __at (0xFD8) STATUSbits;

__sfr __at (0xFD9) FSR2L;

__sfr __at (0xFDA) FSR2H;

__sfr __at (0xFDB) PLUSW2;

__sfr __at (0xFDC) PREINC2;

__sfr __at (0xFDD) POSTDEC2;

__sfr __at (0xFDE) POSTINC2;

__sfr __at (0xFDF) INDF2;

__sfr __at (0xFE0) BSR;

__sfr __at (0xFE1) FSR1L;

__sfr __at (0xFE2) FSR1H;

__sfr __at (0xFE3) PLUSW1;

__sfr __at (0xFE4) PREINC1;

__sfr __at (0xFE5) POSTDEC1;

__sfr __at (0xFE6) POSTINC1;

__sfr __at (0xFE7) INDF1;

__sfr __at (0xFE8) WREG;

__sfr __at (0xFE9) FSR0L;

__sfr __at (0xFEA) FSR0H;

__sfr __at (0xFEB) PLUSW0;

__sfr __at (0xFEC) PREINC0;

__sfr __at (0xFED) POSTDEC0;

__sfr __at (0xFEE) POSTINC0;

__sfr __at (0xFEF) INDF0;

__sfr __at (0xFF0) INTCON3;
volatile __INTCON3bits_t __at (0xFF0) INTCON3bits;

__sfr __at (0xFF1) INTCON2;
volatile __INTCON2bits_t __at (0xFF1) INTCON2bits;

__sfr __at (0xFF2) INTCON;
volatile __INTCONbits_t __at (0xFF2) INTCONbits;

__sfr __at (0xFF3) PROD;

__sfr __at (0xFF3) PRODL;

__sfr __at (0xFF4) PRODH;

__sfr __at (0xFF5) TABLAT;

__sfr __at (0xFF6) TBLPTR;

__sfr __at (0xFF6) TBLPTRL;

__sfr __at (0xFF7) TBLPTRH;

__sfr __at (0xFF8) TBLPTRU;

__sfr __at (0xFF9) PC;

__sfr __at (0xFF9) PCL;

__sfr __at (0xFFA) PCLATH;

__sfr __at (0xFFB) PCLATU;

__sfr __at (0xFFC) STKPTR;
volatile __STKPTRbits_t __at (0xFFC) STKPTRbits;

__sfr __at (0xFFD) TOS;

__sfr __at (0xFFD) TOSL;

__sfr __at (0xFFE) TOSH;

__sfr __at (0xFFF) TOSU;


