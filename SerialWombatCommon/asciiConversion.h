#ifndef ASCII_CONVERSION_H
#define ASCII_CONVERSION_H
#include <stdint.h>
uint8_t ascii_to_val(uint8_t a);
void uint16ToAscii5(uint16_t val, uint8_t* buffer);
void uint16ToAscii5NoHWMath(uint16_t val, uint8_t* buffer);
void uint16ToAscii5NoHWMathTx(uint16_t val, uint8_t index);
void uint16ToAscii5NoHWMathNoIndex(void);
extern uint16_t asciiVal;
extern uint8_t asciiChar[5];



#endif
