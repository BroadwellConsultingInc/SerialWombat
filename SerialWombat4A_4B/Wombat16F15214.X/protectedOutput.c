#include <stdint.h>
#include "serialWombat.h"

#define PO_METHOD_EQUAL 0
#define PO_METHOD_GREATER 2
#define PO_METHOD_LESS 3

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

