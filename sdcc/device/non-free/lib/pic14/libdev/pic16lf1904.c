/* Register definitions for pic16lf1904.
 * This file was automatically generated by:
 *   inc2h.pl V4850
 *   Copyright (c) 2002, Kevin L. Pauba, All Rights Reserved
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
#include <pic16lf1904.h>

__sfr  __at (INDF0_ADDR)                   INDF0;
__sfr  __at (INDF1_ADDR)                   INDF1;
__sfr  __at (PCL_ADDR)                     PCL;
__sfr  __at (STATUS_ADDR)                  STATUS;
__sfr  __at (FSR0_ADDR)                    FSR0;
__sfr  __at (FSR0L_ADDR)                   FSR0L;
__sfr  __at (FSR0H_ADDR)                   FSR0H;
__sfr  __at (FSR1_ADDR)                    FSR1;
__sfr  __at (FSR1L_ADDR)                   FSR1L;
__sfr  __at (FSR1H_ADDR)                   FSR1H;
__sfr  __at (BSR_ADDR)                     BSR;
__sfr  __at (WREG_ADDR)                    WREG;
__sfr  __at (PCLATH_ADDR)                  PCLATH;
__sfr  __at (INTCON_ADDR)                  INTCON;
__sfr  __at (PORTA_ADDR)                   PORTA;
__sfr  __at (PORTB_ADDR)                   PORTB;
__sfr  __at (PORTC_ADDR)                   PORTC;
__sfr  __at (PORTD_ADDR)                   PORTD;
__sfr  __at (PORTE_ADDR)                   PORTE;
__sfr  __at (PIR1_ADDR)                    PIR1;
__sfr  __at (PIR2_ADDR)                    PIR2;
__sfr  __at (TMR0_ADDR)                    TMR0;
__sfr  __at (TMR1_ADDR)                    TMR1;
__sfr  __at (TMR1L_ADDR)                   TMR1L;
__sfr  __at (TMR1H_ADDR)                   TMR1H;
__sfr  __at (T1CON_ADDR)                   T1CON;
__sfr  __at (T1GCON_ADDR)                  T1GCON;
__sfr  __at (TRISA_ADDR)                   TRISA;
__sfr  __at (TRISB_ADDR)                   TRISB;
__sfr  __at (TRISC_ADDR)                   TRISC;
__sfr  __at (TRISD_ADDR)                   TRISD;
__sfr  __at (TRISE_ADDR)                   TRISE;
__sfr  __at (PIE1_ADDR)                    PIE1;
__sfr  __at (PIE2_ADDR)                    PIE2;
__sfr  __at (OPTION_REG_ADDR)              OPTION_REG;
__sfr  __at (PCON_ADDR)                    PCON;
__sfr  __at (WDTCON_ADDR)                  WDTCON;
__sfr  __at (OSCCON_ADDR)                  OSCCON;
__sfr  __at (OSCSTAT_ADDR)                 OSCSTAT;
__sfr  __at (ADRES_ADDR)                   ADRES;
__sfr  __at (ADRESL_ADDR)                  ADRESL;
__sfr  __at (ADRESH_ADDR)                  ADRESH;
__sfr  __at (ADCON0_ADDR)                  ADCON0;
__sfr  __at (ADCON1_ADDR)                  ADCON1;
__sfr  __at (LATA_ADDR)                    LATA;
__sfr  __at (LATB_ADDR)                    LATB;
__sfr  __at (LATC_ADDR)                    LATC;
__sfr  __at (LATD_ADDR)                    LATD;
__sfr  __at (LATE_ADDR)                    LATE;
__sfr  __at (BORCON_ADDR)                  BORCON;
__sfr  __at (FVRCON_ADDR)                  FVRCON;
__sfr  __at (ANSELA_ADDR)                  ANSELA;
__sfr  __at (ANSELB_ADDR)                  ANSELB;
__sfr  __at (ANSELE_ADDR)                  ANSELE;
__sfr  __at (PMADR_ADDR)                   PMADR;
__sfr  __at (PMADRL_ADDR)                  PMADRL;
__sfr  __at (PMADRH_ADDR)                  PMADRH;
__sfr  __at (PMDAT_ADDR)                   PMDAT;
__sfr  __at (PMDATL_ADDR)                  PMDATL;
__sfr  __at (PMDATH_ADDR)                  PMDATH;
__sfr  __at (PMCON1_ADDR)                  PMCON1;
__sfr  __at (PMCON2_ADDR)                  PMCON2;
__sfr  __at (RC1REG_ADDR)                  RC1REG;
__sfr  __at (RCREG_ADDR)                   RCREG;
__sfr  __at (RCREG1_ADDR)                  RCREG1;
__sfr  __at (TX1REG_ADDR)                  TX1REG;
__sfr  __at (TXREG_ADDR)                   TXREG;
__sfr  __at (TXREG1_ADDR)                  TXREG1;
__sfr  __at (SP1BRGL_ADDR)                 SP1BRGL;
__sfr  __at (SPBRG_ADDR)                   SPBRG;
__sfr  __at (SPBRGL_ADDR)                  SPBRGL;
__sfr  __at (SPBRGL1_ADDR)                 SPBRGL1;
__sfr  __at (SP1BRGH_ADDR)                 SP1BRGH;
__sfr  __at (SPBRGH_ADDR)                  SPBRGH;
__sfr  __at (SPBRGH1_ADDR)                 SPBRGH1;
__sfr  __at (RC1STA_ADDR)                  RC1STA;
__sfr  __at (RCSTA_ADDR)                   RCSTA;
__sfr  __at (RCSTA1_ADDR)                  RCSTA1;
__sfr  __at (TX1STA_ADDR)                  TX1STA;
__sfr  __at (TXSTA_ADDR)                   TXSTA;
__sfr  __at (TXSTA1_ADDR)                  TXSTA1;
__sfr  __at (BAUD1CON_ADDR)                BAUD1CON;
__sfr  __at (BAUDCON_ADDR)                 BAUDCON;
__sfr  __at (BAUDCON1_ADDR)                BAUDCON1;
__sfr  __at (WPUB_ADDR)                    WPUB;
__sfr  __at (WPUE_ADDR)                    WPUE;
__sfr  __at (IOCBP_ADDR)                   IOCBP;
__sfr  __at (IOCBN_ADDR)                   IOCBN;
__sfr  __at (IOCBF_ADDR)                   IOCBF;
__sfr  __at (LCDCON_ADDR)                  LCDCON;
__sfr  __at (LCDPS_ADDR)                   LCDPS;
__sfr  __at (LCDREF_ADDR)                  LCDREF;
__sfr  __at (LCDCST_ADDR)                  LCDCST;
__sfr  __at (LCDRL_ADDR)                   LCDRL;
__sfr  __at (LCDSE0_ADDR)                  LCDSE0;
__sfr  __at (LCDSE1_ADDR)                  LCDSE1;
__sfr  __at (LCDSE2_ADDR)                  LCDSE2;
__sfr  __at (LCDSE2_ADDR)                  LCDSE2;
__sfr  __at (LCDDATA0_ADDR)                LCDDATA0;
__sfr  __at (LCDDATA1_ADDR)                LCDDATA1;
__sfr  __at (LCDDATA2_ADDR)                LCDDATA2;
__sfr  __at (LCDDATA3_ADDR)                LCDDATA3;
__sfr  __at (LCDDATA4_ADDR)                LCDDATA4;
__sfr  __at (LCDDATA5_ADDR)                LCDDATA5;
__sfr  __at (LCDDATA6_ADDR)                LCDDATA6;
__sfr  __at (LCDDATA7_ADDR)                LCDDATA7;
__sfr  __at (LCDDATA8_ADDR)                LCDDATA8;
__sfr  __at (LCDDATA9_ADDR)                LCDDATA9;
__sfr  __at (LCDDATA10_ADDR)               LCDDATA10;
__sfr  __at (LCDDATA11_ADDR)               LCDDATA11;
__sfr  __at (LCDDATA12_ADDR)               LCDDATA12;
__sfr  __at (LCDDATA15_ADDR)               LCDDATA15;
__sfr  __at (LCDDATA18_ADDR)               LCDDATA18;
__sfr  __at (LCDDATA21_ADDR)               LCDDATA21;
__sfr  __at (STATUS_SHAD_ADDR)             STATUS_SHAD;
__sfr  __at (WREG_SHAD_ADDR)               WREG_SHAD;
__sfr  __at (BSR_SHAD_ADDR)                BSR_SHAD;
__sfr  __at (PCLATH_SHAD_ADDR)             PCLATH_SHAD;
__sfr  __at (FSR0L_SHAD_ADDR)              FSR0L_SHAD;
__sfr  __at (FSR0H_SHAD_ADDR)              FSR0H_SHAD;
__sfr  __at (FSR1L_SHAD_ADDR)              FSR1L_SHAD;
__sfr  __at (FSR1H_SHAD_ADDR)              FSR1H_SHAD;
__sfr  __at (STKPTR_ADDR)                  STKPTR;
__sfr  __at (TOSL_ADDR)                    TOSL;
__sfr  __at (TOSH_ADDR)                    TOSH;

//
// bitfield definitions
//
volatile __ADCON0bits_t __at(ADCON0_ADDR) ADCON0bits;
volatile __ADCON1bits_t __at(ADCON1_ADDR) ADCON1bits;
volatile __ANSELAbits_t __at(ANSELA_ADDR) ANSELAbits;
volatile __ANSELBbits_t __at(ANSELB_ADDR) ANSELBbits;
volatile __ANSELEbits_t __at(ANSELE_ADDR) ANSELEbits;
volatile __BAUD1CONbits_t __at(BAUD1CON_ADDR) BAUD1CONbits;
volatile __BAUDCONbits_t __at(BAUDCON_ADDR) BAUDCONbits;
volatile __BAUDCON1bits_t __at(BAUDCON1_ADDR) BAUDCON1bits;
volatile __BORCONbits_t __at(BORCON_ADDR) BORCONbits;
volatile __BSRbits_t __at(BSR_ADDR) BSRbits;
volatile __FVRCONbits_t __at(FVRCON_ADDR) FVRCONbits;
volatile __INTCONbits_t __at(INTCON_ADDR) INTCONbits;
volatile __IOCBFbits_t __at(IOCBF_ADDR) IOCBFbits;
volatile __IOCBNbits_t __at(IOCBN_ADDR) IOCBNbits;
volatile __IOCBPbits_t __at(IOCBP_ADDR) IOCBPbits;
volatile __LATAbits_t __at(LATA_ADDR) LATAbits;
volatile __LATBbits_t __at(LATB_ADDR) LATBbits;
volatile __LATCbits_t __at(LATC_ADDR) LATCbits;
volatile __LATDbits_t __at(LATD_ADDR) LATDbits;
volatile __LATEbits_t __at(LATE_ADDR) LATEbits;
volatile __LCDCONbits_t __at(LCDCON_ADDR) LCDCONbits;
volatile __LCDCSTbits_t __at(LCDCST_ADDR) LCDCSTbits;
volatile __LCDDATA0bits_t __at(LCDDATA0_ADDR) LCDDATA0bits;
volatile __LCDDATA1bits_t __at(LCDDATA1_ADDR) LCDDATA1bits;
volatile __LCDDATA10bits_t __at(LCDDATA10_ADDR) LCDDATA10bits;
volatile __LCDDATA11bits_t __at(LCDDATA11_ADDR) LCDDATA11bits;
volatile __LCDDATA12bits_t __at(LCDDATA12_ADDR) LCDDATA12bits;
volatile __LCDDATA15bits_t __at(LCDDATA15_ADDR) LCDDATA15bits;
volatile __LCDDATA18bits_t __at(LCDDATA18_ADDR) LCDDATA18bits;
volatile __LCDDATA2bits_t __at(LCDDATA2_ADDR) LCDDATA2bits;
volatile __LCDDATA21bits_t __at(LCDDATA21_ADDR) LCDDATA21bits;
volatile __LCDDATA3bits_t __at(LCDDATA3_ADDR) LCDDATA3bits;
volatile __LCDDATA4bits_t __at(LCDDATA4_ADDR) LCDDATA4bits;
volatile __LCDDATA5bits_t __at(LCDDATA5_ADDR) LCDDATA5bits;
volatile __LCDDATA6bits_t __at(LCDDATA6_ADDR) LCDDATA6bits;
volatile __LCDDATA7bits_t __at(LCDDATA7_ADDR) LCDDATA7bits;
volatile __LCDDATA8bits_t __at(LCDDATA8_ADDR) LCDDATA8bits;
volatile __LCDDATA9bits_t __at(LCDDATA9_ADDR) LCDDATA9bits;
volatile __LCDPSbits_t __at(LCDPS_ADDR) LCDPSbits;
volatile __LCDREFbits_t __at(LCDREF_ADDR) LCDREFbits;
volatile __LCDRLbits_t __at(LCDRL_ADDR) LCDRLbits;
volatile __LCDSE0bits_t __at(LCDSE0_ADDR) LCDSE0bits;
volatile __LCDSE1bits_t __at(LCDSE1_ADDR) LCDSE1bits;
volatile __LCDSE2bits_t __at(LCDSE2_ADDR) LCDSE2bits;
volatile __OPTION_REGbits_t __at(OPTION_REG_ADDR) OPTION_REGbits;
volatile __OSCCONbits_t __at(OSCCON_ADDR) OSCCONbits;
volatile __OSCSTATbits_t __at(OSCSTAT_ADDR) OSCSTATbits;
volatile __PCONbits_t __at(PCON_ADDR) PCONbits;
volatile __PIE1bits_t __at(PIE1_ADDR) PIE1bits;
volatile __PIE2bits_t __at(PIE2_ADDR) PIE2bits;
volatile __PIR1bits_t __at(PIR1_ADDR) PIR1bits;
volatile __PIR2bits_t __at(PIR2_ADDR) PIR2bits;
volatile __PMCON1bits_t __at(PMCON1_ADDR) PMCON1bits;
volatile __PORTAbits_t __at(PORTA_ADDR) PORTAbits;
volatile __PORTBbits_t __at(PORTB_ADDR) PORTBbits;
volatile __PORTCbits_t __at(PORTC_ADDR) PORTCbits;
volatile __PORTDbits_t __at(PORTD_ADDR) PORTDbits;
volatile __PORTEbits_t __at(PORTE_ADDR) PORTEbits;
volatile __RC1STAbits_t __at(RC1STA_ADDR) RC1STAbits;
volatile __RCSTAbits_t __at(RCSTA_ADDR) RCSTAbits;
volatile __RCSTA1bits_t __at(RCSTA1_ADDR) RCSTA1bits;
volatile __SP1BRGHbits_t __at(SP1BRGH_ADDR) SP1BRGHbits;
volatile __SP1BRGLbits_t __at(SP1BRGL_ADDR) SP1BRGLbits;
volatile __SPBRGbits_t __at(SPBRG_ADDR) SPBRGbits;
volatile __SPBRGHbits_t __at(SPBRGH_ADDR) SPBRGHbits;
volatile __SPBRGH1bits_t __at(SPBRGH1_ADDR) SPBRGH1bits;
volatile __SPBRGLbits_t __at(SPBRGL_ADDR) SPBRGLbits;
volatile __SPBRGL1bits_t __at(SPBRGL1_ADDR) SPBRGL1bits;
volatile __STATUSbits_t __at(STATUS_ADDR) STATUSbits;
volatile __STATUS_SHADbits_t __at(STATUS_SHAD_ADDR) STATUS_SHADbits;
volatile __T1CONbits_t __at(T1CON_ADDR) T1CONbits;
volatile __T1GCONbits_t __at(T1GCON_ADDR) T1GCONbits;
volatile __TRISAbits_t __at(TRISA_ADDR) TRISAbits;
volatile __TRISBbits_t __at(TRISB_ADDR) TRISBbits;
volatile __TRISCbits_t __at(TRISC_ADDR) TRISCbits;
volatile __TRISDbits_t __at(TRISD_ADDR) TRISDbits;
volatile __TRISEbits_t __at(TRISE_ADDR) TRISEbits;
volatile __TX1STAbits_t __at(TX1STA_ADDR) TX1STAbits;
volatile __TXSTAbits_t __at(TXSTA_ADDR) TXSTAbits;
volatile __TXSTA1bits_t __at(TXSTA1_ADDR) TXSTA1bits;
volatile __WDTCONbits_t __at(WDTCON_ADDR) WDTCONbits;
volatile __WPUBbits_t __at(WPUB_ADDR) WPUBbits;
volatile __WPUEbits_t __at(WPUE_ADDR) WPUEbits;

