#include <xc.h>
#include "dates.h"

#include <xc.h>

extern unsigned char test_mode;

/*****************************************************
 *Called during a maximum of 7 days per year to check if the clocks should be wound back
 *Checks to see if it is a Sunday and 2AM, if so it decrements Timer1 by one
 *****************************************************/
void check_dst_bwd(unsigned char *phour, unsigned char *pday_of_week,unsigned char *pdst_bwd) 
{   
    if((*pday_of_week == 7) && (*phour == 2) ){
        *pdst_bwd = 1;
        TMR1L = 0b00000001; //decrement hour counter
    }
}

/**************
 * Called during a maximum of 7 days per year to check if the clocks should be wound forward
 * Checks to see if it is a Sunday and 2AM, if so it increments Timer1 by one
 **************/
void check_dst_fwd(unsigned char *phour, unsigned char *pday_of_week, unsigned char *pdst_fwd) 
{
    if((*pday_of_week == 7) && (*phour == 2)) 
    {
        *pdst_fwd = 1; //toggle
        TMR1L = 0b00000011; //increment hour counter
    }
}

 /**********************************************
 * Called once hour variable equals 24
 * Updates the day of week, day of year, and hour to reflect new day
 **********************************************/      
void new_day(unsigned char *phour, unsigned char *pday_of_week, unsigned int *pday_of_year) 
{
    *phour = 0;
    TMR1L = 0; //reset hour counter to zero
    (*pday_of_year)++;
    (*pday_of_week)++;
    if(*pday_of_week & 8){ //check for next week
        *pday_of_week = 1; 
        if(!test_mode){ 
            // add a 2.086 second delay per week to counteract the yearly 108 second drift
            // this is done by decrementing the value set in interrupt by 32
            TMR0H = 0b00101011; 
            TMR0L = 0b00000100;
        }
        
    }
}


/****************************************************
 * Called once day_of_year variable hits 365, or 366 in leap years
 * Updates the year variable and resets day of year to 1 
 * Resets daylight savings time toggles, and checks if new year is leap year
 ****************************************************/
void new_year(unsigned int *pday_of_year, unsigned char *pyear, unsigned char *pleap, 
    unsigned char *pdst_bwd, unsigned char *pdst_fwd) 
{
    if(*pleap == 0){
        *pday_of_year = 1;
        (*pyear) ++;
        *pdst_fwd = 0; 
        *pdst_bwd = 0;
        if (*pyear % 4 & 0) *pleap = 1; // check if new year is leap year
    } else if(*pleap & 1){
        if(*pday_of_year > 366){
            *pday_of_year = 1;
            (*pyear) ++;
            *pdst_fwd = 0;
            *pdst_bwd = 0; 
            *pleap = 0; //new year can not be a leap year as well
        }
    }
}
