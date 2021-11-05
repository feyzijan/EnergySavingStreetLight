#include <xc.h>
#include "dates.h"

#include <xc.h>



/**************
 * 
 **************/
void check_dst_bwd(unsigned char *phour, unsigned char *pday_of_week,unsigned char *pdst_bwd) 
{   
    if(*pday_of_week  == 7 && *phour == 2)
    {
        *pdst_bwd = 1;
        TMR1Lbits.TMR1L0 =1 ; //decrement hour counter
        TMR1Lbits.TMR1L1 =0 ; 
        
    }
}

/**************
 * 
 **************/
void check_dst_fwd(unsigned char *phour, unsigned char *pday_of_week, unsigned char *pdst_fwd) 
{
    if(*pday_of_week == 7 && *phour == 2) 
    {
        TMR1Lbits.TMR1L0 =1 ; //increment hour counter
        *pdst_fwd = 1; //toggle
    }
}

 /**************
 * 
 **************/      
void new_day(unsigned char *phour, unsigned char *pday_of_week, unsigned int *pday_of_year) 
{
    *phour = 0;
    TMR1L = 0; //reset hour counter to zero
    (*pday_of_year)++;
    (*pday_of_week)++;
    //checkpoint();
    if(*pday_of_week == 8) *pday_of_week = 1; //check for next week
    //increment day_of_year, year, and update leap
    //checkpoint();
}


/**************
 * 
 **************/
void new_year(unsigned char *pday_of_week,unsigned int *pday_of_year, 
        unsigned char *pyear, unsigned char *pleap, unsigned char *pdst_bwd, unsigned char *pdst_fwd) 
{
    if(*pleap == 0)
    {
        *pday_of_year = 1;
        *pyear ++;
        *pdst_fwd = 0; 
        *pdst_bwd = 0;
        if (*pyear%4 == 0) *pleap = 1; // check if new year is leap year
    } 
    else if(*pleap == 1)
    {
        if(*pday_of_year > 366)
        {
            *pday_of_year = 1;
            *pyear ++;
            *pdst_fwd = 0;
            *pdst_bwd = 0; 
            *pleap = 0; //new year can not be leap year
        }
    }
}
