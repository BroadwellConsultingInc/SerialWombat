/*
Copyright 2020-2022 Broadwell Consulting Inc.

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
 
 Serial Wombat is a registered trademark in the United States of Broadwell 
 Consulting Inc.
*/
#include "serialWombat.h"
#include <stdint.h>
#include "inputProcess.h"
#include "pic24fj256ga702/mcc_generated_files/mcc.h"
uint16_t GetADCConversion(uint8_t pin);



typedef struct resistanceInput_n{

    uint16_t lastSample;
    uint8_t delayCount;
    inputProcess_t inputProcess;
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

Initialize Resistance Input.  Disables averaged and filtered values.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x02 (Resistance Input) | 0x55* |0x55* |0x55* |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 3 to Resistance Input.

> `0xC0 0x03 0x18 0x55 0x55 0x55 0x55 0x55 `

----


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
                    inputProcessInit(&resistanceInput->inputProcess);
                    resistanceInput->inputProcess.active = true;
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
               
				resistanceInput->inputProcess.average.samplesToAverage = RXBUFFER16(3);
                resistanceInput->inputProcess.firstOrder.filterconstant = RXBUFFER16(5);
				resistanceInput->inputProcess.filterMode = Rxbuffer[7];
                
			}
			break;
            /*  Removed
             
		case CONFIGURE_CHANNEL_MODE_2:
			{
                  if (CurrentPinRegister->generic.mode == PIN_MODE_ANALOGINPUT)
				{
				resistanceInput->dataSourcePin = Rxbuffer[3];
                }
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;
             * */

		case CONFIGURE_CHANNEL_MODE_3: // Get Minimum and Maximum.
			{
                
				TXBUFFER16(3,resistanceInput->inputProcess.min);
				TXBUFFER16(5,resistanceInput->inputProcess.max);
				if (Rxbuffer[3] > 0)
				{
					resistanceInput->inputProcess.min = 65535;
					resistanceInput->inputProcess.max = 0;
				}
                
			}
			break;
		case CONFIGURE_CHANNEL_MODE_4: 
			{
                
				TXBUFFER16(3,resistanceInput->inputProcess.average.average);
				TXBUFFER16(5,resistanceInput->inputProcess.firstOrder.filteredValue);
               
			}
			break;
        	case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&resistanceInput->inputProcess);
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
	
    if (resistanceInput->delayCount > 1)
    {
        --resistanceInput->delayCount;
         CurrentPinRegister->generic.buffer = inputProcessProcess(&resistanceInput->inputProcess,resistanceInput->lastSample);
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
         CurrentPinRegister->generic.buffer = inputProcessProcess(&resistanceInput->inputProcess,resistanceInput->lastSample);
        return;
            
    }
    else if (resistanceInput->delayCount == 0)
    {
        if (AD1CON1bits.DONE)
        {
            resistanceInput->lastSample = GetCurrentPinReistanceOhmsRead(GetSourceVoltage_mV());
            ADC1Semaphore = RESOURCE_AVAILABLE;

            resistanceInput->delayCount = 50;
        }
        else
        {
             CurrentPinRegister->generic.buffer = inputProcessProcess(&resistanceInput->inputProcess,resistanceInput->lastSample);
         return;  
            
         }
    }
    
 CurrentPinRegister->generic.buffer = inputProcessProcess(&resistanceInput->inputProcess,resistanceInput->lastSample);
 
	

}

