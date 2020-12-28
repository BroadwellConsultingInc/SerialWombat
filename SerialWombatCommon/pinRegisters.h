#ifndef PIN_TYPES_H
#define PIN_TYPES_H

#include <stdint.h>

#ifdef _PIC14EX 
#define BYTES_PER_PIN_REGISTER 20
#else
#define BYTES_PER_PIN_REGISTER 40
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
	struct pulse_output_n
	{
		uint8_t bytes[27];
		uint8_t lastDMA;
		uint16_t highRemaining;
		uint16_t lowRemaining;
		uint16_t highReload;
		uint16_t lowReload;
		uint16_t buffer;
		uint16_t mode;
	} pulse_output;
#endif
} pinRegister_t;

extern pinRegister_t PinUpdateRegisters[NUMBER_OF_TOTAL_PINS];

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
