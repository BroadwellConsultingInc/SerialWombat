/*
Copyright 2020, 2021 Broadwell Consulting Inc.

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

/* Serial Wombat is a trademark of Broadwell Consulting Inc. registered
 * in the United States. */


#ifndef PIN_TYPES_H
#define PIN_TYPES_H

#include <stdint.h>

#ifdef _PIC14EX 
#define BYTES_PER_PIN_REGISTER 20
#else
#define BYTES_PER_PIN_REGISTER 96
#define BYTES_AVAILABLE_INPUT_DMA (BYTES_PER_PIN_REGISTER - 5)
#endif

typedef union _pin_register_t{ 
	uint8_t bytes[BYTES_PER_PIN_REGISTER];
	uint16_t uwords[BYTES_PER_PIN_REGISTER/2];

	/// \brief A generic descriptor, typically used to access the buffer and mode variables
	///
	struct generic_n {
		uint16_t pinUwords[(BYTES_PER_PIN_REGISTER / 2) - 2];
		/// \brief  A 16 bit 'public' variable which is in the same location for every pin.
		/// 
		/// One pin mode can read or modify another pin's public data.  
		uint16_t buffer;

		/// \brief The mode of the current pin.
		///
		uint8_t mode;     // Do not move
	} generic;
#ifndef _PIC14EX
	
    
    struct pulse_input_n
    {
        uint8_t bytes[BYTES_AVAILABLE_INPUT_DMA];
        uint8_t lastDMA;
        uint16_t buffer;
		uint16_t mode;
    }pulse_input;
    
#endif
} pinRegister_t;


/// \brief Awesome way to check structure sizes at build time.
///
/// See https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))


extern pinRegister_t PinUpdateRegisters[NUMBER_OF_TOTAL_PINS];

extern uint16_t virtualPinHardwareSim[NUMBER_OF_VIRTUAL_PINS];

#define setVirtualPinHardware(_pin, _value) { if (_pin >= FIRST_VIRTUAL_PIN && _pin < (FIRST_VIRTUAL_PIN + NUMBER_OF_VIRTUAL_PINS){virutalPinHardwareSim[_pin - FIRST_VIRTUAL_PIN] = _value;}}

#ifdef _PIC14EX 
#define USE_BUFFERED_PIN_REGISTER
#endif

#ifdef USE_BUFFERED_PIN_REGISTER
extern  pinRegister_t pinRegisterBuffer;
void CopyFromArrayToPinBuffer(void);
void CopyFromPinBufferToArray(void);
#define CurrentPinRegister (&pinRegisterBuffer)
void CopyFromArrayToPinBuffer();
void CopyFromPinBufferToArray();
#else
    extern pinRegister_t* CurrentPinRegister;
#endif


void SetBuffer(uint8_t pin, uint16_t value);
uint16_t GetBuffer(uint8_t pin);
void SetMode(uint8_t pin, uint8_t mode);
uint8_t GetMode(uint8_t pin);
#endif
