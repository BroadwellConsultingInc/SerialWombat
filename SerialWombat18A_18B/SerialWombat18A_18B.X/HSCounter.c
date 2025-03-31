/*
Copyright 2023 Broadwell Consulting Inc.

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
#include "inputProcess.h"
#include "pic24fj256ga702/mcc_generated_files/mcc.h"


/// This enum is designed to be compatible with PULSE_TIMER_PUBLIC_DATA
typedef enum {
		PULSE_COUNT = 2,
		FREQUENCY_ON_LTH_TRANSITION = 5,
}HSCOUNTER_PUBLIC_DATA;


typedef struct HSCounter_n{
    inputProcess_t inputProcess; ///< Input processing generic structure
	uint32_t lastCount;  ///< The previous count when sampleFrames == sampleFrameCount
	uint32_t frequency; ///< The last calculated frequency
	uint16_t sampleFrames; ///< The number of 1ms frames between frequency, public data updates
	uint16_t sampleFrameCount; ///< The number of 1ms frames since the last frequency / pd updates
	uint16_t publicOutputDivisor; ///< The number to divide the frequency or counts by before making public
	uint8_t publicDataOutput; ///< Enumerated HSCOUNTER_PUBLIC_DATA type
	uint8_t resource;  // The timer resource 
}HSCounter_t;



/*!
    \brief Initialization routine for High Speed Counter

----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize High Speed Counter


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (TO HS Counter)|0x1# (HS Counter ) | Sample Frames LSB |Sample Frames MSB| Public Data Divisor LSB |Public Data Divisor LSB MSB|  Public data enum (2 = count, 5 = freq)|


 * Sample Frames :  The number of 1ms frames between frequency, public data updates.  This should be a number that 1000 can be divided by with no remainder (e.g. 5, 25, 100, 250, etc)
 * Public Data Divisor :  A number to divide the public data output by before placing it in the 16 bit buffer.  A value of 100 would allow a 2MHz frequency to be expressed at 20000
 * Public Data Enum:  Set to 2 to output the number of counts as the pin public data, set to 5 to output frequency as the pin public data
Response:

Command is echoed

Examples:

Set pin 19 to HS Counter, update every 100mS, output frequency divided by 10 as public data

> `0xC0 0x13 0x1E 0x00 0x64 0xF8 0x03 0x05 `

----

CONFIGURE_CHANNEL_MODE_19:
---------------------

Disable High Speed Counter and return the hardware resource used to the timing resource allocator


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (TO HS Clock)|0x1D (HS Clock ) | 0x55 |0x55 | 0x55 | 0x55| 0x55|



Response:

Echoed back

Examples:

Disable pin 19  HS Clock

> `0xDB 0x13 0x1D 0x55 0x55 0x55 0x55 0x55 `

----


*/

HSCounter_t* debugHSCounter;
void initHSCounter (void)
{
	HSCounter_t* hscounter = (HSCounter_t*) CurrentPinRegister;
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_HS_COUNTER)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinInput();
				CurrentPinRegister->generic.mode = PIN_MODE_HS_COUNTER;
				hscounter->resource = timingResourceCounterClaim(TIMING_RESOURCE_ANY_HARDWARE_OC);
				timingResourceResetCounter(hscounter->resource);
				hscounter->lastCount = 0;
				hscounter->sampleFrames = RXBUFFER16(3);
				hscounter->sampleFrameCount = 0;
				hscounter->publicOutputDivisor = RXBUFFER16(5);
				if (hscounter->publicOutputDivisor == 0)
				{
					hscounter->publicOutputDivisor = 1; // Prevent divide by 0
				}
				hscounter->publicDataOutput = Rxbuffer[7];
				hscounter->frequency = 0;
				inputProcessInit(&hscounter->inputProcess);
			}
			break;
            
            case CONFIGURE_CHANNEL_MODE_1:
			{
				TXBUFFER32(3,timingResourceReadCounter(hscounter->resource));
				if (Rxbuffer[3] > 0)
				{
					timingResourceResetCounter(hscounter->resource);
				}
			}
			break;
            case CONFIGURE_CHANNEL_MODE_2:
			{
				TXBUFFER32(3,hscounter->frequency);
			}
			break;

        	case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&hscounter->inputProcess);
			}
			break;    
            case CONFIGURE_CHANNEL_MODE_DISABLE:
			{
                timingResourceRelease(hscounter->resource);
            }
            break;
		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
    }
	
}


/// \brief The function that updates High Speed Counter  mode
///
/// On the Serial Wombat 18AB chip the counting is done by the timer hardware on MCCP1 or CCP2 
/// The update looks to see if the specified number of frames has passed and if so updates 
/// the frequency and count. 
void updateHSCounter()
{ 
	debugHSCounter = (HSCounter_t*) CurrentPinRegister;
	HSCounter_t* hscounter = (HSCounter_t*) CurrentPinRegister;

	++hscounter->sampleFrameCount;
	if (hscounter->sampleFrameCount >= hscounter->sampleFrames)
	{
		hscounter->sampleFrameCount = 0;
		
		uint32_t newCount = timingResourceReadCounter(hscounter->resource);
		uint32_t difference = newCount - hscounter->lastCount;
	       hscounter->lastCount = 	newCount;
	       hscounter->frequency = difference * (1000 / hscounter->sampleFrames);
	       uint32_t output;
	        if (hscounter->publicDataOutput ==  PULSE_COUNT)
		{
			output = newCount / hscounter->publicOutputDivisor;
		}
		else
		{
			output = hscounter->frequency / hscounter->publicOutputDivisor;

		}

		if (output > 0x10000)
		{
			output = 0xFFFF; // Saturate
		}

		 CurrentPinRegister->generic.buffer = inputProcessProcess(&hscounter->inputProcess,(uint16_t)output);
	}

}


