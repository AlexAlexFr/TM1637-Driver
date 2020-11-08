/*
 * TM1637.c
 *
 * Created: 19/09/2020 20:50:14
 *  Author: Alexey Ivanov
 *	Driver for TM1637
 *  v1.0
 *  NOTA!! no key scanning end-user functions implemented
 */ 

#include "TM1637.h"
#include <avr/pgmspace.h>

const char TM1637_7SEG_Digits[] PROGMEM =
{
	TM1637_0,	//0
	TM1637_1,	//1
	TM1637_2,	//2
	TM1637_3,	//3
	TM1637_4,	//4
	TM1637_5,	//5
	TM1637_6,	//6
	TM1637_7,	//7
	TM1637_8,	//8
	TM1637_9,	//9
	TM1637_A,	//A
	TM1637_B,	//B
	TM1637_C,	//C
	TM1637_D,	//D
	TM1637_E,	//E
	TM1637_F
};

void TM1637_Initialize()
{
	TM1637_PIN_DIRECTION |= (1<<TM1637_CLK)|(1<<TM1637_DIO);
	
	TM1637_PORT |= (1<<TM1637_CLK)|(1<<TM1637_DIO);

	TM1637_SetBrightness(0);

}

void TM1637_SetBrightness(unsigned char ucBrightness)
{
	TM1637_Start();
	TM1637_SendByte(TM1637_DISPLAY_1_16 + ucBrightness);
	TM1637_Stop();	
}

void TM1637_DisplayOff()
{
	TM1637_Start();
	TM1637_SendByte(TM1637_DISPLAY_OFF);
	TM1637_Stop();
	
}

static void TM1637_Start()
{
	
	TM1637_DIO_LOW
	_delay_us(TM1637_DELAY);
	TM1637_CLK_LOW
	_delay_us(TM1637_DELAY);
	
}

static void TM1637_Stop()
{
	TM1637_DIO_LOW
	_delay_us(TM1637_DELAY);
	TM1637_CLK_HIGH
	_delay_us(TM1637_DELAY);
	TM1637_DIO_HIGH
	_delay_us(TM1637_DELAY);
}

void TM1637_DisplayDigit(char cAdr, char cDigit)
{
	TM1637_Start();
	TM1637_SendByte(TM1637_WRITE_CMD);
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_SendByte(TM1637_SET_ADDR + cAdr);
	TM1637_SendByte(cDigit);
	
	TM1637_Stop();
}

void TM1637_DisplayAll(char cData[], char cDataLen)
{
	TM1637_Start();
	TM1637_SendByte(TM1637_WRITE_CMD);
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_SendByte(TM1637_SET_ADDR + TM1637_C0H_ADR);
	
	for (unsigned char c=0; c<cDataLen; c++)
	{
			TM1637_SendByte(cData[c]);
	}
	
	TM1637_Stop();
}

static void TM1637_SendCommand (unsigned char ucCommand, unsigned char ucAdress, unsigned char data[], unsigned char ucLen, unsigned char ucDisplayControl)
{
	TM1637_Start();			
	TM1637_SendByte(ucCommand);
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_SendByte(ucAdress);
	
	for (unsigned char c=0; c<ucLen; c++)
	{
		TM1637_SendByte(data[c]);
	}
	
	
	TM1637_Start();
	TM1637_SendByte(ucDisplayControl);
	TM1637_Stop();
	
}

static void TM1637_SendByte(unsigned char ucByte)
{

	unsigned char state = ucByte;
	

	
	for(unsigned char ucCount = 0;ucCount<8;ucCount++)
	{
		_delay_us(TM1637_DELAY);
		TM1637_CLK_LOW
		_delay_us(TM1637_DELAY);
		if (state & 0x01 )
		{
			TM1637_DIO_HIGH
		}
		else
		{
			TM1637_DIO_LOW
		}
		_delay_us(TM1637_DELAY);
		
		TM1637_CLK_HIGH
		_delay_us(TM1637_DELAY);

		state = state>>1;	
	}
	
	
	TM1637_CLK_LOW		
	TM1637_DIO_HIGH
	
	TM1637_PIN_DIRECTION &= ~(1<<TM1637_DIO);
	
	_delay_us(TM1637_DELAY);
	
	TM1637_CLK_HIGH
	_delay_us(TM1637_DELAY);
	
	TM1637_CLK_LOW
	_delay_us(TM1637_DELAY);
	
	TM1637_PIN_DIRECTION |= (1<<TM1637_DIO);
	_delay_us(TM1637_DELAY);	
		
}


char TM1637_7SgmDigit(char cDigit)
{
	return pgm_read_byte(&TM1637_7SEG_Digits[cDigit]);
}