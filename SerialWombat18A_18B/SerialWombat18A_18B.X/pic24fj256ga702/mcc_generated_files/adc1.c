
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC24FJ256GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "adc1.h"
#include "serialWombat.h"
/**
  Section: Driver Interface
*/

uint16_t VbgCalibration = 1200;  //Nominal value
volatile uint8_t CTMUTrim = 0xFF;
int16_t TemperatureCache = 2500;

void ADC1_ResetConditions(void)
{
    AD1CON1 = 0;
  AD1CON2 = 0;
  AD1CON3 = 0;
  AD1CON4 = 0;
  AD1CON5 = 0;
  AD1CSSH = 0;
  AD1CSSL = 0;
}

void ADC1_Initialize (void)
{ 					
    {  // Calibrate Vbg
    uint8_t tblpag = TBLPAG;
    TBLPAG = VBG_CAL_ADDRESS >> 16;
    uint16_t VbgStored  = __builtin_tblrdl((uint16_t)VBG_CAL_ADDRESS);
    TBLPAG = tblpag;
    if (VbgStored > 1000 && VbgStored < 1400)
    {
        VbgCalibration = VbgStored;
    }
    else if (VbgCalibration < 1000 || VbgCalibration > 1400)
    {
        VbgCalibration = 1200; // Nominal value
    }
    }
    
    if (CTMUTrim > 62)
    {  // Calibrate ITrim
    uint8_t tblpag = TBLPAG;
    TBLPAG = VBG_CAL_ADDRESS >> 16;

    //*((uint16_t*)&CTMUTrim)= __builtin_tblrdl((uint16_t)(VBG_CAL_ADDRESS + 2));
    CTMUTrim = (uint8_t) __builtin_tblrdl((uint16_t)(VBG_CAL_ADDRESS + 2));
    
    TBLPAG = tblpag;
    if (CTMUTrim >= 0 && CTMUTrim <= 62)
    {
       
    }
    else
    {
        CTMUTrim = 31; // Nominal value
    }
    }
    
    ADC1_ResetConditions();

AD1CON1 = 0x0670; // Internal counter triggers conversion, Unsigned Fraction, 12 bit
AD1CHS = 0x0000; // Connect AN0 as positive input
AD1CSSL = 0x03FF;  // Scan 0,1,2,3,4,5,6,7,8,9
AD1CSSH = 0x1000;  // Scan  28 (VBG)
AD1CON3 = 0x1F0A; // Sample time = 15Tad, Tad = Tcy
AD1CON2 = 0x0400 | ((11)<<2); // Continuous Scan, Set AD1IF after every 11 samples
AD1CON5 = 0x0000; // Autoscan.
AD1CON1bits.ADON = 1;
IFS0bits.AD1IF = 0;
IEC0bits.AD1IE = 1;
ANCFG |= 0x04; // Enable VBG for A/D
AD1CON1bits.ASAM = 1;  // auto start sampling for 31Tad

   
}

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADC1Interrupt ( void )
{
	if(IFS0bits.AD1IF)
	{
	
		// clear the ADC interrupt flag
		IFS0bits.AD1IF = false;
	}
}

uint16_t GetADCConversion(uint8_t pin)
{
	switch (pin)
	{
        

		case 0: return (ADC1BUF0);
        		//  ADDR PIN  return (ADC1BUF1);
		case 1: return (ADC1BUF2);
		case 2: return (ADC1BUF3);
		case 3: return (ADC1BUF4);
		case 4: return (ADC1BUF5);
		case 16: return (ADC1BUF8);
		case 17: return (ADC1BUF7);
		case 18: return (ADC1BUF6);
		case 19: return (ADC1BUF9);
	}
	if (ReadPin(pin))
	{
		return (0xFFFF);
	}
	else
	{
		return (0);
	}

}
volatile int32_t adc_i=0;
uint16_t GetAddressPinVoltage_mV()
{
    AD1CON1 = 0;
        AD1CON2 = 0;
        AD1CON3 = 0;
        AD1CON4 = 0;
        AD1CON5 = 0; 
        
        
        
    CTMUCON1Lbits.CTMUEN = 1;
    CTMUCON1Lbits.EDGEN = 0;
    CTMUCON1Lbits.IRNG = 3;
    CTMUCON1Hbits.IRNGH = 0;
    CTMUCON1Hbits.EDG1STAT = 1;
    CTMUCON1Hbits.EDG2STAT = 0;
    AD1CON5bits.CTMREQ =1;
        

        AD1CHS = 1; // Channel 1
        CTMUCON1Lbits.IDISSEN = 1;
        volatile uint32_t i;
        for (adc_i = 0; adc_i < 10000; ++adc_i)
        {
            
        }
        
        CTMUCON1Lbits.IDISSEN = 0;
        CTMUCON1Hbits.EDG2STAT = 0;

        AD1CON3 = 0x1FFF; // Sample time = 15Tad, Tad = Tcy
        AD1CON1bits.MODE12 = 1;  // Turn on 12 bit
        AD1CON1bits.FORM = 2; // Left Justified
        AD1CON1bits.SSRC = 0;  // manual end sampling 
        AD1CON1bits.ADON = 1; // Turn on A/D
        AD1CON1bits.SAMP = 1; //Start conversion.
          //Provide Delay
     
        for(i=0;i <10000;i++)
        {
        }
        AD1CON1bits.SAMP = 0; // End sampling
        while(AD1CON1bits.DONE == 0);

        uint32_t result = ADC1BUF0;      
        CTMUCON1L = 0 ;  //CTMU OFF
        result *= GetSourceVoltage_mV(); 
        result >>= 16;
        ADC1_Initialize();  // Put things back where we found them.
        return ( (uint16_t) result);    
  
    }

void GetCurrentPinReistanceOhmsSetup()
{
    if (WombatPinToADCChannel[CurrentPin] == 0xFF)
    {
        return;
    }
    AD1CON1 = 0;
        AD1CON2 = 0;
        AD1CON3 = 0;
        AD1CON4 = 0;
        AD1CON5 = 0; 
        
        
        
    CTMUCON1Lbits.CTMUEN = 1;
    CTMUCON1Lbits.EDGEN = 0;
    CTMUCON1Lbits.IRNG = 3;
    CTMUCON1Hbits.IRNGH = 0;
    CTMUCON1Hbits.EDG1STAT = 1;
    CTMUCON1Hbits.EDG2STAT = 0;
    AD1CON5bits.CTMREQ =1;
        

        AD1CHS = WombatPinToADCChannel[CurrentPin]; // Channel 1
     
        
        CTMUCON1Lbits.IDISSEN = 0;
        CTMUCON1Hbits.EDG2STAT = 0;
        CTMUCON1Lbits.ITRIM = CTMUTrim - 31;
        AD1CON3 = 0x9F0A;
        //AD1CON3 = 0x9F30; // Sample time = 15Tad, Tad = Tcy
       AD1CON1bits.MODE12 = 1;  // Turn on 12 bit
        AD1CON1bits.FORM = 2; // Left Justified
        AD1CON1bits.SSRC = 7;  // manual end sampling 
        AD1CON1bits.ADON = 1; // Turn on A/D
        AD1CON1bits.SAMP = 1; //Start conversion.
}
uint16_t GetCurrentPinReistanceOhmsRead(uint16_t sourceVoltagemV)
{
        
        while(AD1CON1bits.DONE == 0);

        uint32_t result = ADC1BUF0;      
        
        CTMUCON1L = 0 ;  //CTMU OFF
        result *= sourceVoltagemV; 
        result += 0x8000;
        result >>= 16;
        result *= 18182; // 1/ .000055 A
        result /= 1000;
        ADC1_Initialize();  // Put things back where we found them.
       
        return ( (uint16_t) result);    
  
    }
int16_t GetTemperature_degC100ths(bool corrected)
{
    if (ADC1Semaphore != RESOURCE_AVAILABLE )
    {
        return TemperatureCache;
    }
        int32_t Vref = GetSourceVoltage_mV();
         AD1CON1 = 0;
        AD1CON2 = 0;
        AD1CON3 = 0;
        AD1CON4 = 0;
        AD1CON5 = 0; 

        CTMUCON1L = 0x8003;  //CTMU ON, 55uA
        CTMUCON1H = 0; // Set both edgestat's to 0
        CTMUCON2L = 0;
        AD1CON5bits.CTMREQ = 1;
        AD1CHS = 14; // Die Temperature Conversion
        AD1CON3 = 0x1F20;
        //AD1CON3 = 0x1FFF; // Sample time = 15Tad, Tad = Tcy
        AD1CON1bits.MODE12 = 1;  // Turn on 12 bit
        AD1CON1bits.FORM = 2; // Left Justified
        AD1CON1bits.SSRC = 7;  // Auto Convert
        AD1CON1bits.ADON = 1; // Turn on A/D
        AD1CON1bits.SAMP = 1; //Start conversion.
        while(AD1CON1bits.DONE == 0);
        CTMUCON1L = 0 ;  //CTMU OFF
        volatile int32_t result = 0;
        result = ADC1BUF0;      
        result *= Vref; 
   
        result =  ((int32_t)760 * 65536) - result;
        result /= ((int32_t)(.0155 * 65535));
        TemperatureCache = result;
          
        if (corrected)
        {  // Get Temperature offset
              int16_t tReported, tActual;
    uint8_t tblpag = TBLPAG;
    TBLPAG = VBG_CAL_ADDRESS >> 16;

    *((uint16_t*)&tReported) = __builtin_tblrdl((uint16_t)(VBG_CAL_ADDRESS + 4) );
    *((uint16_t*)&tActual) = __builtin_tblrdl((uint16_t)(VBG_CAL_ADDRESS + 6) );
    TBLPAG = tblpag;
           TemperatureCache = result + (tActual-tReported);
    }

        ADC1_Initialize();  // Put things back where we found them.
        return ( TemperatureCache);    
}

uint16_t GetSourceVoltage_mV()
{
    uint16_t VrefADC = ADC1BUF10;
    
    uint32_t temp = 65536 * VbgCalibration;
    temp /= VrefADC;
    return ((uint16_t)temp);
}

uint16_t GetSourceVoltageADC()
{
    return (ADC1BUF10);
}

uint16_t GetVBgCountsVsVRefPin()
{
         AD1CON1 = 0;
        AD1CON2 = 0;
        AD1CON3 = 0;
        AD1CON4 = 0;
        AD1CON5 = 0; 
        
        
        
        ANSELA |= 0x0001; // Make VREF analog
        AD1CHS = 28; // VBG
        

        AD1CON3 = 0x1FFF; // Sample time = 15Tad, Tad = Tcy
        AD1CON1bits.MODE12 = 1;  // Turn on 12 bit
        AD1CON1bits.FORM = 0; // Left Justified
        AD1CON1bits.SSRC = 7;  // 
        AD1CON2bits.PVCFG = 1; // External Vref
        
        AD1CON1bits.ADON = 1; // Turn on A/D

        uint16_t result = 0;
        {
            uint8_t i;
        for (i = 0; i < 16; ++i)
        {
        AD1CON1bits.SAMP = 1;
        while(AD1CON1bits.DONE == 0);

        result += ADC1BUF0;      
        }
        }
        ADC1_Initialize();  // Put things back where we found them.
        return ( (uint16_t) result);    
}
/**
  End of File
*/
