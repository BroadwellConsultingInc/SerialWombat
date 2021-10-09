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
uint32_t result = GetSourceVoltageADC();
        result *= 1024;  //Convert to 1.2  V reference to 1.024 v reference for compatibility with SW4B
        result /=1200;
        return ((uint16_t) result); 

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
     extern uint16_t OverflowFrames;
     return (OverflowFrames);
    }
    else if (pin == 70)
    {
        return ( GetTemperature_degC100ths());    
    }
     else if (pin == 71)
    {
         extern uint16_t PacketsProcessed;
        return (PacketsProcessed );    
    }
     else if (pin == 72)
     {
         extern uint16_t Errors;
         return(Errors);
     }
     else if (pin == 73)
     {
         extern volatile uint16_t FramesDropped;
         return (FramesDropped);
     }
     else if (pin == 74)
     {
         extern uint16_t SystemUtilizationAverage;
         return (SystemUtilizationAverage);
     }
    else if (pin == 85) //0x55
    {
        return (0x5555);
    }
    else
	{
		return(0);
	}
    return(0);
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

