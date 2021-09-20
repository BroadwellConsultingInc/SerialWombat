#include "SerialWombat.h"
#include <stdint.h>

typedef struct servo_n{
	uint16_t fixedPeriod;
	uint16_t variablePeriod;
	uint16_t inactivePeriod;
	uint8_t commandPin;
	uint8_t reverse;
	uint8_t invertPolarity; 
}servoPin_t;


void init_servo (void)
{
	servoPin_t* servo = (servoPin_t*) CurrentPinRegister;
	switch(Rxbuffer[0])
	{
        case CONFIGURE_CHANNEL_MODE_0:
        {
                servo->fixedPeriod = (uint16_t) (.0005 * DMA_FREQUENCY); 	//500us
                servo->variablePeriod =(uint16_t)(.002 * DMA_FREQUENCY);	//2000us
                servo->inactivePeriod = (uint16_t)(.018 * DMA_FREQUENCY);	//18 ms between pulses
		servo->commandPin = Rxbuffer[3]; // TODO error check
		servo->reverse = Rxbuffer[4] > 0;

		servo->invertPolarity= Rxbuffer[5] > 0;  
		CurrentPinRegister->generic.buffer = RXBUFFER16(6);
		{
	            SetPin(CurrentPin,DIGITAL_LOW); // Make output
		}
		CurrentPinRegister->pulse_output.lastDMA = 0;
		CurrentPinRegister->pulse_output.lowRemaining = 0;
		CurrentPinRegister->pulse_output.highRemaining = 0;
		CurrentPinRegister->generic.mode = PIN_MODE_SERVO;
	}
	break;
	case CONFIGURE_CHANNEL_MODE_1:
        {
            //TODO:  convert to microseconds
                servo->fixedPeriod =RXBUFFER16(3); 	
                servo->variablePeriod =RXBUFFER16(5);
        }        
	break;
	case CONFIGURE_CHANNEL_MODE_2:
        {
            //TODO:  Convert to microseconds
                servo->inactivePeriod =RXBUFFER16(3); 	
        }        
	break;

  }
}

void update_servo()
{ 
	uint32_t temp32;
	uint16_t position;
	servoPin_t* servo = (servoPin_t*) CurrentPinRegister;
	
	if (servo->commandPin !=CurrentPin)
	{
		CurrentPinRegister->generic.buffer = GetBuffer(servo->commandPin);
	}

	if (servo->reverse)
	{
		position = 0xFFFF - CurrentPinRegister->generic.buffer;
	}
	else
	{
		position = CurrentPinRegister->generic.buffer;
	}

	temp32 = ((uint32_t)position) * servo->variablePeriod;
	temp32 += ((uint32_t)servo->fixedPeriod) << 16;
	


	if (servo->invertPolarity)
	{	     
		CurrentPinRegister->pulse_output.lowReload = temp32 >>16;
		CurrentPinRegister->pulse_output.highReload = servo->inactivePeriod;
	}
	else
	{
		CurrentPinRegister->pulse_output.highReload = temp32 >>16;
		CurrentPinRegister->pulse_output.lowReload = servo->inactivePeriod;
		
	}
	updatePulse(CurrentPin);

}

