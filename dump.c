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

/*
         
        if (hour == 24){
            TMR1L = 0; //reset hour counter to zero
            day_of_year ++;
            
            //increment day_of_month, month
         
            if (day_of_month == month_lengths[month-1])
            {
                day_of_month = 1;
                if(month < 12){
                    month ++;
                } else {
                    month = 1;
                    year ++;
                    day_of_year = 0;
                }
            } else {
                day_of_month ++;
            }
            
            //increment day of week
            if (day_of_week < 7) {
                day_of_week ++;
            } else {
                day_of_week = 1;
            }
            
            //check for DST
         * 
         * 
 
 //leap year check - Make this very rare!
        if (year % 4 == 0){
            leap = 1;
            month_lengths[1] = 29;
        } else{
            month_lengths[1] = 28;
        }
           
 
 * unsigned char day_of_month = 0; // 1-31
unsigned char month; //1-12
 * 
unsigned char month_lengths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
 
 
 */

 
            
            
            
            



