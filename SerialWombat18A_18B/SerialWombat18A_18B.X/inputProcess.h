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
 
 Serial Wombat is a trademark of Broadwell Consulting Inc.
*/

#ifndef _INPUT_PROCESS_
#define _INPUT_PROCESS_

#include <stdint.h>
#include "serialWombat.h"

typedef enum
{
    INPUT_FILTER_MODE_NONE = 0,
    INPUT_FILTER_MODE_AVERAGE = 1,
    INPUT_FILTER_MODE_FIRST_ORDER = 2,         
}INPUT_FILTER_MODE_t;

typedef enum
{
    INPUT_TRANSFORM_MODE_NONE = 0,
            INPUT_TRANSFORM_MODE_SCALE_RANGE = 1,
            INPUT_TRANSFORM_MODE_MXB = 2,
}INPUT_TRANSFORM_MODE_t;

typedef struct inputProcess_n
{
	
		struct {
			uint16_t filteredValue;
			uint16_t filterconstant;
		}firstOrder;
		struct {
			uint32_t sum;
			uint16_t samplesToAverage;
			uint16_t samplesAddedToSum;
            uint16_t average;
		}average;
		union{
		int16_t transform_i16[6];
		uint16_t transform_u16[6];    
		uint8_t transform_bytes[12];
		struct{
			int32_t m;
			int32_t b;
		}mxb;
        struct{
            uint16_t low;
            uint16_t high;
        }scaleRange;
	};
	uint16_t lastInput;
	uint16_t excludeBelow;
	uint16_t excludeAbove;
    uint16_t min;
    uint16_t max;
    uint16_t queue;
	uint8_t filterMode;
    uint8_t transformMode;
	uint8_t invert:1;
	uint8_t active:1;
	uint8_t initialized:1;
    uint8_t queueHighByte:1;
    uint8_t queueLowByte:1;
    uint8_t queueFrequency:4;
}inputProcess_t;

void inputProcessInit(inputProcess_t* inputProcess);
uint16_t inputProcessProcess(inputProcess_t* inputProcess, uint16_t inputValue);
void inputProcessCommProcess(inputProcess_t* inputProcess);
#endif
