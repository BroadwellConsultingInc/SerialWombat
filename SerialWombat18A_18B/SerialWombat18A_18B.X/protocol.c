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

volatile uint8_t debugBreakpointVariable = 0;
uint16_t lastUserBufferIndex = 0xFFFF;
uint16_t lastQueueIndex = 0xFFFF;

uint8_t testSequenceNumber = 0;
bool testSequenceArmed = 0;
void ProcessSetPin(void);

//#define I2C_DEBUG_OUTPUT
#ifdef I2C_DEBUG_OUTPUT
#define OUTPUT_I2C_DEBUG(_value) {LATB = (_value <<11);  LATBbits.LATB10= 1;Nop();Nop();Nop();Nop(); LATBbits.LATB10 = 0;}
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
|'D'|Pin X 10's|Pin X 1's|Public Data 10000's|Public Data 1000's|Public Data 100's | Public Data 10's | Public Data 1's|

Examples:

`D0213143`

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
|'G'|Pin X 10's|Pin X 1's|'U'*|'U'*|'U'*|'U'*|'U'*|

 *'U' is recommended, but any byte is acceptable

Examples:

`G02UUUUU`

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
|'P'|Pin X 10's|Pin X 1's|Pin X Setting|Pin X+1 Setting|Pin X+2 Setting|Pin X+3 Setting|Pin X+4 Setting|

Possible Pin Settings:
 - 'l' Make the pin an Output Low
 - 'h' Make the pin an Output High
 - 'a' Make the pin an Analog Input
 - 'd' Make the pin an Input (with a weak Pull Down)
 - 'i' Make the pin an Input (without a weak Pull Up or Pull Down)
 - 's' Make the pin a Servo Controller
 - 'u' Make the pin an Input (with a weak Pull Up)
 - 'w' Make the pin a PWM Output
 - 'x' No change
Echos back response unless error.

Examples:

`P021xxxx`

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
				for ( rxIndex = 3; rxIndex < 8 ; ++rxIndex,++pinToSet )
				{
					if (Rxbuffer[rxIndex] == 'a')
					{
						CurrentPin = pinToSet;		
                        CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
						Rxbuffer[0] = CONFIGURE_CHANNEL_MODE_0;
                        void initAnalogInput(void);
						initAnalogInput();
					}
					else
					{
						ConfigurePinAnalog(pinToSet,false);
						SetMode(pinToSet,PIN_MODE_DIGITAL_IO) ;
						switch(Rxbuffer[rxIndex])
						{
							case 'i':
								{
									PinInput(pinToSet);
								}
								break;
							case 'l':	
								{
									PinLow(pinToSet);
								}
								break;
							case 'h':
								{
									PinHigh(pinToSet);
								}
								break;
							case 'u':  //Pull Up Input
								{
									//TODO add pullup
									PinInput(pinToSet);
								}
								break;
							case 'd':  //Pull Down Input
								{
									//TODO add pulldown
									PinInput(pinToSet);
								}
								break;
							case 's':  //Servo
								{
                                    void initServoSimple(uint8_t pinToSet);
									initServoSimple(pinToSet);
								}
								break;
							case 'w':  //PWM
								{
                                    void initPWMSimple(uint8_t pinToSet);
									initPWMSimple(pinToSet);
								}
								break;
							case 'x':
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
			Txbuffer[1] = 'S';   //Serial Wombat
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
		case COMMAND_BINARY_SET_PIN_BUFFFER:
		{
			SetBuffer(Rxbuffer[1],RXBUFFER16(2));
			SetBuffer(Rxbuffer[4],RXBUFFER16(5));
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
				 memcpy(&Txbuffer[1],&user_buffer[address],count);
			 }
			 //TODO:  Error on bad address
		}
		break;

		case COMMAND_BINARY_WRITE_USER_BUFFER:
		{
			 lastUserBufferIndex = RXBUFFER16(1);
			 if (lastUserBufferIndex< SIZE_OF_USER_BUFFER)
			 {
				uint16_t count = SIZE_OF_USER_BUFFER - lastUserBufferIndex - 1;
				if (count > 5)
				{
					count = 5;
				}
				 memcpy(&user_buffer[lastUserBufferIndex],&Rxbuffer[3],count);
				 lastUserBufferIndex += count;
			 }
			 //TODO:  Error on bad address

		}
		break;
		case COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE:
		{
			 if (lastUserBufferIndex < SIZE_OF_USER_BUFFER)
			 {
				uint16_t count = SIZE_OF_USER_BUFFER - lastUserBufferIndex - 1;
				if (count > 7)
				{
					count = 7;
				}
				 memcpy(&user_buffer[lastUserBufferIndex],&Rxbuffer[3],count);
				 lastUserBufferIndex += count;
			 }
			 //TODO:  Error on bad address

		}
		break;

		case COMMAND_BINARY_QUEUE_INITIALIZE:
		{
/** \addtogroup ProtocolBinaryCommands
\{

Initialize Queue
---------------------
Initialize a queue in user memory 
Queue types are as follows:  
0 - Byte data queue in RAM

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x90 |Queue Address LSB |Queue Address MSB |Size LSB|Size MSB|Queue Type|Varies|Varies|

Examples:

`0x90 0x0010 0x0020 0 0 0`

Initializes a ram queue of 32 bytes at address 0x0010 in user memory.

\}
**/
			QueueByteInitialize(RXBUFFER16(1),RXBUFFER16(2));	
			//TODO handle error return codes

		}
		break;
		case COMMAND_BINARY_QUEUE_ADD_BYTES:
		{
/** \addtogroup ProtocolBinaryCommands
\{

Add bytes to queue
---------------------
Add bytes to a ram queue of bytes.  Updates the internal last queue variable with the queue being added to.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x90 |Queue Address LSB |Queue Address MSB |Count of bytes to add (0-4)| Byte to Add| Byte to Add| Byte to Add| Byte to Add|

Examples:

`0x90 0x0010 4 0x31 0x32 0x33 0x34`

Add bytes 0x31, 0x32, 0x33, and 0x34 to queue located at 0x0010.

\}
**/
			uint8_t i;
			lastQueueIndex = RXBUFFER16(1);
			for (i = 0; i < Rxbuffer[3]; ++i)
			{
				QueueAddByte(lastQueueIndex,Rxbuffer[4 + i]);
			}
			//TODO handle error return codes

		}
		break;
		case COMMAND_BINARY_QUEUE_ADD_7BYTES:
		{
/** \addtogroup ProtocolBinaryCommands
\{

Add bytes to queue
---------------------
Add 7 bytes to the last written ram queue of bytes.  

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x92 |Byte to Add|Byte to Add|Byte to Add|  Byte to Add| Byte to Add| Byte to Add| Byte to Add|

Examples:

`0x92 0x35 0x36 0x37 0x38 0x39 0x3A 0x3B`

Add bytes 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A and 0x3B to queue last added to.

\}
**/
			uint8_t i;
			lastQueueIndex = RXBUFFER16(1);
			for (i = 0; i < Rxbuffer[3]; ++i)
			{
				QueueAddByte(lastQueueIndex,Rxbuffer[4 + i]);
			}
			//TODO handle error return codes

		}
		break;
		case COMMAND_BINARY_QUEUE_READ_BYTES:
		{
/** \addtogroup ProtocolBinaryCommands
\{

Read Bytes from Queue
---------------------
Read up to 6 bytes from a given queue

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x93 |Queue Address LSB|Queue Address MSB|Maximum bytes to read|Unused|Unused|Unused|Unused|


Response:
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x93 |Number of Bytes read from Queue|Data Byte|Data Byte|Data Byte|Data Byte|Data Byte|Data Byte|
Examples:

`0x93 0x0170 0x04 0x20 0x20 0x20 0x20`

Read up to 4 bytes from queue at address 0x0170

Sample Response:
`0x93 0x02 0x34 0x35 0x20 0x20 0x20 0x20` 

Two bytes were available in the queue.  0x34, and 0x35

\}
**/
			QUEUE_RESULT_t result = QUEUE_RESULT_SUCCESS;
			uint8_t i;
			for (i = 0; i < Rxbuffer[3] && result == QUEUE_RESULT_SUCCESS; ++i)
			{
				result = QueueAddByte(RXBUFFER16(1),&Txbuffer[2 + i]); //TODO this is wrong...
			}
			Txbuffer[1] = i;
			//TODO handle error return codes

		}
		break;
       case COMMAND_BINARY_READ_RAM:
        {
            /** \addtogroup ProtocolBinaryCommands
\{

----

Binary Read RAM, 16 Bit address
---------------------

Reads a byte from an address in Microcontroller RAM.  The SW4A and SW4B use 16 bit addresses.  

Note that the PIC16F15214 is a Microchip Enhanced Mid-Range chip with both a banked RAM area and a Linear RAM area at an offset address.  
See the datasheet for details.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xA0|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address | 0x55* | 0x55* | 0x55* |  0x55* | 0x55* |
 *0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xA0|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address | Byte Read From Ram| Echoed | Echoed |  Echoed | Echoed |

Examples:

Read the byte at RAM address 0x0247.

> `0xA0 0x47 0x02 0x55 0x55 0x55 0x55 0x55`

Assuming address 0x0247 held the value 0xAC ,
Response:
> `0xA0 0x47 0x02 0xAC 0x55 0x55 0x55 0x55`

\}
**/
	uint16_t addr = RXBUFFER16(1);
    Txbuffer[3] = *(uint8_t*)addr;
            
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
        
        case COMMAND_BINARY_TEST_SEQUENCE:
        {
            if (Txbuffer[1] == 'R' && 
                    Txbuffer[2] == 'E'  &&
                    Txbuffer[3] == 'S'  &&
                    Txbuffer[4] == 'E'  &&
                    Txbuffer[5] == 'T' )
            {
                testSequenceNumber = 0;
                testSequenceArmed = 1;
            }
            else
            {
                uint8_t i;
                for (i = 1; i < 8 ; ++ i )
                {
                    if (Txbuffer[i] != testSequenceNumber && testSequenceArmed)
                    {
                        #ifdef __DEBUG    
    __builtin_software_breakpoint();
    testSequenceArmed = 0;
    /* If we are in debug mode, cause a software breakpoint in the debugger */
#endif
                    }
                    ++testSequenceNumber;
                    
                }
            }
            
        }
        break;

		case CONFIGURE_CHANNEL_MODE_0:
		case CONFIGURE_CHANNEL_MODE_1:
		case CONFIGURE_CHANNEL_MODE_2:
		case CONFIGURE_CHANNEL_MODE_3:
		case CONFIGURE_CHANNEL_MODE_4:
		case CONFIGURE_CHANNEL_MODE_5:
		case CONFIGURE_CHANNEL_MODE_6:
		case CONFIGURE_CHANNEL_MODE_7:
		case CONFIGURE_CHANNEL_MODE_8:
		case CONFIGURE_CHANNEL_MODE_9:
		case CONFIGURE_CHANNEL_MODE_10:
		case CONFIGURE_CHANNEL_MODE_11:
		case CONFIGURE_CHANNEL_MODE_12:
		case CONFIGURE_CHANNEL_MODE_13:
		case CONFIGURE_CHANNEL_MODE_14:
		case CONFIGURE_CHANNEL_MODE_15:
		case CONFIGURE_CHANNEL_MODE_16:
		case CONFIGURE_CHANNEL_MODE_17:
		case CONFIGURE_CHANNEL_MODE_18:
        case CONFIGURE_CHANNEL_MODE_DISABLE:
        case CONFIGURE_CHANNEL_MODE_HW_0:
        case CONFIGURE_CHANNEL_MODE_HW_1:
        case CONFIGURE_CHANNEL_MODE_HW_2 :
        case CONFIGURE_CHANNEL_MODE_HW_3:
        {
			ProcessSetPin();
        }
			break;
		default:
			error(SW_ERROR_INVALID_COMMAND);
#ifdef TEST_COMM_VERBOSE
			printf("Invalid command received. Using default handler in ProcessRxbuffer()\n");
#endif
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
        
        memcpy(Rxbuffer,wombatI2CRxData,8);
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
        if (Rxbuffer[1] == 0x21 && Rxbuffer[0] != 0x21 )
        {
            ++debugBreakpointVariable;
        }
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




void ProcessSetPin()
{
	CurrentPin = Rxbuffer[1];
	CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
	if (CurrentPin >= NUMBER_OF_TOTAL_PINS)
	{
		//TODO error message
		return;
	}

	switch (Rxbuffer[2])
	{
		case PIN_MODE_QUADRATURE_ENC:
		{
            void initQuadEnc(void);
			initQuadEnc();		
		}
		break;

        case PIN_MODE_DEBOUNCE:
        {
            void initDebounce(void);
            initDebounce();
        }
        break;
        
		case PIN_MODE_SERVO:
		case PIN_MODE_PWM:
        case PIN_MODE_DMA_PULSE_OUTPUT:
		{
            void initPulseOut(void);
			initPulseOut();
		}
		break;
        
        case PIN_MODE_DIGITAL_IO:
        {
            uint8_t pin = Rxbuffer[1];
            CurrentPinRegister->generic.mode = PIN_MODE_DIGITAL_IO;
            SetPin(pin,Rxbuffer[3]);
                    
        }
        break;
        
        case PIN_MODE_PULSE_TIMER:
        {
            void initPulseTimer(void);
            initPulseTimer();
        }
        break;

        case PIN_MODE_WATCHDOG:
        {
            void initWatchdog(void);
            initWatchdog();
        }
        break;
	case PIN_MODE_ANALOGINPUT:
	{
        void initAnalogInput(void);
		initAnalogInput();
	}
	break;
    
        case PIN_MODE_FRAME_TIMER:
        {
            SetCurrentPin(0);
            extern uint8_t FrameTimingPin;
            FrameTimingPin = CurrentPin;
        }
        break;
        
        
    }
}
