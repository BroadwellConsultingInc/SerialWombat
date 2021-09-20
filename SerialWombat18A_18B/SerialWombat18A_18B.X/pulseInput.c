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


void initPulseTimer()
{
	pulseOut_t* pulse = (pulseIn_t*) CurrentPinRegister;
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
                TXBUFFER16(3,CurrentPinRegister->generic.buffer);
                Txbuffer[7] = (uint8_t)pulseTimer->PulseCounter;  
                TXBUFFER16(5,pulseTimer->PulseLowTime );
            }
            break;
          
             case CONFIGURE_CHANNEL_MODE_2:
 	    {
                extern __bit IOC_Overflow ;
                TXBUFFER16(3,CurrentPinRegister->generic.buffer);
                Txbuffer[7] = 0; //IOC_Overflow;  
                TXBUFFER16(5,pulseTimer->PulseCounter );
//                IOC_Overflow = 0;
            }
            break;
             
	}       
} 

void updatePulseTimer()
{

	if (pulseTimer->units)
	{
		//mS timer, just read the pin every mS
		if (CurrentPinRead())
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

	}
	else
	{
		for (uint8_t i = 0; i != IOC_BUFFER_SIZE; ++i)
		{
			uint8_t currentInput;
			currentInput = copy_IOC_PortBuffer[i];
			if (currentInput & 0x80u)
			{
				//Not set.
				continue;
			}
			if (pulseTimer->readState)
			{
				if (copy_IOC_PortBuffer[i] & CurrentPinMask)
				{
					//Do nothing
				}
				else
				{
					pulseTimer->readState = 0;				
					CurrentPinRegister->generic.buffer =
						copy_IOC_TimeBuffer[i] - pulseTimer->lastTimerTime;
					pulseTimer->lastTimerTime = copy_IOC_TimeBuffer[i];
					++pulseTimer->PulseCounter; 
				}
			}
			else
			{
				if (copy_IOC_PortBuffer[i] & CurrentPinMask)
				{
					//Do nothing
					pulseTimer->readState = 1;
					pulseTimer->PulseLowTime = 
						copy_IOC_TimeBuffer[i] - pulseTimer->lastTimerTime;
					pulseTimer->lastTimerTime = copy_IOC_TimeBuffer[i];
				}

			}
		}
	}
}


#if 0
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
			uint16_t sampleCounter = 0;

			CurrentPinRegister->generic.mode = Rxbuffer[2];

			switch(CurrentPinRegister->generic.mode)
			{	case PIN_MODE_PWM:
				{
					pulse->modeSpecific.swpwmPeriod = 58;//RXBUFFER16(6);
					CurrentPinRegister->pulse_output.highReload = (((uint32_t) CurrentPinRegister->generic.buffer * pulse->modeSpecific.swpwmPeriod) >> 16);
					CurrentPinRegister->pulse_output.lowReload = pulse->modeSpecific.swpwmPeriod - CurrentPinRegister->pulse_output.highReload;
					PinLow(CurrentPin); //TODO make generic output, place after updatePulse
					updatePulse(CurrentPin);

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
				case PIN_MODE_PWM:
				{
					pulse->modeSpecific.swpwmPeriod = (((uint32_t)RXBUFFER16(3)) * DMA_FREQUENCY) / 1000000 ; 
					CurrentPinRegister->pulse_output.highReload = (((uint32_t) CurrentPinRegister->generic.buffer * pulse->modeSpecific.swpwmPeriod) >> 16);
					CurrentPinRegister->pulse_output.lowReload = pulse->modeSpecific.swpwmPeriod - CurrentPinRegister->pulse_output.highReload;
					updatePulse(CurrentPin);

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
			updatePulse(CurrentPin);
			break;
	}
}

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
	updatePulse(pin);
}

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
#endif
