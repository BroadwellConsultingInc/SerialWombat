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

#ifndef _OUTPUT_SCALE_
#define _OUTPUT_SCALE_

#include <stdint.h>
#include "serialWombat.h"

typedef enum 
{
    OUTPUT_TRANSFORM_MODE_NONE,
    OUTPUT_TRANSFORM_MODE_LINEAR,
    OUTPUT_TRANSFORM_MODE_2D_LOOKUP,
    OUTPUT_TRANSFORM_MODE_PID_CONTROL,
    OUTPUT_TRANSFORM_MODE_HYSTERESIS,
}OUTPUT_TRANSFORM_MODE_t;

typedef enum
{
    OUTPUT_FILTER_MODE_NONE = 0,
    OUTPUT_FILTER_MODE_CHANGE_LIMIT = 1,
    OUTPUT_FILTER_MODE_FIRST_ORDER = 2,         
}OUTPUT_FILTER_MODE_t;

typedef struct outputScale_n
{
    union{
        int16_t transform_i16[7];
    uint16_t transform_u16[7];    
    uint8_t transform_bytes[14];
	struct{
		uint16_t highLimit;
		uint16_t lowLimit;
		uint16_t outputHigh;
		uint16_t outputLow;
        uint16_t lastValue;
	}hystersis;
	struct{
		int32_t integrator;
		uint16_t lastProcessVariable;
		uint16_t kp;
		uint16_t ki;
		uint16_t kd;
	}pid;
    };
    uint16_t inputMin;
    uint16_t inputMax;
    uint16_t outputMin;
    uint16_t outputMax;
    uint16_t filterConstant;
    uint16_t currentOutput;
    uint16_t commTimeout;
    uint16_t commTimeoutCounter;
    uint16_t commTimeoutValue;
    uint16_t targetValue;
        uint16_t lastValue;
    uint8_t filterMode;
    uint8_t  transformMode;
    uint8_t sourcePin;
    uint8_t invert:1;
    uint8_t active:1;
    uint8_t sampleRate:4;
    
}outputScale_t;


void outputScaleInit(outputScale_t* outputScale);

void outputScaleResetTimeout(outputScale_t* outputScale);

uint16_t outputScaleProcess(outputScale_t* outputScale);
uint16_t outputScaleCommProcess(outputScale_t* outputScale);


#endif
