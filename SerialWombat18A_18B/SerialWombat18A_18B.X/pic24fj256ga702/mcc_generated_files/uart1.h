/**
  UART1 Generated Driver API Header File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.h

  @Summary
    This is the generated header file for the UART1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for UART1. 
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

#ifndef UART1_H
#define UART1_H

/**
 Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
        
#define UART1_CONFIG_TX_BYTEQ_LENGTH 64
#define UART1_CONFIG_RX_BYTEQ_LENGTH 128
        
/**
  Section: Data Types
*/

/** UART1 Driver Hardware Flags

  @Summary
    Specifies the status of the hardware receive or transmit

  @Description
    This type specifies the status of the hardware receive or transmit.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/

typedef enum
{
    /* Indicates that Receive buffer has data, at least one more character can be read */
    UART1_RX_DATA_AVAILABLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,
    
    /* Indicates that Receive buffer has overflowed */
    UART1_RX_OVERRUN_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that Framing error has been detected for the current character */
    UART1_FRAMING_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that Parity error has been detected for the current character */
    UART1_PARITY_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that Receiver is Idle */
    UART1_RECEIVER_IDLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

    /* Indicates that the last transmission has completed */
    UART1_TX_COMPLETE
        /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,

    /* Indicates that Transmit buffer is full */
    UART1_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/

} UART1_STATUS;

/** UART1 Driver Transfer Flags

  @Summary
    Specifies the status of the receive or transmit

  @Description
    This type specifies the status of the receive or transmit operation.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/

typedef enum
{
    /* Indicates that the core driver buffer is full */
    UART1_TRANSFER_STATUS_RX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

    /* Indicates that at least one byte of Data has been received */
    UART1_TRANSFER_STATUS_RX_DATA_PRESENT
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver receiver buffer is empty */
    UART1_TRANSFER_STATUS_RX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is full */
    UART1_TRANSFER_STATUS_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is empty */
    UART1_TRANSFER_STATUS_TX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/

} UART1_TRANSFER_STATUS;

/**
  Section: UART1 Driver Routines
*/

/**
  @Summary
    Initializes the UART instance : 1

  @Description
    This routine initializes the UART driver instance for : 1
    index.
    This routine must be called before any other UART routine is called.
    
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Comment
    
 
  @Example
    <code>
        const uint8_t writeBuffer[35] = "1234567890ABCDEFGHIJKLMNOP\r\n" ;
        unsigned int numBytes = 0;
        int  writebufferLen = strlen((char *)writeBuffer);
        UART1_Initialize();
	
        while(numBytes < writebufferLen)
        {    
            int bytesToWrite = UART1_TransmitBufferSizeGet();
            numBytes += UART1_WriteBuffer ( writeBuffer+numBytes, bytesToWrite)  ;
        }
    </code>

*/

void UART1_Initialize(void);

/**
  @Summary
    Allows setting of a the enable bit for the UART1 mode

  @Description
    This routine is used to enable the UART1
  
  @Preconditions
    UART1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to UART1_Initialize(); for an example
*/

void UART1_Enable(void);

/**
  @Summary
    Allows setting of a the disable bit for the UART1 mode

  @Description
    This routine is used to disable the UART1
  
  @Preconditions
    UART1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to UART1_Initialize(); for an example
*/

void UART1_Disable(void);

/**
  @Summary
    Read a byte of data from the UART1

  @Description
    This routine reads a byte of data from the UART1.

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function. The transfer status should be checked to see 
    if the receiver is not empty before calling this function.

  @Param
    None.

  @Returns
    A data byte received by the driver.

  @Example
    <code>
    uint8_t myBuffer[MY_BUFFER_SIZE];
    unsigned int numBytes = 0;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.
    
    do
    {
        if( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet() )
        {
            myBuffer[numBytes++] = UART1_Read();
        }

        // Do something else...

    } while( numBytes < MY_BUFFER_SIZE);
    </code>
*/

uint8_t UART1_Read( void);

/**
  @Summary
    Returns the number of bytes read by the UART1 peripheral

  @Description
    This routine returns the number of bytes read by the Peripheral and fills the
    application read buffer with the read data.

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function

  @Param
    buffer       - Buffer into which the data read from the UART1

  @Param
    numbytes     - Total number of bytes that need to be read from the UART1
                   (must be equal to or less than the size of the buffer)

  @Returns
    Number of bytes actually copied into the caller's buffer or -1 if there
    is an error.

  @Example
    <code>
    uint8_t readBuffer[MY_BUFFER_SIZE];
    unsigned int status, numBytes = 0;
    
    // Pre-initialize readBuffer with MY_BUFFER_SIZE bytes of valid data.
    
    while (numBytes < MY_BUFFER_SIZE);
    {
        status = UART1_TransferStatusGet();
        if (status & UART1_TRANSFER_STATUS_RX_FULL) {
            numBytes += UART1_ReadBuffer(readBuffer + numBytes, MY_BUFFER_SIZE - numBytes);
        }

        // Do something else...
    }
    </code>
*/

unsigned int UART1_ReadBuffer( uint8_t *buffer ,  const unsigned int numbytes);

/**
  @Summary
    Writes a byte of data to the UART1

  @Description
    This routine writes a byte of data to the UART1.

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function. The transfer status should be checked to see if
    transmitter is not full before calling this function.

  @Param
    byte         - Data byte to write to the UART1

  @Returns
    None.

  @Example
    <code>
    uint8_t myBuffer[MY_BUFFER_SIZE];
    unsigned int numBytes = 0;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    while (numBytes < MY_BUFFER_SIZE);
    {
        if (!(UART1_TRANSFER_STATUS_TX_FULL & UART1_TransferStatusGet())) {
            UART1_Write(myBuffer[numBytes++]);
        }

        // Do something else...
    }
    </code>
*/

void UART1_Write( const uint8_t byte);

/**
  @Summary
    Returns the number of bytes written into the internal buffer

  @Description
    This API transfers the data from application buffer to internal buffer and 
    returns the number of bytes added in that queue

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function

  @Example
    <code>
    uint8_t myBuffer[MY_BUFFER_SIZE];
    unsigned int numBytes = 0;
    UART1_TRANSFER_STATUS status;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    while (numBytes < MY_BUFFER_SIZE);
    {
        status = UART1_TransferStatusGet();
        if (status & UART1_TRANSFER_STATUS_TX_EMPTY) {
            numBytes += UART1_WriteBuffer(myBuffer + numBytes, MY_BUFFER_SIZE - numBytes);

        }
        // Do something else...
    }
    </code>
*/

unsigned int UART1_WriteBuffer( const uint8_t *buffer , const unsigned int numbytes );

/**
  @Summary
    Returns the transmitter and receiver transfer status

  @Description
    This returns the transmitter and receiver transfer status.The returned status 
    may contain a value with more than one of the bits
    specified in the UART1_TRANSFER_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART1_TRANSFER_STATUS value describing the current status 
    of the transfer.

  @Example
    Refer to UART1_ReadBuffer and UART1_WriteBuffer for example

*/

UART1_TRANSFER_STATUS UART1_TransferStatusGet (void );

/**
  @Summary
    Returns the character in the read sequence at the offset provided, without
    extracting it

  @Description
    This routine returns the character in the read sequence at the offset provided,
    without extracting it
 
  @Param
    None.
    
  @Example 
    <code>
    uint8_t readBuffer[5];
    unsigned int data, numBytes = 0;
    unsigned int readbufferLen = sizeof (readBuffer);
    UART1_Initialize();

    while (numBytes < readbufferLen) {
        //Check for data at a particular place in the buffer
        data = UART1_Peek(3);
        if (data == 5) {
            //discard all other data if byte that is wanted is received.    
            //continue other operation
            numBytes += UART1_ReadBuffer(readBuffer + numBytes, readbufferLen);
        } else {
            break;
        }
    }
    </code>
 
*/

uint8_t UART1_Peek(uint16_t offset);

/**
  @Summary
    Validates the offset input and get the character in the read sequence at the 
    offset provided, without extracting it

  @Description
    This routine validates the offset input and get the character in the read 
    sequence at the offset provided, without extracting it. 
 
  @Param
    dataByte     - Data byte to be read from UART1 RX buffer based on offset position.
    offset       - UART1 RX buffer peek position. Offset input range is should be
                   0 to (UART1_CONFIG_RX_BYTEQ_LENGTH - 1).

  @Return   
    false        - If the UART1 RX buffer is empty or dataByte is NULL or UART1 RX 
                   buffer is empty.
    true         - Valid offset input position.
 
  @Example 
    <code>
    uint8_t readBuffer[MY_BUFFER_SIZE], data;
    unsigned int numBytes = 0;
    UART1_Initialize();

    // Pre-initialize readBuffer with MY_BUFFER_SIZE bytes of valid data.

    while (numBytes < MY_BUFFER_SIZE) {
        //Check for data at a particular place in the buffer
        if (UART1_PeekSafe(&data, 3)) {
            if (data == 5) {
                //discard all other data if byte that is wanted is received.    
                //continue other operation
                numBytes += UART1_ReadBuffer(readBuffer + numBytes, MY_BUFFER_SIZE - numBytes);
            } else {
                break;
            }
        }
    }
    </code>
 
*/

bool UART1_PeekSafe(uint8_t *dataByte, uint16_t offset);

/**
  @Summary
    Returns the number of bytes remaining in the receive buffer

  @Description
    This routine returns the number of bytes remaining in the receive buffer.

  @Param
    None.

  @Returns
    Remaining size of receive buffer.
    
  @Example 
    <code>
    uint8_t readBuffer[MY_BUFFER_SIZE];
    unsigned int size, numBytes = 0;
    UART1_Initialize();

    // Pre-initialize readBuffer with MY_BUFFER_SIZE bytes of valid data.
    
    while (size < MY_BUFFER_SIZE) {
        size = UART1_ReceiveBufferSizeGet();
    }
    numBytes = UART1_ReadBuffer(readBuffer, MY_BUFFER_SIZE);
    </code>
 
*/

unsigned int UART1_ReceiveBufferSizeGet(void);

/**
  @Summary
    Returns the number of bytes remaining in the transmit buffer.

  @Description
    This routine returns the number of bytes remaining in the transmit buffer.

 @Param
    None.
 
 @Returns
    Remaining size of transmit buffer.

 @Example
    Refer to UART1_Initialize(); for example.
*/

unsigned int UART1_TransmitBufferSizeGet(void);

/**
  @Summary
    Returns the status of the receive buffer

  @Description
    This routine returns if the receive buffer is empty or not.

  @Param
    None.
 
  @Returns
    True if the receive buffer is empty
    False if the receive buffer is not empty
    
  @Example
    <code>
    uint8_t myBuffer[MY_BUFFER_SIZE];
    unsigned int numBytes;
    UART1_TRANSFER_STATUS status;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    numBytes = 0;
    while (numBytes < MY_BUFFER_SIZE);
    {
        status = UART1_TransferStatusGet();
        if (!UART1_ReceiveBufferIsEmpty()) {
            numBytes += UART1_ReadBuffer(myBuffer + numBytes, MY_BUFFER_SIZE - numBytes);
        }
        // Do something else...
    }
    </code>
 
*/

bool UART1_ReceiveBufferIsEmpty (void);

/**
  @Summary
    Returns the status of the transmit buffer

  @Description
    This routine returns if the transmit buffer is full or not.

 @Param
    None.
 
 @Returns
    True if the transmit buffer is full
    False if the transmit buffer is not full

 @Example
    Refer to UART1_Initialize() for example.
 
*/

bool UART1_TransmitBufferIsFull (void);

/**
  @Summary
    Returns the transmitter and receiver status

  @Description
    This returns the transmitter and receiver status. The returned status 
    contains a 16 bit value. 
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    16 bit value describing the current status of the transfer.

  @Example
    <code>
        while(!(UART1_StatusGet() & UART1_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/

uint16_t UART1_StatusGet (void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
    
#endif  // UART1_H

