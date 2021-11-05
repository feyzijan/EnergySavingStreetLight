#include <xc.h>
#include "LEDarray.h"

/************************************
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers as 0 (output) for pins connected to LED array 
    //and initialise values to zero
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    Pin0 = 0;
    Pin1 = 0;
    Pin2 = 0;
    Pin3 = 0;
    Pin4 = 0;
}

/************************************
/ Function used to display a max 5 bit number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned char number)
{
	//Use Bit Masks to determine which pins should be turned on 
    Pin0 = (number & 0b000010000) >> 4;
    Pin1 = (number & 0b000001000) >> 3;
    Pin2 = (number & 0b000000100) >> 2;
    Pin3 = (number & 0b000000010) >> 1;
    Pin4 = (number & 0b000000001) >> 0; 
}