/*
Copyright 2020-2025 Broadwell Consulting Inc.

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

typedef struct pwm_n{
    outputScale_t outputScale;
    pulse_output_t pulseOutput;
    uint32_t period_uS;
    uint16_t lastValue;
    uint8_t controlPin;
	uint8_t invert:1;  ///< Inverts the duty cycle %, not the signal.
}pwm_t;

void updatePWM(void);



#define pwm  ((pwm_t*) CurrentPinRegister)
void initPWM (void)
{
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PWM)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    BUILD_BUG_ON( sizeof(pwm_t) >  BYTES_PER_PIN_REGISTER );
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_PWM;
				CurrentPinRegister->generic.buffer = RXBUFFER16(4);
				pwm->invert = Rxbuffer[6];
                pwm->outputScale.sourcePin = CurrentPin;
                timingResourceRelease(TIMING_RESOURCE_ALL);
                InitializePinLow(CurrentPin);
                pwm->pulseOutput.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,1000);
                if (pwm->pulseOutput.resource == TIMING_RESOURCE_PORT_DMA)
                {
                     initializeBitStreamOutput(CurrentPin,  0, &pwm->pulseOutput.bitStream );
                }
                pwm->lastValue = CurrentPinRegister->generic.buffer + 1;
                pwm->period_uS = 1000;
                outputScaleInit(&pwm->outputScale);
				updatePWM();
			}
			break;
            case CONFIGURE_CHANNEL_MODE_HW_0:
			{
				
					pwm->period_uS = RXBUFFER32(3);
                    timingResourceRelease(pwm->pulseOutput.resource);
                    pwm->pulseOutput.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,pwm->period_uS);
				
			}
			break;
            
             case CONFIGURE_CHANNEL_MODE_10:
        {
            outputScaleCommProcess(&pwm->outputScale);
        }
        break;
         default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;


	}
}

void initPWMSimple()
{
                CurrentPinRegister->generic.mode = PIN_MODE_PWM;
				CurrentPinRegister->generic.buffer = 0;
				pwm->invert = 0;
                pwm->outputScale.sourcePin = CurrentPin;

                InitializePinLow(CurrentPin);
                pwm->pulseOutput.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,1000);
                pwm->lastValue = CurrentPinRegister->generic.buffer + 1;
                pwm->period_uS = 1000;
				updatePWM();
}

void updatePWM(void)
{
   
    uint16_t outputValue;
    
    outputValue = outputScaleProcess(&pwm->outputScale);
     if (pwm->outputScale.sourcePin != CurrentPin)
    {
	CurrentPinRegister->generic.buffer = outputValue;  
     }
        
    timingResourcePWM(&pwm->pulseOutput, pwm->period_uS, outputValue);
    timingResourceService(&pwm->pulseOutput);
     
   
}


