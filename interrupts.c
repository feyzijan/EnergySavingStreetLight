#include <xc.h>
#include "interrupts.h"

extern unsigned char test_mode;

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
    PIE2bits.C1IE = 1; // Toggle interrupt source for comparator  
    INTCONbits.PEIE = 1; // Toggle peripheral interrupts  
    INTCONbits.GIE = 1; //Toggle interrupts Globally

}


/************************************
 * High priority interrupt service routine
 * Toggle the state of the LED RH3 whenever the LDR senses a shift in light levels. 
 * Initialise Timer0 with correct values so it overflows in almost precisely 
 * (1 hour or 1 second in test mode) 
 ************************************/
void __interrupt(high_priority) HighISR()
{
    if(PIR0bits.TMR0IF == 1) { // check interrupt flag for timer        
        if(test_mode){
            //LATDbits.LATD7 =1; //for testing/debugging purposes only 
            // write 3036 into TMR0L bits to fix timer to 1 second
            TMR0H = 0b00001011;
            TMR0L = 0b11011100;
        } else {
            // Write appropriate value to get overflow in exactly one hour 
            TMR0H = 0b00101011; 
            TMR0L = 0b00100011;
        }
         PIR0bits.TMR0IF = 0; // clear interrupt flag
   }
   if(PIR2bits.C1IF == 1) { // check interrupt flag for comparator
        //LATDbits.LATD7 =1; //for testing/debugging purposes only 
        LATHbits.LATH3 = !LATHbits.LATH3; // take action - toggle LED 
        PIR2bits.C1IF = 0; // clear interrupt flag
   }
}


