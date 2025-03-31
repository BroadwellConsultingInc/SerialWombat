/*
Copyright 2020 Broadwell Consulting Inc.

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

#include <stdint.h>
#include "serialWombat.h"

#define PO_METHOD_EQUAL 0
#define PO_METHOD_GREATER 1
#define PO_METHOD_LESS 2

typedef struct protectedOutput_n{
	uint16_t expectedValue;
	uint8_t monitorPin;
	uint8_t debounceTime;
	uint8_t differenceCount;
	uint8_t safeState;
	uint8_t matchMethod;
	uint8_t tempMistmatchBit:1;
}protectedOutput_t;

#define protectedOutput ((protectedOutput_t*) CurrentPinRegister)

void initProtectedOutput (void)
{
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PROTECTEDOUTPUT)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
		{
			CurrentPinRegister->generic.mode = PIN_MODE_PROTECTEDOUTPUT;
			protectedOutput->expectedValue = RXBUFFER16(3);
			protectedOutput->debounceTime = Rxbuffer[5];
			protectedOutput->differenceCount = protectedOutput->debounceTime;
			protectedOutput->monitorPin = Rxbuffer[6];
			protectedOutput->safeState = Rxbuffer[7];
			SetCurrentPin(protectedOutput->safeState);  
		
		}
		break;
		case CONFIGURE_CHANNEL_MODE_1:
		{
			protectedOutput->differenceCount = 0;
			protectedOutput->matchMethod = Rxbuffer[3];
			SetCurrentPin(Rxbuffer[4]);
		}
		break;
        
                default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
	}
}



void updateProtectedOutput()
{ 
	protectedOutput->tempMistmatchBit = 0;
	uint16_t data = GetBuffer(protectedOutput->monitorPin);
	switch (protectedOutput->matchMethod)
	{
		case PO_METHOD_EQUAL:
		{
			if (data != protectedOutput->expectedValue)
			{
				protectedOutput->tempMistmatchBit = 1;
			}
		}
		break;

		case PO_METHOD_GREATER:
		{
			if (data < protectedOutput->expectedValue)
			{
				protectedOutput->tempMistmatchBit = 1;
			}
		}
		break;
		case PO_METHOD_LESS:
		{
			if (data > protectedOutput->expectedValue)
			{
				protectedOutput->tempMistmatchBit = 1;
			}
		}
		break;
	}
    if (protectedOutput->differenceCount < protectedOutput->debounceTime)
	{
	if (protectedOutput->tempMistmatchBit )
	{
		
			++protectedOutput->differenceCount;
		
	}
	else
	{
		protectedOutput->differenceCount = 0;
	}	
    }

	if (protectedOutput->differenceCount >= protectedOutput->debounceTime)
	{
		SetCurrentPin(protectedOutput->safeState);
	}
  	CurrentPinRegister->generic.buffer = protectedOutput->differenceCount; 
}


