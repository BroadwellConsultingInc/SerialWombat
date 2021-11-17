/*
Copyright 2021 Broadwell Consulting Inc.

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

typedef struct
{
    timingResourceCallback_t callBack;
    uint8_t resourceHolder;    
    uint32_t period_uS;
    uint16_t highTime_uS;
    uint16_t lowTime_uS;
    uint16_t pwmDutyCycle;
}timingResourceManager_t;

timingResourceManager_t timingResources[TIMING_RESOURCE_NUMBER_OF_RESOURCES];

void timingResourceDefault(TIMING_RESOURCE_t resource)
{
	timingResources[resource].resourceHolder = 0xFF;
	timingResources[resource].callBack = NULL;

	switch (resource)
	{
		case TIMING_RESOURCE_OC1:
			{
				OC1CON1 = 0;
				OC1CON2 = 0x000C;
				OC1TMR = 0;       
				IEC0bits.OC1IE = false;
				IFS0bits.OC1IF = false;
			}
			break;


		case TIMING_RESOURCE_OC2:
			{
				OC2CON1 = 0;
				OC2CON2 = 0x000C;
				OC2TMR = 0;       
				IEC0bits.OC2IE = false;
				IFS0bits.OC2IF = false;
			}
			break;


		case TIMING_RESOURCE_OC3:
			{
				OC3CON1 = 0;
				OC3CON2 = 0x000C;
				OC3TMR = 0;       
				IEC1bits.OC3IE = false;
				IFS1bits.OC3IF = false;

			}
			break;

			/*
			   case TIMING_RESOURCE_MCCP1:
			   {
			   CCP1CON1L = 0;
			   CCP1CON1H = 0;
			   CCP1CON2L = 0;
			   CCP1CON2H = 0x0100;
			   CCP1CON3L = 0;
			   CCP1CON3H = 0;
			   CCP1STATL = 0;
			   CCP1STATH = 0;
			   }
			   break;
			   */

		case TIMING_RESOURCE_MCCP2:
			{
				CCP2CON1L = 0;
				CCP2CON1H = 0;
				CCP2CON2L = 0;
				CCP2CON2H = 0x0100;
				CCP2CON3H = 0;
				CCP2STATL = 0;
				CCP2STATH = 0;
			}
			break;


		case TIMING_RESOURCE_MCCP3:
			{
				CCP3CON1L = 0;
				CCP3CON1H = 0;
				CCP3CON2L = 0;
				CCP3CON2H = 0x0100;
				CCP3CON3H = 0;
				CCP3STATL = 0;
				CCP3STATH = 0;
			}
			break;


		case TIMING_RESOURCE_MCCP4:
			{
				CCP4CON1L = 0;
				CCP4CON1H = 0;
				CCP4CON2L = 0;
				CCP4CON2H = 0x0100;
				CCP4CON3H = 0;
				CCP4STATL = 0;
				CCP4STATH = 0;
			}
			break;


		case TIMING_RESOURCE_PORT_DMA:
			{

			}
			break;

		default:

			break;
	}
}

void timingResourceManagerInit()
{
    uint8_t i;
    for (i = 0; i < TIMING_RESOURCE_NUMBER_OF_RESOURCES; ++i)
    {
        timingResourceDefault(i);      
    }
}

TIMING_RESOURCE_t timingResourceHighPulseClaim(TIMING_RESOURCE_t resource)
{
	uint8_t i;


	if (!pinIsPPSCapable(CurrentPin))
	{
		if (resource < TIMING_RESOURCE_PORT_DMA || resource == TIMING_RESOURCE_ANY_HARDWARE)
		{
			return TIMING_RESOURCE_NONE;
		}
		else
		{
			return(TIMING_RESOURCE_PORT_DMA);
		}
	}

	if (resource == TIMING_RESOURCE_PORT_DMA)
	{
		return(TIMING_RESOURCE_PORT_DMA);
	}

	//i = (TIMING_RESOURCE_PORT_DMA);
	for (i = 0; i < TIMING_RESOURCE_PORT_DMA; ++i)
	{
		if (timingResources[i].resourceHolder == 0xFF || i == TIMING_RESOURCE_PORT_DMA)
		{
			timingResources[i].resourceHolder = CurrentPin;
			return(i);
		}
	}
	return(TIMING_RESOURCE_NONE);
}

TIMING_RESOURCE_t timingResourcePWMClaim(TIMING_RESOURCE_t resource, uint32_t period_uS)
{
	uint8_t i;

   	if (resource == TIMING_RESOURCE_PORT_DMA)
	{
        //If they specifically want the DMA, give it to them.
		return(TIMING_RESOURCE_PORT_DMA);
	}

    if (!pinIsPPSCapable(CurrentPin))
	{
        // If we can't connect a timing resource to the current pin, give em a DMA port unless they
        // specifically call out hardware.
		if (resource < TIMING_RESOURCE_PORT_DMA || resource == TIMING_RESOURCE_ANY_HARDWARE)
		{
			return TIMING_RESOURCE_NONE;
		}
		else
		{
			return(TIMING_RESOURCE_PORT_DMA);
		}
	}
    
	if (period_uS > 65500)
	{
		return (TIMING_RESOURCE_PORT_DMA);  // Use software for long period PWM (up to 1.13 s)
	}

    else if (period_uS > 30000 || period_uS <= 2040)
    {
        // 30000 to 65500 uS period is capable on CCP2,3, and 4
        // CCP is better than OC at really fast as well (less than 2.04 mS,)
        // Because we can connect it to a faster clock
        if (timingResources[TIMING_RESOURCE_MCCP2].resourceHolder  == 0xFF ||
               timingResources[TIMING_RESOURCE_MCCP2].resourceHolder == CurrentPin )
        {
            timingResources[TIMING_RESOURCE_MCCP2].resourceHolder = CurrentPin;
            return (TIMING_RESOURCE_MCCP2);
        }
        if (timingResources[TIMING_RESOURCE_MCCP3].resourceHolder  == 0xFF ||
               timingResources[TIMING_RESOURCE_MCCP3].resourceHolder == CurrentPin )
        {
            timingResources[TIMING_RESOURCE_MCCP3].resourceHolder = CurrentPin;
            return (TIMING_RESOURCE_MCCP3);
        }
        if (timingResources[TIMING_RESOURCE_MCCP4].resourceHolder  == 0xFF ||
               timingResources[TIMING_RESOURCE_MCCP4].resourceHolder == CurrentPin )
        {
            timingResources[TIMING_RESOURCE_MCCP4].resourceHolder = CurrentPin;
            return (TIMING_RESOURCE_MCCP3);
        }
        
        
        if (period_uS > 30000)
        {
            // No CCP module was free.  Give 'em the DMA PORT because the
            // OC's can't create a longer period.
            return (TIMING_RESOURCE_PORT_DMA);
        }
    }
    
	


	for (i = 0; i < TIMING_RESOURCE_PORT_DMA; ++i)
	{
        // If we get to this point and we haven't picked an optimal resource, just give em whatever's free.
		if (timingResources[i].resourceHolder == 0xFF  || timingResources[i].resourceHolder == CurrentPin )
		{
			timingResources[i].resourceHolder = CurrentPin;
			return(i);
		}
	}
    
    // Nothing was free.
    if (resource == TIMING_RESOURCE_ANY_HARDWARE)
    {
        // They specifically didn't want DMA, so give em nothing.
        return(TIMING_RESOURCE_NONE);
    }
    
    // Otherwise, you can always fall back on the good old DMA.
    return (TIMING_RESOURCE_PORT_DMA);
    
}

void timingResourceRelease(TIMING_RESOURCE_t resource)
{
	uint8_t i;

	if (pinIsPPSCapable(CurrentPin))
	{
		SetPPSOutput(CurrentPin,0);
	}

	if (resource == TIMING_RESOURCE_ALL)
	{
		for (i = 0; i < TIMING_RESOURCE_NUMBER_OF_RESOURCES; ++i)
		{
			if (timingResources[i].resourceHolder == CurrentPin)
			{
				timingResourceDefault(i);
			}
		}
	}
	else if (resource < TIMING_RESOURCE_PORT_DMA)
	{
		timingResourceDefault(resource);
	}
}

void timingResourcesHighPulse(TIMING_RESOURCE_t resource, uint16_t pulseTime_uS)
{


	switch (resource)
	{
		case TIMING_RESOURCE_OC1:
			{
				OC1CON1 = 0x1C00;
				OC1CON2 = 0x0000;
				OC1RS = 0x00;
				OC1R = pulseTime_uS * 16;
				OC1TMR = 0;       
				IFS0bits.OC1IF = false;
				IEC0bits.OC1IE = false;
				OC1CON1 = 0x1C02;
				SetPPSOutput(CurrentPin,13);  // Connect pin to OC1
			}
			break;


		case TIMING_RESOURCE_OC2:
			{
				OC2CON1 = 0x1C00;
				OC2CON2 = 0x0000;
				OC2RS = 0x00;
				OC2R = pulseTime_uS * 16;
				OC2TMR = 0;       
				IFS0bits.OC2IF = false;
				IEC0bits.OC2IE = false;
				OC2CON1 = 0x1C02;
				SetPPSOutput(CurrentPin,14);  // Connect pin to OC2

			}
			break;


		case TIMING_RESOURCE_OC3:
			{
				OC3CON1 = 0x1C00;
				OC3CON2 = 0x0000;
				OC3RS = 0x00;
				OC3R = pulseTime_uS * 16;
				OC3TMR = 0;       
				IFS1bits.OC3IF = false;
				IEC1bits.OC3IE = false;
				OC3CON1 = 0x1C02;
				SetPPSOutput(CurrentPin,15);  // Connect pin to OC2
			}
			break;

		case TIMING_RESOURCE_MCCP2:
			{
				CCP2CON1L = 0x0000;
				CCP2TMRL = 0;
				CCP2RAL = pulseTime_uS * 16;
				SetPPSOutput(CurrentPin,16); //CCP2A Output
				CCP2STATL = 0; // Clear SCEVT
				CCP2CON1L = 0x8002;
			}
			break;


		case TIMING_RESOURCE_MCCP3:
			{
				CCP3CON1L = 0x0000;
				CCP3TMRL = 0;
				CCP3RAL = pulseTime_uS * 16;
				SetPPSOutput(CurrentPin,18); //CCP3A Output
				CCP3STATL = 0; // Clear SCEVT
				CCP3CON1L = 0x8002;
			}
			break;


		case TIMING_RESOURCE_MCCP4:
			{
				CCP4CON1L = 0x0000;
				CCP4TMRL = 0;
				CCP4RAL = pulseTime_uS * 16;               
				SetPPSOutput(CurrentPin,20); //CCP2A Output
				CCP4STATL = 0; // Clear SCEVT
				CCP4CON1L = 0x8002;
			}
			break;


		case TIMING_RESOURCE_PORT_DMA:
			{
				CurrentPinRegister->pulse_output.highReload = 
					(((uint32_t)pulseTime_uS) * DMA_FREQUENCY) / 1000000;
				CurrentPinRegister->pulse_output.lowReload = 65534;
				CurrentPinRegister->pulse_output.highRemaining = 0;
				CurrentPinRegister->pulse_output.lowRemaining = 0;
				SetPPSOutput(CurrentPin,0); 

			}
			break;

		default:
			{

			}
			break;

	}
}

void timingResourcePWM(TIMING_RESOURCE_t resource, uint32_t period_uS, uint16_t dutyCycle)
{
	switch (resource)
	{

		case TIMING_RESOURCE_OC1:
			{

				if (dutyCycle == 0)
				{
					CurrentPinLow();
				}
				else if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					if (period_uS <= 3000 )
					{
						period_uS *= 16;
						uint32_t highTime = period_uS * dutyCycle;
						highTime >>= 16;

						if ((OC1CON2 & 0x1F) == 0x1F && OC1RS == period_uS && OC1R == highTime && (OC1CON1 & 0x1C07) == 0x1C06)
						{

						}
						else
						{
							OC1CON2 = 0x0000 | 0x1F;
							OC1RS = period_uS;
							OC1R = highTime;
							IFS0bits.OC1IF = false;
							IEC0bits.OC1IE = false;
							OC1CON1 = 0x1C06;
						}
					}
					else if (period_uS <= 30000)
					{
						period_uS *= 2;
						uint32_t highTime = period_uS * dutyCycle;
						highTime >>= 16;

						if ((OC1CON2 & 0x1F) == 0x1F && OC1RS == period_uS && OC1R == highTime && (OC1CON1 & 0x1C07) == 0x0006)
						{

						}
						else
						{
							OC1CON2 = 0x0000 | 0x1F;
							OC1RS = period_uS;
							OC1R = highTime;
							//OC1TMR = 0;       
							IFS0bits.OC1IF = false;
							IEC0bits.OC1IE = false;
							OC1CON1 = 0x0006;
						}
					}
					SetPPSOutput(CurrentPin,13);  // Connect pin to OC1
				}
			}
			break;


		case TIMING_RESOURCE_OC2:
			{
				if (dutyCycle == 0)
				{
					CurrentPinLow();
				}
				else if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					if (period_uS <= 3000 )
					{
						period_uS *= 16;
						uint32_t highTime = period_uS * dutyCycle;
						highTime >>= 16;

						if ((OC2CON2 & 0x1F) == 0x1F && OC2RS == period_uS && OC2R == highTime && (OC2CON1 & 0x1C07) == 0x1C06)
						{

						}
						else
						{
							OC2CON2 = 0x0000 | 0x1F;
							OC2RS = period_uS;
							OC2R = highTime;
							//OC1TMR = 0;       
							IFS0bits.OC2IF = false;
							IEC0bits.OC2IE = false;
							OC2CON1 = 0x1C06;
						}
						SetPPSOutput(CurrentPin,14);  // Connect pin to OC1
					}
					else if (period_uS <= 30000)
					{
						period_uS *= 2;
						uint32_t highTime = period_uS * dutyCycle;
						highTime >>= 16;

						if ((OC2CON2 & 0x1F) == 0x1F &&
								OC2RS == period_uS &&
								OC2R == highTime &&
								(OC2CON1 & 0x1C07) == 0x0006)
						{

						}
						else
						{
							OC2CON2 = 0x0000 | 0x1F;
							OC2RS = period_uS;
							OC2R = highTime;
							//OC1TMR = 0;       
							IFS0bits.OC2IF = false;
							IEC0bits.OC2IE = false;
							OC2CON1 = 0x0006;
						}
						SetPPSOutput(CurrentPin,14);  // Connect pin to OC1
					}
				}

			}
			break;


		case TIMING_RESOURCE_OC3:
			{
				if (dutyCycle == 0)
				{
					CurrentPinLow();
				}
				else if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					if (period_uS <= 3000 )
					{
						period_uS *= 16;
						uint32_t highTime = period_uS * dutyCycle;
						highTime >>= 16;

						if ((OC3CON2 & 0x1F) == 0x1F &&
								OC3RS == period_uS &&
								OC3R == highTime &&
								(OC3CON1 & 0x1C07) == 0x1C06)
						{

						}
						else
						{
							OC3CON2 = 0x0000 | 0x1F;
							OC3RS = period_uS;
							OC3R = highTime;
							//OC1TMR = 0;       
							IFS1bits.OC3IF = false;
							IEC1bits.OC3IE = false;
							OC3CON1 = 0x1C06;
						}
						SetPPSOutput(CurrentPin,15);  // Connect pin to OC3
					}
					else if (period_uS <= 30000)
					{
						period_uS *= 2;
						uint32_t highTime = period_uS * dutyCycle;
						highTime >>= 16;

						if ((OC3CON2 & 0x1F) == 0x1F &&
								OC3RS == period_uS &&
								OC3R == highTime &&
								(OC3CON1 & 0x1C07) == 0x0006)
						{

						}
						else
						{
							OC3CON2 = 0x0000 | 0x1F;



							OC3RS = period_uS;
							OC3R = highTime;
							//OC1TMR = 0;       
							IFS1bits.OC3IF = false;
							IEC1bits.OC3IE = false;
							OC3CON1 = 0x0006;
						}
						SetPPSOutput(CurrentPin,15);  // Connect pin to OC3
					}
				}
			}
			break;


		case TIMING_RESOURCE_MCCP2:
			{
				if (dutyCycle == 0)
				{
					CurrentPinLow();
				}
				else if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					if (period_uS <= 2040 )
					{
						period_uS *= 32;
						if (CCP2CON1L != 0x8405 || CCP2RA != 0 || CCP2PRL != period_uS)
						{
							CCP2CON1L = 0x0000;
							CCP2TMRL = 0;
							CCP2RA = 0;
							CCP2PRL = period_uS;             
							CCP2CON1L = 0x8405;
						}
					}
					else if (period_uS <= 4040 )
					{
						period_uS *= 16;
						if (CCP2CON1L != 0x8005 ||	CCP2RA != 0 ||	CCP2PRL != period_uS)
						{
							CCP2CON1L = 0x0000;
							CCP2TMRL = 0;
							CCP2RA = 0;
							CCP2PRL = period_uS;             
							CCP2CON1L = 0x8005;
						}
					}
					else if (period_uS <= 16300 )
					{
						period_uS *= 4;
						if (CCP2CON1L != 0x8045 || CCP2RA != 0 || CCP2PRL != period_uS)
						{
							CCP2CON1L = 0x0000;
							CCP2TMRL = 0;
							CCP2RA = 0;
							CCP2PRL = period_uS;             
							CCP2CON1L = 0x8045;
						}
					}
					else if (period_uS <= 65000 )
					{
						if (CCP2CON1L != 0x8085 ||	CCP2RA != 0 ||	CCP2PRL != period_uS)
						{
							CCP2CON1L = 0x0000;
							CCP2TMRL = 0;
							CCP2RA = 0;
							CCP2PRL = period_uS;             
							CCP2CON1L = 0x8085;
						}
					}
					uint32_t highTime = ((uint32_t) CCP2PRL) * dutyCycle;
					highTime >>= 16;
					CCP2RB = highTime;
                        SetPPSOutput(CurrentPin,16);  // Connect pin to CCP2
				}
			}
			break;


		case TIMING_RESOURCE_MCCP3:
			{
                if (dutyCycle == 0)
				{
					CurrentPinLow();
				}
				else if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					if (period_uS <= 2040 )
					{
						period_uS *= 32;
						if (CCP3CON1L != 0x8405 || CCP3RA != 0 || CCP3PRL != period_uS)
						{
							CCP3CON1L = 0x0000;
							CCP3TMRL = 0;
							CCP3RA = 0;
							CCP3PRL = period_uS;             
							CCP3CON1L = 0x8405;
						}
					}
					else if (period_uS <= 4040 )
					{
						period_uS *= 16;
						if (CCP3CON1L != 0x8005 ||	CCP3RA != 0 ||	CCP3PRL != period_uS)
						{
							CCP3CON1L = 0x0000;
							CCP3TMRL = 0;
							CCP3RA = 0;
							CCP3PRL = period_uS;             
							CCP3CON1L = 0x8005;
						}
					}
					else if (period_uS <= 16300 )
					{
						period_uS *= 4;
						if (CCP3CON1L != 0x8045 || CCP3RA != 0 || CCP3PRL != period_uS)
						{
							CCP3CON1L = 0x0000;
							CCP3TMRL = 0;
							CCP3RA = 0;
							CCP3PRL = period_uS;             
							CCP3CON1L = 0x8045;
						}
					}
					else if (period_uS <= 65000 )
					{
						if (CCP3CON1L != 0x8085 ||	CCP3RA != 0 ||	CCP3PRL != period_uS)
						{
							CCP3CON1L = 0x0000;
							CCP3TMRL = 0;
							CCP3RA = 0;
							CCP3PRL = period_uS;             
							CCP3CON1L = 0x8085;
						}
					}
					uint32_t highTime = ((uint32_t) CCP3PRL) * dutyCycle;
					highTime >>= 16;
					CCP3RB = highTime;
                    SetPPSOutput(CurrentPin,18);  // Connect pin to CCP3
				}
			}
			break;


		case TIMING_RESOURCE_MCCP4:
			{
                if (dutyCycle == 0)
				{
					CurrentPinLow();
				}
				else if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					if (period_uS <= 2040 )
					{
						period_uS *= 32;
						if (CCP4CON1L != 0x8405 || CCP4RA != 0 || CCP4PRL != period_uS)
						{
							CCP4CON1L = 0x0000;
							CCP4TMRL = 0;
							CCP4RA = 0;
							CCP4PRL = period_uS;             
							CCP4CON1L = 0x8405;
						}
					}
					else if (period_uS <= 4040 )
					{
						period_uS *= 16;
						if (CCP4CON1L != 0x8005 ||	CCP4RA != 0 ||	CCP4PRL != period_uS)
						{
							CCP4CON1L = 0x0000;
							CCP4TMRL = 0;
							CCP4RA = 0;
							CCP4PRL = period_uS;             
							CCP4CON1L = 0x8005;
						}
					}
					else if (period_uS <= 16300 )
					{
						period_uS *= 4;
						if (CCP4CON1L != 0x8045 || CCP4RA != 0 || CCP4PRL != period_uS)
						{
							CCP4CON1L = 0x0000;
							CCP4TMRL = 0;
							CCP4RA = 0;
							CCP4PRL = period_uS;             
							CCP4CON1L = 0x8045;
						}
					}
					else if (period_uS <= 65000 )
					{
						if (CCP4CON1L != 0x8085 ||	CCP4RA != 0 ||	CCP4PRL != period_uS)
						{
							CCP4CON1L = 0x0000;
							CCP4TMRL = 0;
							CCP4RA = 0;
							CCP4PRL = period_uS;             
							CCP4CON1L = 0x8085;
						}
					}
					uint32_t highTime = ((uint32_t) CCP4PRL) * dutyCycle;
					highTime >>= 16;
					CCP4RB = highTime;
                    SetPPSOutput(CurrentPin,20);  // Connect pin to CCP4
				}
			}
			break;

		case TIMING_RESOURCE_PORT_DMA:
			{
				if (dutyCycle == 0xFFFF)
				{
					CurrentPinHigh();
				}
				else
				{
					CurrentPinLow();
					period_uS *= 3775;
					period_uS += 0x8000; // Round up
					period_uS >>= 16;   // Fractional math instead of dividing by 57600 DMA rate

					uint32_t high = period_uS * dutyCycle;
					high >>= 16;

					CurrentPinRegister->pulse_output.highReload = 
						high;
					CurrentPinRegister->pulse_output.lowReload = period_uS - high;
					if (CurrentPinRegister->pulse_output.highRemaining > CurrentPinRegister->pulse_output.highReload)
					{
						CurrentPinRegister->pulse_output.highRemaining = CurrentPinRegister->pulse_output.highReload;
					}
					if (CurrentPinRegister->pulse_output.lowRemaining > CurrentPinRegister->pulse_output.lowReload)
					{
						CurrentPinRegister->pulse_output.lowRemaining = CurrentPinRegister->pulse_output.lowReload;
					}
				}

			}
			break;

		default:
			{

			}
			break;

	}
}
bool timingResourceHighPulseBusy(TIMING_RESOURCE_t resource)
{
	

	switch (resource)
	{
		case TIMING_RESOURCE_OC1:
			{
				return(! IFS0bits.OC1IF);
			}
			break;


		case TIMING_RESOURCE_OC2:
			{
				return(! IFS0bits.OC2IF);
			}
			break;


		case TIMING_RESOURCE_OC3:
			{
				return(! IFS1bits.OC3IF);
			}
			break;

			/*
			   case TIMING_RESOURCE_MCCP1:
			   {

			   }
			   break;

*/
			   case TIMING_RESOURCE_MCCP2:
			   {
                    return (!CCP2STATLbits.SCEVT );
			   }
			   break;


			   case TIMING_RESOURCE_MCCP3:
			   {
                    return (!CCP3STATLbits.SCEVT );
			   }
			   break;


			   case TIMING_RESOURCE_MCCP4:
			   {
                     return (!CCP4STATLbits.SCEVT );
			   }
			   break;
	

		case TIMING_RESOURCE_PORT_DMA:
			{
				
                        if (CurrentPinRegister->pulse_output.highRemaining == 0 &&
                                CurrentPinRegister->pulse_output.lowRemaining < 65400)
                        {
                            return (false);
                        }
                        return (true);
        }
    }
    return(false);
}

bool timingResourceService(TIMING_RESOURCE_t resource)
{
   

	switch (resource)
	{
        case TIMING_RESOURCE_PORT_DMA:
        {
            updatePulseOutput(CurrentPin);
        }
    }
    return true;
}

TIMING_RESOURCE_t timingResourceInterruptClaim(TIMING_RESOURCE_t resource, uint16_t counts, uint16_t uS, timingResourceCallback_t callback)
{
    // If they asked for something specific, give them that if possible.
    if (resource < TIMING_RESOURCE_PORT_DMA)
    {
        if (timingResources[resource].resourceHolder == 0xFF  || timingResources[resource].resourceHolder == CurrentPin)
    {
       timingResources[resource].resourceHolder = CurrentPin;
       timingResources[resource].callBack = callback;
       timingResources[resource].period_uS = uS;
       timingResources[resource].highTime_uS = counts;
       return (resource);
    }
        return (TIMING_RESOURCE_NONE);
    }
    
    // We can't tie CCP1 to a pin via PPS, so it's a good first choice to use for interrupts.  Use that
    // if it's free.
    if (timingResources[TIMING_RESOURCE_MCCP1].resourceHolder == 0xFF  || timingResources[TIMING_RESOURCE_MCCP1].resourceHolder == CurrentPin)
    {
       timingResources[TIMING_RESOURCE_MCCP1].resourceHolder = CurrentPin;
       timingResources[TIMING_RESOURCE_MCCP1].callBack = callback;
       timingResources[TIMING_RESOURCE_MCCP1].period_uS = uS;
       timingResources[TIMING_RESOURCE_MCCP1].highTime_uS = counts;
       return (TIMING_RESOURCE_MCCP1);
    }
    
    //  The OC modules are less flexible than the CCP modules in terms of frequency
    // so use one of those if possbile.
    uint16_t i;
        for (i = TIMING_RESOURCE_OC1; i < TIMING_RESOURCE_PORT_DMA; ++i)
		{
			if (timingResources[i].resourceHolder == 0xFF)
			{
				timingResourceDefault(i);
                timingResources[i].resourceHolder = CurrentPin;
       timingResources[i].callBack = callback;
       timingResources[i].period_uS = uS;
       timingResources[i].highTime_uS = counts;
                return (i);
			}
		}
    
     // If not, then see if one of the CCP's is avaialable
     for (i = 0; i < TIMING_RESOURCE_OC1; ++i)
		{
			if (timingResources[i].resourceHolder == 0xFF)
			{
				timingResourceDefault(i);
                timingResources[i].resourceHolder = CurrentPin;
       timingResources[i].callBack = callback;
       timingResources[i].period_uS = uS;
       timingResources[i].highTime_uS = counts;
                return (i);
			}
		}
    
    
    // Nothing is avaiable at this time.
    return(TIMING_RESOURCE_NONE);
}


void timingResourceInterruptActivate(TIMING_RESOURCE_t resource)
{
    switch (resource)
    {
        case TIMING_RESOURCE_MCCP1:
        {
            CCP1CON1L = 0;
            CCP1TMRL = 0;
            IFS6bits.CCT1IF = 0;
            CCP1PRL = timingResources[TIMING_RESOURCE_MCCP1].highTime_uS;
            CCP1CON1L = 0x8000;
            IEC6bits.CCT1IE = 1;
        }
        break;
        
        case TIMING_RESOURCE_MCCP2:
        {
            CCP2CON1L = 0;
            CCP2TMRL = 0;
            IFS6bits.CCT2IF = 0;
            CCP2PRL = timingResources[TIMING_RESOURCE_MCCP2].highTime_uS;
            CCP2CON1L = 0x8000;
            IEC6bits.CCT2IE = 1;
        }
        break;
        
        case TIMING_RESOURCE_MCCP3:
        {
            CCP3CON1L = 0;
            CCP3TMRL = 0;
            IFS2bits.CCT3IF = 0;
            CCP3PRL = timingResources[TIMING_RESOURCE_MCCP3].highTime_uS;
            CCP3CON1L = 0x8000;
            IEC2bits.CCT3IE = 1;
        }
        break;
        
        case TIMING_RESOURCE_MCCP4:
        {
            CCP4CON1L = 0;
            CCP4TMRL = 0;
            IFS2bits.CCT4IF = 0;
            CCP4PRL = timingResources[TIMING_RESOURCE_MCCP4].highTime_uS;
            CCP4CON1L = 0x8000;
            IEC2bits.CCT4IE = 1;
        }
        break;
        
         case TIMING_RESOURCE_OC1:
        {
                 OC1CON1 = 0x1C00;
				OC1CON2 = 0x0000;
				OC1RS = 0x00;
				OC1R = timingResources[TIMING_RESOURCE_OC1].highTime_uS;
				OC1TMR = 0;       
				IFS0bits.OC1IF = 0;
				IEC0bits.OC1IE = 1;
				OC1CON1 = 0x1C02;
				
        }
        break;
         case TIMING_RESOURCE_OC2:
        {
                 OC1CON1 = 0x1C00;
				OC1CON2 = 0x0000;
				OC1RS = 0x00;
				OC1R = timingResources[TIMING_RESOURCE_OC2].highTime_uS;
				OC1TMR = 0;       
				IFS0bits.OC1IF = 0;
				IEC0bits.OC1IE = 1;
				OC1CON1 = 0x1C02;
				
        }
        break;

         case TIMING_RESOURCE_OC3:
        {
                 OC3CON1 = 0x1C00;
				OC3CON2 = 0x0000;
				OC3RS = 0x00;
				OC3R = timingResources[TIMING_RESOURCE_OC3].highTime_uS;
				OC3TMR = 0;       
				IFS1bits.OC3IF = 0;
				IEC1bits.OC3IE = 1;
				OC3CON1 = 0x1C02;
				
        }
        break;

    }
}


volatile uint16_t CCT1InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT1Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_MCCP1].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_MCCP1].callBack();
    }
    IFS6bits.CCT1IF = 0;
    IEC6bits.CCT1IE = 0;
    ++ CCT1InterruptCount;
    timingResources[TIMING_RESOURCE_MCCP1].resourceHolder = 0xFF;
}

volatile uint16_t CCT2InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT2Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_MCCP2].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_MCCP2].callBack();
    }
    IFS6bits.CCT2IF = 0;
    IEC6bits.CCT2IE = 0;
    ++ CCT2InterruptCount;
    timingResources[TIMING_RESOURCE_MCCP2].resourceHolder = 0xFF;
}

volatile uint16_t CCT3InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT3Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_MCCP3].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_MCCP3].callBack();
    }
    IFS2bits.CCT3IF = 0;
    IEC2bits.CCT3IE = 0;
    ++ CCT3InterruptCount;
    timingResources[TIMING_RESOURCE_MCCP3].resourceHolder = 0xFF;
}

volatile uint16_t CCT4InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT4Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_MCCP4].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_MCCP4].callBack();
    }
    IFS2bits.CCT4IF = 0;
    IEC2bits.CCT4IE = 0;
    ++ CCT4InterruptCount;
    timingResources[TIMING_RESOURCE_MCCP4].resourceHolder = 0xFF;
}

volatile uint16_t OC1InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _OC1Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_OC1].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_OC1].callBack();
    }
    IFS0bits.OC1IF = 0;
	IEC0bits.OC1IE = 0;
    ++ OC1InterruptCount;
    timingResources[TIMING_RESOURCE_OC1].resourceHolder = 0xFF;
}

volatile uint16_t OC2InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _OC2Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_OC2].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_OC2].callBack();
    }
    IFS0bits.OC2IF = 0;
	IEC0bits.OC2IE = 0;
    ++ OC2InterruptCount;
    timingResources[TIMING_RESOURCE_OC2].resourceHolder = 0xFF;
}

volatile uint16_t OC3InterruptCount = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _OC3Interrupt (  )
{
    
    if (timingResources[TIMING_RESOURCE_OC3].callBack != NULL)
    {
        timingResources[TIMING_RESOURCE_OC3].callBack();
    }
    IFS1bits.OC3IF = 0;
	IEC1bits.OC3IE = 0;
    ++ OC3InterruptCount;
    timingResources[TIMING_RESOURCE_OC3].resourceHolder = 0xFF;
}