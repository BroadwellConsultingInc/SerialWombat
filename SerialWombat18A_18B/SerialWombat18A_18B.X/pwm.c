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

/* Serial Wombat is a trademark of Broadwell Consulting Inc. */

#include "serialWombat.h"
#include <stdint.h>
#include "outputScale.h"

typedef struct pulseTimer_n{
    outputScale_t outputScale;
    uint32_t period_uS;
    uint16_t lastValue;
    uint8_t controlPin;
	uint8_t invert:1;  ///< Inverts the duty cycle %, not the signal.
}pwm_t;

void updatePWM(void);


//TODO: 
volatile uint32_t debugInterruptTestCounter = 0;
void debugInterruptTest()
{
    PinLow(12);
    ++debugInterruptTestCounter;
}
#define pwm  ((pwm_t*) CurrentPinRegister)
void initPWM (void)
{

	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_PWM;
				CurrentPinRegister->generic.buffer = RXBUFFER16(4);
				pwm->invert = Rxbuffer[6];
                pwm->outputScale.sourcePin = CurrentPin;

                CurrentPinLow(); //TODO make output, initialize DMA low
                CurrentPinRegister->pulse_output.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,1000); 
                pwm->lastValue = CurrentPinRegister->generic.buffer + 1;
                pwm->period_uS = 1000;
				updatePWM();
                
                //TODO TEST CODE:
                {
                    
                    TIMING_RESOURCE_t resource;
                    resource = timingResourceInterruptClaim(TIMING_RESOURCE_OC1, 24000, 1000, debugInterruptTest);
                    INTERRUPT_GlobalDisable();
                    timingResourceInterruptActivate(resource);
                    PinHigh(12);
                    INTERRUPT_GlobalEnable();
                }
			}
			break;
            case CONFIGURE_CHANNEL_MODE_HW_0:
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_PWM)
				{
					pwm->period_uS = RXBUFFER32(3);
                    timingResourceRelease(CurrentPinRegister->pulse_output.resource);
                    CurrentPinRegister->pulse_output.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,pwm->period_uS); 
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;


	}
}

void initPWMSimple()
{
    Rxbuffer[0] = CONFIGURE_CHANNEL_MODE_0;
    Rxbuffer[4] = 0;
    Rxbuffer[5] = 0;
    initPWM();
}

void updatePWM(void)
{
   
    uint16_t outputValue;
    
    outputValue = outputScaleProcess(&pwm->outputScale);
	  
        
    timingResourcePWM(CurrentPinRegister->pulse_output.resource, pwm->period_uS, outputValue);
    timingResourceService(CurrentPinRegister->pulse_output.resource);
     
   
}


