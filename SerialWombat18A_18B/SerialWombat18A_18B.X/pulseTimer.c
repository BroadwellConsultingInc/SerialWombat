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
#include <stdint.h>

typedef struct pulseTimer_n{
	uint8_t readState:1;
	uint8_t units: 1; // 0 = uS, 1 = mS
	uint16_t PulseCounter;
	uint16_t PulseLowTime;
	uint16_t lastTimerTime;
}pulseTimer_t;

#define COUNTS_TO_uS(_a) ((uint16_t)((uint32_t)( _a * (65536.0 * 1000000 / 57600 + .5)) >> 16))

void initPulseTimer()
{
//	pulseIn_t* pulse = (pulseIn_t*) CurrentPinRegister;
	pulseTimer_t* pulseTimer = (pulseTimer_t*) CurrentPinRegister;

	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:

			{
				pulseTimer->units = Rxbuffer[4];
				CurrentPinRegister->generic.mode =PIN_MODE_PULSE_TIMER;
				CurrentPinRegister->generic.buffer = 0; 
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
				/*
				if (!pulseTimer->units)
				{
					CaptureIOCTime = 1;
					PIE0bits.IOCIE = 1;
				     WP_IOCN |= CurrentPinMask;
				     WP_IOCP |= CurrentPinMask;
				}
				*/

			}
			break;

            case CONFIGURE_CHANNEL_MODE_1:
	    {
                if (pulseTimer->units)
                {
                TXBUFFER16(3,CurrentPinRegister->generic.buffer);
             }
             else
             {
                 TXBUFFER16(3,COUNTS_TO_uS(CurrentPinRegister->generic.buffer));
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
             
	}       
} 

void updatePulseTimer()
{
  //  pulseIn_t* pulse = (pulseIn_t*) CurrentPinRegister;
	pulseTimer_t* pulseTimer = (pulseTimer_t*) CurrentPinRegister;
    uint8_t sample;
    
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
			}
		}
		else
		{
			//Pin is Low
			if (pulseTimer->readState)
			{
				//Last pin was high
				CurrentPinRegister->generic.buffer =  pulseTimer->lastTimerTime;
				 pulseTimer->lastTimerTime = 0;
				pulseTimer->readState = 0;
				++pulseTimer->PulseCounter;
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

