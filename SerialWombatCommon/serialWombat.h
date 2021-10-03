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

#define RXBUFFER_LENGTH 8
extern uint8_t Rxbuffer[RXBUFFER_LENGTH];

#define TXBUFFER_LENGTH 8
extern uint8_t Txbuffer[TXBUFFER_LENGTH];

#if SIZE_OF_USER_BUFFER > 0
extern uint8_t user_buffer[SIZE_OF_USER_BUFFER];
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
    SW_ERROR_UNNUMBERED_ERROR = 0,
    SW_ERROR_PINS_MUST_BE_ON_SAME_PORT = 1, ///< Pins must be on the same microcontroller part (e.g. PORTA, PORTB, etc.).  See datasheet of micro for port assignments.
    SW_ERROR_ASCII_NUMBER_TOO_BIG_16 = 2, ///<A number bigger than 65535 was provided to convert to a 16 bit value
            SW_ERROR_UNKNOWN_PIN_MODE = 3, ///< A Pin mode was indicated that is not avaialble on this model of Serial Wombat chip
            SW_ERROR_RESET_STRING_INCORRECT = 4, ///<A Packet starting with 'R' was received but didn't have the correct following bytes to cause a reset
            SW_ERROR_INVALID_COMMAND = 5, ///< The first byte of a received packet does not correspond with a command supported by this model of Serial Wombat chip
            SW_ERROR_INSUFFICIENT_SPACE = 6,  ///< There was not sufficient space in the queue or user area to complete the command.
            SW_ERROR_WUB_COUNT_GT_4 = 7, ///< A count greater than 4 was provided as a number of bytes to write to count user buffer
            SW_ERROR_WUB_INVALID_ADDRESS = 8, ///<An attempt to write to a user buffer address outside the user buffer was attempted.
            SW_ERROR_WUB_CONTINUE_OUTOFBOUNDS = 9, ///<  A call to Write User Buffer Continue would have written out of bounds.
            SW_ERROR_RF_ODD_ADDRESS = 10, ///< Addresses Read From Flash must be even.
            SW_ERROR_FLASH_WRITE_INVALID_ADDRESS = 11, ///<An attempt to write or erase flash was made to a protected or non-existant area
	    SW_ERROR_INVALID_PIN_COMMAND = 12, ///< The pin command 0xC1, 0xC2, etc is not suported by this pin mode (May vary by model)
            
            
            
}SW_ERROR_t;

void error (SW_ERROR_t errorCode);
#endif

