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

typedef enum
{
 TRANSFORM_TYPE_DIRECT = 0,
 TRANSFORM_TYPE_LINEAR = 1,
}transformType_t;

typedef struct linear_n
{
	int32_t offset;
	int32_t scalar;
}linear_t;

typedef struct lookup2D_n
{
	uint16_t tableAddress;
}lookup2D_t;


typedef struct servo_n
{
	uint16_t fixedPeriod;
	uint16_t variablePeriod;
	uint16_t inactivePeriod;
	uint8_t reverse;
	uint8_t invertPolarity; 

}servo_t;


typedef struct pulseOut_n{
	union{
		uint8_t transformDataBytes[8];
		linear_t linear;
		lookup2D_t lookup2D;
	}transformData;
	uint16_t sampleTime;
	uint16_t sampleCounter;
	union{
	uint16_t swpwmPeriod;
	servo_t servo;
 	}modeSpecific;
	uint8_t commandPin;
	uint8_t transformType;
}pulseOut_t;

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



void initPulseOut (void)
{
	pulseOut_t* pulse = (pulseOut_t*) CurrentPinRegister;
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
		{
			pulse->commandPin = Rxbuffer[3];
			CurrentPinRegister->generic.buffer = RXBUFFER16(4);
			pulse->transformType = TRANSFORM_TYPE_DIRECT;

			CurrentPinRegister->generic.mode = Rxbuffer[2];

			switch(CurrentPinRegister->generic.mode)
			{	case PIN_MODE_PWM:
				{
					pulse->modeSpecific.swpwmPeriod = 58;//RXBUFFER16(6);
					CurrentPinRegister->pulse_output.highReload = (((uint32_t) CurrentPinRegister->generic.buffer * pulse->modeSpecific.swpwmPeriod) >> 16);
					CurrentPinRegister->pulse_output.lowReload = pulse->modeSpecific.swpwmPeriod - CurrentPinRegister->pulse_output.highReload;
					PinLow(CurrentPin); //TODO make generic output, place after updatePulse
					updatePulseOutput(CurrentPin);

				}
				break;

				case PIN_MODE_SERVO:
				{
					pulse->modeSpecific.servo.fixedPeriod = (uint16_t) (.0005 * DMA_FREQUENCY + 0.5); 	//500us
					pulse->modeSpecific.servo.variablePeriod =(uint16_t)(.002 * DMA_FREQUENCY + 0.5);	//2000us
					pulse->modeSpecific.servo.inactivePeriod = (uint16_t)(.018 * DMA_FREQUENCY);	//18 ms between pulses
					pulse->modeSpecific.servo.reverse = Rxbuffer[6] > 0;
					pulse->modeSpecific.servo.invertPolarity= 0;
					PinLow(CurrentPin); //TODO make generic output
				}
				break;
                case PIN_MODE_DMA_PULSE_OUTPUT:
				{
					
					CurrentPinRegister->pulse_output.highReload = RXBUFFER16(3);
					CurrentPinRegister->pulse_output.lowReload = RXBUFFER16(5);
					PinLow(CurrentPin); //TODO make generic output, place after updatePulse
					updatePulseOutput(CurrentPin);

				}
				break;
			}
		}
			break;
		case CONFIGURE_CHANNEL_MODE_1:
		{
			switch(CurrentPinRegister->generic.mode)
			{
				case PIN_MODE_SERVO:
				{
					pulse->modeSpecific.servo.fixedPeriod = (((uint32_t)RXBUFFER16(3)) * DMA_FREQUENCY) / 1000000 ; 
					pulse->modeSpecific.servo.variablePeriod =(((uint32_t)RXBUFFER16(5)) * DMA_FREQUENCY) / 1000000;
				}
				break;
				
			}
		}
		break;
		case CONFIGURE_CHANNEL_MODE_2:
		{
			switch(CurrentPinRegister->generic.mode)
			{
				case PIN_MODE_SERVO:
				{
					pulse->modeSpecific.servo.inactivePeriod = RXBUFFER16(3);
					pulse->modeSpecific.servo.invertPolarity= Rxbuffer[5];
				}
				break;
			}
		}
		break;
        
        case CONFIGURE_CHANNEL_MODE_HW_0:
		{
            switch(CurrentPinRegister->generic.mode)
			{
                case PIN_MODE_PWM:
				{
					pulse->modeSpecific.swpwmPeriod = (((uint32_t)RXBUFFER16(3)) * DMA_FREQUENCY) / 1000000 ; 
					CurrentPinRegister->pulse_output.highReload = (((uint32_t) CurrentPinRegister->generic.buffer * pulse->modeSpecific.swpwmPeriod) >> 16);
					CurrentPinRegister->pulse_output.lowReload = pulse->modeSpecific.swpwmPeriod - CurrentPinRegister->pulse_output.highReload;
					updatePulseOutput(CurrentPin);

				}
				break;
            }
            
        }
        break;
	}
}

void updatePulseOut(void)
{
	pulseOut_t* pulse = (pulseOut_t*) CurrentPinRegister;
	if (pulse->commandPin == 255)
	{
		return;
	}
	if (pulse->sampleCounter < pulse->sampleTime)
	{
		++pulse->sampleCounter;
	}
	else
	{
		uint32_t temp32;
		pulse->sampleCounter = 0;
		temp32 = GetBuffer(pulse->commandPin);
		/*		temp32 *= tp->pwm_follow_direct.scalar;
				temp32 >>=8;
				int32_t stemp32 = temp32;
				stemp32 += tp->pwm_follow_direct.offset;
				if (stemp32 > 65535)
				{
				stemp32 = 65535;
				}
				else if (stemp32 < 0)
				{
				stemp32 = 0;
				}
				*/
		switch (CurrentPinRegister->generic.mode)
		{
			case PIN_MODE_PWM:
				{
					if (temp32 == 0xFFFF)
					{
						CurrentPinRegister->pulse_output.highReload = pulse->modeSpecific.swpwmPeriod;
						CurrentPinRegister->pulse_output.lowReload = 0;                
					}
					else
					{
						CurrentPinRegister->pulse_output.highReload = (((uint32_t) temp32 * pulse->modeSpecific.swpwmPeriod) >> 16);
						CurrentPinRegister->pulse_output.lowReload = pulse->modeSpecific.swpwmPeriod - CurrentPinRegister->pulse_output.highReload;
					}
				}
				break;
			case PIN_MODE_SERVO:
				{
					if (pulse->modeSpecific.servo.reverse)
					{
						temp32 = 0xFFFF - temp32;
					}


					temp32 = ((uint32_t)temp32) * pulse->modeSpecific.servo.variablePeriod;
					temp32 += ((uint32_t)pulse->modeSpecific.servo.fixedPeriod) << 16;



					if (pulse->modeSpecific.servo.invertPolarity)
					{	     
						CurrentPinRegister->pulse_output.lowReload = temp32 >>16;
						CurrentPinRegister->pulse_output.highReload = pulse->modeSpecific.servo.inactivePeriod;
					}
					else
					{
						CurrentPinRegister->pulse_output.highReload = temp32 >>16;
						CurrentPinRegister->pulse_output.lowReload = pulse->modeSpecific.servo.inactivePeriod;

					}
				}
				break;
                
            case PIN_MODE_DMA_PULSE_OUTPUT:
                break;
		}
		//		else if (tp->generic.mode == PIN_MODE_ANALOG_OUT_FOLLOW)
		//		{
		//			CVRCON = 0x00C0 | (((uint16_t)stemp32) >> 11);
		//		}

	}

	switch (CurrentPinRegister->generic.mode)
	{
		case PIN_MODE_PWM:
		case PIN_MODE_SERVO:
        case PIN_MODE_DMA_PULSE_OUTPUT:
			updatePulseOutput(CurrentPin);
			break;
	}
}
/*
void initPWMSimple(uint8_t pin)
{
	pinRegister_t* pr = &PinUpdateRegisters[pin];
	pulseOut_t* pulse = (pulseOut_t*) pr;
	pulse->commandPin = pin;
	pulse->transformType = TRANSFORM_TYPE_DIRECT;

	pr->generic.mode = PIN_MODE_PWM;

	pulse->modeSpecific.swpwmPeriod = 256;
	pr->pulse_output.highReload = (((uint32_t) pr->generic.buffer * pulse->modeSpecific.swpwmPeriod) >> 16);
	pr->pulse_output.lowReload = pulse->modeSpecific.swpwmPeriod - pr->pulse_output.highReload;
	PinLow(pin); //TODO make generic output, place after updatePulse
	updatePulseOutput(pin);
}
 */

void initServoSimple(uint8_t pin)
{
	pinRegister_t* pr = &PinUpdateRegisters[pin];
	pulseOut_t* pulse = (pulseOut_t*) pr;
	pulse->commandPin = pin;
	pulse->transformType = TRANSFORM_TYPE_DIRECT;

	pr->generic.mode = PIN_MODE_SERVO;
	pulse->modeSpecific.servo.fixedPeriod = (uint16_t) (.0005 * DMA_FREQUENCY); 	//500us
	pulse->modeSpecific.servo.variablePeriod =(uint16_t)(.002 * DMA_FREQUENCY);	//2000us
	pulse->modeSpecific.servo.inactivePeriod = (uint16_t)(.018 * DMA_FREQUENCY);	//18 ms between pulses
	pulse->modeSpecific.servo.reverse = 0;
	pulse->modeSpecific.servo.invertPolarity= 0;

	PinLow(pin); //TODO make generic output, place after updatePulse
}

