#include "serialWombat.h"
#include "mcc_generated_files/mcc.h"


//TODO update
//300  1200 2400  4800  9600  19.2  38.4  57.6  115.2
const uint8_t baudDivisorL[] = { 0x2A,0x0A,0x04, 0x82, 0x40, 0xA0, 0xCF, 0x8A, 0x43  };
const uint8_t baudDivisorH[] = { 0x68,0x1A,0x0D, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00};

void initUART()
{

    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0  &&
	CurrentPinRegister->generic.mode != PIN_MODE_UART0_TXRX &&
	CurrentPinRegister->generic.mode != PIN_MODE_UART1_TXRX)
    {
	// We're getting out of order configuration.  Return an error
	// and do nothing.	
	error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
	return;

    }

    if (!pinIsPPSCapable(Rxbuffer[1]))
    {
	    error(SW_ERROR_PIN_NOT_CAPABLE);
	    return;
    }
    

    switch (Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:
        {
	    if (Rxbuffer[2] == PIN_MODE_UART1_TXRX)
	    {    
		    if (UART1Semaphore != RESOURCE_AVAILABLE)
		    {
			    error (SW_ERROR_HW_RESOURCE_IN_USE);
			    return;
		    }
	    }
	    else
	    {
		    if (UART2Semaphore != RESOURCE_AVAILABLE)
		    {
			    error (SW_ERROR_HW_RESOURCE_IN_USE);
			    return;
		    }
	    }
     
            CurrentPinRegister->generic.mode = Rxbuffer[2];
            if (Rxbuffer[3] >8)
            {
                Rxbuffer[3] = 8;
            }
    		   
	    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {    
//TODO		    SP1BRGL = baudDivisorL[Rxbuffer[3]];
//TODO		    SP1BRGH = baudDivisorH[Rxbuffer[3]];    
	    }
             
            if (Rxbuffer[4] < NUMBER_OF_PHYSICAL_PINS)
            {
		    SetPin(Rxbuffer[4], DIGITAL_INPUT);
            
		    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
		    {    
//TODO			RX1PPS = PPS_PORT | PinToPort[Rxbuffer[4]];
		    }
                
             
            }
            if (Rxbuffer[5] < NUMBER_OF_PHYSICAL_PINS)
            {
                SetPin(Rxbuffer[5], DIGITAL_LOW);
                
		    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
		    {    
			 SetPPSOutput(CurrentPin, 0x03);  //UART 1 
		    }
		    else
		    {
			 SetPPSOutput(CurrentPin, 0x05);    //UART 2

		    }
            }
            
	    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {    
		    UART1_Initialize();
	    }
	    else
	    {
		    UART2_Initialize();
	    }
        }

        break;
         case CONFIGURE_CHANNEL_MODE_1:  //Transmit 
        {
            uint8_t i;
	    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {    
		    for (i = 0; i < Rxbuffer[3]; ++i)
		    {
			    UART1_Write(Rxbuffer[4 + i]);
		    }
		    Txbuffer[3] = UART1_TransmitBufferSizeGet() ;
		    Txbuffer[4] = UART1_CONFIG_TX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet();
	    }
	    else
	    {
		    for (i = 0; i < Rxbuffer[3]; ++i)
		    {
			    UART2_Write(Rxbuffer[4 + i]);
		    }
//TODO		    Txbuffer[3] = UART2_TransmitBufferSizeGet() ;
//TODO		    Txbuffer[4] = UART2_CONFIG_TX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet();

	    }
        }
         break;
        case CONFIGURE_CHANNEL_MODE_2:
        {
            Txbuffer[3] = 0;
            Rxbuffer[3] += 4;
            uint8_t i;
	    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {    
		    for (i = 4; i < Rxbuffer[3] && (UART1_CONFIG_TX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet()) != 0 ; ++i)
		    {
			    Txbuffer[i] = UART1_Read();
			    ++Txbuffer[3];
		    }
	    }
	    else 
	    {    
/*TODO		    for (i = 4; i < Rxbuffer[3] && (UART2_CONFIG_TX_BYTEQ_LENGTH -  UART2_ReceiveBufferSizeGet()) != 0 ; ++i)
		    {
			    Txbuffer[i] = UART2_Read();
			    ++Txbuffer[3];
		    }
 * */
	    }
        }
        break;
        
        case CONFIGURE_CHANNEL_MODE_3: // Peek RX
        {
	    if (CurrentPinRegister->generic.mode == PIN_MODE_UART1_TXRX)
	    {    
		    Txbuffer[3] = UART1_TransmitBufferSizeGet() ;
		    Txbuffer[4] = UART1_CONFIG_TX_BYTEQ_LENGTH -  UART1_ReceiveBufferSizeGet();
		    Txbuffer[5] = UART1_Peek(0);
	    }
	    else
	    {
            /*TODO
		    Txbuffer[3] = UART2_TransmitBufferSizeGet() ;
		    Txbuffer[4] = UART2_CONFIG_TX_BYTEQ_LENGTH -  UART2_ReceiveBufferSizeGet();
		    Txbuffer[5] = UART2_Peek(0);
             */
	    }
        }
        break; 
        
    }
    
    
}
