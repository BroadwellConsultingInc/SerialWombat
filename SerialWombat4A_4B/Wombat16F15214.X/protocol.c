/*
Copyright 2020 Broadwell Consulting Inc.

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
#include "serialWombat.h"
#include "asciiConversion.h"


uint8_t UartRxbufferCounter = 0;
uint8_t Rxbuffer[RXBUFFER_LENGTH];
uint8_t Txbuffer[TXBUFFER_LENGTH];


//uint16_t lastUserBufferIndex = 0xFFFF;
//uint16_t lastQueueIndex = 0xFFFF;
void ProcessSetPin(void);
void UART1_WriteBuffer(uint8_t* buffer, uint8_t count);

#ifdef I2CWOMBAT
extern volatile uint8_t i2cTxBufferCounter;
#endif

#ifdef UARTWOMBAT
bool LineBreaksAndEcho = false;
void WriteCRLF()
{
    EUSART1_Write('\r');
    EUSART1_Write('\n');
}
#endif

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
        EUSART1_Write(Txbuffer[i]);
    }
	if (LineBreaksAndEcho)
	{
		WriteCRLF();WriteCRLF();
	}
#endif

#ifdef I2CWOMBAT
	i2cTxBufferCounter = 8;
#endif

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
    
    if (Rxbuffer[0] >= CONFIGURE_CHANNEL_MODE_0  && Rxbuffer[0] <= CONFIGURE_CHANNEL_MODE_HW_4)
    {
        ProcessSetPin();
    }
    else
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
#ifdef UARTWOMBAT
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
#endif
        case COMMAND_BOOTLOAD:
        {
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
								}
								break;
							case 'h':
								{
									CurrentPinHigh();
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
					error();
				} 
			}
			break;
        
        case COMMAND_ASCII_SLEEP:
        {
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
			Txbuffer[2] = (uint8_t)((NUMBER_OF_PHYSICAL_PINS / 10) + '0');   
			Txbuffer[3] = (uint8_t)((NUMBER_OF_PHYSICAL_PINS % 10) + '0');
			Txbuffer[4] = SERIAL_WOMBAT_HARDWARE_IDENTIFIER;	     
			Txbuffer[5] = '2';	     
			Txbuffer[6] = '0';	     
			Txbuffer[7] = '1';	     

			break;
#if 0
        case 'v':
        {
            /** \addtogroup ProtocolAsciiCommands
\{

ASCII Voltage Command
---------------------
Sends back v followed by 4 ascii digits indicating source voltage in mV.
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|'v'|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|'U'*|
*'U' is recommended, but any byte is acceptable

Examples:

`vUUUUUUU`

 Will respond 
 
 `v3160   `

 Or similar

\}
**/
            uint16_t temp1 = GetADCConversion(0x1E); //1.024v reference
            asciiVal = (uint16_t)(((uint32_t)1024 * 65536) / temp1);
            uint16ToAscii5NoHWMathNoIndex();
            Txbuffer[1] = asciiChar[0]; 
            Txbuffer[2] = asciiChar[1];
            Txbuffer[3] = asciiChar[2];
            Txbuffer[4] = asciiChar[3];
            Txbuffer[5] = asciiChar[4];
			Txbuffer[6] = ' ';	     
			Txbuffer[7] = ' ';	     
        }
			break;
#endif
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
        
        case COMMAND_BINARY_READ_RAM:
        {
		uint16_t addr = RXBUFFER16(1);
    Txbuffer[3] = *(uint8_t*)addr;
            
        }
        break;
        
        case COMMAND_BINARY_READ_FLASH:
        {
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
#ifdef I2CWOMBAT
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
} // end ProcessRxbuffer



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
        UartRxbufferCounter = 8;
        
extern volatile __bit PacketAvailable;
extern volatile uint8_t RX_ClockStretching;
extern volatile uint8_t TX_ClockStretching;
         PacketAvailable = 0;
    if (RX_ClockStretching)
    {
    
         
         TX_ClockStretching = 0;
         SSP1CON1bits.CKP = 1; // Release clock stretch
    }
   
       
        
         
    }

#endif
        
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
		int i;
		ProcessRxbuffer();
		UartRxbufferCounter = 0;
            #ifdef I2CWOMBAT
            extern volatile __bit ResponseAvailable;
            extern volatile uint8_t RX_ClockStretching;
		ResponseAvailable = 1;
        if (RX_ClockStretching)
    {
    
         RX_ClockStretching = 0;
         
         ResponseAvailable = 0;
    }
#endif
		uartStartTX();
        
       
	}
    #ifdef I2CWOMBAT
            extern volatile uint8_t TX_ClockStretching;
            extern volatile uint8_t RX_ClockStretching;
             extern volatile __bit ResponseAvailable;
        if (TX_ClockStretching && ResponseAvailable)
        {

            TX_ClockStretching = 0;
            RX_ClockStretching = 0;
            i2cTxBufferCounter = 7;
            ResponseAvailable = 0;
            SSP1BUF = Txbuffer[0];            
            SSP1CON1bits.CKP = 1; // Release clock stretch
        }
        #endif

}




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
            extern  void init_quadEnc(void);
			init_quadEnc();		
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
}
