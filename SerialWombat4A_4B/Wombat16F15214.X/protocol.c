/*
Copyright 2020-2021 Broadwell Consulting Inc.

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

/*! \file protocol.c

  This file contains the functions which process incoming data from the host and generate response packets.

 */

#include <stdint.h>
#include <stdbool.h>
#include "serialWombat.h"
#include "asciiConversion.h"

/// \brief The number of bytes received towards a new packet
uint8_t UartRxbufferCounter = 0;
/// \brief A buffer for incoming commands from the host
uint8_t Rxbuffer[RXBUFFER_LENGTH];

/// \brief A buffer for outgoing commands to the host.
uint8_t Txbuffer[TXBUFFER_LENGTH];

#define I2C_REINIT_TIME 30000
uint16_t I2C_Reinit_Countdown = I2C_REINIT_TIME;
extern __bit I2C_Recovery; 
void ProcessSetPin(void);
void UART1_WriteBuffer(uint8_t* buffer, uint8_t count);

#ifdef I2CWOMBAT
/// \brief  When using I2C, the number of bytes remaining to send
extern volatile uint8_t i2cTxBufferCounter;
#endif

#ifdef UARTWOMBAT

/// \brief  When true, add line breaks to each command and echo bytes back to the host.  Used for manual command entry over terminal
bool LineBreaksAndEcho = false;

/// \brief  Send a carraige return / line feed to the host
void WriteCRLF()
{
    EUSART1_Write('\r');
    EUSART1_Write('\n');
}
#endif


///  \brief Send the Txbuffer to the host.
void uartStartTX()
{
#ifdef UARTWOMBAT
	if (LineBreaksAndEcho)
	{
		WriteCRLF();
	}

	uint8_t i;
    for (i = 0; i < 8; ++i)
    {
        EUSART1_Write(Txbuffer[i]);  // Send all 8 bytes to the UART TX queue
    }
	if (LineBreaksAndEcho)
	{
		WriteCRLF();WriteCRLF();
	}
#endif

#ifdef I2CWOMBAT
	i2cTxBufferCounter = 8;  // Mark buffer as ready to send
#endif

}


///  \brief Process the packet in RxBuffer
void ProcessRxbuffer( void )
{
     I2C_Reinit_Countdown = I2C_REINIT_TIME;
	// Assume we're going to echo the command back.  Individual commands can change bytes as needed.
	Txbuffer[0] = Rxbuffer[0];
	Txbuffer[1] = Rxbuffer[1];
	Txbuffer[2] = Rxbuffer[2];
	Txbuffer[3] = Rxbuffer[3];
	Txbuffer[4] = Rxbuffer[4];
	Txbuffer[5] = Rxbuffer[5];
	Txbuffer[6] = Rxbuffer[6];
	Txbuffer[7] = Rxbuffer[7];
    
    if (Rxbuffer[0] >= CONFIGURE_CHANNEL_MODE_0  && Rxbuffer[0] <= CONFIGURE_CHANNEL_MODE_HW_3)
    {
/** \addtogroup ProtocolBinaryCommands
\{

----

Pin Configuration Commands
---------------------

Commands from 0xC0 to 0xDF (inclusive) are Pin Configuration commands.  The format of a Pin Configuration commands is:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0 to 0xDF|Pin Number being configured|Pin Mode|Varies By Configuration number and Mode|Varies By Configuration number and Mode|Varies By Configuration number and Mode|Varies By Configuration number and Mode|Varies By Configuration number and Mode|

See the init Function documentation for each mode for specifics on how to configure that mode.

Pin Modes Defined for the SerialWombat 4A and 4B (Mode numbers in decimal)
-------------------------------

 * PIN_MODE_DIGITAL_IO = 0  (See  ProcessSetPin() )

 * PIN_MODE_ANALOGINPUT = 2 (See initAnalogInput() )

 * PIN_MODE_SERVO = 3 (See initServo() )

 * PIN_MODE_QUADRATURE_ENC = 5  (See initQuadEnc() )

 * PIN_MODE_WATCHDOG = 7  (See initWatchdog() )

 * PIN_MODE_PROTECTEDOUTPUT = 8 (See initProtectedOutput() )

 * PIN_MODE_DEBOUNCE = 10    (See initDebounce() )

 * PIN_MODE_PWM = 16   (See initPWM() )

 * PIN_MODE_PULSE_TIMER = 18 (See initPulseTimer() )

 Pin Modes Defined for the SerialWombat 4B (Mode numbers in decimal)
 -------------------------------

 * PIN_MODE_UART_TXRX = 17  (see initUART() )



\}
**/
	    //  If a process pin command, process it
        ProcessSetPin();
    }
    else
    {
	    // Some other type of command.  Process accordingly
	switch (Rxbuffer[0])
	{
		case COMMAND_ASCII_ECHO:

/** \addtogroup ProtocolAsciiCommands
\{

----

ASCII Echo 
---------------------

This command simply sends back what was sent and takes no action.
Echos back response unless error.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'!'|AnyByte|AnyByte|AnyByte|AnyByte|AnyByte|AnyByte|AnyByte|

Examples:

> `!1234567`

 Will respond `!1234567`

\}
**/

			break;
#ifdef UARTWOMBAT
		case COMMAND_ASCII_LINEFEED:
		{
/** \addtogroup ProtocolAsciiCommands
\{

----

ASCII Enable / Disable Line Breaks
---------------------

This command causes the Serial Wombat to echo back input and add a carraige return / line feed before and after every returned message.

This command is only valid on UART based Serial Wombats.

This is very useful when you're typing commands in a terminal, but will cause problems if you are talking to the Serial Wombat
with a program, particularly if you are using Binary commands.

This command is not supported on the Serial Wombat 4B.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'^'|'L'|'I'|'N'|'E'|'B'|'K'|'0' or '1'|

Examples:

> `^LINEBK1`

Enables Line Breaks. 

> `^LINEBK0`

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
#endif
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
                INTERRUPT_GlobalInterruptDisable();
                STKPTR = 0xF; // Max value
                CurrentPinAnalog();  // Cause a stack reset.
            }
        }
        break;

#ifdef UARTWOMBAT
        case COMMAND_ASCII_SET_PUBLIC_DATA: // Set Public Data
/** \addtogroup ProtocolAsciiCommands
\{

---- 

ASCII Set Public Data 
---------------------

This command allows the public data of a pin to be set.  Maximum allowable data value is 65535 .  Value is represented in decimal.
Echos back response unless error.

This command is not supported on the Serial Wombat 4B.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'D'|Pin X 10's|Pin X 1's|Public Data 10000's|Public Data 1000's|Public Data 100's | Public Data 10's | Public Data 1's|

Examples:

> `D0213143`

Sets pin 2 Public Data to 13143.

\}
**/
			{
				CurrentPin = ascii_to_val(Rxbuffer[1]);
				CurrentPin  *= 10;
				CurrentPin  += ascii_to_val(Rxbuffer[2]); 
                if (CurrentPin >= NUMBER_OF_PHYSICAL_PINS)
                {
                    error();
                    break;
                }
				uint24_t value = ascii_to_val(Rxbuffer[3]);
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
					SetBuffer(CurrentPin,(uint16_t)value);
				}
				else
				{
					error();
				}
			}
			break;

        case COMMAND_ASCII_GET_PUBLIC_DATA: // Set Public Data
/** \addtogroup ProtocolAsciiCommands
\{

----

ASCII Get Public Data 
---------------------

This command allows the public data of a pin to be set.  Maximum allowable data value is 65535 .  Value is represented in decimal.
Echos back response unless error.

This command is not supported on the Serial Wombat 4B.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'G'|Pin X 10's|Pin X 1's|'U'*|'U'*|'U'*|'U'*|'U'*|

 *'U' is recommended, but any byte is acceptable

Examples:

> `G02UUUUU`

Gets pin 2 Public Data In Ascii
Sample Response:

> `G0226132`

Public data for Pin 2 is 26132.

\}
**/
			{
				CurrentPin = ascii_to_val(Rxbuffer[1]);
				CurrentPin  *= 10;
				CurrentPin  += ascii_to_val(Rxbuffer[2]); 
				//uint16ToAscii5NoHWMathNoIndex(GetBuffer(CurrentPin),3);
                asciiVal = GetBuffer(CurrentPin);
                uint16ToAscii5NoHWMathNoIndex();
                Txbuffer[3] = asciiChar[0];
                Txbuffer[4] = asciiChar[1];
                Txbuffer[5] = asciiChar[2];
                Txbuffer[6] = asciiChar[3];
                Txbuffer[7] = asciiChar[4];
			}
			break;



	case COMMAND_ASCII_SET_PIN: 
/** \addtogroup ProtocolAsciiCommands
\{

----

ASCII Set Pin Command
---------------------

This command allows the digital state of up to 5 consecutive pins to be set.  

This command is not supported on the Serial Wombat 4B.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'P'|Pin X 10's|Pin X 1's|Pin X Setting|Pin X+1 Setting|Pin X+2 Setting|Pin X+3 Setting|Pin X+4 Setting|

Possible Pin Settings:
 - 'l' Make the pin an Output Low
 - 'h' Make the pin an Output High
 - 'a' Make the pin an Analog Input
 - 'i' Make the pin an Input (without a weak Pull Up)
 - 's' Make the pin a Servo Controller
 - 'u' Make the pin an Input (with a weak Pull Up)
 - 'w' Make the pin a PWM Output
 - 'x' No change
Echos back response unless error.

Examples:

> `P021xxxx`

Sets pin 2 high, and doesn't change any other pins


> `P0910xii`

Sets pin 9 High, pin 10 Low, doesn't change pin 11, and sets pins 12 and 13 to inputs

\}
**/
			{
				uint8_t  rxIndex;
				CurrentPin = ascii_to_val(Rxbuffer[1]);
				CurrentPin  *= 10;
				CurrentPin  += ascii_to_val(Rxbuffer[2]); 
               
              
				for ( rxIndex = 3; rxIndex < 8 ; ++rxIndex,++CurrentPin )
				{
                      CurrentPinMask = PinMaskArray[CurrentPin];
     CurrentPinMaskInverted = ~CurrentPinMask;
    #ifdef USE_BUFFERED_PIN_REGISTER
                
#else
	CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
#endif
	if (CurrentPin >= NUMBER_OF_TOTAL_PINS)
	{		
		break;
	}
        #ifdef USE_BUFFERED_PIN_REGISTER
        CopyFromArrayToPinBuffer();
        #endif
#ifdef USE_BUFFERED_PIN_REGISTER
                
#else
                CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
#endif
					if (Rxbuffer[rxIndex] == 'a')
					{
                        
				
						Rxbuffer[0] = CONFIGURE_CHANNEL_MODE_0;
                        void initAnalogInput (void);
						initAnalogInput();
                     
                        
					}
					else
					{
                        
						CurrentPinNotAnalog();
						SetMode(CurrentPin,PIN_MODE_DIGITAL_IO) ;
						switch(Rxbuffer[rxIndex])
						{
							case 'i':
								{
                                    CurrentPinNoPullUp();
									CurrentPinInput();
								}
								break;
							case 'l':	
								{
									CurrentPinLow();
                                    CurrentPinRegister->generic.buffer = 0;
								}
								break;
							case 'h':
								{
									CurrentPinHigh();
                                    CurrentPinRegister->generic.buffer = 1;
								}
								break;
							case 'u':  //Pull Up Input
								{
                                    CurrentPinInput();
									CurrentPinPullUp();

								}
								break;
                                /*
							case 'd':  //Pull Down Input
								{
									//TODO add pulldown
									CurrentPinInput();
								}
								break;
                                 * */
							case 's':  //Servo
								{
                                    void initServoSimple(void);
								    initServoSimple();
								}
								break;
							case 'w':  //PWM
								{
                                    void initPWMSimple(void);
								initPWMSimple();
								}
								break;
							case 'x':
                            case ' ':
								{
								}
								break;
							default:
								{
									error();
								}
								break;
						}
					}
                 #ifdef USE_BUFFERED_PIN_REGISTER
        CopyFromPinBufferToArray();
    #endif
				}
               
			}
			break;
#endif
		case COMMAND_ASCII_RESET: // 'R'
/** \addtogroup ProtocolAsciiCommands
\{

----

ASCII Reset Command
---------------------

This command causes an internal reset of the Serial Wombat, similar to one caused by pulling the reset pin low.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'R'|'e'|'S'|'e'|'T'|'!'|'#'|'*'|


No response, as Wombat enters reset upon receipt.
Example:

> `ReSeT!#*`

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
					error();
				} 
			}
			break;
        
        case COMMAND_ASCII_SLEEP:
        {
/** \addtogroup ProtocolAsciiCommands
\{

---- 

ASCII Sleep Command
---------------------

This command causes the Serial Wombat to go in a low power mode.  Most Serial Wombat functions and pin modes stop.  The host should ensure all pins are in a desired state before sleep.   


Receipt of another byte will wake up the Serial Wombat.  Suggested wakeup sequence for UART is 16 consecutive 0x55 bytes.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'S'|'l'|'E'|'e'|'P'|'!'|'#'|'*'|


Example:

> `SlEeP!#*`

Command is echoed back before sleeping.


\}
**/
            if (Rxbuffer[1] == 'l' && 
						Rxbuffer[2] == 'E' && Rxbuffer[3] == 'e' && 
						Rxbuffer[4] == 'P' && Rxbuffer[5] == '!' &&
						Rxbuffer[6] == '#' &&  Rxbuffer[7] == '*')
            {
                extern bool Sleep;
                Sleep = true;
                    
            }
            else
				{
					error();
				} 
        }
        break;
		case COMMAND_ASCII_VERSION: //Ascii 'V'  Version String
/** \addtogroup ProtocolAsciiCommands
\{

----

ASCII Version Command
---------------------

Sends back V followed by 7 characters indicating the firmware version number
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'V'|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|
*'U' is recommended, but any byte is acceptable

Examples:

> `VUUUUUUU`

 Will respond 
 
 > `VS04B202`

 Or similar based on Model and Firmware version

 V = Version Command

 S = Serial Wombat

 04B or similar = Model

 202 or similar = Firmware Revision

\}
**/
			Txbuffer[1] = 'S';   //Serial Wombat
			Txbuffer[2] = (uint8_t)((NUMBER_OF_PHYSICAL_PINS / 10) + '0');   
			Txbuffer[3] = (uint8_t)((NUMBER_OF_PHYSICAL_PINS % 10) + '0');
			Txbuffer[4] = SERIAL_WOMBAT_HARDWARE_IDENTIFIER;	     
			Txbuffer[5] = '2';	     
			Txbuffer[6] = '0';	     
			Txbuffer[7] = '3';	     

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
			temp = GetBuffer(Rxbuffer[2]);
			TXBUFFER16(4,temp);		
			temp = GetBuffer(Rxbuffer[3]);
			TXBUFFER16(6,temp);		

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

Reads the public data from three consecutive pins starting with a specified pin
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x81|Pin Number requested |Specified Pin Public Data low byte|Specified Pin Public Data High byte|2nd pin number|2nd pin low byte|2nd pin high byte|Echo of sent Byte 7|

Examples:

> `0x81 0x01 0x55 0x55 0x55 0x55 0x55 0x55`

Will read the 16-bit public data from pins 1, 2 and 3.  Assuming pin1's public data was 0x481B, pin 2's was 0x38FC, and pin 3's was 0x0314:

Response:
> `0x81 0x1 0x1B 0x48 0xFC 0x38 0x14 0x03`

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
        
        case COMMAND_BINARY_CONFIGURE:
        {
            /** \addtogroup ProtocolBinaryCommands
\{

----

Configure Serial Wombat parameter
---------------------

Set a configurable parameter in the Serial Wombat firmware


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0x9F|Least Significant byte of 16-bit parameter |Most Significant byte of 16-bit parameter | Parameter value low byte | Parameter Value byte or 0x55* | Parameter Value byte or 0x55* |  Parameter Value byte or 0x55* | 0x55* |
 *0x55 is recommended, but any byte is acceptable

Response:
             
Echoed Back

Examples:

Set Parameter 1 (one byte) to 1.  (Enables I2C recovery and 30 second watchdog on successful receive packet)

> `0x9F 0x01 0x00 0x01  0x55 0x55 0x55 0x55`

\}
**/
            switch(Rxbuffer[1])
            {
                case 1:
                {
                    I2C_Recovery = (__bit) Rxbuffer[3]; 
                }
            }
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

Binary Read Flash, 16 Bit address
---------------------

Reads a byte from an address in Microcontroller RAM.  The SW4A and SW4B use 16 bit addresses.  

See the Datasheet for the microchip PIC16F15214 for information on organization

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xA0|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address | 0x55* | 0x55* | 0x55* |  0x55* | 0x55* |
 *0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xA0|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address | Byte Read From Ram| Echoed | Echoed |  Echoed | Echoed |

Examples:

Read the byte at FLASH address 0x0847.

> `0xA1 0x47 0x08 0x55 0x55 0x55 0x55 0x55`

Assuming address 0x0847 held the value 0xEF ,
Response:
> `0xA1 0x47 0x08 0xEF 0x55 0x55 0x55 0x55`

\}
**/
            NVMCON1bits.NVMREGS = 0x01;
    NVMADRH = Rxbuffer[2];
    NVMADRL = Rxbuffer[1];
    NVMCON1bits.RD = 0x01;
    while (NVMCON1bits.RD == 1);
    Txbuffer[4] = NVMDATL;
    Txbuffer[5] = NVMDATH;
    Txbuffer[6] = 0;
    Txbuffer[7] = 0;
   
            
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
|0xA0|Least Significant byte of 16-bit address |Most Significant byte of 16-bit address | 0 (for 32-bit compatability) | 0 (for 32-bit compatability) | Byte To write |  0x55* | 0x55* |
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
        
#ifdef I2CWOMBAT
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
            void EUSART1_Write(uint8_t txData);
            EUSART1_Write(Rxbuffer[1]);
            EUSART1_Write(Rxbuffer[2]);
            EUSART1_Write(Rxbuffer[3]);
            EUSART1_Write(Rxbuffer[4]);
            EUSART1_Write(Rxbuffer[5]);
            EUSART1_Write(Rxbuffer[6]);
            EUSART1_Write(Rxbuffer[7]);
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
            uint8_t EUSART1_Read(void);
            Txbuffer[1] = EUSART1_Read();
            Txbuffer[2] = EUSART1_Read();
            Txbuffer[3] = EUSART1_Read();
            Txbuffer[4] = EUSART1_Read();
            Txbuffer[5] = EUSART1_Read();
            Txbuffer[6] = EUSART1_Read();
            Txbuffer[7] = EUSART1_Read();
        }
        break;
        
#endif
		default:
			
				{
					error();
        }
			break;
	}
    }
} // end ProcessRxbuffer



// This function is called repeatedly by the main loop when its not busy processing pin state machines.
// This function pulls data from the UART queue or recognizes when an I2C packet is ready, processes the
// packet, and initializes the sending of a response. 
void ProcessRx(void)
{
	if ( UartRxbufferCounter < RXBUFFER_LENGTH)
	{
#ifdef UARTWOMBAT
		while (EUSART1_is_rx_ready() && UartRxbufferCounter < 8)
		{
			uint8_t buffer = EUSART1_Read();
			if (LineBreaksAndEcho)
			{
				EUSART1_Write(buffer);
			}
			Rxbuffer[UartRxbufferCounter++] = buffer;
		}
#endif

#ifdef I2CWOMBAT

		extern uint8_t WombatRX[8];
		extern uint8_t WombatRXBytesReceived ;
		extern volatile __bit PacketAvailable;
		extern volatile __bit ResponseAvailable;
		if (WombatRXBytesReceived >= 8 )
		{
			ResponseAvailable = 0;
			Rxbuffer[0] = WombatRX[0];
			Rxbuffer[1] = WombatRX[1];
			Rxbuffer[2] = WombatRX[2];
			Rxbuffer[3] = WombatRX[3];
			Rxbuffer[4] = WombatRX[4];
			Rxbuffer[5] = WombatRX[5];
			Rxbuffer[6] = WombatRX[6];
			Rxbuffer[7] = WombatRX[7];
			WombatRXBytesReceived = 0;
			UartRxbufferCounter = 8;   // Since this came in over I2C, make it look like we have 8 received bytes ready.

			extern volatile __bit PacketAvailable;
			extern volatile uint8_t RX_ClockStretching;
			extern volatile uint8_t TX_ClockStretching;
			PacketAvailable = 0;  // Packet has been processed.  
			if (RX_ClockStretching)  
			{
				// If we're in the middle of stretching a 2nd request to send us data to from the host, release.  
				// We've made a copy of the incoming data, so we can receive another while we're processing this one.
				// The fact that the host is trying to send us another packet means it doesn't care about the response
				// from the packet we're about to process.
				TX_ClockStretching = 0; 
				SSP1CON1bits.CKP = 1; // Release clock stretch in hardware
			}




		}

#endif

		// Filter out any packets that would start with 0x55  (Capital U)
		while (UartRxbufferCounter > 0  && Rxbuffer[0] == 0x55 )
		{
			uint8_t i;
			for (i = 0; i < RXBUFFER_LENGTH - 1; ++i)
			{
				Rxbuffer[i] = Rxbuffer[i+1];
			}
			-- UartRxbufferCounter;
		}
	}
	if (UartRxbufferCounter >= RXBUFFER_LENGTH)
	{
		// We have a complete packet.  Process it.
		ProcessRxbuffer();
		// And prep for a new packet.
		UartRxbufferCounter = 0;
#ifdef I2CWOMBAT
		extern volatile __bit ResponseAvailable;
		extern volatile uint8_t RX_ClockStretching;
     	INTERRUPT_GlobalInterruptDisable(); 
        NOP();
        NOP();
        NOP();
		ResponseAvailable = 1;
		if (RX_ClockStretching)
		{
			
			// If we're in the middle of stretching a 2nd request to send us data to from the host, release.  
			RX_ClockStretching = 0;

			ResponseAvailable = 0;
		}
#endif
		uartStartTX();  // ProcessRxbuffer put a response in Txbuffer.   Send it...

	}
#ifdef I2CWOMBAT
	extern volatile uint8_t TX_ClockStretching;
	extern volatile uint8_t RX_ClockStretching;
	extern volatile __bit ResponseAvailable;
	if (TX_ClockStretching && ResponseAvailable)
	{

		// If we were clock stretching waiting for a response to the last packet to be generated,
		// it's ready now, so stop stretching the clock.
		TX_ClockStretching = 0;
		RX_ClockStretching = 0;
		i2cTxBufferCounter = 7;
		ResponseAvailable = 0;
		SSP1BUF = Txbuffer[0];            
		SSP1CON1bits.CKP = 1; // Release clock stretch
	}
    INTERRUPT_GlobalInterruptEnable();
#endif

}


/*!
  \brief Processes a pin mode configuration packet

 This subroutine processes all Pin Configuration requests based on 8 bytes stored in Rxbuffer.
 Pins set in Digital I/O pin mode are handled directly in this function.  Other pin modes
 are handled by initailization functions that exist in the .c file that defines that pin mode.


Digital I/O pin configuration:
---------------------

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x00 (Digital I/O mode) |0x00, 0x01, or 0x02 (Low, high, input)|0x00 or 0x01 (Weak Pull up off, Weak Pull up on)|0x00 (reserved for chips that support weak pull downs)|0x00 or 0x01 (Open Drain mode off or on)|0x55*|

*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 2 to Digital I/O, High, no weak pull up, normal mode

> `0xC0 0x02 0x00 0x01 0x00 0x00 0x00 0x55`

Set pin 3 to Digital I/O, Input, wth weak pull up, normal mode

> `0xC0 0x03 0x00 0x02 0x01 0x00 0x00 0x55`

Set pin 1 to Digital I/O, low, open drain 

> `0xC0 0x01 0x00 0x00 0x00 0x00 0x01 0x55`

 */

void ProcessSetPin()
{
	extern const uint8_t PinMaskArray[4];


	CurrentPin = Rxbuffer[1];
	CurrentPinMask = PinMaskArray[CurrentPin];
	CurrentPinMaskInverted = ~CurrentPinMask;
#ifdef USE_BUFFERED_PIN_REGISTER

#else
	CurrentPinRegister = &PinUpdateRegisters[CurrentPin];
#endif

#ifdef USE_BUFFERED_PIN_REGISTER
	CopyFromArrayToPinBuffer();
#endif
	switch (Rxbuffer[2])
	{
		case PIN_MODE_DIGITAL_IO:
			{
				CurrentPinRegister->generic.mode = 0;
				if (Rxbuffer[6] > 0)
				{
					// Set Pull Up
					CurrentPinOpenDrain();
				}
				else
				{
					CurrentPinNotOpenDrain();
				}


				SetCurrentPin(Rxbuffer[3]);
                CurrentPinRegister->generic.buffer = Rxbuffer[3];
				if (Rxbuffer[4] > 0)
				{
					// Set Pull Up
					CurrentPinPullUp();
				}
				else
				{
					CurrentPinNoPullUp();
				}

			}
			break;

		case PIN_MODE_QUADRATURE_ENC:
			{
				extern  void initQuadEnc(void);
				initQuadEnc();		
			}
			break;

		case PIN_MODE_SERVO:
			{
				extern void initServo(void);
				initServo();
			}
			break;

		case PIN_MODE_ANALOGINPUT:
			{
				void initAnalogInput (void);
				initAnalogInput();
			}
			break;
		case PIN_MODE_PWM:
			{
				void initPWM(void);
				initPWM();
			}

			break;

		case PIN_MODE_DEBOUNCE:
			{
				void initDebounce(void);
				initDebounce();
			}
			break;

		case PIN_MODE_WATCHDOG:
			{
				void initWatchdog(void);
				initWatchdog();
			}
			break;

#ifdef I2CWOMBAT
		case PIN_MODE_UART_TXRX:
			{
				void initUART(void);
				initUART();
			}
			break;
#endif

		case PIN_MODE_PULSE_TIMER:
			{
				extern  void initPulseTimer(void);
				initPulseTimer();		
			}
			break;

		case PIN_MODE_PROTECTEDOUTPUT:
			{
				extern void initProtectedOutput(void);
				initProtectedOutput();
			}
			break;

	}
#ifdef USE_BUFFERED_PIN_REGISTER
	CopyFromPinBufferToArray();
#endif
}

uint8_t i2c_sda_low_counter = 0;
///  \brief Called every 1 mS to timeout I2C clock stretching
///
///  Leaving the Clock stretching bit set indefinitely will lock up the I2C bus preventing any
///  device from using it.  We should never be stuck for more than 1 mS.  This function
///  monitors clock stretching time and forces a reset of the I2C bus if a timeout occurs,
/// releasing the I2C bus.
void protocol_1ms()
{
    extern volatile uint8_t TX_ClockStretching;
    extern volatile uint8_t RX_ClockStretching;
    
    if (TX_ClockStretching)
    {
        --TX_ClockStretching;
        if (TX_ClockStretching == 0)
        {
            I2C1_Initialize();
            I2C1_Open();
        }
    }
    if (RX_ClockStretching)
    {
        --RX_ClockStretching;
        if (RX_ClockStretching == 0)
        {
            I2C1_Initialize();
            I2C1_Open();
        }
    }
    
    if (I2C_Recovery)
    {
    if(I2C_Reinit_Countdown)
    {
         --I2C_Reinit_Countdown;
        if (I2C_Reinit_Countdown == 0)
        {
            reset();
        }
    }
    if ((WP_PORT & (1<<5 )))
    {
        i2c_sda_low_counter = 0;
    }
    else
    {
        ++i2c_sda_low_counter;
    }
    if (i2c_sda_low_counter > 40)
    {
        i2c_sda_low_counter = 0;
        uint16_t x = 1000;
        while (((WP_PORT & (1<<5)) == 0 )&& x > 0)
        {
          --x;   
        }
        if (x == 0)
        {
            //Force SCL Low, high
        WP_LAT &= ~(1<<4 );
        WP_TRIS &= ~(1<<4 );
        __delay_us(100);
         WP_TRIS |= (1<<4);
         I2C1_Initialize();
            I2C1_Open();
        }
    }
}
}
