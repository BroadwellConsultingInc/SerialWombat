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

#include "serialWombat.h"
#include <stdint.h>

typedef struct quadEnc_n{
           uint8_t secondPin; 
           uint8_t debounceFrames;
           uint8_t debounceCount;
           uint8_t readState;
           uint8_t tempPrimaryPinState:1;
           uint8_t tempSecondPinState:1;
           uint8_t updateCounter:1;
           uint8_t lastState:1;
           uint8_t ignoreRemaining:1;
           uint8_t debugSamplesProcessed;
           
}quadEnc_t;

#define quadEnc  ((quadEnc_t*) CurrentPinRegister)

void init_quadEnc(void)
{
    
    switch(Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:

        {
           
            
         CurrentPinRegister->generic.mode =PIN_MODE_QUADRATURE_ENC;
        CurrentPinRegister->generic.buffer = 0; 
        quadEnc->debounceFrames = Rxbuffer[3]; 
        quadEnc->debounceCount = 0;
        quadEnc->secondPin = Rxbuffer[5] ;
        SetMode(quadEnc->secondPin, PIN_MODE_CONTROLLED);
        SetPin(quadEnc->secondPin, DIGITAL_INPUT);

        quadEnc->readState = Rxbuffer[6];
        CurrentPinInput();
        switch (Rxbuffer[7]) 
	{
        case 0:
        {
            CurrentPinNoPullUp();
            PinNoPullUp(quadEnc->secondPin);
        }
        break;
        
        case 1:
        {			
                    CurrentPinPullUp();
                    PinPullUp(quadEnc->secondPin);	
        }
        break;
        
       
            
	}    
        
           WP_IOCP |= CurrentPinMask;
           WP_IOCN |= CurrentPinMask; 
        

        PIE0bits.IOCIE = 1;
	
        
        }
        
    
    break;
    /*
    case CONFIGURE_CHANNEL_MODE_1:
        {
            Txbuffer[3] = quadEnc->debugSamplesProcessed;
            Txbuffer[4] = quadEnc->lastState;
            Txbuffer[5] = quadEnc->tempPrimaryPinState;
            Txbuffer[6] = quadEnc->tempSecondPinState;
            Txbuffer[7] = quadEnc->updateCounter;
        }
    break;
    */
    }
} 

extern uint8_t copy_IOC_PortBuffer[IOC_BUFFER_SIZE];
void update_quadEnc(void)
{

    
    if (quadEnc->debounceCount != 0)
    {
        --quadEnc->debounceCount;
        quadEnc->lastState = CurrentPinRead();
                    //EUSART1_Write('M');
        return;
    }
    quadEnc->ignoreRemaining = 0;
    for (uint8_t i = 0; i < IOC_BUFFER_SIZE; ++i)
    {
        uint8_t currentInput;
        if (quadEnc->readState < 4)
        {
        currentInput = copy_IOC_PortBuffer[i];
        if (currentInput & 0x80u)
        {
            //Not set.
            continue;
        }
                ++quadEnc->debugSamplesProcessed;
         //EUSART1_Write(i);
         //EUSART1_Write(currentInput);
      
         quadEnc->tempPrimaryPinState = ((currentInput & CurrentPinMask) != 0);
         quadEnc->tempSecondPinState = ((currentInput & PinMaskArray[quadEnc->secondPin]) != 0);
        }
        else
        {
            quadEnc->tempPrimaryPinState = CurrentPinRead();
            quadEnc->tempSecondPinState = ReadPin(quadEnc->secondPin);
            i = IOC_BUFFER_SIZE; // Only run this loop once.
        }
        
      if (quadEnc->lastState == quadEnc->tempPrimaryPinState )
        {
            //EUSART1_Write('A');
            continue;
        }
   
        quadEnc->lastState = quadEnc->tempPrimaryPinState;
        
        if (quadEnc->ignoreRemaining)
        {
            //EUSART1_Write('B');
            continue;
        }
       
        quadEnc->updateCounter = 0;
            //EUSART1_Write('C');
        if ((quadEnc->readState & 0x03)  == 0)
        {
                        //EUSART1_Write('D');
            if (!quadEnc->tempPrimaryPinState)
            {
                            //EUSART1_Write('E');
                quadEnc->updateCounter = 1;
            }
           
        }
        else if ((quadEnc->readState & 0x03) == 1 )
        {
                        //EUSART1_Write('F');
            if (quadEnc->tempPrimaryPinState)
            {
                            //EUSART1_Write('G');
                 quadEnc->updateCounter = 1;
            }
          
        }
        else if ((quadEnc->readState & 0x03) == 2)
        {
                        //EUSART1_Write('H');
            quadEnc->updateCounter = 1;
           
        }
        
        if (quadEnc->updateCounter)
        {
                        //EUSART1_Write('I');
            if (quadEnc->tempPrimaryPinState == quadEnc->tempSecondPinState)
            {
                            //EUSART1_Write('J');
                ++CurrentPinRegister->generic.buffer;
            }
            else
            {
                            //EUSART1_Write('K');
                --CurrentPinRegister->generic.buffer;
            }
            quadEnc->debounceCount = quadEnc->debounceFrames; 
            if (quadEnc->debounceFrames > 0)
            {
                            //EUSART1_Write('L');
                quadEnc->ignoreRemaining = 1;
                // Don't process any more transitions.  They're bounces...
             
            }
        }     
                   
    }
    quadEnc->lastState = CurrentPinRead();
     
}
