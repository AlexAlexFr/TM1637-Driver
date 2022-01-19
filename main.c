/*
 * TM1637 test.c
 *
 * Created: 07/11/2020 10:00:56
 * Author : aivan
 */ 

#define F_CPU	16000000UL

#include <avr/io.h>
#include "TM1637.h"
#include <util/delay.h>

int main(void)
{
	
	//Initialize TM1637
	TM1637_Initialize();
	
	
	int iCount = 0x0000;						//Counter, will be incremented every  half second
	char cDisplay[4] = {0x7F,0x7F,0x7F,0x7F};	//Array, will be used for digits to display, initialized with 0x7F
		
	TM1637_DisplayAll(cDisplay,4);				//Display the 4 digits 
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		
		for (char c=0; c<4; c++) //For each digit
		{
			cDisplay[c] = TM1637_7SgmDigit((iCount & (0x0F << c*4))>>(c*4)); //Get 7seg code for each digit using 4 bit mask and shifts
			TM1637_DisplayDigit(3-c,cDisplay[c]); //Display the digit at defined position
		}
		
		iCount++;	//increment counter
		
		_delay_ms(250);
		_delay_ms(250);
		
		
		TM1637_SetBrightness(0);	//set brightness to lower
		
		for (char c=0; c<4; c++)
		{
			cDisplay[c] = 0x3F;	
		}
				
		TM1637_DisplayAll(cDisplay,4);	//display something :)
		_delay_ms(250);
		_delay_ms(250);		
		
		TM1637_SetBrightness(7);	//set brightness at max

    }
}

