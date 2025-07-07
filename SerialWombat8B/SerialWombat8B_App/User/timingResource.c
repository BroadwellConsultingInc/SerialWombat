/*
Copyright 2021-2025 Broadwell Consulting Inc.

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
#include <stddef.h>

#include "serialWombat.h"
#include "debug.h"


TIMING_RESOURCE_t timingResourceHighPulseClaim(TIMING_RESOURCE_t resource, pulse_output_t* pulse)
{
	if (!pinIsPPSCapable(CurrentPin))
	{
		if (resource < TIMING_RESOURCE_PORT_DMA || resource == TIMING_RESOURCE_ANY_HARDWARE_OC)
		{
			return TIMING_RESOURCE_NONE;
		}
		else
		{
			initializeBitStreamOutput(CurrentPin,  0, &pulse->bitStream );
			return(TIMING_RESOURCE_PORT_DMA);
		}
	}

	return(TIMING_RESOURCE_NONE);
}

void timingResourcesHighPulse(pulse_output_t* pulse, uint16_t pulseTime_uS)
{
	pulse->highReload =
		(((uint32_t)pulseTime_uS) * DMA_FREQUENCY) / 1000000;
	pulse->lowReload = 65535;
	pulse->highRemaining = pulse->highReload;
	pulse->lowRemaining = pulse->lowReload;

}


void timingResourcePWM(pulse_output_t *pulse , uint32_t period_uS, uint16_t dutyCycle)
{



	period_uS *= 3775;
	period_uS += 0x8000; // Round up
	period_uS >>= 16;   // Fractional math instead of dividing by 57600 DMA rate

	uint32_t high = period_uS * dutyCycle;
	high >>= 16;
	if (dutyCycle == 0)
	{
	    pulse->lowReload = period_uS;
	    pulse->highReload = 0;
	}
	else if (dutyCycle == 65535)
    {
        pulse->lowReload = 0;
        pulse->highReload = period_uS;
    }
	else if (pulse->highReload != high ||
			pulse->lowReload != (period_uS - high) )
	{
		//    CurrentPinLow();  TODO commenting this out may break SW18AB
		pulse->highReload =
			high;
		pulse->lowReload = period_uS - high;
		if (pulse->highRemaining > pulse->highReload)
		{
			pulse->highRemaining = pulse->highReload;
		}
		if (pulse->lowRemaining >pulse->lowReload)
		{
			pulse->lowRemaining = pulse->lowReload;
		}
	}


}

bool timingResourceHighPulseBusy(pulse_output_t* pulse)
{

	if (pulse->highRemaining == 0 &&
			( pulse->lowRemaining < (pulse->lowReload - SIZE_OF_DMA_ARRAY) || (pulse->lowReload < SIZE_OF_DMA_ARRAY)))
	{
		return (false);
	}
	return (true);

}


void timingResourceBusyWait(uint16_t uS)
{

	//TODO
	/*
	   uint32_t end = TIM1->CNT + 12 * uS;

	   while (TIM1->CNT < end);
	   */

}




