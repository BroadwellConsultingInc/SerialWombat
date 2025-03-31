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
#include "Font5x7.h"




typedef struct max7219Matrix_n{
	uint16_t outputBuffer;
    uint8_t dioPin;  
    uint8_t csPin;
	uint8_t numOfDisplays;
    uint8_t flipHorizontal:1;
    uint8_t flipVertical:1;
}max7219Matrix_t;


#define max7219 ((max7219Matrix_t*) CurrentPinRegister)
#define DIO_LOW() {PinLow(max7219->dioPin);}
#define   DIO_HIGH() {PinHigh(max7219->dioPin);}
#define  CLK_LOW() {  CurrentPinLow();}
#define CLK_HIGH() {     CurrentPinHigh();}
#define SET_DIO(_value) {    SetPin(max7219->dioPin, _value);}


#define MAX7219_NOP 0x0000
#define MAX7219_D0 0x0100
#define MAX7219_D1 0x0200
#define MAX7219_D2 0x0300
#define MAX7219_D3 0x0400
#define MAX7219_D4 0x0500
#define MAX7219_D5 0x0600
#define MAX7219_D6 0x0700
#define MAX7219_D7 0x0800
#define MAX7219_DECODE_MODE 0x0900
#define MAX7219_INTENSITY 0x0A00
#define MAX7219_SCAN_LIMIT 0x0B00
#define MAX7219_SHUTDOWN 0x0C00
#define MAX7219_DISPLAYTEST 0x0F00


static void max7219ClockWord(uint16_t data)
{
    uint8_t i;
    SetPin(CurrentPin,0);

	for (i = 0; i < 16; ++i)
	{
		SetPin(max7219->dioPin,(data & 0x8000) > 0);
		SetPin(CurrentPin,1);
		data <<=1;
        SetPin(CurrentPin,0);
	}

}
static void max7219ClockAllDisplays(uint16_t data)
{
    uint8_t d;
        SetPin(max7219->csPin,0);
    for (d = 0; d < max7219->numOfDisplays; ++d)
    {
        max7219ClockWord(data);
    }
        SetPin(max7219->csPin,1);
}


void max7219_hwinit()
{
	InitializePinLow(CurrentPin);
    InitializePinLow(max7219->dioPin);
        InitializePinLow(max7219->csPin);
    PinOD(CurrentPin);
                PinOD(max7219->dioPin);
                PinOD(max7219->csPin);
	PinHigh(max7219->dioPin);
    PinHigh(max7219->csPin);
}





typedef enum {
    
    TM1637_OUTPUT_STATE_SETUP = 0xF0,
    TM1637_OUTPUT_STATE_SET_ADDR = 0xF1,
    TM1637_OUTPUT_STATE_DISPLAY_CONTROL_COMMAND = 0xF2,
    TM1637_OUTPUT_STATE_SKIP_DISPLAY_CONTROL = 0xF3,
    TM1637_OUTPUT_STATE_IDLE = 0xF4
}TM1637_OUTPUT_STATE_t;

/*!
    \brief Initialization routine for TM1637 Seven Segment 

----
//TODO:  UPDATE!

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

Set TM1637 Brightness and Leading Zero Suppression


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) |Brightness (0-7) or 0x55 for unchanged |Leading Zero Supression (0,1, or 0x55 for unchanged) |Unused/0x55* |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19  TM1637 Brightness to level 3, leading zero supression

> `0xC3 0x13 0x0A 0x03 0x01 0x55 0x55 0x55  `


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


CONFIGURE_CHANNEL_MODE_6:
---------------------

Set TM1637 Decimal Points

The bottom 6 LSB are used as decimal points for digits 0-5 (before location translation)

Note that the way TM1637 displays are wired varies a lot from display to display, so this command may not work as expected.
Consult the TM1637 and LED module datasheets.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC6|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) | Decimal Point Bitmap |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19  TM1637 Decimal Point third digit decimal on

> `0xC6 0x13 0x0A 0x04 0x55 0x55 0x55 0x55  `

CONFIGURE_CHANNEL_MODE_7:
---------------------

Set TM1637 Digit Blink

The bottom 6 LSB are used as indicators that the digits indicated as 1's should blink



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC7|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) | Blink Bitmap |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 19  Blink 2nd and 3rd digit

> `0xC7 0x13 0x0A 0x06 0x55 0x55 0x55 0x55  `

CONFIGURE_CHANNEL_MODE_8:
---------------------

Write 1 byte to string mode.

Moves 1 byte into rightmost digit, and shifts all other digits 1 leftward.  Used 
for compatibility with Arduino Print::write function.



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC8|Pin To Set (TO TM1637 Clock)|0x0A (TM1637 ) | Byte to Write |Unused/0x55* |Unused/0x55* |Unused/0x55* |Unused/0x55* | 

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Write an ascii 7 to TM1637 on pin 19.\

> `0xC8 0x13 0x0A 0x37 0x55 0x55 0x55 0x55  `

*/

void initMax7219Matrix (void)
{
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_MAX7219MATRIX)
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
				
				max7219->dioPin = Rxbuffer[3];
                max7219->csPin = Rxbuffer[4];
                max7219->numOfDisplays = Rxbuffer[5];
                max7219->flipHorizontal = Rxbuffer[6] == 1;
                max7219->flipVertical = Rxbuffer[7] == 1;
                max7219->outputBuffer = 0xFFFF;
				SetMode(max7219->dioPin, PIN_MODE_CONTROLLED);
				SetMode(max7219->csPin, PIN_MODE_CONTROLLED);
                
                CurrentPinRegister->generic.mode =PIN_MODE_MAX7219MATRIX;
				max7219_hwinit();
                
                max7219ClockAllDisplays(MAX7219_SHUTDOWN | 0x0001);
                
                max7219ClockAllDisplays(MAX7219_INTENSITY );
                max7219ClockAllDisplays(MAX7219_DISPLAYTEST );
                
                max7219ClockAllDisplays(MAX7219_SCAN_LIMIT | 7 );


                  max7219ClockAllDisplays(MAX7219_DECODE_MODE );


                  uint16_t d;
                  for (d = 1; d <= 8; ++ d)
                  {
                      int r;
                      for (r = 0; r < max7219->numOfDisplays; ++r)
                      {
                      max7219ClockAllDisplays(d <<8); // Clear lines
                      }
                  }

                    
                      
			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
                SetPin(max7219->csPin,0);  
                max7219ClockWord(RXBUFFER16(3));
                if (Rxbuffer[5])
                {
                     SetPin(max7219->csPin,1);  
                }
			}
			break;

		case CONFIGURE_CHANNEL_MODE_2:
			{
                max7219->outputBuffer = RXBUFFER16(3);
			}
			break;
/*
		case CONFIGURE_CHANNEL_MODE_3: 
			{
			
                    if (Rxbuffer[3] != 0x55)
                    {
                        tm1637->brightness = Rxbuffer[3] & 0x07;
                    }
                    if (Rxbuffer[4] != 0x55)
                    {
                        tm1637->suppressLeadingZeros = (Rxbuffer[4] > 0);
                    }
				
				
			}
			break;

		case CONFIGURE_CHANNEL_MODE_4: 
			{
				
					tm1637->outputBuffer[0] = Rxbuffer[3];
					tm1637->outputBuffer[1] = Rxbuffer[4];
					tm1637->outputBuffer[2] = Rxbuffer[5];
					tm1637->outputBuffer[3] = Rxbuffer[6];
					tm1637->outputBuffer[4] = Rxbuffer[7];
				
			}
			break;
		case CONFIGURE_CHANNEL_MODE_5: 
			{
				
					tm1637->outputBuffer[5] = Rxbuffer[3];
				
				
			}
			break;
            case CONFIGURE_CHANNEL_MODE_6: 
			{
				
					tm1637->decimalPointBitmap = Rxbuffer[3];
				
			}
			break;
            
             case CONFIGURE_CHANNEL_MODE_7: 
			{
				
					tm1637->blinkBitmap = Rxbuffer[3];
				
			}
			break;
            
             case CONFIGURE_CHANNEL_MODE_8: 
			{
				
                    if (tm1637->mode != TM1637_MODE_STRING)
					{
                        error(SW_ERROR_TM1637_WRONG_MODE);
                        return;
                    }          
                    if (Rxbuffer[3] > 4)
                    {
                        error(SW_ERROR_CMD_BYTE_3);
                        return;
                    }
                    uint8_t i;
                    for (i = 0; i < Rxbuffer[3]; ++i)
                    {
                    tm1637->outputBuffer[0] = tm1637->outputBuffer[1];
                    tm1637->outputBuffer[1] = tm1637->outputBuffer[2];
                    tm1637->outputBuffer[2] = tm1637->outputBuffer[3];
                    tm1637->outputBuffer[3] = tm1637->outputBuffer[4];
                    tm1637->outputBuffer[4] = tm1637->outputBuffer[5];
                    tm1637->outputBuffer[tm1637->lastDigit] = Rxbuffer[4 + i];
                    }
				
			}
			break;
 */           

		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}
}

#if 0
tm1637_t* debugTM1637;
/// \brief Create a TM1637 bitmap in the displayArray
///
/// This function renders a number or string into an array of LED segments
/// or copies segements from the outputBuffer or User Buffer area based
/// on the mode.   
/// 
/// The decimal point is then ORed in if required.
/// 
/// The rendered array is then rearranged to the proper order in the displayArray
/// to correspond to the way that the TM1637 GRID lines are wired to the digit
/// common anode lines (The leftmost digit doesn't always go to grid 1, depending on
/// the display PCB layout).
void tm1637UpdateRender()
{
    uint8_t renderArray[6];
    bool noDigitsFound = true;
	
	if (tm1637->mode == TM1637_MODE_BUFFER_DEC)
	{
		renderArray[0] = '0';
		uint16ToAscii5(GetBuffer(tm1637->outputBuffer[0]) ,&renderArray[1]);  
        uint8_t i;
         for (i = 0; i < 6; ++i)
         {
             bool render = true;
             if (renderArray[i] == '0')
             {
                if (tm1637->suppressLeadingZeros && //Don't suppress if suppression turned off
                        noDigitsFound &&            //Don't suppress if we've already found a non-zero
                        i != tm1637->lastDigit  &&  //Don't suppress if last displayed digit
                        tm1637->blinkBitmap == 0)   //Don't suppress if we're blinking digits
                {
                    renderArray[i] = seven_seg_table[' '];
                    render = false;
                }
             }
             else
             {
                 noDigitsFound = false;
             }
             if (render)
             {
                renderArray[i] =seven_seg_table[renderArray[i]];
             }
         }
	}
	else if (tm1637->mode == TM1637_MODE_BUFFER_HEX)
	{
		renderArray[0] = ' ';
		renderArray[1] = ' ';
		 uint16ToAsciiHex4(GetBuffer(tm1637->outputBuffer[0]), &renderArray[2]) ;
         uint8_t i;
         for (i = 0; i < 6; ++i)
         {
             renderArray[i] =seven_seg_table[renderArray[i]];
         }
	}
	else if (tm1637->mode == TM1637_MODE_RAW)
	{
		renderArray[0] = tm1637->outputBuffer[0];
		renderArray[1] = tm1637->outputBuffer[1];
		renderArray[2] = tm1637->outputBuffer[2];
		renderArray[3] = tm1637->outputBuffer[3];
		renderArray[4] = tm1637->outputBuffer[4];
		renderArray[5] = tm1637->outputBuffer[5];
	}
	
	else if (tm1637->mode == TM1637_MODE_STRING)
	{
		uint8_t i;
		for (i = 0; i < 6; ++i)
		{
			uint8_t value = tm1637->outputBuffer[i];
			if (value < 0x80)
			{
			    	value = seven_seg_table[value];
			}
			else
			{
				value &= 0x7F;
			}
			renderArray[i] =  value;
		}
	}
    else if (tm1637->mode == TM1637_MODE_ANIMATION)
	{
        uint16_t index = tm1637->outputBuffer[5] * 6 + tm1637->outputBuffer[0] + (((uint16_t)tm1637->outputBuffer[1]) << 8);
		renderArray[0] = UserBuffer[index++];
		renderArray[1] = UserBuffer[index++];
		renderArray[2] = UserBuffer[index++];
		renderArray[3] = UserBuffer[index++];
		renderArray[4] = UserBuffer[index++];
		renderArray[5] = UserBuffer[index];
        ++tm1637->outputBuffer[5];
        if (tm1637->outputBuffer[5] >= tm1637->outputBuffer[4] )
        {
            tm1637->outputBuffer[5] = 0;
        }
	}

    if (tm1637->blinkBitmap && ((FramesRun & 0x0380) ==0)) // Blink based on FramesRun which increments every 1ms
    {
        uint8_t i;
        for (i = 0; i < 6; ++i)
        {
            if (tm1637->blinkBitmap & (1 << i))
        {
            renderArray[ i] = seven_seg_table[' '];
        }
        }
    }
    if (tm1637->decimalPointBitmap)
    {
        uint8_t i;
	for (i = 0; i < 6; ++i)
	{
        if (tm1637->decimalPointBitmap & (1 << i))
        {
            renderArray[ i] |= 0x80;
        }
    }
    }
    
    

    {
        uint8_t i;
	for (i = 0; i < 6; ++i)
	{
		tm1637->displayArray[i] = renderArray[tm1637->displayOrder[i]];
	}
    }
}


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
void updateTM1637()
{ 

    debugTM1637 = (tm1637_t*)CurrentPinRegister;

	switch (tm1637->outputState)
	{
		case TM1637_OUTPUT_STATE_SETUP:
			{
				tm1637UpdateRender();

				if (
						tm1637->lastDisplay[0] == tm1637->displayArray[0] &&
						tm1637->lastDisplay[1] == tm1637->displayArray[1] &&
						tm1637->lastDisplay[2] == tm1637->displayArray[2] &&
						tm1637->lastDisplay[3] == tm1637->displayArray[3] &&
						tm1637->lastDisplay[4] == tm1637->displayArray[4] &&
						tm1637->lastDisplay[5] == tm1637->displayArray[5]
				   )
				{
					//Nothing changed.  Go to idle
					if (tm1637->mode == TM1637_MODE_ANIMATION)
					{
						//Load custom animation delay
						*((uint8_t*)(&tm1637->idleCounter)) = tm1637->outputBuffer[2];   
						*(((uint8_t*)(&tm1637->idleCounter)) +1) = tm1637->outputBuffer[3];   

					}
					else
					{
						//Use standard delay
						tm1637->idleCounter = 20;
					}
					tm1637->outputState = TM1637_OUTPUT_STATE_IDLE;
				}
				else
				{

					tm1637Start();

					tm1637SendMemoryWrite();
					tm1637Stop();
					tm1637->outputState = TM1637_OUTPUT_STATE_SET_ADDR;
				}
			}
			break;

		case TM1637_OUTPUT_STATE_SET_ADDR:
			{
				tm1637Start();
				tm1637->outputState = tm1637SendInitialAddress();
				
				if (tm1637->outputState == 6)
				{
					//Nothing to do
					tm1637Stop();
					if (tm1637->mode == TM1637_MODE_ANIMATION)
					{
						*((uint8_t*)(&tm1637->idleCounter)) = tm1637->outputBuffer[2];   
						*(((uint8_t*)(&tm1637->idleCounter)) +1) = tm1637->outputBuffer[3];   

					}
					else
					{
						tm1637->idleCounter = 20;
					}
					tm1637->outputState = TM1637_OUTPUT_STATE_IDLE;

				}
			}
			break;

		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			{

				uint8_t value = 0;

				//if (tm1637->mode == TM1637_MODE_RAW  || tm1637->mode == TM1637_MODE_STRING  || tm1637->mode == TM1637_MODE_ANIMATION)
				//{
					value = tm1637->displayArray[tm1637->outputState];

				//}
				//else
				//{
				//	value = seven_seg_table[(tm1637->displayArray[tm1637->outputState])];
				//}
				tm1637ClockByte(value);
				tm1637->lastDisplay[tm1637->outputState] = value;
				++ tm1637->outputState;
                 uint8_t i;
                 bool done = true;
                for (i = tm1637->outputState; i <= tm1637->lastDigit; ++ i)
                {
                    if(tm1637->lastDisplay[i] != tm1637->displayArray[i])
                    {
                        done = false;
                        break;
                    }
                }
                
				if (tm1637->outputState > tm1637->lastDigit || done )
				{
					tm1637Stop();
					if (tm1637->mode == TM1637_MODE_ANIMATION)
					{
						*((uint8_t*)(&tm1637->idleCounter)) = tm1637->outputBuffer[2];   
						*(((uint8_t*)(&tm1637->idleCounter)) +1) = tm1637->outputBuffer[3];   

					}
					else
					{
						tm1637->idleCounter = 20;
					}
					if (tm1637->lastBrightness != tm1637->brightness)
					{
						tm1637->outputState = TM1637_OUTPUT_STATE_DISPLAY_CONTROL_COMMAND;
					}
					else
					{
						tm1637->outputState = TM1637_OUTPUT_STATE_IDLE;                        
					}
				}
			}

			break;

		case TM1637_OUTPUT_STATE_DISPLAY_CONTROL_COMMAND:
			{

				tm1637Start();
				tm1637SendDisplayControlCommand(tm1637->brightness);
				tm1637Stop();
				tm1637->outputState = TM1637_OUTPUT_STATE_IDLE;

			}
			break;

		case TM1637_OUTPUT_STATE_IDLE:
			{
				if (tm1637->idleCounter > 0)
				{
					--tm1637->idleCounter;
				}
				else 
				{
					tm1637->outputState = TM1637_OUTPUT_STATE_SETUP;
				}


			}
			break;
	}

}

#endif
volatile uint16_t debugLastClockedOut = 0;
void updateMax7219Matrix()
{
    if (max7219->outputBuffer != 0xFFFF)
    {
       extern uint32_t FramesRun;
		if (FramesRun & 0x3FF ) return;
    int d;
    uint8_t *buffer = &UserBuffer[max7219->outputBuffer ];
    if (max7219->flipHorizontal)
    {
      buffer = &UserBuffer[max7219->outputBuffer + 8 * max7219->numOfDisplays - 1];
    }

        uint16_t l;
        debugLastClockedOut = 0xFFFF;
        
       for (l = 0x100; l <= 0x800; l+= 0x100)
       {
           SetPin(max7219->csPin,0);       
      for (d = 0; d < max7219->numOfDisplays; ++d)
      {
               uint8_t output = * buffer;
                if (max7219->flipHorizontal)
             {
                 uint8_t output2 = 0;
                 if (output & 0x80) output2 |= 0x01;  //TODO optimize with assembly call
                 if (output & 0x40) output2 |= 0x02;  //TODO optimize with assembly call
                 if (output & 0x20) output2 |= 0x04;  //TODO optimize with assembly call
                 if (output & 0x10) output2 |= 0x08;  //TODO optimize with assembly call
                 if (output & 0x08) output2 |= 0x10;  //TODO optimize with assembly call
                 if (output & 0x04) output2 |= 0x20;  //TODO optimize with assembly call
                 if (output & 0x02) output2 |= 0x40;  //TODO optimize with assembly call
                 if (output & 0x01) output2 |= 0x80;  //TODO optimize with assembly call
                 output = output2;
             }
         if (max7219->flipVertical ^ max7219->flipHorizontal)
         {
           
            
                debugLastClockedOut = (0x900-l) | output;
         }
         else
         {
             debugLastClockedOut = l | output;
         }
            max7219ClockWord(debugLastClockedOut);
            if (max7219->flipHorizontal)
            {
                --buffer;
            }
            else
            {
                ++buffer;
            }
        }
           SetPin(max7219->csPin,1);       
                    
          //      max7219ClockAllDisplays(0);// NOP
                
    }
    }
    
}

