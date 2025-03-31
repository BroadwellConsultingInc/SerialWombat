#include "serialWombat.h"


#define RXPIN 5 // WP5 is RX,
#define TXPIN 4 // WP4 is TX,




#define UART_QUEUE_LENGTH 64
typedef struct uartHw_n{
    uint8_t rxQueue[UART_QUEUE_LENGTH +8];
    uint8_t txPin;
    uint8_t rxPin;
    uint8_t baudRate;

}uartHw_t;

typedef struct uartHw_tx_n{
    uint8_t txQueue[UART_QUEUE_LENGTH + 8];

}uartHw_tx_t;
//300  1200 2400  4800  9600  19.2  38.4  57.6  115.2
const uint32_t baudDivisor[] = { 300,1200,2400, 4800, 9600, 19200, 38400, 57600, 115200  };



#include "debug.h"

/* Global define */
#define TxSize1    (size(TxBuffer1))
#define size(a)    (sizeof(a) / sizeof(*(a)))

/* Global typedef */
typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;




/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
static void USARTx_CFG(uint32_t baudRate)  //TODO optimize without API calls
{
	GPIO_InitTypeDef  GPIO_InitStructure = {0};
	USART_InitTypeDef USART_InitStructure = {0};
	NVIC_InitTypeDef  NVIC_InitStructure = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

	/* USART1 TX-->D.5   RX-->D.6 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //TODO probably need to be lower priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

#ifdef PIN_MODE_UART0_TXRX_ENABLE



void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      USART1_IRQHandler
 *
 * @brief   This function handles USART3 global interrupt request.
 *
 * @return  none
 */
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		void* queueAddressstack = queueAddress;
		queueAddress =  &PinUpdateRegisters[RXPIN]; //Get Rx pin address
			QueueAddByte( USART_ReceiveData(USART1));
			queueAddress = queueAddressstack;


	}
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
		void* queueAddressstack = queueAddress;
		queueAddress = &PinUpdateRegisters[TXPIN];//Get tx pin address
		uint8_t data;
		if (QueueReadByte(&data) == QUEUE_RESULT_SUCCESS)
		{
			USART_SendData(USART1,data);

		}
		else {
		    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
		queueAddress = queueAddressstack;
	}
}
#endif


void initUARTHw()
{
	uartHw_t* uartHw = (uartHw_t*)CurrentPinRegister;
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0  &&
			CurrentPinRegister->generic.mode != PIN_MODE_UART0_TXRX )
	{
		// We're getting out of order configuration.  Return an error
		// and do nothing.
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;

	}
	if (Rxbuffer[1] != 5)  // Wombat Pin 5 must be RX, Wombat pin 4 must be TX
	{
		error (SW_ERROR_PIN_NOT_CAPABLE);
		return;
	}

	switch (Rxbuffer[0])
	{
		//TODO add pin mode check for _1 and up,  must be RX hardware pin
		case CONFIGURE_CHANNEL_MODE_0:
			{


				if (Rxbuffer[3] >8)
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
					return;
				}

				if (Rxbuffer[4] == RXPIN && Rxbuffer[5] == TXPIN) //   Rx must be on 5, TX on 4
				{
					// OK.  continue with config


				}
				else {
					error (SW_ERROR_PIN_NOT_CAPABLE);
					return;
				}


				PinUpdateRegisters[TXPIN].generic.mode = PIN_MODE_CONTROLLED;

				CurrentPinRegister->generic.mode = Rxbuffer[2];

				uartHw->baudRate = Rxbuffer[3];

				queueAddress = &uartHw->rxQueue;
				QueueByteInitialize(UART_QUEUE_LENGTH);
				queueAddress = &PinUpdateRegisters[TXPIN]; // Set up Tx queue
				QueueByteInitialize(UART_QUEUE_LENGTH);
				USARTx_CFG(baudDivisor[Rxbuffer[3]]);

			}

			break;
		case CONFIGURE_CHANNEL_MODE_1:  //Transmit
			{
				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
				queueCONFIGURE_CHANNEL_MODE_1_transmit(uartHw->rxQueue,&PinUpdateRegisters[TXPIN]);
				USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //TODO will this kick off the interrupt sequence?  or do we need to force the first one?

			}
			break;
		case CONFIGURE_CHANNEL_MODE_2:
			{
				USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
				queueCONFIGURE_CHANNEL_MODE_2_receive(uartHw->rxQueue);
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				queueCONFIGURE_CHANNEL_MODE_3_peekRX(uartHw->rxQueue, &PinUpdateRegisters[TXPIN]);
			}
			break;

		case CONFIGURE_CHANNEL_MODE_4: // Close Port
			{

			}
			break;

			//TODO why does serial support  5 and 6? -  Answer define queues

		default:
			{
				error(SW_ERROR_INVALID_COMMAND);
			}
			break;

	}


}

void updateUARTHw()
{

	//TODO CurrentPinRegister->generic.buffer = UART1_ReceiveBufferSizeGet();

}
