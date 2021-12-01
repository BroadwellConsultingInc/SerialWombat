/**
  UART1 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.c

  @Summary
    This is the generated source file for the UART1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for UART1. 
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
  Section: Included Files
*/

#include "uart1.h"

/**
  Section: Data Type Definitions
*/

/** UART Driver Queue Status

  @Summary
    Defines the object required for the status of the queue.
*/

typedef union
{
    struct
    {
            uint8_t full:1;
            uint8_t empty:1;
            uint8_t reserved:6;
    }s;
    uint8_t status;
}

UART_BYTEQ_STATUS;

/** UART Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

*/

typedef struct
{
    /* RX Byte Q */
    uint8_t                                      *rxTail ;

    uint8_t                                      *rxHead ;

    /* TX Byte Q */
    uint8_t                                      *txTail ;

    uint8_t                                      *txHead ;

    UART_BYTEQ_STATUS                        rxStatus ;

    UART_BYTEQ_STATUS                        txStatus ;

} UART_OBJECT ;

 volatile UART_OBJECT uart1_obj ; 

/** UART Driver Queue Length

  @Summary
    Defines the length of the Transmit and Receive Buffers

*/



/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

*/

static uint8_t uart1_txByteQ[UART1_CONFIG_TX_BYTEQ_LENGTH] ;
static uint8_t uart1_rxByteQ[UART1_CONFIG_RX_BYTEQ_LENGTH] ;

/**
  Section: Driver Interface
*/

void UART1_Initialize(void)
{
    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U1MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;
	// BaudRate = 115200; Frequency = 16000000 Hz; U1BRG 34; 
    U1BRG = 0x22;
    // ADMADDR 0; ADMMASK 0; 
    U1ADMD = 0x00;
    
  
    
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    
    UART1_Enable();  // enabling UARTEN bit

    uart1_obj.txHead = uart1_txByteQ;
    uart1_obj.txTail = uart1_txByteQ;
    uart1_obj.rxHead = uart1_rxByteQ;
    uart1_obj.rxTail = uart1_rxByteQ;
    uart1_obj.rxStatus.s.empty = true;
    uart1_obj.txStatus.s.empty = true;
    uart1_obj.txStatus.s.full = false;
    uart1_obj.rxStatus.s.full = false;
    IEC0bits.U1RXIE = 1;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1TXInterrupt ( void )
{ 
    if((uart1_obj.txHead == uart1_obj.txTail) && (uart1_obj.txStatus.s.full == false))
    {
        //JAB while(U1STAbits.TRMT == 0){}
        
        uart1_obj.txStatus.s.empty = true;
        IEC0bits.U1TXIE = 0;
        return;
    }

    IFS0bits.U1TXIF = 0;

    while(!(U1STAbits.UTXBF == 1))
    {
        U1TXREG = *uart1_obj.txHead;

        uart1_obj.txHead++;

        if(uart1_obj.txHead == (uart1_txByteQ + UART1_CONFIG_TX_BYTEQ_LENGTH))
        {
            uart1_obj.txHead = uart1_txByteQ;
        }

        uart1_obj.txStatus.s.full = false;

        if(uart1_obj.txHead == uart1_obj.txTail)
        {
            break;
        }
    }
}
uint8_t lastRXInterruptByte = 0x00;
uint32_t TotalRxBytes = 0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt( void )
{

    IFS0bits.U1RXIF = false;
    while((U1STAbits.URXDA == 1))
    {
        lastRXInterruptByte = U1RXREG;
        *uart1_obj.rxTail = lastRXInterruptByte;
        ++TotalRxBytes;
        uart1_obj.rxTail++;

        if(uart1_obj.rxTail == (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH))
        {
            uart1_obj.rxTail = uart1_rxByteQ;
        }

        uart1_obj.rxStatus.s.empty = false;
        
        if(uart1_obj.rxTail == uart1_obj.rxHead)
        {
            //Sets the flag RX full
            uart1_obj.rxStatus.s.full = true;
            break;
        }
    }

    
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt( void )
{
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }
    
    IFS4bits.U1ERIF = false;
}

/**
  Section: UART Driver Client Routines
*/

uint8_t UART1_Read( void)
{
    uint8_t data = 0;
    
  //  if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized

    data = *uart1_obj.rxHead;

    uart1_obj.rxHead++;

    if (uart1_obj.rxHead == (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH))
    {
        uart1_obj.rxHead = uart1_rxByteQ;
    }

    if (uart1_obj.rxHead == uart1_obj.rxTail)
    {
        uart1_obj.rxStatus.s.empty = true;
    }

    uart1_obj.rxStatus.s.full = false;

    return data;
}

unsigned int UART1_ReadBuffer( uint8_t *buffer, const unsigned int bufLen)
 {
    if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized
    IEC0bits.U1RXIE = 0;
    unsigned int numBytesRead = 0 ;
    while ( numBytesRead < ( bufLen ))
    {
        if( uart1_obj.rxStatus.s.empty)
        {
            break;
        }
        else
        {
            buffer[numBytesRead++] = UART1_Read () ;
        }
    }
IEC0bits.U1RXIE = 1;
    return numBytesRead ;
}

void UART1_Write( const uint8_t byte)
{
    if (!IEC0bits.U1RXIE ) return;  //Uninitialized
    IEC0bits.U1TXIE = 0;
    
    *uart1_obj.txTail = byte;

    uart1_obj.txTail++;
    
    if (uart1_obj.txTail == (uart1_txByteQ + UART1_CONFIG_TX_BYTEQ_LENGTH))
    {
        uart1_obj.txTail = uart1_txByteQ;
    }

    uart1_obj.txStatus.s.empty = false;

    if (uart1_obj.txHead == uart1_obj.txTail)
    {
        uart1_obj.txStatus.s.full = true;
    }

    IEC0bits.U1TXIE = 1 ;
}

unsigned int UART1_WriteBuffer( const uint8_t *buffer , const unsigned int bufLen )
{
    unsigned int numBytesWritten = 0 ;
    if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized

    while ( numBytesWritten < ( bufLen ))
    {
        if((uart1_obj.txStatus.s.full))
        {
            break;
        }
        else
        {
            UART1_Write (buffer[numBytesWritten++] ) ;
        }
    }

    return numBytesWritten ;
}

UART1_TRANSFER_STATUS UART1_TransferStatusGet (void )
{
    UART1_TRANSFER_STATUS status = 0;

    /* The TX empty must be checked before the full in order to prevent a race
     * condition where a TX transmission could start between these two checks
     * resulting in both full and empty set at the same time.
     */
    if(uart1_obj.txStatus.s.empty)
    {
        status |= UART1_TRANSFER_STATUS_TX_EMPTY;
    }

    if(uart1_obj.txStatus.s.full)
    {
        status |= UART1_TRANSFER_STATUS_TX_FULL;
    }

    /* The RX full must be checked before the empty in order to prevent a race
     * condition where a RX reception could start between these two checks
     * resulting in both empty and full set at the same time.
     */
    if(uart1_obj.rxStatus.s.full)
    {
        status |= UART1_TRANSFER_STATUS_RX_FULL;
    }

    if(uart1_obj.rxStatus.s.empty)
    {
        status |= UART1_TRANSFER_STATUS_RX_EMPTY;
    }
    else
    {
        status |= UART1_TRANSFER_STATUS_RX_DATA_PRESENT;
    }
    return status;
}

/*
    Uart Peek function returns the character in the read sequence with
    the provided offset, without extracting it.
*/
uint8_t UART1_Peek(uint16_t offset)
{
    if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized
    
    if( (uart1_obj.rxHead + offset) >= (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH))
    {
      return uart1_rxByteQ[offset - (uart1_rxByteQ + UART1_CONFIG_RX_BYTEQ_LENGTH - uart1_obj.rxHead)];
    }
    else
    {
      return *(uart1_obj.rxHead + offset);
    }
}

/*
    Uart PeekSafe function validates all the possible conditions and get the character  
    in the read sequence with the provided offset, without extracting it.
*/
bool UART1_PeekSafe(uint8_t *dataByte, uint16_t offset)
{
    uint16_t index = 0;
    bool status = true;
    if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized
    if((offset >= UART1_CONFIG_RX_BYTEQ_LENGTH) || (uart1_obj.rxStatus.s.empty) || (!dataByte))
    {
        status = false;
    }
    else
    {    
        //Compute the offset buffer overflow range
        index = ((uart1_obj.rxHead - uart1_rxByteQ) + offset) % UART1_CONFIG_RX_BYTEQ_LENGTH;
    
        /**
         * Check for offset input value range is valid or invalid. If the range 
         * is invalid, then status set to false else true.
         */
        if(uart1_obj.rxHead < uart1_obj.rxTail) 
        {
            if((uart1_obj.rxHead + offset) > (uart1_obj.rxTail - 1))
            {
                status = false;
            }
        }
        else if(uart1_obj.rxHead > uart1_obj.rxTail)
        {
            if((uart1_rxByteQ + index) < uart1_obj.rxHead)
            {
                if( (uart1_rxByteQ + index) >= uart1_obj.rxTail )
                {
                    status = false;
                }
            } 
        }

        if(status == true)
        {
            *dataByte = UART1_Peek(offset);
        }
    }
    return status;
}

unsigned int UART1_ReceiveBufferSizeGet(void)
{
    if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized
    if(!uart1_obj.rxStatus.s.full)
    {
        if(uart1_obj.rxHead > uart1_obj.rxTail)
        {
            return(uart1_obj.rxHead - uart1_obj.rxTail);
        }
        else
        {
            return(UART1_CONFIG_RX_BYTEQ_LENGTH - (uart1_obj.rxTail - uart1_obj.rxHead));
        } 
    }
    return 0;
}

unsigned int UART1_TransmitBufferSizeGet(void)
{
    if (!IEC0bits.U1RXIE ) return 0;  //Uninitialized
    if(!uart1_obj.txStatus.s.full)
    { 
        if(uart1_obj.txHead > uart1_obj.txTail)
        {
            return(uart1_obj.txHead - uart1_obj.txTail);
        }
        else
        {
            return(UART1_CONFIG_TX_BYTEQ_LENGTH - (uart1_obj.txTail - uart1_obj.txHead));
        }
    }
    return 0;
}

bool UART1_ReceiveBufferIsEmpty (void)
{
    if (!IEC0bits.U1RXIE ) return true;  //Uninitialized
    return(uart1_obj.rxStatus.s.empty);
}

bool UART1_TransmitBufferIsFull(void)
{
    if (!IEC0bits.U1RXIE ) return false;  //Uninitialized
    return(uart1_obj.txStatus.s.full);
}

uint16_t UART1_StatusGet (void)
{
    return U1STA;
}

void UART1_Enable(void)
{
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
}

void UART1_Disable(void)
{
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
    U1MODEbits.UARTEN = 0;
    U1STAbits.UTXEN = 0;
}

