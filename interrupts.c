#include <xc.h>
#include "interrupts.h"


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
 * Toggle the state of the LED RH3 whenever the timer overflows
************************************/

 
  
void __interrupt(high_priority) HighISR()
{
    if(PIR0bits.TMR0IF == 1) { // check interrupt flag for timer
        //LATHbits.LATH3 = !LATHbits.LATH3; // take action - toggle button for testing
        TMR0Lbits.TMR0L5 = TMR0Lbits.TMR0L2 = 1;  // write 36 into TMR0L bits to fix timer to 1 second
        /*real mode
        TMR0H = 0b01100110;
        TMR0L = 0b00001111;
        //write bits so it starts correctly for 1 hour
        // 0b0110011000001111 - with PS:1024 and CS: 
        
         */
         PIR0bits.TMR0IF = 0; // clear interrupt flag
   }
    
    if(PIR2bits.C1IF == 1) { // check interrupt flag for comparator
        LATHbits.LATH3 = !LATHbits.LATH3; // take action
        PIR2bits.C1IF = 0; // clear interrupt flag
   }
}
  
/*
 TODO:
 * Disable comparator interrupt between seconds 1-5
 * Make timer overflow every 24 seconds
 */
 



/************************************
 * Low priority interrupt service routine
 * Toggle the state of the LED RH3 whenever the DAC threshold
 *  value is passed, i.e. whenever you hold your hands over the LDR
************************************/

/*
void __interrupt(low_priority) LowISR()
{    
    if(PIR2bits.C1IF == 1) { // check interrupt flag
        LATHbits.LATH3 = !LATHbits.LATH3; // take action
        PIR2bits.C1IF = 0; // clear interrupt flag
   }
}
 * 
 * */

