/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    system.h

  @Summary:
    This is the sysetm.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC24FJ256GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
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

#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "crc.h"
#include "interrupt_manager.h"
#include "traps.h"
#include "dma.h"
#include "i2c2.h"
#include "i2c1.h"
#include "adc1.h"
#include "tmr2.h"
#include "tmr3.h"
#include "uart1.h"
#include "tmr1.h"
#include "uart2.h"
#include "cvr.h"
#include "memory/flash.h"
#include "pinDigitalHwSpecific.h"

/* 
 System peripherals:
 * 
 
 
 */
void SYSTEM_Initialize(void)
{
       
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    CLOCK_Initialize();
    UART2_Initialize();
  //  CVR_Initialize();
    CRC_Initialize();
    ADC1_Initialize();
      ANSELB = 0;  // No analogs to start
   ANSELA = 0x02;  // Make addr pin an analog
    
   // TMR3_Initialize();
    TMR2_Initialize();
    DMA_Initialize();
    TMR1_Initialize();  
    {
    uint16_t addressVoltage =   GetAddressPinVoltage_mV();
       extern uint8_t SW_I2CAddress;
    if (addressVoltage < 275)
    {
	extern uint8_t UART1Semaphore;
        SW_I2CAddress = 0;
  
        RPINR18bits.U1RXR = 0x0005;    //RB5->UART1:U1RX
        RPOR2bits.RP4R = 0x0003;    //RB4->UART1:U1TX
        UART1_Initialize();
        IPC3bits.U1TXIP = 1;
        IPC2bits.U1RXIP = 1;
        TRISBbits.TRISB4 = 0;
        UART1Semaphore = RESOURCE_USED_BY_SYSTEM;
    }
    else if (addressVoltage < 825) // 10k
    {
        SW_I2CAddress = 0x68;
         I2C2_Initialize();
    }
    else if (addressVoltage < 1375) //20 k
    {
        SW_I2CAddress = 0x69;
         I2C2_Initialize();
    }
     else if (addressVoltage < 1925)  //30 k
    {
        SW_I2CAddress = 0x6A;
         I2C2_Initialize();
    }
     else
     {
         SW_I2CAddress = 0x6B;
          I2C2_Initialize();
     }
    }
	  
	   //    I2C1_Initialize();
}

/**
 End of File
*/