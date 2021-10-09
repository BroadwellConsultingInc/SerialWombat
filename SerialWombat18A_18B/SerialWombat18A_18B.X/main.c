#include <stdint.h>
#include <stdbool.h>
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
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
}

uint16_t OverflowFrames = 0;
uint32_t FramesRun = 0;
uint16_t SystemUtilizationAverage = 0x8000;
uint16_t SystemUtilizationCount = 0;
uint32_t SystemUtilizationSum = 0;
uint32_t volatile debug_i;
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
    {
        uint16_t i;
        for (i = 0; i <SIZE_OF_USER_BUFFER; ++i )
        {
            UserBuffer[i] = 0;
        }
    }
	SYSTEM_Initialize();
    while (!HLVDCONbits.BGVST); // Wait for Band Gap to stabilize.
    
    INTERRUPT_GlobalEnable();
             for (debug_i = 0; debug_i < 10000; ++ debug_i);
 
	while (1)
	{
		//SET_THROUGHPUT_ANALOG(30);
		ProcessRx();
#ifdef TODO
		if (executive_settings.idle_enabled)
		{
			OSCCONbits.IDLEN = 1; 
			sleep();
		}
#endif
		if (RunForeground)
		{
            PinHigh(FrameTimingPin);
//i2cDebugTest();
			RunForeground = false;
//TODO			update_clock_time();
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
//TODO			++bg_systime.u;
			
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
		}
	}
}

#if 0
uint16_t failures = 0;
uint16_t accel[1];
int i2cDebugTest()
{
    {
       
        uint8_t slaveDeviceAddress = 0x6B;
    
     // write to an EEPROM Device
        
        uint16_t        dataAddress;
        uint8_t         sourceData[16] = {  0xA0, 0xA1, 0xA2, 0xA3, 
                                            0xA4, 0xA5, 0xA6, 0xA7, 
                                            0xA8, 0xA9, 0xAA, 0xAB, 
                                            0xAC, 0xAD, 0xAE, 0xAF }; 
        uint8_t         *pData;
        uint16_t        nCount;

        uint8_t         writeBuffer[3];
        uint8_t readBuffer[2];
        uint8_t         *pD;
        uint16_t        counter, timeOut, slaveTimeOut;

         I2C1_MESSAGE_STATUS volatile status = I2C1_MESSAGE_PENDING;

        dataAddress = 0x10;             // starting EEPROM address 
        pD = sourceData;                // initialize the source of the data
        nCount = 16;                    // number of bytes to write

        

            // build the write buffer first
            // starting address of the EEPROM memory
            writeBuffer[0] = 0x10  ;          // low low address
            writeBuffer[1] = 0x10  ;          // low low address

            

            // Now it is possible that the slave device will be slow.
            // As a work around on these slaves, the application can
            // retry sending the transaction
            timeOut = 0;
            slaveTimeOut = 0;
            volatile uint32_t i;
            

             I2C1_Initialize();
            while(status != I2C1_MESSAGE_FAIL)
            {
                // write one byte to EEPROM (3 is the number of bytes to write)
                I2C1_MasterWrite(  writeBuffer,
                                        2,
                                        slaveDeviceAddress,
                                        &status);

                // wait for the message to be sent or status has changed.
                while(status == I2C1_MESSAGE_PENDING)
                {
                    // add some delay here

                    // timeout checking
                    // check for max retry and skip this byte
/*                    if (slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT)
                        break;
                    else
                        slaveTimeOut++;
*/
                } 
                if ( 
                    (status == I2C1_MESSAGE_COMPLETE))
                    break;

                // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
                //               or I2C1_DATA_NO_ACK,
                // The device may be busy and needs more time for the last
                // write so we can retry writing the data, this is why we
                // use a while loop here

                // check for max retry and skip this byte
               
               
            }

            if (status == I2C1_MESSAGE_FAIL)
            {
               ++failures;
            }
            
            
            for (i = 0; i < 10000; ++i);
            I2C1_Initialize();
             writeBuffer[0] = 0x28  ; 
            while(status != I2C1_MESSAGE_FAIL)
            {
                // write one byte to EEPROM (3 is the number of bytes to write)
                I2C1_MasterWrite(  writeBuffer,
                                        1,
                                        slaveDeviceAddress,
                                        &status);

                // wait for the message to be sent or status has changed.
                while(status == I2C1_MESSAGE_PENDING)
                {
                    // add some delay here

                    // timeout checking
                    // check for max retry and skip this byte
/*                    if (slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT)
                        break;
                    else
                        slaveTimeOut++;
*/
                } 
                if ( 
                    (status == I2C1_MESSAGE_COMPLETE))
                    break;

                // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
                //               or I2C1_DATA_NO_ACK,
                // The device may be busy and needs more time for the last
                // write so we can retry writing the data, this is why we
                // use a while loop here

                // check for max retry and skip this byte
               
               
            }

            if (status == I2C1_MESSAGE_FAIL)
            {
               ++failures;
            }

            for (i = 0; i < 10000; ++i);
           status = I2C1_MESSAGE_PENDING;
            I2C1_Initialize();
 while(status != I2C1_MESSAGE_FAIL)
            {
                // write one byte to EEPROM (3 is the number of bytes to write)
                I2C1_MasterRead(  accel,
                                        2,
                                        slaveDeviceAddress,
                                        &status);

                // wait for the message to be sent or status has changed.
                while(status == I2C1_MESSAGE_PENDING)
                {
                    // add some delay here

                    // timeout checking
                    // check for max retry and skip this byte
/*                    if (slaveTimeOut == SLAVE_I2C_GENERIC_DEVICE_TIMEOUT)
                        break;
                    else
                        slaveTimeOut++;
*/
                } 
                if ( 
                    (status == I2C1_MESSAGE_COMPLETE))
                    break;

                // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
                //               or I2C1_DATA_NO_ACK,
                // The device may be busy and needs more time for the last
                // write so we can retry writing the data, this is why we
                // use a while loop here

                // check for max retry and skip this byte
               
               
            }

    }
    return 0;
}	
#endif
