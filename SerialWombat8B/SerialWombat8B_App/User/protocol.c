/*
Copyright 2021-2025 Broadwell Consulting Inc.


"Serial Wombat" is a registered trademark in the United States of Broadwell
Consulting Inc.

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
#include "debug.h"

extern uint16_t stayInBoot;


uint8_t i2cRxCount = 0;
uint8_t i2cTxCount = 0;
uint8_t Rxbuffer[RXBUFFER_LENGTH];
uint8_t Txbuffer[TXBUFFER_LENGTH];

// These are used for unit testing
uint32_t diagnosticTestPassed = 0;
uint32_t diagnosticTestFailed = 0;
uint8_t testSequenceNumber = 0;
bool testSequenceArmed = 0;



uint16_t lastUserBufferIndex = 0xFFFF; //Last buffer index accessed  Used for 7 Byte transfers COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE
void* lastQueueAddress = &UserBuffer[0];



static void ProcessSetPin(void);


//Storage of Error packet on Protocol error 
uint8_t lastErrorPacket[8];
uint16_t Errors = 0;




void error(SW_ERROR_t errorCode)
{
    Txbuffer[0] = 'E';
    uint16ToAscii5((uint16_t) errorCode, &Txbuffer[1]);
    Txbuffer[6] = 0x55;
    Txbuffer[7] = 0x55;
    if (Errors == 65535)
    {
        Errors = 65500;  // Knock down so it will continue changing for pulse on pin or other functions
    }
    ++ Errors;

    uint8_t i;
    for (i = 0; i < 8; ++i)
    {
	    lastErrorPacket[i] = Rxbuffer[i];
    }
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

	switch (Rxbuffer[0])
	{
		case COMMAND_DIAGNOSTIC_MESSAGE:
			{
				if (Rxbuffer[1])
				{
					++diagnosticTestPassed;
				}
				else 
				{
					++diagnosticTestFailed;
				}

			}
			break;
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
				if (((uint32_t*)Rxbuffer)[0] == 0x744F6F42 &&  // BoOt
						((uint32_t*)Rxbuffer)[1] == 0x64416F4C) //LoAd
				{
					stayInBoot = 0xB00A;
					RCC_ClearFlag();
					SystemReset_StartMode(Start_Mode_BOOT);
					NVIC_SystemReset();
				}
				else 
				{
					error(SW_ERROR_BOOT_STRING_INCORRECT);
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
			//OPTIMIZE with 32 bit constants
			Txbuffer[1] = 'S';   //Serial Wombat
			Txbuffer[2] = '0';//(uint8_t)((NUMBER_OF_PHYSICAL_PINS / 10) + '0');
			Txbuffer[3] = '8';//(uint8_t)((NUMBER_OF_PHYSICAL_PINS % 10) + '0');
			Txbuffer[4] = 'B';//SERIAL_WOMBAT_HARDWARE_IDENTIFIER;
			Txbuffer[5] = '2';
			Txbuffer[6] = '2';
			Txbuffer[7] = '1';

			break;
		case COMMAND_BINARY_READ_PIN_BUFFFER:
			{
				/** \addtogroup ProtocolBinaryCommands
				  \{

				  ----

				  Binary Read Pin Public Data Buffer Command
				  ---------------------

				  Reads the public data from three consecutive pins starting with a specified pin
				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0x81|Pin Number|0x55*|'U'*|'U'*|'U'*|'U'*|'U'*|
				 *0x55 is recommended, but any byte is acceptable

Response:

Reads the public data from three consecutive pins starting with a specified pin
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x81|Pin Number requested |Specified Pin Public Data low byte|Specified Pin Public Data High byte|Specified Pin + 1 Public Data low byte|Specified Pin + 1 Public Data High byte|Specified Pin + 2 Public Data low byte|Specified Pin + 2 Public Data High byte|

Examples:

> `0x81 0x01 0x55 0x55 0x55 0x55 0x55 0x55`

Will read the 16-bit public data from pins 1, 2 and 3.  Assuming pin1's public data was 0x481B, pin 2's was 0x38FC, and pin 3's was 0x0314:

Response:
> `0x81 0x1 0x1B 0x48 0xFC 0x38 0x14 0x03`

\}
				 **/
				uint16_t temp = GetBuffer(Rxbuffer[1]);
				TXBUFFER16(2,temp);		

			}
			break;
		case COMMAND_BINARY_SET_PIN_BUFFFER:
			{
				/** \addtogroup ProtocolBinaryCommands
				  \{

				  ----

				  Binary Set Pin Public Data Buffer Command
				  ---------------------

				  Sets the public data  for 2 pins.  (Pin number can be set to 255 to not set a pin).

				  The values returned are the values for the public data before it was changed.  This can be useful when 
				  reading an input's public data value.  For instance, when reading the position of a pin set to Rotary encoder mode,
				  the value before being set could be read, then the value set back to 32768 for center.  
				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0x82|Pin Number to set|Value Low Byte|Value High Byte|Second Pin to set|Second Value Low Byte|Second Value High Byte|'U'*|
				 *0x55 is recommended, but any byte is acceptable

Response:

Reads the public data from  the two set pins
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x82|Pin Number To set |Specified Pin Public Data low byte|Specified Pin Public Data High byte|2nd pin number|2nd pin low byte|2nd pin high byte|Echo of sent Byte 7|

Examples:

> `0x82 0x01 0xCD 0xAB 0x07 0x34 0x12 0x55`

Will set the 16-bit public data of pin 1 to 0xABCD and public data of pin 7 to 0x1234.  Assuming prior to  change pin1's public data was 0x481B, pin 7's was 0x38FC

Response:
> `0x81 0x1 0x1B 0x48 0x07 0xFC 0x38 0x55`

\}
				 **/
				uint16_t temp = GetBuffer(Rxbuffer[1]);
				TXBUFFER16(2,temp);		
				temp = GetBuffer(Rxbuffer[4] );
				TXBUFFER16(5,temp);		
				SetBuffer(Rxbuffer[1],RXBUFFER16(2));
				SetBuffer(Rxbuffer[4],RXBUFFER16(5));
			}
			break;

			/** \addtogroup ProtocolBinaryCommands
			  \{

			  ----

			  Binary Read User Buffer
			  ---------------------

			  Reads up to 7 bytes from the User Buffer User RAM area starting at an index specified.  Values past the end of User Buffer if an index less than 7 bytes from
			  the end of the User Buffer may return random data.
			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |0x83|Index Low Byte|Index High Byte|'U'*|'U'*|'U'*|'U'*|'U'*|
			 *0x55 is recommended, but any byte is acceptable

Response:

Reads 7 bytes from the  from  the specified index
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x83|Byte at Index |Byte at Index + 1 |Byte at Index + 2 |Byte at Index + 3 |Byte at Index + 4 |Byte at Index + 5 |Byte at Index + 6 |

Examples:

> `0x83 0x0A 0x01 0x55 0x55 0x55 0x55 0x55`

Read 7 bytes from User buffer starting at index 266 (0x010A)

Sample Response,  last 7 bytes will vary:
> `0x83 0x43 0x1F 0x48 0x07 0xFC 0x38 0x22`

\}
			 **/
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
					memcpy(&Txbuffer[1],&UserBuffer[address],count);
				}
				else
				{
					error(SW_ERROR_RUB_INVALID_ADDRESS);
				}
			}
			break;

			/** \addtogroup ProtocolBinaryCommands
			  \{

			  ----

			  Binary Write User Buffer
			  ---------------------

			  Writes up to 4 bytes to the User Buffer User RAM area starting at an index specified.  Commands which attempt to write past the end of the User Buffer will return an error message and have no effect .

			  This command also stores the index of the next byte in user buffer not written
			  for use by the COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE command.
			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |0x84|Index Low Byte|Index High Byte|Number of Bytes to Write|byte to write|byte to write|byte to write|byte to write|
			  0x55 is recommended for unused bytes, but any byte is acceptable

Response:

Command is echoed back

Examples:

> `0x84 0x64 0x00 0x03 0x17 0x18 0x19 0x55`

Write 3 bytes (0x17,0x18,0x19) to User buffer starting at index 100 (0x0064)


\}
			 **/
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
						memcpy(&UserBuffer[lastUserBufferIndex],&Rxbuffer[4],count);
						lastUserBufferIndex += count;
					}
					else
					{
						error(SW_ERROR_WUB_INVALID_ADDRESS);
					}
				}
			}
			break;

			/** \addtogroup ProtocolBinaryCommands
			  \{

			  ----

			  Binary Write User Buffer Continue
			  ---------------------

			  Writes 7 bytes to the User Buffer User RAM area at the next index after the last index written by the COMMAND_BINARY_WRITE_USER_BUFFER command.  Commands which attempt to write past the end of the User Buffer will return an error message and have no effect .

			  This command also stores the index of the next byte in user buffer not written
			  for use by subsequent COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE commands.
			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |0x85|byte to write |byte to write |byte to write |byte to write |byte to write|byte to write|byte to write|

Response:

Command is echoed back

Examples:

> `0x85 0x27 0x00 0x03 0x17 0x18 0x19 0x1A`

Write 7 bytes (0x27, 0x00, 0x03,0x17,0x18,0x19, 0x1A) to User buffer starting at the index following the end of the last write command


\}
			 **/
		case COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE:
			{
				if (lastUserBufferIndex < SIZE_OF_USER_BUFFER)
				{
					uint16_t count = SIZE_OF_USER_BUFFER - lastUserBufferIndex - 1;
					if (count >= 7)
					{
						count = 7;
						memcpy(&UserBuffer[lastUserBufferIndex],&Rxbuffer[1],count);
						lastUserBufferIndex += count;
					}
					else
					{
						error(SW_ERROR_WUB_CONTINUE_OUTOFBOUNDS);
					}
				}
			}
			break;

		    case COMMAND_BINARY_READ_PUBLIC_DATA_8BIT:
			{
			                    for (uint8_t i = 0; i < 7; ++i)
			                    {
			                        Txbuffer[i + 1] = (GetBuffer(i + Rxbuffer[1]) >> 8);
			                    }
			}
			break;


			/** \addtogroup ProtocolBinaryCommands
			  \{

			  ----

			  Binary Read All Pins Greater than Zero 
			  ---------------------

			  Allows a single command to poll all pins' public data to determine if
			  they are zero or greater than zero.  This command allows efficient polling
			  of Serial Wombat chips configured with a large number of inputs such
			  as GPIO input or debounced buttons.  Returns bits where 0 means the
			  pin's public data is 0, and 1 means greater than 0.  The lower pin 
			  numbers are in less significant bits.  Unimplemented pins return 0

			  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
			  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
			  |0x8F|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|
			 *0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x8F|pins 0 to 7 status|pins 8 to 15 status|pins 16 to 23 status|pins 24 to 31 status|pins 32 to 39 status|pins 40 to 47 status|pins 48 to 55 status|


Examples:

> `0x8F 0x55 0x55 0x55 0x55 0x55 0x55 0x55`

Requests pin public data status

Response assuming all pins except 1, 14 and 19 are zero:
> `0x8F 0x02 0x40 0x04 0x00 0x00 0x00 0x00`


\}
			 **/
		case COMMAND_BINARY_READ_ALL_PINS_GT_0:
			{
				Txbuffer[1] = Txbuffer[2] = Txbuffer[3] = Txbuffer[4] =
					Txbuffer[5] = Txbuffer[6] = Txbuffer[7] = 0;
				uint8_t* ptr = &Txbuffer[0];
				for (uint8_t i = 0; i < NUMBER_OF_TOTAL_PINS; ++i)
				{
					if ((i & 0x07 ) == 0)
					{
						++ptr;

					}
					if (GetBuffer(i) > 0)
					{
						*ptr |= (1 << (i & 0x07));
					}
				}
			}
			break;
#ifdef QUEUE_ENABLE
		case COMMAND_BINARY_QUEUE_INITIALIZE:
			{
				/** \addtogroup ProtocolBinaryCommands
				  \{

				  Initialize Queue
				  ---------------------
				  Initialize a queue in user memory 
				  Queue types are as follows:  
				  0 - Byte data queue in RAM
				  1 - Byte data using shifted QUEUE in RAM (Write only, no read, used for Displays and similar)

				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0x90 |Queue Address LSB |Queue Address MSB |Size LSB|Size MSB|Queue Type|Varies|Varies|

Response: 
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x90 |Queue Address LSB |Queue Address MSB |Used Size LSB|Used Size MSB|Queue Type|Varies|Varies| 


Examples:

`0x90 0x0010 0x0020 0 0 0`

Initializes a ram queue of 32 bytes at address 0x0010 in user memory.

\}
				 **/
				SW_QUEUE_RESULT_t result;
				switch (Rxbuffer[5])
				{
					case 0:
					case 1:
						{
							lastQueueAddress = queueAddress = &UserBuffer[RXBUFFER16(1)];
							result = QueueByteInitialize(RXBUFFER16(3));
						}
						break;

					default:
						{
							error(SW_ERROR_UNKNOWN_QUEUE_TYPE);
							return;
						}
						break;
				}

				if (result == QUEUE_RESULT_SUCCESS)
				{
					uint16_t length = RXBUFFER16(3) + 8;
					TXBUFFER16(3,length);
				}
				else
				{
					TXBUFFER16(3,0);
					Txbuffer[5] = (uint8_t)result;
				}
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

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x90 |Queue Address LSB |Queue Address MSB |Number added| Queue Result Code | Free bytes after add LSB | Free Bytes after add MSB| 0x55|

Examples:

`0x90 0x0010 4 0x31 0x32 0x33 0x34`

Add bytes 0x31, 0x32, 0x33, and 0x34 to queue located at 0x0010.

\}
				 **/
				uint8_t i;
				bool success = true;

				uint8_t successCount = 0;
				SW_QUEUE_RESULT_t result = 0;
				lastQueueAddress =  queueAddress = &UserBuffer[RXBUFFER16(1)];
				for (i = 0; i < Rxbuffer[3] && success ; ++i)
				{
					result =QueueAddByte(Rxbuffer[4 + i]);
					success = result == QUEUE_RESULT_SUCCESS;
					if (success)
					{
						++successCount;
					}
				}
				Txbuffer[3] = successCount;
				Txbuffer[4] = result;
				uint16_t freeBytes;
				QueueGetBytesFreeInQueue(&freeBytes);
				TXBUFFER16(5,freeBytes);
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
				 * 
				 *  Response:

				 |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				 |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				 |0x91 |Queue Address LSB |Queue Address MSB |Number added| Queue Result Code | Free bytes after add LSB | Free Bytes after add MSB| 0x55|

Examples:

`0x92 0x35 0x36 0x37 0x38 0x39 0x3A 0x3B`

Add bytes 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A and 0x3B to queue last added to.

\}
				 **/
				uint8_t i;
				bool success = true;
				uint8_t successCount = 0;
				SW_QUEUE_RESULT_t result = 0;
				queueAddress = lastQueueAddress;
				for (i = 0; i < 7 && success ; ++i)
				{
					result =QueueAddByte(Rxbuffer[1 + i]);
					success = result == QUEUE_RESULT_SUCCESS;
					if (success)
					{
						++successCount;
					}
				}
				Txbuffer[3] = successCount;
				Txbuffer[4] = result;
				uint16_t freeBytes;
				QueueGetBytesFreeInQueue(&freeBytes);
				TXBUFFER16(5,freeBytes);

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


Response :
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x93 |Number of Bytes read from Queue|Data Byte|Data Byte|Data Byte|Data Byte|Data Byte|Data Byte|

Note:  If Byte 1 is 5 or less, then byte 7 will contain the last queue result.
Examples:


`0x93 0x0170 0x04 0x20 0x20 0x20 0x20`

Read up to 6 bytes from queue at address 0x0170

Sample Response:
`0x93 0x02 0x34 0x35 0x20 0x20 0x20 0x20` 

Two bytes were available in the queue.  0x34, and 0x35

				 * TODO:  Make rx[1] equal to total bytes avaialble or 255

				 \}
				 **/
				SW_QUEUE_RESULT_t result = QUEUE_RESULT_SUCCESS;
				uint8_t i;
				Txbuffer[1] = 0;
				lastQueueAddress = queueAddress = &UserBuffer[RXBUFFER16(1)];
				for (i = 0; i < Rxbuffer[3] && result == QUEUE_RESULT_SUCCESS; ++i)
				{
					result = (SW_QUEUE_RESULT_t) QueueReadByte(&Txbuffer[2 + i]);
					if (result == QUEUE_RESULT_SUCCESS)
					{
						++Txbuffer[1];
					}
				}

				if (i <= 5)
				{
					Txbuffer[7] = (uint8_t) result;
				}
			}
			break;

		case COMMAND_BINARY_QUEUE_GET_INFO:
			{
				/** \addtogroup ProtocolBinaryCommands
				  \{

				  Peek the first byte from the queue without removing it.  Get the number of available bytes to read and free space.
				  ---------------------

				  |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
				  |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
				  |0x94 |Queue Address LSB|Queue Address MSB|Unused|Unused|Unused|Unused|Unused|


Response :
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x94 |Queue Address LSB|Queue Address MSB|Peeked Byte| Bytes Available to Read LSB |Bytes Available to Read MSB |Free Bytes LSB | Free Bytes MSB|


Note:  Ignore peeked value if Bytes Available == 0.
Example:  

`0x94 0x70 0x01 0x55 0x55 0x55 0x55 0x55`

Peek byte from queue at address 0x0170

Sample Response:


`0x94 0x70 0x01 0x37 0x80 0x01 0xF4 0x01` 

Next byte is 0x37 .  384 bytes available to read, 500 bytes Free

\}
				 **/
				uint16_t bytesFree = 0;
				uint16_t bytesAvailable = 0;
				SW_QUEUE_RESULT_t result = QUEUE_RESULT_SUCCESS;
				lastQueueAddress = queueAddress = &UserBuffer[RXBUFFER16(1)];	
				result = (SW_QUEUE_RESULT_t) QueuePeekByte(&Txbuffer[3]);

				if (result == QUEUE_RESULT_SUCCESS)
				{

					QueueGetBytesFilledInQueue( &bytesAvailable);
					QueueGetBytesFreeInQueue( &bytesFree);
				}
				else if (result == QUEUE_RESULT_EMPTY)
				{
					QueueGetBytesFreeInQueue( &bytesFree);
				}
				TXBUFFER16(4,bytesAvailable);
				TXBUFFER16(6,bytesFree);

			}
			break;
#endif

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
				uint32_t addr = RXBUFFER32(1);
				Txbuffer[3] = *(uint8_t*)addr;
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
				uint32_t addr = RXBUFFER32(2);
				*(uint8_t*)addr = Rxbuffer[1];
			}
			break;

#ifdef PROTOCOL_BINARY_TEST_SEQUENCE_ENABLE
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
#ifdef __DEBUG
						if (Txbuffer[i] != testSequenceNumber && testSequenceArmed)
						{

							__builtin_software_breakpoint();
							testSequenceArmed = 0;
							/* If we are in debug mode, cause a software breakpoint in the debugger */

						}
#endif
						++testSequenceNumber;
					}
				}
			}
			break;
#endif

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
			}
			break;



		case COMMAND_READ_LAST_ERROR_PACKET:
			{
				Txbuffer[1] = lastErrorPacket[0];
				Txbuffer[2] = lastErrorPacket[1];
				Txbuffer[3] = lastErrorPacket[2];
				Txbuffer[4] = lastErrorPacket[3];
				Txbuffer[5] = lastErrorPacket[4];
				Txbuffer[6] = lastErrorPacket[5];
				Txbuffer[7] = lastErrorPacket[6];
			}
			break;


#ifdef PIN_MODE_UART0_TXRX_ENABLE
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
				queueAddress =  &PinUpdateRegisters[4];   //Hard Coded to TX pin

				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
				{
					int16_t i;
					for (i = 1; i <= 7; ++i)
					{
						QueueAddByte(Rxbuffer[i]);
					}
				}
				USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
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
				USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
				queueAddress =  &PinUpdateRegisters[5];   //Hard Coded to RX pin
				{
					int16_t i;
					for (i = 1; i <=7; ++i)
					{
						QueueReadByte(&Txbuffer[i]);
					}
				}

				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			}
			break;
#endif

		case COMMAND_BINARY_SET_COMMUNICATION_ADDRESS:
			{
				uint32_t tempUB[4];
				memcpy(tempUB,(void*)0x1FFFF800,16);
				FLASH_EraseOptionBytes();
				tempUB[1] &= 0xFFFFFF00;
				tempUB[1] |= Rxbuffer[1];
				FLASH_ProgramOptionByteData(0x1FFFF800,(tempUB[0] & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF802,((tempUB[0] >>16) & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF804,(tempUB[1] & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF806,((tempUB[1] >>16) & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF808,(tempUB[2] & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF80A,((tempUB[2] >>16) & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF80C,(tempUB[3] & 0xFF));
				FLASH_ProgramOptionByteData(0x1FFFF80E,((tempUB[3] >>16) & 0xFF));
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


#define FLAG_Mask                ((uint32_t)0x00FFFFFF)
#define ITEN_Mask                ((uint32_t)0x07000000)

#define I2C_GetITStatusSmall(I2C_IT )  (( (I2C1->STAR1 & I2C_IT) ) && ((uint32_t)(((I2C_IT & ITEN_Mask) >> 16) & (I2C1->CTLR2))))

#define I2C_ReceiveData(_dummy) ((uint8_t)I2C1->DATAR)

volatile uint8_t debugLastInterruptAction = 2;

#define I2C_MODE_INIT 0
#define I2C_MODE_RECEIVING 1
#define I2C_MODE_TRANSMITTING 2
uint16_t i2cMode = 0; // 0 = INIT, 1 = Receiving, 2 = Transmitting

volatile I2C_TypeDef *i2cDebugPtr;
uint16_t star1;
void ProcessRx(void)
{
	i2cDebugPtr = I2C1;
	volatile uint16_t x; // Used for delay


	uint8_t loop = 1;
	while (loop)
	{
		//  for (x = 0; x < 500; ++x); //Debug
		star1 = I2C1->STAR1;
		while (i2cMode == I2C_MODE_RECEIVING && (star1 & 0x040)) // RxNE
		{
			if (i2cRxCount > 5)
			{
				for (x = 0; x < 1000; ++x); //  This delay seems to help prevent bus lockups due to missed last byte before stop
			}
			Rxbuffer[i2cRxCount] = I2C1->DATAR;

			++i2cRxCount;
			if (i2cRxCount == 8)
			{
				ProcessRxbuffer();
				i2cRxCount = 0;
				i2cTxCount = 0;
			}
			star1 = I2C1->STAR1;
		}

		if (i2cMode == I2C_MODE_TRANSMITTING && (star1 & 0x80)) //TxE
		{
			I2C1->DATAR = Txbuffer[i2cTxCount];
			++i2cTxCount;
		}
		else if ((star1 & 0x02) && !(star1 & 0x040))  //Address bit set  and RXNE not
		{
			if (i2cRxCount == 7)
			{
				for (x = 0; x < 500; ++x); //Debug
			}
			if ( i2cRxCount == 0)
			{
				uint16_t tra  = I2C1->STAR2 & 0x04;  //Reading STAR1 and STAR 2 clears bit.
				i2cRxCount = 0;
				i2cTxCount = 0;

				if (tra == 0)
				{
					i2cMode = I2C_MODE_RECEIVING;
				}
				else 
				{
					i2cMode = I2C_MODE_TRANSMITTING;
					I2C1->DATAR = Txbuffer[i2cTxCount];
					++i2cTxCount;
				}
			}
		}
		else {
			loop = 0;
		}
	}
}




static void ProcessSetPin()
{
	CurrentPin = Rxbuffer[1];

	if (CurrentPin >= NUMBER_OF_TOTAL_PINS)
	{
		error(SW_ERROR_PIN_NUMBER_TOO_HIGH);
		return;
	}
    CurrentPinRegister = &PinUpdateRegisters[CurrentPin];

	switch (Rxbuffer[2])  // Pin mode service
	{
        case PIN_MODE_DIGITAL_IO:
        {
		void initDigitalIO(void);
		initDigitalIO();
		/*
            uint8_t pin = Rxbuffer[1];
            CurrentPinRegister->generic.mode = PIN_MODE_DIGITAL_IO;
            SetPin(pin,Rxbuffer[3]);
            if (Rxbuffer[4] == 1)
            {
                PinPullUp(pin);
            }
            else
            {
                PinNoPullUp(pin);
            }
            if (Rxbuffer[5] == 1)
            {
                PinPullDown(pin);
            }
            else
            {
                PinNoPullDown(pin);
            }
           if (Rxbuffer[6] == 1)
            {
                PinOD(pin);
            }
            else
            {
                PinNoOD(pin);
            }
                 */   
        }
        break;
#ifdef PIN_MODE_QUADRATURE_ENC_ENABLE
        case PIN_MODE_QUADRATURE_ENC:
                      {
                          void initQuadEnc(void);
                          initQuadEnc();
                      }
                      break;
#endif

#ifdef PIN_MODE_SERVO_ENABLE
        case PIN_MODE_SERVO:
                {
                    void initServoHw(void);
                    initServoHw();
                }
                break;
#endif

#ifdef PIN_MODE_PWM_ENABLE
        case PIN_MODE_PWM:
                {
                    void initPWM(void);
                    initPWM();
                }
                break;
#endif

#ifdef PIN_MODE_ANALOGINPUT_ENABLE
        case PIN_MODE_ANALOGINPUT:
            {
                void initAnalogInput(void);
                initAnalogInput();
            }
            break;
#endif

#ifdef PIN_MODE_FRAME_TIMER_ENABLE
        case PIN_MODE_FRAME_TIMER:
              {
                  SetCurrentPin(0);
                  extern uint8_t FrameTimingPin;
                  FrameTimingPin = CurrentPin;
              }
              break;
#endif

#ifdef PIN_MODE_DEBOUNCE_ENABLE
        case PIN_MODE_DEBOUNCE:
               {
                   void initDebounce(void);
                   initDebounce();
               }
               break;
#endif

#ifdef PIN_MODE_SW_UART_ENABLE

        case PIN_MODE_SW_UART:
               {
                   extern void initUARTSw(void);
                   initUARTSw();

               }
               break;
#endif

#ifdef PIN_MODE_MATRIX_KEYPAD_ENABLE

        case PIN_MODE_MATRIX_KEYPAD:
           {
               void initMatrixKeypad(void);
               initMatrixKeypad();
           }
           break;
#endif


#ifdef PIN_MODE_HBRIDGE_ENABLE
        case PIN_MODE_HBRIDGE:
                    {
                        void inithBridge(void);
                        inithBridge();
                    }
                    break;
#endif

#ifdef PIN_MODE_TM1637_ENABLE
        case PIN_MODE_TM1637:
                      {
                          extern void initTM1637();
                          initTM1637();
                      }
                      break;

#endif
#ifdef PIN_MODE_THROUGHPUT_CONSUMER_ENABLE
        case PIN_MODE_THROUGHPUT_CONSUMER:
        {
            void initThroughputConsumer();
            initThroughputConsumer();
        }
        break;
#endif 

        
#ifdef PIN_MODE_HF_SERVO_ENABLE
		case PIN_MODE_HF_SERVO:
        {
            void initHfServo(void);
            initHfServo();
        }
        break;
#endif
      
        
#ifdef PIN_MODE_PULSE_TIMER_ENABLE   
        case PIN_MODE_PULSE_TIMER:
        {
            void initPulseTimer(void);
            initPulseTimer();
        }
        break;
#endif

#ifdef PIN_MODE_ULTRASONIC_DISTANCE_ENABLE
        case PIN_MODE_ULTRASONIC_DISTANCE:
        {
            void initUltrasonicDistance(void);
            initUltrasonicDistance();
        }
        break;
#endif

#ifdef PIN_MODE_INPUT_PROCESSOR_ENABLE
        case PIN_MODE_INPUT_PROCESSOR:
        {
            void initPinInputProcessor(void);
            initPinInputProcessor();
        }
        break;
#endif

#ifdef PIN_MODE_WATCHDOG_ENABLE
        case PIN_MODE_WATCHDOG:
        {
            void initWatchdog(void);
            initWatchdog();
        }
        break;
#endif

#ifdef PIN_MODE_WS2812_ENABLE
	case PIN_MODE_WS2812:
        {
            extern void initWS2812();
            initWS2812();
        }
        break;
#endif

#ifdef PIN_MODE_TOUCH_ENABLE
        case PIN_MODE_TOUCH:
        {
            extern void initTouch();
            initTouch();
        }
        break;
#endif
     
#ifdef PIN_MODE_PULSE_ON_CHANGE_ENABLE
        case PIN_MODE_PULSE_ON_CHANGE:
            {
                extern void initPulseOnChange();
                initPulseOnChange();
            }
            break;
#endif

#ifdef PIN_MODE_LIQUID_CRYSTAL_ENABLE	    
            case PIN_MODE_LIQUID_CRYSTAL:
            {
                extern void initLiquidCrystal();
                initLiquidCrystal();
            }
            break;
#endif

#ifdef PIN_MODE_RESISTANCE_INPUT_ENABLE
        case PIN_MODE_RESISTANCE_INPUT:
            {
                extern void initResistanceInput(void);
               initResistanceInput();
            }
            break;
#endif
    
#ifdef PIN_MODE_PROTECTEDOUTPUT_ENABLE	    
              case PIN_MODE_PROTECTEDOUTPUT:
            {
                extern void initProtectedOutput(void);
               initProtectedOutput();
            }
            break;
#endif 

#ifdef PIN_MODE_UART0_TXRX_ENABLE
        case PIN_MODE_UART0_TXRX:
        {
            extern void initUARTHw(void);
            initUARTHw();
        }
        break;
#endif

#ifdef PIN_MODE_HS_CLOCK_ENABLE
        
        case PIN_MODE_HS_CLOCK:
        {
            extern void initHSClock(void);
            initHSClock();
        }
        break;
#endif

#ifdef PIN_MODE_HS_COUNTER_ENABLE	
        case PIN_MODE_HS_COUNTER:
        {
            extern void initHSCounter(void);
            initHSCounter();
        }
        break;
#endif

#ifdef PIN_MODE_VGA_ENABLE	
        case PIN_MODE_VGA:
        {
            extern void initVGA(void);
            initVGA();
        }
        break;
#endif
     
#ifdef PIN_MODE_I2C_CONTROLLER_ENABLE
        case PIN_MODE_I2C_CONTROLLER:
        {
            extern void initI2CController(void);
            initI2CController();
        }
        break;
#endif

#ifdef PIN_MODE_QUEUED_PULSE_OUTPUT_ENABLE
        case PIN_MODE_QUEUED_PULSE_OUTPUT:
        {
            extern void initQueuedPulseOutput(void);
            initQueuedPulseOutput();
        }
        break;
#endif

#ifdef PIN_MODE_FREQUENCY_OUTPUT_ENABLE
	case PIN_MODE_FREQUENCY_OUTPUT:
	{
		extern void initFrequencyOutput(void);
		initFrequencyOutput();

	}
	break;
#endif

#ifdef PIN_MODE_PS2_KEYBOARD_ENABLE
        
	case PIN_MODE_PS2_KEYBOARD:
	{
		extern void initPS2Keyboard(void);
		initPS2Keyboard();
	}
	break;
#endif

#ifdef PIN_MODE_MAX7219MATRIX_ENABLE

	case PIN_MODE_MAX7219MATRIX:
	{
		extern void initMax7219Matrix(void);
		initMax7219Matrix();

	}
	break;
#endif
        
       
        default:
        {
            error(SW_ERROR_UNKNOWN_PIN_MODE);
        }
        break;
    }
}

void protocolInitPinsToDIO_Input()
{
Rxbuffer[0] = CONFIGURE_CHANNEL_MODE_0;
   Rxbuffer[2] = PIN_MODE_DIGITAL_IO;
   Rxbuffer[3] = 2; //Input
   Rxbuffer[4] = 0; // No Pull up
   Rxbuffer[5] = 0; // No Pull Down
   Rxbuffer[6] = 0; // Not Open Drain
   Rxbuffer[7] = 0x55;  //Unused
   for (uint8_t i = 1; i < NUMBER_OF_TOTAL_PINS; ++i ) // Skip 0, or we lock out of debug mode
   {
       Rxbuffer[1] = i;
       ProcessSetPin();
   }
}
