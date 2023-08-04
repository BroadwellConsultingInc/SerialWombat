/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
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

/**
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    UERI: U1E - UART1 Error
    //    Priority: 1
 //BDB       IPC16bits.U1ERIP = 1;
    //    UTXI: U1TX - UART1 Transmitter
    //    Priority: 1
 //BDB           IPC3bits.U1TXIP = 1;
    //    URXI: U1RX - UART1 Receiver
    //    Priority: 1
 //BDB           IPC2bits.U1RXIP = 1;
    //    MICI: MI2C1 - I2C1 Master Events
    //    Priority: 1
  //BDB          IPC4bits.MI2C1IP = 1;
    //    SICI: SI2C1 - I2C1 Periph Events
    //    Priority: 1
 //BDB           IPC4bits.SI2C1IP = 1;
    //    DMA0I: DMA0 - Direct Memory Access 0
    //    Priority: 1
 //BDB           IPC1bits.DMA0IP = 1;
    //    TI: T2 - Timer2
    //    Priority: 1
  //BDB          IPC1bits.T2IP = 1;
    //    MICI: MI2C2 - I2C2 Master Events
    //    Priority: 1
  //BDB          IPC12bits.MI2C2IP = 1;
    //    SICI: SI2C2 - I2C2 Periph Events
    //    Priority: 1
  //BDB          IPC12bits.SI2C2IP = 1;
    IPC0bits.T1IP = 5; // Raise above default 4.  //TODO is this necessary or desirable?  I don't remember why I did this

}
