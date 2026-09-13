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
#include "asciiConversion.h"
#include "inputProcess.h"
uint32_t debug_discarded_bytes = 0;

uint8_t SW_I2CAddress = 0x6B;
bool UART2ndInterface = false;
uint8_t UartRxbufferCounter = 0;
uint8_t UartTxbufferCounter = 0;
uint8_t Rxbuffer[RXBUFFER_LENGTH];
uint8_t Txbuffer[TXBUFFER_LENGTH];
bool LineBreaksAndEcho = false;

volatile bool ResponsePending = false;
volatile bool ResponseAvailable = false;
volatile uint8_t TX_ClockStretching = 0;
volatile uint8_t RX_ClockStretching = 0;



void ProcessSetPin(void);

#define PROTOCOL_MAX_CAPTURED_PACKETS 256
extern bool protocolCapturingPackets ;
extern uint16_t protocolCapturedPackets;

void storeCapturedPackets(void);




volatile unsigned short crcResultCRCCCITT = 0;
//#define I2C_DEBUG_OUTPUT
#ifdef I2C_DEBUG_OUTPUT
#define OUTPUT_I2C_DEBUG(_value) {LATB = (_value <<7);  LATBbits.LATB6= 1;Nop();Nop();Nop();Nop(); LATBbits.LATB6 = 0;}
#warning I2C_DEBUG_OUTPUT ENABLED!   PORT B DMA Disabled!
#else
#define OUTPUT_I2C_DEBUG(_value){}
#endif

void uartStartTX()
{
	uint8_t crlf[] = {'\r','\n'};
	if (LineBreaksAndEcho)
	{
		UART1_WriteBuffer(crlf,2);
     
	}

	UART1_WriteBuffer(Txbuffer,TXBUFFER_LENGTH); //TODO Fix Line Breaks and Echo
	if (LineBreaksAndEcho)
	{
		UART1_WriteBuffer(crlf,2);
           UART1_WriteBuffer(crlf,2);
	}
	UartTxbufferCounter = 0;
}



uint16_t PacketsProcessed = 0;
void ProcessRxbuffer( void )
{
	PacketsProcessed++;
	Txbuffer[0] = Rxbuffer[0];
	Txbuffer[1] = Rxbuffer[1];
	Txbuffer[2] = Rxbuffer[2];
	Txbuffer[3] = Rxbuffer[3];
	Txbuffer[4] = Rxbuffer[4];
	Txbuffer[5] = Rxbuffer[5];
	Txbuffer[6] = Rxbuffer[6];
	Txbuffer[7] = Rxbuffer[7];
    
    if (protocolCapturingPackets  && Rxbuffer[0] != COMMAND_CAPTURE_STARTUP_SEQUENCE  && Rxbuffer[0] != COMMAND_ASCII_RESET)
    {
        if (protocolCapturedPackets < PROTOCOL_MAX_CAPTURED_PACKETS)
        {
            uint16_t index = SIZE_OF_USER_BUFFER - PROTOCOL_MAX_CAPTURED_PACKETS * 12 + protocolCapturedPackets * 12;
            UserBuffer[index ] = Rxbuffer[0];
            UserBuffer[index + 1] = Rxbuffer[1];
            UserBuffer[index + 2] = Rxbuffer[2];
            UserBuffer[index + 3] = 0 ;  // Unimplemented in flash
            UserBuffer[index + 4 ] = Rxbuffer[3];
            UserBuffer[index + 5] = Rxbuffer[4];
            UserBuffer[index + 6] = Rxbuffer[5];
            UserBuffer[index + 7] = 0 ;  // Unimplemented in flash
            UserBuffer[index + 8 ] = Rxbuffer[6];
            UserBuffer[index + 9] = Rxbuffer[7];
            UserBuffer[index + 10] = 0x55;
            UserBuffer[index + 11] = 0 ;  // Unimplemented in flash
            
            ++protocolCapturedPackets;
        }
    
    }
	switch (Rxbuffer[0])
	{
	
            
           
		case COMMAND_ASCII_LINEFEED:
			{
				/** \addtogroup ProtocolAsciiCommands
				  \{

				  ASCII Enable / Disable Line Breaks
				  ---------------------
				  This command causes the Serial Wombat to echo back input and add a carraige return / line feed before and after every returned message.

				  This is very useful when you're typing commands in a terminal, but will cause problems if you are talking to the Serial Wombat
				  with a program, particularly if you are using Binary commands.

				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |'^'|'L'|'I'|'N'|'E'|'B'|'K'|'0' or '1'|

Examples:

`^LINEBK1`

Enables Line Breaks. 

`^LINEBK0`

Disables Line Breaks (default). 

\}
				 **/

				if (Rxbuffer[1] == 'L' &&
						Rxbuffer[2] == 'I' &&
						Rxbuffer[3] == 'N' &&
						Rxbuffer[4] == 'E' &&
						Rxbuffer[5] == 'B' &&
						Rxbuffer[6] == 'K')
				{
					if (Rxbuffer[7] == '1')
					{
						LineBreaksAndEcho = true;
					}
					else
					{
						LineBreaksAndEcho = false;
					}

				}
			}
			break;

		case COMMAND_ASCII_SET_PUBLIC_DATA: // Set Public Data
			/** \addtogroup ProtocolAsciiCommands
			  \{

			  ASCII Set Public Data 
			  ---------------------
			  This command allows the public data of a pin to be set.  Maximum allowable data value is 65535 .
			  Echos back response unless error.

			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |'d'|Pin X 10's|Pin X 1's|Public Data 10000's|Public Data 1000's|Public Data 100's | Public Data 10's | Public Data 1's|

Examples:

`d0213143`

Sets pin 2 Public Data to 13143.

\}
			 **/
			{
				uint8_t pin =  ascii_to_val(Rxbuffer[1]);
				pin *= 10;
				pin += ascii_to_val(Rxbuffer[2]);
				uint32_t value = ascii_to_val(Rxbuffer[3]);
				value *= 10;
				value += ascii_to_val(Rxbuffer[4]);
				value *= 10;
				value += ascii_to_val(Rxbuffer[5]);
				value *= 10;
				value += ascii_to_val(Rxbuffer[6]);
				value *= 10;
				value += ascii_to_val(Rxbuffer[7]);
				if (value <= 0xFFFF)
				{
					SetBuffer(pin,value);
				}
				else
				{
					error(SW_ERROR_ASCII_NUMBER_TOO_BIG_16);
				}
			}
			break;

		case COMMAND_ASCII_GET_PUBLIC_DATA: // Set Public Data
			/** \addtogroup ProtocolAsciiCommands
			  \{

			  ASCII Get Public Data 
			  ---------------------
			  This command allows the public data of a pin to be set.  Maximum allowable data value is 65535 .
			  Echos back response unless error.

			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |'G'|Pin X 100's |Pin X 10's|Pin X 1's|'U'*|'U'*|'U'*|'U'*|

			 *'U' is recommended, but any byte is acceptable

Examples:

`G002UUUUU`

Gets pin 2 Public Data In Ascii
Sample Response:

`G0226132`

Public data for Pin 2 is 26132.

\}
			 **/
			{
				uint8_t pin =  ascii_to_val(Rxbuffer[1]);
				pin *= 10;
				pin += ascii_to_val(Rxbuffer[2]);
                pin *= 10;
				pin += ascii_to_val(Rxbuffer[3]);
                Txbuffer[1] = Rxbuffer[3];
                Txbuffer[2] = ' ';
				uint16ToAscii5(GetBuffer(pin),&Txbuffer[3]);
			}
			break;



		case COMMAND_ASCII_SET_PIN: 
			/** \addtogroup ProtocolAsciiCommands
			  \{

			  ASCII Set Pin Command
			  ---------------------
			  This command allows the digital state of up to 5 consecutive pins to be set.  

			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |'p'|Pin X 10's|Pin X 1's|Pin X Setting|Pin X+1 Setting|Pin X+2 Setting|Pin X+3 Setting|Pin X+4 Setting|

			  Possible Pin Settings:
			  - 'l' Make the pin an Output Low
			  - 'h' Make the pin an Output High
			  - 'a' Make the pin an Analog Input
			  - 'd' Make the pin an Input (with a weak Pull Down)
			  - 'i' Make the pin an Input (without a weak Pull Up or Pull Down)
			  - 'r' Make the pin a Resistance Input
			  - 's' Make the pin a Servo Controller
			  - 'u' Make the pin an Input (with a weak Pull Up)
			  - 'w' Make the pin a PWM Output
			  - 'x' or ' ' or 'U' No change
			  Echos back response unless error.

Examples:

`p021xxxx`

Sets pin 2 high, and doesn't change any other pins


`P0910xii`

Sets pin 9 High, pin 10 Low, doesn't change pin 11, and sets pins 12 and 13 to inputs

\}
			 **/
			{
				uint8_t pinToSet, rxIndex;
				pinToSet = ascii_to_val(Rxbuffer[1]);
				pinToSet  *= 10;
				pinToSet  += ascii_to_val(Rxbuffer[2]); 
                CurrentPin = pinToSet;		
				CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
				for ( rxIndex = 3; rxIndex < 8 ; ++rxIndex,++pinToSet )
				{
					
					{
                        
                        if(Rxbuffer[rxIndex] != 'a')
                        {
						ConfigurePinAnalog(pinToSet,false);
						SetMode(pinToSet,PIN_MODE_DIGITAL_IO) ;
                        }
						switch(Rxbuffer[rxIndex])
						{
							case 'i':
								{
								    SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,0);
								PinInput(pinToSet);
								}
								break;
							case 'l':	
								{
								    SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,0);
									PinLow(pinToSet);
								}
								break;
							case 'h':
								{
								    SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,0);
									PinHigh(pinToSet);
								}
								break;
							case 'u':  //Pull Up Input
								{
                                    SetPinPullDown(pinToSet,0);
									SetPinPullUp(pinToSet,1);
									PinInput(pinToSet);
								}
								break;
							case 'd':  //Pull Down Input
								{
									SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,1);
									PinInput(pinToSet);
								}
								break;
							case 'r':  //Resistance Input
								{
									void initResistanceInputSimple(void);
									initResistanceInputSimple();
								}
								break;
							case 's':  //Servo
								{
									void initServoHwSimple(void);
								    SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,0);
									initServoHwSimple();
								}
								break;
							case 'w':  //PWM
								{
									void initPWMSimple(void);
									    SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,0);
								initPWMSimple();
								}
								break;
                            
                            case 'a':
                                {
                                    void analogInputBegin(uint8_t pin, uint16_t averageSamples , uint16_t filterConstant  , uint8_t publicDataOutput );
 								    SetPinPullUp(pinToSet,0);
                                    SetPinPullDown(pinToSet,0);
                                    analogInputBegin(CurrentPin,64,0xFF80,INPUT_FILTER_MODE_NONE);
                               }
                                break;
                                
							case 'x':
                            case ' ':
                            case 'U':
								{
								}
								break;
							default:
								{
									error(SW_ERROR_UNKNOWN_PIN_MODE);
								}
								break;
						}
					}
				}
			}
			break;
	
      
      

		case COMMAND_BINARY_READ_FLASH:
			{
				/** \addtogroup ProtocolBinaryCommands
				  \{

				  ----

				  Binary Read Flash, 32 Bit address, 32 Bit result
				  ---------------------

				  Reads two bytes from an address in Microcontroller Flash.  The SW18AB  uses 32 bit addresses.  Due to 24 bit architecture the high byte of a 32 bit word is 0.
				  Multiply the Word Address by 2 to get the byte address.  

				  See the Datasheet for the microchip PIC16F15214 for information on organization

				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0xA1|Least Significant byte of 32-bit byte address (must be multiple of 4) |Middle low byte of 32-bit byte address  | Middle High byte of 32-bit byte address | Most Significant byte of 32-bit byte address | 0x55* |  0x55* | 0x55* |


Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xA1|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address |Echoed|Echoed| Low Byte Read From Flash| High Byte Read From Flash |  Echoed |

Examples:

Read the word at FLASH address 0x010846.

> `0xA1 0x46 0x08 0x01 0x00 0x55 0x55 0x55`

Assuming address 0x0846 held the value 0x07EF ,
Response:
> `0xA1 0x46 0x08 0x01 0x00 0xEF 0x07 0x55`

\}
				 **/
				uint32_t address = RXBUFFER32(1);
				uint16_t result = 0;
				if (address & 0x01)
				{
					error(SW_ERROR_RF_ODD_ADDRESS);
				}
				else
				{
					//TODO Investigate Further.  INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
					uint8_t tblpag = TBLPAG;
					TBLPAG = address >>16;
					result = __builtin_tblrdl(address );
					TXBUFFER16(4,result);          
					result = __builtin_tblrdh(address );
					TBLPAG = tblpag;
					//TODO Investigate Further INTERRUPT_GlobalEnable();
					TXBUFFER16(6,result);

				}

			}
			break;
            case COMMAND_BINARY_WRITE_FLASH:
		{
			switch (Rxbuffer[1])
			{
				case 0:
				{
					// Erase block - 32 bit address at rxbuffer[2], 16 bit length at rxbuffer[6]
					// Up to caller to assure the block is aligned.
                    // Called once per block.
					// RXbuffer Address is in bytes not words to match hex file
                    // User should delay appropriate time to allow erase completion before requesting response over I2C
                   
                    uint32_t address = RXBUFFER32(2)/2;  // Convert to Words
                    if (address < 0x4000)  // Beginning of Application
                    {
                        error(SW_ERROR_FLASH_WRITE_INVALID_ADDRESS);
                    }
                    else
                    {
                    NVMADRU = (uint16_t)(address >>16);
                    NVMADR = (uint16_t)(address & 0xFFFF);
                            NVMCON = 0x4003;
                    __builtin_disi(6);
                    __builtin_write_NVM();
                    }
				}
				break;

				case 1:
				{
					// Write block - 32 bit address at rxbuffer[2], 16 bit length at rxbuffer[6]
					// up to caller to assure block is aligned, right length.
					// All bytes are included, even if they are not implemented.
					// Address is in bytes not words to match hex file
                    // Called once per block.
                    // User should delay appropriate time to allow erase completion before requesting response over I2C
                    uint32_t address = RXBUFFER32(2)/2;
                    if (address < 0x4000)  // Beginning of Application
                    {
                        error(SW_ERROR_FLASH_WRITE_INVALID_ADDRESS);
                    }
                    else
                    {
                        INTERRUPT_GlobalDisable();
                        FLASH_Unlock(FLASH_UNLOCK_KEY);

                    FLASH_WriteRow24(address, (uint32_t*)UserBuffer);
                    INTERRUPT_GlobalEnable();
                    }
                   
				}
				break;
                
                case 2:
                {
                    extern volatile unsigned short crcResultCRCCCITT ;
                    void crcAppSpace(uint32_t address_w, uint32_t length_w);
                    crcAppSpace(0x4000,0x1F800 - 0x4000);
                    TXBUFFER16(2,crcResultCRCCCITT);
                    
                    
                }
                break;
                 case 3:
                {
                    extern volatile unsigned short crcResultCRCCCITT ;
                  
                    TXBUFFER16(2,crcResultCRCCCITT);
            uint16_t result = 0;
           
                INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                uint8_t tblpag = TBLPAG;
                TBLPAG = 1;
                    result = __builtin_tblrdl(0xF804);      
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
                    TXBUFFER16(4,result);
                    TXBUFFER16(6,1);
                    
                }
                break;
               
                    
            }
		}
		break;

		case COMMAND_BINARY_WRITE_RAM:
			{
				/** \addtogroup ProtocolBinaryCommands
				  \{

				  ----

				  Binary Write RAM, 16 Bit address (
				  ---------------------

				  Reads a byte from an address in Microcontroller RAM.  The SW4A and SW4B use 16 bit addresses.  

				  Note that the PIC16F15214 is a Microchip Enhanced Mid-Range chip with both a banked RAM area and a Linear RAM area at an offset address.  
				  See the datasheet for details.


				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0xA3|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address | 0 (for 32-bit compatability) | 0 (for 32-bit compatability) | Byte To write |  0x55* | 0x55* |
				 *0x55 is recommended, but any byte is acceptable

Response:

Echoed Back.
				 * 
Examples:

Write 0x32 the byte at RAM address 0x0247.

> `0xA3 0x47 0x02 0x00 0x00 0x32 0x55 0x55`



\}
				 **/
				uint16_t addr = RXBUFFER16(1);
				*(uint8_t*)addr = Rxbuffer[5];            
			}
			break;


             

 case COMMAND_ADJUST_FREQUENCY:
        {
            if (RXBUFFER16(1) > 0)
            {
                OSCTUN +=((uint8_t)(RXBUFFER16(1)));
            }
            if (RXBUFFER16(3) > 0)
            {
                OSCTUN -=((uint8_t) (RXBUFFER16(3)));
            }
            TXBUFFER16(5,OSCCON);
        }
        break;
	case COMMAND_SET_PIN_HW:
	{

		if (Rxbuffer[2] == 1)
		{
			PinPullUp(Rxbuffer[1]);
		}
		else if (Rxbuffer[2] == 0)
		{
			PinNoPullUp(Rxbuffer[1]);
		}
		if (Rxbuffer[3] == 1)
		{
			PinPullDown(Rxbuffer[1]);
		}
		else if (Rxbuffer[3] == 0)
		{
			PinNoPullDown(Rxbuffer[1]);
		}
		if (Rxbuffer[4] == 1)
		{
			PinOD(Rxbuffer[1]);
		}
		else if (Rxbuffer[4] == 0)
		{
			PinNoOD(Rxbuffer[1]);
		}
        if (Rxbuffer[5] == 1)
        {
            timingResourceForceDMA(Rxbuffer[1],1);
        }
        else if (Rxbuffer[5] == 0)
        {
            timingResourceForceDMA(Rxbuffer[1],0);
        }
	}
    break;
        case COMMAND_CALIBRATE_ANALOG:
        {
            
            extern uint16_t VbgCalibration ;  
            extern volatile uint8_t CTMUTrim;
            int i;
            
              if (RXBUFFER16(1) != 0xABCD)  // Unlock value
            {
                 error(SW_ERROR_ANALOG_CAL_WRONG_UNLOCK);
                 return;
            }
            
            VbgCalibration = 0;
            uint32_t vbg = 0;
            for (i = 0; i < 16; ++i)
            {
                vbg += GetVBgCountsVsVRefPin();
            }            
           
            TXBUFFER16(3,vbg);
            TXBUFFER16(5,(vbg/65536));
            vbg /= 512;
            VbgCalibration = vbg;
            TXBUFFER16(1,VbgCalibration);
            
            {
                
            
                uint8_t bestTrim = CTMUTrim;
            int16_t bestDifference = 30000;
            int16_t difference = 30000;
            CTMUCON1Lbits.ITRIM = CTMUTrim - 31;
            CurrentPin = 19; // Read 30k resistance on pin 19
            uint16_t ohms = 0;
            
            int i;
            for (i = 0; i < 32; ++i)
            {
                {
                    uint32_t ohms32 = 0;
                int ohms_i;
                for (ohms_i = 0; ohms_i < 8; ++ ohms_i)
                {
                    
            GetCurrentPinReistanceOhmsSetup(); 
            timingResourceBusyWait(5000);
            ohms32 +=  GetCurrentPinReistanceOhmsRead(GetSourceVoltage_mV());
            ohms32 += 4;
                }
                ohms = ohms32 / 8;
                }
            if (ohms > 30000)
            {
                difference = ohms - 30000;
                  if (difference < bestDifference)
            {
                bestDifference = difference;
                bestTrim = CTMUTrim;
            }
                if (CTMUTrim > 0)
                {
                    --CTMUTrim;
                }
            }
            else
            {
                difference = 30000 - ohms;
                  if (difference < bestDifference)
            {
                bestDifference = difference;
                bestTrim = CTMUTrim;
            }
                if (CTMUTrim < 61)
                {
                    ++CTMUTrim;
                }
            }
          
            }
            CTMUTrim = bestTrim;
            CTMUCON1Lbits.ITRIM = CTMUTrim - 31;
            }
            
            uint32_t externalTemperature = 0;
            uint32_t internalTemperature = 0;
            //Temperature calibration (single point)
            {
            
                
                int i;
                for (i = 0; i < 16; ++i)
                {
                    uint16_t GetADCConversion(uint8_t pin);
                    uint32_t temperature = GetADCConversion(18); // TMP235 Temperature sensor on Pin 18
                    temperature *= GetSourceVoltage_mV();
                    temperature >>= 16;
                    externalTemperature += temperature;
                    internalTemperature += GetTemperature_degC100ths(false);
                    	timingResourceBusyWait(100);
                }
                externalTemperature +=8;
                externalTemperature /= 16;
                externalTemperature -= 500;
                externalTemperature *= 10;
                               
                internalTemperature += 8;
                internalTemperature /= 16;
            }
             INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                uint8_t tblpag = TBLPAG;
                
                           
                TBLPAG = VBG_CAL_ADDRESS >>16;
                for (i = 0; i < 192; ++i)
                {
                    ((uint32_t*)UserBuffer)[i] = __builtin_tblrdl(VBG_CAL_ADDRESS + 2 * i);
                }
                           
                uint32_t address = VBG_CAL_ADDRESS;
                
                NVMADRU = (uint16_t)(address >>16);
                    NVMADR = (uint16_t)(address & 0xFFFF);
                            NVMCON = 0x4003;
                    __builtin_disi(6);
                    __builtin_write_NVM();
                
                TBLPAG = address >>16;
     
                uint32_t* UserBufferWord32s = (uint32_t*)&UserBuffer;
                UserBufferWord32s[0] = VbgCalibration;
                UserBufferWord32s[1] = CTMUTrim;
                UserBufferWord32s[2] = internalTemperature;
                UserBufferWord32s[3] = externalTemperature;
                 FLASH_Unlock(FLASH_UNLOCK_KEY);
                    FLASH_WriteRow24(address, UserBufferWord32s);
                   
                   TBLPAG = tblpag;
                   
                   INTERRUPT_GlobalEnable();
                   
            
        }
        break;
        				/** \addtogroup ProtocolBinaryCommands
				  \{

				  ----

				  Enable 2nd Command Interface 
				  ---------------------

                         This command is only supported on the SW18AB chip.
				  When in I2C mode by address pin, this enables the UART command interface in parallel with I2C on pins WP7 (TX out) and
                         W9 (RX in).
                         This allows monitoring of the Serial Wombat Chip by a PC or other tool while the chip is also being commanded
                         over I2C
                         
                         Note that enabling then disabling this feature will leave the UART interface interally connected to pins 7 and 9,
                         however commands will no longer be processed through this interface.  A reset is required to fully disconnect internally.
                         
                         The last 6 bytes must match exactly in order to prevent accidental enabling.

				  


				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0xA5|1 = enable, 0 = disable |0xB2 |0xA5 |0x61 |0x73 |0xF8 |0xA2|

Response:

Echoed Back or error message.
				 * 
Examples:

Enable 2nd command interface.

> `0xA5 0x01 0xB2 0xA5 0x61 0x73 0xF8 0xA2`



\}
				 **/
        case COMMAND_ENABLE_2ND_UART:
        {
            if (RXBUFFER16(2) == 0xA5B2 &&
                    RXBUFFER16(4) == 0x7361 &&
                    RXBUFFER16(6) == 0xA2F8)
            {
                if (Rxbuffer[1] == 1 )
                {
                    if(SW_I2CAddress != 0)
                {
            
             RPINR18bits.U1RXR = 0x0005;    //RB5->UART1:U1RX
        RPOR2bits.RP4R = 0x0003;    //RB4->UART1:U1TX
        UART1_Initialize();
        IPC3bits.U1TXIP = 1;
        IPC2bits.U1RXIP = 1;
        TRISBbits.TRISB4 = 0;
        UART1Semaphore = RESOURCE_USED_BY_SYSTEM;
        UART2ndInterface = true;
                }
                    else
                    {
                        error(SW_ERROR_2ND_INF_UNAVAILABLE);
                    }
                }
                else
                {
                   UART2ndInterface = false;
                }
            }
            else
            {
                error(SW_ERROR_2ND_INF_WRONG_UNLOCK);
            
            }
        }
        break;
        
      
/** \addtogroup ProtocolBinaryCommands
\{

----

Binary Send 7 bytes out first UART 
---------------------

Queues 7 bytes to be sent out of the first avaialble Hardware UART.  Assumes a UART pin mode has already been set up.  The host should
query avaialble space before using this command.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB0|1st Byte to Send |2nd Byte To send |3rd Byte To send | 4th Byte To send | 5th Byte To send |  6th Byte To send | 7th Byte To send |

Response:

Packet is echoed back to the host.

Examples:

Send *WOMBAT!* out of the UART 

> `0xB0 0x57 0x4F 0x4D 0x42 0x41 0x54 0x21`

\}
**/
        case COMMAND_UART0_TX_7BYTES:
        {
            if (!IEC0bits.U1RXIE ) 
            {
               error(SW_ERROR_UART_NOT_INITIALIZED);
               return;
            }
            void UART1_Write(uint8_t txData);
            UART1_Write(Rxbuffer[1]);
            UART1_Write(Rxbuffer[2]);
            UART1_Write(Rxbuffer[3]);
            UART1_Write(Rxbuffer[4]);
            UART1_Write(Rxbuffer[5]);
            UART1_Write(Rxbuffer[6]);
            UART1_Write(Rxbuffer[7]);
        }
        break;
        
/** \addtogroup ProtocolBinaryCommands
\{

----

Binary Read 7 bytes from first UART 
---------------------

Read 7 bytes from the queue of the  first avaialble Hardware UART.  Assumes a UART pin mode has already been set up.  The host should
query avaialble bytes to determine the nubmer of bytes avaiable before using this command.  This command should only be called if at
least 7 bytes are available.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB1| 0x55* | 0x55* | 0x55* | 0x55* | 0x55* | 0x55* | 0x55* |
 *0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB1|  1st byte read from UART queue |2nd byte read from UART queue |3rd byte read from UART queue |4th byte read from UART queue |5th byte read from UART queue |6th byte read from UART queue |7th byte read from UART queue |


Examples:

Assuming *GHIJKLM* are the first 7 bytes in the UART RX QUEUE:

Sent:
> `0xB1 0x55 0x55 0x55 0x55 0x55 0x55 0x55`

Received:

> `0xB1 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D`

\}
**/
        case COMMAND_UART0_RX_7BYTES:
        {
            if (!IEC0bits.U1RXIE ) 
            {
               error(SW_ERROR_UART_NOT_INITIALIZED);
               return;
            }
            uint8_t UART1_Read(void);
            Txbuffer[1] = UART1_Read();
            Txbuffer[2] = UART1_Read();
            Txbuffer[3] = UART1_Read();
            Txbuffer[4] = UART1_Read();
            Txbuffer[5] = UART1_Read();
            Txbuffer[6] = UART1_Read();
            Txbuffer[7] = UART1_Read();
        }
        break;
/** \addtogroup ProtocolBinaryCommands
\{

----

Binary Send 7 bytes out first UART 
---------------------

Queues 7 bytes to be sent out of the first avaialble Hardware UART.  Assumes a UART pin mode has already been set up.  The host should
query avaialble space before using this command.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB2|1st Byte to Send |2nd Byte To send |3rd Byte To send | 4th Byte To send | 5th Byte To send |  6th Byte To send | 7th Byte To send |

Response:

Packet is echoed back to the host.

Examples:

Send *WOMBAT!* out of the UART 

> `0xB2 0x57 0x4F 0x4D 0x42 0x41 0x54 0x21`

\}
**/
        case COMMAND_UART1_TX_7BYTES:
        {
            void UART2_Write(uint8_t txData);
            UART2_Write(Rxbuffer[1]);
            UART2_Write(Rxbuffer[2]);
            UART2_Write(Rxbuffer[3]);
            UART2_Write(Rxbuffer[4]);
            UART2_Write(Rxbuffer[5]);
            UART2_Write(Rxbuffer[6]);
            UART2_Write(Rxbuffer[7]);
        }
        break;
        
/** \addtogroup ProtocolBinaryCommands
\{

----

Binary Read 7 bytes from first UART 
---------------------

Read 7 bytes from the queue of the  first avaialble Hardware UART.  Assumes a UART pin mode has already been set up.  The host should
query avaialble bytes to determine the nubmer of bytes avaiable before using this command.  This command should only be called if at
least 7 bytes are available.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB3| 0x55* | 0x55* | 0x55* | 0x55* | 0x55* | 0x55* | 0x55* |
 *0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB1|  1st byte read from UART queue |2nd byte read from UART queue |3rd byte read from UART queue |4th byte read from UART queue |5th byte read from UART queue |6th byte read from UART queue |7th byte read from UART queue |


Examples:

Assuming *GHIJKLM* are the first 7 bytes in the UART RX QUEUE:

Sent:
> `0xB3 0x55 0x55 0x55 0x55 0x55 0x55 0x55`

Received:

> `0xB3 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D`

\}
**/
        case COMMAND_UART1_RX_7BYTES:
        {
            uint8_t UART2_Read(void);
            Txbuffer[1] = UART2_Read();
            Txbuffer[2] = UART2_Read();
            Txbuffer[3] = UART2_Read();
            Txbuffer[4] = UART2_Read();
            Txbuffer[5] = UART2_Read();
            Txbuffer[6] = UART2_Read();
            Txbuffer[7] = UART2_Read();
        }
        break;
        

	

	
		default:
		{
			void ProcessRxBufferCommon(void);
			ProcessRxBufferCommon();
			}
			break;
	}
} // end ProcessRxbuffer

void ProcessRx(void)
{
	if (SW_I2CAddress == 0 || UART2ndInterface)  // Use UART
	{
        uint8_t peekData = UART1_Peek(0);
        
        
        if ((UART1_CONFIG_RX_BYTEQ_LENGTH -UART1_ReceiveBufferSizeGet()) >= 8)
        {
            while(((UART1_CONFIG_RX_BYTEQ_LENGTH - UART1_ReceiveBufferSizeGet()) > 0) && (peekData == 0x55 || peekData == ' ') )
        {
            UART1_Read();
            peekData = UART1_Peek(0);
        }
            if ((UART1_CONFIG_RX_BYTEQ_LENGTH -UART1_ReceiveBufferSizeGet()) >= 8)
            {
                
            uint8_t i; 
            for (i = 0; i < 8; ++i)
            {
                Rxbuffer[i] = UART1_Read();
            }
            if (LineBreaksAndEcho)
			{
				UART1_WriteBuffer(Rxbuffer,8);
			}
            ProcessRxbuffer();
            uartStartTX();
                        }

        }
        /*
		if ( UartRxbufferCounter < RXBUFFER_LENGTH)
		{
			uint8_t numberOfBytesRead = 0;
			numberOfBytesRead = UART1_ReadBuffer(&Rxbuffer[UartRxbufferCounter], RXBUFFER_LENGTH - UartRxbufferCounter);
			if (LineBreaksAndEcho)
			{
				UART1_WriteBuffer(&Rxbuffer[UartRxbufferCounter],numberOfBytesRead);
			}
			UartRxbufferCounter += numberOfBytesRead;

			while (UartRxbufferCounter > 0  && (Rxbuffer[0] == 0x55 || Rxbuffer[0] == ' ')  )
			{
				uint8_t i;
				for (i = 0; i < RXBUFFER_LENGTH - 1; ++i)
				{
					Rxbuffer[i] = Rxbuffer[i+1];

				}
				-- UartRxbufferCounter;
				++debug_discarded_bytes;
			}
         
		}
*/
        /*
		if (UartRxbufferCounter >= RXBUFFER_LENGTH)
		{
			int i;
			ProcessRxbuffer();
			UartRxbufferCounter = 0;
			for (i = 0; i < RXBUFFER_LENGTH; ++i)
			{
				Rxbuffer[i] = 0xFE;
			}	
			uartStartTX();
		}
         */
	}
	if (SW_I2CAddress != 0)  // Use I2C
	{

#ifdef I2C_DEBUG_OUTPUT
        TRISB = 0;
#endif
		extern volatile uint8_t wombatI2CRxData[8];
		extern volatile uint8_t wombatI2CTxData[8];
		extern volatile uint8_t wombatI2CRxDataCount;
        
        

		if (wombatI2CRxDataCount >= 8)
		{
			OUTPUT_I2C_DEBUG(0x11);
			OUTPUT_I2C_DEBUG(0x11);


			ResponseAvailable = false;

			memcpy(Rxbuffer,(const void*)wombatI2CRxData,8);
			wombatI2CRxDataCount = 0;
			if (RX_ClockStretching)  
			{
				OUTPUT_I2C_DEBUG(30);
				// If we're in the middle of stretching a 2nd request to send us data to from the host, release.  
				// We've made a copy of the incoming data, so we can receive another while we're processing this one.
				// The fact that the host is trying to send us another packet means it doesn't care about the response
				// from the packet we're about to process.
				TX_ClockStretching = 0; 
				I2C2CONLbits.SCLREL	 = 1; // Release clock stretch in hardware
			}

			ProcessRxbuffer();
		
			IEC3bits.SI2C2IE = 0; //INTERRUPT_GlobalDisable();
			memcpy((void*)wombatI2CTxData,(const void*)Txbuffer,8);
			ResponseAvailable = true;
			ResponsePending = false;

			if (RX_ClockStretching)
			{
				OUTPUT_I2C_DEBUG(28);
				// If we're in the middle of stretching a 2nd request to send us data to from the host, release.  
				RX_ClockStretching = 0;
				ResponseAvailable = false;
			}

			if (TX_ClockStretching && ResponseAvailable)
			{
				OUTPUT_I2C_DEBUG(29);
				// If we were clock stretching waiting for a response to the last packet to be generated,
				// it's ready now, so stop stretching the clock.
				TX_ClockStretching = 0;
				RX_ClockStretching = 0;
				extern volatile uint8_t wombatI2CTxDataCount;
				I2C2CONLbits.SCLREL	 = 1; // Release clock stretch
				ResponseAvailable = 0;
				//I2C2TRN =   wombatI2CTxData[ 0 ];   
				wombatI2CTxDataCount = 0;

			}
			IEC3bits.SI2C2IE = 1; //INTERRUPT_GlobalEnable();
			OUTPUT_I2C_DEBUG(0x11);
			OUTPUT_I2C_DEBUG(0x11);
		}
	}
}






void crcAppSpace(uint32_t address_w, uint32_t length_w)
{


unsigned short data;
////////////////////////////////////////////////////////////////////////////////
// standard CRC-CCITT
////////////////////////////////////////////////////////////////////////////////
#define CRCCCITT_POLYNOMIAL ((unsigned short)0x1021)
#define CRCCCITT_SEED_VALUE ((unsigned short)0x84CF) // non-direct of 0xffff
CRCCON1 = 0;
CRCCON2 = 0;
CRCCON1bits.CRCEN = 1; // enable CRC
CRCCON1bits.CRCISEL = 0; // interrupt when all shifts are done
CRCCON1bits.LENDIAN = 0; // big endian
CRCCON2bits.DWIDTH = 16-1; // 16-bit data width
CRCCON2bits.PLEN = 16-1; // 16-bit polynomial order
CRCCON1bits.CRCGO = 1; // start CRC calculation
CRCXORL = CRCCCITT_POLYNOMIAL; // set polynomial
CRCXORH = 0;
CRCWDATL = CRCCCITT_SEED_VALUE; // set initial value
CRCWDATH = 0;

uint32_t address;
for (address = address_w; address < address_w + length_w;  address += 2)
{
    
    if (address == 0x4800)
    {
        Nop();
    }
while(CRCCON1bits.CRCFUL); // wait if FIFO is full

 INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                uint8_t tblpag = TBLPAG;
                TBLPAG = address >>16;
                    data = __builtin_tblrdl(address );
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
//data = *pointer++; // load data
asm volatile ("swap %0" : "+r"(data)); // swap bytes for big endian
CRCDATL = data; // 16 bit word access to FIFO

while(CRCCON1bits.CRCFUL); // wait if FIFO is full

 INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                tblpag = TBLPAG;
                TBLPAG = address >>16;
                    data = __builtin_tblrdh(address );
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
//data = *pointer++; // load data
asm volatile ("swap %0" : "+r"(data)); // swap bytes for big endian
CRCDATL = data; // 16 bit word access to FIFO


}
while(CRCCON1bits.CRCFUL); // wait if FIFO is full
CRCCON1bits.CRCGO = 0; // suspend CRC calculation to clear interrupt flag
_CRCIF = 0; // clear interrupt flag
CRCDATL = 0; // load dummy data to shift out the CRC result
// data width must be equal to polynomial length
CRCCON1bits.CRCGO = 1; // resume CRC calculation
while(!_CRCIF); // wait until shifts are done
crcResultCRCCCITT = CRCWDATL; // get CRC result (must be 0x9B4D)

}



void processCapturedCommands()
{

    uint16_t x = 0;
    uint32_t address = 0x27000;
    for (x = 0; x < PROTOCOL_MAX_CAPTURED_PACKETS; ++x )
    {
                    uint8_t tblpag = TBLPAG;

					TBLPAG = address >>16;
					uint16_t result = __builtin_tblrdl(address );
					Rxbuffer[0] = (uint8_t)result;         
					Rxbuffer[1] = (uint8_t)(result>>8);         
					result = __builtin_tblrdh(address );
					Rxbuffer[2] = (uint8_t)(result);         

                    address += 2;

					TBLPAG = address >>16;
					result = __builtin_tblrdl(address );
					Rxbuffer[3] = (uint8_t)result;         
					Rxbuffer[4] = (uint8_t)(result>>8);         
					result = __builtin_tblrdh(address );
					Rxbuffer[5] = (uint8_t)(result);         

                    address += 2;

					TBLPAG = address >>16;
					result = __builtin_tblrdl(address );
					Rxbuffer[6] = (uint8_t)result;         
					Rxbuffer[7] = (uint8_t)(result >> 8);         
					
                    address += 2;



					TBLPAG = tblpag;
                    
                    if (Rxbuffer[0] == 0x55 || Rxbuffer[0] == 0 || Rxbuffer[0] == 0xFF || Rxbuffer[0] == ' ')
                    {
                        return;
                    }
                    ProcessRxbuffer();

    }
    
}

 void storeCapturedPackets()
{
                        //TODO check that Capturing packets is false, 
                    
                    // Erase block - 32 bit address at rxbuffer[2], 16 bit length at rxbuffer[6]
					// Up to caller to assure the block is aligned.
                    // Called once per block.
					// RXbuffer Address is in bytes not words to match hex file
                    // User should delay appropriate time to allow erase completion before requesting response over I2C
                   
    bool writeRequired = false;
    // Check to see if write is necessary.  Perhaps this sequence is already stored.
    {
        uint16_t x = 0;
    uint32_t address = 0x27000;
    uint8_t buffer[12];

    for (x = 0; x < PROTOCOL_MAX_CAPTURED_PACKETS  && ! writeRequired; ++x )
    {
                    uint8_t tblpag = TBLPAG;

					TBLPAG = address >>16;
					uint16_t result = __builtin_tblrdl(address );
					buffer[0] = (uint8_t)result;         
					buffer[1] = (uint8_t)(result>>8);         
					result = __builtin_tblrdh(address );
					buffer[2] = (uint8_t)(result);       
                    buffer[3] = 0;

                    address += 2;

					TBLPAG = address >>16;
					result = __builtin_tblrdl(address );
					buffer[4] = (uint8_t)result;         
					buffer[5] = (uint8_t)(result>>8);         
					result = __builtin_tblrdh(address );
					buffer[6] = (uint8_t)(result);         
                    buffer[7] = 0;

                    address += 2;

					TBLPAG = address >>16;
					result = __builtin_tblrdl(address );
					buffer[8] = (uint8_t)result;         
					buffer[9] = (uint8_t)(result >>8);   
                    buffer[10] = 0x55;
					buffer[11] = 0;

                    address += 2;



					TBLPAG = tblpag;
              
                    uint8_t y;
                    for (y = 0; y < 12; ++y)
                    {
                        uint8_t ubVal = UserBuffer[SIZE_OF_USER_BUFFER - PROTOCOL_MAX_CAPTURED_PACKETS *12 + 12 * x + y];
                        if (buffer[y] != ubVal )
                        {
                            writeRequired = true;
                        }
                    }
                    

    }
    }
    
    //Write the sequence
    if (writeRequired)
    {
                    uint32_t address = 0x27000;  // Convert to Words
                    uint16_t i = 0;
                    
                    NVMADRU = (uint16_t)(address >>16);
                    NVMADR = (uint16_t)(address & 0xFFFF);
                            NVMCON = 0x4003;
                    __builtin_disi(6);
                    __builtin_write_NVM();
                  
				
					// Write block - 32 bit address at rxbuffer[2], 16 bit length at rxbuffer[6]
					// up to caller to assure block is aligned, right length.
					// All bytes are included, even if they are not implemented.
					// Address is in bytes not words to match hex file
                    // Called once per block.
                    // User should delay appropriate time to allow erase completion before requesting response over I2C
                    
                     for (address = 0x27000; address < 0x27800; address += 0x80)
                    {
                        INTERRUPT_GlobalDisable();
                        FLASH_Unlock(FLASH_UNLOCK_KEY);

                    FLASH_WriteRow24(address, (uint32_t*)&UserBuffer[SIZE_OF_USER_BUFFER - PROTOCOL_MAX_CAPTURED_PACKETS *12 + 256 * i]);
                    INTERRUPT_GlobalEnable();
                    ++i;
                    }
                    
    }
}
