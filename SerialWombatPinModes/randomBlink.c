/*
Copyright 2026 Broadwell Consulting Inc.

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

/* Serial Wombat is a registered trademark of Broadwell Consulting Inc. in the United States.
 * See SerialWombat.com for usage instructions.
 * */

#include "serialWombat.h"
#include <stdint.h>
#include "outputScale.h"
#include "swMath.h"



typedef struct randomBlink_n{
    outputScale_t outputScale;
    pulse_output_t pulseOutput;
    uint16_t offTimeMin;
    uint16_t offTimeMax;
    uint16_t onTimeMin;
    uint16_t onTimeMax;
    uint16_t onPWMMin;
    uint16_t onPWMMax;
    uint16_t offPWMMin;
    uint16_t offPWMMax;
    uint16_t countDown;
    uint16_t currentlyOn:1;

}randomBlink_t;

void updateRandomBlink(void);

#define PWMFREQUENCY 120
#define PWM_uSEC  (1000000/PWMFREQUENCY)


#define randomBlink  ((randomBlink_t*) CurrentPinRegister)
void initRandomBlink (void)
{
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_RANDOMBLINK)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    BUILD_BUG_ON( sizeof(randomBlink_t) >  BYTES_PER_PIN_REGISTER );
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_RANDOMBLINK;
				randomBlink->onTimeMax = RXBUFFER16(3);
                randomBlink->offTimeMin = randomBlink->offTimeMax = RXBUFFER16(5);
                randomBlink->onTimeMin = randomBlink->offTimeMin = 0;
                randomBlink->onPWMMin = randomBlink->onPWMMax = 0xFFFF;
                randomBlink->offPWMMin = randomBlink->offPWMMax = 0;
				timingResourceRelease(TIMING_RESOURCE_ALL);
                InitializePinLow(CurrentPin);
                randomBlink->pulseOutput.resource = timingResourcePWMClaim(TIMING_RESOURCE_PORT_DMA,PWM_uSEC);
               
                initializeBitStreamOutput(CurrentPin,  0, &randomBlink->pulseOutput.bitStream );
                randomBlink->currentlyOn = 0;
                randomBlink->countDown = 0;

                outputScaleInit(&randomBlink->outputScale);
			}
			break;

            case CONFIGURE_CHANNEL_MODE_1:
            {
                randomBlink->onPWMMin = RXBUFFER16(3);
                randomBlink->onPWMMax = RXBUFFER16(5);
            }
            break;

            case CONFIGURE_CHANNEL_MODE_2:
            {
                randomBlink->offPWMMin = RXBUFFER16(3);
                randomBlink->offPWMMax = RXBUFFER16(5);
            }
            break;

            case CONFIGURE_CHANNEL_MODE_3:
            {
                randomBlink->onTimeMin = RXBUFFER16(3);
                randomBlink->offTimeMin = RXBUFFER16(5);
            }
            break;

            
             case CONFIGURE_CHANNEL_MODE_10:
        {
            outputScaleCommProcess(&randomBlink->outputScale);
        }
        break;
         default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;


	}
}


void updateRandomBlink(void)
{
   
    if (randomBlink->countDown > 0)
    {
        randomBlink->countDown--;
    }
    else
    {
        if (randomBlink->currentlyOn)
        {
            randomBlink->countDown = randomRange(randomBlink->offTimeMin, randomBlink->offTimeMax);
            CurrentPinRegister->generic.buffer = randomRange(randomBlink->offPWMMin, randomBlink->offPWMMax);
        }
        else
        {
            randomBlink->countDown = randomRange(randomBlink->onTimeMin, randomBlink->onTimeMax);
            CurrentPinRegister->generic.buffer = randomRange(randomBlink->onPWMMin, randomBlink->onPWMMax);
        }
        randomBlink->currentlyOn = !randomBlink->currentlyOn;
    }
        
    uint16_t outputValue = outputScaleProcess(&randomBlink->outputScale);
        
    timingResourcePWM(&randomBlink->pulseOutput, PWM_uSEC, outputValue);
    timingResourceService(&randomBlink->pulseOutput);
     
   
}


