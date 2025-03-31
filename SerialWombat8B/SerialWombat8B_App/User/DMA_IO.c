/*
Copyright 2024 Broadwell Consulting Inc.

Serial Wombat is a registered trademark of Broadwell Consulting Inc.
in the United States 

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
#include <stdbool.h>
#include <string.h>
#include "serialWombat.h"
#include "deviceSpecific.h"
#include "debug.h"
 uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY];  // High bytes are Set bits, low bytes are clear bits


//void or128(uint16_t* array, uint16_t value);
//void and128(uint16_t* array, uint16_t value);

 volatile uint8_t DMACNT0 = SIZE_OF_DMA_ARRAY ; // Simulates the constantly running DMA counter on the PIC24, used to indicate the next byte to be sent out .  Decrement each time we move data, roll over from 1 to 128
#define DMACNT2 DMACNT0  // Simulates the constantly running DMA counter on the PIC24, used to indicate the next location that will be written by reading the port
 uint32_t dmaInterrupts = 0;
 volatile uint8_t InputArrayA[SIZE_OF_DMA_ARRAY];


  void orCount(uint8_t buffer, uint16_t bitmap, uint16_t count)
 {
     int i;
     uint16_t b = bitmap << 8;
     uint16_t bi = ~bitmap;

     for (i = 0; i < count; ++i)
     {
         OutputArrayA[i+ buffer] |= b;
         OutputArrayA[i+ buffer] &= bi;
     }
 }
 void andCount(uint8_t buffer, uint16_t bitmap, uint16_t count)
 {
     int i;
          uint16_t b = (bitmap << 8) | 0xFF;
          uint16_t bi = ~bitmap;
          for (i = 0; i < count; ++i)
          {
              OutputArrayA[i+ buffer] &= b;
              OutputArrayA[i+ buffer] |= bi;
          }
 }
// PWM Failure test:
 // 0xC8 0x07 0x10 0x07 0 0 0 0x55
 // 0xDC 0x07 0x10 0x34 0x21 0 0 0x55
 // 0x82 0x07 0x4A 0xF6 0xFF 0x55 0x55 0x55

 void deactivateOutputDMA(uint8_t pin)
 {
     int i;
     uint16_t b = ~pinBitmap[pin] & 0xFF;
     b |= ((uint16_t)(~pinBitmap[pin])) << 8;
     for (i = 0; i < SIZE_OF_DMA_ARRAY; ++i){
      OutputArrayA[i] &= b;
     }
 }
 void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

 volatile uint16_t FramesDropped = 0;
 volatile uint32_t System1msCount = 0;

uint8_t highCount = 0;
uint8_t lastValue = 0;
 void SysTick_Handler(void)
 {

        uint8_t currentEntry = SIZE_OF_DMA_ARRAY-DMACNT0;
        volatile uint8_t* writeAddress =&InputArrayA[currentEntry];
        *writeAddress = (uint8_t)GPIOD->INDR;
        GPIOD->BSHR = (uint16_t)(OutputArrayA[currentEntry] >>8);
               GPIOD->BCR = (uint16_t)(OutputArrayA[currentEntry] & 0xFF );

               -- DMACNT0;
               if (DMACNT0 == 0)
               {
                   DMACNT0 = SIZE_OF_DMA_ARRAY;
               }
               ++ dmaInterrupts;


     SysTick->SR = 0;
 }






#define PIN_QUICK_SET_DMA_COUNTS 15  //How many DMA counts into the future to set the current state.   This has to last until the pin gets set again. 


const uint16_t pinBitmap[NUMBER_OF_PHYSICAL_PINS] =
{
	0x02 , // 0 PD1
	0x04 , // 1 PD2
	0x08 , // 2 PD3
	0x10 , // 3 PD4
	0x20 , // 4 PD5
	0x40 , // 5 PD6
	0x80 , // 6 PD7
        0x01 , // 7 PD0
};


const uint32_t pin_CFGLR_Mode_Bitmap[NUMBER_OF_PHYSICAL_PINS] =
{
        0x3 << (1 * 4),
        0x3 << (2 * 4),
        0x3 << (3 * 4),
        0x3 << (4 * 4),
        0x3 << (5 * 4),
        0x3 << (6 * 4),
        0x3 << (7 * 4),
        0x3  // << (0 * 4),
};

bool pinIsHWOutput(uint8_t pin)
 {
     return ((GPIOD->CFGLR & pin_CFGLR_Mode_Bitmap[pin]) != 0);
 }




uint16_t CurrentPinBitmap(void)
{
	if (CurrentPin >= NUMBER_OF_PHYSICAL_PINS)
	{

		return (0);
	}
	return (pinBitmap[CurrentPin]);

}
bool PinIsAnalogCapable(uint8_t pin);
void ConfigurePinAnalog(uint8_t pin, bool makeAnalog)
{
    //TODO update for pin remapping for non analog pins merged with others
	PinInput(pin);
	 GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.GPIO_Pin = pinBitmap[pin];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

bool PinIsAnalogCapable(uint8_t pin)
{
	return true;
	/*
	switch (pin)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 17:
		case 18:
		case 19:
		case 20:
			return true;

	}

	return false;
	*/
}




bool ReadPin(uint8_t pin)
{
	return ((GPIOD->INDR & pinBitmap[pin]) > 0);
}
void PinOutput(uint8_t pin)
{
    if (pin == 0)
    {
       AFIO->PCFR1 |= AFIO_PCFR1_SWJ_CFG_2;   // Disable debug
    }
	GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = pinBitmap[pin];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void PinInput(uint8_t pin)
{
    if (pin == 0)
       {
          AFIO->PCFR1 |= AFIO_PCFR1_SWJ_CFG_2;   // Disable debug
       }
	GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = pinBitmap[pin];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

}

bool CurrentPinRead()
{
	return(ReadPin(CurrentPin));
}

#ifdef NOTDMAONLY
uint8_t pinIsPPSCapable(uint8_t pin)
{
	return false;
	
}
#endif


void SetPin(uint8_t pin, uint8_t pinState)
{
	if (pinState == DIGITAL_INPUT)
	{
		PinInput(pin);
	}
	else if (pinState == DIGITAL_LOW)
	{
		PinLow(pin);
	}
	else if (pinState == DIGITAL_HIGH)
	{
		PinHigh(pin);
	}
}

void CurrentPinInput()
{
    PinInput(CurrentPin);
}

void CurrentPinAnalog()
{
	ConfigurePinAnalog(CurrentPin,true);
}


void SetPinQuick(uint8_t pin, uint8_t pinState)
{
    SetPin(pin,pinState);
    
}

void SetCurrentPin(uint8_t pinState)
{
    SetPin(CurrentPin,pinState);
}
void PinLow(uint8_t pin)
{
	GPIOD->BCR = pinBitmap[pin];
	PinOutput(pin);
    GPIOD->BCR = pinBitmap[pin];
}

void PinHigh(uint8_t pin)
{
	GPIOD->BSHR = pinBitmap[pin];
	PinOutput(pin);
	GPIOD->BSHR = pinBitmap[pin];
}


void SetPinPullUp(uint8_t pin, bool isPulledUp)
{
    if(pinIsHWOutput(pin))
    {
        // Don't mess with pull ups on pins configured to output
        return;
    }
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    if (isPulledUp)
       {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
       }
    else {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    }
        GPIO_InitStructure.GPIO_Pin = pinBitmap[pin];

        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        if (isPulledUp)
        {
        GPIOD->BSHR = pinBitmap[pin];
        }
}

void SetPinPullDown(uint8_t pin, bool isPulledDown)
{
    if(pinIsHWOutput(pin))
    {
        // Don't mess with pull downs on pins configured to output
        return;
    }
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    if (isPulledDown)
       {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
       }
    else {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    }
        GPIO_InitStructure.GPIO_Pin = pinBitmap[pin];

        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void SetPinOpenDrain(uint8_t pin, bool isOpenDrain)
{
    if (!pinIsHWOutput(pin))
    {
        return;
    }
    GPIO_InitTypeDef GPIO_InitStructure = {0};
       if (isOpenDrain)
          {
           GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
          }
       else {
           GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

       }
           GPIO_InitStructure.GPIO_Pin = pinBitmap[pin];

           GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
           GPIO_Init(GPIOD, &GPIO_InitStructure);

}
void PinPullUp(uint8_t pin)
{
    SetPinPullDown(pin,false);
    SetPinPullUp(pin,true);
}
void PinNoPullUp(uint8_t pin)
{
    SetPinPullUp(pin,false);
}
void PinPullDown(uint8_t pin)
{
    SetPinPullUp(pin,false);
    SetPinPullDown(pin,true);    
}



void PinNoPullDown(uint8_t pin)
{
    SetPinPullDown(pin,false);
}

void PinOD(uint8_t pin)
{
    SetPinOpenDrain(pin,true);
}

void PinNoOD(uint8_t pin)
{
    SetPinOpenDrain(pin,false);
}


void CurrentPinHigh()
{
    PinHigh(CurrentPin);
}

void InitializePinLow(uint8_t pin)
{
    deactivateOutputDMA(pin);
	PinLow(pin);
}

void InitializePinHigh(uint8_t pin)
{
    deactivateOutputDMA(pin);
    PinHigh(pin);
}

void InitializePinInput(uint8_t pin)
{
    deactivateOutputDMA(pin);
    PinInput(pin);
}

void CurrentPinLow()
{
    PinLow(CurrentPin);
}
void CurrentPinPullUp()
{
    PinPullUp(CurrentPin);
}

void CurrentPinNoPullUp()
{
    SetPinPullUp(CurrentPin,false);

}

void CurrentPinPullDown()
{
    PinPullDown(CurrentPin);
}

void CurrentPinNoPullDown()
{
        SetPinPullDown(CurrentPin,false);
}

const uint8_t WombatPinToADCChannel[NUMBER_OF_PHYSICAL_PINS] =
{
    0, 
    1,
    2,
    3,
    4,
    5,
    6,
    7,
};


void updatePulseOutput(uint8_t pin, pulse_output_t* pulse)
{
    bool recycle = true;
    while (recycle)
    {
        recycle = false;
    if (pulse->highRemaining > 0)
    {
        pulse->highRemaining = updateBitStreamOutput(pin, 1, pulse->highRemaining,&pulse->bitStream);
        pulse->lowRemaining = pulse->lowReload;
    }
    if (pulse->highRemaining == 0)
    {
        pulse->lowRemaining = updateBitStreamOutput(pin, 0, pulse->lowRemaining,&pulse->bitStream);
        if (pulse->lowRemaining == 0)
        {
            pulse->highRemaining = pulse->highReload;

            recycle = true;
        }
    }
    }

}
#define BS_ST_ENTRY_1 1
#define BS_ST_FILL_NLTQ_TO_END_2 2
#define BS_ST_FILL_HIGH_NLTQ_TO_NDHT_6 6

// This function is called to update a DMA or interrupt based bit stream generator based on
// a circular output buffer fed to a port output register bit.  This
// function generates a bunch of bits, and the DMA or interrupt feeds them out synchronously
// This function must be called more often than the period of time required for the DMA
// to clock out all bits.  If the DMA ever gets ahead of this function then glitches
// in output will occur
//
// When this function is entered, a stream may already be in process.  A stream output is defined
// by DMABitStream_t.
// Two variables in this function are essential:
//
// nextLocationToQueue :  This variable contains the last DMA entry filled in for output.  new
// output needs to be added after this point, in a circular queue manner  This value is stored
// across calls in the pulse_output_t structure
//
// nextDMAHWTransfer : This is the next location that will be transferered to the port by the DMA.
// Our goal in this function is to fill the circular buffer up to but not including that point.
// The DMA or transfer interrupt may move while we're in this function.  That's OK, as we'll generate
// enough bits to keep it busy until the next call of this function.  We copy the DMA next location
// to nextDMAHWTransfer so we have a stable value that isn't changing.
//
// The function is designed to calculate how many high and low bits remain in the current pulse and
// place them in the buffer accordingly.  Conceptually it would be easier to iterate through locations
// in the circular buffer calculating high or low bits for each one.  However, this is very CPU intensive.
// It's better to calculate how many bits need to be queued, and send them to special orCount and andCount
// functions, as these can be written in loopless, branchless assembly to be very fast.
// These functions are dumb and don't understand the circular buffer, so we have to make two calls
// if we need to write to the end of the circular buffer then roll over to the beginning.
//
// The function runs on a state machine:
//
// State 1 BS_ST_ENTRY:
// Upon entry it is determined if nextDMAHWTransfer is lower or higher than
// nextLocationToQueue.  This affects the number of available bytes to
// queue calculation, and how circular queue wrap around is handled
//  If nextDMAHWTransfer is less than nextLocationToQueue, then
//  the DMA rolled over the circle.  Go to  BS_ST_FILL_NLTQ_TO_END
//  otherwise go to BS_ST_FILL_HIGH_NLTQ_TO_NDHT
//
// State 2 BS_ST_FILL_NLTQ_TO_END :
uint16_t updateBitStreamOutput(uint8_t pin, uint8_t level, uint16_t count, DMABitStream_t* bitStream )
{
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	volatile uint8_t nextLocationToQueue = bitStream->nextLocationToQueue; //TODO remove volatile debug
	//uint16_t* baseAddress;

	volatile int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.


	//baseAddress = OutputArrayA;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; //TODO remove volatile debug

    if (bitStream->initialize)
    {
        bitStream->initialize = 0;
        nextLocationToQueue = (nextDMAHWTransfer + 10) & 0x7F;
    }
	// This can go a few ways:
	
	//1: The DMA pointer is at a lower address than the last byte we queued.  If this is the case, go to case 2.  Otherwise, skip to case 6
	//2: Are there enough high bits left to fill the DMA to the end? yes  Do that, subtract the nubmer from the high count, and skip to case 6 , else go to 3
	//3: There wasn't enough to fill the DMA to the end.  Put them all in there.  Go to 4.
	//4: Are there enough low bits to fill the DMA to the end?  Yes: Do that, subtract the nubmer from the low count, and skip to case 7, else go to step 5
	//5: There weren't enough low bits to fill the DMA to the end. Fill them all  Reset the high and low counters, and go to state 1.
	//6:  Are there enough High bits to fill the DMA from the beginning to the DMA pointer? Yes:  Do that, subtract from counter.  Done.  No:  Put them all in and go to step 7.
	//7:  Are there enough Low bits to fill the DMA from the beginning to the DMA pointer? Yes:  Do that, subtract from counter.  Done.  No:  Put them all in, reset counters and go to step 6. 
	//8: Done


	volatile uint8_t state = 1; //TODO remove volatile debug
	uint8_t output = 100;
	output += count * 2;
	output += level;

	//USART_SendData(USART1,output );while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	while (state < 8)
	{


		switch (state)
		{
			case BS_ST_ENTRY_1:
				{

					if (nextDMAHWTransfer < nextLocationToQueue)
					{
						// DMA counter rolled over.
						state = BS_ST_FILL_NLTQ_TO_END_2;
					}
					else
					{
						state = BS_ST_FILL_HIGH_NLTQ_TO_NDHT_6;
					}	

				}
				break;
			case BS_ST_FILL_NLTQ_TO_END_2:
			{
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (count > AvailableDMASpace)
				{
					count -= AvailableDMASpace;
					if (level)
					{
					   // USART_SendData(USART1, 21);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
						orCount(nextLocationToQueue,bitmap,AvailableDMASpace);
					}
					else
					{
					   // USART_SendData(USART1, 22);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
						andCount(nextLocationToQueue,invbitmap,AvailableDMASpace);
					}
					nextLocationToQueue = 0;
					state = BS_ST_FILL_HIGH_NLTQ_TO_NDHT_6;
				}
				else
				{
					state = 3;
				}


			}
			break;

			case 3:
			{
					if (level)
					{
					   // USART_SendData(USART1, 31);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
						orCount(nextLocationToQueue,bitmap,count);
					}
					else
					{
					   // USART_SendData(USART1, 32);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
						andCount(nextLocationToQueue,invbitmap,count);
					}
					nextLocationToQueue+= count;
					nextLocationToQueue &= 127;
					count = 0;
					state = 4;

			}
			break;

			case 4:
			{

                state = 8;
			}
			break;

			case 5:
			{

                state = 8;
			}
			break;

			case BS_ST_FILL_HIGH_NLTQ_TO_NDHT_6:
			{

				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (count > AvailableDMASpace)
				{
					count -= AvailableDMASpace;
					if (level)
					{
					    //USART_SendData(USART1, 61);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
					orCount(nextLocationToQueue,bitmap,AvailableDMASpace);
					}
					else
					{
					    //USART_SendData(USART1, 62);while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
						andCount(nextLocationToQueue,invbitmap,AvailableDMASpace);
					}
					nextLocationToQueue  += AvailableDMASpace;
					state = 8;
				}
				else
				{
					if (level)
					{
					orCount(nextLocationToQueue,bitmap,count);
					}
					else
					{
					andCount(nextLocationToQueue,invbitmap,count);
					}

					nextLocationToQueue+= count;
					count = 0;
					state = 7;
				}

			}
			break;

			case 7:
			{

                state = 8;
			}
			break;

			default:
			{
				state = 8;
			}
			break;
		

		}
	}

	
	bitStream->nextLocationToQueue = nextLocationToQueue ;
    //USART_SendData(USART1,count );while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return (count);
}
void initializeBitStreamOutput(uint8_t pin, uint8_t level, DMABitStream_t* bitStream )
{
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	//uint16_t* baseAddress;


    if (level)
    {
	orCount(0,bitmap,SIZE_OF_DMA_ARRAY);
    }
    else
    {
        andCount(0,invbitmap,SIZE_OF_DMA_ARRAY);
    }
    bitStream->initialize = 1;

}


uint16_t removeBitStreamOutput(uint8_t pin, uint16_t count, uint16_t margin, DMABitStream_t* bitStream )
{
	
    
    

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.


		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; 

    
    int16_t available;
    if (nextDMAHWTransfer >  bitStream->nextLocationToQueue)
    {
        available = SIZE_OF_DMA_ARRAY - nextDMAHWTransfer + bitStream->nextLocationToQueue;
    }
    else if (nextDMAHWTransfer <  bitStream->nextLocationToQueue )
    {
        available = bitStream->nextLocationToQueue - nextDMAHWTransfer;
    }
    else
    {
        return 0;
    }
    
    available -= margin; // Leave these;
    if (available <= 0)
    {
        return 0;
    }
    
    int16_t removed = 0;
    if (available >= count)
    {
        removed = count;
    }
    else
    {
        removed = available;
    }
    
    if (nextDMAHWTransfer >  bitStream->nextLocationToQueue)
    {
        if (bitStream->nextLocationToQueue >= removed)
        {
           bitStream->nextLocationToQueue -= removed;
           return (removed);
        }
        else
        {
            uint16_t returnval = removed;
            removed -= bitStream->nextLocationToQueue;
            bitStream->nextLocationToQueue = SIZE_OF_DMA_ARRAY - removed;
            return (returnval);
        }
       
    }
    else if (nextDMAHWTransfer <  bitStream->nextLocationToQueue )
    {
        bitStream->nextLocationToQueue -= removed;
        return (removed);
    }
    
/*
	if (bitStream->nextLocationToQueue > nextDMAHWTransfer)
	{
		uint16_t available = bitStream->nextLocationToQueue - nextDMAHWTransfer;
		if (available > margin)
		{
			removed = available - margin;
			if (removed > count)
			{
				removed = count;
			}
			if (bitStream->nextLocationToQueue > removed)
            {
                bitStream->nextLocationToQueue -= removed;
            }
            PinHigh(12);
            PinLow(12);
            return (removed);

		}
		else
		{
			return 0 ;
		}
	}
 */
    /*
        if (bitStream->nextLocationToQueue < nextDMAHWTransfer)
	{
		uint16_t available = bitStream->nextLocationToQueue;
        
        if (count > bitStream->nextLocationToQueue)
        {
            bitStream->nextLocationToQueue = 0;
        }
        else if (((int)(bitStream->nextLocationToQueue)) - count > margin)
        {
            bitStream->nextLocationToQueue -= count;
        }
    
    }
     */
    return (removed);
}


uint8_t  PulseInGetOldestDMABit(uint8_t pin)
{
    volatile uint8_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
   

		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 

    
    if (pinPtr->pulse_input.lastDMA == nextDMAHWTransfer)
    {
        return 2;
    }
    else
    {
        uint8_t returnval = (baseAddress[pinPtr->pulse_input.lastDMA] & bitmap) > 0;
        ++pinPtr->pulse_input.lastDMA;
        if (pinPtr->pulse_input.lastDMA >= SIZE_OF_DMA_ARRAY)
        {
            pinPtr->pulse_input.lastDMA = 0;
        }
        return (returnval);
    }
}

uint8_t PulseInDiscardUntilLow(uint8_t pin)
{
     volatile uint8_t* baseAddress;
     uint8_t count = 0;
	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
   

		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 

    
    while (pinPtr->pulse_input.lastDMA != nextDMAHWTransfer)
    {
     
        if( (baseAddress[pinPtr->pulse_input.lastDMA] & bitmap)  ==  0)
        {
            return count;
        }
        ++pinPtr->pulse_input.lastDMA;
        if (pinPtr->pulse_input.lastDMA >= SIZE_OF_DMA_ARRAY)
        {
            pinPtr->pulse_input.lastDMA = 0;
        }
        ++count;
    }
    return count;
}

uint8_t PulseInDiscardUntilHigh(uint8_t pin)
{
     volatile uint8_t* baseAddress;
     uint8_t count = 0;
	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
   

		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 

    
    while (pinPtr->pulse_input.lastDMA != nextDMAHWTransfer)
    {
     
        if(baseAddress[pinPtr->pulse_input.lastDMA] & bitmap) 
        {
            return count;
        }
        ++pinPtr->pulse_input.lastDMA;
        if (pinPtr->pulse_input.lastDMA >= SIZE_OF_DMA_ARRAY)
        {
            pinPtr->pulse_input.lastDMA = 0;
        }
        ++count;
    }
    return count;
}

/// \return number of bits Skipped
uint8_t  PulseInSkipDMABits(uint8_t pin, uint8_t count)
{
 

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
   

         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 

    
    if (pinPtr->pulse_input.lastDMA == nextDMAHWTransfer)
    {
        return 0;
    }
    else
    {
        if (nextDMAHWTransfer > pinPtr->pulse_input.lastDMA)
        {
            uint8_t available = nextDMAHWTransfer - pinPtr->pulse_input.lastDMA;
            if (count >= available)
            {
                pinPtr->pulse_input.lastDMA = nextDMAHWTransfer;
                return available;
            }
            else
            {
                pinPtr->pulse_input.lastDMA += count;
                pinPtr->pulse_input.lastDMA &= 0x7F;
                return ( count);
            }
        }
        else
        {
            uint8_t available = SIZE_OF_DMA_ARRAY - pinPtr->pulse_input.lastDMA;
            available += nextDMAHWTransfer;
            if (count >= available)
            {
                pinPtr->pulse_input.lastDMA = nextDMAHWTransfer;
                return available;
            }
            else
            {
                pinPtr->pulse_input.lastDMA += count;
                pinPtr->pulse_input.lastDMA &= 0x7F;
#if (SIZE_OF_DMA_ARRAY != 128)
#error AND 0x7F constant based on 128 DMA array size
#endif
                return (count);
            }
            
        }
        return (0);
    }
}

/// \returnval Returns true if sample avaialable false if not.
bool  PulseInGetOldestDMASample(uint8_t pin, uint16_t* value)
{
    volatile uint8_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
   

		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 

    
    if (pinPtr->pulse_input.lastDMA == nextDMAHWTransfer)
    {
        return 0;
    }
    else
    {
        *value = baseAddress[pinPtr->pulse_input.lastDMA];
        ++pinPtr->pulse_input.lastDMA;
        if (pinPtr->pulse_input.lastDMA >= SIZE_OF_DMA_ARRAY)
        {
            pinPtr->pulse_input.lastDMA = 0;
        }
        return (1);
    }
}

