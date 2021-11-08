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

#ifndef SERIALWOMBAT_H
#define SERIALWOMBAT_H
#include <stdint.h>
#include <stdbool.h>
#include "pinModes.h"
#include "deviceSpecific.h"
#include "pinRegisters.h"
#include "protocol.h"
#include "queue.h"

extern  uint8_t CurrentPin;

extern pinRegister_t PinUpdateRegisters[NUMBER_OF_TOTAL_PINS];

extern bool RunForeground;

#define RXBUFFER_LENGTH 8
extern uint8_t Rxbuffer[RXBUFFER_LENGTH];

#define TXBUFFER_LENGTH 8
extern uint8_t Txbuffer[TXBUFFER_LENGTH];

#if SIZE_OF_USER_BUFFER > 0
extern uint8_t UserBuffer[SIZE_OF_USER_BUFFER];
#endif

#define CLOCK_STRETCHING_MAX 10
#define DIGITAL_LOW 0
#define DIGITAL_HIGH 1
#define DIGITAL_INPUT 2
uint8_t CurrentPinPort(void);
uint16_t CurrentPinBitmap(void);
bool CurrentPinRead(void);
bool ReadPin(uint8_t pin);
void ConfigurePinAnalog(uint8_t pin, bool makeAnalog);
void CurrentPinAnalog(void);
void CurrentPinNotAnalog(void);
void CurrentPinPullUp(void);
void CurrentPinNoPullUp(void);

void PinInput(uint8_t pin);
void PinOutput(uint8_t pin);
void PinHigh(uint8_t pin);
void PinLow(uint8_t pin);
void SetPin(uint8_t pin, uint8_t pinState); 
void CurrentPinInput(void);
void CurrentPinOutput(void);
void CurrentPinHigh(void);
void CurrentPinLow(void);
void SetCurrentPin(uint8_t pinState);
void CurrentPinPullup(void);
void CurrentPinNoPullup(void);
void PinPullUp(uint8_t pin);
void PinNoPullUp(uint8_t pin);
bool ReadPin(uint8_t pin);
void CurrentPinOpenDrain(void);
void CurrentPinNotOpenDrain(void);

void ProcessRx(void);
void ProcessPins(void);
void reset(void);


typedef enum {

	SW_DATA_SOURCE_PIN_0 = 0,
	SW_DATA_SOURCE_PIN_1 = 1,
	SW_DATA_SOURCE_PIN_2 = 2,
	SW_DATA_SOURCE_PIN_3 = 3,
	SW_DATA_SOURCE_PIN_4 = 4,
	SW_DATA_SOURCE_PIN_5 = 5,
	SW_DATA_SOURCE_PIN_6 = 6,
	SW_DATA_SOURCE_PIN_7 = 7,
	SW_DATA_SOURCE_PIN_8 = 8,
	SW_DATA_SOURCE_PIN_9 = 9,
	SW_DATA_SOURCE_PIN_10 = 10,
	SW_DATA_SOURCE_PIN_11 = 11,
	SW_DATA_SOURCE_PIN_12 = 12,
	SW_DATA_SOURCE_PIN_13 = 13,
	SW_DATA_SOURCE_PIN_14 = 14,
	SW_DATA_SOURCE_PIN_15 = 15,
	SW_DATA_SOURCE_PIN_16 = 16,
	SW_DATA_SOURCE_PIN_17 = 17,
	SW_DATA_SOURCE_PIN_18 = 18,
	SW_DATA_SOURCE_PIN_19 = 19,
//	SW_DATA_SOURCE_PIN_20 = 20,
//	SW_DATA_SOURCE_PIN_21 = 21,
//	SW_DATA_SOURCE_PIN_22 = 22,
//	SW_DATA_SOURCE_PIN_23 = 23,
//	SW_DATA_SOURCE_PIN_24 = 24,
//	SW_DATA_SOURCE_PIN_25 = 25,
//	SW_DATA_SOURCE_PIN_26 = 26,
//	SW_DATA_SOURCE_PIN_27 = 27,
//	SW_DATA_SOURCE_PIN_28 = 28,
//	SW_DATA_SOURCE_PIN_29 = 29,
//	SW_DATA_SOURCE_PIN_30 = 30,
//	SW_DATA_SOURCE_PIN_31 = 31,
//	SW_DATA_SOURCE_PIN_32 = 32,
//	SW_DATA_SOURCE_PIN_33 = 33,
//	SW_DATA_SOURCE_PIN_34 = 34,
//	SW_DATA_SOURCE_PIN_35 = 35,
//	SW_DATA_SOURCE_PIN_36 = 36,
//	SW_DATA_SOURCE_PIN_37 = 37,
//	SW_DATA_SOURCE_PIN_38 = 38,
//	SW_DATA_SOURCE_PIN_39 = 39,
//	SW_DATA_SOURCE_PIN_40 = 40,
//	SW_DATA_SOURCE_PIN_41 = 41,
//	SW_DATA_SOURCE_PIN_42 = 42,
//	SW_DATA_SOURCE_PIN_43 = 43,
//	SW_DATA_SOURCE_PIN_44 = 44,
//	SW_DATA_SOURCE_PIN_45 = 45,
//	SW_DATA_SOURCE_PIN_46 = 46,
//	SW_DATA_SOURCE_PIN_47 = 47,
//	SW_DATA_SOURCE_PIN_48 = 48,
//	SW_DATA_SOURCE_PIN_49 = 49,
//	SW_DATA_SOURCE_PIN_50 = 50,
//	SW_DATA_SOURCE_PIN_51 = 51,
//	SW_DATA_SOURCE_PIN_52 = 52,
//	SW_DATA_SOURCE_PIN_53 = 53,
//	SW_DATA_SOURCE_PIN_54 = 54,
//	SW_DATA_SOURCE_PIN_55 = 55,
//	SW_DATA_SOURCE_PIN_56 = 56,
//	SW_DATA_SOURCE_PIN_57 = 57,
//	SW_DATA_SOURCE_PIN_58 = 58,
//	SW_DATA_SOURCE_PIN_59 = 59,
//	SW_DATA_SOURCE_PIN_60 = 60,
//	SW_DATA_SOURCE_PIN_61 = 61,
//	SW_DATA_SOURCE_PIN_62 = 62,
//	SW_DATA_SOURCE_PIN_63 = 63,
	SW_DATA_SOURCE_INCREMENTING_NUMBER = 65, ///< An number that increments each time it is accessed.
	SW_DATA_SOURCE_1024mvCounts = 66 , ///< The number of ADC counts that result from a 1.024V reading
	SW_DATA_SOURCE_FRAMES_RUN_LSW = 67, ///< The number of frames run since reset, least significant 16 bits
	SW_DATA_SOURCE_FRAMES_RUN_MSW = 68, ///< The number of frames run since reset, most significant 16 bits
	SW_DATA_SOURCE_OVERRUN_FRAMES = 69, ///< The number of frames that ran more than 1mS
	SW_DATA_SOURCE_TEMPERATURE = 70, ///<The internal core temperature expressed in 100ths deg C
	SW_DATA_SOURCE_PACKETS_RECEIVED = 71,  ///<The nubmer of incoming command packets that have been processed since reset (rolls over at 65535)
	SW_DATA_SOURCE_ERRORS = 72,  ///<The number of incoming packets that have caused errors since reset (rolls over at 65535)  
	SW_DATA_SOURCE_FRAMES_DROPPED = 73 , ///<The number of times since reset that a frame ran so far behind that it crossed two subsequent 1ms boundaries, causing a permanent lost frame
	SW_DATA_SOURCE_SYSTEM_UTILIZATION = 74 , ///< A number between 0 and 65535 that scales to the average length of pin processing frames between 0 and 1000mS
}SW_DATA_SOURCE_t;
 

typedef enum {
    SW_ERROR_UNNUMBERED_ERROR = 0,
    SW_ERROR_PINS_MUST_BE_ON_SAME_PORT = 1, ///< Pins must be on the same microcontroller part (e.g. PORTA, PORTB, etc.).  See datasheet of micro for port assignments.
    SW_ERROR_ASCII_NUMBER_TOO_BIG_16 = 2, ///<A number bigger than 65535 was provided to convert to a 16 bit value
            SW_ERROR_UNKNOWN_PIN_MODE = 3, ///< A Pin mode was indicated that is not avaialble on this model or version of Serial Wombat chip
            SW_ERROR_RESET_STRING_INCORRECT = 4, ///<A Packet starting with 'R' was received but didn't have the correct following bytes to cause a reset
            SW_ERROR_INVALID_COMMAND = 5, ///< The first byte of a received packet does not correspond with a command supported by this model of Serial Wombat chip
            SW_ERROR_INSUFFICIENT_SPACE = 6,  ///< There was not sufficient space in the queue or user area to complete the command.
            SW_ERROR_WUB_COUNT_GT_4 = 7, ///< A count greater than 4 was provided as a number of bytes to write to count user buffer
            SW_ERROR_WUB_INVALID_ADDRESS = 8, ///<An attempt to write to a user buffer address outside the user buffer was attempted.
            SW_ERROR_WUB_CONTINUE_OUTOFBOUNDS = 9, ///<  A call to Write User Buffer Continue would have written out of bounds.
            SW_ERROR_RF_ODD_ADDRESS = 10, ///< Addresses Read From Flash must be even.
            SW_ERROR_FLASH_WRITE_INVALID_ADDRESS = 11, ///<An attempt to write or erase flash was made to a protected or non-existant area
	    SW_ERROR_INVALID_PIN_COMMAND = 12, ///< The pin command 0xC1, 0xC2, etc is not suported by this pin mode (May vary by model)
            SW_ERROR_PIN_CONFIG_WRONG_ORDER = 13, ///<The called pin command 0xC1, 0xC2 was called before other required prior commands (e.g. 0xC0)
            SW_ERROR_WS2812_INDEX_GT_LEDS = 14, ///<The command references an index that is greater or equal to the number of leds
            SW_ERROR_PIN_NOT_CAPABLE = 15, ///<The commanded pin does not have the hardware support to perform the commanded pin mode
	    SW_ERROR_HW_RESOURCE_IN_USE = 16, ///<The requested hardware or software resource in use has already been exclusively claimed by another pin
            SW_ERROR_INVALID_PARAMETER_3 = 17, ///<The pin configuration parameter in Byte 3 was invalid
            SW_ERROR_INVALID_PARAMETER_4 = 18, ///<The pin configuration parameter in Byte 4 was invalid
            SW_ERROR_INVALID_PARAMETER_5 = 19, ///<The pin configuration parameter in Byte 5 was invalid
            SW_ERROR_INVALID_PARAMETER_6 = 20, ///<The pin configuration parameter in Byte 6 was invalid
            SW_ERROR_INVALID_PARAMETER_7 = 21, ///<The pin configuration parameter in Byte 7 was invalid
            SW_ERROR_PIN_NUMBER_TOO_HIGH = 22, ///<The pin number indicated was greater than the greatest avaialable pin
            SW_ERROR_PIN_IS_COMM_INTERFACE =23, ///<The pin number indicated is currently being used for Serial Wombat protocol communicaitons
}SW_ERROR_t;

void error (SW_ERROR_t errorCode);

extern uint32_t FramesRun;

#endif

