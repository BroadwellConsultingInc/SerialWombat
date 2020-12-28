#ifndef PIN_DIGITAL_HW_SPECIFIC_H
#define PIN_DIGITAL_HW_SPECIFIC_H
#include <stdint.h>


extern uint8_t CurrentPinMask;
extern uint8_t CurrentPinMaskInverted;
extern   uint8_t const PinMaskArray[4];
extern uint8_t const PinToPort[4];

void SetLowMaskCurrentPin (void);

#endif