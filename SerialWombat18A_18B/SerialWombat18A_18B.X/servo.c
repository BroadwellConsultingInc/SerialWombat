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

/*! \file servo.c
 */
#include <stdint.h>
#include "serialWombat.h"
#include "outputScale.h"


typedef struct servo_n{
	uint16_t fixedPeriod; ///< The shortest possible pulse in uS 
	uint16_t variablePeriod; ///< The difference between the shortest possible pulse and the longest possible pulse in uS
	uint8_t inactiveCount; ///< How many 1ms Frames have 
    uint8_t waitingCount; ///< How long have we waited for frame to finish?
	uint8_t reverse; ///< 0:  Normal  1:  Subtract commanded value from 65535.
    uint8_t state;
    outputScale_t outputScale;
}servoPin_t;
#define  servo ((servoPin_t*) CurrentPinRegister)


typedef enum
{
   SERVO_STATE_WAITING = 0,
  SERVO_STATE_GENERATING_PULSE = 1,
}SERVO_STATE_t;

/// \brief  A simple, no-parameter call to initialize the Servo.  Used in ASCII pin configuration commands.
///
///  Initializes servo to 500-2500 uS pulse, not reversed.
void initServoHwSimple()
{
    BUILD_BUG_ON( sizeof(servoPin_t) >  BYTES_AVAIALABLE_OUTPUT_PULSE );
    CurrentPinRegister->generic.mode = PIN_MODE_SERVO;
    CurrentPinRegister->generic.buffer = 0;
    servo->fixedPeriod = 500 ;
    servo->variablePeriod = 2000 ;
    servo->reverse = 0;
    outputScaleInit(&servo->outputScale);
    CurrentPinLow();
}

/*!
    \brief Initialization routine for Servo.

----

CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Servo.  This command causes the pulse width to default to 500uS to 2500uS.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x03 (servo mode) |Pin To Set (Required for compatability with SW19)|Position Value Low Byte|Position Value High Byte|0x00 or 0x01 (Normal or Reverse)|0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 2 to Servo, Position 0x4080, no reverse

> `0xC0 0x02 0x03 0x02 0x80 0x40 0x00 0x55`

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Set Pulse widths.  This command must come after a servo CONFIGURE_CHANNEL_MODE_0 command for the same pin.  Units are microseconds


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set|0x03 (servo mode) |Fixed pulse time low byte| Fixed pulse time high byte | Variable pulse time low byte | variable pulse time high byte | 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 2  Servo Pulse width to range between 750 and 1750 uS.  
Fixed period is 750 = 0x02EE, variable period is (1750 - 750) = 1000 = 0x03E8

> `0xC1 0x02 0x03 0xEE 0x02 0xE8 0x03 0x55`


*/
void initServoHw (void)
{
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_SERVO)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
        case CONFIGURE_CHANNEL_MODE_0:
        {
            initServoHwSimple();
             CurrentPinRegister->generic.buffer = RXBUFFER16(4);
            servo->reverse = Rxbuffer[6];
            servo->state = SERVO_STATE_WAITING;
            timingResourceRelease(TIMING_RESOURCE_ALL);
            CurrentPinRegister->pulse_output.resource = TIMING_RESOURCE_NONE;
            CurrentPinLow();
              servo->waitingCount = 0;
       outputScaleInit(&servo->outputScale);
	}
	break;
	case CONFIGURE_CHANNEL_MODE_1:
        {
           
                servo->fixedPeriod =RXBUFFER16(3) ; 	
                servo->variablePeriod =RXBUFFER16(5) ;
        }        
	break;
    
        case CONFIGURE_CHANNEL_MODE_2:
        {
            CurrentPinRegister->generic.buffer = RXBUFFER16(3);
            outputScaleResetTimeout(&servo->outputScale);
        }
        break;
      
        case CONFIGURE_CHANNEL_MODE_10:
        {
            outputScaleCommProcess(&servo->outputScale);
        }
        break;
  default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
  }
}

/*!
\brief Periodic call to service the Servo State Machine for a pin

This function expects to get called every mS.  

On most calls increments inactiveCount and returns.

When inactive count >= 20 and the CCP1 compare register isn't busy (indicated by CCP1SetLowMask == 0xFF)
the function sets the output high, sets the CCP1SetLowMask variable to set the pin low when its port is &'d with
the CCP1SetLowMask, and calculates a time in the future based on the calculated pulse width + TMR1 reading.

When the interrupt goes off it and's the LAT register with CCP1SetLowMask, setting the value low again.

This algorithm assumes that only one pin is using the CCP1 at a time, which is enforced by the check for CCP1SetLowMask == 0xFF.

pulsetime = fixed time + variableTime * buffer / 65536.  

*/

void updateServoHw()
{   
    uint16_t driveValue;
    driveValue = outputScaleProcess(&servo->outputScale);
    if (servo->outputScale.sourcePin != CurrentPin)
    {
        CurrentPinRegister->generic.buffer = driveValue;
    }
	switch (servo->state)
	{
		case SERVO_STATE_WAITING:
			{
				servo->inactiveCount++;
                if (RunForeground)
                {
                    // We're running behind.  Wait a frame
                    return;
                }

				if (  servo->inactiveCount  >= 20) // && CCP1SetLowMask == 0xFF)
				{

					//	CCP1CON = 0x80; //Disable CCP1CON

					uint32_t period =  (uint32_t) driveValue;
					if (servo->reverse)
					{
						period = 65535 - period;
					}
					period *=   servo->variablePeriod;
					period >>= 16;
					period += servo->fixedPeriod;
                    uint8_t resource = timingResourceHighPulseClaim(TIMING_RESOURCE_ANY_HARDWARE);
                    
					if (resource != TIMING_RESOURCE_NONE)
					{
                        CurrentPinRegister->pulse_output.resource = resource;
						timingResourcesHighPulse(CurrentPinRegister->pulse_output.resource, period);
						servo->state = SERVO_STATE_GENERATING_PULSE;
                        servo->waitingCount = 0;						
					}
                    else if (servo->inactiveCount > 22)
                    {
                        // We've been waiting a long time for
                        // a hardware resource.  Settle for 
                        // dma based
                        timingResourceHighPulseClaim(TIMING_RESOURCE_PORT_DMA);
                        CurrentPinRegister->pulse_output.resource =TIMING_RESOURCE_PORT_DMA;
                        timingResourcesHighPulse(CurrentPinRegister->pulse_output.resource, period);                 
						servo->state = SERVO_STATE_GENERATING_PULSE;
                        servo->waitingCount = 0;
                    }
				}
			}

			break;

		case SERVO_STATE_GENERATING_PULSE:
			{
    
                timingResourceService(CurrentPinRegister->pulse_output.resource);
				if (!timingResourceHighPulseBusy(CurrentPinRegister->pulse_output.resource))
				{
                    CurrentPinLow();
					timingResourceRelease(TIMING_RESOURCE_ALL);
                    CurrentPinRegister->pulse_output.resource = TIMING_RESOURCE_NONE;
					servo->waitingCount = 0;
                    servo->inactiveCount = 0;
					servo->state = SERVO_STATE_WAITING;
				}

                else
                {
                    ++servo->waitingCount;
                    if (servo->waitingCount > 5)
                    {
                         CurrentPinLow();
					timingResourceRelease(TIMING_RESOURCE_ALL);
                    CurrentPinRegister->pulse_output.resource = TIMING_RESOURCE_NONE;
					servo->waitingCount = 0;
                    servo->inactiveCount = 0;
					servo->state = SERVO_STATE_WAITING;
                    }
                }
               
			}
			break;
	}

}

