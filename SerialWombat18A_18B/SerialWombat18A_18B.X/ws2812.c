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
#include "asciiConversion.h"


typedef enum 
{
    WS2812_MODE_BUFFERED = 0,
            WS2812_MODE_ANIMATION = 1,
            WS2812_MODE_CHASE = 2,
            WS2812_MODE_BARGRAPH = 3,
    
}ws2812_mode_t;

typedef struct ws2812{
    uint32_t offColor;
    uint32_t onColor;
    uint16_t* dmaQueuePosition;
    uint16_t userBufferIndex;
    uint16_t animationLedsIndex;
    uint16_t delay ;
    uint16_t bgMax;
    uint16_t bgMin;
    uint8_t numOfLEDS;
    uint8_t chaseColor;
    uint8_t chaseLED;
    uint8_t mode;
    uint8_t animationFrames;
    uint8_t currentAnimationFrame;
    uint8_t bgSourcePin;
     uint8_t bgOnLEDs;
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
    DMADST5 =(uint16_t) &SPI1BUFL;
    DMASRC5 = (uint16_t) dmaBuffer;
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

Initialize WS2812 Output


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set |0x0C  | userBufferIndex LSB |userBufferIndex MSB | Number of LEDS |Unused 0x55*  |Unused 0x55* |

\*0x55 is recommended, but any byte is acceptable


Response:

Command is echoed back.

Examples:

Set pin 19 to WS2812, user buffer index of 0x180, 16 LEDS

> `0xC0 0x13 0x0B 0x80 0x01 0x10 0x55 0x55 `

----


CONFIGURE_CHANNEL_MODE_1:
---------------------

Set an LED RGB Value.  Index 0 also sets off mode for Bargraph, Index 1 also sets on Mode for bargraph.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set |0x0B  |LED index (0 to (Num LEDs - 1)) |Blue (0-255) | Green(0-255) |Red (0-255) |Unused 0x55* |
\*0x55 is recommended, but any byte is acceptable



Response:

Command is echoed back.

Examples:

Set Pin 16,  LED 7 to RGB value 0x002532BF


> `0xC1 0x13 0x0B 0x07 0xBF 0x32 0x25 0x55 `



----

CONFIGURE_CHANNEL_MODE_2:
---------------------

Respond with number of bytes needed in User Buffer to store a support a specified number of LEDS



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set |0x0B |Number of LEDS |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set |0x0B |Number of Bytes MSB |Number of Bytes LSB |Unused/0x55* |Unused/0x55* |Unused/0x55* |

Examples:

Set Pin 16,  Request byte count for 15 LEDS


> `0xC2 0x13 0x0B 0x0F 0x55 0x55 0x55 0x55 `
Response (assume answer is 725 bytes (0x2D5):
> `0xC2 0x13 0x0B 0xD5 0x02 0x55 0x55 0x55 `

CONFIGURE_CHANNEL_MODE_3:
---------------------

Set an LED RGB Value in an animation frame.  This command cannot be called until the Animation buffer index is set with command 0xC4


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set |0x0B  |Frame Index | LED index (0 to (Num LEDs - 1)) |Blue (0-255) | Green(0-255) |Red (0-255) |



Response:

Command is echoed back.

Examples:

Set Pin 16,  Frame 3 LED 7 to RGB value 0x002532BF


> `0xC1 0x13 0x0B 0x03 0x07 0xBF 0x32 0x25 `



CONFIGURE_CHANNEL_MODE_4:
---------------------

Set the index of the animation frames area and the number of frames.   The animation frames area is separate from the buffer defined in command 0xC0 and cannot overlap.   The length of this area is (2 + 3 * NumLeds)* NumFrames.  

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC4|Pin To Set|0x0B |Animation Buffer Index LSB|Animation Buffer Index MSB|Number of Animation Frames|Unused 0x55* | Unused 0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set the animation buffer index to 0x0440 and the number of frames to 10

> `0xC0 0x13 0x0B 0x40 0x04 0x0A 0x55 0x05 `



CONFIGURE_CHANNEL_MODE_5:
---------------------

Set the delay for an animation frame in mS.  This command must not be called before the animation buffer index is set with command  0xC4.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC5|Pin To Set|0x0B | Frame Index |delay LSB |delay MSB |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19  Animation frame 2 to a delay of 8000 ms (0x1F40)

> `0xC5 0x13 0x0B 0x02 0x40 0x1F 0x55 0x55  `

CONFIGURE_CHANNEL_MODE_7:
---------------------

 Set the bargraph mode min and max values

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC6|Pin To Set|0x0B | bargraph min lsb |bargraph min msb |bargraph max lsb |bargraph max msb |  Unused/0x55* | 

 
\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19 bargraph min 1000, max 64000

> `0xC7 0x13 0x0B 0x0E8 0x03 0x00 0xFA 0x55  

*/



void initWS2812 (void)
{

    debugWS2812 = (ws2812_t*) CurrentPinRegister;
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
                ws2812->userBufferIndex = RXBUFFER16(3);
                ws2812->animationLedsIndex = 0x0000; // Will cause invalid writes if not set
                ws2812->animationFrames = 0;
                ws2812->numOfLEDS = Rxbuffer[5];
                ws2812->dmaQueuePosition = dmaBuffer;
                ws2812->chaseColor = 0;
                ws2812->chaseLED = 0;
                ws2812->delay = 0;
                ws2812->mode = 0;
                ws2812->bgMax = 65535;
                ws2812->bgMin  = 0;
                
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
					uint32_t rgb = (RXBUFFER32(4) & 0x00FFFFFF);
					uint16_t index = ws2812->userBufferIndex + ((uint16_t) Rxbuffer[3])*24 * 2 + RESET_SIGNAL_LENGTH * 2;
					if (Rxbuffer[3] >=  ws2812->numOfLEDS)
					{
						error(SW_ERROR_WS2812_INDEX_GT_LEDS);
					}
					else if (index + 48 > SIZE_OF_USER_BUFFER)
					{
						error(SW_ERROR_WUB_INVALID_ADDRESS);
					}
					else
					{
                        
                            if (Rxbuffer[3] == 0)
                            {
                                ws2812->offColor = rgb;
                            }
                            else if (Rxbuffer[3] == 1)
                            {
                                ws2812->onColor = rgb;
                            }
                       
						ws2812->dmaQueuePosition = 
							(uint16_t*)&UserBuffer[ index ];
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
                    UserBuffer[ index ] = Rxbuffer[7];
                    UserBuffer[ index + 1 ] = Rxbuffer[6];
                    UserBuffer[ index + 2 ] = Rxbuffer[5];
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
                    if (Rxbuffer[3] <= WS2812_MODE_BARGRAPH)
                    {
                        ws2812->mode = Rxbuffer[3];
                        if (ws2812->mode == WS2812_MODE_BARGRAPH)
                        {
                            ws2812->bgSourcePin = Rxbuffer[4];
                        }
                    }
                    else
                    {
                        error(SW_ERROR_INVALID_PARAMETER_3);
                    }
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;
            
            case CONFIGURE_CHANNEL_MODE_7: 
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
				{
                    ws2812->bgMin = RXBUFFER16(3);
                    ws2812->bgMax = RXBUFFER16(5);
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
/// \brief update the WS2812 pin state machine
///

void updateWS2812()
{
	debugWS2812 = (ws2812_t*) CurrentPinRegister;
	if (ws2812->delay)
	{
		-- ws2812->delay;
	}
	if (ws2812->delay > ws2812->numOfLEDS)
	{

	}
    else if (ws2812->delay == 0)
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
		else if (ws2812->mode == WS2812_MODE_ANIMATION)
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
       else if (ws2812->mode == WS2812_MODE_BARGRAPH)
            {
           if (ws2812->delay == ws2812->numOfLEDS )
            {
                 ws2812->bgOnLEDs = 0;

                uint32_t value = GetBuffer(ws2812->bgSourcePin);
                if (value >= ws2812->bgMax)
                {
                    ws2812->bgOnLEDs = ws2812->numOfLEDS;    
                }
                else if (value <= ws2812->bgMin)
                {
                    ws2812->bgOnLEDs = 0;    
                }
                else if ((ws2812->bgMin == 0 && ws2812->bgMax == 65535) || ws2812->bgMax == ws2812->bgMin)
                {
                    value *= ws2812->numOfLEDS;
                    value >>= 16;
                    ws2812->bgOnLEDs = value;
                }
                else
                {
                    value -= ws2812->bgMin;
                    value <<= 16;
                    value /= (ws2812->bgMax - ws2812->bgMin);
                    value *= ws2812->numOfLEDS;
                    value >>= 16;
                    ws2812->bgOnLEDs = value;
                }
                
            }
           if (ws2812->numOfLEDS - ws2812->delay >= ws2812->bgOnLEDs )
           {
               QueueRGB(ws2812->offColor);
           }
           else
           {
               QueueRGB(ws2812->onColor);
           }
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
                uint16_t index = ws2812->animationLedsIndex + ws2812->currentAnimationFrame * (2 + 3 * ws2812->numOfLEDS);
                ws2812->delay = UserBuffer[index + 1];  // Do it byte by byte.  May be a non-word aligned address.
                ws2812->delay <<= 8;
                ws2812->delay += UserBuffer[index];
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




