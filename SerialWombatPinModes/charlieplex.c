/*
Copyright 2026 Broadwell Consulting Inc.

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

/* Serial Wombat is a registered trademark of Broadwell Consulting Inc. */
#include "serialWombat.h"
#include "outputScale.h"

#define CHARLIEPLEX_MAX_PINS 8
#define CHARLIEPLEX_MAX_LEDS (CHARLIEPLEX_MAX_PINS * (CHARLIEPLEX_MAX_PINS -1))
#define CHARLIEPLEX_ARRAY_SIZE ((CHARLIEPLEX_MAX_LEDS / 8 ) + ((CHARLIEPLEX_MAX_LEDS % 8 != 0)?1:0))


typedef struct charlieplex_n{
	outputScale_t outputScale;
	uint8_t ledArray[CHARLIEPLEX_ARRAY_SIZE];  // [0] lsb is 0,1 with 0 low.  [0] bit 0x02 is 0,1 with 0 high.  [0] bit 0x04 is 0,2 with 0 low, and so on
	uint8_t ledArrayCopy[CHARLIEPLEX_ARRAY_SIZE];  // At the begining of each update  ledArray is copied here and then the bits are picked off one by one
	uint8_t pinNumbers[CHARLIEPLEX_MAX_PINS];
	uint8_t displayMode; // 0 = All LEDs array, 1 = public data is bitfield for first 16 LEDs.  the rest by protocol. 2 = only public data LED  , 3 = all up to public data  
	uint8_t scanPeriod_mS; // Used to add delay frames with no leds on to equalize brightness 
	uint8_t numberOfPins; // Number of pins used to Charlieplex (at least 2)
	uint8_t updateCounter; // Used to add delay frames with no leds on to equalize brightness 

}charlieplex_t;

typedef struct charlieplexLookup_n{
	uint8_t charliePinArray[CHARLIEPLEX_MAX_LEDS];
}charlieplexLookup_t;

const uint8_t charliePinArray[CHARLIEPLEX_MAX_LEDS] = {
	0x10,
	0x01,
	0x20,
	0x02,
	0x21,
	0x12,
	0x30,	
	0x03,
	0x31,
	0x13,
	0x32,
	0x23,
	0x40,
	0x04,
	0x41,
	0x14,
	0x42,
	0x24,
	0x43,
	0x34,
	0x50,
	0x05,
	0x51,	
0x15,
	0x52,
	0x25,
	0x53,
	0x35,
	0x54,
	0x45,
	0x60,
	0x06,
	0x61,
	0x16,
	0x62,
	0x26,
	0x63,
	0x36,
	0x64,
	0x46,
	0x65,
	0x56,
	0x70,
	0x07,
	0x71,
	0x17,
	0x72,
	0x27,
	0x73,
	0x37,
	0x74,
	0x47,
	0x75,
	0x57,
	0x76,
	0x67,
};

static void allPinsInput()
{
	charlieplex_t* charlie = (charlieplex_t*)CurrentPinRegister;
	for (int i = 0; i < charlie->numberOfPins; i++)
	{
		PinInput(charlie->pinNumbers[i]);
	}
}

static void clearUnusedBits()
{
	charlieplex_t* charlie = (charlieplex_t*)CurrentPinRegister;
	int i;
	for (i = charlie->numberOfPins * (charlie->numberOfPins - 1); i < CHARLIEPLEX_MAX_LEDS; i++)
	{
		charlie->ledArray[i / 8] &= ~(1 << (i % 8));
	}
}

/*!
    \brief Initialization and protocol-processing routine for the Charlieplex LED pin mode.

The Charlieplex pin mode uses between 2 and 8 physical pins to control up to
N * (N - 1) LEDs.  The pin on which this mode is configured is logical pin 0
and is the controlling pin.  Logical pin 1 stores the customizable 56-byte
LED-to-pin-pair lookup table in its pin update register memory.

Each lookup-table byte encodes one logical LED connection:

- Bits 7:4 contain the logical pin index driven high.
- Bits 3:0 contain the logical pin index driven low.

For example, a lookup value of 0x62 drives logical pin 6 high and logical pin
2 low.  Unused physical-pin fields should be set to 0xFF.

Display modes:

- 0: The seven-byte LED bitmap is written using CONFIGURE_CHANNEL_MODE_2 and
  CONFIGURE_CHANNEL_MODE_3.
- 1: The controlling pin's 16-bit public data is used as the bitmap for LEDs
  0 through 15.
- 2: The scaled-output value selects one logical LED.
- 3: The scaled-output value lights a bar from LED 0 through the selected
  logical LED, inclusive.

In the examples below, `CP` represents the numeric value assigned to
`PIN_MODE_CHARLIEPLEX`.

----

CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize the Charlieplex pin mode, configure logical pins 0 through 2, and
initialize the lookup table to the default logical LED ordering.  Logical pin
1 must be a valid physical pin and must not be the controlling pin because its
pin update register memory stores the lookup table.  For a two-pin display,
BYTE 7 should be 0xFF.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC0|Controlling pin|PIN_MODE_CHARLIEPLEX|Number of pins, 2 through 8|Display mode, 0 through 3|Minimum scan period in ms|Logical pin 1 / lookup-storage pin|Logical pin 2 or 0xFF|

The recommended scan-period range is 0 through 56.  A value of zero adds no
blank frames between scans.  If the number of enabled LEDs is greater than the
configured period, the scan naturally takes longer than the requested period.

Response:

Command is echoed back.

Example:

Initialize controlling pin 0 with four Charlieplex pins, bitmap display mode,
a 12 ms minimum scan period, physical pin 1 as logical pin 1, and physical pin
2 as logical pin 2.

> `0xC0 0x00 CP 0x04 0x00 0x0C 0x01 0x02`

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Configure logical pins 3 through 7.  This command must follow
CONFIGURE_CHANNEL_MODE_0.  Send 0xFF for logical pins not used by the selected
pin count.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC1|Controlling pin|PIN_MODE_CHARLIEPLEX|Logical pin 3 or 0xFF|Logical pin 4 or 0xFF|Logical pin 5 or 0xFF|Logical pin 6 or 0xFF|Logical pin 7 or 0xFF|

Response:

Command is echoed back.

Example:

Complete the four-pin configuration above by assigning physical pin 3 as
logical pin 3 and marking the remaining logical pins unused.

> `0xC1 0x00 CP 0x03 0xFF 0xFF 0xFF 0xFF`

----

CONFIGURE_CHANNEL_MODE_2:
---------------------

Write bitmap bytes 0 through 4.  Bit 0 of BYTE 3 controls logical LED 0 and bit
7 of BYTE 7 controls logical LED 39.  Bits for LEDs that do not exist for the
configured pin count are cleared by the firmware.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC2|Controlling pin|PIN_MODE_CHARLIEPLEX|LED bits 0-7|LED bits 8-15|LED bits 16-23|LED bits 24-31|LED bits 32-39|

Response:

Command is echoed back.

Example:

Set logical LEDs 0, 1, and 8 in the first five bitmap bytes.

> `0xC2 0x00 CP 0x03 0x01 0x00 0x00 0x00`

----

CONFIGURE_CHANNEL_MODE_3:
---------------------

Write bitmap bytes 5 and 6.  These bytes control logical LEDs 40 through 55.
BYTEs 5 through 7 are unused.  Bits for LEDs that do not exist for the
configured pin count are cleared by the firmware.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC3|Controlling pin|PIN_MODE_CHARLIEPLEX|LED bits 40-47|LED bits 48-55|Unused|Unused|Unused|

Response:

Command is echoed back.

Example:

Set logical LED 40 and clear LEDs 48 through 55.

> `0xC3 0x00 CP 0x01 0x00 0x55 0x55 0x55`

----

CONFIGURE_CHANNEL_MODE_4:
---------------------

Write up to four consecutive entries in the customizable logical LED lookup
table.  BYTE 3 specifies the first logical LED index.  BYTEs 4 through 7
contain encoded high-pin/low-pin pairs.  Writes that reach the end of the
56-entry table are truncated.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC4|Controlling pin|PIN_MODE_CHARLIEPLEX|First logical LED index, 0-55|Lookup entry 0|Lookup entry 1|Lookup entry 2|Lookup entry 3|

Response:

Command is echoed back.

Example:

Map logical LEDs 12 through 15 to encoded pin pairs 0x30, 0x03, 0x31, and
0x13.

> `0xC4 0x00 CP 0x0C 0x30 0x03 0x31 0x13`

----

CONFIGURE_CHANNEL_MODE_5:
---------------------

Set up to five logical LED bits in the firmware bitmap without changing any
other LED bits.  Each field is a logical LED index from 0 through 55.  Use
0xFF for unused fields.  Other out-of-range values are ignored.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC5|Controlling pin|PIN_MODE_CHARLIEPLEX|LED index or 0xFF|LED index or 0xFF|LED index or 0xFF|LED index or 0xFF|LED index or 0xFF|

Response:

Command is echoed back.

Example:

Set logical LEDs 1, 4, and 9.

> `0xC5 0x00 CP 0x01 0x04 0x09 0xFF 0xFF`

----

CONFIGURE_CHANNEL_MODE_6:
---------------------

Clear up to five logical LED bits in the firmware bitmap without changing any
other LED bits.  Each field is a logical LED index from 0 through 55.  Use
0xFF for unused fields.  Other out-of-range values are ignored.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC6|Controlling pin|PIN_MODE_CHARLIEPLEX|LED index or 0xFF|LED index or 0xFF|LED index or 0xFF|LED index or 0xFF|LED index or 0xFF|

Response:

Command is echoed back.

Example:

Clear logical LEDs 4 and 9.

> `0xC6 0x00 CP 0x04 0x09 0xFF 0xFF 0xFF`

----

CONFIGURE_CHANNEL_MODE_10:
----------------------

Configure the Serial Wombat scaled-output block used by display modes 2 and
3.  BYTEs 3 through 7 are processed by `outputScaleCommProcess()`.  See the
Serial Wombat scaled-output protocol documentation for the available
subcommands and payload formats.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xCA|Controlling pin|PIN_MODE_CHARLIEPLEX|Scaled-output command data|Scaled-output command data|Scaled-output command data|Scaled-output command data|Scaled-output command data|

Response:

Command is echoed back.

*/
void initCharliePlex()
{
	charlieplex_t* charlie = (charlieplex_t*)CurrentPinRegister;
  BUILD_BUG_ON( sizeof(charlieplex_t) >  BYTES_PER_PIN_REGISTER );
  BUILD_BUG_ON( sizeof(charlieplexLookup_t) > BYTES_PER_PIN_REGISTER);
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_CHARLIEPLEX)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				int i;
				charlie->numberOfPins = Rxbuffer[3];
				if ( charlie->numberOfPins > CHARLIEPLEX_MAX_PINS)
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
					return;
				}
				charlie->displayMode = Rxbuffer[4];


				/*
 * scanPeriod_mS must be 0 through CHARLIEPLEX_MAX_LEDS.
 * Larger values are invalid but do not create an unsafe condition,
 * so the range is not enforced to conserve flash.
 */
				charlie->updateCounter = charlie->scanPeriod_mS = Rxbuffer[5];
				
								if ( Rxbuffer[6] >= NUMBER_OF_TOTAL_PINS || Rxbuffer[6]  == CurrentPin)
				{
					error(SW_ERROR_INVALID_PARAMETER_6);
					return;
				}
				charlie->pinNumbers[1] = Rxbuffer[6];
				SetMode(charlie->pinNumbers[1], PIN_MODE_CONTROLLED);
				charlie->pinNumbers[2] = Rxbuffer[7];
				
				SetMode(charlie->pinNumbers[2], PIN_MODE_CONTROLLED);

				CurrentPinRegister->generic.mode = PIN_MODE_CHARLIEPLEX;
				for (i = 0; i < CHARLIEPLEX_ARRAY_SIZE; i++)
				{
					charlie->ledArray[i] = 0;
					charlie->ledArrayCopy[i] = 0;
				}			
				charlie->pinNumbers[0] = CurrentPin;
				for (i = 3; i < CHARLIEPLEX_MAX_PINS; i++)
				{
					charlie->pinNumbers[i] = 0xFF;  // No connection
				}
				charlieplexLookup_t* lookup = (charlieplexLookup_t*)&PinUpdateRegisters[charlie->pinNumbers[1]];
				for (i = 0; i < CHARLIEPLEX_MAX_LEDS; i++)
				{
					lookup->charliePinArray[i] = charliePinArray[i];
				}
							    allPinsInput();
				outputScaleInit(&charlie->outputScale);
			}
			break;
			
		case CONFIGURE_CHANNEL_MODE_1: 
		
			{
				charlie->pinNumbers[3] = Rxbuffer[3];
				SetMode(charlie->pinNumbers[3], PIN_MODE_CONTROLLED);
				charlie->pinNumbers[4] = Rxbuffer[4];
				SetMode(charlie->pinNumbers[4], PIN_MODE_CONTROLLED);
				charlie->pinNumbers[5] = Rxbuffer[5];
				SetMode(charlie->pinNumbers[5], PIN_MODE_CONTROLLED);
								charlie->pinNumbers[6] = Rxbuffer[6];
				SetMode(charlie->pinNumbers[6], PIN_MODE_CONTROLLED);
				charlie->pinNumbers[7] = Rxbuffer[7];
				SetMode(charlie->pinNumbers[7], PIN_MODE_CONTROLLED);
			}
			break;
	
		case CONFIGURE_CHANNEL_MODE_2:
		{
				charlie->ledArray[0] = Rxbuffer[3];
				charlie->ledArray[1] = Rxbuffer[4];
				charlie->ledArray[2] = Rxbuffer[5];
				charlie->ledArray[3] = Rxbuffer[6];
				charlie->ledArray[4] = Rxbuffer[7];
				clearUnusedBits();
		} 
		break;

		case CONFIGURE_CHANNEL_MODE_3:
		{
				charlie->ledArray[5] = Rxbuffer[3];
				charlie->ledArray[6] = Rxbuffer[4];
				clearUnusedBits();
		}
		break;

		case CONFIGURE_CHANNEL_MODE_4:
		{
			    if (Rxbuffer[3] >= CHARLIEPLEX_MAX_LEDS)
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
					return;
				}
				charlieplexLookup_t* lookup = (charlieplexLookup_t*)&PinUpdateRegisters[charlie->pinNumbers[1]];
				{

				int i;
				for (i = 0; i < 4 && (i + Rxbuffer[3]) < CHARLIEPLEX_MAX_LEDS; i++)
				{
					lookup->charliePinArray[i + Rxbuffer[3]] = Rxbuffer[4 + i];
				}
			}
			}
			break;

		case CONFIGURE_CHANNEL_MODE_5: // Set up to five LEDs
		case CONFIGURE_CHANNEL_MODE_6: // Clear up to five LEDs
		{
			uint8_t setLEDs = (Rxbuffer[0] == CONFIGURE_CHANNEL_MODE_5);
			int i;

			for (i = 3; i < 8; ++i)
			{
				uint8_t ledIndex = Rxbuffer[i];

				/* 0xFF and any other out-of-range value are ignored. */
				if (ledIndex < CHARLIEPLEX_MAX_LEDS)
				{
					uint8_t mask = (uint8_t)(1u << (ledIndex & 7));

					if (setLEDs)
					{
						charlie->ledArray[ledIndex >> 3] |= mask;
					}
					else
					{
						charlie->ledArray[ledIndex >> 3] &= (uint8_t)~mask;
					}
				}
			}

			/* Remove any LEDs that do not exist for the configured pin count. */
			clearUnusedBits();
		}
		break;

		case CONFIGURE_CHANNEL_MODE_10:
        {
            outputScaleCommProcess(&charlie->outputScale);
        }
		break;
		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}


}

void updateCharlieplex()
{
	charlieplex_t* charlie = (charlieplex_t*)CurrentPinRegister;

	allPinsInput();
	charlie->updateCounter++;
	uint8_t allZeros = 1;
	int i;
	uint16_t outputValue = outputScaleProcess(&charlie->outputScale);
	for ( i = 0; i < CHARLIEPLEX_ARRAY_SIZE; i++)
	{
		if (charlie->ledArrayCopy[i] != 0)
		{
			allZeros = 0;
			break;
		}

	}

	if (allZeros)
	{
		if (charlie->updateCounter < charlie->scanPeriod_mS)
		{
			return;
		}
		else
		{
			charlie->updateCounter = 0;
		}
		if (charlie->displayMode == 1)
		{
			charlie->ledArray[0] = CurrentPinRegister->generic.buffer & 0xFF;
			charlie->ledArray[1] = CurrentPinRegister->generic.buffer >> 8;
			for (i = 2; i < CHARLIEPLEX_ARRAY_SIZE; ++i)
			{
				charlie->ledArray[i] = 0;
			}
			clearUnusedBits();
		}
		
		if (charlie->displayMode > 1)
		{
			 
		
     if (charlie->outputScale.sourcePin != CurrentPin)
    {
	CurrentPinRegister->generic.buffer = outputValue;  
     }
	 	for (i = 0; i < CHARLIEPLEX_ARRAY_SIZE; i++	)
		{
			charlie->ledArray[i] = 0;
		}

	 		 if (charlie->displayMode == 2)
		{
			uint16_t value = outputValue;
			if (value >= CHARLIEPLEX_MAX_LEDS)
			{
				value = CHARLIEPLEX_MAX_LEDS - 1;
			}
			charlie->ledArray[value / 8] |= (1 << (value % 8));
		}
		if (charlie->displayMode == 3)
		{
			uint16_t value = outputValue;
			if (value >= CHARLIEPLEX_MAX_LEDS)
			{
				value = CHARLIEPLEX_MAX_LEDS - 1;
			}
			int i;
			for (i = 0; i <= value ; i++)
			{
			charlie->ledArray[i / 8] |= (1 << (i % 8));

			}

		}
		clearUnusedBits();

		}
		for (i = 0; i < CHARLIEPLEX_ARRAY_SIZE; i++)
		{
			charlie->ledArrayCopy[i] = charlie->ledArray[i];
		}
	}


	for (i = 0; i < (charlie->numberOfPins * (charlie->numberOfPins - 1	)) ; i++)
	{
		uint8_t b = charlie->ledArrayCopy[i / 8] & (1 << (i % 8));
		if (b)
		{
			

			charlieplexLookup_t* lookup = (charlieplexLookup_t*)&PinUpdateRegisters[charlie->pinNumbers[1]];
			uint8_t x = lookup->charliePinArray[i];
						uint8_t highPin = (x >> 4) & 0x07;
			uint8_t lowPin = x & 0x07;  // Limited to 8 pins, so only 3 bits needed .  This protects against array overflow if the lookup table is corrupted
			PinHigh(charlie->pinNumbers[highPin]);
			PinLow(charlie->pinNumbers[lowPin]);
			charlie->ledArrayCopy[i / 8] &= ~(1 << (i % 8));
			break; // Only light one LED per update
		}

	}

	

}