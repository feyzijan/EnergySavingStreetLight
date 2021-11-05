#ifndef _LEDarray_H
#define _LEDarray_H

#include <xc.h>

#define _XTAL_FREQ 64000000

// define lat bits to refer to pins without confusion (Pin0=LSB, Pin4=MSB)
#define Pin0 LATAbits.LATA4
#define Pin1 LATAbits.LATA5 
#define Pin2 LATFbits.LATF0
#define Pin3 LATBbits.LATB0   
#define Pin4 LATBbits.LATB1

//function prototypes
void LEDarray_init(void);
void LEDarray_button_init(void); 
void LEDarray_disp_bin(unsigned char number);
void LEDarray_disp_dec(unsigned char number);
void LEDarray_disp_PPM(unsigned char number, unsigned char max);

#endif
