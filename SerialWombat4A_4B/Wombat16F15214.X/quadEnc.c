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

/*! \file quadEnc.c
 
  This file contains the Quadrature Encoder pin mode for the Serial Wombat 4A and 4B
 */


typedef struct quadEnc_n{
           uint8_t secondPin; ///< The Second pin used for the qudrature Encoder
           uint8_t debounceFrames;  ///< Number of 1mS frames after a transition before another transition is recognized.
           uint8_t debounceCount;  ///<  How many frames remaining before a transiton will be recognized
           uint8_t readState;     ///< When and how to read inputs:  0:  High to Low, interrupt driven.  1:  Low to high, Interrupt Driven 2:  Both transitions, interrupt driven.  4: High to Low, Polled.  5:  Low to High, Polled.  6:  Both transitions, Polled. 
           uint8_t tempPrimaryPinState:1;  ///< Temporary bit that stores whether this pin is high or low (or was during interrupt)
           uint8_t tempSecondPinState:1;   ///< Temporary bit that stores whether 2nd pin is high or low (or was during interrupt)
           uint8_t updateCounter:1;  ///< Temporary bit indicating if counter needs changed based on transition of primary pin
           uint8_t lastState:1;  ///< State of primary pin on last examination, used to detect transitions.
           uint8_t ignoreRemaining:1; ///<  Temporary bit set to ignore any additional transitions detected this frame (used for debouncing interrupt based input)
           
}quadEnc_t;

#define quadEnc  ((quadEnc_t*) CurrentPinRegister)


/*!
    \brief Initialization routine for Quadrature Encoder pin mode

----

Retrevial of Quadrature Encoder Position Value 
-------------------------------

Configure the QuadEnc pin mode using the CONFIGURE_CHANNEL_MODE_0 command before reading values.  
The Quadrature Encoder Position value is stored in the Primary Pin's 16-bit Public data area.  Use the Read Pin Buffer command to retreive it.

The Position value is a 16-bit unsigned number.  Transitions that decrement a value of 0 will roll over to 65535.  Transitions which
incrment a value of 65535 will roll over to 0.  

-----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Quadrature Encoder Reader.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x05 (Quadrature Encoder) | Debounce Frames (low byte) |Debounce Frames (high byte, ignored) |Second Pin Number |Read State (0,1,2,4,5 or 6) |0: Pull ups off, 1: Pull ups on |

Read State Values:

 * 0 = Read on Primary Pin High to Low transition, sampled with interrupts
 
 * 1 = Read on Primary Pin Low to High transition, sampled with interrupts

 * 2 = Read on Both transitions, sampled with interrupts
 
 * 4 = Read on Primary Pin High to Low transition, polled every 1mS frame
 
 * 5 = Read on Primary Pin Low to High transition, polled every 1mS frame
 
 * 6 = Read on Both transitions, polled every 1mS frame

Response:

Command is echoed back.

Examples:

Set pins 1 (primary) and 2 (secondary) to quadrature encoder reading, 10 mS of debounce, Pull ups on, Read both transitions in polled mode

> `0xC0 0x01 0x05 0x0A 0x00 0x02 0x06 0x01 `

*/
void initQuadEnc(void)
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
 
    }
} 

extern uint8_t copy_IOC_PortBuffer[IOC_BUFFER_SIZE];


/*! 
\brief Periodic call to service the Quadrature Encoder decoder State Machine for a pin

This State machine monitors inputs from two pins (Primary and Secondary) to increment or decrement
a counter based on transitions of a rotary encoder.

This State machine is called every 1 mS by the executive when the Primary pin is serviced.
Initialization of this state machine sets the secondary pin mode to PIN_MODE_CONTROLLED, which
is not serviced by the executive.

The quadrature encoder monitors the state of the Primary and Secondary pins via either polling (the pins are read
when the state machine is serviced) or via interrupt when a change is state on the Primary pin is detected, at which time
the state of both pins is recorded and saved for later processing when the state machine is serivced.

Saved interrupt transitions are stored in copy_IOC_PortBuffer, which is an array which is copied once for all pins from a similar interrupt modified
array just prior to beginning the pin-servicing process every 1 mS.  copy_IOC_PortBuffer stores the state of all 4 SW pins whenever an interrupt-on-change
occurs.  The array is initialized to 0xFF.  Any interrupt on change sets the most significant bit of the value to 0 indicating that the element has new
data.  The array is filled from end to start so that incrementing indexing gets events as they happened in chronological order.  Unused elements are therefore at the
beginning of the array.

The update routine first looks to see if transitions are ignored due to being in a debounce period.  If so, it decrements the debounce counter and returns.

If not in debounce, the state machine either samples and processes the primary pin state, or iterates through the copy_IOC_PortBuffer looking for transitions of
the primary pin.  

When a transition that is relevant based on readState occurs, the state of the second pin is checked against the primary pin.  If they are the same the position
counter is incremented.  If they are different, then the position counter is decremented.  The debounce counter is then set to the configured value.  If the debounce
counter is >0 and interrupt processing is occuring then the remainder of interrupts during that service are ignored.
*/
void update_quadEnc(void)
{


	if (quadEnc->debounceCount != 0)
	{
		// Still in debounce lockout.  Decrement counter and return.
		--quadEnc->debounceCount;
		quadEnc->lastState = CurrentPinRead();
		return;
	}


	quadEnc->ignoreRemaining = 0;

	// Iterate through all of the entried in copy_IOC_PortBuffer
	for (uint8_t i = 0; i < IOC_BUFFER_SIZE; ++i)
	{
		uint8_t currentInput;
		if (quadEnc->readState < 4)
		{
			//Read state is < 4, so we're processing from the interrupt buffer.
			currentInput = copy_IOC_PortBuffer[i];
			if (currentInput & 0x80u)
			{
				//Not set.  There's no interrupt transition in this buffer entry.
				continue;
			}
	

			// Get the primary and secondary pin state by reading the appropriate bits in the copy_IOC_PortBuffer entry
			quadEnc->tempPrimaryPinState = ((currentInput & CurrentPinMask) != 0);
			quadEnc->tempSecondPinState = ((currentInput & PinMaskArray[quadEnc->secondPin]) != 0);
		}
		else
		{
			// Read state is >=4, so we're polling.

			quadEnc->tempPrimaryPinState = CurrentPinRead();
			quadEnc->tempSecondPinState = ReadPin(quadEnc->secondPin);
			i = IOC_BUFFER_SIZE; // Only run this loop once, since we aren't actually using copy_IOC_PortBuffer
		}

		if (quadEnc->lastState == quadEnc->tempPrimaryPinState )
		{
			//No transition has occured.  Go to the next entry

				continue;
		}


		// If we reach this point, the current sample of the primary pin is different from the prior one ( a transition has occured)
		// See if it's relevant to us and if so what we need to do to the counter.
		//
		quadEnc->lastState = quadEnc->tempPrimaryPinState;

		if (quadEnc->ignoreRemaining)
		{
			// We entered a debounce lockout eariler in this service.  Ignore changes.

			continue;
		}

		quadEnc->updateCounter = 0;  // Do we need to update the counter this iteration?  Assume no
		if ((quadEnc->readState & 0x03)  == 0)
		{
			if (!quadEnc->tempPrimaryPinState)
			{
				// Relevant transition is high to low, and we found one.  
				quadEnc->updateCounter = 1;
			}

		}
		else if ((quadEnc->readState & 0x03) == 1 )
		{
			if (quadEnc->tempPrimaryPinState)
			{
				// Relevant transition is low to high , and we found one.  
				quadEnc->updateCounter = 1;
			}
		}
		else if ((quadEnc->readState & 0x03) == 2)
		{
			// Both transitions are relevant.			
			quadEnc->updateCounter = 1;
		}

		if (quadEnc->updateCounter)
		{
			// A relevant transition occured.  Look at the primary and secondary pin states and update the counter.

			if (quadEnc->tempPrimaryPinState == quadEnc->tempSecondPinState)
			{
				++CurrentPinRegister->generic.buffer;
			}
			else
			{
				--CurrentPinRegister->generic.buffer;
			}

			// Set the debounce frame counter
			quadEnc->debounceCount = quadEnc->debounceFrames; 
			if (quadEnc->debounceFrames > 0)
			{
				quadEnc->ignoreRemaining = 1;
				// Don't process any more transitions this servicing.  They're bounces...
			}
		}     
	}
	quadEnc->lastState = CurrentPinRead();
}
