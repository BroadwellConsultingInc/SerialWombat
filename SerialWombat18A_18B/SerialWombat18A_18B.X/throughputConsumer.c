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
#include "pic24fj256ga702/mcc_generated_files/mcc.h"


#define    FCY    2000000UL
#include <libpic30.h>

typedef struct throughputConsumer_n{
	uint16_t delayInuS[16];
}throughputConsumer_t;



/*!
    \brief Initialization routine for ThroughputConsumer 

----

---------------------

Initialize Throutput Consumer.  Sets all values to zero


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x04 (ThroughputConsumer) | 0x55* |0x55* |0x55*  |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Initialize Throughput Consumer on pin 2

> `0xC0 0x02 0x04 0x55 0x55 0x55 0x55 0x55 `

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Set up a frame mod 16 to consume a given amount of throughput in uS  Pin will go high while consuming, low otherwise


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set|0x04 (ThroughputConsumer) |Slot (0-15) |microseconds LSB |microseconds MSB |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Configure pin 2 frame % 16 = 7 to consume 400 uS

> `0xC1 0x02 0x04 0x07 0x90 0x01 0x55 0x55 `


----

CONFIGURE_CHANNEL_MODE_2:
---------------------

Consume indicated number of microseconds during command processing


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set|0x04 (ThroughputConsumer) |microseconds LSB |microseconds MSB |0x55* |0x55* |0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back after delay.

Examples:

Consume 400 microseconds upon receipt

> `0xC2 0x02 0x04 0x90 0x01 0x55 0x55  0x55`



*/

void initThroughputConsumer ()
{
    //TODO put check for pin mode here
	throughputConsumer_t* throughputConsumer = (throughputConsumer_t*)CurrentPinRegister;
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				int i;
				for (i = 0; i < 16; ++i)
				{
					throughputConsumer->delayInuS[i] = 0;
				}
				CurrentPinRegister->generic.mode = PIN_MODE_THROUGHPUT_CONSUMER;

			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
                if (CurrentPinRegister->generic.mode == PIN_MODE_THROUGHPUT_CONSUMER)
				{
					if (Rxbuffer[3] < 16)
					{
						throughputConsumer->delayInuS[Rxbuffer[3]] = RXBUFFER16(4);
					}
					else
					{
						error(SW_ERROR_INVALID_PARAMETER_3);
					}
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
                uint16_t delay = RXBUFFER16(3);
                __delay_us(delay);
			}
			break;
		default:
			{
				error(SW_ERROR_INVALID_COMMAND);
			}
			break;
	}
}


void updateThroughputConsumer()
{ 
    throughputConsumer_t* throughputConsumer = (throughputConsumer_t*)CurrentPinRegister;
    
	CurrentPinRegister->generic.buffer = throughputConsumer->delayInuS[ (FramesRun & 0xF)];
	if (CurrentPinRegister->generic.buffer > 0)
	{
		CurrentPinHigh();
		timingResourceBusyWait(CurrentPinRegister->generic.buffer);
		CurrentPinLow();
	}
}
