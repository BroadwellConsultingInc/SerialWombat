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
				 memcpy(&Txbuffer[1],&user_buffer[address],count);
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
                     memcpy(&user_buffer[lastUserBufferIndex],&Rxbuffer[4],count);
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
                     memcpy(&user_buffer[lastUserBufferIndex],&Rxbuffer[1],count);
                     lastUserBufferIndex += count;
				}
                else
                {
                      error(SW_ERROR_WUB_CONTINUE_OUTOFBOUNDS);
                }
				
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
					uint32_t address32 = RXBUFFER32(2);

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
    extern uint8_t wombatI2CRxData[8];
    extern uint8_t wombatI2CTxData[8];
    extern uint8_t wombatI2CRxDataCount;
    
    if (wombatI2CRxDataCount >= 8)
    {
        ResponseAvailable = false;
        
        memcpy(Rxbuffer,wombatI2CRxData,8);
        wombatI2CRxDataCount = 0;
        	if (RX_ClockStretching)  
			{
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
			
			// If we're in the middle of stretching a 2nd request to send us data to from the host, release.  
			RX_ClockStretching = 0;

			ResponseAvailable = false;
		}
        
        if (TX_ClockStretching && ResponseAvailable)
        {


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
    }
}

