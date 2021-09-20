#ifndef PIN_DIGITAL_HW_SPECIFIC_H
#define PIN_DIGITAL_HW_SPECIFIC_H
#include <stdint.h>
#define SIZE_OF_DMA_ARRAY 128
extern uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t OutputArrayB[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayB[SIZE_OF_DMA_ARRAY];

#define DIGITAL_LOW 0
#define DIGITAL_HIGH 1
#define DIGITAL_INPUT 2
void PinInput(uint8_t pin);
void PinOutput(uint8_t pin);
void PinHigh(uint8_t pin);
void PinLow(uint8_t pin);
void SetPin(uint8_t pin, uint8_t pinState); 

extern const uint16_t pinBitmap[];
extern const uint8_t pinPort[];

void orCount(uint16_t* buffer, uint16_t bitmap, uint16_t count);
void andCount(uint16_t* buffer, uint16_t bitmap, uint16_t count);
void updatePulseOutput(uint8_t pin);
uint8_t  PulseInGetOldestDMABit(uint8_t pin);
bool  PulseInGetOldestDMASample(uint8_t pin, uint16_t* value);

#endif
