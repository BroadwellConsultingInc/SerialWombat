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
    OUTPUT_TRANSFORM_MODE_PID_CONTROL_LOOKUP,
    OUTPUT_TRANSFORM_MODE_HYSTERESIS,
}OUTPUT_TRANSFORM_MODE_t;

typedef enum
{
    OUTPUT_FILTER_MODE_NONE,
    OUTPUT_FILTER_MODE_RATE,
    OUTPUT_FILTER_MODE_FIRST_ORDER,         
}OUTPUT_FILTER_MODE_t;

typedef struct outputScale_n
{
    union{
    uint8_t transformParams[12];
    };
    uint16_t inputMin;
    uint16_t inputMax;
    uint16_t outputMin;
    uint16_t outputMax;
    uint16_t maximumChangeRate;
    uint16_t currentOutput;
    uint8_t filterMode;
    uint8_t  transformMode;
    uint8_t sourcePin;
    uint8_t invert:1;
    
}outputScale_t;


void outputScaleInit(outputScale_t* outputScale)
{
    outputScale->sourcePin = CurrentPin;
    outputScale->inputMin = 0;
    outputScale->inputMax = 65535;
    outputScale->outputMin = 0;
    outputScale->outputMax = 65535;
    outputScale->maximumChangeRate = 0;
    outputScale->transformMode = OUTPUT_TRANSFORM_MODE_NONE;
    outputScale->filterMode = OUTPUT_FILTER_MODE_NONE;
    outputScale->invert = 0;
}


uint16_t outputScaleProcess(outputScale_t* outputScale)
{
    uint32_t outputValue = GetBuffer(outputScale->sourcePin);
    
    
    // Scale the input.  This allows a sub-range of the input to drive the 
    // output a full 0 to 65535
    if (outputScale->inputMin != 0 || outputScale->inputMax != 65535)
    {
        if (outputValue <= outputScale->inputMin)
        {
            outputValue = 0;
        }
        else if (outputValue >= outputScale->inputMax)
        {
            outputValue = 65535;
        }
        else
        {
            outputValue -= outputScale->inputMin;
            outputValue <<= 16;
            outputValue /= outputScale->inputMax - outputScale->inputMin;
            if (outputValue > 65535)
            {
                outputValue = 65535;
            }
        }
    }
    
    if (outputScale->invert)
    {
        outputValue = 65535 - outputValue;
    }
    
    switch (outputScale->transformMode)
    {
        
        default:
        case OUTPUT_TRANSFORM_MODE_NONE:
        {
            
        }
        break;
        
    }
    
     switch (outputScale->filterMode)
    {
        default:
        case OUTPUT_FILTER_MODE_NONE:
        {
            
        }
        break;
    }
     
    
    if (outputScale->outputMin != 0 || outputScale->outputMax != 65535)
    {

        outputValue *= (outputScale->outputMax - outputScale->outputMin);
        outputValue += outputScale->outputMin;
    }
    
   
    
    return(GetBuffer(outputScale->sourcePin));
}


#endif