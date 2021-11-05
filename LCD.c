#include <xc.h>
#include "LCD.h"
#include <stdio.h>

/************************************
 * Function to toggle LCD enable bit on then off
 * when this function is called the LCD screen reads the data lines
************************************/
void LCD_E_TOG(void)
{
    LCD_E = 1; //turn the LCD enable bit on   
	__delay_us(2); //wait a short delay
    LCD_E = 0; //turn the LCD enable bit off again
}

/************************************
 * Function to set the 4-bit data line levels for the LCD
************************************/
void LCD_sendnibble(unsigned char number)
{
	//set the data lines )
    LCD_DB7 = number >>3 & 1;
    LCD_DB6 = number >>2 & 1;
    LCD_DB5 = number >>1 & 1;
    LCD_DB4 = number & 1;
    
    LCD_E_TOG();			//toggle the enable bit to instruct the LCD to read the data lines
    __delay_us(5);      //Delay 5uS
}


/************************************
 * Function to send full 8-bit commands/data over the 4-bit interface
 * high nibble (4 most significant bits) are sent first, then low nibble sent
************************************/
void LCD_sendbyte(unsigned char Byte, char type)
{
    // set RS pin whether it is a Command (0) or Data/Char (1) using type argument
    LCD_RS = type; 
    
    // send high bits of Byte using LCDout function
    LCD_sendnibble(Byte >> 4);
    
    // send low bits of Byte using LCDout function
	LCD_sendnibble(Byte & 0b00001111);
    
    __delay_us(50);               //delay 50uS (minimum for command to execute)
}


/************************************
 * Function to initialise the LCD after power on
************************************/
void LCD_Init(void)
{
    //Define LCD Pins as Outputs and set all pins to low
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC2=0;
    TRISBbits.TRISB3=0;
    TRISBbits.TRISB2=0;
    TRISEbits.TRISE3=0;
    TRISEbits.TRISE1=0;
    LCD_RS = 0; 
    LCD_E = 0;
    LCD_DB4 = 0;
    LCD_DB5 = 0;
    LCD_DB6  = 0;
    LCD_DB7 = 0;
    
    //Initialisation sequence code
    __delay_ms(100);
    LCD_sendnibble(0b0011); // Function set - first one is snet with nibble as LCD is in 8bit mode
    
    LCD_sendbyte(0b00101000, 0); // Function set
    LCD_sendbyte(0b00101000, 0); // Function set
    
    LCD_sendbyte(0b00001000, 0); // Display off, cursor off, blink off
    LCD_sendbyte(0b00000001, 0); // Display clear
    __delay_ms(2);
    
    LCD_sendbyte(0b00000110, 0); // Entry Mode Set: cursor go right, dont shift screen
    
    LCD_sendbyte(0b00001110, 0); // 00001 + turn display back on  + cursor and blink off
}

/************************************
 * Function to set the cursor to beginning of line 1 or 2
************************************/
void LCD_setline (char line)
{
    //Send 0x80 to set line to 1 (0x00 DRAM address)
    if (line == 1) LCD_sendbyte(0b10000000, 0);

    //Send 0xC0 to set line to 2 (0x40 DDRAM address)
    if(line == 2) LCD_sendbyte(0b11000000, 0);
}

void LCD_clear()
{
    LCD_sendbyte(1,0);
    __delay_ms(2);
}

void LCD_sendstring(char *string)
{
	while(*string != 0){  // While data pointed to isn?t 0x00 (strings in C must end with a NULL byte) 
		LCD_sendbyte(*string++,1); 	//Send out current byte pointed to and increment pointer
	}
}

