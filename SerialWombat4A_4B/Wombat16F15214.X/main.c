/**
  Generated Main Source File

Company:
Microchip Technology Inc.

File Name:
main.c

Summary:
This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

Description:
This header file provides implementations for driver APIs for all modules selected in the GUI.
Generation Information :
Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
Device            :  PIC16F15214
Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"

#include <stdint.h>
#include <stdbool.h>
#include "serialWombat.h"
volatile bool RunForeground = false;
volatile bool Sleep = false;
uint16_t FramesRun = 0;

void reset ()
{
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
}

pinRegister_t pinRegisterBuffer;


void main(void)
{
	// initialize the device
	SYSTEM_Initialize();
	CPCON = 0x80; // Enable analog charge pump
	WP_ANSEL = 0; // No Pins Analog
	WP_LAT = WP_LAT_INIT; //Initialize the LAT to all Low.  This is important for interrupt on change processing later, as we count on the non-implemented pins reading low.
	WP_TRIS = WP_TRIS_INIT; //Initialize the non-implemented pins to output.  This is important for interrupt on change processing later, as we count on the non-implemented pins reading low.

	//Manually initialize the PPS.  The PPS is set at power up, but not reset, so turn off any peripherals that were assigned to pins prior to reset.  Note that RA3 does not have a PPS, so we only initialize Wombat Pin 0 for UART Wombats, not I2C.
#ifdef UARTWOMBAT
	WP0_PPS = 0;
#endif
	WP1_PPS = 0;
	WP2_PPS = 0;
	WP3_PPS = 0;
	INTERRUPT_PeripheralInterruptEnable();
	INTERRUPT_GlobalInterruptEnable();
#ifdef I2CWOMBAT
	I2C1_Open();
#endif
    
    PinUpdateRegisters[0].generic.mode = 0;
	PinUpdateRegisters[1].generic.mode = 0;
    PinUpdateRegisters[2].generic.mode = 0;
    PinUpdateRegisters[3].generic.mode = 0;
    while (1)
	{
		ProcessRx();
		if (Sleep)
		{
			
#ifdef I2CWOMBAT
            extern volatile uint8_t i2cTxBufferCounter;
			while (i2cTxBufferCounter > 0);
#endif
#ifdef UARTWOMBAT
            uint8_t IOCNtemp, IOCPtemp;
            IOCNtemp = WP_IOCN;
            IOCPtemp = WP_IOCP;
            __delay_ms(15);
            WP_IOCN = 0x08; // Turn on IOC for RX Pin to wake us up.
            WP_IOCP = 0;
             WP_IOCF = 0;
            PIE0bits.IOCIE = 1;
#endif
			FVRCONbits.FVREN = 0;
			ADCON0bits.ON = 0;
			CPCONbits.CPON = 0;
            
			__delay_ms(5);
			SLEEP();
            
			FVRCONbits.FVREN = 1;
			ADCON0bits.ON = 1;
			CPCONbits.CPON = 1;
			Sleep = false;
#ifdef UARTWOMBAT
            WP_IOCN = IOCNtemp;  //Turn off IOC.
            WP_IOCP = IOCPtemp;
            __delay_ms(15);  //Wait a while for the rest of the packet to complete
            while (EUSART1_is_rx_ready()) // And throw away the data
        {
            EUSART1_Read();
		}
            extern uint8_t UartRxbufferCounter;
            UartRxbufferCounter = 0;
#endif
        }

		if (RunForeground)
		{
			FRAME_TIMING_HIGH();
			RunForeground = false;
            ++FramesRun;
			{
				void ProcessPins(void);
				ProcessPins();
			}
            void protocol_1ms();
            protocol_1ms();
			FRAME_TIMING_LOW();
		}
	}

}


/**
 End of File
*/
