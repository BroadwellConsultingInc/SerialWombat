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

#include "SerialWombat.h"
#include "inputProcess.h"
#include <stdint.h>

typedef enum {
    HIGH_TIME = 0,
		LOW_TIME = 1,
		PULSE_COUNT = 2,
		PERIOD_ON_LTH_TRANSITION= 3,
		PERIOD_ON_HTL_TRANSITION = 4,
		FREQUENCY_ON_LTH_TRANSITION = 5,
		FREQUENCY_ON_HTL_TRANSITION = 6,
		DUTYCYCLE_ON_LTH_TRANSITION = 7,
		DUTYCYCLE_ON_HTL_TRANSITION = 8,
}PULSE_TIMER_PUBLIC_DATA;
typedef struct pulseTimer_n{
    inputProcess_t inputProcess;
    uint16_t PulseCounter;
	uint16_t PulseLowTime;
    uint16_t PulseHighTime;
	uint16_t lastTimerTime;
    uint16_t pulseTimeoutSetting;
    uint16_t pulseTimeoutCounter;
	uint8_t readState:1;
	uint8_t units: 1; // 0 = uS, 1 = mS
    uint8_t publicDataOutput;
	
}pulseTimer_t;

#define COUNTS_TO_uS(_a) ((uint32_t)( _a * (uint32_t) (65536.0 * 1000000 / DMA_FREQUENCY + .5)) >> 16)
#define COUNTS_TO_Hz(_a) (((uint32_t)DMA_FREQUENCY * 2) / ( _a  ) + 1) >> 1;

void initPulseTimer()
{
    BUILD_BUG_ON( sizeof(pulseTimer_t) >  BYTES_AVAILABLE_INPUT_DMA ); 
	pulseTimer_t* pulseTimer = (pulseTimer_t*) CurrentPinRegister;
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PULSE_TIMER)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:

			{
				pulseTimer->units = Rxbuffer[4];
				CurrentPinRegister->generic.mode =PIN_MODE_PULSE_TIMER;
				CurrentPinRegister->generic.buffer = 0; 
				pulseTimer->publicDataOutput = HIGH_TIME;
				pulseTimer->PulseCounter = 0;
				pulseTimer->lastTimerTime = 0;
				CurrentPinInput();
				if (Rxbuffer[3]) 
				{
					CurrentPinPullUp();
				}
				else
				{
					CurrentPinNoPullUp();
				}
                inputProcessInit(&pulseTimer->inputProcess);

			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
				if (pulseTimer->units)
				{
					TXBUFFER16(3,pulseTimer->PulseHighTime );
				}
				else
				{
					TXBUFFER16(3,COUNTS_TO_uS(pulseTimer->PulseHighTime));
				}
				Txbuffer[7] = (uint8_t)pulseTimer->PulseCounter;  
				if (pulseTimer->units)
				{
					TXBUFFER16(5,pulseTimer->PulseLowTime );
				}
				else
				{
					TXBUFFER16(5,COUNTS_TO_uS(pulseTimer->PulseLowTime));
				}

			}
			break;

		case CONFIGURE_CHANNEL_MODE_2:
			{
				//                extern __bit IOC_Overflow ;
				if (pulseTimer->units)
				{
					TXBUFFER16(3,CurrentPinRegister->generic.buffer);
				}
				else
				{
					TXBUFFER16(3,COUNTS_TO_uS(CurrentPinRegister->generic.buffer));
				}
				Txbuffer[7] = 0; //IOC_Overflow;  
				TXBUFFER16(5,pulseTimer->PulseCounter );
				//                IOC_Overflow = 0;
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3:
			{
				if (Rxbuffer[3] <= DUTYCYCLE_ON_HTL_TRANSITION)
				{
					pulseTimer->publicDataOutput = Rxbuffer[3];
				}
				else
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
				}
			}
			break;
        case CONFIGURE_CHANNEL_MODE_4:
        {
            pulseTimer->pulseTimeoutSetting = RXBUFFER16(3);
        }
        break;

		case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&pulseTimer->inputProcess);
			}
			break;
                    default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
	}


} 
pulseTimer_t* debugPulseTimer;
void updatePulseTimer()
{
	//  pulseIn_t* pulse = (pulseIn_t*) CurrentPinRegister;
	pulseTimer_t* pulseTimer = (pulseTimer_t*) CurrentPinRegister;
    debugPulseTimer = pulseTimer;
	uint8_t sample;

    if (pulseTimer->pulseTimeoutSetting > 0 )
    {
        if (pulseTimer->pulseTimeoutCounter < 65535)
        {
        ++ pulseTimer->pulseTimeoutCounter;
        }
        
        if (pulseTimer->publicDataOutput == FREQUENCY_ON_LTH_TRANSITION ||
              pulseTimer->publicDataOutput == FREQUENCY_ON_HTL_TRANSITION  )
        {
               if (pulseTimer->pulseTimeoutCounter > pulseTimer->pulseTimeoutSetting)
                            {
                                CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,0);
                            }
                           
        }
    }
	if (pulseTimer->units == 0)
	{
		sample =  PulseInGetOldestDMABit(CurrentPin);
	}
	else
	{
		sample = CurrentPinRead();
	}
	do
	{
		//mS timer, just read the pin every mS
		if (sample)
		{
			//Pin is high
			if (pulseTimer->readState)
			{
				//Last pin was high
				++pulseTimer->lastTimerTime;
			}
			else
			{
				//Last pin was low
				pulseTimer->PulseLowTime = pulseTimer->lastTimerTime;
	pulseTimer->lastTimerTime = 0;
				pulseTimer->readState = 1;
                		switch (pulseTimer->publicDataOutput)
				{
					case LOW_TIME:
						{
CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,COUNTS_TO_uS(pulseTimer->PulseLowTime));
						}
						break;


						

					case PERIOD_ON_LTH_TRANSITION:
						{
 uint32_t period = pulseTimer->PulseHighTime + pulseTimer->PulseLowTime;
period = COUNTS_TO_uS( period);
                            if (period > 65535)
                            {
                                period = 65535;
                            }
                            CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,period);
						}
						break;

					

					case FREQUENCY_ON_LTH_TRANSITION:
						{
uint32_t period = pulseTimer->PulseHighTime + pulseTimer->PulseLowTime;
                            
                            uint32_t freq = COUNTS_TO_Hz(period);
                            if (freq > 65535)
                            {
                                freq = 65535;
                            }

                            CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,(uint16_t)freq);
                            
						}
						break;


					case DUTYCYCLE_ON_LTH_TRANSITION:
						{
                            uint32_t period = pulseTimer->PulseHighTime + pulseTimer->PulseLowTime;
                            uint32_t duty = pulseTimer->PulseHighTime ;
                            duty <<=16;
                            duty /= period;
                            CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,duty);
						}
						break;
                        					case PULSE_COUNT:
case HIGH_TIME:
    case FREQUENCY_ON_HTL_TRANSITION:
    case PERIOD_ON_HTL_TRANSITION:
        case DUTYCYCLE_ON_HTL_TRANSITION:
                    default:
                    {
                    }
                    break;
				}
			}
		}
		else
		{
			//Pin is Low
			if (pulseTimer->readState)
			{

				pulseTimer->PulseHighTime =  pulseTimer->lastTimerTime;
				
/*
				{ //TODO MAKE FEATURE
					uint32_t period = COUNTS_TO_uS(pulseTimer->lastTimerTime);
					period += COUNTS_TO_uS(pulseTimer->PulseLowTime);
					uint32_t freq = 1000000/period;
					if (freq > 65535)
					{
						freq = 65535;
					}
					CurrentPinRegister->generic.buffer = freq;
				}
 * */
				pulseTimer->lastTimerTime = 0;
				pulseTimer->readState = 0;
				++pulseTimer->PulseCounter;
                pulseTimer->pulseTimeoutCounter = 0;
                	switch (pulseTimer->publicDataOutput)
				{
					case HIGH_TIME:
						{
                            CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,COUNTS_TO_uS( pulseTimer->PulseHighTime));
						}
						break;

					case PERIOD_ON_HTL_TRANSITION:
						{
                            uint32_t period = pulseTimer->PulseHighTime + pulseTimer->PulseLowTime;
                            
                            period = COUNTS_TO_uS( period);
                            if (period > 65535)
                            {
                                period = 65535;
                            }
                           CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,period);
						}
						break;

					case FREQUENCY_ON_HTL_TRANSITION:
						{
                            uint32_t period = pulseTimer->PulseHighTime + pulseTimer->PulseLowTime;
                            
                            uint32_t freq = COUNTS_TO_Hz(period);
                            if (freq > 65535)
                            {
                                freq = 65535;
                            }

                             CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,(uint16_t)freq);
                            
						}
						break;

					case DUTYCYCLE_ON_HTL_TRANSITION:
						{
                            uint32_t period = pulseTimer->PulseHighTime + pulseTimer->PulseLowTime;
                            uint32_t duty = pulseTimer->PulseHighTime ;
                            duty <<=16;
                            duty /= period;
                            CurrentPinRegister->generic.buffer = inputProcessProcess(&pulseTimer->inputProcess,duty);
						}
						break;
                        					case PULSE_COUNT:
                                            {
                                                CurrentPinRegister->generic.buffer = pulseTimer->PulseCounter;
                                            }
                                            break;
                                            
case LOW_TIME:
    case PERIOD_ON_LTH_TRANSITION:
        case DUTYCYCLE_ON_LTH_TRANSITION:
            					case FREQUENCY_ON_LTH_TRANSITION:
                    default:
                    {
                    }
                    break;
				}

			}
			else
			{
				//Last pin was low
				++pulseTimer->lastTimerTime;
			}
		}
		sample = PulseInGetOldestDMABit(CurrentPin);
	} while ( pulseTimer->units == 0 && sample != 2 );
}

