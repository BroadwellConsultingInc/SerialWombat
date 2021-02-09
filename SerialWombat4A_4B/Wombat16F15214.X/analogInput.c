/*
Copyright 2020-2021 Broadwell Consulting Inc.

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

/*!
 \file analogInput.c

 This file contains the Analog Input pin mode for the SerialWombat 4A and 4B.
 */

#if (defined __16F15214__) || (defined __16F15224__)
#define AVERAGE64

#elif (defined __24FJ256GA702)
#define DATASOURCEPIN_ENABLED

#endif


typedef struct analogInput_n{
#ifdef AVERAGE64
    uint16_t averageSum;   ///< Contains the running sum of 10 bit A/D conversions.  When 64 are added together, we're done.
#else
	uint32_t averageSum; ///< container for arbitrary number of values.
#endif
	uint16_t maximum;  ///< Largest Conversion seen, scaled to 16 bits.
	uint16_t minimum;  ///< Smallest Conversion seen, scaled to 16 bits.
	uint16_t average;  ///< Last completed average value
#ifdef AVERAGE64
    uint8_t averageTotalSamples;  ///< Number of samples to average.  Any value other than 0 is treated as 64 on SW4A and SW4B.
#else
	uint16_t averageTotalSamples;
#endif
	uint16_t averageCount;  ///< Number of samples added so far to averageSum
	uint16_t filteredValue; ///< Filtered output value
	uint16_t filterConstant; ///< 16 bit first order filter constant chosen by the user  0 = filtered value off.
#ifdef DATAOURCEPIN_ENABLED
	uint8_t dataSourcePin;
#endif

}analogInput_t;

#define analogInput ((analogInput_t*) CurrentPinRegister)

/*!
    \brief Initialization routine for Analog Input

----

Retrevial of Raw A/D conversions
-------------------------------

Configure the A/D using the CONFIGURE_CHANNEL_MODE_0 command before reading values.  
Raw A/D conversions are stored in the Pin's 16-bit Public data area.  Use the Read Pin Buffer command to retreive it.

-----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Analog Input.  Disables averaged and filtered values.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x02 (Analog Input) | 0x55* |0x55* |0x55* |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 3 to Analog Input.

> `0xC0 0x03 0x02 0x55 0x55 0x55 0x55 0x55 `

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Configure analog input averaging and filtering.  CONFIGURE_CHANNEL_MODE_0 should be sent for the pin prior to sending this command.

Filtering is done by the following algorithm:  

Filtered Value = Prior Filtered value * (constant / 65536) + New Sample * ((65536 - constant) 

This happens every 1mS (1000 hZ).


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set|0x02 (Analog Input) |Averaging Count low byte (0 = off, 64 = 64 counts) | Averaging Count high byte (set to 0, for compatability with SW19) |  Filter Constant Low Byte | Filter Constant High Byte | 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Configure pin 3 Analog input to turn on averaging, set filter constant to 64358 (0xFB66)

> `0xC1 0x03 0x02 0x40 0x00 0x66 0xFB 0x55 `


----

CONFIGURE_CHANNEL_MODE_2:
---------------------


Unused on the SW4A and SW4B.

----

CONFIGURE_CHANNEL_MODE_3:
---------------------

Retreive the Minimum and Maximum recorded raw values.

This command can optionally reset the minimum and maximum values after reading.  This will cause them both to be set to the next A/D sample taken.

The pin should have previously been configured as an analog input before sending this command.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin Number|0x02 (Analog Input) | 0:  Don't reset values  1:  Reset Minimum and Maximum |     0x55* |0x55* |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin Number|0x02 (Analog Input) | Minimum Low Byte | Minimum High Byte | Maximum Low Byte | Maximum High Byte | Echo of Byte 7 |



Examples:

Get Minimum and maximum values from pin 3, and reset after reading.  (Assume minimum value was 0x3F80, and Maximum was 0xDC40 )

Sent: 

> `0xC3 0x03 0x02 0x01 0x55 0x55 0x55 0x55`

Received:

> `0xC3 0x03 0x02 0x80 0x3F 0x40 0xDC 0x55`

----

CONFIGURE_CHANNEL_MODE_4:
---------------------

Retreive the averaged and filtered values. 

The pin should have previously been configured as an analog input  using CONFIGURE_CHANNEL_MODE_0 and the average and/or filtered values enabled using
CONFIGURE_CHANNEL_MODE_1 before sending this command.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC4|Pin Number|0x02 (Analog Input) | 0x55* |     0x55* |0x55* |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC4|Pin Number|0x02 (Analog Input) | Average Low Byte | Average High Byte | Filtered Low Byte | Filtered High Byte | Echo of Byte 7 |



Examples:

Get Averaged and Filtered values from pin 3.  (Assume Averaged value was 0x3F80, and Filtered was 0xDC40 )

Sent: 

> `0xC4 0x03 0x02 0x55 0x55 0x55 0x55 0x55`

Received:

> `0xC4 0x03 0x02 0x80 0x3F 0x40 0xDC 0x55`

*/

void initAnalogInput (void)
{
	
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinInput();
				CurrentPinAnalog();
				CurrentPinRegister->generic.mode = PIN_MODE_ANALOGINPUT;
#ifndef AVERAGE64
				analogInput->averageTotalSamples = 0;
#endif
				analogInput->averageSum = 0;
				analogInput->averageCount = 0;
				analogInput->filterConstant = 0;
#ifdef DATAOURCEPIN_ENABLED
				analogInput->dataSourcePin = CurrentPin;
#endif
				analogInput->average =
					analogInput->filteredValue = GetADCConversion(CurrentPin);
                
					analogInput->minimum = 65535;
					analogInput->maximum = 0;
			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_ANALOGINPUT;
				analogInput->averageTotalSamples = (uint8_t) RXBUFFER16(3);
				analogInput->averageSum = 0;
				analogInput->averageCount = 0;
				analogInput->filterConstant = RXBUFFER16(5);
				//analogInput->publicDataSelection = Rxbuffer[7];
			}
			break;
#ifdef DATAOURCEPIN_ENABLED
		case CONFIGURE_CHANNEL_MODE_2:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_ANALOGINPUT;
				analogInput->dataSourcePin = Rxbuffer[3];
			}
			break;
#endif
		case CONFIGURE_CHANNEL_MODE_3: // Get Minimum and Maximum.
			{
				TXBUFFER16(3,analogInput->minimum);
				TXBUFFER16(5,analogInput->maximum);
				if (Rxbuffer[3] > 0)
				{
					analogInput->minimum = 65535;
					analogInput->maximum = 0;
				}
			}
			break;
		case CONFIGURE_CHANNEL_MODE_4: 
			{
				TXBUFFER16(3,analogInput->average);
				TXBUFFER16(5,analogInput->filteredValue);
			}
			break;
	}
}


/*!
\brief Periodic call to service the Analog Input State Machine for a pin

This function expects to get called every mS.  

This function does A/D conversions during the servicing of the function using the internal 10-bit A/D converter.
Values are shifted six bits left to scale to 0-65535 public data range.  
Conversions which yield 1023 (Maximum value) are Scaled to 65535 to indicate maximum value.  This happens after the
A/D conversion is used to calculate averaged and filtered values, so Averaged values could reach a maximum value of 
65472, not 65535 (64 * 1023 = 65472).

Filtered value and averaged value are updated every call if enabled.  These values are based on scaled values. 

Minimum and Maximum are updated every call and are based on raw A/D values.
*/
void updateAnalogInput()
{ 

	CurrentPinRegister->generic.buffer =  GetADCConversion(CurrentPin);
	if (analogInput -> averageTotalSamples > 0)
	{
		analogInput-> averageSum += (CurrentPinRegister->generic.buffer>>6);
		++analogInput->averageCount;
		if (analogInput->averageCount == 64)
		{
			analogInput->average = analogInput->averageSum;
			analogInput->averageCount = 0;
			analogInput->averageSum = 0;
		}
	}


	if (analogInput -> filterConstant != 0)
	{
		uint32_t temp = ((uint32_t)analogInput-> filteredValue) *  analogInput->filterConstant;
		temp += CurrentPinRegister->generic.buffer * (65536ul - analogInput->filterConstant);
		analogInput->filteredValue = temp >> 16;
	}

	if (CurrentPinRegister->generic.buffer >= 0xFFC0)
	{
		CurrentPinRegister->generic.buffer = 0xFFFF;
	}

	if (CurrentPinRegister->generic.buffer < analogInput->minimum)
	{
		analogInput->minimum = CurrentPinRegister->generic.buffer;
	}
	if (CurrentPinRegister->generic.buffer > analogInput->maximum)
	{
		analogInput->maximum = CurrentPinRegister->generic.buffer;
	}	

}

