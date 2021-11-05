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
#include "dates.h"
 
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz
#define testmode 1; // 1: test mode 1hour represented by 1s, 0:real mode
unsigned char test_mode = testmode; //this value is used to toggle operations in other files


/* Variables to keep track of time - must be correctly initalized, except for hour, 
 * which will start at 0. May use the link below to input variables correctly:
 * https://www.timeanddate.com/date/weekday.html
 */
unsigned char hour; //0-24
unsigned char day_of_week = 7; //1-7
unsigned int day_of_year = 304; //1-365 (or 366 if leap ==1)
unsigned char year = 21; //1-99
unsigned char leap = 0; //1 = leap, 0 = non leap year
unsigned char dst_fwd = 1; // 1= clocks already moved forward this year
unsigned char dst_bwd = 0;// 1= clocks already moved backwards this year
    
void main(void) 
{    
    // setup pin for RD7 LED - for debugging/testing only
    //LATDbits.LATD7=0;   //set initial output state
    //TRISDbits.TRISD7=0; //set TRIS value for pin (output)

    // setup pin for RH3 LED 
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)

    // Initialisations
    Comp1_init();
    Interrupts_init();
    LEDarray_init();
    unsigned char test_mode = testmode;
    Timer0_init();
    Timer1_init(); 

    while (1) 
    {    
        hour = TMR1L; //get current hour(in testing case 1h = 1 second)
        LEDarray_disp_bin(hour); //display hour in LED
        
        //Switch off LED RH3 between 1-5AM 
        if (hour > 0 && hour < 5 ) { 
            LATHbits.LATH3=0;
            CM1CON0bits.EN=0; //disable comparator so it doesn't toggle LED
        } else {
            CM1CON0bits.EN=1; //enable comparator //*****************maybe call this less
        }
        
        //End of day sequence
        if (hour == 24) {   
            //call new_day function with pointers of variables to be updated
            new_day(&hour, &day_of_week, &day_of_year); 
            //end of year sequence
            if ((day_of_year > 365 && leap == 0) || (day_of_year > 366 && leap == 1)){
                new_year(&day_of_year, &year, &leap, &dst_bwd, &dst_fwd);
            }
        }
        
        // Check for daylight savings - whether we need to move clocks forward
        if(dst_fwd == 0 && day_of_year > 83){
            if( (leap == 0) || (leap == 1 &&day_of_year > 84) ) { //consider extra days in leap year
                check_dst_fwd(&hour,&day_of_week,&dst_fwd);
            }
        }
        
        // Check for daylight savings - whether we need to move clocks backwards
        if(dst_bwd == 0 && day_of_year > 297){
            if((leap == 0) || (leap == 1 &&day_of_year > 298) ){
                check_dst_bwd(&hour,&day_of_week,&dst_bwd);
            }
        }
        
    }  
}