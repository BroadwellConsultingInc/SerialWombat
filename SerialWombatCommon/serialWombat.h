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

#endif

