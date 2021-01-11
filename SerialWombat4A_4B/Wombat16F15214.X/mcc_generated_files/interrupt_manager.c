/**
  Generated Interrupt Manager Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15214
        Driver Version    :  2.03
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above or later
        MPLAB 	          :  MPLAB X 5.40
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

#include "interrupt_manager.h"
#include "mcc.h"
#include "protocol.h"
#include "deviceSpecific.h"

uint8_t IOC_PortBuffer[IOC_BUFFER_SIZE];
uint16_t IOC_TimeBuffer[IOC_BUFFER_SIZE];
uint8_t IOC_PortSample;
uint16_t OverflowCount = 0;
__bit CaptureIOCTime = 0;
__bit IOC_Overflow = 0;
void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    
    if (PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1)
    {
        IOC_PortSample = WP_PORT;	
        WP_IOCF = 0;
        PIR0bits.IOCIF = 0;
      
            if (IOC_PortBuffer[0] & 0x80)
            {
                
            }
            else
            {
                IOC_Overflow = 1;
            }
        
        
        IOC_PortBuffer[0] = IOC_PortBuffer[1];
        IOC_PortBuffer[1] = IOC_PortBuffer[2];
        IOC_PortBuffer[2] = IOC_PortBuffer[3];
        IOC_PortBuffer[3] = IOC_PortBuffer[4];
        IOC_PortBuffer[4] = IOC_PortBuffer[5];
        IOC_PortBuffer[5] = IOC_PortBuffer[6];
        IOC_PortBuffer[6] = IOC_PortBuffer[7];
        IOC_PortBuffer[7] = IOC_PortSample;  
        if (CaptureIOCTime)
        {
        IOC_TimeBuffer[0] = IOC_TimeBuffer[1];
        IOC_TimeBuffer[1] = IOC_TimeBuffer[2];
        IOC_TimeBuffer[2] = IOC_TimeBuffer[3];
        IOC_TimeBuffer[3] = IOC_TimeBuffer[4]; 
        IOC_TimeBuffer[4] = IOC_TimeBuffer[5];
        IOC_TimeBuffer[5] = IOC_TimeBuffer[6];
        IOC_TimeBuffer[6] = IOC_TimeBuffer[7];
        *((uint8_t*)&IOC_TimeBuffer[7]) = TMR1L; 
        *(((uint8_t*)&IOC_TimeBuffer[7]) + 1) = TMR1H; 
        }
        return;
    }
    if (PIE1bits.CCP1IE == 1 && PIR1bits.CCP1IF == 1)
    {
        PIR1bits.CCP1IF = 0;
        WP_LAT &= CCP1SetLowMask;
        CCP1SetLowMask = 0xFF;
        PIE1bits.CCP1IE = 0;
        return;
    }
    #ifdef I2CWOMBAT
		 if(PIE1bits.BCL1IE == 1 && PIR1bits.BCL1IF == 1)
        {
             void I2C1_Isr(void);
            I2C1_Isr();
            return;
        } 
        else if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
        {
             void I2C1_Isr(void);
            I2C1_Isr();
            return;
        } 
        else
        {
            //Unhandled Interrupt
        }
#endif
    
    
   
        if(PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1)
        {
            void EUSART1_Receive_ISR(void);
            EUSART1_Receive_ISR();
            return;
        } 
        if(PIE1bits.TX1IE == 1 && PIR1bits.TX1IF == 1)
        {
            void EUSART1_Transmit_ISR(void);
            EUSART1_Transmit_ISR();
            return;
        } 
        

      
    if(PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1)
    {
        extern volatile bool RunForeground ;

// clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    // Write to the Timer0 register
     // TMR0H 224; 
    TMR0H = 0xE0;

    // TMR0L 192; 
    TMR0L = 0xC0;
    if (RunForeground )
    {
         FRAME_OVERFLOW_INDICATOR();
         if (OverflowCount < 65535)
         {
            ++OverflowCount;      
         }

    }
    RunForeground = true;
    }
    
    
}
/**
 End of File
*/
