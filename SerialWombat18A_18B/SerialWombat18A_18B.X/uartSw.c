#include "serialWombat.h"
#include "mcc_generated_files/mcc.h"


//Note:  A 'Nip' is a dma segment.  In this case, 1/57600 of a second.
// 1 nip is a bit at 57600 bps, 6 nips is a bit at 9600 bps.
typedef struct uartSw_n{
	DMABitStream_t bitStream;
    uint16_t txQueue;
    uint16_t rxQueue;
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
                
                if (uartSw->rxPin != 0xFF)
				{
					PinInput(uartSw->rxPin);
					if (uartSw->rxPin != CurrentPin)
					{
						SetMode(uartSw->rxPin, PIN_MODE_CONTROLLED);
					}
				}
                
				if (uartSw->txPin != 0xFF)
				{
                    
                    initializeBitStreamOutput(uartSw->txPin,  1, &uartSw->bitStream );
					PinLow(uartSw->txPin);
					if (uartSw->txPin != CurrentPin)
					{
						SetMode(uartSw->txPin, PIN_MODE_CONTROLLED);
					}
				}
				

				CurrentPinRegister->generic.mode = PIN_MODE_SW_UART;
				uartSw->txQueue = 0xFFFF;
				uartSw->rxQueue = 0xFFFF;
				uartSw->rxState = UART_SW_RX_STATE_IDLE;
				uartSw->rxBitsReceived = 0;
				uartSw->rxSampleDelay = 0;
				uartSw->rxFrameErrors = 0;
			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:  //Transmit 
			{
				uint8_t i;
				   
					for (i = 0; i < Rxbuffer[3]; ++i)
					{
						QueueAddByte(uartSw->txQueue,Rxbuffer[4 + i]);
					}
					uint16_t count;
					QueueGetBytesFreeInQueue(uartSw->txQueue,&count) ;
					if (count < 255)
					{
					Txbuffer[3] = count;
					}
					else
					{
						Txbuffer[3] = 255;
					}

					QueueGetBytesFilledInQueue(uartSw->txQueue,&count);

					if (count < 255)
					{
                        Txbuffer[4] = count;
					}
					else
					{
						Txbuffer[4] = 255;
					}
				
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
				Txbuffer[3] = 0;
				Rxbuffer[3] += 4;
				uint8_t i;
				   
					SW_QUEUE_RESULT_t result = QUEUE_RESULT_SUCCESS; 
					for (i = 4; i < Rxbuffer[3] && result == QUEUE_RESULT_SUCCESS ; ++i)
					{
						uint8_t data;
						result = QueueReadByte(uartSw->rxQueue,&data);
						if (result == QUEUE_RESULT_SUCCESS)
						{
							Txbuffer[i] = data;
							++Txbuffer[3];
						}
					}
				
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				

					uint16_t count;
					QueueGetBytesFreeInQueue(uartSw->txQueue, & count) ;
					if (count >255)
					{
						Txbuffer[3] = 255;
					}
					else
					{
						Txbuffer[3] = count;
					}
					QueueGetBytesFreeInQueue(uartSw->rxQueue, & count) ;
					if (count >255)
					{
						Txbuffer[4] = 255;
					}
					else
					{
						Txbuffer[4] = count;
					}
					QueuePeekByte(uartSw->rxQueue,&Txbuffer[5]);
				
			}
			break; 

		case CONFIGURE_CHANNEL_MODE_4: // Close Port
			{
				uartSw->txPin = 0xFF;
				uartSw->rxPin = 0xFF;
			}
			break; 

		case CONFIGURE_CHANNEL_MODE_5: 
			{  
				uartSw->txQueue = RXBUFFER16(3);
                uint16_t resultSize;
				if (QueueGetBytesFreeInQueue(uartSw->txQueue, &resultSize) != QUEUE_RESULT_SUCCESS)
				{
					error(SW_ERROR_UNNUMBERED_ERROR); // TODO future improvement: make errors based on result
				}
                else
                {
                    TXBUFFER16(5,resultSize);
                }
			}
			break; 

		case CONFIGURE_CHANNEL_MODE_6: 
			{  
				uartSw->rxQueue = RXBUFFER16(3);
                uint16_t resultSize;
				if (QueueGetBytesFreeInQueue(uartSw->txQueue, &resultSize) != QUEUE_RESULT_SUCCESS)
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
        else if ( QueueReadByte(uartSw->txQueue, & uartSw->txRemainingBitmap)== QUEUE_RESULT_SUCCESS ) 
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
                QueueAddByte(uartSw->rxQueue, uartSw->rxBitmap);
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
