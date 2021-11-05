#ifndef _LEDarray_H
#define _LEDarray_H

#include <xc.h>

#define _XTAL_FREQ 64000000

// define lat bits to refer to pins more easily
#define Pin0 LATGbits.LATG0
#define Pin1 LATGbits.LATG1
#define Pin2 LATAbits.LATA2
#define Pin3 LATFbits.LATF6
#define Pin4 LATAbits.LATA4
#define Pin5 LATAbits.LATA5 
#define Pin6 LATFbits.LATF0
#define Pin7 LATBbits.LATB0   
#define Pin8 LATBbits.LATB1

//function prototypes
void LEDarray_init(void);
void LEDarray_button_init(void); 
void LEDarray_disp_bin(unsigned char number);
void LEDarray_disp_dec(unsigned char number);
void LEDarray_disp_PPM(unsigned char number, unsigned char max);

void check_dst_bwd(unsigned char *phour, unsigned char *pday_of_week,unsigned char *pdst_bwd);
void check_dst_fwd(unsigned char *phour, unsigned char *pday_of_week, unsigned char *pdst_fwd);
void new_day(unsigned char *pday_of_week, unsigned int *pday_of_year);
void new_year(unsigned char *pday_of_week,unsigned int *pday_of_year, 
        unsigned char *pyear, unsigned char *pleap, unsigned char *pdst_bwd, unsigned char *pdst_fwd);


#endif
