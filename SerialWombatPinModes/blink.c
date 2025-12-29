/*
Copyright 2025 Broadwell Consulting Inc.

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
/* Serial Wombat is a registered trademark of Broadwell Consulting Inc. */
#include "serialWombat.h"
#include <stdint.h>
#include <stdbool.h>






typedef struct blink_n{
	uint16_t lastValue;
	uint8_t sourcePin;
	uint8_t activeMode;
	uint8_t inactiveMode;
}blink_t;

#define BLINK_TIME 30
//TODO Update documentation
/*!
    \brief Initialize Blink Pin Mode

----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Blink


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set |0x0C  | userBufferIndex LSB |userBufferIndex MSB | Number of LEDS |Unused 0x55*  |Unused 0x55* |

\*0x55 is recommended, but any byte is acceptable


Response:

Command is echoed back.

Examples:

Set pin 19 to WS2812, user buffer index of 0x180, 16 LEDS

> `0xC0 0x13 0x0B 0x80 0x01 0x10 0x55 0x55 `

----

*/



void initBlink (void)
{
    BUILD_BUG_ON( sizeof(blink_t) >  BYTES_PER_PIN_REGISTER );
	blink_t* blink = (blink_t*) CurrentPinRegister;
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				blink->sourcePin = Rxbuffer[3];
				CurrentPinRegister->generic.buffer =  0;
		blink->lastValue = GetBuffer(Rxbuffer[3]);
                CurrentPinRegister->generic.mode = PIN_MODE_BLINK;
			}
			break;

		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}
}


void updateBlink()
{
	blink_t* blink = (blink_t*) CurrentPinRegister;

	 if (CurrentPinRegister->generic.buffer)
	            {
	                -- CurrentPinRegister->generic.buffer;
	            }
	 else {
	     CurrentPinLow();
    }
	uint16_t b = GetBuffer(blink->sourcePin);
	 if (b != blink->lastValue)
	          {
	          blink->lastValue = b;
	          CurrentPinRegister->generic.buffer = BLINK_TIME;
	                CurrentPinHigh();
	          }
}




