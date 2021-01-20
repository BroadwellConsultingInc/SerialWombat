/*
Copyright 2020 Broadwell Consulting Inc.

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


#if (defined __16F15214__) || (defined __16F15224__)
#define AVERAGE64

#elif (defined __24FJ256GA702)
#define DATASOURCEPIN_ENABLED

#endif


typedef struct analogInput_n{
#ifdef AVERAGE64
    uint16_t averageSum;
#else
	uint32_t averageSum;
#endif
	uint16_t maximum;
	uint16_t minimum;
	uint16_t average;
#ifdef AVERAGE64
    uint8_t averageTotalSamples;
#else
	uint16_t averageTotalSamples;
#endif
	uint16_t averageCount;
	uint16_t filteredValue;
	uint16_t filterConstant;
#ifdef DATAOURCEPIN_ENABLED
	uint8_t dataSourcePin;
#endif

}analogInput_t;

#define analogInput ((analogInput_t*) CurrentPinRegister)


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

