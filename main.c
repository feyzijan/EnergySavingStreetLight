// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bit
// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "interrupts.h"
#include "comparator.h"
#include "LEDarray.h"
#include "timers.h"
 
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz
#define testmode 1 // 1: test mode 1hour represented by 1s, 0:real mode
#define DST_fwd_min = 84
#define DST_fwd_max = 90
#define DST_bwd_min = 298
#define DST_bwd_max = 304



//variables to keep track of time
unsigned char hour = 0; //0-24
unsigned char day_of_week = 1; //1-7
unsigned int day_of_year = 1; //1-365
unsigned char year = 21; //1-99
unsigned char leap = 0; //1 = leap, 0 = nonleap

unsigned char dst_fwd = 1;
unsigned char dst_bwd = 1;

void main(void) {
    
    // Initialisation
    Comp1_init();
    Interrupts_init();
    LEDarray_init();
    Timer0_init();
    Timer1_init(); 
    
    // setup pin for RH3 LED - to be toggled with interrupt - for testing only
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    
    while (1) { 
       
        hour = get8LSB_TMR1(); //get hour(in testing case seconds)
        LEDarray_disp_bin(hour); //display hour 
       
        if (hour > 1 && hour <5 ){
            LEDarray_disp_bin(0);//switch off
            CM1CON0bits.EN=0; //disable comparator
        } else {
             CM1CON0bits.EN=0; //enable comparator
        }
        
        //End of day 
        //TODO put this in function
        if (hour == 24){
            TMR1L = 0; //reset hour counter to zero
            day_of_year ++;
            day_of_week ++;
            if(day_of_week == 8) day_of_week = 1; //check for next week
            
            //increment day_of_year, year, and update leap
     
            if (day_of_year > 365){
                if(leap == 0)
                { // normal year- move to next year
                    day_of_year = 1;
                    year ++;
                    dst_fwd = dst_bwd = 0; //toggle daylights savings
                    if (year%4 == 0) leap = 1; // check if new year is leap year
                } 
                else if(leap == 1)
                { //current year is leap year
                    if(day_of_year > 366)
                    {
                        day_of_year = 1;
                        year++;
                        dst_fwd = dst_bwd = 0; //toggle daylight savings
                        leap = 0; //new year can not be leap year
                    }
                }
            }
            
            
            //checking for daylights savings time
            //TODO: put these in functions
            
            //move clocks forward by one hour
            if(day_of_year > 83 && dst_fwd == 0)
            {
                if(leap == 1 && day_of_year > 84)//leap years
                {
                    if(day_of_week == 7 && hour == 2) 
                    {
                        TMR1L ++; //increment hour counter
                        dst_fwd = 1;
                    }
                }
                else if (leap==0)
                {
                    if(day_of_week == 7 && hour == 2) 
                    {
                        TMR1L ++; //increment hour counter
                        dst_fwd = 1;
                    }
                    
                }

            }
            
            //move clocks back an hour
            if(day_of_year > 297 && dst_bwd == 0)
            {
                if(leap == 1 && day_of_year > 298)//leap years
                {
                    if(day_of_week == 7 && hour == 2) 
                    {
                        TMR1L --; //decrement hour counter
                        dst_bwd = 1;
                    }
                }
                else
                {
                    if(day_of_week == 7 && hour == 2) 
                    {
                        TMR1L --; //decrement hour counter
                        dst_bwd = 1;
                    }
                }
            }

        
        }
        
        
        
    }
    
    
    
    
}