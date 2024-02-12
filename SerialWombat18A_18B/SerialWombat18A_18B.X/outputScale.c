/*
Copyright 2022-2023 Broadwell Consulting Inc.

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

#include "serialWombat.h"
#include "outputScale.h"
#include "swMath.h"
#include <string.h> //for memcpy
void outputScaleInit(outputScale_t* outputScale)
{
    outputScale->sourcePin = CurrentPin;
    outputScale->inputMin = 0;
    outputScale->inputMax = 65535;
    outputScale->outputMin = 0;
    outputScale->outputMax = 65535;
    outputScale->filterConstant = 0;
    outputScale->transformMode = OUTPUT_TRANSFORM_MODE_NONE;
    outputScale->filterMode = OUTPUT_FILTER_MODE_NONE;
    outputScale->invert = 0;
    outputScale->commTimeout = 0;
    outputScale->commTimeoutCounter = 0;
    outputScale->active = 0;
    outputScale->sampleRate = 0;
    outputScale->lastValue = GetBuffer(outputScale->sourcePin);
    outputScale->outputScaleMode = OUTPUT_SCALE_2POINT;
}


const uint16_t outputSamplePeriodMask[] = 
{
    0x00, // Every 1
    0x01, // Every 2
    0x03, // Every 4
    0x07, // Every 8
    0x0F, // Every 16
    0x1F, // Every 32
    0x3F, // Every 64
    0x7F, // Every 128
    0xFF, // Every 256
    0x1FF, // every 512
    0x3FF, // every 1024
    
    0x7FF, // Every 2048
    0xfff, // Every 4096
    0x1fff, // Every 8192
    0x3fff, // Every 16384
    0x7fff, // Every 32768
    0xffff, // Every 32768
};

static uint32_t  inputScaling(uint32_t outputValue, outputScale_t* outputScale)
{
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

	return(outputValue);

}


static uint32_t hystersis(uint32_t outputValue,outputScale_t* outputScale)
{
	
	if (outputValue >= outputScale->hystersis.highLimit)
	{
		outputScale->hystersis.lastValue = outputScale->hystersis.outputHigh;
	}
	else if (outputValue <= outputScale->hystersis.lowLimit)
	{
		outputScale->hystersis.lastValue = outputScale->hystersis.outputLow;
	}
	return (outputScale->hystersis.lastValue);
}

int32_t pidLastError = 0;
int32_t pidLastIntegrator = 0;
int32_t pidLastIntegratorEffort = 0;
int32_t pidLastProportionalEffort = 0;
int32_t pidLastDerivativeEffort = 0;
int32_t pidLastEffort = 0;
static uint32_t pid(uint32_t processVariable,outputScale_t* outputScale)
{
	int32_t error = outputScale->targetValue - processVariable;
    pidLastError = error;

    outputScale->pid.integrator += error;
    pidLastIntegratorEffort = outputScale->pid.integrator * outputScale->pid.ki;
	pidLastIntegratorEffort /= 16384;
    if (pidLastIntegratorEffort > 65535)
    {
        //Prevent Windup that doesn't accomplish anything
        outputScale->pid.integrator = ((uint32_t)65535) * 16384 / outputScale->pid.ki;
    }
    pidLastIntegrator = outputScale->pid.integrator;
	pidLastDerivativeEffort = error - outputScale->pid.lastError;
	outputScale->pid.lastError = error;
	pidLastDerivativeEffort *= outputScale->pid.kd;
	pidLastDerivativeEffort /= 256;
	pidLastProportionalEffort = error * outputScale->pid.kp / 256;
    pidLastEffort = pidLastProportionalEffort + pidLastIntegratorEffort + pidLastDerivativeEffort;

    pidLastEffort += 32768; // If bidirectional
    
    if (pidLastEffort > 65535) { pidLastEffort = 65535;}
    if (pidLastEffort < 0 ) { pidLastEffort = 0;}
	

	
	return ((uint16_t) pidLastEffort);



}
/* old PID
static uint32_t pid(uint32_t processVariable,outputScale_t* outputScale)
{
	int32_t output;
	int32_t error = outputScale->targetValue - processVariable;
    pidLastError = error;
	int32_t integratorTemp = error * outputScale->pid.ki;
	integratorTemp /= 16384;
    outputScale->pid.integrator += integratorTemp;
    pidLastIntegrator = outputScale->pid.integrator;
	int32_t derivative = processVariable - outputScale->pid.lastProcessVariable;
	outputScale->pid.lastProcessVariable = processVariable;
	derivative *= outputScale->pid.kd;
	derivative/= 16384;
	error +=  outputScale->pid.integrator;
	error -= derivative;
    
	if (error >65535)
	{
		error = 65535;
	}
	if (error < -65535)
    {
        error = - 65535;
    }

   
	

	output = error * outputScale->pid.kp;

    
    //If Bidirectional
    
   
    output /= 8;
    output += 0x8000; // If bidirectional

    if (output > 65535)
    {
        output = 65535;
    }
    if (output < 0)
    {
        output = 0;
    }
	return (output);



}*/

static uint16_t ramp(int32_t processVariable,outputScale_t* outputScale)
{
    int32_t newOutput = outputScale->ramp.lastRampOutput;
    if (processVariable  + outputScale->ramp.slowIncrementDifference < outputScale->targetValue)
    {
        newOutput += outputScale->ramp.increment;
    }
    else if (processVariable  < outputScale->targetValue)
    {
        newOutput += outputScale->ramp.slowIncrement;
    }
    else if (processVariable - outputScale->ramp.slowIncrementDifference > outputScale->targetValue)
    {
        newOutput -= outputScale->ramp.increment;
    }
    else if (processVariable  > outputScale->targetValue)
    {
        newOutput -= outputScale->ramp.slowIncrement;
    }
   
    if (newOutput > 65535)
    {
        newOutput = 65535;
    }
    else if (newOutput < 0 )
    {
        newOutput = 0;
    }
    
    outputScale->ramp.lastRampOutput = newOutput;
    
    return ((uint16_t) newOutput);
}

outputScale_t* debugOutputScale;
uint16_t outputScaleProcess(outputScale_t* outputScale)
{
    debugOutputScale = outputScale;
	uint32_t outputValue = GetBuffer(outputScale->sourcePin);
    
   
	if (!outputScale->active)
	{
		return (outputValue);
	}

	outputValue = inputScaling((uint16_t) outputValue,outputScale); 


	if (outputScale->invert)
	{
		outputValue = 65535 - outputValue;
	}

    if (outputScale->transformMode != OUTPUT_TRANSFORM_MODE_NONE)
	{
        extern uint32_t FramesRun;
		if ((FramesRun & outputSamplePeriodMask[outputScale->sampleRate])  == 0)
		{
	switch (outputScale->transformMode)
	{

		default:
		case OUTPUT_TRANSFORM_MODE_NONE:
			{

			}
			break;
		case OUTPUT_TRANSFORM_MODE_HYSTERESIS:
			{
				outputValue = hystersis(outputValue,outputScale);
			}
			break;
            
            case OUTPUT_TRANSFORM_MODE_PID_CONTROL:
			{
				outputValue = pid(outputValue,outputScale);
			}
			break;
            
             case OUTPUT_TRANSFORM_MODE_RAMP:
			{
				outputValue = ramp(outputValue,outputScale);
			}
			break;
        }

	}
        else{
            outputValue = outputScale->lastValue;  // Don't change unless on sample period
        }
    }

	if (outputScale->commTimeout > 0)
	{
		if (outputScale->commTimeoutCounter < outputScale->commTimeout)
		{
			++outputScale->commTimeoutCounter;
		}
		else
		{
			outputValue = outputScale->commTimeoutValue;
		}
	}

	if (outputScale->filterConstant > 0  && outputScale->filterMode != OUTPUT_FILTER_MODE_NONE)
	{
		extern uint32_t FramesRun;
		if ((FramesRun & outputSamplePeriodMask[outputScale->sampleRate])  == 0)
		{
			switch (outputScale->filterMode)
			{
				default:
				case OUTPUT_FILTER_MODE_NONE:
					{
						// Do nothing
					}
					break;

				case OUTPUT_FILTER_MODE_CHANGE_LIMIT:
					{
						int32_t difference;

                       
						difference = (int32_t)outputValue - outputScale->lastValue;
                     

						if (difference > 0)
						{
							if (difference > outputScale->filterConstant)
							{
								outputValue = outputScale->lastValue + outputScale->filterConstant;
							}
							else
							{
								outputValue = outputScale->lastValue + difference;
							}
						}
						else 
						{
							if (difference < -((int32_t)outputScale->filterConstant2))
							{
								outputValue = outputScale->lastValue - outputScale->filterConstant2;
							}
							else
							{
								outputValue = outputScale->lastValue + difference;
							}
						}
					}
					break;
                    
                    case OUTPUT_FILTER_MODE_FIRST_ORDER:
					{
                       
                        
                            uint32_t result;
                             result = outputScale->lastValue;
                            result *= outputScale->filterConstant;
                            result += (65535- outputScale->filterConstant) * outputValue;
                            if (result < 0xFFFF0000)
                            {
                                result += 0x8000;
                            }
						outputValue = result >>16;
                        

						
					}
					break;
			}
		}
		else
		{
			outputValue = outputScale->lastValue;  // Don't change unless on sample period
		}
	}

    outputScale->lastValue = outputValue;
    switch (outputScale->outputScaleMode)
    {
        case OUTPUT_SCALE_2POINT:
        {
	if (outputScale->outputMin != 0 || outputScale->outputMax != 65535)
	{

		outputValue *= (outputScale->outputMax - outputScale->outputMin);
		outputValue >>= 16;
		outputValue += outputScale->outputMin;
    }
	}
        break;
        case OUTPUT_SCALE_XY_LINEAR_INTERPOLATION:
        {
            int count = 0;
            uint16_t* data = (uint16_t*)&UserBuffer[outputScale-> linearTableIndex];
            while (outputValue > data[2]  && count  < 16)
            {
                data += 2; // Move forward two entries (one x, one y)
                ++ count;
            }
            if (count < 16)
            {
                //We found a match
                // At this point  data points to the point below, data[2] 
                // points to the point above.
                if (outputValue == data[0])
                {
                    //Exact match.  Set to y value
                    outputValue = data[1];
                }
                else if (outputValue == data[2])
                {
                    //Exact match.  Set to y value
                    outputValue = data[3];
                }
                else
                {
                    //Interpolate
                    outputValue = xyInterpolationU16(outputValue,data[0],data[1],data[2],data[3]);
                }
                
            }
            
            
            
        }
        break;
    }

  

	return(outputValue);
}

void outputScaleResetTimeout(outputScale_t* outputScale)
{
    outputScale->commTimeoutCounter = 0;
}

uint16_t outputScaleCommProcess(outputScale_t* outputScale)
{
    switch (Rxbuffer[3])
    {
        
        case 0:
        {
            outputScale->active = Rxbuffer[4];
            if (outputScale->active)
            {
		outputScale->sourcePin = Rxbuffer[5];
            }
            else 
            {
                outputScaleInit(outputScale);
            }
        }
        break;
        //Set timeout and timeout setting
        case 1:
        {
            outputScale->commTimeout = RXBUFFER16(4);
            outputScale->commTimeoutValue = RXBUFFER16(6);
            outputScale->commTimeoutCounter = 0;
        }
        break;
        
        case 2:
        {
            outputScale->inputMin = RXBUFFER16(4);
            outputScale->inputMax = RXBUFFER16(6);
            
        }
        break;
        
        case 3:
        {
            outputScale->invert = Rxbuffer[4];
        }
        break;
        
        case 4: 
        {
            outputScale->filterMode = Rxbuffer[4];
            outputScale->filterConstant = RXBUFFER16(5);
            outputScale->filterConstant2 = RXBUFFER16(5);
        }
        break;
        case 5:
        {
            outputScale->outputMin = RXBUFFER16(4);
            outputScale->outputMax = RXBUFFER16(6);
            outputScale->outputScaleMode = OUTPUT_SCALE_2POINT;
        }
        break;
        
        case 6:
        {
            outputScale->targetValue = RXBUFFER16(4);
        }
        break;
        
        case 7:
        {
            outputScale->sampleRate = Rxbuffer[4];
        }
        break;
        
         case 8: 
        {
            outputScale->filterConstant2 = RXBUFFER16(4);
        }
        break;
        
        case 9:  //Request last value
        {
            TXBUFFER16(4,outputScale->lastValue);
        }
        break;
        
        case 10: // Set up linear interpolation output
        {
            if ((RXBUFFER16(4) & 0x01)  == 1)
            {
                error(SW_ERROR_NOT_WORD_ALIGNED);
                return 0;
            }
            if (RXBUFFER16(4) < SIZE_OF_USER_BUFFER - 64) 
            {
                 outputScale->outputScaleMode = OUTPUT_SCALE_XY_LINEAR_INTERPOLATION;
            outputScale->linearTableIndex = RXBUFFER16(4);
            }
            else
            {
                error(SW_ERROR_RUB_INVALID_ADDRESS);
                return 0 ;
            }
            
        }
        break;

        case 49:
        {
            outputScale->transformMode = OUTPUT_TRANSFORM_MODE_NONE;
        }
        break;
	case 50:
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_HYSTERESIS;
		outputScale->hystersis.highLimit = RXBUFFER16(4);
		outputScale->hystersis.outputHigh = RXBUFFER16(6);
	}
	break;
	case 51:
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_HYSTERESIS;
		outputScale->hystersis.lowLimit = RXBUFFER16(4);
		outputScale->hystersis.outputLow = RXBUFFER16(6);
	}
	break;
	case 52:
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_HYSTERESIS;
		outputScale->hystersis.lastValue = RXBUFFER16(4);
        outputScale->sampleRate = 0;
	}
	break;
    
        case 60: 
        {
            outputScale->transformMode = OUTPUT_TRANSFORM_MODE_RAMP;
            outputScale->ramp.slowIncrement = RXBUFFER16(4);
            outputScale->ramp.slowIncrementDifference = RXBUFFER16(6);
            outputScale->ramp.increment = outputScale->ramp.slowIncrement;
            outputScale->ramp.lastRampOutput = GetBuffer(CurrentPin);
        }
        break;
         case 61: 
        {
            if(outputScale->transformMode == OUTPUT_TRANSFORM_MODE_RAMP)
            {
            outputScale->ramp.increment = RXBUFFER16(4);
            
            }
        }
        break;

	case 100: 
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_PID_CONTROL;
		outputScale->pid.kp = RXBUFFER16(4);
		outputScale->pid.ki = RXBUFFER16(6);
	}
	break;

	case 101: 
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_PID_CONTROL;
		outputScale->pid.kd = RXBUFFER16(4);
	}
	break;

	case 102:
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_PID_CONTROL;
		outputScale->pid.integrator = 0;
	}
	break;
    
        case 103:
        {
            memcpy(&Txbuffer[4], &pidLastError, 4);
        }
        break;
        case 104:
        {
            memcpy(&Txbuffer[4], &pidLastIntegrator, 4);
        }
        break;
        case 105:
        {
            memcpy(&Txbuffer[4], &pidLastIntegratorEffort, 4);
        }
        break;
        case 106:
        {
            memcpy(&Txbuffer[4], &pidLastProportionalEffort, 4);
        }
        break;
        case 107:
        {
            memcpy(&Txbuffer[4], &pidLastDerivativeEffort, 4);
        }
        break;
        case 108:
        {
            int32_t output = pidLastEffort - 32768; //If bidirectional
            memcpy(&Txbuffer[4], &output, 4); 
        }
        break;
    }
    return(0);
}


