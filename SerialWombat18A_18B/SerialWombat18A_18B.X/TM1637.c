/*
Copyright 2021 Broadwell Consulting Inc.

Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
*/
#include "serialWombat.h"
#include <stdint.h>

const uint8_t seven_seg_table[]={
        //a  b  c  d  e  f  g
0x7E,   //1  1  1  1  1  1  0   0              a
0x30,   //0  1  1  0  0  0  0   1             f b 
0x6D,   //1  1  0  1  1  0  1   2              g 
0x79,   //1  1  1  1  0  0  1   3             e c 
0x33,   //0  1  1  0  0  1  1   4              d 
0x5B,   //1  0  1  1  0  1  1   5 
0x5F,   //1  0  1  1  1  1  1   6 
0x70,   //1  1  1  0  0  0  0   7 
0x7F,   //1  1  1  1  1  1  1   8 
0x7B,   //1  1  1  1  0  1  1   9 
0x37,   //1  1  1  0  1  1  1   A
0x1F,   //0  0  1  1  1  1  1   B
0x0D,   //0  0  0  1  1  0  1   C
0x3D,   //0  1  1  1  1  0  1   D
0x4F,   //1  0  0  1  1  1  1   E
0x47    //1  0  0  0  1  1  1   F
};

typedef enum {
	TM1637_MODE_BUFFER_DEC = 0,
	TM1637_MODE_BUFFER_HEX = 1,
	TM1637_MODE_STRING = 2, 
	TM1637_MODE_ANIMATION = 3,
}TM1637_MODE_t;
typedef struct tm1637_n{
	uint16_t* dmaPtr;
	uint16_t animationAddress;
	uint16_t animationDelay;
	uint16_t lastValue;
	uint8_t outputString[6];
	uint8_t dioPin;
	uint8_t sourcePin;
	uint8_t firstDigit;
	uint8_t lastDigit;
	uint8_t animationCurrentFrame;
	uint8_t animationFrames;
	uint8_t mode;
	uint8_t outputState;
	uint8_t decimalPointBitmap; ///< Least significant is first digit's decimal
}tm1637_t;


#define tm1637 ((tm1637_t*) CurrentPinRegister)
#define DIO_LOW() { PinLow(tm1637->dioPin);}
#define DIO_HIGH() { PinHigh(tm1637->dioPin);}
#define CLK_LOW() { CurrentPinLow();}
#define CLK_HIGH() { CurrentPinHigh();}
#define SET_DIO(_value) { SetPin(tm1637->dioPin, _value);}


void tm1637Start()
{
	DIO_LOW();
}

void tm1637End()
{
	CLK_HIGH();
	DIO_HIGH();
}

void tm1637ClockByte(uint8_t data)
{
    uint8_t i;
	for (i = 0; i < 8; ++i)
	{
		CLK_LOW();
		SET_DIO((data & 0x80) > 0);
		CLK_HIGH();
		data <<= 1;
	}
	DIO_LOW();
	CLK_LOW();
	CLK_HIGH();
}

#define tm1637 ((tm1637_t*) CurrentPinRegister)

void tm1637_hwinit()
{
	CurrentPinHigh();
	PinHigh(tm1637->dioPin);
}


void tm1637SendMemoryWrite()
{
	tm1637ClockByte(0x40);  //Write data, Increment address, normal mode
}

void tm1637SendInitialAddress()
{
	tm1637ClockByte(0xC0); // Address command, CH0H	
}

void tm1637SendData(uint8_t data)
{
	tm1637ClockByte(data);
}

void tm1637SendDisplayControlCommand(uint8_t command)
{
	tm1637SendDisplayControlCommand(0x88 | (command & 0x07));  //Set display control, on, + brightness
}


/*!
    \brief Initialization routine for Analog Input

----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Analog Input.  Disables averaged and filtered values.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x0A (TM1637 ) | Second Pin |Number of digits | Mode |Public Data | 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 3 to Analog Input. //TODO

> `0xC0 0x03 0x02 0x55 0x55 0x55 0x55 0x55 `

----
*/

void initTM1637 (void)
{
	
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
			if (pinPort[Rxbuffer[3]] != CurrentPinPort())
			{
				//Pins must be on same port
				CurrentPinRegister->generic.mode = PIN_MODE_CONTROLLED;
				error(SW_ERROR_PINS_MUST_BE_ON_SAME_PORT);
				return;
			}
     		        CurrentPinRegister->generic.mode =PIN_MODE_TM1637;
			SetMode(tm1637->dioPin, PIN_MODE_CONTROLLED);
			tm1637->lastDigit  = Rxbuffer[4];
			tm1637->firstDigit = 0;
			tm1637->mode = Rxbuffer[5];
			tm1637->sourcePin = Rxbuffer[6];
			tm1637_hwinit();
			//tm1637Update();
			}
			break;
/*
		case CONFIGURE_CHANNEL_MODE_1:
			{
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
			}
			break;
		case CONFIGURE_CHANNEL_MODE_3: 
			{
			}
			break;
		case CONFIGURE_CHANNEL_MODE_4: 
			{
			}
			break;
			*/
		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}
}

void tm1637Update()
{ 
	uint8_t displayArray[6];
	uint16ToAscii5(CurrentPinRegister->generic.buffer ,displayArray);  //TODO genericise
	tm1637Start();
	tm1637SendMemoryWrite();
	tm1637SendInitialAddress();
	uint8_t start = tm1637->firstDigit;
	uint8_t end = tm1637->lastDigit;

	//TODO if start > end, flip and reverse string
    uint8_t i;
	for (i = start; i <= end; ++i)
	{
		tm1637SendData( displayArray[i]);
	}
	tm1637SendDisplayControlCommand(1);
	tm1637End();
	
}


