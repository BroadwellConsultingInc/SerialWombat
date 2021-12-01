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

void initUARTSw()
{
    uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;
    
    
    /*
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0  &&
			CurrentPinRegister->generic.mode != PIN_MODE_UART0_TXRX &&
			CurrentPinRegister->generic.mode != PIN_MODE_UART0_TXRX)
	{
		// We're getting out of order configuration.  Return an error
		// and do nothing.	
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;

	}

*/

	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				

				uartSw->txPin = Rxbuffer[4];
                uartSw->rxPin = Rxbuffer[5];


				if (Rxbuffer[3] >7)
				{
					Rxbuffer[3] = 7;  //TODO make error
                    Txbuffer[3] = 7;
				}
/*
				if (Rxbuffer[2]  == PIN_MODE_UART0_TXRX)
				{    
					U1BRG=    baudDivisor[Rxbuffer[3]]; 
                    
				}
                else
                {
                    U2BRG=    baudDivisor[Rxbuffer[3]]; 
                }

				
				if (Rxbuffer[5] < NUMBER_OF_PHYSICAL_PINS)
				{
					SetPin(Rxbuffer[5], DIGITAL_HIGH);

					if (Rxbuffer[2] == PIN_MODE_UART0_TXRX)
					{    
						SetPPSOutput(CurrentPin, 0x03);  //UART 1 
					}
					else
					{
						SetPPSOutput(CurrentPin, 0x05);    //UART 2

					}
     
                    PinUpdateRegisters[Rxbuffer[5]].generic.mode = PIN_MODE_CONTROLLED;
				}
				CurrentPinRegister->generic.mode = Rxbuffer[2];
				
                uartHw->baudRate = Rxbuffer[3];
                uartHw->rxPin = Rxbuffer[4];
                uartHw->txPin = Rxbuffer[5];
               */ 
                PinInput(uartSw->rxPin);
                PinLow(uartSw->txPin);
                CurrentPinRegister->generic.mode = PIN_MODE_SW_UART;
                uartSw-> divisor  = 6;
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
                               
        }
        break;
        /*
				uint8_t i;
				if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
				{    
					for (i = 0; i < Rxbuffer[3]; ++i)
					{
						UART1_Write(Rxbuffer[4 + i]);
					}
					Txbuffer[3] = UART1_TransmitBufferSizeGet() ;
					Txbuffer[4] = UART1_CONFIG_RX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet();
				}
				else if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
				{
					for (i = 0; i < Rxbuffer[3]; ++i)
					{
						UART2_Write(Rxbuffer[4 + i]);
					}
					Txbuffer[3] = UART2_TransmitBufferSizeGet() ;
					Txbuffer[4] = UART2_CONFIG_RX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet();

				}
			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
				Txbuffer[3] = 0;
				Rxbuffer[3] += 4;
				uint8_t i;
				if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
				{    
					for (i = 4; i < Rxbuffer[3] && (UART1_CONFIG_RX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet()) != 0 ; ++i)
					{
						Txbuffer[i] = UART1_Read();
						++Txbuffer[3];
					}
				}
				else if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
				{    
					for (i = 4; i < Rxbuffer[3] && (UART2_CONFIG_RX_BYTEQ_LENGTH -  UART2_ReceiveBufferSizeGet()) != 0 ; ++i)
					{
						Txbuffer[i] = UART2_Read();
						++Txbuffer[3];
					}

				}
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
				{    
					Txbuffer[3] = UART1_TransmitBufferSizeGet() ;
					Txbuffer[4] = UART1_CONFIG_RX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet();
					Txbuffer[5] = UART1_Peek(0);
				}
				else if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
				{

					Txbuffer[3] = UART2_TransmitBufferSizeGet() ;
					Txbuffer[4] = UART2_CONFIG_RX_BYTEQ_LENGTH -  UART2_ReceiveBufferSizeGet();
					Txbuffer[5] = UART2_Peek(0);

				}
			}
			break; 
            
            case CONFIGURE_CHANNEL_MODE_4: // Close Port
			{
				if (uartSw->txPin != 0xFF)
                {
                    SetPPSOutput(uartHw->txPin, 0); //Return to GPIO
                    PinHigh(uartHw->txPin);
                    if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
                    {
                        UART1_Disable();
                    }
                    else if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
                    {
                        UART2_Disable();
                    }
                }
			}
			break; 
*/
          case CONFIGURE_CHANNEL_MODE_5: 
			{  //TODO add sanity checks, mode, etc
				uartSw->txQueue = RXBUFFER16(3);
                if (QueueByteInitialize(uartSw->txQueue, RXBUFFER16(5)) != QUEUE_RESULT_SUCCESS)
                {
                    error(0); // TODO make errors based on result
                }
			}
			break; 
          case CONFIGURE_CHANNEL_MODE_6: 
			{  //TODO add sanity checks, mode, etc
				uartSw->rxQueue = RXBUFFER16(3);
                if (QueueByteInitialize(uartSw->rxQueue, RXBUFFER16(5)) != QUEUE_RESULT_SUCCESS)
                {
                    error(0); // TODO make errors based on result
                }
			}
			break; 
	}


}



void updateUARTSwTx()
{
    
 
    uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;
   
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
            /*
            
             uartSw->txCurrentBit = uartSw->txRemainingBitmap & 0x01;
            uartSw->txRemainingBitmap >>= 1;
            -- uartSw->txRemainingBits;
             if (uartSw->txRemainingBits == 0)
                {
                    uartSw->txCurrentBit = 1; // stop bit
                }
            uartSw->txRemainingNips = uartSw->divisor;
            while (uartSw->txRemainingBits)
            {
                uint8_t newbit = uartSw->txRemainingBitmap & 0x01;
                if (uartSw->txRemainingBits == 1)
                {
                    newbit = 1;
                }
                if (newbit == uartSw->txCurrentBit)
                {
                          -- uartSw->txRemainingBits;
                          uartSw->txRemainingBitmap >>= 1;
                          uartSw->txRemainingNips += uartSw->divisor;
                          if (uartSw->txRemainingBits == 0)
                          {
                              uartSw->txRemainingNips = updateBitStreamOutput(uartSw->txPin, uartSw->txCurrentBit,  uartSw->txRemainingNips, &uartSw->bitStream);
                          }
                }
                else
                {
                    uartSw->txRemainingNips = updateBitStreamOutput(uartSw->txPin, uartSw->txCurrentBit,  uartSw->txRemainingNips, &uartSw->bitStream);
                    break;
                }
                
            } */
            
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
            
            //TODO optimize:  Add bitstream remove function that removes idled bits at the beginning of next call 
            idle = 1;
        }
        
    }
	        	
}



uint16_t debugBadBytes= 0; //TODO REMOVE
uint8_t debugSamplePoint[8];
uint8_t debugStartPoint;
uint8_t debugStopPoint;
uint8_t debugStartBegin = 0;
uint8_t debugIdleSampleDelay = 0;

uint8_t debugSampleFC[8];
uint8_t debugStartBeginFC;
uint8_t debugStopFC;
uint8_t debugStartSampleFC = 0;
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
            --uartSw->rxSampleDelay;
            inputBit = PulseInGetOldestDMABit(uartSw->rxPin);
        //    SetPin(14,(inputBit & 0x02) > 0);
        //    SetPin(15,(inputBit & 0x01) > 0);
        //    PinHigh(11);
         //       PinLow(11);
                
            if (uartSw->rxSampleDelay > 0 || inputBit == 2)
            {
                
                      continue;
          
            }
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
                debugStartBegin = CurrentPinRegister->pulse_input.lastDMA;
                debugStartBeginFC = FramesRun;
            }
        }
        break;
        
    case UART_SW_RX_STATE_SAMPLE_START:
        {
            debugStartPoint = CurrentPinRegister->pulse_input.lastDMA;
            debugStartSampleFC = FramesRun;
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
            debugSamplePoint[uartSw->rxBitsReceived] = CurrentPinRegister->pulse_input.lastDMA;
                debugSampleFC[uartSw->rxBitsReceived] = FramesRun;
            ++ uartSw->rxBitsReceived;
            if (uartSw->rxBitsReceived >= 8)
            {
                if (uartSw->rxBitmap & 0x80)
                {
                    ++debugBadBytes;
                }
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
                debugIdleSampleDelay = uartSw->rxSampleDelay;
                debugStopPoint = CurrentPinRegister->pulse_input.lastDMA;
                debugStopFC = FramesRun;
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
     //SetPin(14,(inputBit & 0x02) > 0);
      //      SetPin(15,(inputBit & 0x01) > 0);
    }
}

void updateUARTSw()
{
    uartSw_t* uartSw = (uartSw_t*)CurrentPinRegister;
	/*
     if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
	    {    
		    CurrentPinRegister->generic.buffer = UART1_ReceiveBufferSizeGet();
	    }
	    else if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {           
		    CurrentPinRegister->generic.buffer = UART2_ReceiveBufferSizeGet();  
	    }
	    */

    if (uartSw->txPin != 0xFF)
    {
	updateUARTSwTx();
    }
    if (uartSw->rxPin != 0xFF)
    {
        updateUARTSwRx();
    }
}
