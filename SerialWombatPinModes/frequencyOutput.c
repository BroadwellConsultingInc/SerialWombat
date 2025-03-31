/*
Copyright 2024 Broadwell Consulting Inc.

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

/* Serial Wombat is a trademark of Broadwell Consulting Inc. */

#include "serialWombat.h"
#include <stdint.h>
#include "outputScale.h"

typedef struct frequencyOutput_n{
    outputScale_t outputScale;
    pulse_output_t pulseOutput;
    uint16_t dutyCycle;
}frequencyOutput_t;

void updateFrequencyOutput(void);



#define fo  ((frequencyOutput_t*) CurrentPinRegister)
void initFrequencyOutput (void)
{
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_FREQUENCY_OUTPUT)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    BUILD_BUG_ON( sizeof(frequencyOutput_t) >  BYTES_PER_PIN_REGISTER );
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_FREQUENCY_OUTPUT;
				fo->dutyCycle = RXBUFFER16(3);
				CurrentPinRegister->generic.buffer = RXBUFFER16(5);
                fo->outputScale.sourcePin = CurrentPin;
                 uint32_t us = 1000000;
                us /= CurrentPinRegister->generic.buffer;
                InitializePinLow(CurrentPin);
                if (!Rxbuffer[7])
                {
                    fo->pulseOutput.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,us);
                }
                else
                {
                   
                    fo->pulseOutput.resource = timingResourcePWMClaim( TIMING_RESOURCE_PORT_DMA,us);
                    
                }
                outputScaleInit(&fo->outputScale);
				updateFrequencyOutput();
               
			}
			break;
            case CONFIGURE_CHANNEL_MODE_HW_0:
			{
				
					fo->dutyCycle = RXBUFFER16(3);
			}
			break;
            
             case CONFIGURE_CHANNEL_MODE_10:
        {
            outputScaleCommProcess(&fo->outputScale);
        }
        break;
         default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;


	}
}


void updateFrequencyOutput(void)
{
   
    uint16_t outputValue;
    
    outputValue = outputScaleProcess(&fo->outputScale);
     if (fo->outputScale.sourcePin != CurrentPin)
    {
	CurrentPinRegister->generic.buffer = outputValue;  
     }

    if (outputValue == 0 )
    {	    
    timingResourcePWM(&fo->pulseOutput,1000 , 0);
    }
    else
    {
	    uint32_t us = 1000000;
	    us /= outputValue;
    timingResourcePWM(&fo->pulseOutput, us, fo->dutyCycle);
    }
    timingResourceService(&fo->pulseOutput);
     
   
}


