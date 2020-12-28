#include <stdint.h>
#include <string.h>
#include "serialWombat.h"


pinRegister_t PinUpdateRegisters[NUMBER_OF_TOTAL_PINS];

#ifdef USE_BUFFERED_PIN_REGISTER

void CopyFromArrayToPinBuffer()
{
     memcpy(&pinRegisterBuffer,&PinUpdateRegisters[CurrentPin], sizeof(pinRegister_t));
    
}
void CopyFromPinBufferToArray()
{
   memcpy(&PinUpdateRegisters[CurrentPin],&pinRegisterBuffer, sizeof(pinRegister_t));
}

#else
pinRegister_t* CurrentPinRegister;
#endif

void SetBuffer(uint8_t pin, uint16_t value)
{
   if (pin < NUMBER_OF_TOTAL_PINS)
   {
        PinUpdateRegisters[pin].generic.buffer = value;
   }
}

uint16_t GetBuffer(uint8_t pin)
{
	if (pin < NUMBER_OF_TOTAL_PINS)
	{
		return(PinUpdateRegisters[pin].generic.buffer);
	}
	else if (pin == 64)
    {
        extern uint16_t FramesRun;
        return (FramesRun);
    }
    else if (pin == 65)
    {
        extern uint16_t OverflowCount;
        return (OverflowCount);
    }
    else if (pin == 66)
    {
        return GetADCConversion(0x1E);
    }
    else
	{
		return(0);
	}
}

void SetMode(uint8_t pin, uint8_t mode)
{
   if (pin < NUMBER_OF_TOTAL_PINS)
   {
        PinUpdateRegisters[pin].generic.mode = mode;
   }
}

uint8_t GetMode(uint8_t pin)
{
	if (pin < NUMBER_OF_TOTAL_PINS)
	{
		return(PinUpdateRegisters[pin].generic.mode);
	}
	else
	{
		return(0);
	}
}

