#include <stdint.h>
#include "serialWombat.h"


typedef struct debounce_n{
	uint16_t  currentStableTime;
    uint16_t transitions;
   	uint8_t currentDifferenceCount;
	uint8_t debouncePeriod;	
	uint8_t currentReportedLevel:1;
	uint8_t invertPolarity:1;
        uint8_t lastReading;
}debounce_t;

#define debounce ((debounce_t*) CurrentPinRegister)

void initDebounce (void)
{

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
    
		    CurrentPinRegister -> generic.buffer = debounce->currentReportedLevel;
	
}

