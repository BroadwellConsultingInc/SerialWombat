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
#include "pic24fj256ga702/mcc_generated_files/mcc.h"
uint16_t GetADCConversion(uint8_t pin);



typedef struct resistanceInput_n{

    uint32_t averageSum;
	uint16_t maximum;
	uint16_t minimum;
	uint16_t average;
	uint16_t averageTotalSamples;
	uint16_t averageCount;
	uint16_t filteredValue;
	uint16_t filterConstant;
	uint8_t publicDataSelection;
    uint8_t delayCount;
}resistanceInput_t;

#define resistanceInput ((resistanceInput_t*) CurrentPinRegister)

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
|0xC0|Pin To Set|0x02 (Resistance Input) | 0x55* |0x55* |0x55* |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 3 to Analog Input.

> `0xC0 0x03 0x02 0x55 0x55 0x55 0x55 0x55 `

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Configure resistance input averaging and filtering.  CONFIGURE_CHANNEL_MODE_0 should be sent for the pin prior to sending this command.

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

The pin should have previously been configured as an resistance input before sending this command.


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

The pin should have previously been configured as an resistance input  using CONFIGURE_CHANNEL_MODE_0 and the average and/or filtered values enabled using
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

void initResistanceInput (void)
{
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_RESISTANCE_INPUT)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinInput();
				CurrentPinAnalog();
				CurrentPinRegister->generic.mode = PIN_MODE_RESISTANCE_INPUT;
#ifndef AVERAGE128
				resistanceInput->averageTotalSamples = 0;
#endif
				resistanceInput->averageSum = 0;
				resistanceInput->averageCount = 0;
				resistanceInput->filterConstant = 0;
#ifdef DATAOURCEPIN_ENABLED
				resistanceInput->dataSourcePin = CurrentPin;
#endif
				resistanceInput->publicDataSelection = 0;

				resistanceInput->average =
					resistanceInput->filteredValue =
	//CurrentPinRegister->generic.buffer = 65535;
					resistanceInput->minimum = 65535;
					resistanceInput->maximum = 0;
                    resistanceInput->delayCount = 5;
                if (ADC1Semaphore == CurrentPin)
				{
					ADC1Semaphore = RESOURCE_AVAILABLE;
                    CTMUCON1L = 0;
                    CTMUCON1H = 0;
				}

			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
               
				resistanceInput->averageTotalSamples = RXBUFFER16(3);
				resistanceInput->averageSum = 0;
				resistanceInput->averageCount = 0;
				resistanceInput->filterConstant = RXBUFFER16(5);
				resistanceInput->publicDataSelection = Rxbuffer[7];
               
			}
			break;
		
		case CONFIGURE_CHANNEL_MODE_3: // Get Minimum and Maximum.
			{
                
				TXBUFFER16(3,resistanceInput->minimum);
				TXBUFFER16(5,resistanceInput->maximum);
				if (Rxbuffer[3] > 0)
				{
					resistanceInput->minimum = 65535;
					resistanceInput->maximum = 0;
				}
                
			}
			break;
		case CONFIGURE_CHANNEL_MODE_4: 
			{
               
				TXBUFFER16(3,resistanceInput->average);
				TXBUFFER16(5,resistanceInput->filteredValue);
               
			}
			break;
              default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
	}
}

resistanceInput_t* debugResistance;
void updateResistanceInput()
{ 
     debugResistance = (resistanceInput_t*)CurrentPinRegister;
	uint16_t sample = 0;
    if (resistanceInput->delayCount > 1)
    {
        --resistanceInput->delayCount;
        return;
    }
    else if (resistanceInput->delayCount == 1)
    {
        if (ADC1Semaphore == RESOURCE_AVAILABLE)
        {
            ADC1Semaphore = CurrentPin;

            GetCurrentPinReistanceOhmsSetup(); 
            --resistanceInput->delayCount;
        }
        return;
            
    }
    else if (resistanceInput->delayCount == 0)
    {
        if (AD1CON1bits.DONE)
        {
            sample = GetCurrentPinReistanceOhmsRead(GetSourceVoltage_mV());
            ADC1Semaphore = RESOURCE_AVAILABLE;

            resistanceInput->delayCount = 50;
        }
        else
        {
         return;  
            
         }
    }
    
 
	/*
    if (resistanceInput->dataSourcePin == CurrentPin)
    {
 sample =  GetADCConversion(CurrentPin);
if (sample >= ADC_MAX_COUNTS)
{
    sample = 0xFFFF;
}
    }
    else
    {
        sample = GetBuffer(resistanceInput->dataSourcePin);
    }*/
	if (resistanceInput -> averageTotalSamples > 0)
	{
		resistanceInput-> averageSum += sample;
		++resistanceInput->averageCount;
		if (resistanceInput-> averageCount >= resistanceInput->averageTotalSamples)
		{
			resistanceInput->average = resistanceInput->averageSum / resistanceInput->averageTotalSamples;
			resistanceInput->averageCount = 0;
			resistanceInput->averageSum = 0;
		}
	}
	else
	{
		resistanceInput->average = sample;
	}

	if (resistanceInput -> filterConstant != 0)
	{
		uint32_t temp = ((uint32_t)resistanceInput-> filteredValue) *  (resistanceInput->filterConstant + 1 );
		temp += (uint32_t)sample * (((uint32_t)65536) - resistanceInput->filterConstant);
	        resistanceInput->filteredValue = temp >> 16;
			

	}
	else
	{
		resistanceInput->filteredValue = sample;
	}

    if (sample < resistanceInput->minimum)
	{
		resistanceInput->minimum = sample;
	}
	if (sample > resistanceInput->maximum)
	{
		resistanceInput->maximum = sample;
	}
	switch (resistanceInput->publicDataSelection)
	{
		case 1: // filtered value
			CurrentPinRegister ->generic.buffer = resistanceInput->filteredValue;
		break;
		case 2: // average 
			CurrentPinRegister ->generic.buffer = resistanceInput->average;
		break;
		case 3: // minimum 
			CurrentPinRegister ->generic.buffer = resistanceInput->minimum;
		break;
		case 4: // maximum 
			CurrentPinRegister ->generic.buffer = resistanceInput->maximum;
		break;

		case 0:
		default:
			CurrentPinRegister->generic.buffer = sample;
		break;
	}
	

}

