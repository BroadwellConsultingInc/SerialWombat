#include "serialWombat.h"
#include <stdint.h>

typedef struct pulseTimer_n{
	uint8_t invert:1;
}pwm_t;

void updatePWM(void);

#define pwm  ((pwm_t*) CurrentPinRegister)
void initPWM (void)
{
	
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
		{
            CurrentPinRegister->generic.mode = PIN_MODE_PWM;
			CurrentPinRegister->generic.buffer = RXBUFFER16(4);
            pwm->invert = Rxbuffer[6];
          
            switch (CurrentPin)
            {
                case 0:
#ifdef UARTWOMBAT
                    WP0_PPS = 1; // CCP1CON
                    CCP1CON= 0x9F; // PWM on                
#endif
                    break;
                case 1:
                    WP1_PPS = 2; // CCP2CON
                    CCP2CON= 0x9F; // PWM on
                    break;
                    
                    case 2:
                    WP2_PPS = 3; // PWM 3
                    PWM3CON= 0x80; // PWM on    
                    break;
                    
                    case 3:
                    WP3_PPS = 4; // PWM4
                    PWM4CON= 0x80; // PWM on
                    break;
            }
            updatePWM();
            	CurrentPinOutput();
                
			
		}
		break;
        
        case CONFIGURE_CHANNEL_MODE_DISABLE:
        {
            switch (CurrentPin)
            {
                case 0:
                {
#ifdef UARTWOMBAT
                    WP0_PPS = 0;
                    CCP1CON = 0;
#endif
                }
                break;
                
                case 1:
                {
                    WP1_PPS = 0;
                    CCP2CON = 0;
                }
                break;
                
                 case 2:
                {
                    WP2_PPS = 0;
                    PWM3CON = 0;
                }
                break;
                
                case 3:
                {
                    WP3_PPS = 0;
                    PWM4CON = 0;
                }
                break;
            }
                
         
            
         
            
        }
   break;
        case 	CONFIGURE_CHANNEL_MODE_HW_0:
        {
            
            T2CON = (Rxbuffer[3] & 0x70) | 0x80;
            T2CLKCON = (Rxbuffer[3] & 0x07);
        }
        break;

	}
}

void initPWMSimple()
{
    Rxbuffer[0] = CONFIGURE_CHANNEL_MODE_0;
    Rxbuffer[4] = 0;
    Rxbuffer[5] = 0;
    initPWM();
}

void updatePWM(void)
{
    uint16_t outputValue;
    if (pwm->invert)
            {
                outputValue = 65535 - CurrentPinRegister->generic.buffer;
            }
            else
            {
                outputValue = CurrentPinRegister->generic.buffer;
            }

switch (CurrentPin)
            {
                case 0:
                    CCPR1 = outputValue;                  
                    break;
                case 1:
                    CCPR2 = outputValue;     
                    break;
                    
                    case 2:
                                        PWM3DC =outputValue;     
                    break;
                    
                    case 3:
                                        PWM4DC = outputValue;     

                    break;
            }
}


