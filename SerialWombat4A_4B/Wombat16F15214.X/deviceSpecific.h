/*
Copyright 2020 Broadwell Consulting Inc.

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

#ifndef DEVICE_SPECIFIC_H
#define DEVICE_SPECIFIC_H
#include <xc.h> 
#include "mcc_generated_files/mcc.h"

#define JOIN3(_a,_b,_c) JOIN(_a,JOIN(_b,_c))
#define JOIN(_a,_b) JOIN_AGAIN(_a,_b)
#define JOIN_AGAIN(_a,_b) _a ## _b



#define NUMBER_OF_PHYSICAL_PINS 4
#define NUMBER_OF_VIRTUAL_PINS 0
#define NUMBER_OF_TOTAL_PINS (NUMBER_OF_PHYSICAL_PINS + NUMBER_OF_VIRTUAL_PINS)

#ifdef I2CWOMBAT
#define SERIAL_WOMBAT_HARDWARE_IDENTIFIER 'B'
#endif
#ifdef UARTWOMBAT
#define SERIAL_WOMBAT_HARDWARE_IDENTIFIER 'A'
#endif

#define ADC_MAX_COUNTS 0xFFC0

#define SIZE_OF_USER_BUFFER 0

#define IOC_BUFFER_SIZE 8
#include "pinDigitalHwSpecific.h"

extern volatile uint8_t CCP1SetLowMask;
void SetLowMaskCurrentPin();

#ifdef __16F15224__
#define RX_PPS_SOURCE 0x13 //RC3
#define TX_PPS_REGISTER RC2PPS
#define TX_TRISBIT TRISCbits.TRISC2
#define PPS_PORT 0x10
#define PPS_ARRAY (&RC0PPS)
#define I2C_PPS_SCL_IN 0x14
#define I2C_PPS_SCL_OUT  RC4PPS

#define I2C_PPS_SDA_OUT RC5PPS
#define I2C_PPS_SDA_IN 0x15

#define WP_TRIS TRISC
#define WP_TRIS_INIT 0x3F // Set upper 2 pins (not wired) to Output
#define WP_LAT LATC
#define WP_LAT_INIT 0 // All pins low, including non-wired pins
#define WP_PORT PORTC
#define WP_ANSEL ANSELC
#define WP_WPU WPUC
#define WP_ODCON ODCONC
#ifdef UARTWOMBAT
#define WP0_PPS RC5PPS
#define WP1_PPS RC4PPS
#define WP2_PPS RC1PPS
#define WP3_PPS RC0PPS
#define WP0_PORTPINNUM 5
#define WP1_PORTPINNUM 4
#define WP2_PORTPINNUM 1
#define WP3_PORTPINNUM 0
#endif
#ifdef I2CWOMBAT
#define WP0_PPS RC3PPS
#define WP1_PPS RC2PPS
#define WP2_PPS RC1PPS
#define WP3_PPS RC0PPS
#endif
#define WP_IOCN IOCCN
#define WP_IOCP IOCCP
#define WP_IOCF IOCCF
#define FRAME_TIMING_HIGH() {ANSELA = 0; TRISAbits.TRISA5 = 0; LATAbits.LATA5 = 1;}
#define FRAME_TIMING_LOW() {TRISAbits.TRISA5 = 0; LATAbits.LATA5 = 0;}
#define FRAME_OVERFLOW_INDICATOR() {TRISAbits.TRISA4 = 0; LATAbits.LATA4 = ~LATAbits.LATA4;}
#elif defined __16F15214__

#define RX_PPS_SOURCE 0x03 //RA3
#define TX_PPS_REGISTER RA2PPS
#define TX_TRISBIT TRISAbits.TRISA2

#define PPS_PORT 0x00
#define PPS_ARRAY (&RA0PPS)

#define I2C_PPS_SCL_IN 0x04
#define I2C_PPS_SCL_OUT  RA4PPS

#define I2C_PPS_SDA_OUT RA5PPS
#define I2C_PPS_SDA_IN 0x05

#define WP_TRIS TRISA
#define WP_TRIS_INIT 0x3F // Set upper 2 pins (not wired) to Output
#define WP_LAT LATA
#define WP_LAT_INIT 0 // All pins low, including non-wired pins
#define WP_PORT PORTA
#define WP_ANSEL ANSELA
#define WP_WPU WPUA
#define WP_ODCON ODCONA
#ifdef UARTWOMBAT
#define WP0_PPS RA5PPS
#define WP1_PPS RA4PPS
#define WP2_PPS RA1PPS
#define WP3_PPS RA0PPS
#define WP0_PORTPINNUM 5
#define WP1_PORTPINNUM 4
#define WP2_PORTPINNUM 1
#define WP3_PORTPINNUM 0
#endif
#ifdef I2CWOMBAT
// #define WP0_PPS RA3PPS  //No PPS for this pin
#define WP1_PPS RA2PPS
#define WP2_PPS RA1PPS
#define WP3_PPS RA0PPS
#define WP0_PORTPINNUM 3
#define WP1_PORTPINNUM 2
#define WP2_PORTPINNUM 1
#define WP3_PORTPINNUM 0
#endif
#define WP_IOCN IOCAN
#define WP_IOCP IOCAP
#define WP_IOCF IOCAF
#define FRAME_TIMING_HIGH() {}
#define FRAME_TIMING_LOW() {}
#define FRAME_OVERFLOW_INDICATOR() {}

#endif
#define error(_a) {Txbuffer[0] = 'E';  Txbuffer[1] = 'X';}

#endif
