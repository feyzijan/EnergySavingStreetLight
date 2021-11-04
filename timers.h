#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000
// redefine TimerBits for ease of reference
#define TimerL0 TMR0Lbits.TMR0L0
#define TimerL1 TMR0Lbits.TMR0L1
#define TimerL2 TMR0Lbits.TMR0L2
#define TimerL3 TMR0Lbits.TMR0L3
#define TimerL4 TMR0Lbits.TMR0L4
#define TimerL5 TMR0Lbits.TMR0L5
#define TimerL6 TMR0Lbits.TMR0L6
#define TimerL7 TMR0Lbits.TMR0L7
#define TimerH0 TMR0Hbits.TMR0H0
#define TimerH1 TMR0Hbits.TMR0H1
#define TimerH2 TMR0Hbits.TMR0H2
#define TimerH3 TMR0Hbits.TMR0H3
#define TimerH4 TMR0Hbits.TMR0H4
#define TimerH5 TMR0Hbits.TMR0H5
#define TimerH6 TMR0Hbits.TMR0H6
#define TimerH7 TMR0Hbits.TMR0H7

#define Timer1L0 TMR1bits.TMR1L0
#define Timer1L1 TMR1bits.TMR1L1
#define Timer1L2 TMR1bits.TMR1L2
#define Timer1L3 TMR1bits.TMR1L3
#define Timer1L4 TMR1bits.TMR1L4
#define Timer1L5 TMR1bits.TMR1L5
#define Timer1L6 TMR1bits.TMR1L6
#define Timer1L7 TMR1bits.TMR1L7
#define Timer1H0 TMR1bits.TMR1H0
#define Timer1H1 TMR1bits.TMR1H1
#define Timer1H2 TMR1bits.TMR1H2
#define Timer1H3 TMR1bits.TMR1H3
#define Timer1H4 TMR1bits.TMR1H4
#define Timer1H5 TMR1bits.TMR1H5
#define Timer1H6 TMR1bits.TMR1H6
#define Timer1H7 TMR1bits.TMR1H7

void Timer0_init(void);
unsigned char get8MSB_TMR0(void);
unsigned char get8LSB_TMR0(void);
void Timer1_init(void);
unsigned char get8LSB_TMR1(void);
unsigned char get8MSB_TMR1(void);

#endif
