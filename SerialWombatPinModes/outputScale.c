/*
Copyright 2022-2024 Broadwell Consulting Inc.

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

/*! \file outputScale.c
 */


/*! 
\brief Initialize an outputScale structure
\param outputScale  A pointer to an outputScale_t structure, typically in a pin mode's memory area
*/

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
    outputScale->targetPin = 255;
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


/*! 
\brief Does a linear interpolation between a min and max of a value stored in outputScale structure
\param outputValue  16 Bit value to scale.  
\return A value scaled to a 0 to 65535 value
*/

static uint16_t  inputScaling(uint32_t outputValue, outputScale_t* outputScale)  
{
	// Scale the input.  This allows a sub-range of the input to drive the 
	// output a full 0 to 65535
	if (outputScale->inputMin != 0 || outputScale->inputMax != 65535) //TODO can the generic interpolation function be used?
	{
	    outputValue = xyInterpolationU16(outputValue,outputScale->inputMin,0,outputScale->inputMax,65535);

	}

	return((uint16_t)outputValue);
}

/*! 
\brief returns an output based on a hysteresis control algorthim
\param outputValue  16 Bit value to process via hysteresis
\param outputScale A pointer to an initialized outputScale structure containing settings for the Hystereis algorithm
\return A value  that is hystereis output
*/

static uint16_t hystersis(uint32_t outputValue,outputScale_t* outputScale) 
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

int32_t pidLastError = 0;  ///< Used for communication link.  Global Shared by all PIDs
int32_t pidLastIntegrator = 0; ///< Used for communication link.  Global Shared by all PIDs
int32_t pidLastIntegratorEffort = 0; ///< Used for communication link.  Global Shared by all PIDs
int32_t pidLastProportionalEffort = 0; ///< Used for communication link.  Global Shared by all PIDs
int32_t pidLastDerivativeEffort = 0; ///< Used for communication link.  Global Shared by all PIDs
int32_t pidLastEffort = 0; ///< Used for communication link.  Global Shared by all PIDs



/*! 
\brief returns an output based on an integer PID control algorthim
\param processVariable  16 Bit value to process via PID
\param outputScale A pointer to an initialized outputScale structure containing settings for the PiD algorithm
\return A value  that is PID output
*/
static uint16_t pid(uint32_t processVariable,outputScale_t* outputScale)
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

	if (outputScale->pid.add32768)
	{
		pidLastEffort += 32768; // If bidirectional
	}

	if (pidLastEffort > 65535) { pidLastEffort = 65535;}
	if (pidLastEffort < 0 ) { pidLastEffort = 0;}

	return ((uint16_t) pidLastEffort);
}


/*! 
\brief returns an output based on a 2 speed ramp control algorthim
\param processVariable  16 Bit value to process via ramp
\param outputScale A pointer to an initialized outputScale structure containing settings for the PiD algorithm
\return A value  that is hystereis output
*/
static uint16_t ramp(int32_t processVariable,outputScale_t* outputScale)
{
    int32_t newOutput = outputScale->ramp.lastRampOutput;

    if (outputScale->ramp.rampMode == OUTPUT_SCALE_RAMP_MODE_BOTH ||  outputScale->ramp.rampMode == OUTPUT_SCALE_RAMP_MODE_INCREMENT)
    {
    if (processVariable  + outputScale->ramp.slowIncrementDifference < outputScale->targetValue)
    {
        newOutput += outputScale->ramp.increment;
    }
    else if (processVariable  < outputScale->targetValue)
    {
        newOutput += outputScale->ramp.slowIncrement;
    }
    }
    if (outputScale->ramp.rampMode == OUTPUT_SCALE_RAMP_MODE_BOTH ||  outputScale->ramp.rampMode == OUTPUT_SCALE_RAMP_MODE_DECREMENT)
    {
     if (processVariable - outputScale->ramp.slowIncrementDifference > outputScale->targetValue)
    {
        newOutput -= outputScale->ramp.increment;
    }
    else if (processVariable  > outputScale->targetValue)
    {
        newOutput -= outputScale->ramp.slowIncrement;
    }
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


/*!
\brief Top Level Output Scale (output processing) function called by pin mode each frame 
\param outputScale  A pointer to an initialized ouputScale structure, typicallyl in pin mode memory
\return a 16 bit value to control a Pin's output 
*/
uint16_t outputScaleProcess(outputScale_t* outputScale)
{

	// Get the control value from the source pin.  By default this is this pin's public data buffer
	// as sourcePin is initialized to this pin's number
	// This step allows one pin to control another
	debugOutputScale = outputScale;
	uint32_t outputValue = GetBuffer(outputScale->sourcePin);
#ifdef OUTPUT_SCALE_ENABLE

	// If output scale system is inactive just return the output value
	if (!outputScale->active)
	{
		return (outputValue);
	}


	// Some control modes allow a control target value to be provided by another pin.  If configured
	// Load that value here
	if (outputScale->targetPin != 255)
	{
		outputScale->targetValue = GetBuffer(outputScale->targetPin);
	}


	// Perform input scaling.  This allows inputs to be scaled from their natural range to
	// a range of 0-65535.  This allows full use of the 16 bit range by algorithms such as PID
	// The Invert functionality also doesn't make much sense if the range isn't 0-65535
	// By default this step makes no changes to the output
	outputValue = inputScaling((uint16_t) outputValue,outputScale); 


	// Invert the input if configured.   This is useful to change direction of outputs
	// or for control algorithms where power application causes a negative change
	// in the feedback input (such as higher motor power causing shorter encoder pulse periods) 
	if (outputScale->invert)
	{
		outputValue = 65535 - outputValue;
	}

	// Transform the output.  Control Algorithms such as PID run in this step
	// The target value for the feedback control can be set as a constant in this
	// output scale module, or another pin's output can be the target value
	// The transform can be configured to only run occasionally, and output the
	// same value over a period of time between loop execution.  This allows
	// proper matching of the loop frequency with the physical response of the 
	// system being controlled.
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
						// Can't get here, but compiler throws a warning if 
						// all enumerated types aren't included in switch statement
					}
					break;

				case OUTPUT_TRANSFORM_MODE_HYSTERESIS:
					{
#ifdef OUTPUT_SCALE_HYSTERESIS_ENABLE
						outputValue = hystersis(outputValue,outputScale);
#endif
					}
					break;

				case OUTPUT_TRANSFORM_MODE_PID_CONTROL:
					{
#ifdef OUTPUT_SCALE_PID_ENABLE
						outputValue = pid(outputValue,outputScale);
#endif
					}
					break;
				case OUTPUT_TRANSFORM_MODE_RAMP:
					{
#ifdef OUTPUT_SCALE_RAMP_ENABLE
						outputValue = ramp(outputValue,outputScale);
#endif
					}
					break;
			}

		}
		else{
			outputValue = outputScale->lastValue;  // Don't change unless on sample period
		}
	}

	// Check for communications timeout.  This step allows the output to go to a default value
	// if communication is lost.  Note that this value overrides any feedback control algorithm.
	// If a timeout is needed which keeps a feedback loop, use communication timeout on another
	// pin, and use that pin's output as the target value for the feedback loop
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

	//  Next step is filtering.  This allows control of how fast an output can change.
	//  Output change can be controlled either by a limit of number of counts per period,
	//  or by a 1st order filter. 
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
						// Can't get here, but compiler throws a warning if 
						// all enumerated types aren't included in switch statement
					}
					break;
#ifdef OUTPUT_SCALE_OUTPUT_FILTER_CHANGE_LIMIT_ENABLE
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
#endif
#ifdef OUTPUT_SCALE_OUTPUT_FILTER_MODE_FIRST_ORDER_ENABLE
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
#endif
			}
		}
		else
		{
			outputValue = outputScale->lastValue;  // Don't change unless on sample period
		}
	}

	outputScale->lastValue = outputValue; // Remember the last filter output for use in next iteration


	// Finally, scale the output back from a 0-65535 range to a range that makes sense for the output
	// A simple 2 point option exists which is useful for cases such as limiting servo movement to a subset
	// of its range.
	// A 2D lookup table is also availalbe which uses interpolated xy lookup.  This is useful for 
	// linearizing non-linear outputs, such as apparent LED brightness vs duty cycle or 
	// eliminating dead zones where small amounts of power cannot move a motor.  This can make 
	// control algorithms function better. 
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


#endif
	return(outputValue);
}


/*!
\brief reset the output scale communication timeout timer.  Called by the host to prevent going to default value
\param outputScale  A pointer to an initialized outputScale_t structure, typically in pin mode memory
*/
void outputScaleResetTimeout(outputScale_t* outputScale)
{
    outputScale->commTimeoutCounter = 0;
}


/*!
\brief Process an output Scale configuration command
\param outputScale  A pointer to an initialized outputScale_t structure, typically in pin mode memory

This function processes output scale commands.  The command should be located in the global Rxbuffer.
This function is designed to be called from a pin processing command which has the pin processing
command number in Rxbuffer[0], the pin number in[1] and the pin mode in [2].  The Output Scaling sub
command is in [3], and parameters to that sub command are in [4] to [7].
*/

uint16_t outputScaleCommProcess(outputScale_t* outputScale)
{
    switch (Rxbuffer[3])
    {
        
        case 0:  // Set Output scaling active [4]
		 // inactive and set source pin[5]
		 // Whether to reinitialize output scaling to defaults when going inactive[6]
        {
#ifdef OUTPUT_SCALE_ENABLE
            outputScale->active = Rxbuffer[4];
            if (outputScale->active)
            {
		outputScale->sourcePin = Rxbuffer[5];
            }
            else 
            {
                if (Rxbuffer[6] == 0 )
                {
                    // Do not reset outputscaling
                }
                else
                {
                    outputScaleInit(outputScale);
                }
            }
#else
            if (Rxbuffer[4])
            {
                error (SW_ERROR_OUTPUT_SCALE_NOT_AVAILABLE);
            }
#endif
        }
        break;
        //Set timeout and timeout setting
#ifdef OUTPUT_SCALE_ENABLE
        case 1:
        {
            outputScale->commTimeout = RXBUFFER16(4);
            outputScale->commTimeoutValue = RXBUFFER16(6);
            outputScale->commTimeoutCounter = 0;
        }
        break;
        
        case 2: // Set input Scaling
        {
            outputScale->inputMin = RXBUFFER16(4);
            outputScale->inputMax = RXBUFFER16(6);
            
        }
        break;
        
        case 3: // Set inversion
        {
            outputScale->invert = Rxbuffer[4];
        }
        break;
        
        case 4:  // Set Filter mode and Filter constants (constant meanings vary by mode) 
        {
            outputScale->filterMode = Rxbuffer[4];
            outputScale->filterConstant = RXBUFFER16(5);
            outputScale->filterConstant2 = RXBUFFER16(5);
        }
        break;
        case 5:  // Set output Scaling min and max and mode 
        {
            outputScale->outputMin = RXBUFFER16(4);
            outputScale->outputMax = RXBUFFER16(6);
            outputScale->outputScaleMode = OUTPUT_SCALE_2POINT;
        }
        break;
        
        case 6: // Set feedback algorithm target value
        {
            outputScale->targetValue = RXBUFFER16(4);
        }
        break;
        
        case 7: // Set feedback algorithm period (1ms * 2 to the power provided)
        {
            outputScale->sampleRate = Rxbuffer[4];
        }
        break;
        
         case 8:  // Set filter constant 2 
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

        case 49: // Disable Transform / Feedback
        {
            outputScale->transformMode = OUTPUT_TRANSFORM_MODE_NONE;
        }
        break;
#ifdef OUTPUT_SCALE_HYSTERESIS_ENABLE
	case 50: // Set Hysteresis high values
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_HYSTERESIS;
		outputScale->hystersis.highLimit = RXBUFFER16(4);
		outputScale->hystersis.outputHigh = RXBUFFER16(6);
	}
	break;
	case 51:  // Set Hysteresis low values
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_HYSTERESIS;
		outputScale->hystersis.lowLimit = RXBUFFER16(4);
		outputScale->hystersis.outputLow = RXBUFFER16(6);
	}
	break;

	case 52: // Set last value (initializes  output)
	{
		outputScale->transformMode = OUTPUT_TRANSFORM_MODE_HYSTERESIS;
		outputScale->hystersis.lastValue = RXBUFFER16(4);
        outputScale->sampleRate = 0;
	}
	break;
#endif

#ifdef OUTPUT_SCALE_RAMP_ENABLE
        case 60:  // Set Ramp parameters (1 of 2)
        {
            outputScale->transformMode = OUTPUT_TRANSFORM_MODE_RAMP;
            outputScale->ramp.slowIncrement = RXBUFFER16(4);
            outputScale->ramp.slowIncrementDifference = RXBUFFER16(6);
            outputScale->ramp.increment = outputScale->ramp.slowIncrement;
            outputScale->ramp.lastRampOutput = GetBuffer(CurrentPin);
            outputScale->ramp.rampMode = OUTPUT_SCALE_RAMP_MODE_BOTH;
        }
        break;
         case 61: // Set Ramp parameters (2 of 2) 
        {
            if(outputScale->transformMode == OUTPUT_TRANSFORM_MODE_RAMP)
            {
            outputScale->ramp.increment = RXBUFFER16(4);
            outputScale->ramp.rampMode = Rxbuffer[6];
            
            }
        }
        break;
#endif
#ifdef OUTPUT_SCALE_PID_ENABLE
	case 100:  // Set PID kp and ki
	{
		outputScale->pid.kp = RXBUFFER16(4);
		outputScale->pid.ki = RXBUFFER16(6);
	}
	break;

	case 101:  // Set PID kd
	{
		outputScale->pid.kd = RXBUFFER16(4);
        
	}
	break;

	case 102: // Reset PID integrator to 0
	{
		outputScale->pid.integrator = 0;
	}
	break;
    
        case 103: // Get last PID error int32 (reads a global that is set by all PID controllers
        {
            memcpy(&Txbuffer[4], &pidLastError, 4);
        }
        break;
        case 104: // Get last PID Integrator int32 (reads a global that is set by all PID controllers)
        {
            memcpy(&Txbuffer[4], &pidLastIntegrator, 4);
        }
        break;
        case 105: // Get last PID Integrator effort int32 (reads a global that is set by all PID controllers) 
        {
            memcpy(&Txbuffer[4], &pidLastIntegratorEffort, 4);
        }
        break;
        case 106: // Get last PID proportional effort int32 (reads a global that is set by all PID controllers)
        {
            memcpy(&Txbuffer[4], &pidLastProportionalEffort, 4);
        }
        break;
        case 107: // Get last PID derivative effort int32 (reads a global that is set by all PID controllers)
        {
            memcpy(&Txbuffer[4], &pidLastDerivativeEffort, 4);
        }
        break;
        case 108: // Sets a PID offset to make neutral 32768 instead of 0
        {
            int32_t output = pidLastEffort;
            if (outputScale->pid.add32768)
            {
                output -= 32768;
            }
            memcpy(&Txbuffer[4], &output, 4); 
        }
        break;
        case 109: // Set the target pin for PID control
        {
            outputScale->transformMode = OUTPUT_TRANSFORM_MODE_PID_CONTROL;
            outputScale->targetPin = Rxbuffer[4];
            outputScale->pid.add32768 = Rxbuffer[5] > 0;
        }
        break;
         case 110:  // Simultaneously change the target value and reset the integrator
        {
            outputScale->targetValue = RXBUFFER16(4);
            outputScale->pid.integrator = 0;
        }
        break;
        
         case 111:   // Get the last feedback target value read from a pin
        {
           //Get last target value
            TXBUFFER16(4,outputScale->targetValue);
        }
        break;
#endif
#endif
         default:
             error(SW_ERROR_UNKNOWN_OUTPUTSCALE_COMMAND);
             break;
    }
    return(0);
}


