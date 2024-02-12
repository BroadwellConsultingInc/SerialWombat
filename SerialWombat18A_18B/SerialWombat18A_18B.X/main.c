/*
Copyright 2021-2023 Broadwell Consulting Inc.

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
#include <stdbool.h>
#include <string.h>
#include "serialWombat.h"
#include "pic24fj256ga702/mcc_generated_files/mcc.h"
#define    FCY    16000000UL
#include <libpic30.h> 
uint8_t CurrentPin;

uint8_t FrameTimingPin = 0xFF;

 bool RunForeground = false;


uint8_t UserBuffer[SIZE_OF_USER_BUFFER];
void processCapturedCommands();

void reset ()
{
    #ifdef __DEBUG    
        //TODO  future internal debugging feature: shut down peripherals, shut off interrupts, jump to reset vector ?
#else
    
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
#endif
}
/*
 Serial Wombat Memory Map :
 0 - 0x4000  Bootloader
 0x4000 - 0x4100 Alternate IVT
 * 0x4100 - 0x1F800 Program memory
 * 0x1F800   Magic number 0xCD23
 * 0x1F804 - 16 bit CRC
 * 0x20000 - 0x27000 -  User Space
 * 0x27000 - 0x27800 - Initialization sequence space
 * 0x27800 - 0x28800- User Buffer initialization
 * 0x2A000 - 0x2B000 - Calibration space:
 *  0x2A000 - Vbg in mV
 *  0x2A002 - Trim value for 55uA current
 *  0x2A004 - Temperature reading reported
 *  0x2A006 - Temperature reading actual
 * 0x2A008 - Temperature reading2 reported
 *  0x2A00A - Temperature reading2 actual
 * 0x02A00C - 
 
 */
uint16_t OverflowFrames = 0;
uint32_t FramesRun = 0;
uint16_t SystemUtilizationAverage = 0x8000;
uint16_t SystemUtilizationCount = 0;
uint32_t SystemUtilizationSum = 0;
int main(void)
{
    INTERRUPT_GlobalDisable();
    RCON = 0;
    INTCON2 |= 0x100; // Set Alternate vector table.  Bits in .h file are wrong in INTCON2bits so use bit or
	// initialize the device
    for (CurrentPin = 0; CurrentPin <  NUMBER_OF_TOTAL_PINS; ++CurrentPin)
	{
        SetMode(CurrentPin, PIN_MODE_DIGITAL_IO);
    }
    memset(UserBuffer,0, sizeof(UserBuffer));
	SYSTEM_Initialize();
    while (!HLVDCONbits.BGVST); // Wait for Band Gap to stabilize.

    SPI3CON1L = 0x8020;  // Make SPI3 Leader, CS enabled as high data source for PPS  //TODO Is this debug code?
        SPI3CON1H = 0x0010;

        timingResourceManagerInit();
    
 
    processCapturedCommands();
    
    INTERRUPT_GlobalEnable();
    
    
	while (1)
	{
		//SET_THROUGHPUT_ANALOG(30);
		ProcessRx();

		if (RunForeground)
		{
            PinHigh(FrameTimingPin);

			RunForeground = false;
            ++FramesRun;
			ProcessPins();
            if (RunForeground)
			{
					++OverflowFrames;
			}
            else
            {
                SystemUtilizationSum += TMR2_Counter16BitGet();
                ++SystemUtilizationCount;
                if (SystemUtilizationCount == 1024)
                {
                    SystemUtilizationSum <<= 6;
                    SystemUtilizationSum/= PR2;
                    SystemUtilizationAverage = SystemUtilizationSum;
                    SystemUtilizationCount = 0;
                    SystemUtilizationSum = 0;
                }
            }
            PinLow(FrameTimingPin);			
		}
        {
         
        i2cHealthMonitor();
        }
        
	}

	return 1;
}

void ProcessPins()
{
	//IO Processing

	for (CurrentPin = 0; CurrentPin <  NUMBER_OF_TOTAL_PINS; ++CurrentPin)
	{
		CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
		switch (CurrentPinRegister->generic.mode)
		{
			case PIN_MODE_DIGITAL_IO:
				{
					if (CurrentPinRead())
					{
						CurrentPinRegister->generic.buffer = 65535;
					}
					else
					{
						CurrentPinRegister->generic.buffer = 0;
					}
				}
				break;
			case PIN_MODE_ANALOGINPUT:
				{
					void updateAnalogInput(void);
					updateAnalogInput();
				}
				break;
			case PIN_MODE_CONTROLLED:
			case PIN_MODE_FRAME_TIMER:
				break;

			case PIN_MODE_QUADRATURE_ENC:
				{
					void updateQuadEnc(void);
					updateQuadEnc();
				}
				break;
            case PIN_MODE_HBRIDGE:
            {
                void updatehBridge(void);
                updatehBridge();
            }
            break;
			case PIN_MODE_SERVO:
				{
					void updateServoHw(void);
					updateServoHw();
				}
				break;
			case PIN_MODE_HF_SERVO:
				{
					void updateHfServo(void);
					updateHfServo();
				}
				break;
			
			case PIN_MODE_MATRIX_KEYPAD:
				{
					void updateMatrixKeypad(void);
					updateMatrixKeypad();
				}
				break;
			case PIN_MODE_WATCHDOG:
				{
					void updateWatchdog(void);
					updateWatchdog();
				}
				break;         
				/*			case PIN_MODE_DIAGNOSTIC:
				//update_diagnostics();
				break;         
				case PIN_MODE_COUNTER:
				//update_counter();
				break;
				*/
			case PIN_MODE_DEBOUNCE:
				{
					void updateDebounce(void);
					updateDebounce();
				}
				break;

			case PIN_MODE_PULSE_TIMER:
				{
					void updatePulseTimer(void);
					updatePulseTimer();
				}
				break;
			case PIN_MODE_ULTRASONIC_DISTANCE:
				{
					void updateUltrasonicDistance(void);
					updateUltrasonicDistance();
				}
				break;
			case PIN_MODE_INPUT_PROCESSOR:
				{
					void updatePinInputProcessor(void);
					updatePinInputProcessor();
				}
				break;

			case PIN_MODE_PWM:
				{
					void updatePWM(void);
					updatePWM();
				}
				break;

			case PIN_MODE_SW_UART:
				{
					extern void updateUARTSw(void);
					updateUARTSw();
				}
				break;

			case PIN_MODE_PROTECTEDOUTPUT:
				{
					extern void updateProtectedOutput();
					updateProtectedOutput();
				}
				break;

			case PIN_MODE_TM1637:
				{
					extern void updateTM1637();
					updateTM1637();
				}
				break;

			case PIN_MODE_WS2812:
				{
					extern void updateWS2812();
					updateWS2812();
				}
				break;
			case PIN_MODE_TOUCH:
				{
					extern void updateTouch();
					updateTouch();
				}
				break;

			case PIN_MODE_RESISTANCE_INPUT:
				{
					extern void updateResistanceInput(void);
					updateResistanceInput();
				}
				break;
			case PIN_MODE_THROUGHPUT_CONSUMER:
				{
					void updateThroughputConsumer();
					updateThroughputConsumer();
				}
				break;

			case PIN_MODE_PULSE_ON_CHANGE:
				{
					void updatePulseOnChange(void);
					updatePulseOnChange();
				}
				break;
			case PIN_MODE_LIQUID_CRYSTAL:
				{
					void updateLiquidCrystal(void);
					updateLiquidCrystal();
				}
				break;

			case PIN_MODE_UART0_TXRX:
			case PIN_MODE_UART1_TXRX:
				{
					extern void updateUARTHw(void);
					updateUARTHw();
				}
				break;

			case PIN_MODE_HS_CLOCK:
				{
					extern void updateHSClock();
					updateHSClock();
				}
				break;

			case PIN_MODE_HS_COUNTER:
				{
					extern void updateHSCounter();
					updateHSCounter();
				}
				break;

			case PIN_MODE_VGA:
				{
					extern void updateVGA();
					updateVGA();
				}
				break;
			case PIN_MODE_PS2_KEYBOARD:
				{
					extern void updatePS2Keyboard();
					updatePS2Keyboard();
				}
				break;
                
        case PIN_MODE_QUEUED_PULSE_OUTPUT:
        {
            extern void updateQueuedPulseOutput(void);
            updateQueuedPulseOutput();
        }
        break;
		}
	}
}




