/*
Copyright 2021-2024 Broadwell Consulting Inc.

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
void ProcessFrameDataQueue();

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

/*!
 Version Changes:
V2.1.2
	- Added H Bridge Pin Mode
	- Added Input Processor Integrator function
	- Reworked and improved PID output scaling function
	- Added ability to read last error, last integrator, last output power, last proportional power, last integrator power, last derviative power through protocol
	- Added output scaling linear interpolation transform
	- Beginning of MAX7219Matrix mode added (not officlaly released)
	- Improved PS2Keyboard efficiency
	- Improved quadrature encoder hardware mode efficiency
	- Improved Ultrasonic Distance sensor efficiency
	- Added  queue interface for 16 bit unsigned numbers
	- Added queued pulse output pin mode
	- Added new file swmath for math functions - currently linear interpolation
	- Fixed bug in PWM / Pulse generation on CCP2 / CCP3
   - Added target pin for public data change on Quad Enc
   - Added frequency measurement on Quad Enc

 V2.1.3
   - Added Frequency Output
   - Added Frame based data logging to queue 
   - Added some infrastructure to support Software I2C Writer
 
 */
uint16_t OverflowFrames = 0;
uint32_t FramesRun = 0;
uint16_t SystemUtilizationAverage = 0x8000;
uint16_t SystemUtilizationCount = 0;
uint32_t SystemUtilizationSum = 0;

uint16_t FrameDataQueue[NUMBER_OF_TOTAL_PINS / 8 + 1]; // Queue from 0 to 19, 8 pins per word, lsb and msb queueing
uint16_t  FrameQueueFrequencyMask = 0;  // FramesRun is anded with this value.  Zero result causes queueing
bool FrameQueueFrameNumber = false;  // Whether or not to add the frame # to the queue before data when queueing
bool FrameQueueEnable = false;     // Overall turn on and off for efficiency
bool FrameQueueChanges = false;
bool FrameQueueFirstRun;
uint16_t FrameDataQueueIndex = 0xFFFF;  // Location in User Data Area of Queue (Should be initialized before use)
uint16_t FrameDataLastValue[NUMBER_OF_TOTAL_PINS];

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
            if (FrameQueueEnable)
            {
                ProcessFrameDataQueue();
            }
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
                
            case PIN_MODE_I2C_CONTROLLER:
            {
                extern void updateI2CController();
                updateI2CController();
            }
                
        case PIN_MODE_QUEUED_PULSE_OUTPUT:
        {
            extern void updateQueuedPulseOutput(void);
            updateQueuedPulseOutput();
        }
        break;

	case PIN_MODE_FREQUENCY_OUTPUT:
	{
		extern void updateFrequencyOutput(void);
		updateFrequencyOutput();
	}
	break;
        
            case PIN_MODE_MAX7219MATRIX:
            {
                extern void updateMax7219Matrix(void);
                updateMax7219Matrix();
            }
            break;
		}
	}
}


void ProcessFrameDataQueue()
{
	uint8_t pin;
	if ((FramesRun & FrameQueueFrequencyMask) == 0 || FrameQueueChanges )
	{
		uint8_t arrayIndex = 0;
		uint16_t mask = 0x01;
		int bytesToQueue = 0;

		// Find out how many bytes to queue to see if there's space
		for (pin = 0; pin <  NUMBER_OF_TOTAL_PINS; )
		{

			if (FrameDataQueue[arrayIndex] & mask)
			{
				// Queue Low byte
				++bytesToQueue;
			}
			mask <<= 1;
			if (FrameDataQueue[arrayIndex] & mask)
			{
				// Queue High byte
				++bytesToQueue;
			}
			mask <<= 1;
			++ pin;

			// Every 8 pins advance the array index and reset the mask.
			if ((pin & 0x07) == 0)
			{
				++ arrayIndex;
				mask = 0x01;
			}
		}
		if (FrameQueueFrameNumber)
		{
			bytesToQueue += 2;
		}

		// Check to see if the queue is valid and initialized, and get the remaining free bytes
		uint16_t bytesFree;
		SW_QUEUE_RESULT_t result =  QueueGetBytesFreeInQueue(FrameDataQueueIndex, &bytesFree);
		if (result != QUEUE_RESULT_SUCCESS)
		{
			//Something's wrong with this queue.  Give up.
			return;
		}
		if (bytesFree < bytesToQueue )
		{
			// Not enough free space to queue all the data this frame.  Give up.
			return;
		}
       arrayIndex = 0;
		mask = 0x01;

		if (FrameQueueChanges)  
		{
			//We only queue on frame data changes for enabled pins
			bool changeFound = 0;
			if (FrameQueueFirstRun) 
			{
				//This is the first run after initialization of the logger.  Log data by marking change Found
				changeFound = 1;
				FrameQueueFirstRun = 0;
			}
			for (pin = 0; pin <  NUMBER_OF_TOTAL_PINS; )
			{
				//Scan through the pins seeing if they're of interest to the data
				// logger.  If so, check to see if that pin has changed since last check
				if (FrameDataQueue[arrayIndex] & mask)
				{
					// Check low byte
					if ((GetBuffer(pin) & 0xFF) != (FrameDataLastValue[pin] & 0xFF) )
					{
						changeFound = 1;
						break;
					}
				}
				mask <<= 1;

				// Check high byte
				if (FrameDataQueue[arrayIndex] & mask)
				{
					if ((GetBuffer(pin) >> 8) != (FrameDataLastValue[pin] >> 8) )
					{
						changeFound = 1;
						break;
					}
				}
				mask <<= 1;
				++ pin;

				// Every 8 pins advance the array index and reset the mask.
				if ((pin & 0x07) == 0)
				{
					++ arrayIndex;
					mask = 0x01;
				}
			}
			if (! changeFound)
			{
				// No changes found.  Don't queue anything.  Return
				return;
			}

			// If we're here, something changed.
		}

		// Start queueing data
		if (FrameQueueFrameNumber)
		{
			// If configured, store the 16 bit frame counter.  This allows relative timing
			// and indication of missed packets.
			QueueAddByte(FrameDataQueueIndex,(uint8_t)FramesRun);
			QueueAddByte(FrameDataQueueIndex,(uint8_t)(FramesRun>>8));
		}


		arrayIndex = 0;
		mask = 0x01;
		// Iterate through each pin.  Each pin gets 2 bits.  The lower bit indicates that
		// the low byte of the pin's public data should be stored.
		// The higher bit indicates that the high byte of the pin's public data should be stored.
		for (pin = 0; pin <  NUMBER_OF_TOTAL_PINS; )
		{

			if (FrameDataQueue[arrayIndex] & mask)
			{
				// Queue Low byte
				QueueAddByte(FrameDataQueueIndex,(uint8_t)GetBuffer(pin));
			}
			mask <<= 1;
			if (FrameDataQueue[arrayIndex] & mask)
			{
				// Queue High byte
				QueueAddByte(FrameDataQueueIndex,(uint8_t)(GetBuffer(pin)>>8));
			}
			mask <<= 1;
			++ pin;

			// Every 8 pins advance the array index and reset the mask.
			if ((pin & 0x07) == 0)
			{
				++ arrayIndex;
				mask = 0x01;
			}
		}

		if (FrameQueueChanges)  
		{
			//Store current values for comparision the next time in here
			for (int pin = 0; pin <  NUMBER_OF_TOTAL_PINS; ++pin)
			{

				FrameDataLastValue[pin] = GetBuffer(pin) ;
			}
		}
	}
}

