/*
Copyright 2024 Broadwell Consulting Inc.

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

/* Serial Wombat is a trademark of Broadwell Consulting Inc. */

#include "serialWombat.h"
#include <stdint.h>
#include "outputScale.h"

#define QUEUE_ENTRIES 20
typedef struct queuedPulseOutput_n{
    DMABitStream_t bitStream;
	uint16_t internalQueue[QUEUE_ENTRIES];
	uint16_t queueAddress;
	uint16_t remainingCounts;
	uint8_t units:1; // 0 = uS, 1 = mS
	uint8_t idleState:2; // 0 = Low, 1 = high, 2 = last value
    uint8_t paused:1;
    	uint8_t currentUSState:1;
	uint8_t repeat;
	uint8_t itemsInQueue;
	uint8_t queueHead;
	uint8_t repeatItem;
	uint8_t repeatCount;
}queuedPulseOutput_t;

void updatehQueuedPulseOutput(void);




#define queuedPulseOutput  ((queuedPulseOutput_t*) CurrentPinRegister)
queuedPulseOutput_t* debugQueuedPulseOutput;


static uint8_t PushQueue(uint16_t value)
{
	if (queuedPulseOutput->itemsInQueue < QUEUE_ENTRIES)
	{
		uint8_t index = queuedPulseOutput->itemsInQueue + queuedPulseOutput->queueHead;
		index %= QUEUE_ENTRIES;
		queuedPulseOutput->internalQueue[index] = value;
		queuedPulseOutput->itemsInQueue ++;
		return 1;
	}
	else return 0;
}

static  int32_t ShiftQueue(void)
{
    if (queuedPulseOutput->queueAddress == 0xFFFF)
    {
	if (queuedPulseOutput->itemsInQueue)
	{
		uint16_t returnval = queuedPulseOutput->internalQueue[queuedPulseOutput->queueHead];
		--queuedPulseOutput->itemsInQueue;
		++queuedPulseOutput->queueHead;
		queuedPulseOutput->queueHead %= QUEUE_ENTRIES;
        return returnval;
	}
	else
	{
		return -1;
	}
    }
    else
    {
        uint16_t returnval;
        if  (QueueRead16Word(queuedPulseOutput->queueAddress, &returnval) == QUEUE_RESULT_SUCCESS)
        {
            return returnval;
        }
        return -1;
    }

}

void initQueuedPulseOutput (void)
{
	debugQueuedPulseOutput = queuedPulseOutput;
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_QUEUED_PULSE_OUTPUT)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	BUILD_BUG_ON( sizeof(queuedPulseOutput_t) >  BYTES_AVAIALABLE_OUTPUT_PULSE );   
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_QUEUED_PULSE_OUTPUT;
				CurrentPinRegister->generic.buffer = 0;

				InitializePinLow(CurrentPin);
				SetCurrentPin(Rxbuffer[3]);
				queuedPulseOutput->remainingCounts = 0;
				queuedPulseOutput->idleState = Rxbuffer[4];
				queuedPulseOutput->units = Rxbuffer[5];
				queuedPulseOutput->queueAddress = RXBUFFER16(6);
				queuedPulseOutput->itemsInQueue = 0;
				queuedPulseOutput->queueHead = 0;
				queuedPulseOutput->repeat = 0;
				queuedPulseOutput->paused = 0;
				if (queuedPulseOutput->units == 0)
				{
					initializeBitStreamOutput(CurrentPin,  Rxbuffer[3], &queuedPulseOutput->bitStream );
					PinLow(CurrentPin);
				}

			}
			break;
		case CONFIGURE_CHANNEL_MODE_1:  // Add items to queue
			{
				uint8_t result = 0;
				if (RXBUFFER16(3) > 0)
				{
					result += PushQueue(RXBUFFER16(3));
				}
				if (RXBUFFER16(5) > 0)
				{
					result += PushQueue(RXBUFFER16(5));
				}
				Txbuffer[3] = result;
				Txbuffer[4] = queuedPulseOutput->itemsInQueue;
				Txbuffer[5] = QUEUE_ENTRIES - queuedPulseOutput->itemsInQueue;
			}
			break;

		case CONFIGURE_CHANNEL_MODE_2:  // Add items to queue
			{
				queuedPulseOutput->paused = (Rxbuffer[3] > 0);
			}
			break;

		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;


	}
}


void updateQueuedPulseOutput(void)
{
	if (queuedPulseOutput->units == 1)
	{
		if (queuedPulseOutput->remainingCounts)
		{
			-- queuedPulseOutput->remainingCounts;
			return;
		}
		int32_t value = -1;
		if (! queuedPulseOutput->paused)
		{
			value = ShiftQueue();
		}
		if (value >= 0)
		{
			if (value & 0x8000)
			{
				CurrentPinHigh();
			}
			else
			{
				CurrentPinLow();
			}
			queuedPulseOutput->remainingCounts = value & 0x7FFF;
		}
		else
		{
			switch(queuedPulseOutput->idleState)
			{
				case 0:
					{
						CurrentPinLow();
					}
					break;

				case 1:
					{
						CurrentPinHigh();
					}
					break;

				default:
					{
						//leave the output alone
					}
					break;
			}

		}
	}
	else
	{
		//Microseconds.  Use DMA

		if (queuedPulseOutput->remainingCounts)
		{
			queuedPulseOutput->remainingCounts = updateBitStreamOutput(CurrentPin, queuedPulseOutput->currentUSState, queuedPulseOutput->remainingCounts, &queuedPulseOutput->bitStream);
		}

		while (queuedPulseOutput->remainingCounts == 0)
		{

			int32_t value = -1;
			if (! queuedPulseOutput->paused)
			{
				value = ShiftQueue();
			}
			if (value >= 0)
			{
               
				if (value & 0x8000)
				{
					queuedPulseOutput->currentUSState = 1;
				}
				else
				{
					queuedPulseOutput->currentUSState = 0;
				}
                uint32_t valueInNips = (value & 0x7FFF) * 3774;  // Multiply by 3774/65536 =  1/57600
                valueInNips >>= 16;
				queuedPulseOutput->remainingCounts = (uint16_t) valueInNips;
                queuedPulseOutput->remainingCounts = updateBitStreamOutput(CurrentPin, queuedPulseOutput->currentUSState, queuedPulseOutput->remainingCounts, &queuedPulseOutput->bitStream);
			}
			else
			{
				queuedPulseOutput->remainingCounts = 0;
				switch(queuedPulseOutput->idleState)
				{
					case 0:
						{
							queuedPulseOutput->currentUSState = 0;
						}
						break;

					case 1:
						{
							queuedPulseOutput->currentUSState = 1;
						}
						break;

					default:
						{
							//leave the output alone
						}
						break;
				}
				updateBitStreamOutput(CurrentPin, queuedPulseOutput->currentUSState, DMA_FREQUENCY / 1000 + 3,  &queuedPulseOutput->bitStream);
				break;
			}
		}
	}

}


