/*
 * TM1637.h
 *
 * Created: 19/09/2020 20:50:30
 *  Author: Alexey Ivanov
 *	Driver for TM1637
 *  v1.0
 *  NOTA!! no key scanning end-user functions implemented
 */


#ifndef TM1637_H_
#define TM1637_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

//delay to stabilize output before next pin change in us
#define TM1637_DELAY			10

//Ports and pins definition for communication
#define TM1637_PORT				PORTD
#define TM1637_PIN_DIRECTION	DDRD
#define TM1637_CLK				PIND2
#define TM1637_DIO				PIND3

//TM1637 Commands definition
#define TM1637_WRITE_CMD	0b01000000
#define TM1637_READ_KEY		0b01000010
#define TM1637_FIX_ADDR		0b01000100
#define TM1637_SET_ADDR		0b11000000
#define TM1637_SET_DISPLAY	0b10000000

//Addresses of each display
#define TM1637_C0H_ADR		0
#define TM1637_C1H_ADR		1
#define TM1637_C2H_ADR		2
#define TM1637_C3H_ADR		3
#define TM1637_C4H_ADR		4
#define TM1637_C5H_ADR		5

//Control Display commands: ON/OFF
//Brightness is set directly with DISPLAY_ON command
#define TM1637_DISPLAY_ON		0b10001000
#define TM1637_DISPLAY_OFF		0b10000000
#define TM1637_DISPLAY_1_16		0b10001000
#define TM1637_DISPLAY_2_16		0b10001001
#define TM1637_DISPLAY_4_16		0b10001010
#define TM1637_DISPLAY_10_16	0b10001011
#define TM1637_DISPLAY_11_16	0b10001100
#define TM1637_DISPLAY_12_16	0b10001101
#define TM1637_DISPLAY_13_16	0b10001110
#define TM1637_DISPLAY_14_16	0b10001111

#define TM1637_CLK_HIGH		TM1637_PORT|=(1<<TM1637_CLK);
#define TM1637_CLK_LOW		TM1637_PORT&=~(1<<TM1637_CLK);

#define TM1637_DIO_HIGH		TM1637_PORT|=(1<<TM1637_DIO);
#define TM1637_DIO_LOW		TM1637_PORT&=~(1<<TM1637_DIO);

//Digits definition to display
/*************************
Dots are displayed by setting MSB bit of digit
Example: if dots must be displayed with digit 2 -> TM1637_2|TM1637_DOTS
*************************/
//Segments					  .GFEDCBA
#define TM1637_NONE			0b00000000
#define TM1637_0			0b00111111
#define TM1637_1			0b00000110
#define TM1637_2			0b01011011
#define TM1637_3			0b01001111
#define TM1637_4			0b01100110
#define TM1637_5			0b01101101
#define TM1637_6			0b01111101
#define TM1637_7			0b00000111
#define TM1637_8			0b01111111
#define TM1637_9			0b01101111
#define TM1637_A			0b01110111
#define TM1637_B			0b01111100
#define TM1637_C			0b00111001
#define TM1637_D			0b01011110
#define TM1637_E			0b01111001
#define TM1637_F			0b01110001
#define TM1637_DOTS			0b10000000


/************************************************************************/
/* Full command in autoincrement mode
   not used in driver                                                   */
/************************************************************************/
static void TM1637_SendCommand (unsigned char ucCommand, unsigned char ucAdress, unsigned char data[], unsigned char ucLen, unsigned char ucDisplayControl);

/************************************************************************/
/* Function to Initialize TM1637                                        */
/************************************************************************/
void TM1637_Initialize();

/************************************************************************/
/* Display all digits in one command starting from first 
 cData[] - digits to Display
 cDataLen - Length of cData                                             */
/************************************************************************/
void TM1637_DisplayAll(char cData[], char cDataLen);

/************************************************************************/
/* Set brightness of digits value from 0 to 7                           */
/************************************************************************/
void TM1637_SetBrightness(unsigned char ucBrightness);

/************************************************************************/
/* Display one digit, address from 0 to 5                               */
/* Brightness from 0 to 7												*/
/************************************************************************/
void TM1637_DisplayDigit(char cAdr, char cDigit);

/************************************************************************/
/* Display off command                                                                     */
/************************************************************************/
void TM1637_DisplayOff();

//sending one complete byte
static void TM1637_SendByte(unsigned char ucByte);

//Send end of the frame
static void TM1637_Stop();
//send start of the frame
static void TM1637_Start();

/************************************************************************/
/* Get 7Segment presentation of digit from 0 to F                       */
/************************************************************************/
char TM1637_7SgmDigit(char cDigit);


#endif /* TM1637_H_ */