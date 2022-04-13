/*
Copyright 2021 Broadwell Consulting Inc.

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

/*! \file hfservo.c
 */
#include <stdint.h>
#include "serialWombat.h"
#include "outputScale.h"


typedef struct hfServo_n{
    outputScale_t outputScale;
	uint16_t fixedPeriod; ///< The shortest possible pulse in uS 
	uint16_t variablePeriod; ///< The difference between the shortest possible pulse and the longest possible pulse in uS
	uint8_t reverse; ///< 0:  Normal  1:  Subtract commanded value from 65535.
	uint16_t period;
	uint8_t resource;
}hfServo_t;
#define  servo ((hfServo_t*) CurrentPinRegister)

#define DUTY_CYCLE ((((uint32_t)CurrentPinRegister->generic.buffer * servo->variablePeriod)  + (((uint32_t)servo->fixedPeriod) <<16)) / (servo->period))


/*!
    \brief Initialization routine for Servo.

----

CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Servo.  This command causes the pulse width to default to 500uS to 2500uS.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x1A (hf servo mode) |Pin To Set (Required for compatability with SW19)|Position Value Low Byte|Position Value High Byte|0x00 or 0x01 (Normal or Reverse)|0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 2 to Servo, Position 0x4080, no reverse

> `0xC0 0x02 0x16 0x02 0x80 0x40 0x00 0x55`

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Set Pulse widths.  This command must come after a servo CONFIGURE_CHANNEL_MODE_0 command for the same pin.  Units are microseconds


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set|0x1A (hf servo mode) |Fixed pulse time low byte| Fixed pulse time high byte | Variable pulse time low byte | variable pulse time high byte | 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 2  Servo Pulse width to range between 750 and 1750 uS.  
Fixed period is 750 = 0x02EE, variable period is (1750 - 750) = 1000 = 0x03E8

> `0xC1 0x02 0x16 0xEE 0x02 0xE8 0x03 0x55`


*/
void initHfServo (void)
{
	BUILD_BUG_ON( sizeof(hfServo_t) >  BYTES_AVAIALABLE_OUTPUT_PULSE );
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_HF_SERVO)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				timingResourceRelease(TIMING_RESOURCE_ALL);
				uint8_t resource =timingResourcePWMClaim(TIMING_RESOURCE_ANY_HARDWARE,2000);
				if (resource == TIMING_RESOURCE_NONE)
				{
					error (SW_ERROR_HW_RESOURCE_IN_USE );
					return;
				}
				servo->resource = resource;
				CurrentPinRegister->generic.mode = PIN_MODE_HF_SERVO;
				CurrentPinRegister->generic.buffer = 0;
				servo->fixedPeriod = 500 ;
				servo->variablePeriod = 2000 ;
				servo->reverse = 0;
				servo->period = 0;
				outputScaleInit(&servo->outputScale);
				CurrentPinLow();
				CurrentPinRegister->generic.buffer = RXBUFFER16(4);
				servo->reverse = Rxbuffer[6];

				CurrentPinRegister->pulse_output.resource = TIMING_RESOURCE_NONE;
				CurrentPinLow();
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
		case CONFIGURE_CHANNEL_MODE_3:
			{
				servo->period = RXBUFFER16(3);
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


void updateHfServo()
{   

    CurrentPinRegister->generic.buffer = outputScaleProcess(&servo->outputScale);
    if (servo->period > 0)
    {
	timingResourcePWM(servo->resource,servo->period, DUTY_CYCLE);
    }

}

