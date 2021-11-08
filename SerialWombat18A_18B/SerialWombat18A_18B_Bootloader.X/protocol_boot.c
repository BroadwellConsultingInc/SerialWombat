#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "SerialWombat.h"
#include "asciiConversion.h"
uint32_t debug_discarded_bytes = 0;

uint8_t SW_I2CAddress = 0x6B;
uint8_t UartRxbufferCounter = 0;
uint8_t UartTxbufferCounter = 0;
uint8_t Rxbuffer[RXBUFFER_LENGTH];
uint8_t Txbuffer[TXBUFFER_LENGTH];
bool LineBreaksAndEcho = false;

volatile bool ResponsePending = false;
volatile bool ResponseAvailable = false;
volatile uint8_t TX_ClockStretching = 0;
volatile uint8_t RX_ClockStretching = 0;

uint16_t lastUserBufferIndex = 0xFFFF;
uint16_t lastQueueIndex = 0xFFFF;

uint16_t debugFlashWrites = 0;
#ifdef I2C_DEBUG_OUTPUT
#define OUTPUT_I2C_DEBUG(_value) {LATB = (_value <<11);  LATBbits.LATB10= 1;Nop();Nop();Nop();Nop(); LATBbits.LATB10 = 0;}
#warning I2C_DEBUG_OUTPUT ENABLED!   PORT B DMA Disabled!
#else
#define OUTPUT_I2C_DEBUG(_value){}
#endif
extern uint8_t* UserBufferBoot;
extern uint8_t* UserBufferPtr;
void uartStartTX()
{
	uint8_t crlf[] = {'\r','\n'};
	if (LineBreaksAndEcho)
	{
		UART1_WriteBuffer(crlf,2);
     
	}

	UART1_WriteBuffer(Txbuffer,TXBUFFER_LENGTH); //TODO put in right spot.
	if (LineBreaksAndEcho)
	{
		UART1_WriteBuffer(crlf,2);
           UART1_WriteBuffer(crlf,2);
	}
	UartTxbufferCounter = 0;
}

void error(SW_ERROR_t errorCode)
{
    Txbuffer[0] = 'E';
    uint16ToAscii5((uint16_t) errorCode, &Txbuffer[1]);
    Txbuffer[6] = 0x55;
    Txbuffer[7] = 0x55;
}

void ProcessRxbuffer( void )
{
	Txbuffer[0] = Rxbuffer[0];
	Txbuffer[1] = Rxbuffer[1];
	Txbuffer[2] = Rxbuffer[2];
	Txbuffer[3] = Rxbuffer[3];
	Txbuffer[4] = Rxbuffer[4];
	Txbuffer[5] = Rxbuffer[5];
	Txbuffer[6] = Rxbuffer[6];
	Txbuffer[7] = Rxbuffer[7];
	switch (Rxbuffer[0])
	{
		case COMMAND_ASCII_ECHO:

/** \addtogroup ProtocolAsciiCommands
\{

ASCII Echo 
---------------------
This command simply sends back what was sent and takes no action.
Echos back response unless error.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'!'|AnyByte|AnyByte|AnyByte|AnyByte|AnyByte|AnyByte|AnyByte|

Examples:

`!1234567`

 Will respond `!1234567`

\}
**/

			break;
	
                   case COMMAND_BOOTLOAD:
        {
/** \addtogroup ProtocolAsciiCommands
\{

----

Jump to Bootloader
---------------------

This command causes the Serial Wombat to cease all operation immediately and reset.  After reset it remains in the UART bootloader.  Standard Serial Wombat commands do not work when in the bootloader.  A power cycle is necessary to leave the bootloader.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'B'|'o'|'O'|'t'|'L'|'o'|'A'|'d'|

Examples:

> `^LINEBK1`

Enables Line Breaks. 

> `^LINEBK0`

Disables Line Breaks (default). 

\}
**/
            if (Rxbuffer[1] == 'o'  && Rxbuffer[2] == 'O' && Rxbuffer[3] == 't'
                    && Rxbuffer[4] == 'L' && Rxbuffer[5] == 'o' && Rxbuffer[6] == 'A'
                    && Rxbuffer[7] == 'd')
            {
                extern bool StayInBoot;
                StayInBoot = true;
            }
        }
        break;

		case COMMAND_ASCII_RESET: // 'R'
/** \addtogroup ProtocolAsciiCommands
\{

ASCII Reset Command
---------------------
This command causes an internal reset of the Serial Wombat, similar to one caused by pulling the reset pin low.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'R'|'e'|'S'|'e'|'T'|'!'|'#'|'*'|


No response, as Wombat enters reset upon receipt.
Example:

`ReSeT!#*`

\}
**/
			{
				if (Rxbuffer[1] == 'e' && 
						Rxbuffer[2] == 'S' && Rxbuffer[3] == 'e' && 
						Rxbuffer[4] == 'T' && Rxbuffer[5] == '!' &&
						Rxbuffer[6] == '#' &&  Rxbuffer[7] == '*')
				{
					reset();
				}
				else
				{
					error(SW_ERROR_RESET_STRING_INCORRECT);
				} 
			}
			break;
		case COMMAND_ASCII_VERSION: //Ascii 'V'  Version String
/** \addtogroup ProtocolAsciiCommands
\{

ASCII Version Command
---------------------
Sends back V followed by 7 characters indicating the firmware version number
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'V'|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|
*'U' is recommended, but any byte is acceptable

Examples:

`VUUUUUUU`

 Will respond 
 
 `VSW20001`

 Or similar

\}
**/
			Txbuffer[1] = 'B';   //Boot
			Txbuffer[2] = '1';//(uint8_t)((NUMBER_OF_PHYSICAL_PINS / 10) + '0');   
			Txbuffer[3] = '8';//(uint8_t)((NUMBER_OF_PHYSICAL_PINS % 10) + '0');
			Txbuffer[4] = 'B';//SERIAL_WOMBAT_HARDWARE_IDENTIFIER;	     
			Txbuffer[5] = '2';	     
			Txbuffer[6] = '0';	     
			Txbuffer[7] = '3';	     

			break;
		

			case COMMAND_BINARY_READ_PIN_BUFFFER:
		{
			uint16_t temp = GetBuffer(Rxbuffer[1]);
			TXBUFFER16(2,temp);		
			temp = GetBuffer(Rxbuffer[1] + 1);
			TXBUFFER16(4,temp);		
			temp = GetBuffer(Rxbuffer[1] + 2);
			TXBUFFER16(6,temp);		

		}
		break;

		case COMMAND_BINARY_READ_USER_BUFFER:
		{
			 uint16_t address = RXBUFFER16(1);
			 if (address< SIZE_OF_USER_BUFFER)
			 {
				uint16_t count = SIZE_OF_USER_BUFFER - address - 1;
				if (count > 7)
				{
					count = 7;
				}
				 memcpy(&Txbuffer[1],UserBufferPtr + address,count);
			 }
			 //TODO:  Error on bad address
		}
		break;

		case COMMAND_BINARY_WRITE_USER_BUFFER:
		{
			 lastUserBufferIndex = RXBUFFER16(1);
             uint16_t count = Rxbuffer[3];
             if (count > 4)
             {
                 error(SW_ERROR_WUB_COUNT_GT_4);
             }
             else
             {
                 
             
                 if (lastUserBufferIndex + count < SIZE_OF_USER_BUFFER)
                 {
                     memcpy(UserBufferPtr+lastUserBufferIndex,&Rxbuffer[4],count);
                     lastUserBufferIndex += count;
                 }
                 else
                 {
                     error(SW_ERROR_WUB_INVALID_ADDRESS);
                 }
             }

		}
		break;
		case COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE:
		{
			 if (lastUserBufferIndex < SIZE_OF_USER_BUFFER)
			 {
				uint16_t count = SIZE_OF_USER_BUFFER - lastUserBufferIndex - 1;
				if (count >= 7)
				{
					count = 7;
                  
                    
                     memcpy(UserBufferPtr + lastUserBufferIndex ,&Rxbuffer[1],count);
                     lastUserBufferIndex += count;
                     
                     
                  /*
                     uint8_t i;
                     for (i = 0; i < count; ++i)
                     {
                         UserBufferBoot[lastUserBufferIndex] = Rxbuffer[i + 1];
                         ++lastUserBufferIndex;
                     }
                    */ 

				}
                else
                {
                      error(SW_ERROR_WUB_CONTINUE_OUTOFBOUNDS);
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
                INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                uint8_t tblpag = TBLPAG;
                TBLPAG = address >>16;
                    result = __builtin_tblrdl(address );
                    TXBUFFER16(4,result);          
                    result = __builtin_tblrdh(address );
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
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
					// Address is in bytes not words to match hex file
                    // User should delay appropriate time to allow erase completion before requesting response over I2C
                   
                    uint32_t address = RXBUFFER32(2)/2;
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
                        FLASH_Unlock(FLASH_UNLOCK_KEY);

                    FLASH_WriteRow24(address, (uint32_t*)UserBufferPtr);
                    ++debugFlashWrites;
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
                    TXBUFFER16(6,debugFlashWrites);//TODO
                    
                }
                break;
               
                    
            }
		}
		break;

		
		default:
			error(SW_ERROR_INVALID_COMMAND);
			break;
	}
} // end ProcessRxbuffer

void ProcessRx(void)
{
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
        
		while (UartRxbufferCounter > 0  && Rxbuffer[0] == 0x55 )
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
        INTERRUPT_GlobalDisable();
        memcpy(wombatI2CTxData,Txbuffer,8);
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
        INTERRUPT_GlobalEnable();
			OUTPUT_I2C_DEBUG(0x11);
			OUTPUT_I2C_DEBUG(0x11);
    }
}

uint16_t GetBuffer(uint8_t pin)
{
	
	if (pin == 66)
    {
        uint32_t result = GetSourceVoltageADC();
        result *= 1024;  //Convert to 1.2  V reference to 1.024 v reference for compatibility with SW4B
        result /=1200;
        return ((uint16_t) result); 
    }
    
    else if (pin == 70)
    {
         
        return ( GetTemperature_degC100ths());    
    }
    else if (pin == 85) //0x55
    {
        return (0x5555);
    }
    else
	{
		return(0);
	}
    return(0);
}

