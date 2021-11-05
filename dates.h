#ifndef _dates_H
#define _dates_H

#include <xc.h>

#define _XTAL_FREQ 64000000

//define functions used to keep track of time
void check_dst_bwd(unsigned char *phour, unsigned char *pday_of_week,unsigned char *pdst_bwd);
void check_dst_fwd(unsigned char *phour, unsigned char *pday_of_week, unsigned char *pdst_fwd);
void new_day(unsigned char *phour, unsigned char *pday_of_week, unsigned int *pday_of_year);
void new_year(unsigned int *pday_of_year, unsigned char *pyear, unsigned char *pleap, 
        unsigned char *pdst_bwd, unsigned char *pdst_fwd);


#endif
