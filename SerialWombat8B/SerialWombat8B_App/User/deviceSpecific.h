/*
Copyright 2021-2023 Broadwell Consulting Inc.

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

#ifndef DEVICE_SPECIFIC_H
#define DEVICE_SPECIFIC_H

#include "swFeatureEnable.h"

#define NUMBER_OF_PHYSICAL_PINS 8
#define NUMBER_OF_VIRTUAL_PINS 0
#define NUMBER_OF_TOTAL_PINS (NUMBER_OF_PHYSICAL_PINS + NUMBER_OF_VIRTUAL_PINS)

#define DMA_FREQUENCY 57600
#define ADC_MAX_COUNTS 0xFFC0

#define SIZE_OF_USER_BUFFER 128


#include "pinDigitalHwSpecific.h"
#define ADC1Semaphore  RESOURCE_AVAILABLE


#endif
