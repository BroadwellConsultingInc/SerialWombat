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


void pinRegisterSizeCheck()
{
    BUILD_BUG_ON( sizeof(pinRegister_t) != 64 );
}

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
	 else if (pin == SW_DATA_SOURCE_INCREMENTING_NUMBER)
    {
        return(incrementingValue++);
    }
    else if (pin == SW_DATA_SOURCE_1024mvCounts)
    {
uint32_t result = GetSourceVoltageADC();
        result *= 1024;  //Convert to 1.2  V reference to 1.024 v reference for compatibility with SW4B
        result /=1200;
        return ((uint16_t) result); 

    }
    
    else if (pin == SW_DATA_SOURCE_FRAMES_RUN_LSW)
    {
       extern uint32_t FramesRun;
       return ((uint16_t)FramesRun);
    }
    else if (pin == SW_DATA_SOURCE_FRAMES_RUN_MSW)
    {
        extern uint32_t FramesRun;
        return (FramesRun>>16);
    }
    else if (pin == SW_DATA_SOURCE_OVERRUN_FRAMES)
    {
     extern uint16_t OverflowFrames;
     return (OverflowFrames);
    }
    else if (pin == SW_DATA_SOURCE_TEMPERATURE)
    {
        uint16_t result = (uint16_t) GetTemperature_degC100ths(true);
        return (result);    
    }
     else if (pin == 71)
    {
         extern uint16_t PacketsProcessed;
        return (PacketsProcessed );    
    }
     else if (pin == SW_DATA_SOURCE_ERRORS)
     {
         extern uint16_t Errors;
         return(Errors);
     }
     else if (pin == SW_DATA_SOURCE_FRAMES_DROPPED)
     {
         extern volatile uint16_t FramesDropped;
         return (FramesDropped);
     }
     else if (pin == SW_DATA_SOURCE_SYSTEM_UTILIZATION)
     {
         extern uint16_t SystemUtilizationAverage;
         return (SystemUtilizationAverage);
     }
     else if (pin == SW_DATA_SOURCE_VCC_mVOLTS)
     {
           
                
            return (GetSourceVoltage_mV()); 
     }
     else if (pin == SW_DATA_SOURCE_VBG_COUNTS_VS_VREF)
     {  
         return(GetVBgCountsVsVRefPin());
     }
     else if (pin >= SW_DATA_SOURCE_PIN_0_MV &&pin <= SW_DATA_SOURCE_PIN_19_MV )
     {
         uint32_t result = PinUpdateRegisters[pin - SW_DATA_SOURCE_PIN_0_MV].generic.buffer;
         result *= GetSourceVoltage_mV();
         result >>= 16;
         return ((uint16_t)result);
         
     }
    
     else if (pin == SW_DATA_SOURCE_RESET_REGISTER)
     {
         uint16_t rcon = RCON;
         RCON = 0;
         return(rcon);
     }
    
     else if (pin ==  SW_DATA_SOURCE_2HZ_SQUARE )
     {  extern uint32_t FramesRun;
         return ( (FramesRun & 0x100)? 0xFFFF:0);
     }
     else if (pin ==  SW_DATA_SOURCE_1HZ_SQUARE )
     {  extern uint32_t FramesRun;
         return ( (FramesRun & 0x200)? 0xFFFF:0);
     }
     else if (pin ==  SW_DATA_SOURCE_2SEC_SQUARE )
     {  extern uint32_t FramesRun;
         return ( (FramesRun & 0x400)? 0xFFFF:0);
     }
     else if (pin ==  SW_DATA_SOURCE_8SEC_SQUARE )
     {  extern uint32_t FramesRun;
         return ( (FramesRun & 0x1000)? 0xFFFF:0);
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

