/*
Copyright 2022-2025 Broadwell Consulting Inc.

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
#include <stdbool.h>


typedef enum {
    STATE_WAITING_FOR_PULSE,
            STATE_PULSING_ACTIVE,
            STATE_PULSING_INACTIVE,
}PULSE_ON_CHANGE_STATE_t;

typedef enum 
{
    PULSE_ON_CHANGE = 0,
    PULSE_ON_INCREASE = 1,
    PULSE_ON_DECREASE = 2,
    PULSE_EQUAL_VALUE = 3,
    PULSE_BELOW_VALUE = 4,
    PULSE_ABOVE_VALUE = 5,
    PULSE_NOT_EQUAL_VALUE = 6,
    PULSE_EQUAL_PIN = 7,
    PULSE_ABOVE_PIN = 8,
    PULSE_BELOW_PIN = 9,
    PULSE_NOT_EQUAL_PIN = 10,
    PULSE_CROSS_VALUE = 11,
    PULSE_CROSS_VALUE_ASCENDING = 12,
    PULSE_CROSS_VALUE_DESCENDING = 13,
    PULSE_WITHIN_RANGE = 14,
    PULSE_OUTSIDE_RANGE = 15,
            
    PULSE_NUM_MODES 
}PULSE_ON_CHANGE_MODE_t;

#define NUM_CHANGE_REC 8
typedef struct changeRec_n{
	uint16_t value0;
	uint16_t value1;
	uint8_t pin;
	uint8_t mode;
}changeReq_t;

typedef struct pulseOnChange_n{
    pulse_output_t pulseOutput;
	changeReq_t entry[NUM_CHANGE_REC];
	uint16_t pwmPeriod;
	uint16_t pwmDutyCycle;
	uint16_t durationOn;
	uint16_t durationOff;
	uint16_t counter;
    uint8_t state;
	uint8_t activeMode;
	uint8_t inactiveMode;
	uint8_t orNotAnd:1;
   
}pulseOnChange_t;


pulseOnChange_t* debugPulseOnChange;

//TODO Update documentation
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



void initPulseOnChange (void)
{
    BUILD_BUG_ON( sizeof(pulseOnChange_t) >  BYTES_PER_PIN_REGISTER );
	debugPulseOnChange = (pulseOnChange_t*) CurrentPinRegister;
	pulseOnChange_t* pulseOnChange = (pulseOnChange_t*) CurrentPinRegister;
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PULSE_ON_CHANGE)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				uint8_t i;
				for (i = 0; i < NUM_CHANGE_REC; ++i)
				{
					pulseOnChange->entry[i].pin = 0xFF;
				}

				pulseOnChange->activeMode = Rxbuffer[3];
				pulseOnChange->inactiveMode = Rxbuffer[4];
				pulseOnChange->orNotAnd = Rxbuffer[5];
				pulseOnChange->durationOn = 0;
				pulseOnChange->durationOff = 0;
				pulseOnChange->pwmPeriod = 0;
				pulseOnChange->pwmDutyCycle = 0x8000;
				pulseOnChange->counter = 0;
                pulseOnChange->state =  STATE_WAITING_FOR_PULSE;
                CurrentPinRegister->generic.mode = PIN_MODE_PULSE_ON_CHANGE;
                timingResourceRelease(TIMING_RESOURCE_ALL);

			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{
				pulseOnChange->durationOn = RXBUFFER16(3);
				pulseOnChange->durationOff = RXBUFFER16(5);
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
				pulseOnChange->pwmPeriod = RXBUFFER16(3);
				pulseOnChange->pwmDutyCycle = RXBUFFER16(5);
                
                if (pulseOnChange->pwmPeriod > 0)
                {
                    InitializePinLow(CurrentPin);
                    pulseOnChange->pulseOutput.resource = timingResourcePWMClaim(TIMING_RESOURCE_ANY,pulseOnChange->pwmPeriod);
                    timingResourcePWM(&pulseOnChange->pulseOutput, pulseOnChange->pwmPeriod, 0);
                }
                else
                {
                        timingResourceRelease(TIMING_RESOURCE_ANY);
                }
			}
			break;
		case CONFIGURE_CHANNEL_MODE_3:
			{
				if (Rxbuffer[3] >= NUM_CHANGE_REC)
				{
					error(SW_ERROR_PULSE_ON_CHANGE_ENTRY_OUT_OF_RANGE);
					return;

				}
				pulseOnChange->entry[Rxbuffer[3]].value0 = RXBUFFER16(4);
				pulseOnChange->entry[Rxbuffer[3]].value1 = RXBUFFER16(6);

			}
			break;
		case CONFIGURE_CHANNEL_MODE_4:
			{
				if (Rxbuffer[3] >= NUM_CHANGE_REC)
				{
					error(SW_ERROR_PULSE_ON_CHANGE_ENTRY_OUT_OF_RANGE);
					return;

				}
				if (Rxbuffer[4] >= PULSE_NUM_MODES)
				{
					error (SW_ERROR_PULSE_ON_CHANGE_UNKNOWN_MODE);
					return;
				}
				pulseOnChange->entry[Rxbuffer[3]].pin = Rxbuffer[5];
				pulseOnChange->entry[Rxbuffer[3]].mode = Rxbuffer[4];
				switch (pulseOnChange->entry[Rxbuffer[3]].mode)
				{
					case PULSE_ON_CHANGE:
					case PULSE_ON_INCREASE:
					case PULSE_ON_DECREASE:
                            case PULSE_CROSS_VALUE:
    case PULSE_CROSS_VALUE_ASCENDING:
         case   PULSE_CROSS_VALUE_DESCENDING:
						{

							pulseOnChange->entry[Rxbuffer[3]].value1 = GetBuffer(pulseOnChange->entry[Rxbuffer[3]].pin);

						}
						break;
					case PULSE_EQUAL_VALUE:
					case PULSE_BELOW_VALUE:
					case PULSE_ABOVE_VALUE:
					case PULSE_NOT_EQUAL_VALUE:
					case PULSE_EQUAL_PIN:
					case PULSE_ABOVE_PIN:
					case PULSE_BELOW_PIN:
					case PULSE_NOT_EQUAL_PIN:
                    case     PULSE_WITHIN_RANGE:
            case PULSE_OUTSIDE_RANGE:
					default:
						{

						}
						break;
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

static bool activeCondition(pulseOnChange_t* pulseOnChange)
{
bool oneTrue = false;
	bool allTrue = true;

	uint8_t i;
	for (i = 0; i < NUM_CHANGE_REC; ++i)
	{

		changeReq_t* e = &pulseOnChange->entry[i];

		if (e->pin == 255)
		{
			continue;
		}
		uint16_t value = GetBuffer(e->pin);

		switch (e->mode)
		{
			case PULSE_ON_CHANGE:
			{
				if (value != e->value1)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}
				e->value1 = value;

			}
			break;

			case PULSE_ON_INCREASE:
				{
				if (value > e->value1)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}
				e->value1 = value;


				}
				break;

			case PULSE_ON_DECREASE:
				{
				if (value < e->value1)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}
				e->value1 = value;

				}
				break;

			case PULSE_EQUAL_VALUE:
				{
				if (value == e->value0)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}

				}
				break;

			case PULSE_BELOW_VALUE:
				{
				if (value < e->value0)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}

				}
				break;

			case PULSE_ABOVE_VALUE:
				{
				if (value > e->value0)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}

				}
				break;

			case PULSE_NOT_EQUAL_VALUE:
				{
				if (value != e->value0)
				{
					oneTrue = true; 	
				}	
				else
				{
					allTrue = false;
				}

				}
				break;

			case PULSE_EQUAL_PIN:
				{
                    uint16_t x = GetBuffer(e->value0);
                    if (value == x)
                    {
                        oneTrue = true;
                    }
                    else
                    {
                        allTrue = false;
                    }
				}
				break;

			case PULSE_ABOVE_PIN:
				{
 uint16_t x = GetBuffer(e->value0);
                    if (value > x)
                    {
                        oneTrue = true;
                    }
                    else
                    {
                        allTrue = false;
                    }
				}
				break;

			case PULSE_BELOW_PIN:
				{
 uint16_t x = GetBuffer(e->value0);
                    if (value < x)
                    {
                        oneTrue = true;
                    }
                    else
                    {
                        allTrue = false;
                    }
				}
				break;

			case PULSE_NOT_EQUAL_PIN:
				{
 uint16_t x = GetBuffer(e->value0);
                    if (value != x)
                    {
                        oneTrue = true;
                    }
                    else
                    {
                        allTrue = false;
                    }
				}
				break;

		}

	}
        if ((pulseOnChange->orNotAnd && oneTrue) || (!pulseOnChange->orNotAnd && allTrue))
    {
            return(true);
        }
    return(false);
}

void updatePulseOnChange()
{
	debugPulseOnChange = (pulseOnChange_t*) CurrentPinRegister;
	pulseOnChange_t* pulseOnChange = (pulseOnChange_t*) CurrentPinRegister;

    
    switch (pulseOnChange->state)
    {
        case STATE_WAITING_FOR_PULSE:
        {
          if (activeCondition(pulseOnChange))
          {
                       pulseOnChange->counter = pulseOnChange->durationOn;
                pulseOnChange->state = STATE_PULSING_ACTIVE;
                if (pulseOnChange->pwmPeriod > 0)
                {
                    timingResourcePWM(&pulseOnChange->pulseOutput, pulseOnChange->pwmPeriod, pulseOnChange->pwmDutyCycle);
                }
                else
                {
                SetCurrentPin(pulseOnChange->activeMode);
                }
          }
          else
          {
              if (pulseOnChange->pwmPeriod > 0)
                {
                    timingResourcePWM(&pulseOnChange->pulseOutput, pulseOnChange->pwmPeriod, 0);
                }
                else
                {
              SetCurrentPin(pulseOnChange->inactiveMode);
                }
          }
        }
        break;
        case   STATE_PULSING_ACTIVE:
        {
            if (pulseOnChange->counter  && pulseOnChange->counter != 0xFFFF)
            {
                -- pulseOnChange->counter;
            }
            else
            {
                
                if (pulseOnChange->durationOff >0)
                {
                pulseOnChange->counter = pulseOnChange->durationOff;
                
                pulseOnChange->state = STATE_PULSING_INACTIVE;
                }
                else
                {
                    pulseOnChange->state = STATE_WAITING_FOR_PULSE;
                }
            }
           // return; // TODO future improvement: work on constant on
        }
        break;
        case    STATE_PULSING_INACTIVE:
        {
            if (pulseOnChange->counter)
            {
                -- pulseOnChange->counter;
            }
            else
            {
                
                pulseOnChange->counter = pulseOnChange->durationOn;
                pulseOnChange->state = STATE_WAITING_FOR_PULSE;
                return;
            }
                  if (pulseOnChange->pwmPeriod > 0)
                {
                    timingResourcePWM(&pulseOnChange->pulseOutput, pulseOnChange->pwmPeriod, 0);
                }
                else
                {
                SetCurrentPin(pulseOnChange->inactiveMode);
                }
            
           // return; // TODO future improvement: work on constant on
            
        }
        break;
    }
       if (pulseOnChange->pwmPeriod > 0)
       {
	
            timingResourceService(&pulseOnChange->pulseOutput);
       }
    
   


}




