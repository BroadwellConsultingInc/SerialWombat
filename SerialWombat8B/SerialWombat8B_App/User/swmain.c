/*
Copyright 2025 Broadwell Consulting Inc.

Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:

 Serial Wombat is a registered trademark in the United States of Broadwell Consulting Inc.
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
#include <stdbool.h>
#include <string.h>
#include "serialWombat.h"
#include "debug.h"

uint8_t CurrentPin;

uint8_t FrameTimingPin = 0xFF;

 volatile bool RunForeground = false;


uint8_t UserBuffer[SIZE_OF_USER_BUFFER];



// PASTE INITIALIZATION ARRAY BELOW HERE



// PASTE INITIALZIATION ARRAY ABOVE HERE

void reset ()
{
    #ifdef __DEBUG    
        //TODO  future internal debugging feature: shut down peripherals, shut off interrupts, jump to reset vector ?
#else
    NVIC_SystemReset();
    return;
	while (1)
	{           
//TODO		{ __asm__ volatile (" reset");  }
	}
#endif
}
uint16_t OverflowFrames = 0;
uint32_t FramesRun = 0;
uint16_t SystemUtilizationAverage = 0x8000;
uint16_t SystemUtilizationCount = 0;
uint32_t SystemUtilizationSum = 0;


void swSetup(void)
{

	// initialize the device
    memset(UserBuffer,0, sizeof(UserBuffer));
    memset(PinUpdateRegisters,0,sizeof(PinUpdateRegisters));

    void systemInitDMAIO(void);
    systemInitDMAIO();


    {void protocolInitPinsToDIO_Input(void);
   protocolInitPinsToDIO_Input();
    }

}



void swLoop()
    
 	{
		ProcessRx();

		if (RunForeground)
		{
           // PinHigh(FrameTimingPin);

			RunForeground = false;
            ++FramesRun;
			ProcessPins();

            if (RunForeground)
			{
					++OverflowFrames;
			}
            else
            {
                uint32_t t = SysTick->CNT;
                SystemUtilizationSum += t;
                ++SystemUtilizationCount;
                if (SystemUtilizationCount == 1024)
                {
                    SystemUtilizationSum <<= 6;
                    SystemUtilizationSum/= SysTick->CMP;
                    SystemUtilizationAverage = SystemUtilizationSum;
                    SystemUtilizationCount = 0;
                    SystemUtilizationSum = 0;
                }
            }
		}
	}


void ProcessPins()
{
	for (CurrentPin = 0; CurrentPin <  NUMBER_OF_TOTAL_PINS; ++CurrentPin)
	{
		CurrentPinRegister = &PinUpdateRegisters[CurrentPin];

		switch (CurrentPinRegister->generic.mode)
		{
			case PIN_MODE_DIGITAL_IO:
				{
					void updateDigitalIO(void);
				 //TODO needs tested   updateDigitalIO();
				}
				break;
#ifdef PIN_MODE_SERVO_ENABLE
			case PIN_MODE_SERVO:
				{
					void updateServoHw(void);
					updateServoHw();
				}
				break;
#endif


#ifdef PIN_MODE_PWM_ENABLE
			case PIN_MODE_PWM:
				{
					void updatePWM(void);
					updatePWM();
				}
				break;
#endif
#ifdef PIN_MODE_QUADRATURE_ENC_ENABLE
			case PIN_MODE_QUADRATURE_ENC:
				{
					void updateQuadEnc(void);
					updateQuadEnc();
				}
				break;
#endif
#ifdef PIN_MODE_ANALOGINPUT_ENABLE
			case PIN_MODE_ANALOGINPUT:
				{
					void updateAnalogInput(void);
					updateAnalogInput();
				}
				break;
#endif





#ifdef PIN_MODE_DEBOUNCE_ENABLE
			case PIN_MODE_DEBOUNCE:
				{
					void updateDebounce(void);
					updateDebounce();
				}
				break;
#endif

#ifdef PIN_MODE_SW_UART_ENABLE
			case PIN_MODE_SW_UART:
				{
					extern void updateUARTSw(void);
					updateUARTSw();
				}
				break;
#endif
#ifdef PIN_MODE_MATRIX_KEYPAD_ENABLE
			case PIN_MODE_MATRIX_KEYPAD:
				{
					void updateMatrixKeypad(void);
					updateMatrixKeypad();
				}
				break;
#endif


#ifdef PIN_MODE_HBRIDGE_ENABLE
			case PIN_MODE_HBRIDGE:
				{
					void updatehBridge(void);
					updatehBridge();
				}
				break;
#endif

#ifdef PIN_MODE_TM1637_ENABLE
			case PIN_MODE_TM1637:
				{
					extern void updateTM1637();
					updateTM1637();
				}
				break;
#endif


			case PIN_MODE_CONTROLLED:
			case PIN_MODE_FRAME_TIMER:
				break;


#ifdef PIN_MODE_HF_SERVO_ENABLE
			case PIN_MODE_HF_SERVO:
				{
					void updateHfServo(void);
					updateHfServo();
				}
				break;
#endif


#ifdef PIN_MODE_WATCHDOG_ENABLE
			case PIN_MODE_WATCHDOG:
				{
					void updateWatchdog(void);
					updateWatchdog();
				}
				break;
#endif         


#ifdef PIN_MODE_PULSE_TIMER_ENABLE
			case PIN_MODE_PULSE_TIMER:
				{
					void updatePulseTimer(void);
					updatePulseTimer();
				}
				break;
#endif
#ifdef PIN_MODE_ULTRASONIC_DISTANCE_ENABLE
			case PIN_MODE_ULTRASONIC_DISTANCE:
				{
					void updateUltrasonicDistance(void);
					updateUltrasonicDistance();
				}
				break;
#endif
#ifdef PIN_MODE_INPUT_PROCESSOR_ENABLE
			case PIN_MODE_INPUT_PROCESSOR:
				{
					void updatePinInputProcessor(void);
					updatePinInputProcessor();
				}
				break;
#endif




#ifdef PIN_MODE_PROTECTEDOUTPUT_ENABLE
			case PIN_MODE_PROTECTEDOUTPUT:
				{
					extern void updateProtectedOutput();
					updateProtectedOutput();
				}
				break;
#endif


#ifdef PIN_MODE_WS2812_ENABLE
			case PIN_MODE_WS2812:
				{
					extern void updateWS2812();
					updateWS2812();
				}
				break;
#endif
#ifdef PIN_MODE_TOUCH_ENABLE
			case PIN_MODE_TOUCH:
				{
					extern void updateTouch();
					updateTouch();
				}
				break;
#endif

#ifdef PIN_MODE_RESISTANCE_INPUT_ENABLE
			case PIN_MODE_RESISTANCE_INPUT:
				{
					extern void updateResistanceInput(void);
					updateResistanceInput();
				}
				break;
#endif
#ifdef PIN_MODE_THROUGHPUT_CONSUMER_ENABLE
			case PIN_MODE_THROUGHPUT_CONSUMER:
				{
					void updateThroughputConsumer();
					updateThroughputConsumer();
				}
				break;
#endif

#ifdef PIN_MODE_PULSE_ON_CHANGE_ENABLE
			case PIN_MODE_PULSE_ON_CHANGE:
				{
					void updatePulseOnChange(void);
					updatePulseOnChange();
				}
				break;
#endif
#ifdef PIN_MODE_LIQUID_CRYSTAL_ENABLE
			case PIN_MODE_LIQUID_CRYSTAL:
				{
					void updateLiquidCrystal(void);
					updateLiquidCrystal();
				}
				break;
#endif

#ifdef PIN_MODE_UART_ENABLE
			case PIN_MODE_UART0_TXRX:
			case PIN_MODE_UART1_TXRX:
				{
					extern void updateUARTHw(void);
					updateUARTHw();
				}
				break;
#endif

#ifdef PIN_MODE_HS_CLOCK_ENABLE
			case PIN_MODE_HS_CLOCK:
				{
					extern void updateHSClock();
					updateHSClock();
				}
				break;
#endif

#ifdef PIN_MODE_HS_COUNTER_ENABLE
			case PIN_MODE_HS_COUNTER:
				{
					extern void updateHSCounter();
					updateHSCounter();
				}
				break;
#endif

#ifdef PIN_MODE_VGA_ENABLE
			case PIN_MODE_VGA:
				{
					extern void updateVGA();
					updateVGA();
				}
				break;
#endif
#ifdef PIN_MODE_PS2_KEYBOARD_ENABLE
			case PIN_MODE_PS2_KEYBOARD:
				{
					extern void updatePS2Keyboard();
					updatePS2Keyboard();
				}
				break;
#endif

#ifdef PIN_MODE_I2C_CONTROLLER_ENABLE
			case PIN_MODE_I2C_CONTROLLER:
				{
					extern void updateI2CController();
					updateI2CController();
				}
				break;
#endif

#ifdef PIN_MODE_QUEUED_PULSE_OUTPUT_ENABLE
			case PIN_MODE_QUEUED_PULSE_OUTPUT:
				{
					extern void updateQueuedPulseOutput(void);
					updateQueuedPulseOutput();
				}
				break;
#endif

#ifdef PIN_MODE_FREQUENCY_OUTPUT_ENABLE
			case PIN_MODE_FREQUENCY_OUTPUT:
				{
					extern void updateFrequencyOutput(void);
					updateFrequencyOutput();
				}
				break;
#endif

#ifdef PIN_MODE_MAX7219MATRIX_ENABLE
			case PIN_MODE_MAX7219MATRIX:
				{
					extern void updateMax7219Matrix(void);
					updateMax7219Matrix();
				}
				break;
#endif
		}
	}

}

volatile uint16_t FramesDropped = 0;
volatile uint32_t System1msCount = 0;

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_Handler(void)
{
               ++System1msCount;
               if (RunForeground)
               {
                   FramesDropped++;
               }
                RunForeground = true;
    SysTick->SR = 0;
}

