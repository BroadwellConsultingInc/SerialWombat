/*
Copyright 2020 Broadwell Consulting Inc.

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

#include <stdint.h>
#include "serialWombat.h"


typedef struct watchdog_n{
	uint8_t timeoutPinState; 
    uint8_t defaultPinState;
    uint8_t defaultPinValues;
	uint16_t delayBeforeSerialWombatReset;
	uint8_t resetAfterTimeout:1;
	uint8_t setPinsToDefault:1;

	
}watchdog_t;

#define watchdog ((watchdog_t*) CurrentPinRegister)
void initWatchdog()
{

	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
		{
            watchdog->defaultPinState = Rxbuffer[3];
			SetCurrentPin(Rxbuffer[3]);
			watchdog->timeoutPinState = Rxbuffer[4];
			CurrentPinRegister->generic.mode = PIN_MODE_WATCHDOG;
			CurrentPinRegister->generic.buffer = RXBUFFER16(5);
			watchdog->resetAfterTimeout = Rxbuffer[7];
			watchdog->delayBeforeSerialWombatReset = 10;

		}
		break;
		case CONFIGURE_CHANNEL_MODE_1:
		{
			watchdog->setPinsToDefault = Rxbuffer[3];
			watchdog->defaultPinValues = Rxbuffer[4];
			watchdog->delayBeforeSerialWombatReset = RXBUFFER16(5);
		}
		break;
	}
}


void updateWatchdog()
{ 

	if (CurrentPinRegister->generic.buffer > 0)
	{
		-- CurrentPinRegister->generic.buffer;
        if (CurrentPinRegister->generic.buffer == 0)
        {
        SetCurrentPin(watchdog->timeoutPinState);
        if (watchdog->setPinsToDefault)
				{
#ifdef UARTWOMBAT
					WP0_PPS = 0;
#endif
					WP1_PPS = 0;
					WP2_PPS = 0;
					WP3_PPS = 0;
                    WP_ANSEL = 0;
                    WP_WPU = 0;
					uint8_t i;
					for (i = 0; i < NUMBER_OF_TOTAL_PINS; ++i)
					{
						SetMode(i, PIN_MODE_CONTROLLED);
						SetPin(i,watchdog->defaultPinValues & 0x03);
						watchdog->defaultPinValues >>= 2;
					}
				}
        }
	}
	else
	{
        
		if ( watchdog->delayBeforeSerialWombatReset > 0)
		{
			-- watchdog->delayBeforeSerialWombatReset;
		}
		else
		{
			
			if (watchdog->resetAfterTimeout)
			{
				RESET();
			}
            else
            {
                SetCurrentPin(watchdog->defaultPinState);
            }
		}	
	}
}

