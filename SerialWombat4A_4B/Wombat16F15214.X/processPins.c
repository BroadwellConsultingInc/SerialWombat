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

#include "serialWombat.h"

uint8_t CurrentPin;
uint8_t CurrentPinMask;
uint8_t CurrentPinMaskInverted;
uint8_t copy_IOC_PortBuffer[IOC_BUFFER_SIZE];
uint16_t copy_IOC_TimeBuffer[IOC_BUFFER_SIZE];

extern __bit CaptureIOCTime; 

void ProcessPins()
{
	extern uint8_t IOC_PortBuffer[IOC_BUFFER_SIZE]; // Note not marked volatile due to GIE disabled when accessed.
	INTERRUPT_GlobalInterruptDisable();
	copy_IOC_PortBuffer[0] = IOC_PortBuffer[0];
	copy_IOC_PortBuffer[1] = IOC_PortBuffer[1];   
	copy_IOC_PortBuffer[2] = IOC_PortBuffer[2];
	copy_IOC_PortBuffer[3] = IOC_PortBuffer[3];
	copy_IOC_PortBuffer[4] = IOC_PortBuffer[4];
	copy_IOC_PortBuffer[5] = IOC_PortBuffer[5];
	copy_IOC_PortBuffer[6] = IOC_PortBuffer[6];
	copy_IOC_PortBuffer[7] = IOC_PortBuffer[7];
	IOC_PortBuffer[1] = 0xFF;	
    IOC_PortBuffer[0] = 0xFF;
	IOC_PortBuffer[2] = 0xFF;
	IOC_PortBuffer[3] = 0xFF;
	IOC_PortBuffer[4] = 0xFF;
	IOC_PortBuffer[5] = 0xFF;
	IOC_PortBuffer[6] = 0xFF;
	IOC_PortBuffer[7] = 0xFF;
	if (CaptureIOCTime)
	{
        extern uint16_t IOC_TimeBuffer[IOC_BUFFER_SIZE];
	copy_IOC_TimeBuffer[0] = IOC_TimeBuffer[0];
	copy_IOC_TimeBuffer[1] = IOC_TimeBuffer[1];
	copy_IOC_TimeBuffer[2] = IOC_TimeBuffer[2];
	copy_IOC_TimeBuffer[3] = IOC_TimeBuffer[3];
	copy_IOC_TimeBuffer[4] = IOC_TimeBuffer[4];
	copy_IOC_TimeBuffer[5] = IOC_TimeBuffer[5];
	copy_IOC_TimeBuffer[6] = IOC_TimeBuffer[6];
	copy_IOC_TimeBuffer[7] = IOC_TimeBuffer[7];
	}

	INTERRUPT_GlobalInterruptEnable();

	//IO Processing
	for (CurrentPin = 0; CurrentPin <  NUMBER_OF_TOTAL_PINS; ++CurrentPin)
	{
		CopyFromArrayToPinBuffer();

		CurrentPinMask = PinMaskArray[CurrentPin];
		CurrentPinMaskInverted = ~CurrentPinMask;

		switch (CurrentPinRegister->generic.mode)
		{
			case PIN_MODE_DIGITAL_IO:
				{
					CurrentPinRegister->generic.buffer = CurrentPinRead();
				}
				break;

			case PIN_MODE_ANALOGINPUT:
				{
					void updateAnalogInput(void);
					updateAnalogInput();
				}
				break;

			case PIN_MODE_CONTROLLED:
				break;

			case PIN_MODE_SERVO:
				{
					void updateServo(void);           
					updateServo();
				}
				break;

			case PIN_MODE_PWM:
				{
					void updatePWM(void);
					updatePWM();
				}
				break;

			case PIN_MODE_DEBOUNCE:
				{
					void updateDebounce(void);
					updateDebounce();
				}
				break;

			case PIN_MODE_QUADRATURE_ENC:
				{
					void  update_quadEnc(void);
					update_quadEnc();
				}
				break;

			case PIN_MODE_WATCHDOG:
				{
					void updateWatchdog(void);
					updateWatchdog();
				}
				break; 
            
            case PIN_MODE_PULSE_TIMER:
            {
                void updatePulseTimer(void);
                updatePulseTimer();
            }
            break;
            case PIN_MODE_PROTECTEDOUTPUT:
            {
                void updateProtectedOutput(void);
                updateProtectedOutput();
            }
            break;
		}    
		CopyFromPinBufferToArray();
	}
}

