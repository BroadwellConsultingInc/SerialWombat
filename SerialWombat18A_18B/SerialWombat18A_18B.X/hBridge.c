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

typedef struct hBridge_n{
    outputScale_t outputScale;
    uint32_t period_uS;
    uint16_t lastValue;
    uint8_t secondPin;
    uint8_t trmResource;
	uint8_t invert:1;  ///< Inverts the duty cycle %, not the signal.
}hBridge_t;

void updatehBridge(void);



#define hBridge  ((hBridge_t*) CurrentPinRegister)
hBridge_t* debughBridge;
void inithBridge (void)
{
    debughBridge = hBridge;
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_HBRIDGE)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    BUILD_BUG_ON( sizeof(hBridge_t) >  BYTES_AVAIALABLE_OUTPUT_PULSE );   
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_HBRIDGE;
				CurrentPinRegister->generic.buffer = 32768;
				
				hBridge->secondPin = Rxbuffer[3];
				
				hBridge->outputScale.sourcePin = CurrentPin;

                InitializePinLow(CurrentPin);
                InitializePinLow(hBridge->secondPin);
                CurrentPinLow();
                	PinLow(hBridge->secondPin);
                hBridge->trmResource =  timingResourcePWMClaim(TIMING_RESOURCE_ANY,1000); 
                hBridge->lastValue = 0;
                hBridge->period_uS = 1000;
                outputScaleInit(&hBridge->outputScale);
		updatehBridge();
               
			}
			break;
            case CONFIGURE_CHANNEL_MODE_HW_0:
			{
				
					hBridge->period_uS = RXBUFFER32(3);
                    timingResourceRelease(hBridge->trmResource);
                    hBridge->trmResource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,hBridge->period_uS); 
				
			}
			break;
            
             case CONFIGURE_CHANNEL_MODE_10:
        {
            outputScaleCommProcess(&hBridge->outputScale);
        }
        break;
         default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;


	}
}


void updatehBridge(void)
{

	uint16_t outputValue;

	outputValue = outputScaleProcess(&hBridge->outputScale);
	CurrentPinRegister->generic.buffer = outputValue; 

	if (outputValue == 0)
	{
		//Main pin low
		//Secondary pin high
		//Secondary pin controls resouce
		if (hBridge->lastValue >= 32768)
		{
			//Claim PWM for secondary  pin
            timingResourceRelease(hBridge->trmResource);
			uint8_t temp = CurrentPin;
			CurrentPin = hBridge->secondPin;
			hBridge->trmResource =  timingResourcePWMClaim(hBridge->trmResource,hBridge->period_uS); 
            timingResourcePWM(hBridge->trmResource, hBridge->period_uS, 65535);
			CurrentPin = temp;

		}
        if (outputValue!= hBridge->lastValue)
        {
            uint8_t temp = CurrentPin;
			CurrentPin = hBridge->secondPin;
            timingResourcePWM(hBridge->trmResource, hBridge->period_uS, 65535);
			CurrentPin = temp;
            CurrentPinLow();
        }
		
         uint8_t temp = CurrentPin;
		timingResourceService(CurrentPinRegister->pulse_output.resource);
        CurrentPin = temp;

	}
	else if (outputValue == 0xFFFF)
	{
		//Main pin high
		//Secondary pin low
		//Main pin controls resouce
		if (hBridge->lastValue < 32768)
		{
			//Claim PWM for main pin
			uint8_t temp = CurrentPin;
			CurrentPin = hBridge->secondPin;
			    timingResourceRelease(hBridge->trmResource);
			CurrentPin = temp;
			hBridge->trmResource =  timingResourcePWMClaim(hBridge->trmResource,hBridge->period_uS); 
		}
        if (outputValue!= hBridge->lastValue)
        {    
            timingResourcePWM(hBridge->trmResource, hBridge->period_uS, 65535);
            	PinLow(hBridge->secondPin);

        }
		timingResourceService(CurrentPinRegister->pulse_output.resource);
		
	}
	else if (outputValue == 32768)
	{
		//Main pin high or low depending on settings
		//Secondary pin  matches Main pin
		//Main pin controls resouce
		if (hBridge->lastValue < 32768)
		{
			//Claim PWM for main pin
			uint8_t temp = CurrentPin;
			CurrentPin = hBridge->secondPin;
			    timingResourceRelease(hBridge->trmResource);
			CurrentPin = temp;
			hBridge->trmResource = timingResourcePWMClaim(hBridge->trmResource,hBridge->period_uS); 
		}
		//TODO add high or low option
        if (outputValue!= hBridge->lastValue)
        { 
		timingResourcePWM(hBridge->trmResource, hBridge->period_uS, 0);
        PinLow(hBridge->secondPin);
         }
		
        timingResourceService(CurrentPinRegister->pulse_output.resource);
	}
	else if (outputValue > 0x8000 )
	{
		//Main pin high
		//Secondary pin low
		//Main pin controls resouce
		if (hBridge->lastValue < 0x8000)
		{
			//Claim PWM for main  pin
         
			uint8_t temp = CurrentPin;
			CurrentPin = hBridge->secondPin;
			   timingResourceRelease(hBridge->trmResource);
			CurrentPin = temp;
            hBridge->trmResource =  timingResourcePWMClaim(hBridge->trmResource,hBridge->period_uS); 

		}
		if (outputValue!= hBridge->lastValue)
        { 
		timingResourcePWM(hBridge->trmResource, hBridge->period_uS, (outputValue - 0x8000) * 2);
        PinLow(hBridge->secondPin);
         }
        timingResourceService(hBridge->trmResource);
	}
	else if (outputValue < 32768 )
	{
		//Main pin low
		//Secondary pin high
		//Secondary pin controls resouce
		if (hBridge->lastValue >= 32768)
		{
			timingResourceRelease(hBridge->trmResource);
			uint8_t temp = CurrentPin;
			CurrentPin = hBridge->secondPin;
			hBridge->trmResource = timingResourcePWMClaim(hBridge->trmResource,hBridge->period_uS); 
			CurrentPin = temp;

		}
		if (outputValue!= hBridge->lastValue)
        { 
            uint8_t temp = CurrentPin;
            CurrentPin = hBridge->secondPin;
		timingResourcePWM(hBridge->trmResource, hBridge->period_uS, (  32768 - outputValue) * 2);
        CurrentPin = temp;
        CurrentPinLow();
         }
        uint8_t temp = CurrentPin;
        CurrentPin = hBridge->secondPin;
		timingResourceService(hBridge->trmResource);
        CurrentPin = temp;
	}
    hBridge->lastValue = outputValue;


}


