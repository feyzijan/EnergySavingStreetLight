#include <xc.h>
#include "LEDarray.h"



/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers as 0 (output) for pins connected to LED array
	TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    //set initial output LAT values to 0 (led off)
    
    Pin0 = 0; //most significant digit
    Pin1 = Pin2 = Pin3 = Pin4 = Pin5 = Pin6 = Pin7 = 0; 
    Pin8 = 0; //least significant digit
    
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/


void LEDarray_disp_bin(unsigned char number)
{
	//Use Bit Masks to determine which pins should be turned on 
    
    //Pin0 = (number & 0b100000000) >> 8; // > 255; 
    //Pin1 = (number & 0b010000000) >> 7;
    //Pin2 = (number & 0b001000000) >> 6;
    //Pin3 = (number & 0b000100000) >> 5;
    Pin4 = (number & 0b000010000) >> 4;
    Pin5 = (number & 0b000001000) >> 3;
    Pin6 = (number & 0b000000100) >> 2;
    Pin7 = (number & 0b000000010) >> 1;
    Pin8 = (number & 0b000000001) >> 0;
    
}
