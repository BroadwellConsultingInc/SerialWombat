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
#include "inputProcess.h"
#include <stdint.h>

typedef enum {
	HC_SR04 = 0,
}DRIVER_t;

typedef struct ultrasonicDistance_n{
    inputProcess_t inputProcess;
    uint16_t PulseCounter;
	uint16_t PulseLowTime;
    uint16_t PulseHighTime;
	uint16_t lastTimerTime;
    uint16_t pulseTimeoutSetting;
    uint16_t pulseTimeoutCounter;
    uint8_t triggerPin;
    uint8_t driver;
	uint8_t readState:1;
    uint8_t autotrigger:1;
    uint8_t manualTrigger:1;
}ultrasonicDistance_t;

#define COUNTS_TO_uS(_a) ((uint32_t)( _a * (uint32_t) (65536.0 * 1000000 / DMA_FREQUENCY + .5)) >> 16)
#define COUNTS_TO_Hz(_a) (((uint32_t)DMA_FREQUENCY * 2) / ( _a  ) + 1) >> 1;
#define COUNTS_TO_mm(_a) (COUNTS_TO_uS(_a) * 170 / 1000)  //TODO future optimization: optimize for integer math with fractional multipy and shift

void initUltrasonicDistance()
{
    BUILD_BUG_ON( sizeof(ultrasonicDistance_t) >  BYTES_AVAILABLE_INPUT_DMA ); 
	ultrasonicDistance_t* ud = (ultrasonicDistance_t*) CurrentPinRegister;
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_ULTRASONIC_DISTANCE)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:

			{

				ud->driver = Rxbuffer[3]; //TODO add range checks
				ud->triggerPin = Rxbuffer[4];
                ud->autotrigger = Rxbuffer[6];
             
                PinLow(ud->triggerPin);
				CurrentPinRegister->generic.mode =PIN_MODE_ULTRASONIC_DISTANCE;
				CurrentPinRegister->generic.buffer = 0; 
				ud->PulseCounter = 0;
				ud->lastTimerTime = 0;
				CurrentPinInput();
				if (Rxbuffer[5]) 
				{
					CurrentPinPullUp();
				}
				else
				{
					CurrentPinNoPullUp();
				}
                inputProcessInit(&ud->inputProcess);
                    ud->inputProcess.active = true;
                if (ud->autotrigger){
                    PinHigh(ud->triggerPin);
                    PinLow(ud->triggerPin);
                }

			}
			break;
            case CONFIGURE_CHANNEL_MODE_1:
			{
				
                    ud->manualTrigger = Rxbuffer[3];
              
					TXBUFFER16(3,CurrentPinRegister->generic.buffer);
				
				Txbuffer[7] = 0; //IOC_Overflow;  
				TXBUFFER16(5,ud->PulseCounter );
				//                IOC_Overflow = 0;
			}
			break;

case CONFIGURE_CHANNEL_MODE_2:
			{
				
					TXBUFFER16(3,CurrentPinRegister->generic.buffer);
				
				Txbuffer[7] = 0; //IOC_Overflow;  
				TXBUFFER16(5,ud->PulseCounter );
				//                IOC_Overflow = 0;
			}
			break;
		case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&ud->inputProcess);
			}
			break;
                    default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
	}


} 
ultrasonicDistance_t* debugUltrasonicDistance;
void updateUltrasonicDistance()
{
	//  pulseIn_t* pulse = (pulseIn_t*) CurrentPinRegister;
	ultrasonicDistance_t* ud = (ultrasonicDistance_t*) CurrentPinRegister;
    debugUltrasonicDistance = ud;
	uint8_t sample;

    if (ud->manualTrigger)
    {
        PinHigh(ud->triggerPin);
        PinLow(ud->triggerPin);
        ud->manualTrigger = 0;
    }
    if (ud->pulseTimeoutSetting > 0 )
    {
        if (ud->pulseTimeoutCounter < 65535)
        {
        ++ ud->pulseTimeoutCounter;
        }
        
    }
		sample =  PulseInGetOldestDMABit(CurrentPin);
	do
	{
		if (sample)
		{
			//Pin is high
			if (ud->readState)
			{
				//Last pin was high
				++ud->lastTimerTime;
			}
			else
			{
				//Last pin was low
				ud->PulseLowTime = ud->lastTimerTime;
	ud->lastTimerTime = 0;
				ud->readState = 1;
			}
		}
		else
		{
			//Pin is Low
			if (ud->readState)
			{

				ud->PulseHighTime =  ud->lastTimerTime;
				
				ud->lastTimerTime = 0;
				ud->readState = 0;
				++ud->PulseCounter;
				ud->pulseTimeoutCounter = 0;
                CurrentPinRegister->generic.buffer = inputProcessProcess(&ud->inputProcess,COUNTS_TO_mm( ud->PulseHighTime));
                if(ud->autotrigger)
                {
                    PinHigh(ud->triggerPin);
                    PinLow(ud->triggerPin);
                }
			}
			else
			{
				//Last pin was low
				++ud->lastTimerTime;
			}
		}
		sample = PulseInGetOldestDMABit(CurrentPin);
	} while (  sample != 2 );
}

