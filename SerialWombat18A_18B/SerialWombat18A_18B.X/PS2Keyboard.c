/*
Copyright 2023 Broadwell Consulting Inc.

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
#include "serialWombat.h"
#include <stdint.h>


#define PS2KB_QUEUE_LENGTH 16   ///< Length in 16 bit words
typedef struct PS2Keyboard_n{

    uint16_t queue[PS2KB_QUEUE_LENGTH];  ///< A buffer used to hold queued bytes, or in the case of PS2KEYBOARD_QUEUEDATA_CURRENTLY_PRESSED an array of 256 bits
    uint16_t queueAddress;  ///< An address if you want to use an external queue defined in the User memory area instead of the in-pin queue
    uint16_t bytesProcessed ; ///< The number of bytes processed by the PS2 processor.  Includes make, break, and extended bytes
    uint8_t bytesInQueue; ///< The number of bytes available in the in-pin queue
    uint8_t queueDataMode; ///< The mode of the data queue.  See enumerated types PS2KEYBOARD_QUEUEDATA_t
           uint8_t lastNextDMA; ///< Used to store the next DMA location to be read
           uint8_t dataPin; ///< The pin connected to the PS2 data line (clock line is the pin running the state machine)
	   uint8_t state; ///<  Current PS2 Decoding state
	   uint8_t data; ///<  Current data byte being assembled by the PS2 State machine
       uint8_t lastCodeBreak:1; ///<  A Break code has been received prior to the key code
       uint8_t lastCodeExtended:1; ///< An Extended code has been received prior to the key code
       uint8_t leftShiftActive:1; ///< Left shift is currently pressed
       uint8_t rightShiftActive:1; ///< Right shift is currently pressed
       uint8_t publicDataOutput:2; ///< Public data output:  0 outputs the last non extended make code:  1 - Outputs Ascii of the last make code 2- Increments on each make
}PS2Keyboard_t;


typedef enum 
{
    PS2KEYBOARD_QUEUEDATA_ASCII = 0, ///< Queue the data in ASCII, taking into account the shift key
    PS2KEYBOARD_QUEUEDATA_MAKE_CODES = 1, ///<  Queue only the Make codes
    PS2KEYBOARD_QUEUEDATA_ALL_CODES = 2, ///<  Queue all codes, make and break
    PS2KEYBOARD_QUEUEDATA_CURRENTLY_PRESSED = 3,  ///<  Use the queue area as a 256 bit field
}PS2KEYBOARD_QUEUEDATA_t;

typedef enum
{
	PS2KB_STATE_IDLE = 0,
	PS2KB_STATE_WAITING_FOR_START_RISE = 1,
	PS2KB_STATE_WAITING_FOR_DATA0_FALL = 2,
	PS2KB_STATE_WAITING_FOR_DATA0_RISE = 3,
	PS2KB_STATE_WAITING_FOR_DATA1_FALL = 4,
	PS2KB_STATE_WAITING_FOR_DATA1_RISE = 5,
	PS2KB_STATE_WAITING_FOR_DATA2_FALL = 6,
	PS2KB_STATE_WAITING_FOR_DATA2_RISE = 7,
	PS2KB_STATE_WAITING_FOR_DATA3_FALL = 8,
	PS2KB_STATE_WAITING_FOR_DATA3_RISE = 9,
	PS2KB_STATE_WAITING_FOR_DATA4_FALL = 10,
	PS2KB_STATE_WAITING_FOR_DATA4_RISE = 11,
	PS2KB_STATE_WAITING_FOR_DATA5_FALL = 12,
	PS2KB_STATE_WAITING_FOR_DATA5_RISE = 13,
	PS2KB_STATE_WAITING_FOR_DATA6_FALL = 14,
	PS2KB_STATE_WAITING_FOR_DATA6_RISE = 15,
	PS2KB_STATE_WAITING_FOR_DATA7_FALL = 16,
	PS2KB_STATE_WAITING_FOR_DATA7_RISE = 17,
	PS2KB_STATE_WAITING_FOR_PARITY_FALL = 18,
	PS2KB_STATE_WAITING_FOR_PARITY_RISE = 19,
	PS2KB_STATE_WAITING_FOR_STOP_FALL = 20,
	PS2KB_STATE_WAITING_FOR_STOP_RISE = 21,
	PS2KB_STATE_WAITING_FOR_IDLE0 = 246,
	PS2KB_STATE_WAITING_FOR_IDLE1 = 247,
	PS2KB_STATE_WAITING_FOR_IDLE2 = 248,
	PS2KB_STATE_WAITING_FOR_IDLE3 = 249,
	PS2KB_STATE_WAITING_FOR_IDLE4 = 250,
	PS2KB_STATE_WAITING_FOR_IDLE5 = 251,
	PS2KB_STATE_WAITING_FOR_IDLE6 = 252,
	PS2KB_STATE_WAITING_FOR_IDLE7 = 253,
	PS2KB_STATE_WAITING_FOR_IDLE8 = 254,
	PS2KB_STATE_WAITING_FOR_IDLE9 = 255,
}
PS2KeyboardState_t;


/// This array is used to convert PS2 Code set 2 codes to Ascii. The first column is unshfited data, the second if shift is active
const uint8_t KBSCSet2[][2] = 
{
{ ' ' , ' ' },  /* 0 */
{ ' ' , ' ' },  /* 1 */
{ ' ' , ' ' },  /* 2 */
{ ' ' , ' ' },  /* 3 */
{ ' ' , ' ' },  /* 4 */
{ ' ' , ' ' },  /* 5 */
{ ' ' , ' ' },  /* 6 */
{ ' ' , ' ' },  /* 7 */
{ ' ' , ' ' },  /* 8 */
{ ' ' , ' ' },  /* 9 */
{ ' ' , ' ' },  /* A */
{ ' ' , ' ' },  /* B */
{ ' ' , ' ' },  /* C */
{ 9 , 9 },  /* D */
{ '`' , '~' },  /* E */
{ ' ' , ' ' },  /* F */
{ ' ' , ' ' },  /* 10 */
{ ' ' , ' ' },  /* 11 */
{ 0 , 0 },  /* 12 */
{ ' ' , ' ' },  /* 13 */
{ ' ' , ' ' },  /* 14 */
{ 'q' , 'Q' },  /* 15 */
{ '1' , '!' },  /* 16 */
{ ' ' , ' ' },  /* 17 */
{ ' ' , ' ' },  /* 18 */
{ ' ' , ' ' },  /* 19 */
{ 'z' , 'Z' },  /* 1A */
{ 's' , 'S' },  /* 1B */
{ 'a' , 'A' },  /* 1C */
{ 'w' , 'W' },  /* 1D */
{ '2' , '@' },  /* 1E */
{ ' ' , ' ' },  /* 1F */
{ ' ' , ' ' },  /* 20 */
{ 'c' , 'C' },  /* 21 */
{ 'x' , 'X' },  /* 22 */
{ 'd' , 'D' },  /* 23 */
{ 'e' , 'E' },  /* 24 */
{ '4' , '$' },  /* 25 */
{ '3' , '#' },  /* 26 */
{ ' ' , ' ' },  /* 27 */
{ ' ' , ' ' },  /* 28 */
{ ' ' , ' ' },  /* 29 - SPACE */
{ 'v' , 'V' },  /* 2A */
{ 'f' , 'F' },  /* 2B */
{ 't' , 'T' },  /* 2C */
{ 'r' , 'R' },  /* 2D */
{ '5' , '%' },  /* 2E */
{ ' ' , ' ' },  /* 2F */
{ ' ' , ' ' },  /* 30 */
{ 'n' , 'N' },  /* 31 */
{ 'b' , 'B' },  /* 32 */
{ 'h' , 'H' },  /* 33 */
{ 'g' , 'G' },  /* 34 */
{ 'y' , 'Y' },  /* 35 */
{ '6' , '^' },  /* 36 */
{ ' ' , ' ' },  /* 37 */
{ ' ' , ' ' },  /* 38 */
{ ' ' , ' ' },  /* 39 */
{ 'm' , 'M' },  /* 3A */
{ 'j' , 'J' },  /* 3B */
{ 'u' , 'U' },  /* 3C */
{ '7' , '&' },  /* 3D */
{ '8' , '*' },  /* 3E */
{ ' ' , ' ' },  /* 3F */
{ ' ' , ' ' },  /* 40 */
{ ',' , '>' },  /* 41 */
{ 'k' , 'K' },  /* 42 */
{ 'i' , 'I' },  /* 43 */
{ 'o' , 'O' },  /* 44 */
{ '0' , ')' },  /* 45 */
{ '9' , '(' },  /* 46 */
{ ' ' , ' ' },  /* 47 */
{ ' ' , ' ' },  /* 48 */
{ '.' , '<' },  /* 49 */
{ '/' , '?' },  /* 4A */
{ 'l' , 'L' },  /* 4B */
{ ';' , ':' },  /* 4C */
{ 'p' , 'P' },  /* 4D */
{ '-' , '_' },  /* 4E */
{ ' ' , ' ' },  /* 4F */
{ ' ' , ' ' },  /* 50 */
{ ' ' , ' ' },  /* 51 */
{ '\'' , '"' },  /* 52 */
{ ' ' , ' ' },  /* 53 */
{ '[' , '{' },  /* 54 */
{ '=' , '+' },  /* 55 */
{ ' ' , ' ' },  /* 56 */
{ ' ' , ' ' },  /* 57 */
{ ' ' , ' ' },  /* 58 */
{ 0 , 0 },  /* 59 */
{ 0xD , 0xD },  /* 5A */
{ ']' , '}' },  /* 5B */
{ ' ' , ' ' },  /* 5C */
{ '\\' , '|' },  /* 5D */
{ ' ' , ' ' },  /* 5E */
{ ' ' , ' ' },  /* 5F */
{ ' ' , ' ' },  /* 60 */
{ ' ' , ' ' },  /* 61 */
{ ' ' , ' ' },  /* 62 */
{ ' ' , ' ' },  /* 63 */
{ ' ' , ' ' },  /* 64 */
{ ' ' , ' ' },  /* 65 */
{ 8 , 8 },  /* 66 */
{ ' ' , ' ' },  /* 67 */
{ ' ' , ' ' },  /* 68 */
{ '1' , '1' },  /* 69 */
{ ' ' , ' ' },  /* 6A */
{ '4' , '4' },  /* 6B */
{ '7' , '7' },  /* 6C */
{ ' ' , ' ' },  /* 6D */
{ ' ' , ' ' },  /* 6E */
{ ' ' , ' ' },  /* 6F */
{ '0' , '0' },  /* 70 */
{ ' ' , ' ' },  /* 71 */
{ '2' , '2' },  /* 72 */
{ '5' , '5' },  /* 73 */
{ '6' , '6' },  /* 74 */
{ '8' , '8' },  /* 75 */
{ 0x1B , 0x1B },  /* 76 */
{ ' ' , ' ' },  /* 77 */
{ ' ' , ' ' },  /* 78 */
{ ' ' , ' ' },  /* 79 */
{ '3' , '3' },  /* 7A */
{ ' ' , ' ' },  /* 7B */
{ ' ' , ' ' },  /* 7C */
{ '9' , '9' },  /* 7D */
{ ' ' , ' ' },  /* 7E */
{ ' ' , ' ' },  /* 7F */

	};

#define LEFT_SHIFT_CODE 0x12
#define RIGHT_SHIFT_CODE 0x59

static uint8_t localQueueBytesAvailable()
{
    PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;
    return (PS2Keyboard->bytesInQueue);
}


/// \brief Get one byte out of the local queue
static bool localShiftByte(uint8_t* data)
{
    PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;
    
    if (PS2Keyboard->bytesInQueue == 0) return false;
    
    *data = PS2Keyboard->queue[0];
    int i;
    for (i = 1; i < PS2KB_QUEUE_LENGTH; ++i)
    {
        PS2Keyboard->queue[i-1] = PS2Keyboard->queue[i];
    }
    --PS2Keyboard->bytesInQueue;
    return(true);
}

/// \brief Add one byte to the local queue
static void localPushByte(uint8_t data)
{
    PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;
    if (PS2Keyboard->bytesInQueue < PS2KB_QUEUE_LENGTH)
    {
        PS2Keyboard->queue[PS2Keyboard->bytesInQueue] = data;
        ++ PS2Keyboard->bytesInQueue;
    }
}

/*!
\brief initialize the PS2 Keyboard pin mode

----

 * Configuration of PS2 Keboard
-------------------------------

Configure a pair of pins to be PS2 Keyboard pins.  The pins must be on the same physical port (0,5,6,8) or (1,2,3,4,7,9-19),
and use of 5V tolerant pins (10-12,14,15) is reccommended. 

This pin mode uses DMA based sampling, and consumes a significant amount 10-25% of the Serial Wombat 18AB's processing time

-----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Analog Input.  Disables averaged and filtered values.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) | Data Pin |Queue Mode |Public Data Mode |0x55* |Internal Pull Up enable  |

\*0x55 is recommended, but any byte is acceptable

See PS2KEYBOARD_QUEUEDATA_t for queue modes.

Public data mode = 0 puts the ascii of the last make code as public data
Public data mode = 1 puts the raw last make code as public data

Internal pull ups are recommened to be turned off, and external pull up resistors to 5V used.


Response:

Command is echoed back.

Examples:

Set pin 10 to PS2 Keyboard, with pin 11 as the data pin,  Queue Ascii values, output ascii as public data, pull ups off

> `0xC0 0x0A 0x20 0x0B 0x00 0x00 0x55 0x00 `


CONFIGURE_CHANNEL_MODE_2:
---------------------

Read bytes from queue


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |Maximum Bytes to Read (up to 4) |0x55* |0x55* | 0x55* |0x55* | 

\*0x55 is recommended, but any byte is acceptable


Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |Number of bytes read |Read Data or Echo |Read Data or Echo | Read Data or Echo |Read Data or Echo | 

Examples:

Read up to 3 bytes from queue

> `0xC2 0x0A 0x20 0x03 0x55 0x55 0x55 0x55 `

Response:
2 bytes were available:  0x31 and 0x32
> `0xC2 0x0A 0x20 0x02 0x31 0x32 0x55 0x55 `


CONFIGURE_CHANNEL_MODE_3:
---------------------

Peek Bytes in Queue


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |0x55 |0x55* |0x55* | 0x55* |0x55* | 

\*0x55 is recommended, but any byte is acceptable


Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |0|  Bytes Available to Read | Next byte to read| 0x55* |0x55* | 

Examples:

Peak Queue

> `0xC3 0x0A 0x20 0x55 0x55 0x55 0x55 0x55 `

Response:
2 bytes were available, next byte is :  0x31 
> `0xC2 0x0A 0x20 0x00 0x02 0x31  0x55 0x55 `

CONFIGURE_CHANNEL_MODE_6:
---------------------

Set the index of a queue in the User Ram Area


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC6|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |Queue Index LSB |Queue Index MSB |0x55* | 0x55* |0x55* | 

\*0x55 is recommended, but any byte is acceptable


Examples:

Use a queue created at user memory index 0x780

> `0xC6 0x0A 0x20 0x80 0x07 0x55 0x55 0x55 `

Response:

Command is echoed back.


CONFIGURE_CHANNEL_MODE_7:
---------------------

Get currently pressed keys (only when queue mode is PS2KEYBOARD_QUEUEDATA_CURRENTLY_PRESSED)


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC7|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |First scan code to check |0x55| 0x55* | 0x55* |0x55* | 

\*0x55 is recommended, but any byte is acceptable


Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC7|Pin To Set (Keyboard Clock Pin)|0x20 (PS2 Keyboard Mode) |Scan code or 0 |Scan code or 0| Scan code or 0| Scan code or 0|Scan code or 0| 

Extended scan codes are indicated by setting the 0x80 bit.

\*0x55 is recommended, but any byte is acceptable


Examples:

Get currently pressed keys starting with scan code 0x00

> `0xC7 0x0A 0x20 0x00 0x55 0x55 0x55 0x55 `

Response:

Key Codes for spacebar (0x29)  and right arrow (extended 0x74 -> 0xF4) are currently pressed

> `0xC7 0x0A 0x20 0x29 0xF4 0x00 0x00 0x00 `
*/
void initPS2Keyboard()
{
	PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PS2_KEYBOARD)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:

			{
				if (pinPort[Rxbuffer[3]] != CurrentPinPort())
				{
					//Pins must be on same port
					CurrentPinRegister->generic.mode = PIN_MODE_CONTROLLED;
					error(SW_ERROR_PINS_MUST_BE_ON_SAME_PORT);
					return;
				}
				CurrentPinRegister->generic.mode =PIN_MODE_PS2_KEYBOARD;
				PS2Keyboard->dataPin = Rxbuffer[3] ;
				PS2Keyboard->queueDataMode = Rxbuffer[4];
				SetMode(PS2Keyboard->dataPin, PIN_MODE_CONTROLLED);
				CurrentPinRegister->generic.buffer = 0; 
				PS2Keyboard->state = PS2KB_STATE_WAITING_FOR_IDLE0;
				CurrentPinInput();
				PinInput(PS2Keyboard->dataPin);
				PS2Keyboard->data = 0;
				PS2Keyboard->queueAddress = 0xFFFF;  // Use pin-mode queue
				PS2Keyboard->bytesInQueue = 0;
				PS2Keyboard->lastCodeBreak = 0;
				PS2Keyboard->lastCodeExtended= 0;
				PS2Keyboard->leftShiftActive= 0;
				PS2Keyboard->rightShiftActive= 0;
				PS2Keyboard->bytesProcessed = 0;
				{ // Clear the queue for currently pressed mode
					int i;
					for (i = 0; i < PS2KB_QUEUE_LENGTH; ++ i)
					{
						PS2Keyboard->queue[i] = 0;
					}

				}


				PS2Keyboard->publicDataOutput = Rxbuffer[5];
				switch (Rxbuffer[7]) 
				{
					case 0:
						{
							// Pull ups off

							switch(CurrentPinPort())
							{
								case 0:  // Port A
									{
										IOCPDA &=~CurrentPinBitmap();
										IOCPDA &= ~pinBitmap[PS2Keyboard->dataPin];
										IOCPUA &=~CurrentPinBitmap();
										IOCPUA &= ~pinBitmap[PS2Keyboard->dataPin];

									}
									break;

								case 1:  // PORT B
									{
										IOCPDB &=~CurrentPinBitmap();
										IOCPDB &= ~pinBitmap[PS2Keyboard->dataPin];
										IOCPUB &=~CurrentPinBitmap();
										IOCPUB &= ~pinBitmap[PS2Keyboard->dataPin];
									}
									break;

							}
						}
						break;

					case 1:
						{
							//Pull high
							switch(CurrentPinPort())
							{
								case 0:  // Port A
									{
										IOCPDA &=~CurrentPinBitmap();
										IOCPDA &= ~pinBitmap[PS2Keyboard->dataPin];
										IOCPUA |= CurrentPinBitmap();
										IOCPUA |= pinBitmap[PS2Keyboard->dataPin];

									}
									break;

								case 1:  // PORT B
									{
										IOCPDB &=~CurrentPinBitmap();
										IOCPDB &= ~pinBitmap[PS2Keyboard->dataPin];
										IOCPUB |= CurrentPinBitmap();
										IOCPUB |= pinBitmap[PS2Keyboard->dataPin];

									}
									break;
							}
						}
						break;


				}        



			}
			break;
		case CONFIGURE_CHANNEL_MODE_2: //Shares Interface with UART queues
			{
				Txbuffer[3] = 0;
				Rxbuffer[3] += 4;
				uint8_t i;

				if (PS2Keyboard->queueAddress != 0xFFFF)
				{
					// Queue is in the User Buffer
					SW_QUEUE_RESULT_t result = QUEUE_RESULT_SUCCESS; 
					for (i = 4; i < Rxbuffer[3] && result == QUEUE_RESULT_SUCCESS ; ++i)
					{
						uint8_t data;
						result = QueueReadByte(PS2Keyboard->queueAddress,&data);
						if (result == QUEUE_RESULT_SUCCESS)
						{
							Txbuffer[i] = data;
							++Txbuffer[3];
						}
					}
				}
				else
				{
					uint8_t data;
					//Local queue
					for (i = 4; i < Rxbuffer[3] && localShiftByte(&data); ++i)
					{
						Txbuffer[i] = data;
						++Txbuffer[3];
					}
				}

			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX //Shares Interface with UART queues
			{
				Txbuffer[3] = 0;  // No Transmit queue
				if (PS2Keyboard->queueAddress != 0xFFFF)
				{
					uint16_t count;

					QueueGetBytesFreeInQueue(PS2Keyboard->queueAddress, &count) ;
					if (count >255)
					{
						Txbuffer[4] = 255;
					}
					else
					{
						Txbuffer[4] = count;
					}
					QueuePeekByte(PS2Keyboard->queueAddress,&Txbuffer[5]);
				}
				else
				{
					Txbuffer[4] = localQueueBytesAvailable();
					Txbuffer[5] = PS2Keyboard->queue[0];
				}

			}
			break; 

		case CONFIGURE_CHANNEL_MODE_6:  //Shares Interface with UART queues
			{  
				PS2Keyboard->queueAddress = RXBUFFER16(3);
				TXBUFFER16(5,0); // No TX Queue
			}
			break; 
		case CONFIGURE_CHANNEL_MODE_7:  //Get first currently pressed keypad values, starting with code in Rxbuffer[3]  
			{  
				if (PS2Keyboard->queueDataMode != PS2KEYBOARD_QUEUEDATA_CURRENTLY_PRESSED)
				{
					error(SW_ERROR_PS2KB_WRONG_MODE);
					return;
				}
				uint8_t keysFound = 0;
				int i;
				Txbuffer[3] = Txbuffer[4] = Txbuffer[5] = Txbuffer[6] = Txbuffer[7] =  0;
				uint8_t* queueBytes = (uint8_t*)PS2Keyboard->queue;
				for (i = Rxbuffer[3]; i < PS2KB_QUEUE_LENGTH * 2 * 8 && keysFound < 5 ;  ++i)
				{
					uint8_t offset = i / 8;
					if (queueBytes[offset] & (1<< (i % 8)))
					{
						Txbuffer[3 + keysFound] = i;
						++ keysFound;
					}
				}

			}
			break; 
		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}
} 

PS2Keyboard_t* debugKeyboard;

int16_t ps2kb_processAscii(uint8_t data)
{
	bool queueData = true;
	uint8_t dataToQueue = 0;
	PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;

	if (data == 0xF0) // Break signal
	{
		PS2Keyboard->lastCodeBreak = true;
		queueData = false;
	}
	else if (data == 0xE0)  // Extended signal
	{
		PS2Keyboard->lastCodeBreak = false;
		PS2Keyboard->lastCodeExtended = true;
		queueData = false;
	}
	else 
	{
		if (PS2Keyboard->lastCodeBreak || PS2Keyboard->lastCodeExtended)
		{
			queueData = false;
		}
		if (PS2Keyboard->lastCodeBreak)
		{
			switch (data)
			{
				case LEFT_SHIFT_CODE:
					{
						PS2Keyboard->leftShiftActive = false;
					}
					break;
				case RIGHT_SHIFT_CODE:
					{
						PS2Keyboard->rightShiftActive = false;
					}
					break;
				default:
					{
					}
					break;
			}
		}
		else
		{

			switch (data)
			{
				case LEFT_SHIFT_CODE:
					{
						PS2Keyboard->leftShiftActive = true;
					}
					break;
				case RIGHT_SHIFT_CODE:
					{
						PS2Keyboard->rightShiftActive = true;
					}
					break;
				default:
					{
					}
					break;
			}
		}



		PS2Keyboard->lastCodeBreak = false;
		PS2Keyboard->lastCodeExtended = false;
		if (data <= 0x7F){
			if (PS2Keyboard->leftShiftActive || PS2Keyboard->rightShiftActive)
			{
				dataToQueue = KBSCSet2[data][1];  // Get shifted value
			}
			else
			{
				dataToQueue = KBSCSet2[data][0];
			}
		}
		else
		{
			dataToQueue = data |0x80;
		}
	}

	if (dataToQueue == 0)
	{
		queueData = false;
	}
	if (!queueData)
	{
		return -1;
	}
	else
	{
		return dataToQueue;
	}
}


void ps2kb_processCurrentlyPressed(uint8_t data) 
{
	PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;

	if (data == 0xF0) // Break signal
	{
		PS2Keyboard->lastCodeBreak = true;
	}
	else if (data == 0xE0)  // Extended signal
	{
		//PS2Keyboard->lastCodeBreak = false;
		PS2Keyboard->lastCodeExtended = true;
	}
	else 
	{
		if (PS2Keyboard->lastCodeBreak)
		{
			if (PS2Keyboard->lastCodeExtended)
			{
				data += 128;
			}
			uint8_t offset = data / 8;
			uint8_t* queueBytes = (uint8_t*) PS2Keyboard->queue;
			queueBytes[offset ] &= ~(1 << (data & 0x07));
		}
		else
		{
			if (PS2Keyboard->lastCodeExtended)
			{
				data += 128;
			}
			uint8_t offset = data / 8;
			uint8_t* queueBytes =  (uint8_t*) PS2Keyboard->queue;
			queueBytes[offset ] |= (1 << (data & 0x07));
		}
		PS2Keyboard->lastCodeBreak = false;
		PS2Keyboard->lastCodeExtended = false;
	}
}

int16_t ps2kb_processMakeCodes(uint8_t data)
{
	bool queueData = true;
	uint8_t dataToQueue = 0;
	PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;

	if (data == 0xF0) // Break signal
	{
		PS2Keyboard->lastCodeBreak = true;
		queueData = false;
	}
	else if (data == 0xE0)  // Extended signal
	{
		PS2Keyboard->lastCodeBreak = false;
		PS2Keyboard->lastCodeExtended = true;
		queueData = false;
	}
	else if (data <= 0x7F)
	{
		if (PS2Keyboard->lastCodeBreak || PS2Keyboard->lastCodeExtended)
		{
			queueData = false;
		}

		PS2Keyboard->lastCodeBreak = false;
		PS2Keyboard->lastCodeExtended = false;
		dataToQueue = data;
	}
	else 
	{
		queueData = false;
	}
	if (dataToQueue == 0)
	{
		queueData = false;
	}
	if (!queueData)
	{
		return -1;
	}
	else
	{
		return dataToQueue;
	}
}


void ps2kb_processData(uint8_t data)
{
	PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;
	PS2Keyboard->bytesProcessed++;
	uint8_t dataToQueue = 0;
	bool queueData = true;

    if (data <= 0x7F)
    {
        switch (PS2Keyboard->publicDataOutput)
        {
            case 0:
	{
		CurrentPinRegister->generic.buffer = KBSCSet2[data][0];
	}
            break;
            case 1:
	{
            CurrentPinRegister->generic.buffer = data;
	}
            break;
            case 2:
            default:
	{
        if (! PS2Keyboard->lastCodeBreak)
        {
            ++CurrentPinRegister->generic.buffer;
        }
	}
            break;
        }
    }

	if (PS2Keyboard->queueDataMode == PS2KEYBOARD_QUEUEDATA_ASCII)
	{
		int16_t result =  ps2kb_processAscii(data);
		if (result < 0)
		{
			queueData = false;
		}
		else
		{
			dataToQueue = (uint8_t) result;
		}
	}
	else if (PS2Keyboard->queueDataMode == PS2KEYBOARD_QUEUEDATA_MAKE_CODES)
	{
		int16_t result =  ps2kb_processMakeCodes(data);
		if (result < 0)
		{
			queueData = false;
		}
		else
		{
			dataToQueue = (uint8_t) result;
		}
	}
	else if (PS2Keyboard->queueDataMode == PS2KEYBOARD_QUEUEDATA_CURRENTLY_PRESSED)
	{
		  ps2kb_processCurrentlyPressed(data);
			queueData = false;
	}
	else if (PS2Keyboard->queueDataMode == PS2KEYBOARD_QUEUEDATA_ALL_CODES)
	{
		dataToQueue = data;
	}

	if (queueData)
	{
		if (PS2Keyboard->queueAddress != 0xFFFF)
		{
			QueueAddByte(PS2Keyboard->queueAddress,dataToQueue);
		}
		else
		{
			localPushByte(dataToQueue);
		}
	}

}



	
void updatePS2Keyboard(void)
{

	BUILD_BUG_ON( sizeof(PS2Keyboard_t) >  BYTES_AVAILABLE_INPUT_DMA );   
	PS2Keyboard_t* PS2Keyboard = (PS2Keyboard_t*) CurrentPinRegister;
	debugKeyboard = PS2Keyboard;
	uint16_t clockBitmap = CurrentPinBitmap();
	uint16_t sample = 0;
	uint16_t dataBitmap = pinBitmap[PS2Keyboard->dataPin];
	bool clockSample;
	bool dataSample;
	uint8_t currentState = PS2Keyboard->state;

	bool processSamples = true;

	processSamples =  PulseInGetOldestDMASample(CurrentPin,&sample);
	clockSample = (sample & clockBitmap) > 0;
	dataSample = (sample & dataBitmap ) > 0;
	while (processSamples )
	{


		if (currentState == PS2KB_STATE_IDLE)
		{
			if (!clockSample)
			{
				PS2Keyboard->data = 0; //Starting new frame
				++currentState;
			}
		}
		else if (currentState >= PS2KB_STATE_WAITING_FOR_IDLE0)
		{
			if (!clockSample)
			{
				currentState = PS2KB_STATE_WAITING_FOR_IDLE0;
			}
			else
			{
				++currentState;
			}
		}
		else if (currentState == PS2KB_STATE_WAITING_FOR_START_RISE)
		{
			if (clockSample)
			{
				++currentState;
			}
		}
		else if (currentState <= PS2KB_STATE_WAITING_FOR_DATA7_RISE)
		{
			if (currentState & 0x01)
			{
				//Waiting for rise
				if (clockSample)
				{
					PS2Keyboard->data >>= 1;
					dataSample = (sample & dataBitmap ) > 0;
					if (dataSample)
					{
						PS2Keyboard->data |= 0x80;
					}
					++currentState;
				}

			}
			else
			{
				//Waiting for fall
				if (!clockSample)
				{
					++currentState;
				}
			}

		}
		else if (currentState == PS2KB_STATE_WAITING_FOR_PARITY_FALL)
		{
			if (!clockSample)
			{
				++currentState;
			}
		}
		else if (currentState == PS2KB_STATE_WAITING_FOR_PARITY_RISE)
		{
			if (clockSample)
			{
				uint8_t i;
				uint8_t copy = PS2Keyboard->data;
				uint8_t parity = 0;
				for (i = 0; i < 8; ++i)
				{
					if (copy & 0x01)
					{
						++parity;
					}
					copy >>= 1;
				}
				dataSample = (sample & dataBitmap ) > 0;
				if (dataSample)
				{
					++parity;
				}
				//Parity should be odd
				if (parity & 0x01)
				{
					// Good
					++currentState;
				}
				else
				{
					// Bad
					currentState = PS2KB_STATE_WAITING_FOR_IDLE0;
				}

			}
		}

		else if (currentState == PS2KB_STATE_WAITING_FOR_STOP_FALL)
		{
			if (!clockSample)
			{
				++currentState;
			}
		}
		else if (currentState == PS2KB_STATE_WAITING_FOR_STOP_RISE)
		{
			if (clockSample)
			{
				dataSample = (sample & dataBitmap ) > 0;
				if (dataSample)
				{
					//Good
					ps2kb_processData(PS2Keyboard->data);
					currentState = PS2KB_STATE_IDLE;
				}
				else
				{
					// Bad
					currentState = PS2KB_STATE_WAITING_FOR_IDLE0;
				}
			}

		}
		processSamples =  PulseInGetOldestDMASample(CurrentPin,&sample);
		clockSample = (sample & clockBitmap) > 0;

	}

	PS2Keyboard->state = currentState;

}
