/*
Copyright 2020-2021 Broadwell Consulting Inc.

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
#include "pic24fj256ga702/mcc_generated_files/mcc.h"


typedef enum {
	TOUCH_STATE_IDLE = 0,
	TOUCH_STATE_DISCHARGE = 1,
	TOUCH_STATE_SAMPLING = 2,
	TOUCH_STATE_WAITING_FOR_COMPLETION = 3,
}touch_state_t;

typedef struct touch_n{
	uint32_t averageSum;
	uint16_t delay;
	uint16_t delayCounter;
	uint16_t chargeTime;
	uint16_t hysteresisHigh;
	uint16_t hysteresisLow;
	uint16_t highCapDigOutput;
	uint16_t lowCapDigOutput;
	uint32_t  debounceLastTransitionFrameCount;
	uint16_t debounceTransitions;
	uint8_t debounceLastReading;
	uint8_t state;
	uint8_t averageCount;
	uint8_t debounceCurrentDifferenceCount;
	uint8_t debounceLimit;	
    uint8_t waitLimit;
    uint8_t timingResource;
	uint8_t debounceCurrentReportedLevel:1;
	uint8_t digitalOutput:1;
	uint8_t invert:1;


}touch_t;

#define touch ((touch_t*) CurrentPinRegister)

#define CTMU_MODE_EDGE 0
#define RANGE_0_550uA 1 // .550uA
#define CTMU_TOUCH_THRESHHOLD_OFFSET 20

typedef enum
{
	TOUCH_CHANNEL_ON_OFF,
	TOUCH_CHANNEL_MODE
}
TOUCH_CHANNEL_t;



/*!
    \brief Initialization routine for Capacitive Touch sensor

----

Retrevial of Raw A/D conversions
-------------------------------

Configure the A/D using the CONFIGURE_CHANNEL_MODE_0 command before reading values.  
Raw A/D conversions are stored in the Pin's 16-bit Public data area.  Use the Read Pin Buffer command to retreive it.

-----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize Cap Touch to Analog mode and set charge time


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set|0x16 (CapTouch) | ChargeTime (LSB) |ChargeTime (MSB) |0x55* |0x55* |0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set pin 0 to Cap Touch, with a charge time of 0x2080

> `0xC0 0x00 0x16 0x80 0x20 0x55 0x55 0x55 `

----

CONFIGURE_CHANNEL_MODE_1:
---------------------

Configure high and low limits (Hysteresis) for digital mode.

Must not be called before 0xC0 command.

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set|0x16 (CapTouch) |Low Limit (LSB) | Low Limit (MSB) | High Limit (LSB) | High Limit (MSB)|0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Configure pin 0 to Captouch mode, Low Limit 0xC830, High Limit 0xF020

> `0xC1 0x00 0x16 0x30 0xC8 0x20 0xF0 0x55 `


----

CONFIGURE_CHANNEL_MODE_2:
---------------------

Set the values reported as public data for Low (touch present) and High (touch absent) coniditions when in digital mode

Must not be called before 0xC0 command.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set|0x16 (CapTouch) |Low Value (LSB) | Low ValueLimit (MSB) | High ValueLimit (LSB) | High Value (MSB)|0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Configure pin 0 to Report 10000 (0x2710) when touch is present and 2000 (0x07D0) when touch is absent

> `0xC2 0x00 0x16 0x10 0x27 0xD0 0x07 0x55 `



----

CONFIGURE_CHANNEL_MODE_3:
---------------------

Set the values reported as public data for Low (touch present) and High (touch absent) coniditions when in digital mode

Must not be called before 0xC0 command.
Commands 0xC1 and 0xC2 should be called before this command.

Debounce counts are in Cap Touch Samples, not mS.  With proper Hysteresis settings this number is typically 0 or in the single digits

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC3|Pin To Set|0x16 (CapTouch) |0: Analog  1: Digital | Inversion:  0: Touch Present is logic 1  1: Touch Present is Logic 0 | Debounce Counts (LSB) | Debounce Counts(MSB)|0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Configure pin 0 to Digital mode, no iversion, 3 debounce counts

> `0xC3 0x00 0x16 0x01 0x00 0x03 0x00 0x55 `



----

CONFIGURE_CHANNEL_MODE_4:
---------------------

Get digital status.

Must not be called before 0xC0 command.
Commands 0xC1 and 0xC2 and 0xC3 should be called before this command.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC4|Pin To Set|0x16 (CapTouch) |Reset Transition Count: 0:Don't reset   1: Reset |0x55*|0x55*|0x55*|0x55*|

\*0x55 is recommended, but any byte is acceptable

Response:
|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC4|Pin To Set|0x16 (CapTouch) |Current digital state (0 or 1)| Transitions (LSB) | Transitions (MSB) | Time since transtion (LSB), mS)| Time since transition (MSB)|


Examples:

Read current digital state, transitions, and time in state from Captouch pin 0.  Reset the Transition count on read

> `0xC4 0x00 0x16 0x01 0x55 0x55 0x55 0x55 `

Response is logic high, 11 transistions, 7000 mS (1B58) since transition:
> `0xC4 0x00 0x16 0x01 0x0A 0x00 0x58 0x1B `
*/

void initTouch (void)
{
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PROTECTEDOUTPUT)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinInput();
				if (CurrentPin >= NUMBER_OF_PHYSICAL_PINS  || WombatPinToADCChannel[CurrentPin] == 0xFF)
				{
					error(SW_ERROR_PIN_NOT_CAPABLE);
					CurrentPinRegister->generic.mode = PIN_MODE_CONTROLLED;
					return;
				}			
				CurrentPinAnalog();
				CurrentPinRegister->generic.mode = PIN_MODE_TOUCH;
				touch->state = TOUCH_STATE_IDLE;
				touch->delay = RXBUFFER16(5);
				touch->delayCounter = 0;
				touch->averageCount = 0;
				touch->averageSum = 0;
				touch->chargeTime = RXBUFFER16(3);
				touch->digitalOutput = 0;
                touch->waitLimit = 0;
                


				if (ADC1Semaphore == CurrentPin)
				{
					ADC1Semaphore = RESOURCE_AVAILABLE;
				}
				if (TMR1Semaphore == CurrentPin)
				{
					TMR1Semaphore = RESOURCE_AVAILABLE;
				}
				if (TMR3Semaphore == CurrentPin)
				{
					TMR3Semaphore = RESOURCE_AVAILABLE;
				}

                
                
			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:
			{		
					touch->hysteresisLow = RXBUFFER16(3);
					touch->hysteresisHigh = RXBUFFER16(5);
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{	
					touch->lowCapDigOutput = RXBUFFER16(3);
					touch->highCapDigOutput = RXBUFFER16(5);		
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3:
			{		
					touch->digitalOutput = Rxbuffer[3] > 0;
					touch->invert = Rxbuffer[4] > 0;
					touch->debounceLimit = RXBUFFER16(5);		
			}
			break;

		case CONFIGURE_CHANNEL_MODE_4:
			{
					Txbuffer[3] =  touch->debounceCurrentReportedLevel;
					TXBUFFER16(4, touch->debounceTransitions);
					uint32_t timedifference = FramesRun - touch->debounceLastTransitionFrameCount;
					if (timedifference > 65535)
					{
						timedifference = 65535;
					}
					TXBUFFER16(6, ((uint16_t) timedifference));
					if (Rxbuffer[3] != 0)
					{
						touch->debounceTransitions   = 0;
					}
			}
			break;
            
               default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
	}
}
touch_t* debugTouch;

void touchProcessDigital()
{
   	if (touch->debounceCurrentReportedLevel)
	{
		//Logic 1, lower capacitance
		if (CurrentPinRegister->generic.buffer  >= touch->hysteresisHigh)
		{
			++touch->debounceCurrentDifferenceCount;
			if (touch->debounceCurrentDifferenceCount > touch->debounceLimit)
			{
				touch->debounceCurrentReportedLevel = 0;
				touch->debounceCurrentDifferenceCount = 0;
				++touch->debounceTransitions;
				touch->debounceLastTransitionFrameCount = FramesRun;
			}
		}
		else
		{
				touch->debounceCurrentDifferenceCount = 0;
		}

	}
	else
	{
		//Logic 0, higher capacitance
		if (CurrentPinRegister->generic.buffer  <= touch->hysteresisLow)
		{
			++touch->debounceCurrentDifferenceCount;
			if (touch->debounceCurrentDifferenceCount > touch->debounceLimit)
			{
				touch->debounceCurrentReportedLevel = 1;
				touch->debounceCurrentDifferenceCount = 0;
				++touch->debounceTransitions;
				touch->debounceLastTransitionFrameCount = FramesRun;
			}
		}
		else
		{
				touch->debounceCurrentDifferenceCount = 0;
                
		}
	}
	if (touch->debounceCurrentReportedLevel)
	{
		if (touch->invert)
		{
			CurrentPinRegister->generic.buffer = touch->highCapDigOutput;
		}
		else
		{
			CurrentPinRegister->generic.buffer = touch->lowCapDigOutput;
		}
	}
	else
	{
		if (touch->invert)
		{
			CurrentPinRegister->generic.buffer = touch->lowCapDigOutput;
		}
		else
		{
			CurrentPinRegister->generic.buffer = touch->highCapDigOutput;
		}
	}


}

void touchCallback()
{
      CTMUCON1Lbits.IDISSEN = 0; // Disable discharge (start charging)
}

void updateTouch()
{ 
	debugTouch =(touch_t*) CurrentPinRegister;
	switch (touch->state)
	{
		case TOUCH_STATE_IDLE:
			{
				++ touch->delayCounter;
				if (touch->delayCounter >= touch->delay)
				{
					if (ADC1Semaphore == RESOURCE_AVAILABLE && 
                            TMR3Semaphore == RESOURCE_AVAILABLE)
					{
                        TIMING_RESOURCE_t timingResource = 
                                timingResourceInterruptClaim(TIMING_RESOURCE_ANY,
                                8000, 0, touchCallback);
                        if (timingResource != TIMING_RESOURCE_NONE)
                        {
                            touch->timingResource = timingResource;    
                            ADC1Semaphore = CurrentPin;
                            TMR3Semaphore = CurrentPin;
                            touch->state = TOUCH_STATE_DISCHARGE;                
                        }
					}
				}
			}
			break;

		case TOUCH_STATE_DISCHARGE:
			{
				//Reset ADC to reset conditions
				ADC1_ResetConditions();
                TMR3_ResetConditions();

				CTMUCON1L = 0x0000; // Disable CTMU
				CTMUCON1Lbits.TGEN = CTMU_MODE_EDGE; // Enable/Disable Time Generation mode
				CTMUCON1Lbits.EDGEN = 0; // Edges are disabled
				CTMUCON1Lbits.ITRIM = 0; // Set trim
				CTMUCON1Lbits.CTTRIG = 0; // Trigger output disabled
				CTMUCON1Lbits.IRNG = ( RANGE_0_550uA & 3); // Set range
				CTMUCON1H = 0; // Edges are disabled, edge controls ignored
				// This line does not apply to all devices
				CTMUCON1Hbits.IRNGH = (RANGE_0_550uA>>2); // set high bit of range

				CTMUCON2Lbits.IRSTEN = 0; // Current source reset disabled
				CTMUCON2Lbits.DSCHS = 0; // Discharge source disabled

				// start conversion, Sample when SAMP bit is set
				AD1CON2 = 0x0000; // VR+ = AVDD, V- = AVSS, Don't scan,
				AD1CON3 = 0x000A; // ADC uses system clock
				AD1CON5 = 0x0000; // Auto-Scan disabled
                AD1CON1 = 0x8620;  // Turn on A/D, Left Justified, 12 bit, TMR3 triggered

				AD1CHSbits.CH0SA = WombatPinToADCChannel[CurrentPin]; // Select the analog channel

				CTMUCON1Lbits.CTMUEN = 1; // Enable the CTMU
				CTMUCON1Hbits.EDG1STAT = 1; // Enable current source
				CTMUCON1Lbits.IDISSEN = 1; // Enable discharge
				AD1CON1bits.DONE = 0; //Set up the timer 
				AD1CON1bits.SAMP = 1; // Manual sampling start

				touch->state = TOUCH_STATE_SAMPLING;
			}
			break;

		case TOUCH_STATE_SAMPLING:
			{

				T3CON = 0;
				PR3 = touch->chargeTime + 8000; //8000 minimum clocks to trigger A/D.
                TMR3 = 0;
                timingResourceInterruptActivate(touch->timingResource);
				T3CON = 0x8000; //Start timer
                
            

				touch->state = TOUCH_STATE_WAITING_FOR_COMPLETION;
				touch->delayCounter = 0;
			}
			break;

		case TOUCH_STATE_WAITING_FOR_COMPLETION:
			{
				if(AD1CON1bits.DONE == 1)
				{
					// Step 12 Disable the current source
					CTMUCON1Hbits.EDG1STAT = 0; // Disable current source
					IFS0bits.AD1IF = 0; // Clear ADC interrupt flag
					CTMUCON1Lbits.CTMUEN = 0; // Disable the CTMU
					touch->averageSum += ADC1BUF0;
					++touch->averageCount;
					if (touch->averageCount >= 8)
					{
						CurrentPinRegister->generic.buffer = touch->averageSum / 8;
						touch->averageSum = 0;
						touch->averageCount = 0;

						if (touch->digitalOutput)
						{
							touchProcessDigital();
						}
					}
					touch->delayCounter = 0;
					touch->state = TOUCH_STATE_IDLE;

					ADC1_Initialize();

                    TMR3_ResetConditions();
					T3CON = 0;
					ADC1Semaphore = RESOURCE_AVAILABLE;

					TMR3Semaphore = RESOURCE_AVAILABLE;
				}
                else
                {
                    ++touch->waitLimit;
                    if (touch->waitLimit >= 100){//This should happen in 1...
                        ADC1_Initialize();

                    TMR3_ResetConditions();
					ADC1Semaphore = RESOURCE_AVAILABLE;

					TMR3Semaphore = RESOURCE_AVAILABLE;
                    	touch->state = TOUCH_STATE_IDLE;
                        touch->waitLimit = 0;
                    }  
                        
                }
			}
	}
}


