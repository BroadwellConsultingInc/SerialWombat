/**
  UART2 Generated Driver API Header File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart2.h

  @Summary
    This is the generated header file for the UART2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for UART2. 
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

#ifndef UART2_H
#define UART2_H

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
        
#define UART2_CONFIG_TX_BYTEQ_LENGTH 64
#define UART2_CONFIG_RX_BYTEQ_LENGTH 128
        
/**
  Section: Data Types
*/

/** UART2 Driver Hardware Flags

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
    UART2_RX_DATA_AVAILABLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,
    
    /* Indicates that Receive buffer has overflowed */
    UART2_RX_OVERRUN_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that Framing error has been detected for the current character */
    UART2_FRAMING_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that Parity error has been detected for the current character */
    UART2_PARITY_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that Receiver is Idle */
    UART2_RECEIVER_IDLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

    /* Indicates that the last transmission has completed */
    UART2_TX_COMPLETE
        /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,

    /* Indicates that Transmit buffer is full */
    UART2_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/

} UART2_STATUS;

/** UART2 Driver Transfer Flags

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
    UART2_TRANSFER_STATUS_RX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

    /* Indicates that at least one byte of Data has been received */
    UART2_TRANSFER_STATUS_RX_DATA_PRESENT
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver receiver buffer is empty */
    UART2_TRANSFER_STATUS_RX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is full */
    UART2_TRANSFER_STATUS_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is empty */
    UART2_TRANSFER_STATUS_TX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/

} UART2_TRANSFER_STATUS;

/**
  Section: UART2 Driver Routines
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
        UART2_Initialize();
	
        while(numBytes < writebufferLen)
        {    
            int bytesToWrite = UART2_TransmitBufferSizeGet();
            numBytes += UART2_WriteBuffer ( writeBuffer+numBytes, bytesToWrite)  ;
        }
    </code>

*/

void UART2_Initialize(void);

/**
  @Summary
    Allows setting of a the enable bit for the UART2 mode

  @Description
    This routine is used to enable the UART2
  
  @Preconditions
    UART2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to UART2_Initialize(); for an example
*/

void UART2_Enable(void);

/**
  @Summary
    Allows setting of a the disable bit for the UART2 mode

  @Description
    This routine is used to disable the UART2
  
  @Preconditions
    UART2_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to UART2_Initialize(); for an example
*/

void UART2_Disable(void);

/**
  @Summary
    Read a byte of data from the UART2

  @Description
    This routine reads a byte of data from the UART2.

  @Preconditions
    UART2_Initialize function should have been called 
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
        if( UART2_TRANSFER_STATUS_RX_DATA_PRESENT & UART2_TransferStatusGet() )
        {
            myBuffer[numBytes++] = UART2_Read();
        }

        // Do something else...

    } while( numBytes < MY_BUFFER_SIZE);
    </code>
*/

uint8_t UART2_Read( void);

/**
  @Summary
    Returns the number of bytes read by the UART2 peripheral

  @Description
    This routine returns the number of bytes read by the Peripheral and fills the
    application read buffer with the read data.

  @Preconditions
    UART2_Initialize function should have been called 
    before calling this function

  @Param
    buffer       - Buffer into which the data read from the UART2

  @Param
    numbytes     - Total number of bytes that need to be read from the UART2
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
        status = UART2_TransferStatusGet();
        if (status & UART2_TRANSFER_STATUS_RX_FULL) {
            numBytes += UART2_ReadBuffer(readBuffer + numBytes, MY_BUFFER_SIZE - numBytes);
        }

        // Do something else...
    }
    </code>
*/

unsigned int UART2_ReadBuffer( uint8_t *buffer ,  const unsigned int numbytes);

/**
  @Summary
    Writes a byte of data to the UART2

  @Description
    This routine writes a byte of data to the UART2.

  @Preconditions
    UART2_Initialize function should have been called 
    before calling this function. The transfer status should be checked to see if
    transmitter is not full before calling this function.

  @Param
    byte         - Data byte to write to the UART2

  @Returns
    None.

  @Example
    <code>
    uint8_t myBuffer[MY_BUFFER_SIZE];
    unsigned int numBytes = 0;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    while (numBytes < MY_BUFFER_SIZE);
    {
        if (!(UART2_TRANSFER_STATUS_TX_FULL & UART2_TransferStatusGet())) {
            UART2_Write(myBuffer[numBytes++]);
        }

        // Do something else...
    }
    </code>
*/

void UART2_Write( const uint8_t byte);

/**
  @Summary
    Returns the number of bytes written into the internal buffer

  @Description
    This API transfers the data from application buffer to internal buffer and 
    returns the number of bytes added in that queue

  @Preconditions
    UART2_Initialize function should have been called 
    before calling this function

  @Example
    <code>
    uint8_t myBuffer[MY_BUFFER_SIZE];
    unsigned int numBytes = 0;
    UART2_TRANSFER_STATUS status;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    while (numBytes < MY_BUFFER_SIZE);
    {
        status = UART2_TransferStatusGet();
        if (status & UART2_TRANSFER_STATUS_TX_EMPTY) {
            numBytes += UART2_WriteBuffer(myBuffer + numBytes, MY_BUFFER_SIZE - numBytes);

        }
        // Do something else...
    }
    </code>
*/

unsigned int UART2_WriteBuffer( const uint8_t *buffer , const unsigned int numbytes );

/**
  @Summary
    Returns the transmitter and receiver transfer status

  @Description
    This returns the transmitter and receiver transfer status.The returned status 
    may contain a value with more than one of the bits
    specified in the UART2_TRANSFER_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART2_Initialize function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART2_TRANSFER_STATUS value describing the current status 
    of the transfer.

  @Example
    Refer to UART2_ReadBuffer and UART2_WriteBuffer for example

*/

UART2_TRANSFER_STATUS UART2_TransferStatusGet (void );

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
    UART2_Initialize();

    while (numBytes < readbufferLen) {
        //Check for data at a particular place in the buffer
        data = UART2_Peek(3);
        if (data == 5) {
            //discard all other data if byte that is wanted is received.    
            //continue other operation
            numBytes += UART2_ReadBuffer(readBuffer + numBytes, readbufferLen);
        } else {
            break;
        }
    }
    </code>
 
*/

uint8_t UART2_Peek(uint16_t offset);

/**
  @Summary
    Validates the offset input and get the character in the read sequence at the 
    offset provided, without extracting it

  @Description
    This routine validates the offset input and get the character in the read 
    sequence at the offset provided, without extracting it. 
 
  @Param
    dataByte     - Data byte to be read from UART2 RX buffer based on offset position.
    offset       - UART2 RX buffer peek position. Offset input range is should be
                   0 to (UART2_CONFIG_RX_BYTEQ_LENGTH - 1).

  @Return   
    false        - If the UART2 RX buffer is empty or dataByte is NULL or UART2 RX 
                   buffer is empty.
    true         - Valid offset input position.
 
  @Example 
    <code>
    uint8_t readBuffer[MY_BUFFER_SIZE], data;
    unsigned int numBytes = 0;
    UART2_Initialize();

    // Pre-initialize readBuffer with MY_BUFFER_SIZE bytes of valid data.

    while (numBytes < MY_BUFFER_SIZE) {
        //Check for data at a particular place in the buffer
        if (UART2_PeekSafe(&data, 3)) {
            if (data == 5) {
                //discard all other data if byte that is wanted is received.    
                //continue other operation
                numBytes += UART2_ReadBuffer(readBuffer + numBytes, MY_BUFFER_SIZE - numBytes);
            } else {
                break;
            }
        }
    }
    </code>
 
*/

bool UART2_PeekSafe(uint8_t *dataByte, uint16_t offset);

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
    UART2_Initialize();

    // Pre-initialize readBuffer with MY_BUFFER_SIZE bytes of valid data.
    
    while (size < MY_BUFFER_SIZE) {
        size = UART2_ReceiveBufferSizeGet();
    }
    numBytes = UART2_ReadBuffer(readBuffer, MY_BUFFER_SIZE);
    </code>
 
*/

unsigned int UART2_ReceiveBufferSizeGet(void);

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
    Refer to UART2_Initialize(); for example.
*/

unsigned int UART2_TransmitBufferSizeGet(void);

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
    UART2_TRANSFER_STATUS status;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    numBytes = 0;
    while (numBytes < MY_BUFFER_SIZE);
    {
        status = UART2_TransferStatusGet();
        if (!UART2_ReceiveBufferIsEmpty()) {
            numBytes += UART2_ReadBuffer(myBuffer + numBytes, MY_BUFFER_SIZE - numBytes);
        }
        // Do something else...
    }
    </code>
 
*/

bool UART2_ReceiveBufferIsEmpty (void);

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
    Refer to UART2_Initialize() for example.
 
*/

bool UART2_TransmitBufferIsFull (void);

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
    UART2_Initialize function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    16 bit value describing the current status of the transfer.

  @Example
    <code>
        while(!(UART2_StatusGet() & UART2_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/

uint16_t UART2_StatusGet (void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
    
#endif  // UART2_H

