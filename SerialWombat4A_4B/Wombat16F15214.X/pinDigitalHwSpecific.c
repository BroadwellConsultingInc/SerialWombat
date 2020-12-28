#include "serialWombat.h"

uint8_t const PinMaskArray[4] = {   
	1<<WP0_PORTPINNUM,
	1<<WP1_PORTPINNUM,
	1<<WP2_PORTPINNUM,
	1<<WP3_PORTPINNUM
};
uint8_t const PinToPort[4] = {WP0_PORTPINNUM,WP1_PORTPINNUM,WP2_PORTPINNUM,WP3_PORTPINNUM};

volatile uint8_t CCP1SetLowMask = 0xFF;
void CurrentPinInput(){
    WP_TRIS |= CurrentPinMask;
}
void CurrentPinOutput(){
    WP_TRIS &= CurrentPinMaskInverted;
}
void CurrentPinHigh()
{
    WP_LAT |= CurrentPinMask;
 CurrentPinOutput();
}
void CurrentPinLow(){
    WP_LAT &= CurrentPinMaskInverted;
    CurrentPinOutput();
}
void SetPin(uint8_t pin, uint8_t pinState)
{
    uint8_t temp = CurrentPin;
    CurrentPin = pin;
    CurrentPinMask = PinMaskArray[CurrentPin];
	CurrentPinMaskInverted = ~CurrentPinMask;
    SetCurrentPin(pinState);
    CurrentPin = temp;
    CurrentPinMask = PinMaskArray[CurrentPin];
	CurrentPinMaskInverted = ~CurrentPinMask;
}

void SetCurrentPin( uint8_t pinState){
    switch(pinState)
    {
        case 0:
        CurrentPinLow();
        break;
        
        case 1:
            CurrentPinHigh();
            break;
            
            case 2:
            CurrentPinInput();
            break;
    }
    
}

void SetLowMaskCurrentPin()
{
    
            CCP1SetLowMask = CurrentPinMaskInverted;

        
    
}

bool CurrentPinRead()
{
    return ((WP_PORT & CurrentPinMask) > 0);
}

bool ReadPin(uint8_t pin)
{
    return  ((WP_PORT & PinMaskArray[pin]) > 0);
}

void CurrentPinAnalog()
{
    CurrentPinInput();
    WP_ANSEL |= CurrentPinMask;
}


void CurrentPinPullUp()
{
    WP_WPU |= CurrentPinMask;
}

void CurrentPinNoPullUp()
{
    WP_WPU &= CurrentPinMaskInverted;
}

void PinPullUp(uint8_t pin)
{
    WP_WPU |= PinMaskArray[pin];
}

void PinNoPullUp(uint8_t pin)
{
    WP_WPU &= ~PinMaskArray[pin];
}

void CurrentPinNotAnalog()
{
    WP_ANSEL &=  CurrentPinMaskInverted;
}

void CurrentPinOpenDrain()
{
    WP_ODCON |= CurrentPinMask;
}

void CurrentPinNotOpenDrain()
{
    WP_ODCON &= CurrentPinMaskInverted;
}