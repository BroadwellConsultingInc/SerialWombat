/*
Copyright 2021-2023 Broadwell Consulting Inc.

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
               uint16_t debouncesamples;
               uint16_t debouncecounter;
               uint16_t max;
               uint16_t min;
           uint16_t increment;
           uint8_t lastNextDMA;
           uint16_t currentState:1;
           uint16_t interruptDriven:1;
           uint8_t secondPin; 
           uint8_t readState;
}quadEnc_t;



void initQuadEnc(void)
{
    quadEnc_t* quadEnc = (quadEnc_t*) CurrentPinRegister;
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_QUADRATURE_ENC)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    switch(Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:

        {
            
            
	if (pinPort[Rxbuffer[5]] != CurrentPinPort())
	{
		//Pins must be on same port
		CurrentPinRegister->generic.mode = PIN_MODE_CONTROLLED;
		error(SW_ERROR_PINS_MUST_BE_ON_SAME_PORT);
		return;
	}
         CurrentPinRegister->generic.mode =PIN_MODE_QUADRATURE_ENC;
        SetMode(quadEnc->secondPin, PIN_MODE_CONTROLLED);
        CurrentPinRegister->generic.buffer = 0; 
        quadEnc->debouncesamples = RXBUFFER16(3) ; 
        quadEnc->debouncecounter = 0;
        quadEnc->secondPin = Rxbuffer[5] ;
        quadEnc->readState = Rxbuffer[6] & 0x03;
        quadEnc->interruptDriven = Rxbuffer[6] < 4;
	CurrentPinInput();
	PinInput(quadEnc->secondPin);
        
        if (quadEnc->interruptDriven)
        {
             quadEnc->debouncesamples *= (DMA_FREQUENCY / 1000);
        }
	switch (Rxbuffer[7]) 
	{
        case 0:
        {
            
            		switch(CurrentPinPort())
		{
			case 0:  // Port A
				{
                    IOCPDA &=~CurrentPinBitmap();
					IOCPDA &= ~pinBitmap[quadEnc->secondPin];
					IOCPUA &=~CurrentPinBitmap();
					IOCPUA &= ~pinBitmap[quadEnc->secondPin];
                    
				}
				break;

			case 1:  // PORT B
				{
                    IOCPDB &=~CurrentPinBitmap();
					IOCPDB &= ~pinBitmap[quadEnc->secondPin];
                    IOCPUB &=~CurrentPinBitmap();
					IOCPUB &= ~pinBitmap[quadEnc->secondPin];
				}
				break;

        }
        }
        break;
        
        case 1:
        {
		switch(CurrentPinPort())
		{
			case 0:  // Port A
				{
                    IOCPDA &=~CurrentPinBitmap();
					IOCPDA &= ~pinBitmap[quadEnc->secondPin];
					IOCPUA |= CurrentPinBitmap();
					IOCPUA |= pinBitmap[quadEnc->secondPin];
                    
				}
				break;

			case 1:  // PORT B
				{
                    IOCPDB &=~CurrentPinBitmap();
					IOCPDB &= ~pinBitmap[quadEnc->secondPin];
					IOCPUB |= CurrentPinBitmap();
					IOCPUB |= pinBitmap[quadEnc->secondPin];

				}
				break;
		}
        }
        break;
        
        case 2:
        {
            switch(CurrentPinPort())
		{
			case 0:  // Port A
				{
                    IOCPUA &=~CurrentPinBitmap();
					IOCPUA &= ~pinBitmap[quadEnc->secondPin];
					IOCPDA |= CurrentPinBitmap();
					IOCPDA |= pinBitmap[quadEnc->secondPin];   
				}
				break;

			case 1:  // PORT B
				{
                    IOCPUB &=~CurrentPinBitmap();
					IOCPUB &= ~pinBitmap[quadEnc->secondPin];
					IOCPDB |= CurrentPinBitmap();
					IOCPDB |= pinBitmap[quadEnc->secondPin];
				}
				break;
		}
        }
        break;
            
	}        

        quadEnc->min = 65535;
        quadEnc->max = 0;
        uint16_t sample;
        uint16_t bitmap = CurrentPinBitmap();
        
        if (quadEnc->interruptDriven){
        while(PulseInGetOldestDMASample(CurrentPin,&sample))
        {
            quadEnc->currentState = (sample & bitmap) > 0;
        }
        }
        else
        {
            quadEnc->currentState = CurrentPinRead();
        }
        
        quadEnc->increment = 1;
        
        
        }
    break;
        case CONFIGURE_CHANNEL_MODE_1:
    {
        quadEnc->increment = RXBUFFER16(3); 

    }
    break;
        case CONFIGURE_CHANNEL_MODE_2:
    {
        quadEnc->min = RXBUFFER16(3); 
        quadEnc->max = RXBUFFER16(5); 
        if (CurrentPinRegister->generic.buffer < quadEnc->min)
	{
		CurrentPinRegister->generic.buffer = quadEnc->min;
	}
        if (CurrentPinRegister->generic.buffer > quadEnc->max)
	{
		CurrentPinRegister->generic.buffer = quadEnc->max;
	}
	CurrentPinRegister->generic.mode = PIN_MODE_QUADRATURE_ENC;

    }
    break;
    
     default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
    }
} 

quadEnc_t* debugQuadEnc;
void updateQuadEnc(void)
{
    
	quadEnc_t* quadEnc = (quadEnc_t*) CurrentPinRegister;
    debugQuadEnc = quadEnc;
	uint16_t bitmap = CurrentPinBitmap();
	uint16_t buffer = CurrentPinRegister->generic.buffer;
	uint16_t sample = 0;
    uint16_t secondBitmap = pinBitmap[quadEnc->secondPin];
    uint8_t inputSample0;
    uint8_t inputSample1;
    bool currentState = quadEnc->currentState;
    
    bool processSamples = true;
    
    if (quadEnc->interruptDriven)
        {
           processSamples =  PulseInGetOldestDMASample(CurrentPin,&sample);
           inputSample0 = (sample & bitmap) > 0;
         inputSample1 = (sample & secondBitmap ) > 0;
       }
    else
    {
        inputSample0 = CurrentPinRead();
        inputSample1 = ReadPin(quadEnc->secondPin);
    }
    while (processSamples )
    {
        
        
       
        


			//Process data
			if (inputSample0)
			{
				//Input High
				if (!currentState)
				{
					//Was low!
					++ quadEnc->debouncecounter;
                  
					if (quadEnc->debouncecounter >= quadEnc->debouncesamples)
					{    

						currentState = 1;

						if (1 == quadEnc->readState || 2 == quadEnc->readState)
						{
							if (inputSample1)
							{
								int32_t sum;
								sum = buffer + quadEnc->increment;


								if (quadEnc->max > 0 && sum > quadEnc->max )
								{
									sum = quadEnc->max ;
								}
								buffer = (uint16_t) sum;
							}
							else
							{
								int32_t sum;
								sum = buffer - quadEnc->increment;

								if (quadEnc->min != 65535 && sum < quadEnc->min )
								{
									sum = quadEnc->min ;
								}
								buffer = (uint16_t) sum;

							}
						}
                        quadEnc->debouncecounter = 0;
					}

				}
				else
				{
					quadEnc->debouncecounter = 0;
					// Stayed the same.  Do nothing

				}

			}
			else
			{

				//Input Low
				if (currentState)
				{
                    //Was High
					++ quadEnc->debouncecounter;
  					if (quadEnc->debouncecounter > quadEnc->debouncesamples)
					{    
						
						currentState = 0;

						if (0 == quadEnc->readState || 2 == quadEnc->readState)
						{
							if (inputSample1)
							{
								int32_t sum;
								sum = buffer - quadEnc->increment;

								if (quadEnc->max > 0 && sum > quadEnc->max )
								{
									sum = quadEnc->max ;
								}
								buffer = (uint16_t) sum;
							}
							else
							{
								int32_t sum;
								sum = buffer + quadEnc->increment;

								if (quadEnc->min != 65535 && sum < quadEnc->min )
								{
									sum = quadEnc->min ;
								}
								buffer = (uint16_t) sum;

							}
						}
                        quadEnc->debouncecounter = 0;
					}
				}
				else
				{
					quadEnc->debouncecounter = 0;
					// Stayed the same.  Do nothing
				}
			}
             if (quadEnc->interruptDriven)
        {
           processSamples =  PulseInGetOldestDMASample(CurrentPin,&sample);
           inputSample0 = (sample & bitmap) > 0;
         inputSample1 = (sample & secondBitmap ) > 0;
       }
    else
    {
                 processSamples = false;
    }
		}
	
	quadEnc->currentState = currentState;
	CurrentPinRegister->generic.buffer = buffer;
}
