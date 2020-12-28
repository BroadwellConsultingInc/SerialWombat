/**
  I2C1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1_follower.h

  @Summary
    This is the generated header file for the I2C1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15214
        Driver Version    :  1.0.1
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above or later
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

#ifndef I2C1_SLAVE_H
#define I2C1_SLAVE_H

#include <stdbool.h>
#include <stdint.h>

typedef void (*i2c1InterruptHandler)(void);
/**
 * \brief Initialize I2C1 interface
 * If module is configured to disabled state, the clock to the I2C1 is disabled
 * if this is supported by the device's clock system.
 *
 * \return None
 */
void I2C1_Initialize(void);

/**
 * \brief Open the I2C1 for communication. Enables the module if disabled.
 *
 * \return Nothing
 */
void I2C1_Open(void);

/**
 * \brief Close the I2C1 for communication. Disables the module if enabled.
 * Disables address recognition.
 *
 * \return Nothing
 */
void I2C1_Close(void);

/**
 * \brief Read data from I2C1 communication. 
 *
 * \return Read Data
 */
uint8_t I2C1_Read(void);

/**
 * \brief Write data over the communication. 
 *
 * \return None
 */
void I2C1_Write(uint8_t data);

/**
 * \brief Check for Master Read/Write Request
 *
 * \return bool
 * 1 - Master Read Request
 * 0 - Master Write Request
 */
bool I2C1_IsRead(void);

/**
 * \brief Enable the communication by initialization of hardware 
 *
 * \return None
 */
void I2C1_Enable(void);

/**
 * \brief Send the Ack Signal to Master 
 *
 * \return None
 */
void I2C1_SendAck(void);

/**
 * \brief Send the Nack Signal to Master 
 *
 * \return None
 */
void I2C1_SendNack(void);

/**
 * \brief The function called by the I2C1 Irq handler.
 * Can be called in a polling loop in a polled driver.
 *
 * \return Nothing
 */
void I2C1_FollowerSetIsrHandler(i2c1InterruptHandler handler);
void I2C1_FollowerSetAddrIntHandler(i2c1InterruptHandler handler);
void I2C1_FollowerSetReadIntHandler(i2c1InterruptHandler handler);
void I2C1_FollowerSetWriteIntHandler(i2c1InterruptHandler handler);
void I2C1_FollowerSetBusColIntHandler(i2c1InterruptHandler handler);
void I2C1_FollowerSetWrColIntHandler(i2c1InterruptHandler handler);

//void (*MSSP1_InterruptHandler)(void);
//void (*I2C1_FollowerRdInterruptHandler)(void);
//void (*I2C1_FollowerWrInterruptHandler)(void);
//void (*I2C1_FollowerAddrInterruptHandler)(void);
//void (*I2C1_FollowerBusColInterruptHandler)(void);
//void (*I2C1_FollowerWrColInterruptHandler)(void);


#endif /* I2C1_SLAVE_H */
