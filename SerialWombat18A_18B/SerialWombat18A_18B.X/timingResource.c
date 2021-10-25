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
    TIMING_RESOURCE_MODE_t mode;
    uint8_t resourceHolder;    
    uint32_t period_uS;
    uint16_t highTime_uS;
    uint16_t lowTime_uS;
    uint16_t pwmDutyCycle;
}timingResourceManager_t;

timingResourceManager_t timingResources[TIMING_RESOURCE_NUMBER_OF_RESOURCES];

void timingResourceDefault(TIMING_RESOURCE_t resource)
{
        timingResources[resource].mode = TIMING_RESOURCE_MODE_IDLE;
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

		}
		break;


		case TIMING_RESOURCE_MCCP2:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP3:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP4:
		{

		}
		break;
*/

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

TIMING_RESOURCE_t timingResourceClaim(bool requireHardwareResource)
{
    uint8_t i;
    
    uint8_t last = TIMING_RESOURCE_NUMBER_OF_RESOURCES;
    if (requireHardwareResource)
    {
        --last;
    }
    for (i = 0; i < last; ++i)
    {
        if (timingResources[i].resourceHolder == 0xFF)
        {
            timingResources[i].resourceHolder = CurrentPin;
            return(i);
        }
    }
    return(TIMING_RESOURCE_NONE);
}

void timingResourceRelease()
{
    uint8_t i;
    
    if (pinIsPPSCapable(CurrentPin))
    {
        SetPPSOutput(CurrentPin,0);
    }
    for (i = 0; i < TIMING_RESOURCE_NUMBER_OF_RESOURCES; ++i)
    {
        if (timingResources[i].resourceHolder == CurrentPin)
        {
            timingResourceDefault(i);
        }
    }
}

void timingResourcesHighPulse(uint16_t pulseTime_uS)
{
    uint8_t i;
    uint8_t resource = 0xFF;
        for (i = 0; i < TIMING_RESOURCE_NUMBER_OF_RESOURCES; ++i)
    {
        if (timingResources[i].resourceHolder == CurrentPin)
        {
            resource = i;
        }
    }
    
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
		}
		break;


		case TIMING_RESOURCE_OC2:
		{
           
		}
		break;


		case TIMING_RESOURCE_OC3:
		{
            

		}
		break;

/*
		case TIMING_RESOURCE_MCCP1:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP2:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP3:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP4:
		{

		}
		break;
*/

		case TIMING_RESOURCE_PORT_DMA:
		{

		}
		break;

		default:
		{
            
        }
		break;
        
    }
}

bool timingResourceIsBusy()
{
       uint8_t i;
    uint8_t resource = 0xFF;
        for (i = 0; i < TIMING_RESOURCE_NUMBER_OF_RESOURCES; ++i)
    {
        if (timingResources[i].resourceHolder == CurrentPin)
        {
            resource = i;
        }
    }
    
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


		case TIMING_RESOURCE_MCCP2:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP3:
		{

		}
		break;


		case TIMING_RESOURCE_MCCP4:
		{

		}
		break;
*/

		case TIMING_RESOURCE_PORT_DMA:
		{
            return(0); //TODO
		}
		break;

		default:
            return(0);
		break;
        }
}