#include <xc.h>
#include "timers.h"

extern int timer;

/************************************
 * Function to set up timer 0
************************************/
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4 ( Our base oscillation frequency(Fosc) is 64 Mhz)
    T0CON1bits.T0ASYNC=1; // needed to ensure correct operation when Fosc/4 used as clock source
    T0CON1bits.T0CKPS=0b1000 ; // Prescaler =  1000 = 1:256 - for one second we need 244 
    T0CON0bits.T016BIT=1;	//16bit mode	
    
    PIE0bits.TMR0IE = 1; //enable interrupt
    IPR0bits.TMR0IP = 1; //priority high
    
    // Initialise the timer registers at 0 - write High-Reg first as it updates when Low-Reg is written
    TMR0H = 0;
    TMR0L = 0;
    
    T0CON0bits.T0EN=1;	//start the timer
}

void Timer1_init(void) // see page 365 for possible error cause
{ 
    TMR1CLKbits.CS = 0b1000; // select clock source: TMR0 overflow
    T1CONbits.CKPS = 0b00; // select pre-scaler: 1:1 
    //T1CONbits.RD16 = 1; //Enables register read/write of Timer in one 16-bit operation
    PIE5bits.TMR1IE = 1; //enables interrupt
    IPR5bits.TMR1IP = 1; //interrupt priority set high
    /* Initialise the timer registers at 0 */
    TMR1H = 0;
    TMR1L = 0;
    /*Enable timer and counter */
    T1CONbits.ON = 1; 
    T1GCONbits.GE = 1;
}

unsigned char get8LSB_TMR1(void){ 
    return TMR1L; 
}
unsigned char get8MSB_TMR1(void){
    TMR1L;
    return TMR1H;
}


/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned char get8MSB_TMR0(void)
{
    TMR0L;
    return TMR0H;
}

unsigned char get8LSB_TMR0(void)
{
    return TMR0L;
}
