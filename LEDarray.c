#include <xc.h>
#include "LEDarray.h"



//TODO: remove Pins [0-3]

/************************************
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers as 0 (output) for pins connected to LED array 
    //and initialise values to zero
    
	//unused?
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    Pin0 = 0;
    Pin1 = 0;
    Pin2 = 0;
    Pin3 = 0; 
    //
    
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    Pin4 = 0;
    Pin5 = 0;
    Pin6 = 0;
    Pin7 = 0;
    Pin8 = 0;
}

/************************************
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned char number)
{
	//Use Bit Masks to determine which pins should be turned on 
    Pin4 = (number & 0b000010000) >> 4;
    Pin5 = (number & 0b000001000) >> 3;
    Pin6 = (number & 0b000000100) >> 2;
    Pin7 = (number & 0b000000010) >> 1;
    Pin8 = (number & 0b000000001) >> 0; 
}