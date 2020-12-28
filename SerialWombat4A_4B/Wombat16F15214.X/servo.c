#include <stdint.h>
#include "serialWombat.h"


typedef struct servo_n{
	uint16_t fixedPeriod;
	uint16_t variablePeriod;
	uint8_t inactiveCount;
	uint8_t commandPin;
	uint8_t reverse;
	uint8_t invertPolarity; 
}servoPin_t;
#define  servo ((servoPin_t*) CurrentPinRegister)
void initServoSimple()
{
    
    CurrentPinRegister->generic.mode = PIN_MODE_SERVO;
    servo->commandPin = CurrentPin;
    CurrentPinRegister->generic.buffer = 0;
    servo->fixedPeriod = 500 ;
    servo->variablePeriod = 2000 ;
    servo->reverse = 0;
    servo->invertPolarity = 0;
    CurrentPinLow();
        
        TMR1_StartTimer();
}
void initServo (void)
{

	switch(Rxbuffer[0])
	{
        case CONFIGURE_CHANNEL_MODE_0:
        {
            initServoSimple();
            servo->commandPin = Rxbuffer[3];
            CurrentPinRegister->generic.buffer = RXBUFFER16(4);
            servo->reverse = Rxbuffer[6];
	}
	break;
	case CONFIGURE_CHANNEL_MODE_1:
        {
           
                servo->fixedPeriod =RXBUFFER16(3) ; 	
                servo->variablePeriod =RXBUFFER16(5) ;
        }        
	break;
	

  }
}


void updateServo()
{   
    if (  servo->inactiveCount  >= 20 && CCP1SetLowMask == 0xFF)
    {
        
         CCP1CON = 0x80;
         
            uint32_t period =  (uint32_t) CurrentPinRegister->generic.buffer;
            if (servo->reverse)
            {
                period = 65535 - period;
            }
            period *=   servo->variablePeriod;
            uint16_t period16;
    period16 = period >> 16;
    period16 += servo->fixedPeriod;
     
    period16 += TMR1_ReadTimer();
    CurrentPinHigh();
    CCPR1L = (uint8_t)period16;
    CCPR1H = (uint8_t)(period16 >>8);
     PIR1bits.CCP1IF = 0;
    CCP1CON = 0x82;
    SetLowMaskCurrentPin();
     PIR1bits.CCP1IF = 0;
     PIE1bits.CCP1IE = 1;
        servo->inactiveCount = 0;
    }
   
    
         servo->inactiveCount++;
    
    
 
}

