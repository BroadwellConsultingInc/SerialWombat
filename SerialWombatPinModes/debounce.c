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
    uint16_t doubleClickPeriod;
    uint16_t doubleClickCount;
    uint16_t doubleClickCounter;
    uint16_t pushOutputValue;
    uint8_t pushOutputPin;
    uint16_t doubleClickOutputValue;
   	uint8_t currentDifferenceCount;
	uint8_t debouncePeriod;	
	uint8_t currentReportedLevel:1;
	        uint8_t doubleClickPending;  // 0 = no timer, 1 = first release timer, 2 = third press timer; Double click increments after timeout of third press timer
	uint8_t invertPolarity:1;
    uint8_t toggleSimulation:1;

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
        #ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
        debounce->doubleClickPeriod = 150;
        debounce->doubleClickCount = 0;
        debounce->doubleClickCounter = 0;
        debounce->doubleClickPending = 0;
        debounce->toggleSimulation = 0;
        #endif
        #ifndef ENABLE_DEBOUNCE_SETPIN_DISABLE
        debounce->pushOutputPin = 255;
        #endif
       


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
#ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
        case CONFIGURE_CHANNEL_MODE_2:
        {
            debounce->doubleClickPeriod = RXBUFFER16(3);
            debounce->doubleClickCounter = 0;
            debounce->doubleClickPending = 0;

        }
        break;  

#endif
#ifndef ENABLE_DEBOUNCE_SETPIN_DISABLE
        case CONFIGURE_CHANNEL_MODE_3:
        {
            debounce->pushOutputPin = Rxbuffer[3];
            debounce->pushOutputValue = RXBUFFER16(4);
            debounce ->doubleClickOutputValue = RXBUFFER16(6);
        }
break;
        #endif  
#ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
        case CONFIGURE_CHANNEL_MODE_4:
        {
            TXBUFFER16(3, debounce->doubleClickCount);
            if (Rxbuffer[3] != 0)
            {
                debounce->doubleClickCount = 0;
            }
        }
        break;  
        #endif
#ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
        case CONFIGURE_CHANNEL_MODE_5:
        {
            debounce->toggleSimulation = Rxbuffer[3];
            debounce->transitions = RXBUFFER16(4);
        }
        break;

#endif
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

#ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
    if (debounce->doubleClickPending)
    {
        if (debounce->doubleClickCounter < 65535)
        {
            ++debounce->doubleClickCounter;
        }
        if (debounce->doubleClickPending == 2 &&
            debounce->doubleClickCounter >= debounce->doubleClickPeriod)
        {
            ++debounce->doubleClickCount;
            if (debounce->transitions >= 4)
            {
                debounce->transitions -= 4;
            }
            else
            {
                debounce->transitions = 0;
            }
#ifndef ENABLE_DEBOUNCE_SETPIN_DISABLE
            SetBuffer(debounce->pushOutputPin, debounce->doubleClickOutputValue);
#endif
            debounce->doubleClickCounter = 0;
            debounce->doubleClickPending = 0;
        }
    }
    #endif

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
#ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
                if (debounce->doubleClickPeriod)
                {
                    if (debounce->currentReportedLevel)
                    {
                        // A press during the third timer makes this a sequence
                        // of three presses rather than a double click and a
                        // press.  Its release can start a new first timer.
                        if (debounce->doubleClickPending == 2)
                        {
                            debounce->doubleClickCounter = 0;
                            debounce->doubleClickPending = 0;
                        }
                    }
                    else
                    {
                        if (debounce->doubleClickPending == 0)
                        {
                            // Start the first timer on the first release.
                            debounce->doubleClickPending = 1;
                            debounce->doubleClickCounter = 0;
                        }
                        else if (debounce->doubleClickPending == 1)
                        {
                            if (debounce->doubleClickCounter < debounce->doubleClickPeriod)
                            {
                                // The second release occurred within the
                                // period.  Start the third timer and wait to
                                // make sure that there is no third press.
                                debounce->doubleClickPending = 2;
                            }
                            // If the second release was too late, it becomes
                            // the first release of a new potential double click.
                            debounce->doubleClickCounter = 0;
                        }
                    }
                }
            #endif
#ifndef ENABLE_DEBOUNCE_SETPIN_DISABLE
                SetBuffer(debounce->pushOutputPin, debounce->pushOutputValue);
            #endif
        }
    }
    else
    {
        debounce->currentDifferenceCount = 0;
    }
    
    uint16_t outputValue = debounce->currentReportedLevel?65535:0;

#ifndef ENABLE_DEBOUNCE_DOUBLECLICK_AND_TOGGLE_DISABLE
       if (debounce->toggleSimulation)
        {
            outputValue = (debounce->transitions &0x02)? 65535:0;
        }
    #endif

            CurrentPinRegister->generic.buffer = inputProcessProcess(&debounce->inputProcess,outputValue);
	
}

