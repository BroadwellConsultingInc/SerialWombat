/*
Copyright 2020-2025 Broadwell Consulting Inc.

Serial Wombat is a registered trademark of Broadwell Consulting Inc in
the United States.  See SerialWombat.com for usage guidelines.

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

#include "serialWombat.h"
#include <stddef.h>  // For NULL
//#include "mcc_generated_files/mcc.h"



#define UART_QUEUE_LENGTH 32

//Note:  A 'Nip' is a dma segment.  In this case, 1/57600 of a second.
// 1 nip is a bit at 57600 bps, 6 nips is a bit at 9600 bps.
typedef struct uartSw_n{
	DMABitStream_t bitStream;
	uint8_t queueDataSpace[UART_QUEUE_LENGTH + 16]; // 16 to allow for queue overhead
    void* txQueue;
    void* rxQueue;
    uint16_t txRemainingNips;
    uint16_t rxFrameErrors;
    uint8_t idleBitsQueued;
    uint8_t txCurrentBit:1;
    uint8_t txRemainingBitmap;
    uint8_t txRemainingBits;
    uint8_t txPin;
    uint8_t rxPin;
    uint8_t rxState;
    uint8_t rxBitmap;
    uint8_t rxSampleDelay;
    uint8_t rxBitsReceived;
    uint8_t divisor;
}uartSw_t;

typedef enum
{
    UART_SW_RX_STATE_IDLE = 0,
    UART_SW_RX_STATE_SAMPLE_START = 1,
    UART_SW_RX_STATE_BITS = 2,
    UART_SW_RX_STATE_STOP = 3,
            UART_SW_RX_STATE_WAIT_FOR_IDLE = 4,
            
    
}UART_SW_RX_STATE_t;

//300  1200 2400  4800  9600  19.2  28.8  57.6  115.2
const uint16_t swBaudDivisor[] = { 192,48,24, 12, 6, 3, 2, 1, 1  };


void initUARTSw()
{
	uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_SW_UART)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				if (Rxbuffer[3] >7)
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
                    return;
				}
				uartSw-> divisor  = swBaudDivisor[Rxbuffer[3]];
				uartSw->rxPin = Rxbuffer[4];
				uartSw->txPin = Rxbuffer[5];
                
				uartSw->txQueue = NULL;
				uartSw->rxQueue = NULL;
                if (uartSw->rxPin != 0xFF)
				{
					PinInput(uartSw->rxPin);
					if (uartSw->rxPin != CurrentPin)
					{
						SetMode(uartSw->rxPin, PIN_MODE_CONTROLLED);
					}
					uartSw->rxQueue = (((uartSw_t*)&PinUpdateRegisters[uartSw->rxPin])->queueDataSpace);
					queueAddress = uartSw->rxQueue;
					QueueByteInitialize(UART_QUEUE_LENGTH);
					PulseInSkipDMABits(uartSw->rxPin,SIZE_OF_DMA_ARRAY);
				}
                
				if (uartSw->txPin != 0xFF)
				{
				    InitializePinHigh(uartSw->txPin);
                    initializeBitStreamOutput(uartSw->txPin,  1, &uartSw->bitStream );
					
					if (uartSw->txPin != CurrentPin)
					{
						SetMode(uartSw->txPin, PIN_MODE_CONTROLLED);
					}
					uartSw->txQueue = (((uartSw_t*)&PinUpdateRegisters[uartSw->txPin])->queueDataSpace);
                    queueAddress = uartSw->txQueue;
                    QueueByteInitialize(UART_QUEUE_LENGTH);
				}
				

				CurrentPinRegister->generic.mode = PIN_MODE_SW_UART;
				uartSw->rxState = UART_SW_RX_STATE_IDLE;
				uartSw->rxBitsReceived = 0;
				uartSw->rxSampleDelay = 0;
				uartSw->rxFrameErrors = 0;
			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:  //Transmit 
			{
				  	queueCONFIGURE_CHANNEL_MODE_1_transmit(uartSw->rxQueue,uartSw->txQueue);
				
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
				queueCONFIGURE_CHANNEL_MODE_2_receive(&uartSw->rxQueue);
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				queueCONFIGURE_CHANNEL_MODE_3_peekRX(uartSw->rxQueue, uartSw->txQueue);
				
			}
			break; 

		case CONFIGURE_CHANNEL_MODE_4: // Close Port
			{
				uartSw->txPin = 0xFF;
				uartSw->rxPin = 0xFF;
			}
			break; 

		case CONFIGURE_CHANNEL_MODE_5:   // Set up location of txQueue in User memory
			{  
				queueAddress = uartSw->txQueue = &UserBuffer[ RXBUFFER16(3)];
                uint16_t resultSize;
				if (QueueGetBytesFreeInQueue( &resultSize) != QUEUE_RESULT_SUCCESS)
				{
					error(SW_ERROR_UNNUMBERED_ERROR); // TODO future improvement: make errors based on result
				}
                else
                {
                    TXBUFFER16(5,resultSize);
                }
			}
			break; 

		case CONFIGURE_CHANNEL_MODE_6:  // Set up location of rxQueue in user memory
			{  
				queueAddress = uartSw->rxQueue = &UserBuffer[ RXBUFFER16(3)];
				
                uint16_t resultSize;
                queueAddress = uartSw->rxQueue;
				if (QueueGetBytesFreeInQueue( &resultSize) != QUEUE_RESULT_SUCCESS)
				{
					error(SW_ERROR_UNNUMBERED_ERROR); // TODO future improvement: make errors based on result
				}
                else
                {
                    TXBUFFER16(5,resultSize);
                }
			}
			break; 
            
             default:
        {
            error(SW_ERROR_INVALID_COMMAND);      
        }
        break;
	}


}

uartSw_t* debuguartSw;

void updateUARTSwTx()
{
    uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;
    queueAddress = uartSw->txQueue;
    debuguartSw = uartSw;
   
    if (uartSw->idleBitsQueued)
    {
    removeBitStreamOutput(uartSw->txPin, uartSw->idleBitsQueued, 5, &uartSw->bitStream);
    uartSw->idleBitsQueued = 0;
    }
    if (uartSw->txRemainingNips)
	{
		uartSw->txRemainingNips = updateBitStreamOutput(uartSw->txPin, uartSw->txCurrentBit, uartSw->txRemainingNips, &uartSw->bitStream);
	}	
    
    uint8_t idle = 0;
    uint8_t bytesToAdd = 2;
	while (uartSw->txRemainingNips == 0 && !idle)
    {
        // we still have room in the DMA

        if (uartSw->txRemainingBits)
        {    
            //one bit at a time
            uartSw->txCurrentBit = uartSw->txRemainingBitmap & 0x01;
            uartSw->txRemainingBitmap >>= 1;
            -- uartSw->txRemainingBits;
            uint16_t nips = uartSw->divisor;
            while (uartSw->txRemainingBits >= 2 &&
                    (uartSw->txCurrentBit == (uartSw->txRemainingBitmap & 0x01)))
            {
                 uartSw->txRemainingBitmap >>= 1;
            -- uartSw->txRemainingBits;
             nips += uartSw->divisor;
            }
            if (uartSw->txRemainingBits == 0)
            {
                uartSw->txCurrentBit = 1; // Stop bit
            }
            uartSw->txRemainingNips = updateBitStreamOutput(uartSw->txPin, uartSw->txCurrentBit,  nips, &uartSw->bitStream);
             
        }

        else if (QueueReadByte(& uartSw->txRemainingBitmap)== QUEUE_RESULT_SUCCESS )
        {
             uartSw->txCurrentBit = 0; // start bit
            uartSw->txRemainingBits = 9;
            uartSw->txRemainingNips = updateBitStreamOutput(uartSw->txPin, uartSw->txCurrentBit,  uartSw->divisor, &uartSw->bitStream);
            --bytesToAdd;
        }
        else
        {
            //Idle
             uartSw->idleBitsQueued = 255 - updateBitStreamOutput(uartSw->txPin, 1,  255, &uartSw->bitStream);
             
            idle = 1;
        }
        
    }
	        	
}



void updateUARTSwRx()
{
    uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;
    uint8_t inputBit;
    inputBit = PulseInGetOldestDMABit(uartSw->rxPin);
   //  SetPin(14,(inputBit & 0x02) > 0);
       //     SetPin(15,(inputBit & 0x01) > 0);
    while (inputBit != 2)
    {
       
        if (uartSw->rxSampleDelay > 0)
        {
            -- uartSw->rxSampleDelay; // The bit we'll take on the way out
            if (uartSw->rxSampleDelay > 0)
            {
                uartSw->rxSampleDelay -=   PulseInSkipDMABits(uartSw->rxPin, uartSw->rxSampleDelay);
            }
            inputBit = PulseInGetOldestDMABit(uartSw->rxPin);
            continue;
        }

         
    switch (uartSw->rxState)
    {
        case UART_SW_RX_STATE_IDLE:
        {
            if (inputBit == 0)
            {
             //   PinHigh(12);
                uartSw->rxState = UART_SW_RX_STATE_SAMPLE_START;
                uartSw->rxSampleDelay = (uartSw->divisor  ) /2  - 1;
                if (uartSw->divisor < 3)
                {
                    uartSw->rxState = UART_SW_RX_STATE_SAMPLE_START;
                    uartSw->rxSampleDelay = 0;
                    uartSw->rxBitmap = 0;
                    uartSw->rxBitsReceived = 0;
                    uartSw->rxState = UART_SW_RX_STATE_BITS;
                }
             }

            else
            {
                PulseInDiscardUntilLow(uartSw->rxPin);
            }
        }
        break;
        
    case UART_SW_RX_STATE_SAMPLE_START:
        {
            if (inputBit != 0)
            {
                uartSw->rxState = UART_SW_RX_STATE_IDLE;
            }
            else 
            {
                uartSw->rxSampleDelay = uartSw->divisor - 1;
                uartSw->rxBitmap = 0;
                uartSw->rxBitsReceived = 0;
                uartSw->rxState = UART_SW_RX_STATE_BITS;
          //      PinLow(12);
            }
        }
        break;
        
    case UART_SW_RX_STATE_BITS:
        {
            uartSw->rxBitmap >>= 1;
           // PinHigh(13);
           // PinLow(13);
            if (inputBit)
            {
                uartSw->rxBitmap |= 0x80;
            }
            ++ uartSw->rxBitsReceived;
            if (uartSw->rxBitsReceived >= 8)
            {
                uartSw->rxState = UART_SW_RX_STATE_STOP;
            }
            uartSw->rxSampleDelay = uartSw->divisor - 1;
        }
        break;
        
    case UART_SW_RX_STATE_STOP:
        {

            if (inputBit)
            {
              //  PinHigh(12);
             //   PinLow(12);

                queueAddress = uartSw->rxQueue;
                QueueAddByte(uartSw->rxBitmap);

                uartSw->rxState = UART_SW_RX_STATE_IDLE;
            }
            else
            {
                ++ uartSw->rxFrameErrors;
                uartSw->rxState =  UART_SW_RX_STATE_WAIT_FOR_IDLE;
            }
            
            
        }
        break;
        
        default:
        case UART_SW_RX_STATE_WAIT_FOR_IDLE:
        {
            if (inputBit)
            {
                uartSw->rxState = UART_SW_RX_STATE_IDLE;
            }
        }
        break;
        
      
        
    }
    inputBit = PulseInGetOldestDMABit(uartSw->rxPin);
    }
}

void updateUARTSw()
{
    uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;

    if (uartSw->txPin != 0xFF)
    {
	updateUARTSwTx();
    }
    if (uartSw->rxPin != 0xFF)
    {
        updateUARTSwRx();
    }
}


void queueCONFIGURE_CHANNEL_MODE_1_transmit(void* rxQueue, void* txQueue)
{
                uint8_t i;
                    queueAddress = txQueue;
                    for (i = 0; i < Rxbuffer[3]; ++i)
                    {
                        QueueAddByte(Rxbuffer[4 + i]);
                    }
                    uint16_t count;
                    QueueGetBytesFreeInQueue(&count) ;
                    if (count < 255)
                    {
                    Txbuffer[3] = count;
                    }
                    else
                    {
                        Txbuffer[3] = 255;
                    }

                    queueAddress = rxQueue;
                    QueueGetBytesFilledInQueue(&count);

                    if (count < 255)
                    {
                        Txbuffer[4] = count;
                    }
                    else
                    {
                        Txbuffer[4] = 255;
                    }

}

//TODO add address validation system to queue functions
void queueCONFIGURE_CHANNEL_MODE_2_receive(void* rxQueue)
{
                Txbuffer[3] = 0;

                uint8_t i;
                uint8_t data;
                if (Rxbuffer[3] > 4)
                {
                    Rxbuffer[3] = 4;
                }
                queueAddress = rxQueue;
                for (i = 0; i < Rxbuffer[3] && (QueueReadByte(&data)== QUEUE_RESULT_SUCCESS) ; ++i)
                {
                    Txbuffer[i+4] = data;
                    ++Txbuffer[3];
                }
}

void queueCONFIGURE_CHANNEL_MODE_3_peekRX(void* rxQueue, void* txQueue)
{
                queueAddress = txQueue;
                uint16_t bytesFree;
                                 QueueGetBytesFreeInQueue(&bytesFree);
                Txbuffer[3] = (uint8_t)bytesFree ;
                queueAddress = rxQueue;
                uint16_t bytesFilled;
                QueueGetBytesFilledInQueue(&bytesFilled);
               Txbuffer[4] = (uint8_t) bytesFilled;
               uint8_t data;
               QueuePeekByte(&data);
                Txbuffer[5] = data;
}
