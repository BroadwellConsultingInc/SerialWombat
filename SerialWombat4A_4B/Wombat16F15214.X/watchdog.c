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


/*! \file quadEnc.c
 
  This file contains the Watchdog pin mode for the Serial Wombat 4A and 4B
 */

#include <stdint.h>
#include "serialWombat.h"
/*! \file watchdog.c
*/

typedef struct watchdog_n{
	uint8_t timeoutPinState; ///<   0:Low 1:High 2:Input
	uint8_t defaultPinState; ///<   0:Low 1:High 2:Input
	uint8_t defaultPinValues; ///<   Misnamed.  Should be timeoutPin values.  An 8 bit field which sets all pins to state .  2 LSBs are pin 0
	uint16_t delayBeforeSerialWombatReset; ///< How long to stay in timeout state before resetting wombat if enabled. 
	uint8_t resetAfterTimeout:1;  ///< 1: Reset Wombat after timeout and delayBeforeSerialWombatReset.  0:  Don't reset.
	uint8_t setPinsToDefault:1; ///< 1:  Set all 4 pins to timeout values on timeout   0:  Only set this pin to it's timeoutPinState
}watchdog_t;

#define watchdog ((watchdog_t*) CurrentPinRegister)

/*!  \brief Initialization routine for Watchdog pin mode

----

Retrevial of Time remaining until timeout
-------------------------------

Configure the Watchdog pin mode using the CONFIGURE_CHANNEL_MODE_0 command before reading values.  
The Watchdog time remaining value is stored in the Pin's 16-bit Public data area.  Use the Read Pin Buffer command to retreive it.  Units are mS.


-----

Resetting the Watchdog Time
---------------------------
Either reconfigure the Watchdog using CONFIGURE_CHANNEL_MODE_0 and CONFIGURE_CHANNEL_MODE_1 before it times out, or write a new value to its public data representing mS until timeout.


----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Watchdog.  This command needs to be followed by CONFIGURE_CHANNEL_MODE_1 for reliable operation.



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x07 (Watchdog) | Non-Timeout Pin State (0 = Low, 1 = High, 2 = Input) | Timeout Pin State (0 = Low, 1 = High, 2 = Input) |mS Until Timeout low byte) |mS Until Timeout high byte |0: No Self-Reset on Timeout 1: Serial Wombat Self-Resets on Timeout|


Response:

Command is echoed back.

Examples:

Set pins 1 to be an input as Non-Timeout state, and Low on timeout, and reset the Serial Wombat as well, timeout 30 seconds (30000 mS = 0x7530).

(This is a typical configuration when using the Serial Wombat for as a watchdog for its host).

> `0xC0 0x01 0x07 0x02 0x00 0x30 0x75 0x01 `

----


CONFIGURE_CHANNEL_MODE_1:
---------------------
Determine if Watchdog sets all pins to default states, or just the pin assigned the Watchdog State Machine.  
Set time in mS that the Wombat stays in timeout state before self-resetting, if enabled.  This pin will be returned to the non-timeout state at the end of this period.
Set this time to 0xFFFF to stay in timeout state forever after a timeout until commanded differently by the host.

The Other pin timeout state settings exist as a bitfield, and override the  Timeout Pin State from CONFIGURE_CHANNEL_MODE_0.



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set|0x07 (Watchdog) | 0: Use Timeout Pin State on timeout for this pin   1:  Set all 4 pins based on bitfield |  Other Pins Bitfield (see below) | mS to wait before Self Reset low byte |mS to wait before Self Reset high byte | 0x55* |

\*0x55 is recommended, but any byte is acceptable

Other pin bitfield is calculated as follows:

(Pin 0 Setting (0,1 2)) + (Pin 1 Setting (0,1 or 2) * 4 + (Pin 2 Setting (0,1 or 2) * 16 + ( Pin 3 Setting (0,1 or 2) * 64)

Response:

Command is echoed back.

Examples:

Set pin 1 to use the all-pins bitfield, Pin 0 = Input, Pin 1 = Low, Pin 2 = Input, Pin 3 = Input, Self-Reset delay of 100 mS = 0x0064


Bitfield = 2 + 0 * 4 + 2 * 16 + 2 * 64 = 162 = 0xA2

> `0xC1 0x01 0x07 0x01 0xA2 0x64 0x00 0x55 `

*/
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
                watchdog->setPinsToDefault = 0;

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


/*!
\brief Periodic call to service the Analog Input State Machine for a pin

This function expects to get called every mS.  
*/
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
				// Disable any hardware driving the pins by making sure the Pin select is set to GPIO.
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
            if (watchdog->delayBeforeSerialWombatReset != 0xFFFF)
            {
			-- watchdog->delayBeforeSerialWombatReset;
            }
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

