/*
Copyright 2020-2025 Broadwell Consulting Inc.

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
	INPUT_FILTER_MODE_NONE = 0,  ///< No input filtering
	INPUT_FILTER_MODE_FIRST_ORDER = 1,  ///< First order IIR filtering
	INPUT_FILTER_MODE_AVERAGE = 2, ///< Average a specified number of samples
}INPUT_FILTER_MODE_t;

typedef enum
{
	INPUT_TRANSFORM_MODE_NONE = 0, ///< No input transform
	INPUT_TRANSFORM_MODE_SCALE_RANGE = 1, ///< Scale input to 0-65535
	INPUT_TRANSFORM_MODE_LINEAR_MXB = 2, ///< Transform input with mx + b
	//#ifdef INPUTPROCESSINTEGRATORPRESENT
	INPUT_TRANSFORM_MODE_INTEGRATOR = 3, ///< Integrate input based on range multipliers
	//#endif
}INPUT_TRANSFORM_MODE_t;

typedef struct inputProcess_n
{

	struct {
		uint16_t filteredValue; ///< First order filtered value
		uint16_t filterconstant; ///< First order constant, numerator over 65536, higher = more filtering
	}firstOrder;
	struct {
		uint32_t sum;  ///< sum of points to average
		uint16_t samplesToAverage; ///< Number of samples to average
		uint16_t samplesAddedToSum; ///< number of samples so far
		uint16_t average; ///< Last completed average value
	}average;
	union{
		int16_t transform_i16[9];
		uint16_t transform_u16[9];    
		uint8_t transform_bytes[18];
		struct{
			int32_t m;  ///< m value, in 256ths 
			int32_t b;  ///<  b value in 1's
		}mxb;
		//#ifdef INPUTPROCESSINTEGRATORPRESENT
		struct {
			uint16_t maxInc; ///<  Max increment amount
			uint16_t midInc; ///<  Mid increment amount
			uint16_t negMaxIndex; ///<  value at/below max decrement
			uint16_t negMidIndex; ///<  value for mid decrement
			uint16_t negDeadZone; ///<  value where no decrement / increment
			uint16_t posMaxIndex; ///<  value at above max decrement
			uint16_t posMidIndex; ///<  value for mid increment
			uint16_t posDeadZone; ///<  value where no increment/decrement
			uint16_t currentValue; ///<  Current integrated value
			uint8_t updateFrequencyMask; ///<  Update rate - ms * 2 ^ value
		}integrator;
		//#endif
		struct{
			uint16_t low;  ///<  Range scale low
			uint16_t high;  ///<  Range scale high
		}scaleRange;
	};
	uint16_t lastInput;  ///< Last non-excluded value, used if current value is excluded
	//#ifdef INPUTPROCESSEXCLUDEPRESENT
	uint16_t excludeBelow; ///< exclude values below this threshold and substitue lastInput
	uint16_t excludeAbove; ///< exclude values above this threshold and substitue lastInput
	//#endif
	uint16_t min;  ///< Minimum observed final value
	uint16_t max; ///< Maximum observed final value
	//#ifdef INPUTPROCESSQUEUEPRESENT
	uint16_t queue; ///< Index of Queue to store final values in
	//#endif
	uint8_t filterMode; ///< Enumerated filter type
	uint8_t transformMode; ///< Enumerated transform type
	uint8_t invert:1; ///< Invert input 
	uint8_t active:1; ///< Input processing is active
	uint8_t initialized:1; ///< Input processing has been initialized
	//#ifdef INPUTPROCESSQUEUEPRESENT
	uint8_t queueHighByte:1; ///< Whether to queue the high byte of input
	uint8_t queueLowByte:1; ///< Whether to queue the low byte of input
	uint8_t queueFrequency:4; ///< how often to queue input (1ms * 2^value)
	//#endif
}inputProcess_t;

void inputProcessInit(inputProcess_t* inputProcess);
uint16_t inputProcessProcess(inputProcess_t* inputProcess, uint16_t inputValue);
void inputProcessCommProcess(inputProcess_t* inputProcess);
#endif
