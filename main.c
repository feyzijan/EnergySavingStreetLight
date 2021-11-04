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

//variables to keep track of time
unsigned char hour = 0; //0-24
unsigned char day_of_week = 0; //1-7
unsigned char day_of_month = 0; // 1-31
unsigned char month; //1-12
unsigned int day_of_year; //1-365
unsigned char year; //1-20?

unsigned int counter = 0; //?

void main(void) {
    
    // Initialisation
    Comp1_init();
    Interrupts_init();
    LEDarray_init();
    Timer0_init();
    Timer1_init(); 
    
    // setup pin for RH3 LED - to be toggled with interrupt
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    while (1) {
        
        hour = get8LSB_TMR1(); //get hour
        
        if (counter < 1 || counter >=5 ){
            LEDarray_disp_bin(hour);
        }
        
        //End of day
        if (hour == 24){
            TMR1L = 0; //reset hour counter to zero
        }
        
        
        
    }
    
    
    
    
}