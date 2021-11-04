/*
 * Hold some unused but written code here
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

 /* Timer 3
 * 
void Timer3_init(void) // see page 365 for possible error cause
{ 
    TMR3CLKbits.CS = 0b1001; // select clock source: TMR1 overflow
    
    T3CONbits.CKPS = 0b00; // select pre-scaler: 1:1 
    //T1CONbits.RD16 = 1; //Enables register read/write of Timer in one 16-bit operation
    PIE5bits.TMR3IE = 1; //enables interrupt
    IPR5bits.TMR3IP = 1; //interrupt priority set high
    // Initialise the timer registers at 0 
    TMR3H = 0;
    TMR3L = 0;
    //Enable timer and counter 
    T3CONbits.ON = 1; 
    T3GCONbits.GE = 1;
}

unsigned int get8LSB_TMR3(void){ 
    return TMR3L; 
}
unsigned int get8MSB_TMR3(void){
    TMR3L;
    return TMR3H;
}

#define Timer3L0 TMR3bits.TMR3L0
#define Timer3L1 TMR3bits.TMR3L1
#define Timer3L2 TMR3bits.TMR3L2
#define Timer3L3 TMR3bits.TMR3L3
#define Timer3L4 TMR3bits.TMR3L4
#define Timer3L5 TMR3bits.TMR3L5
#define Timer3L6 TMR3bits.TMR3L6
#define Timer3L7 TMR3bits.TMR3L7
#define Timer3H0 TMR3bits.TMR3H0
#define Timer3H1 TMR3bits.TMR3H1
#define Timer3H2 TMR3bits.TMR3H2
#define Timer3H3 TMR3bits.TMR3H3
#define Timer3H4 TMR3bits.TMR3H4
#define Timer3H5 TMR3bits.TMR3H5
#define Timer3H6 TMR3bits.TMR3H6
#define Timer3H7 TMR3bits.TMR3H7
  * 
void Timer3_init(void);
unsigned int get8LSB_TMR3(void);
unsigned int get8MSB_TMR3(void);
*/


