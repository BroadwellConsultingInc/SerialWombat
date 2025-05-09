/*
Copyright 2020-2025 Broadwell Consulting Inc.

Serial Wombat is a registered trademark of Broadwell Consulting Inc in
the United States.  See SerialWombat.com for usage guidelines.

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
#include "serialWombat.h"
#include "inputProcess.h"

typedef struct debounce_n{
	uint16_t  currentStableTime;
    uint16_t transitions;
   	uint8_t currentDifferenceCount;
	uint8_t debouncePeriod;	
	uint8_t currentReportedLevel:1;
	uint8_t invertPolarity:1;
        uint8_t lastReading;
         inputProcess_t inputProcess;
}debounce_t;

#define debounce ((debounce_t*) CurrentPinRegister)

void initDebounce (void)
{
 if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_DEBOUNCE)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
        case CONFIGURE_CHANNEL_MODE_0:
        {
            CurrentPinRegister->generic.mode = PIN_MODE_DEBOUNCE;
	    CurrentPinInput();
	    if (Rxbuffer[7] & 1)
	    {
		    CurrentPinPullUp();
	    }
	    else
	    {
		    CurrentPinNoPullUp();
	    }

        debounce->debouncePeriod = Rxbuffer[3];
	    debounce->invertPolarity = Rxbuffer[5];

	    debounce->currentStableTime = 0;
	    debounce->currentDifferenceCount = 0;
        debounce->transitions = 0;
	    inputProcessInit(&debounce->inputProcess);
	}
	break;
    
        case CONFIGURE_CHANNEL_MODE_1:
        {
            Txbuffer[3] =  debounce->currentReportedLevel;
            TXBUFFER16(4, debounce->transitions);
            TXBUFFER16(6, debounce->currentStableTime);
            if (Rxbuffer[3] != 0)
            {
                debounce->transitions = 0;
            }
        }
        break;
	        default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&debounce->inputProcess);
			}
			break;    
  }
}


void updateDebounce()
{ 

    
    if (debounce->currentStableTime < 65535)
    {
        ++debounce->currentStableTime;
    }
    debounce->lastReading = CurrentPinRead();
    if (debounce->invertPolarity )
    {
		 
		    debounce->lastReading = !debounce->lastReading;
	}
    
    
    if (debounce->lastReading != debounce->currentReportedLevel)
    {
        ++ debounce->currentDifferenceCount;
        if (debounce->currentDifferenceCount >= debounce->debouncePeriod)
        {
            debounce->currentReportedLevel = debounce->lastReading;
            debounce->currentDifferenceCount = 0;
            debounce->currentStableTime = 0;        
            debounce->transitions++;        
        }
    }
    else
    {
        debounce->currentDifferenceCount = 0;
    }
    
    uint16_t outputValue = debounce->currentReportedLevel?65535:0;

            CurrentPinRegister->generic.buffer = inputProcessProcess(&debounce->inputProcess,outputValue);
	
}

