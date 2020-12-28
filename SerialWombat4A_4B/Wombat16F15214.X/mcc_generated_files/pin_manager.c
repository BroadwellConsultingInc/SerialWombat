/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15214
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB             :  MPLAB X 5.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"
#include "deviceSpecific.h"




void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x3B;

#ifdef UARTWOMBAT
    TX_TRISBIT = 0;
#endif
    
    /**
    ANSELx registers
    */
    ANSELA = 0;

#ifdef __16F15224__
    ANSELC = 0;
#endif
    /**
    WPUx registers
    */
    WPUA = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
#ifdef UARTWOMBAT
    RX1PPS = RX_PPS_SOURCE;   //RA3->EUSART1:RX1;    
    TX_PPS_REGISTER = 0x05;   //RA2->EUSART1:TX1;    
#endif
    
    

#ifdef I2CWOMBAT    
    WP_ODCON = 0x30; // Pins 4 and 5 Open drain for I2C
    SSP1CLKPPS = I2C_PPS_SCL_IN;   //RA4->MSSP1:SCL1;    
    I2C_PPS_SCL_OUT = 0x07;   //RA4->MSSP1:SCL1;    
    I2C_PPS_SDA_OUT = 0x08;   //RA2->MSSP1:SDA1;    
    SSP1DATPPS = I2C_PPS_SDA_IN;   //RA2->MSSP1:SDA1;    
#endif
}
  

/**
 End of File
*/