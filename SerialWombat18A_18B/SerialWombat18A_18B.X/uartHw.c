#include "serialWombat.h"
#include "mcc_generated_files/mcc.h"


typedef struct uartHw_n{
    uint8_t txPin;
    uint8_t rxPin;
    uint8_t baudRate;
}uartHw_t;

//300  1200 2400  4800  9600  19.2  38.4  57.6  115.2  
const uint16_t baudDivisor[] = { 13332,3332,1666, 832, 416, 207, 103, 68, 34  };


void initUARTHw()
{
    uartHw_t* uartHw = (uartHw_t*)CurrentPinRegister;
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0  &&
			CurrentPinRegister->generic.mode != PIN_MODE_UART0_TXRX &&
			CurrentPinRegister->generic.mode != PIN_MODE_UART1_TXRX)
	{
		// We're getting out of order configuration.  Return an error
		// and do nothing.	
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;

	}



	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{

				if (!pinIsPPSCapable(Rxbuffer[1]))
				{
					error(SW_ERROR_PIN_NOT_CAPABLE);
					return;
				}
				if (Rxbuffer[4] != 0xFF && !pinIsPPSCapable(Rxbuffer[4]))
				{
					error(SW_ERROR_PIN_NOT_CAPABLE);
					return;
				}
				if (Rxbuffer[5] != 0xFF && !pinIsPPSCapable(Rxbuffer[5]))
				{
					error(SW_ERROR_PIN_NOT_CAPABLE);
					return;
				}

                if (Rxbuffer[3] >8)
				{
				  error(SW_ERROR_INVALID_PARAMETER_3);
                  return;
				}

				if (Rxbuffer[2] == PIN_MODE_UART0_TXRX)
				{    
					if (UART1Semaphore != RESOURCE_AVAILABLE  && UART1Semaphore != CurrentPin)
					{
						error (SW_ERROR_HW_RESOURCE_IN_USE);
						return;
					}


					if (Rxbuffer[4] != 0xFF)
					{
                        PinInput(Rxbuffer[4]);
                        SetPinPullUp(Rxbuffer[4],1);
						RPINR18bits.U1RXR = pinPPSInputMap[Rxbuffer[4]];
                        
                        PinUpdateRegisters[Rxbuffer[4]].generic.mode = PIN_MODE_CONTROLLED;
					}
					UART1_Initialize();
                    
                    if (Rxbuffer[4] != 0xFF)
                    {
                        SetPinPullUp(Rxbuffer[4],0);
                    }
                        
                        
				}
				else
				{
					if (UART2Semaphore != RESOURCE_AVAILABLE && UART2Semaphore != CurrentPin)
					{
						error (SW_ERROR_HW_RESOURCE_IN_USE);
						return;
					}
					
					if (Rxbuffer[4] != 0xFF)
					{
						RPINR19bits.U2RXR = pinPPSInputMap[Rxbuffer[4]];
                        PinInput(Rxbuffer[4]);
                        PinUpdateRegisters[Rxbuffer[4]].generic.mode = PIN_MODE_CONTROLLED;
                    }
					UART2_Initialize();
				}


				

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
						SetPPSOutput(Rxbuffer[5], 0x03);  //UART 1 
					}
					else
					{
						SetPPSOutput(Rxbuffer[5], 0x05);    //UART 2

					}
     
                    PinUpdateRegisters[Rxbuffer[5]].generic.mode = PIN_MODE_CONTROLLED;
				}
				CurrentPinRegister->generic.mode = Rxbuffer[2];
				
                uartHw->baudRate = Rxbuffer[3];
                uartHw->rxPin = Rxbuffer[4];
                uartHw->txPin = Rxbuffer[5];
                
			}

			break;
		case CONFIGURE_CHANNEL_MODE_1:  //Transmit 
			{
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
					Txbuffer[4] = UART2_CONFIG_RX_BYTEQ_LENGTH -  UART2_ReceiveBufferSizeGet();

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
				if (uartHw->txPin != 0xFF)
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

	}


}

void updateUARTHw()
{
     if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
	    {    
		    CurrentPinRegister->generic.buffer = UART1_ReceiveBufferSizeGet();
	    }
	    else if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {           
		    CurrentPinRegister->generic.buffer = UART2_ReceiveBufferSizeGet();  
	    }
}
