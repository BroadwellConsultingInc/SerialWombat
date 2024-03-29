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
void uint16ToAsciiHex4(uint16_t val, uint8_t* buffer);



#endif
