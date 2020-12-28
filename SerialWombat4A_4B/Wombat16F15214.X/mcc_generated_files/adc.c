/**
  ADC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.c

  @Summary
    This is the generated driver implementation file for the ADC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15214
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB             :  MPLAB X 5.40
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc.h"
#include "device_config.h"
#include "serialWombat.h"

/**
  Section: Macro Declarations
*/

#define ACQ_US_DELAY 5


/**
  Section: ADC Module APIs
*/

void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // ADFM left; ADPREF VDD; ADCS FOSC/32; 
    ADCON1 = 0x20;
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // GO_nDONE stop; ADON enabled; CHS ANA0; 
    ADCON0 = 0x01;
    
}


#ifdef I2CWOMBAT
   #ifdef __16F15224__
   const uint8_t PinToADC [4] = {  0x13, //ANC3
                                   0x12, //ANC2
                                  0xFF, // No ADC
                                  0xFF,  //NoADC
                                   };
#endif
#ifdef __16F15214
   const uint8_t PinToADC [4] = {  0xFF, // No A/D
                                   2,
                                  1,
                                  0,
                                   };
   
   
#endif
#endif
   #ifdef UARTWOMBAT
   #ifdef __16F15224__
   const uint8_t PinToADC [4] = {  0x15,
                                   0x14, //ANC2
                                  0xFF, // No ADC
                                  0xFF,  //NoADC
                                   };
#endif
#ifdef __16F15214
   const uint8_t PinToADC [4] = {  5, 
                                   4,
                                  1,
                                  0,
                                   };
   
   
#endif
#endif
adc_result_t GetADCConversion(adc_channel_t channel)
{
    if (channel < 4)
    {
       
        if (PinToADC[channel] == 0xFF)
        {
            if (ReadPin(channel))
            {
                return (0xFFFF);
            }
            else
            {
                return (0);
            }
        }
        channel = PinToADC[channel];
    }
    
    // select the A/D channel
    ADCON0bits.CHS = channel;    
    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }

    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}


/**
 End of File
*/