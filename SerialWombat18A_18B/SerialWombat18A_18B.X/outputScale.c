#include "SerialWombat.h"
#include "outputScale.h"
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
    outputScale->sampleRate = 10;
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

static uint32_t pid(uint32_t processVariable,outputScale_t* outputScale)
{
	uint32_t output;
	int32_t error = outputScale->targetValue - processVariable;
	int32_t integratorTemp = error * outputScale->pid.ki;
	integratorTemp /= 16384;
    outputScale->pid.integrator += integratorTemp;
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
	if ( error < 0)
	{
	     error = 0;
	}

	uint32_t erroru = error;

	output = erroru * outputScale->pid.kp;
	return (output >>8);



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
        }

	}
        else{
            outputValue = CurrentPinRegister->generic.buffer;  // Don't change unless on sample period
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

                        if (outputScale->sourcePin == CurrentPin)
                        {
                            difference = (int32_t)outputScale->targetValue - CurrentPinRegister->generic.buffer;
                        }
                        else
                        {
						difference = (int32_t)outputValue - CurrentPinRegister->generic.buffer;
                        }

						if (difference > 0)
						{
							if (difference > outputScale->filterConstant)
							{
								outputValue = CurrentPinRegister->generic.buffer + outputScale->filterConstant;
							}
							else
							{
								outputValue = CurrentPinRegister->generic.buffer + difference;
							}
						}
						else 
						{
							if (difference < -((int32_t)outputScale->filterConstant))
							{
								outputValue = CurrentPinRegister->generic.buffer - outputScale->filterConstant;
							}
							else
							{
								outputValue = CurrentPinRegister->generic.buffer + difference;
							}
						}
					}
					break;
                    
                    case OUTPUT_FILTER_MODE_FIRST_ORDER:
					{
                        if (outputScale->sourcePin == CurrentPin)
                        {
                            outputValue = CurrentPinRegister->generic.buffer;
                            outputValue *= outputScale->filterConstant;
                            outputValue += (65535- outputScale->filterConstant) * (uint32_t) outputScale->targetValue;
                            if (outputValue < 0xFFFF0000)
                            {
                                outputValue += 0x8000;
                            }
                            outputValue >>= 16;
                        }
                        else
                        {
                            uint32_t result;
                             result = CurrentPinRegister->generic.buffer;
                            result *= outputScale->filterConstant;
                            result += (65535- outputScale->filterConstant) * outputValue;
                            if (result < 0xFFFF0000)
                            {
                                result += 0x8000;
                            }
						outputValue = result >>16;
                        }

						
					}
					break;
			}
		}
		else
		{
			outputValue = CurrentPinRegister->generic.buffer;  // Don't change unless on sample period
		}
	}


	if (outputScale->outputMin != 0 || outputScale->outputMax != 65535)
	{

		outputValue *= (outputScale->outputMax - outputScale->outputMin);
		outputValue >>= 16;
		outputValue += outputScale->outputMin;
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
        }
        break;
        case 5:
        {
            outputScale->outputMin = RXBUFFER16(4);
            outputScale->outputMax = RXBUFFER16(6);
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
    }
    return(0);
}


