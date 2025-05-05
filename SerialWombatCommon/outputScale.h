/*
Copyright 2021-2025 Broadwell Consulting Inc.

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
	OUTPUT_TRANSFORM_MODE_NONE = 0,  ///< Public Data Input is passed as is
	OUTPUT_TRANSFORM_MODE_LINEAR = 1, ///< Public Data Input has an mX + b transform applied
	// undefined = 2,
	OUTPUT_TRANSFORM_MODE_PID_CONTROL = 3, ///< Public Data Input is feedback into a PID Algorithm with an assigned target.
	OUTPUT_TRANSFORM_MODE_HYSTERESIS = 4, ///< Public Data Input is feedback into a Hysteresis Algorithm with assigned low and high limits
	OUTPUT_TRANSFORM_MODE_RAMP = 5,  ///< Public Data is input is feedback into a two speed chasing algorithm
}OUTPUT_TRANSFORM_MODE_t;

typedef enum
{
	OUTPUT_FILTER_MODE_NONE = 0,  ///< output goes to pin mode driver unchanged
	OUTPUT_FILTER_MODE_CHANGE_LIMIT = 1, ///< output change is limited to a specified amount per time period
	OUTPUT_FILTER_MODE_FIRST_ORDER = 2,   ///< output is 1st order filtered based on a commanded time period and filter constant 
}OUTPUT_FILTER_MODE_t;


typedef enum
{
	OUTPUT_SCALE_2POINT = 0,  ///< output is scaled based min and max numbers
	OUTPUT_SCALE_XY_LINEAR_INTERPOLATION = 1, ///< output is scaled based on a 2d linear interpolation based on a table stored in user RAM
}OUTPUT_SCALE_MODE_t;

typedef enum
{
    OUTPUT_SCALE_RAMP_MODE_BOTH = 0,
    OUTPUT_SCALE_RAMP_MODE_INCREMENT = 1,
    OUTPUT_SCALE_RAMP_MODE_DECREMENT = 2,
}OUTPUT_SCALE_RAMP_MODE_t;

typedef struct outputScale_n
{
	union{
		int16_t transform_i16[9];  ///< Transform Data in int16's
		uint16_t transform_u16[9];      ///< Transform Data in uint16's
		uint8_t transform_bytes[18];  ///<Transform data in bytes
		//#ifdef OS_HYSTERESIS_PRESENT
		struct{
			uint16_t highLimit;  ///< Hysteresis High Limit
			uint16_t lowLimit;  ///< Hysteresis low Limit
			uint16_t outputHigh; ///<  Value to Output when Hystereis is High 
			uint16_t outputLow; ///< Value to Output when Hystereis is low;
			uint16_t lastValue;
		}hystersis;
		//#endif

		//#ifdef OS_PID_PRESENT
		struct{
			int32_t integrator;
			int32_t lastError;
			uint16_t kp;
			uint16_t ki;
			uint16_t kd;
			uint8_t add32768:1;   ///< Used to add an offset to output for center zero outputs like H Bridge
		}pid;
		//#endif

		//#ifdef OS_RAMP_PRESENT	
		struct{
			int16_t increment;  ///< Amount to change output if input is more than slowIncrementDifference away from target
			uint16_t lastRampOutput; ///< Last Ramp output
			int16_t slowIncrement; ///< Amount to change output if input is less than slowIncrementDifference away from target
			uint16_t slowIncrementDifference; ///< Difference between input and target to switch from increment to slowIncrement
			uint8_t rampMode;
		}ramp;
		//#endif
	};
	uint16_t inputMin;  ///< Input Scaling Min.  Values below this scale to 0
	uint16_t inputMax;  ///< Input Scaling Max.  Values above this scale to 65535.  Values between are interpolated to 0-65535
	union{
		uint16_t outputMin;   ///< Output minimum for Min Max Scaling
		uint16_t linearTableIndex; ///< 2D Lookup table Index in User Buffer
	};
	uint16_t outputMax;  ///< Output max
	uint16_t filterConstant;  ///< Output Filter Constant 1.  Meaning varies by mode
	uint16_t filterConstant2;  ///< Output Filter Constant 2.  Meaning varies by mode
	uint16_t currentOutput;  //TODO is this used?
	//#ifdef OS_COM_TIMEOUT_PRESENT
	uint16_t commTimeout;  ///< Communications timeout period in mS
	uint16_t commTimeoutCounter; ///< Upwards Counter of timeout counter towards commTimeout
	uint16_t commTimeoutValue;  ///< Value to set output to if communication timeout expires
	//#endif

	uint16_t targetValue;  ///< Target value for control algorithms
	uint16_t lastValue; ///< prior filter output.  Used for output filtering
	uint8_t filterMode;  ///< Mode for output filter.  Enumerated type but not stored that way to ensure minimal storage space.
	uint8_t  transformMode; ///< Mode for transform.  Enumerated type but not stored that way to ensure minimal storage space. 
	uint8_t sourcePin;  ///< The pin from which the output scaling initial value is read
	uint8_t targetPin;  ///< The pin used to get the target value for control loop.  Host provided constant if 255
	uint8_t invert:1;   ///< Invert the output before sending to pin mode driver
	uint8_t active:1;   ///< Output scaling is enabled or disabled
	uint8_t sampleRate:4;  ///< Rate at which to run control and filtering algorithms.  Two to the Power of This number, in mS
	uint8_t outputScaleMode:1; ///< Enumerated type, but stored this way to minimize storage space

}outputScale_t;


void outputScaleInit(outputScale_t* outputScale);

void outputScaleResetTimeout(outputScale_t* outputScale);

uint16_t outputScaleProcess(outputScale_t* outputScale);
uint16_t outputScaleCommProcess(outputScale_t* outputScale);

#endif
