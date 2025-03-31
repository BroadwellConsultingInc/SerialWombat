#include <stdint.h>
#include "serialWombat.h"



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
            if (pulse->lowRemaining)
            {
            recycle = true;
            }
        }
    }
    }

}

#ifdef OLDVERISON
void updatePulseOutput(uint8_t pin)
{
	pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	uint8_t nextLocationToQueue = pinPtr->pulse_output.lastDMA;
	uint16_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.

	if (pinPort[pin] == 0)
	{
		baseAddress = OutputArrayA;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; 
	}
	else
	{
		baseAddress = OutputArrayB;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT1 ;
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


	uint8_t state = 1;


	while (state < 8)
	{
		switch (state)
		{
			case 1:
				{

					if (nextDMAHWTransfer < nextLocationToQueue)
					{
						// DMA counter rolled over.
						state = 2;
					}
					else
					{
						state = 6;
					}	

				}
				break;
			case 2:
			{
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (pinPtr->pulse_output.highRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.highRemaining -= AvailableDMASpace;
					orCount(&baseAddress[nextLocationToQueue],bitmap,AvailableDMASpace);
					nextLocationToQueue = 0;
					state = 6;
				}
				else
				{
					state = 3;
				}


			}
			break;

			case 3:
			{
					orCount(&baseAddress[nextLocationToQueue],bitmap,pinPtr->pulse_output.highRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.highRemaining;
					pinPtr->pulse_output.highRemaining = 0;
					state = 4;

			}
			break;

			case 4:
			{
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (pinPtr->pulse_output.lowRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.lowRemaining -= AvailableDMASpace;
					andCount(&baseAddress[nextLocationToQueue],invbitmap,AvailableDMASpace);
					nextLocationToQueue = 0;
					state = 7;
				}
				else
				{
					state = 5;
				}

			}
			break;

			case 5:
			{
					andCount(&baseAddress[nextLocationToQueue],invbitmap,pinPtr->pulse_output.lowRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.lowRemaining;
					pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
					pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
					state = 1;

			}
			break;

			case 6:
			{
				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (pinPtr->pulse_output.highRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.highRemaining -= AvailableDMASpace;
					orCount(&baseAddress[nextLocationToQueue],bitmap,AvailableDMASpace);
					nextLocationToQueue  += AvailableDMASpace;
					state = 8;
				}
				else
				{
					orCount(&baseAddress[nextLocationToQueue],bitmap,pinPtr->pulse_output.highRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.highRemaining;
					pinPtr->pulse_output.highRemaining = 0;
					state = 7;
				}

			}
			break;

			case 7:
			{
				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (pinPtr->pulse_output.lowRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.lowRemaining -= AvailableDMASpace;
					andCount(&baseAddress[nextLocationToQueue],invbitmap,AvailableDMASpace);
					nextLocationToQueue += AvailableDMASpace;
					state = 8;
				}
				else
				{
					andCount(&baseAddress[nextLocationToQueue],invbitmap,pinPtr->pulse_output.lowRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.lowRemaining;
					pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
					pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
					state = 6;
				}

			}
			break;

			default:
			{
				state = 8;
			}
			break;
		

		}
	}

	
	pinPtr->pulse_output.lastDMA = nextLocationToQueue;
}
#endif
uint16_t updateBitStreamOutput(uint8_t pin, uint8_t level, uint16_t count, DMABitStream_t* bitStream )
{
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	uint8_t nextLocationToQueue = bitStream->nextLocationToQueue;
	uint16_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.

	if (pinPort[pin] == 0)
	{
		baseAddress = OutputArrayA;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; 
	}
	else
	{
		baseAddress = OutputArrayB;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT1 ;
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


	uint8_t state = 1;


	while (state < 8)
	{
		switch (state)
		{
			case 1:
				{

					if (nextDMAHWTransfer < nextLocationToQueue)
					{
						// DMA counter rolled over.
						state = 2;
					}
					else
					{
						state = 6;
					}	

				}
				break;
			case 2:
			{
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (count > AvailableDMASpace)
				{
					count -= AvailableDMASpace;
					if (level)
					{
						orCount(&baseAddress[nextLocationToQueue],bitmap,AvailableDMASpace);
					}
					else
					{
						andCount(&baseAddress[nextLocationToQueue],invbitmap,AvailableDMASpace);
					}
					nextLocationToQueue = 0;
					state = 6;
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
						orCount(&baseAddress[nextLocationToQueue],bitmap,count);
					}
					else
					{
						andCount(&baseAddress[nextLocationToQueue],invbitmap,count);
					}
					nextLocationToQueue+= count;
					count = 0;
					state = 4;

			}
			break;

			case 4:
			{
				/* ???
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (pinPtr->pulse_output.lowRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.lowRemaining -= AvailableDMASpace;
					andCount(&baseAddress[nextLocationToQueue],invbitmap,AvailableDMASpace);
					nextLocationToQueue = 0;
					state = 7;
				}
				else
				{
					state = 5;
				}

				*/
                state = 8;
			}
			break;

			case 5:
			{
				/*
					andCount(&baseAddress[nextLocationToQueue],invbitmap,pinPtr->pulse_output.lowRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.lowRemaining;
					pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
					pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
					state = 1;
				*/
                state = 8;
			}
			break;

			case 6:
			{
				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (count > AvailableDMASpace)
				{
					count -= AvailableDMASpace;
					if (level)
					{
					orCount(&baseAddress[nextLocationToQueue],bitmap,AvailableDMASpace);
					}
					else
					{
						andCount(&baseAddress[nextLocationToQueue],invbitmap,AvailableDMASpace);
					}
					nextLocationToQueue  += AvailableDMASpace;
					state = 8;
				}
				else
				{
					if (level)
					{
					orCount(&baseAddress[nextLocationToQueue],bitmap,count);
					}
					else
					{
					andCount(&baseAddress[nextLocationToQueue],invbitmap,count);
					}

					nextLocationToQueue+= count;
					count = 0;
					state = 7;
				}

			}
			break;

			case 7:
			{
				/* ???
				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (pinPtr->pulse_output.lowRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.lowRemaining -= AvailableDMASpace;
					andCount(&baseAddress[nextLocationToQueue],invbitmap,AvailableDMASpace);
					nextLocationToQueue += AvailableDMASpace;
					state = 8;
				}
				else
				{
					andCount(&baseAddress[nextLocationToQueue],invbitmap,pinPtr->pulse_output.lowRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.lowRemaining;
					pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
					pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
					state = 6;
				}
				*/
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
	return (count);
}
void initializeBitStreamOutput(uint8_t pin, uint8_t level, DMABitStream_t* bitStream )
{
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	uint16_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.

	if (pinPort[pin] == 0)
	{
		baseAddress = OutputArrayA;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; 
	}
	else
	{
		baseAddress = OutputArrayB;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT1 ;
	}


    if (level)
    {
	orCount(baseAddress,bitmap,SIZE_OF_DMA_ARRAY);
    }
    else
    {
        andCount(baseAddress,invbitmap,SIZE_OF_DMA_ARRAY);
    }
    bitStream->nextLocationToQueue = nextDMAHWTransfer + 10;
    if (nextDMAHWTransfer >= SIZE_OF_DMA_ARRAY )
    {
        nextDMAHWTransfer -= SIZE_OF_DMA_ARRAY;
    }
}


uint16_t removeBitStreamOutput(uint8_t pin, uint16_t count, uint16_t margin, DMABitStream_t* bitStream )
{
	
    
    

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.

	if (pinPort[pin] == 0)
	{
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; 
	}
	else
	{
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT1 ;
	}
    
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
    uint16_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
   
	if (pinPort[pin] == 0)
	{
		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 
	}
	else
	{
		baseAddress = InputArrayB;
         while (DMACNT3 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT3 ;
	}
    
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
     uint16_t* baseAddress;
     uint8_t count = 0;
	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
   
	if (pinPort[pin] == 0)
	{
		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 
	}
	else
	{
		baseAddress = InputArrayB;
         while (DMACNT3 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT3 ;
	}
    
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
     uint16_t* baseAddress;
     uint8_t count = 0;
	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
	uint16_t bitmap = pinBitmap[pin];
   
	if (pinPort[pin] == 0)
	{
		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 
	}
	else
	{
		baseAddress = InputArrayB;
         while (DMACNT3 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT3 ;
	}
    
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
   
	if (pinPort[pin] == 0)
	{
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 
	}
	else
	{
         while (DMACNT3 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT3 ;
	}
    
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
    uint16_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.
    pinRegister_t* pinPtr = &PinUpdateRegisters[pin];
   
	if (pinPort[pin] == 0)
	{
		baseAddress = InputArrayA;
         while (DMACNT2 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT2 ; 
	}
	else
	{
		baseAddress = InputArrayB;
         while (DMACNT3 == 0); // Wait for reload
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT3 ;
	}
    
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
    

