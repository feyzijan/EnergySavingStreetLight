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
#include <stdio.h>
 
#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz
#define testmode 1 // 1: test mode 1hour represented by 1s, 0:real mode
/* 
#define DST_fwd_min = 84
#define DST_fwd_max = 90
#define DST_bwd_min = 298
#define DST_bwd_max = 304
 */


/*variables to keep track of time - must be correctly initalized, except for hour, 
 * which will start at 0. May use the link below to input variables correctly:
 * https://www.timeanddate.com/date/weekday.html

 */
unsigned char hour; //0-24
unsigned char day_of_week = 7; //1-7
unsigned int day_of_year = 304; //1-365 (or 366 if leap ==1)
unsigned char year = 21; //1-99
unsigned char leap = 0; //1 = leap, 0 = nonleap
unsigned char dst_fwd = 1;
unsigned char dst_bwd = 0;


void main(void) 
{    
    // Initialisations
    Comp1_init();
    Interrupts_init();
    LEDarray_init();
    Timer0_init();
    Timer1_init(); 
    
    // setup pin for RH3 LED - to be toggled with interrupt - for testing only
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    
    while (1) 
    {    
        hour = get8LSB_TMR1(); //get current hour(in testing case 1h = 1 second)
        
       
        if (hour > 0 && hour < 5 )//LED will switch off 1-5AM 
        { 
            LEDarray_disp_bin(0);//display nothing in LED
            CM1CON0bits.EN=0; //disable comparator so it doesn't toggle LED
        } else {
            LEDarray_disp_bin(hour); //display hour 
            CM1CON0bits.EN=1; //enable comparator //*****************maybe call this less
        }
        
        //End of day sequence
        if (hour == 24)
        {   
            //call new_day function with necessary pointers
            new_day(&hour, &day_of_week, &day_of_year); 
            //end of year sequence
            if ((day_of_year > 365 && leap ==0) || (day_of_year > 366 && leap ==1))
            {
                new_year(&day_of_week, &day_of_year, &year, &leap, &dst_bwd, &dst_fwd);
            }
        }
        
        // Check for daylight savings - moving clocks forward
        if(dst_fwd == 0 && day_of_year > 83){
            if( (leap == 0) || (leap == 1 &&day_of_year > 84) )
            {
                check_dst_fwd(&hour,&day_of_week,&dst_fwd);
            }
        }
        
        // Check for daylight savings - moving clocks backward
        if(dst_bwd == 0 && day_of_year > 297){
            if( (leap == 0) || (leap == 1 &&day_of_year > 298) )
            {
                check_dst_bwd(&hour,&day_of_week,&dst_bwd);
            }
        }
        
    }  
}