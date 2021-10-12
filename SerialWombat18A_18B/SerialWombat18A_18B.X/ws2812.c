/*
Copyright 2021 Broadwell Consulting Inc.

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
#include <string.h>  //for memset
#include "asciiConversion.h"


typedef enum 
{
    WS2812_MODE_BUFFERED = 0,
            WS2812_MODE_ANIMATION = 1,
            WS2812_MODE_CHASE = 2,
    
}ws2812_mode_t;

typedef struct ws2812{
    uint16_t userBufferIndex;
    uint16_t animationLedsIndex;
    uint16_t* dmaQueuePosition;
    uint16_t delay ;
    uint8_t numOfLEDS;
    uint8_t chaseColor;
    uint8_t chaseLED;
    uint8_t mode;
    uint8_t animationFrames;
    uint8_t currentAnimationFrame;
}ws2812_t;


#define ws2812 ((ws2812_t*) CurrentPinRegister)
#define dmaBuffer ((uint16_t*)&UserBuffer[ws2812->userBufferIndex])
void ws2812_SPI1_Initialize (void)
{
 // AUDEN disabled; FRMEN disabled; AUDMOD I2S; FRMSYPW One clock wide; AUDMONO stereo; FRMCNT 0; MSSEN disabled; FRMPOL disabled; IGNROV disabled; SPISGNEXT not sign-extended; FRMSYNC disabled; URDTEN disabled; IGNTUR disabled; 
    SPI1CON1H = 0x00;
    // WLENGTH 9; 
    SPI1CON2L = 0x09;
    // SPIROV disabled; FRMERR disabled; 
    SPI1STATL = 0x00;
    // SPI1BRGL 0; 
    SPI1BRGL = 0x00;
    // SPITBFEN disabled; SPITUREN disabled; FRMERREN disabled; SRMTEN disabled; SPIRBEN disabled; BUSYEN disabled; SPITBEN disabled; SPIROVEN disabled; SPIRBFEN disabled; 
    SPI1IMSKL = 0x08; //SPITBEN generates an interrupt.
    // RXMSK 0; TXWIEN disabled; TXMSK 0; RXWIEN disabled; 
    SPI1IMSKH = 0x00;
    // SPI1URDTL 0; 
    SPI1URDTL = 0x00;
    // SPI1URDTH 0; 
    SPI1URDTH = 0x00;
    // SPIEN enabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:Low, Active:High; SSEN disabled; MSTEN Master; MODE16 enabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse precedes; CKE Idle to Active; MODE32 disabled; SPISIDL disabled; ENHBUF enabled; DISSDI disabled; 
    SPI1CON1L = 0x8421;

}


void ws2812ConfigHardware()
{
	ws2812_SPI1_Initialize();
//	RPOR3bits.RP6R = 0x001C;    //RB6->INTERNAL OSCILLATOR:REFO
//    RPOR7bits.RP14R = 0x0008;    //RB14->SPI1:SCK1OUT
    //RPOR5bits.RP11R = 0x0007;    //RB15->SPI1:SDO1
    SetPPSOutput(CurrentPin,0x0007);

}
#define RESET_SIGNAL_LENGTH 2

ws2812_t* debugWS2812;




#define WAIT_UNTIL_SPI_NOT_FULL() { while( SPI1STATLbits.SPITBF == 1 );}

#define SPI_1_BIT 0xFC00
#define SPI_0_BIT 0xE000




//uint16_t dmaBuffer[24 * NUMBER_OF_LEDS + RESET_SIGNAL_LENGTH];
//uint16_t dmaQueuePosition = 0;
inline void queue1Bit()
{
   
    {
        {
         *ws2812->dmaQueuePosition = SPI_1_BIT;
         ++ws2812->dmaQueuePosition;
        }
    }
}


inline void queue0Bit()
{
   
    {
         *ws2812->dmaQueuePosition = SPI_0_BIT;
         ++ws2812->dmaQueuePosition;
    }
}

//Queue R, G, B values to the SPI.  For each of R, G, and B send 8 bits, MSB first
//WS2812B requires that we send G, then R, then B (not R,G,B).
//The queue1Bit / queue0Bit functions will take 1 bit of color information and
//expand that bit into multiple bits to send to the SPI which represent the waveform
//that the WS2812B requires for 

inline void QueueRGB(uint32_t RGB)
{
	uint8_t r = (uint8_t)(RGB >>16);
	uint8_t g = (uint8_t)(RGB >>8);
	uint8_t b = (uint8_t)(RGB);

    if (RGB == 0)
    {
        queue0Bit();queue0Bit();queue0Bit();queue0Bit();
        queue0Bit();queue0Bit();queue0Bit();queue0Bit();
        queue0Bit();queue0Bit();queue0Bit();queue0Bit();
        queue0Bit();queue0Bit();queue0Bit();queue0Bit();
        queue0Bit();queue0Bit();queue0Bit();queue0Bit();
        queue0Bit();queue0Bit();queue0Bit();queue0Bit();        
    }
    else
    {
    if (g & 0x80){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x40){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x20){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x10){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x08){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x04){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x02){queue1Bit(); }    else    {        queue0Bit();    }
    if (g & 0x01){queue1Bit(); }    else    {        queue0Bit();    }
    
     if (r & 0x80){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x40){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x20){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x10){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x08){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x04){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x02){queue1Bit(); }    else    {        queue0Bit();    }
    if (r & 0x01){queue1Bit(); }    else    {        queue0Bit();    }
   
        if (b & 0x80){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x40){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x20){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x10){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x08){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x04){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x02){queue1Bit(); }    else    {        queue0Bit();    }
    if (b & 0x01){queue1Bit(); }    else    {        queue0Bit();    }
    }
}

inline void SendResetSignal()
{
	uint8_t i;
	for (i = 0; i < RESET_SIGNAL_LENGTH; ++i)
	{
         *ws2812->dmaQueuePosition = 0;
         ++ws2812->dmaQueuePosition;
	}
}


#define NUMBER_OF_COLORS 6
uint32_t ColorTable[] = 
{
	0x00FF0000, // Red
	0x0000FF00, // Green
	0x000000FF, // BLUE
	0x00FFFFFF, // White
	0x00FFFF00, // Yellow
	0x00800080, // Purple
};
//uint8_t ChaseLED = 0;
//uint8_t Color = 0;

void StartDMA()
{
    DMACH5bits.CHEN = 0;
    DMACNT5 = (uint16_t)ws2812->numOfLEDS * 24 * 2;//ws2812->dmaQueuePosition - dmaBuffer;
    DMADST5 = &SPI1BUFL;
    DMASRC5 = dmaBuffer;
    DMACH5 = 0x140 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL SPI1 Transmit Interrupt; HIGHIF disabled; 
    DMAINT5= 0x2700;
    DMACH5bits.CHEN = 1;
    ws2812->dmaQueuePosition = dmaBuffer;
}

void StopDMA()
{
    DMACH5bits.CHEN = 0;
}


/*!
    \brief Initialization routine for WS2812B driver 

----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize TM1637 Output


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) | Second Pin (TO TM1637 Data) |Digits | Mode |Public Data Source pin | Brightness (0-7) |


Modes:

- 16 bit Decimal output from Pin Public Data = 0,
- 16 bit Hex output from Pin public Data = 1,
- Char Array provided with 0xC4, 0xC5 commands  = 2, 
- Raw 7 segment provided with 0xC4, 0xC5 commands  = 3,
- Animation = 4,

Response:

Command is echoed back.

Examples:

Set pin 19 to TM1637 Clock, 18 to TM1637 Data,  4 digit display, Hex output of pin 19, Brightness 5

> `0xC0 0x13 0x0A 0x12 0x04 0x02 0x13 0x05 `

----


CONFIGURE_CHANNEL_MODE_1:
---------------------

Change Display order of Digits 0-4.   If "012345" is displayed on the display after the 0xC0 command is sent and the digits appear in the
wrong order, then use this command and CONFIGURE_CHANNEL_MODE_2 to change the display order.

This command is also useful to map the bottom 4 digits of a 5 digit (16 bit) decimal display to the 4 digits of a 4-place display.



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) |Mapping for 0 digit |Mapping for 1 digit | Mapping for 2 digit |Mapping for 3 digit | Mapping for 4 digit |



Response:

Command is echoed back.

Examples:


Upon displaying "012345" on a six digit display "210543" is displayed.  This can be corrected by sending the commands:

> `0xC1 0x13 0x0A 0x02 0x01 0x00 0x15 0x04 `

> `0xC2 0x13 0x0A 0x03 0x55 0x55 0x55 0x55 `


----

CONFIGURE_CHANNEL_MODE_2:
---------------------

Change Display order of Digit 5.    See CONFIGURE_CHANNEL_MODE_1



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) |Mapping for 5 digit |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* |

\*0x55 is recommended, but any byte is acceptable


CONFIGURE_CHANNEL_MODE_3:
---------------------

Set TM1637 Brightness


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) |Brightness (0-7) |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19  TM1637 Brightness to level 3

> `0xC3 0x13 0x0A 0x03 0x55 0x55 0x55 0x55  `


CONFIGURE_CHANNEL_MODE_4:
---------------------

Set output values for TM1637.     0xC4 and 0xC5 are used to set 6 output bytes when in the Char array (2), Raw Segment (3), and animation (4) modes.  

For Char array, ASCII characters are loaded into output values 0-5.  These are translated within the pin mode to Seven Segment displays.  Bytes above ASCII range (0x7F) in char mode are anded with 0x7F and transferred as is, allowing raw display in addition to characters.

In Raw Segment Mode the 8 bit data (7 segments (Seg A in LSB)  and decimal point (MSB)) are transferred directly to the display.

In animation mode output values specify a 16 bit index into the User Memory buffer where a series of 6 byte Raw Segment arrays are stored, a 16 bit delay time between arrays, and an 8 bit count of the number of arrays to display.  The final output value byte is used internally by the firmware and should be set to 0.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC4|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) |OutputValue[0] |OutputValue[1]|OutputValue[2]|OutputValue[3]|OutputValue[4]| 


Response:

Command is echoed back.

Examples:

Display "Hello" on the display:

Initialize the display in character array mode (mode 2) (assume pin 19 clk and 18 dio as above), brightness 5.   The source
pin value in the 0xC0 command isn't used in this mode so we'll set it to 0x55.

> `0xC0 0x13 0x0A 0x12 0x02 0x02 0x55 0x05 `

At this point0xC1 and 0xC2 commands would be sent if necessary to define the order in which the display's digits are ordered.

Send the "Hello " to the output:

> `0xC4 0x13 0x0A ` '`H`' '`E`' '`L`' '`L`' '`O`'  

> `0xC5 0x13 0x0A ` '` ` ' `0x55 0x55 0x55 0x55 ` 


Display a set of 12 raw arrays of segment data on the display with 1000ms delays in between.  Data is stored in the user buffer
at index 0x180 .


Start by sending the array of data to the user buffer starting at index 0x180 using the 0x84 WRITE USER BUFFER and 0x85 WRITE USER BUFFER CONTINUE COMMANDS 


Initialize the display in character Animation mode (mode 4) (assume pin 19 clk and 18 dio as above), brightness 5.   The source
pin value in the 0xC0 command isn't used in this mode so we'll set it to 0x55.

> `0xC0 0x13 0x0A 0x12 0x04 0x02 0x55 0x05 `

At this point 0xC1 and 0xC2 commands would send the important data - Index (0x180) in Little Endian format, delay (0x1E8) in little endian format, and frame count (0x0C) 

and set the final byte to 0 with the 0xC5 command

Send the animation setup to the output array:

> `0xC4 0x13 0x0A 0x80 0x01 0xE8 0x03 0xC `

> `0xC5 0x13 0x0A 0x00 0x55 0x55 0x55 0x55 ` 


CONFIGURE_CHANNEL_MODE_5:
---------------------

Set TM1637 Decimal Points

The bottom 6 LSB are used as decimal points for digits 0-5 (before location translation)

Note that the way TM1637 displays are wired varies a lot from display to display, so this command may not work as expected.
Consult the TM1637 and LED module datasheets.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) | Decimal Point Bitmap |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19  TM1637 Decimal Point third digit decimal on

> `0xC6 0x13 0x0A 0x04 0x55 0x55 0x55 0x55  `

*/

void initWS2812 (void)
{

    debugWS2812 = CurrentPinRegister;
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
                ws2812->userBufferIndex = RXBUFFER16(3);
                ws2812->animationLedsIndex = 0x8000; // Will cause invalid writes if not set
                ws2812->animationFrames = 0;
                ws2812->numOfLEDS = Rxbuffer[5];
                ws2812->dmaQueuePosition = dmaBuffer;
                ws2812->chaseColor = 0;
                ws2812->chaseLED = 0;
                ws2812->delay = 0;
                ws2812->mode = 0;
                //memset(dmaBuffer,0, ws2812->userBufferIndex + ((uint16_t)ws2812->numOfLEDS )*24 * 2 + RESET_SIGNAL_LENGTH * 2);
                SendResetSignal();
                uint8_t i;
                for (i = 0; i < ws2812->numOfLEDS; ++i)
                {
                    QueueRGB(0);
                }
                ws2812->dmaQueuePosition = dmaBuffer;
                CurrentPinRegister->generic.mode =PIN_MODE_WS2812;
		CurrentPinLow();
		ws2812ConfigHardware();
			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                    uint32_t rgb = RXBUFFER32(4);
                    uint16_t index = ws2812->userBufferIndex + ((uint16_t) Rxbuffer[3])*24 * 2 + RESET_SIGNAL_LENGTH * 2;
                    if (index + 48 > SIZE_OF_USER_BUFFER)
                    {
                        error(SW_ERROR_WUB_INVALID_ADDRESS);
                    }
                    else
                    {
                    ws2812->dmaQueuePosition = 
                            &UserBuffer[ index ];
                    QueueRGB(rgb);
                    ws2812->dmaQueuePosition = dmaBuffer;
                    ws2812->delay = 0;
                    }
                    
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;

		case CONFIGURE_CHANNEL_MODE_2:
			{
                //Return the number of user buffer bytes required for a given number of LEDS
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                     TXBUFFER16(3,((uint16_t)Rxbuffer[3] * 24 * 2 + RESET_SIGNAL_LENGTH * 2));
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: 
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                    
                    uint16_t index = ws2812->animationLedsIndex  + //Initial address 
                            ((uint16_t) Rxbuffer[3])* (2 + 3 *(uint16_t) ws2812->numOfLEDS)   +   // Skip Rxbuffer[3] Frames
                            (uint16_t)  Rxbuffer[4] * 3 + 2;  // And this frame's delay and Rxbuffer[4] LEDS]
                    if (index + 3  > SIZE_OF_USER_BUFFER)
                    {
                        error(SW_ERROR_WUB_INVALID_ADDRESS);
                    }
                    else
                    {
                    UserBuffer[ index ] = Rxbuffer[5];
                    UserBuffer[ index + 1 ] = Rxbuffer[6];
                    UserBuffer[ index + 2 ] = Rxbuffer[7];
                    }
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;

		case CONFIGURE_CHANNEL_MODE_4: 
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                    ws2812->animationLedsIndex = RXBUFFER16(3);
                    ws2812->animationFrames = Rxbuffer[5];
                   
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;
		case CONFIGURE_CHANNEL_MODE_5: 
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                     uint16_t index = ws2812->animationLedsIndex  + //Initial address 
                            ((uint16_t) Rxbuffer[3])* (2 + 3 *(uint16_t) ws2812->numOfLEDS);  // Skip Rxbuffer[3] Frames

                    if (index + 2  > SIZE_OF_USER_BUFFER)
                    {
                        error(SW_ERROR_WUB_INVALID_ADDRESS);
                    }
                    else
                    {
                    UserBuffer[ index ] = Rxbuffer[4];
                    UserBuffer[ index + 1 ] = Rxbuffer[5];
                    }
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;
            case CONFIGURE_CHANNEL_MODE_6: 
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                    ws2812->mode = Rxbuffer[3];
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;

		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}
}

//TODO update
/// \brief update the TM1637 pin state machine
///
/// This state machine is used to update the TM1637 display.
///
/// It progresses through the following states after initialization:
///
/// Setup:  The segments to be displayed are rendered and put in digit order by 
/// tm1637UpdateRender().
/// The displayArray is then compared with lastDisplay to see if anything has changed
/// since the display is last written.  If not, then the update gets skipped to save
/// Serial Wombat chip CPU cycles.
/// 
/// If an update is required, then the MEMORY WRITE TM1637 command is sent followed by the
/// Initial address.  A digit by digit comparison from position 0 to 5 is then performed
/// to determine if one or more digits can be skipped due to being identical to the last write,
/// and the TM1637 address is set accordingly.
///
/// Data bytes from the first changed location to the last are clocked out.
///
/// If the brightness has changed, then the brightness command is clocked out.
///
/// The system then stays in idle mode for a number of calls.  20 for decimal, hex,
/// string, and raw modes, and a user-defined period for animation.
void updateWS2812()
{
	debugWS2812 = CurrentPinRegister;
	if (ws2812->delay)
	{
		-- ws2812->delay;
	}
	if (ws2812->delay > ws2812->numOfLEDS)
	{

	}
	else 
	{
		
		if (ws2812->mode == WS2812_MODE_CHASE)
		{
			if (ws2812->delay == (ws2812->numOfLEDS - ws2812->chaseLED))
			{
				// This is the current LED.  Turn it on with the color stored in r,g,b
				QueueRGB(ColorTable[ws2812->chaseColor]);
			}
			else
			{
				QueueRGB(0); // This is not the current LED.  Turn it off.
			}
		}
		if (ws2812->mode == WS2812_MODE_ANIMATION)
		{

			// This is the current LED.  Turn it on with the color stored in r,g,b
			uint16_t index = ws2812->animationLedsIndex + 
				ws2812->currentAnimationFrame  * (3 * ws2812->numOfLEDS + 2) +
				2 + (ws2812->numOfLEDS - ws2812->delay) * 3;

            uint32_t RGB = UserBuffer[index] + 
                    (((uint32_t)UserBuffer[index + 1]) <<8) +
                    (((uint32_t)UserBuffer[index + 2]) <<16);
			QueueRGB(RGB);


		}
        
        
	}

	if (ws2812->delay == 0 )
	{
		if(SPI1Semaphore == RESOURCE_AVAILABLE && DMA5Semaphore == RESOURCE_AVAILABLE)
		{
            if (ws2812->mode == WS2812_MODE_CHASE)
            {
			ws2812->delay = 200;
			++ ws2812->chaseLED;    
			if (ws2812->chaseLED >= ws2812->numOfLEDS)
			{
				ws2812->chaseLED = 0;
				++ws2812->chaseColor;
				if (ws2812->chaseColor > NUMBER_OF_COLORS)
				{
					ws2812->chaseColor = 0;
				}
			}
            }
            else if (ws2812->mode == WS2812_MODE_ANIMATION)
            {
                ws2812->delay = *(uint16_t*) &UserBuffer[ws2812->animationLedsIndex + ws2812->currentAnimationFrame * (2 + 3 * ws2812->numOfLEDS)];
                ++ws2812->currentAnimationFrame;
                if (ws2812->currentAnimationFrame == ws2812->animationFrames)
                {
                    ws2812->currentAnimationFrame = 0;
                }
            }
            else
            {

                ws2812->delay = ws2812->numOfLEDS + 10;
                
            }


			SPI1Semaphore= CurrentPin;
			DMA5Semaphore = CurrentPin;
			ws2812ConfigHardware();
			SendResetSignal();

			StartDMA();
		}
	}
	if (DMA5Semaphore == CurrentPin  && DMAINT5bits.DONEIF)
	{
		StopDMA();
		SetPPSOutput(CurrentPin, 0);
		DMA5Semaphore = RESOURCE_AVAILABLE;
		SPI1Semaphore = RESOURCE_AVAILABLE;


	}


}




