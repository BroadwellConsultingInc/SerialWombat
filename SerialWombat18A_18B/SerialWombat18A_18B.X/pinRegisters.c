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

int16_t debug_Temperature = 0; //TODO

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
        return (0x5000); //TODO fix FVR conversion
    }
    
    else if (pin == 67)
    {
     //TODO   extern uint32_t FramesRun;
     //TODO   return ((uint16_t)FramesRun);
    }
    else if (pin == 68)
    {
      //TODO  extern uint32_t FramesRun;
      //TODO  return (FramesRun>>16);
    }
    else if (pin == 69)
    {
     //TODO   extern uint16_t OverflowCount;
     //TODO   return (OverflowCount);
    }
    else if (pin == 70)
    {
        
        AD1CON1 = 0;
        AD1CON2 = 0;
        AD1CON3 = 0;
        AD1CON4 = 0;
        AD1CON5 = 0; 
        
        CTMUCON1L = 0x8003;  //CTMU ON, 55uA
        AD1CON5bits.CTMREQ = 1;
        AD1CHS = 14; // Die Temperature Conversion
        AD1CON3 = 0x1FFF; // Sample time = 15Tad, Tad = Tcy
        AD1CON1bits.MODE12 = 1;  // Turn on 12 bit
        AD1CON1bits.FORM = 2; // Left Justified
        AD1CON1bits.SSRC = 7;  // Auto Convert
        AD1CON1bits.ADON = 1; // Turn on A/D
        AD1CON1bits.SAMP = 1; //Start conversion.
        while(AD1CON1bits.DONE == 0);
        CTMUCON1L = 0 ;  //CTMU OFF
        int32_t result = ADC1BUF0;      
        result *= 3300; //TODO base on FVR instead of fixed value
        result = ((int32_t)760 * 65536) - result;
        result /= ((int32_t)(.0155 * 65535));
        ADC1_Initialize();  // Put things back where we found them.
         debug_Temperature = GetTemperature_degC100ths();
       
        return ( (uint16_t) result);    
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

