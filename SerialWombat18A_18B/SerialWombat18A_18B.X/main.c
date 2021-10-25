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

void reset ()
{
    #ifdef __DEBUG    
        //TODO  shut down peripherals, shut off interrupts, jump to reset vector ?
#else
    
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
#endif
}

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
    for (CurrentPin = 0; CurrentPin <=  NUMBER_OF_TOTAL_PINS; ++CurrentPin)
	{
        SetMode(CurrentPin, PIN_MODE_DIGITAL_IO);
    }
    memset(UserBuffer,0, sizeof(UserBuffer));
	SYSTEM_Initialize();
    while (!HLVDCONbits.BGVST); // Wait for Band Gap to stabilize.
    timingResourceManagerInit();
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

	for (CurrentPin = 0; CurrentPin <=  NUMBER_OF_TOTAL_PINS; ++CurrentPin)
	{


		if ((CurrentPin & 0x01) )
		{
#ifdef TODO
        }
			if(comm_settings.processrxbeforeoddpins)
			{
				SET_THROUGHPUT_ANALOG(31);
				ProcessRx();
			}
#endif
		}
		else
		{
#ifdef TODO
			if (comm_settings.processrxbeforeevenpins)
			{
				SET_THROUGHPUT_ANALOG(31);
				ProcessRx();
			}
#endif
		}
		CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
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
            case PIN_MODE_FRAME_TIMER:
				break;
			case PIN_MODE_DMA_WIGGLE:
                        //TODO
				break;
			case PIN_MODE_QUADRATURE_ENC:
            {
                void updateQuadEnc(void);
				updateQuadEnc();
            }
				break;
			case PIN_MODE_SERVO:
            {
                void updatePulseOut(void);
				updatePulseOut();
            }
				break;
			case PIN_MODE_HYSTERESIS:
				//update_hysteresis();
				break;
			case PIN_MODE_KEYPAD_SCAN_ROW:
				//keypad_process();
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
            
			case PIN_MODE_PWM:
            case PIN_MODE_DMA_PULSE_OUTPUT:
            {
                void updatePulseOut(void);
				updatePulseOut();
            }
				break;
#ifdef TODO
			case PIN_MODE_PWM_FOLLOW_DIRECT:
			case PIN_MODE_ANALOG_OUT_FOLLOW:
				//update_pwm_follow_direct();
				break;
#endif
			

			case PIN_MODE_SW_UART_RX:
				{
					//update_uart_rx();
				}
				break;
			case PIN_MODE_SW_UART_TX:
				{
					//update_uart_tx();
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
		}
	}
}

