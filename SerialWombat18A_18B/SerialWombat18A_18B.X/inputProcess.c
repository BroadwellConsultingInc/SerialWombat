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
#include "inputProcess.h"
void inputProcessInit(inputProcess_t* inputProcess)
{
	inputProcess->filterMode = INPUT_FILTER_MODE_NONE;
	inputProcess->active = 0;
    inputProcess->average.samplesToAverage = 64;
    inputProcess->firstOrder.filterconstant = 0xFF80;
	inputProcess->initialized = 0;
    inputProcess->excludeAbove = 65535;
    inputProcess->excludeBelow = 0;
    inputProcess->queue = 0xFFFF;
    inputProcess->queueFrequency = 0;
    inputProcess->min = 65535;
    inputProcess->max = 0;
}


const uint16_t inputProcessSamplePeriodMask[] = 
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


inputProcess_t* debugInputProcess;
uint16_t inputProcessProcess(inputProcess_t* inputProcess, uint16_t inputValue)
{
    
    debugInputProcess = inputProcess;
    
    if (inputProcess->active)
    {
        if (inputValue > inputProcess->excludeAbove || inputValue < inputProcess->excludeBelow)
        {
            inputValue = inputProcess->lastInput;
        }
        
        inputProcess->lastInput = inputValue;
        
        if (inputProcess->invert)
        {
            inputValue = 65535 - inputValue;
        }
        {
            //Process Transform
            switch (inputProcess->transformMode)
            {
                case INPUT_TRANSFORM_MODE_SCALE_RANGE:
                {
                    if (inputValue >= inputProcess->scaleRange.high)
                    {
                        inputValue = 65535;
                    }
                    else if (inputValue <= inputProcess->scaleRange.low)
                    {
                        inputValue = 0;
                    }
                    else
                    {
                        uint32_t temp = inputValue - inputProcess->scaleRange.low;
                        temp *= 65536;
                        temp /= (inputProcess->scaleRange.high - inputProcess->scaleRange.low);
                        inputValue = temp;
                    }
                    
                }
                break;
                
                case INPUT_TRANSFORM_MODE_LINEAR_MXB:
                {
                    int32_t temp = inputProcess->mxb.m * inputValue;
                    temp /= 256;
                    temp += inputProcess->mxb.b;
                    if (temp > 65535)
                    {
                        temp = 65535;
                    }
                    else if (temp < 0)
                    {
                        temp = 0;
                    }
                    
                    inputValue = (uint16_t) temp;
                }
                break;
                
                case INPUT_TRANSFORM_MODE_NONE:
                default:
                {
                    
                }
              
            }
            
            
        }
        { // Process Average
                if (!inputProcess->initialized || inputProcess->average.samplesAddedToSum > inputProcess->average.samplesToAverage)
                {
                    inputProcess->average.average = inputValue;
                    inputProcess->average.sum = 0;
                    inputProcess->average.samplesAddedToSum = 0;
                }               
                inputProcess->average.sum += inputValue;
                ++inputProcess->average.samplesAddedToSum;
                if (inputProcess->average.samplesAddedToSum == inputProcess->average.samplesToAverage)
                {
                    inputProcess->average.sum /= inputProcess->average.samplesToAverage;
                    if (inputProcess->average.sum > 65535)
                    {
                        inputProcess->average.sum = 65535;
                    }
                    inputProcess->average.average = inputProcess->average.sum;
                    inputProcess->average.sum = 0;
                    inputProcess->average.samplesAddedToSum = 0;
                }    
            }
             { // Process Filter
                if (!inputProcess->initialized )
                {
                    inputProcess->firstOrder.filteredValue = inputValue;
                }               
                uint32_t filter =  (uint32_t)inputProcess->firstOrder.filteredValue * inputProcess->firstOrder.filterconstant;
                filter += (uint32_t) inputValue * (65535 - inputProcess->firstOrder.filterconstant);
                filter>>= 16;
                inputProcess->firstOrder.filteredValue = filter;
            }
       
            switch (inputProcess->filterMode)
            {
                case INPUT_FILTER_MODE_AVERAGE:
                {
                    inputValue = inputProcess->average.average;
                }
                 break;
                 
                case INPUT_FILTER_MODE_FIRST_ORDER:
                {
                    inputValue = inputProcess->firstOrder.filteredValue;
                }
                
            }
           
                
             
       
            inputProcess->initialized = 1;
    }
    else
    {
        inputProcess->initialized = 0;
    }

    if (inputValue < inputProcess->min)
    {
        inputProcess->min =  inputValue;
    }
    if (inputValue > inputProcess->max)
    {
        inputProcess->max = inputValue;
    }
    
    if (inputProcess->queue != 0xFFFF )
    {
        extern uint32_t FramesRun;
		if ((FramesRun & inputProcessSamplePeriodMask[inputProcess->queueFrequency])  == 0)
		{
            uint16_t bytesAvailable;
            if (QueueGetBytesFreeInQueue(inputProcess->queue,&bytesAvailable) == QUEUE_RESULT_SUCCESS)
            {
                if (bytesAvailable >= 2)
                {
                    if (inputProcess->queueLowByte)
                    {
                        QueueAddByte(inputProcess->queue, (uint8_t)inputValue);
                    }
                    if (inputProcess->queueHighByte)
                    {
                        QueueAddByte(inputProcess->queue, (uint8_t)(inputValue>>8));                        
                    }
                }
            }
        }
    }
    return (inputValue);
	
}

void inputProcessCommProcess(inputProcess_t* inputProcess)
{
    switch (Rxbuffer[3])
	{

        case 0:
        {
             inputProcess->active = Rxbuffer[4];
             if (!inputProcess->active)
             {
                 inputProcess->initialized = 0;
             }
        }
        break;
        
        case 1:
        {
            inputProcess->average.samplesToAverage = RXBUFFER16(4);
            inputProcess->firstOrder.filterconstant = RXBUFFER16(6);
        }
        break;
        case 2:
        {
            inputProcess->excludeBelow = RXBUFFER16(4);
            inputProcess->excludeAbove = RXBUFFER16(6);
        }
        break;
        
        case 3:
        {
            inputProcess->invert = Rxbuffer[4];
        }
        break;
        
        case 4:
        {
            inputProcess->filterMode = Rxbuffer[4];
        }
        break;
        
        case 5:
        {
            inputProcess->queue = RXBUFFER16(4);
            inputProcess->queueFrequency = Rxbuffer[6];
            inputProcess->queueHighByte = (Rxbuffer[7] & 0x02) >0;
            inputProcess->queueLowByte = (Rxbuffer[7] & 0x01) >0;
        }
        break;
        
        case 6:
        {
            inputProcess->transformMode = INPUT_TRANSFORM_MODE_SCALE_RANGE;
            inputProcess->scaleRange.low = RXBUFFER16(4);
            inputProcess->scaleRange.high= RXBUFFER16(6);
        }
        break;
        
         case 7:
        {
            inputProcess->mxb.m =(int32_t) RXBUFFER32(4);
        }
         break;
        case 8:
		{
            inputProcess->transformMode = INPUT_TRANSFORM_MODE_LINEAR_MXB;
            inputProcess->mxb.b = (int32_t)RXBUFFER32(4);
		}
		break;
        
        case 9:
        {
            TXBUFFER16(4,inputProcess->min);
          
            if (Rxbuffer[4] > 0)
            {
                inputProcess->min = 65535;

            }
        }
        break;
        
        case 10:
        {
            TXBUFFER16(4,inputProcess->max);
          
            if (Rxbuffer[4] > 0)
            {
                inputProcess->max = 0;

            }
        }
        break;
        
        case 11:
        {
            TXBUFFER16(4,inputProcess->average.average);
            TXBUFFER16(6,inputProcess->firstOrder.filteredValue);    
        }
        break;
        
        default:
        {
            
        }
        break;

	}
}






