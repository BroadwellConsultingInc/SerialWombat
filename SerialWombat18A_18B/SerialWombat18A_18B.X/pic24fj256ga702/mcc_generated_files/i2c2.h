
/**
  I2C2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.h

  @Summary
    This is the generated header file for the I2C2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for I2C2.
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

#ifndef _I2C2_H
#define _I2C2_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


/**
  I2C Periph Driver Status

  @Summary
    Defines the different status that the periph driver has
    detected over the i2c bus.

  @Description
    This defines the different status that the periph driver has
    detected over the i2c bus. The status is passed to the
    I2C2_StatusCallback() callback function that is implemented by
    the user of the periph driver as a parameter to inform the user
    that there was a change in the status of the driver due to
    transactions on the i2c bus. User of the periph driver can use these
    to manage the read or write buffers.

 */

typedef enum
{
    /* This state indicates that the periph driver has detected a transmit request from the master.
       The next transaction will be a read transaction. Application should prime the transmit
       buffer with the valid data to be sent to the master using the: I2C2_ReadPointerSet()
       
     */
    I2C2_PERIPH_TRANSMIT_REQUEST_DETECTED,
            
    /* This state indicates that the periph driver has detected a reception request from the master.
       The next transaction will be a write transaction. Application should set up the receive 
       buffer by setting the location of the receive buffer using the: I2C2_WritePointerSet()
     */
    I2C2_PERIPH_RECEIVE_REQUEST_DETECTED,

    /* This state indicates that the periph driver has received data from the master.
       Application can use this status to process the received data set up the receive
       buffer in anticipation of next reception in case the master sends more data. 
       See I2C2_PERIPH_RECEIVE_REQUEST_DETECTED.
     */
    I2C2_PERIPH_RECEIVED_DATA_DETECTED,
            
    /* This state indicates that the periph driver has detected the most significant
       byte of the 10-bit periph address. Another transaction with the least 
       significant byte of the 10-bit address with a read/write request will
       be detected next. This second detection is automatically done by the 
       driver which may return one of the following:
           a. I2C2_PERIPH_RECEIVE_REQUEST_DETECTED
           b. I2C2_PERIPH_TRANSMIT_REQUEST_DETECTED
           c. I2C2_PERIPH_10BIT_RECEIVE_REQUEST_DETECTED
       a or b is detected depending on the read/write bit of the received 
       control data. If c is detected next, the master decided to resend
       the most significant address.  
     */
    I2C2_PERIPH_10BIT_RECEIVE_REQUEST_DETECTED,

} I2C2_PERIPH_DRIVER_STATUS;

#define I2C2_PERIPH_DEFAULT_ADDRESS          99

/**
    @Summary
        Initializes and enables the i2c periph instance : 2

    @Description
        This routine initializes the i2c periph driver instance for : 2
        index, making it ready for clients to open and use it.

    @Preconditions
        None

    @Param
        None

    @Returns
        None

    @Example
        <code>
            
            uint8_t PeriphReadBuffer;
            uint8_t PeriphWriteBuffer;

            // initialize the i2c periph driver    
            I2C2_Initialize();
    
            // set up the periph driver
 
            // initialize the location of the read buffer
            I2C2_ReadPointerSet(PeriphReadBuffer);
            // initialize the location of the write buffer
            I2C2_WritePointerSet(PeriphWriteBuffer);
  
        </code>
*/

void I2C2_Initialize(void);


/**
    @Summary
        This function sets the periph address mask.

    @Description
        This function sets the 10-bit periph address mask to be able to
        respond to multiple addresses. This function should be called
        after the initialization of the module.

    @Preconditions
        None

    @Param
        mask - The address mask to be used when filtering
            addresses from the i2c master transactions.

    @Returns
        None

    @Example
        <code>
            Refer to I2C2_PeriphAddressSet() for an example	
        </code>

*/

void I2C2_PeriphAddressMaskSet(
                                uint16_t mask);

/**
    @Summary
        This function sets the periph address.

    @Description
        This function sets the 10-bit periph address to be used by the
        module when filtering transactions from the i2c masters in the
        bus. The function analyzes the given address and decides if
        the 10-bit or 7-bit mode will be enabled. Once the function
        returns, the given address is set for the periph module.

        This function should be called after the initialization of
        the module.

        When changing the periph address the module must be idle.

    @Preconditions
        None

    @Param
        address - The address to be used to determine if the transaction
            is intended for this periph module.

    @Returns
        None

    @Example
        <code>
            // initialize the i2c periph driver    
            I2C2_Initialize();
 
            // set the periph address and address mask if the default
            // values set in the initialize is not the desired values.
            I2C2_PeriphAddressMaskSet(0x0xF);
            I2C2_PeriphAddressSet(0x3C);
 
        </code>

*/

void I2C2_PeriphAddressSet(
                                uint16_t address);


/**
    @Summary
        This function sets the read pointer for the periph driver.

    @Description
        This function sets the read pointer that the driver will
        need to retrieve data that will be transmitted to the master
        whenever the master requests a read.

    @Preconditions
        None

    @Param
        *p - The pointer to the read buffer, that will be used to transmit
             data to the requesting i2c master.

    @Returns
        None

    @Example
        <code>
            Refer to I2C2_Initialize() for an example	
        </code>

*/

void I2C2_ReadPointerSet(uint8_t *p);

/**
    @Summary
        This function sets the write pointer for the periph driver.

    @Description
        This function sets the write pointer that the driver will
        need to save data that will be received from the master
        whenever the master requests a write.

    @Preconditions
        None

    @Param
        *p - The pointer to the read buffer, that will be used to transmit
             data to the requesting i2c master.

    @Returns
        None

    @Example
        <code>
            Refer to I2C2_Initialize() for an example	
        </code>

*/

void I2C2_WritePointerSet(uint8_t *p);

/**
    @Summary
        This function returns the current read pointer used by the
        periph driver.

    @Description
        This function returns the current read pointer used by the
        periph driver. As the operation executes, the pointer is
        incremented. User of the periph driver can use this function
        to check on the current address that the pointer is pointing to.

    @Preconditions
        None

    @Param
        None

    @Returns
        The current pointer used to transmit data to the requesting
        i2c master

    @Example
        <code>
            uint8_t *pReadBuffer;
 
            pReadBuffer = I2C2_ReadPointerGet();
        </code>

*/

uint8_t *I2C2_ReadPointerGet(void);

/**
    @Summary
        This function returns the current write pointer used by the
        periph driver.

    @Description
        This function returns the current write pointer used by the
        periph driver. As the operation executes, the pointer is
        incremented. User of the periph driver can use this function
        to check on the current address that the pointer is pointing to.

    @Preconditions
        None

    @Param
        None

    @Returns
        The current pointer used to save received data from the requesting
        i2c master

    @Example
        <code>
            uint8_t *pWriteBuffer;
 
            pWriteBuffer = I2C2_WritePointerGet();
 
        </code>

*/

uint8_t *I2C2_WritePointerGet(void);

/**
   @Summary
        This application implemented function passes the
        status of the i2c periph driver.

    @Description
        This application implemented function passes the
        status of the i2c periph driver. The status passed
        can be used by the application to manage the read and
        write buffers. This function is called by the periph
        driver everytime there is an event in the i2c bus that caused
        an interrupt in the i2c periph module to be asserted.

        The function will return boolean. The value of the return
        will determine if the next received byte will be ack'ed or 
        nack'ed. By doing that, the application can have the 
        ability to delay incoming transactions. When a false is
        returned, the next transactions will be nack'ed forcing the 
        master to restart the transactions. 
 
        Returning a false will give the application a chance to
        prepare for the next transactions (for example: a read
        requests from the master) or process the recently received
        data.

    @Preconditions
        None

    @Param
        status - The latest status of the periph driver due
            to an event in the i2c bus.

    @Returns
        True, if the application is ready for the next transaction.
        False, if the application is not ready for the next transaction.

    @Example
        <code>

            // Example implementation of the callback

            static uint8_t i2c2_periphWriteData = 0xAA;

            bool I2C2_StatusCallback(I2C2_PERIPH_DRIVER_STATUS status)
            {

                // this emulates the periph device memory where data written to periph
                // is placed and data read from periph is taken
                static uint8_t EMULATE_EEPROM_Memory[64] =
                        {
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                        };

                static uint16_t address, addrByteCount;
                static bool     addressState = true;

                switch (status)
                {
                    case I2C2_PERIPH_TRANSMIT_REQUEST_DETECTED:

                        // set up the periph driver buffer transmit pointer
                        I2C2_ReadPointerSet(&EMULATE_EEPROM_Memory[address]);
                        address++;

                        break;

                    case I2C2_PERIPH_RECEIVE_REQUEST_DETECTED:

                        addrByteCount = 0;
                        addressState = true;

                        // set up the periph driver buffer receive pointer
                        I2C2_WritePointerSet(&i2c2_periphWriteData);

                        break;

                    case I2C2_PERIPH_RECEIVED_DATA_DETECTED:

                        if (addressState == true)
                        {
                            // get the address of the memory being written
                            if (addrByteCount == 0)
                            {
                                address = (i2c2_periphWriteData << 8) & 0xFF00;
                                addrByteCount++;
                            }
                            else if (addrByteCount == 1)
                            {
                                address = address | i2c2_periphWriteData;
                                addrByteCount = 0;
                                addressState = false;
                            }
                        }
                        else // if (addressState == false)
                        {
                            // set the memory with the received data
                            EMULATE_EEPROM_Memory[address] = i2c2_periphWriteData;
                        }

                        break;

                    case I2C2_PERIPH_10BIT_RECEIVE_REQUEST_DETECTED:

                        // do something here when 10-bit address is detected

                        // 10-bit address is detected

                        break;

                    default:
                        break;

                }

                return true;
            }
   
        </code>

 */

//#pragma message "I2C2_StatusCallback() is an Application implemented function. If this function is already implemented, you can turn off this message by deleting or commenting out this message."
bool I2C2_StatusCallback(I2C2_PERIPH_DRIVER_STATUS status);

void i2cHealthMonitor(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _I2C2_H
