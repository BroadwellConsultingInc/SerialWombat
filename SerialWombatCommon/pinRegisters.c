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
uint16_t incrementingValue = 0;
uint16_t GetBuffer(uint8_t pin)
{
	if (pin < NUMBER_OF_TOTAL_PINS)
	{
		return(PinUpdateRegisters[pin].generic.buffer);
	}
	 else if (pin == 65)
    {
        return(incrementingValue++);
    }
    else if (pin == 66)
    {
        return GetADCConversion(0x1E);
    }
    
    else if (pin == 67)
    {
        extern uint32_t FramesRun;
        return ((uint16_t)FramesRun);
    }
    else if (pin == 68)
    {
        extern uint32_t FramesRun;
        return (FramesRun>>16);
    }
    else if (pin == 69)
    {
        extern uint16_t OverflowCount;
        return (OverflowCount);
    }
    else if (pin == 85) //0x55
    {
        return (0x5555);
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

