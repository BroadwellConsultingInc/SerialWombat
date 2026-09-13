#include "serialWombat.h"
#include "debug.h"

/*
 * CH32V006 hardware UART pin assignments.
 *
 * UART0 / USART1: TX = WP4 / PD5, RX = WP5 / PD6
 * UART1 / USART2: TX = WP1 / PD2, RX = WP2 / PD3
 */
#define UART0_RXPIN 5
#define UART0_TXPIN 4
#define UART1_RXPIN 2
#define UART1_TXPIN 1

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


/*
 * Retain unused CH32V003 source declarations for examination and later removal.
 */
#ifdef KEEP_CH32V003_UNUSED_UART_CODE
#define TxSize1    (size(TxBuffer1))
#define size(a)    (sizeof(a) / sizeof(*(a)))

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;
#endif


static uint8_t getUARTHardware(uint8_t mode, USART_TypeDef **USARTx, uint8_t *rxPin, uint8_t *txPin)
{
    if (mode == PIN_MODE_UART0_TXRX)
    {
        *USARTx = USART1;
        *rxPin = UART0_RXPIN;
        *txPin = UART0_TXPIN;
        return 1;
    }
    else if (mode == PIN_MODE_UART1_TXRX)
    {
        *USARTx = USART2;
        *rxPin = UART1_RXPIN;
        *txPin = UART1_TXPIN;
        return 1;
    }

    return 0;
}


/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the selected USART peripheral.
 *
 * @return  none
 */
static void USARTx_CFG(uint8_t mode, uint32_t baudRate)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};
    USART_TypeDef *USARTx;
    uint8_t rxPin;
    uint8_t txPin;

    if (!getUARTHardware(mode, &USARTx, &rxPin, &txPin))
    {
        return;
    }

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD | RCC_PB2Periph_AFIO, ENABLE);

    if (mode == PIN_MODE_UART0_TXRX)
    {
        RCC_PB2PeriphClockCmd(RCC_PB2Periph_USART1, ENABLE);

        /* USART1 TX-->D.5   RX-->D.6 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOD, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    }
    else
    {
        RCC_PB2PeriphClockCmd(RCC_PB2Periph_USART2, ENABLE);

        /* USART2 partial remap 3: TX-->D.2   RX-->D.3 */
        GPIO_PinRemapConfig(GPIO_PartialRemap3_USART2, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOD, &GPIO_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    }

    USART_Cmd(USARTx, DISABLE);
    USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);

    USART_InitStructure.USART_BaudRate = baudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USARTx, &USART_InitStructure);
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USARTx, ENABLE);
}


#ifdef PIN_MODE_UART0_TXRX_ENABLE
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      USART1_IRQHandler
 *
 * @brief   This function handles USART1 global interrupt request.
 *
 * @return  none
 */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        void* queueAddressstack = queueAddress;
        queueAddress =  &PinUpdateRegisters[UART0_RXPIN];
        QueueAddByte((uint8_t)USART_ReceiveData(USART1));
        queueAddress = queueAddressstack;
    }

    if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
    {
        void* queueAddressstack = queueAddress;
        queueAddress = &PinUpdateRegisters[UART0_TXPIN];
        uint8_t data;
        if (QueueReadByte(&data) == QUEUE_RESULT_SUCCESS)
        {
            USART_SendData(USART1,data);
        }
        else
        {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
        queueAddress = queueAddressstack;
    }
}
#endif


#ifdef PIN_MODE_UART1_TXRX_ENABLE
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      USART2_IRQHandler
 *
 * @brief   This function handles USART2 global interrupt request.
 *
 * @return  none
 */
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        void* queueAddressstack = queueAddress;
        queueAddress =  &PinUpdateRegisters[UART1_RXPIN];
        QueueAddByte((uint8_t)USART_ReceiveData(USART2));
        queueAddress = queueAddressstack;
    }

    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {
        void* queueAddressstack = queueAddress;
        queueAddress = &PinUpdateRegisters[UART1_TXPIN];
        uint8_t data;
        if (QueueReadByte(&data) == QUEUE_RESULT_SUCCESS)
        {
            USART_SendData(USART2,data);
        }
        else
        {
            USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
        }
        queueAddress = queueAddressstack;
    }
}
#endif


void initUARTHw()
{
    uartHw_t* uartHw = (uartHw_t*)CurrentPinRegister;
    USART_TypeDef *USARTx;
    uint8_t rxPin;
    uint8_t txPin;
    uint8_t mode;

    if (Rxbuffer[0] == CONFIGURE_CHANNEL_MODE_0)
    {
        mode = Rxbuffer[2];
    }
    else
    {
        mode = CurrentPinRegister->generic.mode;
    }

    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0  &&
            CurrentPinRegister->generic.mode != PIN_MODE_UART0_TXRX &&
            CurrentPinRegister->generic.mode != PIN_MODE_UART1_TXRX)
    {
        // We're getting out of order configuration.  Return an error
        // and do nothing.
        error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
        return;
    }

    if (!getUARTHardware(mode, &USARTx, &rxPin, &txPin))
    {
        error(SW_ERROR_PIN_NOT_CAPABLE);
        return;
    }

    /* The UART mode is owned by its fixed RX pin. */
    if (Rxbuffer[1] != rxPin)
    {
        error (SW_ERROR_PIN_NOT_CAPABLE);
        return;
    }

    switch (Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:
            {
                if (Rxbuffer[3] >8)
                {
                    error(SW_ERROR_INVALID_PARAMETER_3);
                    return;
                }

                if (Rxbuffer[4] != rxPin || Rxbuffer[5] != txPin)
                {
                    error (SW_ERROR_PIN_NOT_CAPABLE);
                    return;
                }

                PinUpdateRegisters[txPin].generic.mode = PIN_MODE_CONTROLLED;
                CurrentPinRegister->generic.mode = mode;

                uartHw->baudRate = Rxbuffer[3];
                uartHw->rxPin = rxPin;
                uartHw->txPin = txPin;

                void* queueAddressstack = queueAddress;
                queueAddress = &uartHw->rxQueue;
                QueueByteInitialize(UART_QUEUE_LENGTH);
                queueAddress = &PinUpdateRegisters[txPin]; // Set up Tx queue
                QueueByteInitialize(UART_QUEUE_LENGTH);
                queueAddress = queueAddressstack;

                USARTx_CFG(mode, baudDivisor[Rxbuffer[3]]);
            }
            break;

        case CONFIGURE_CHANNEL_MODE_1:  //Transmit
            {
                USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
                queueCONFIGURE_CHANNEL_MODE_1_transmit(uartHw->rxQueue,&PinUpdateRegisters[txPin]);
                USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
            }
            break;

        case CONFIGURE_CHANNEL_MODE_2:
            {
                USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
                queueCONFIGURE_CHANNEL_MODE_2_receive(uartHw->rxQueue);
                USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
            }
            break;

        case CONFIGURE_CHANNEL_MODE_3: // Peek RX
            {
                queueCONFIGURE_CHANNEL_MODE_3_peekRX(uartHw->rxQueue, &PinUpdateRegisters[txPin]);
            }
            break;

        case CONFIGURE_CHANNEL_MODE_4: // Close Port
            {
                GPIO_InitTypeDef GPIO_InitStructure = {0};
                uint16_t gpioTxPin;
                uint16_t gpioRxPin;

                USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
                USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
                USART_Cmd(USARTx, DISABLE);

                if (mode == PIN_MODE_UART0_TXRX)
                {
                    gpioTxPin = GPIO_Pin_5;
                    gpioRxPin = GPIO_Pin_6;
                }
                else
                {
                    gpioTxPin = GPIO_Pin_2;
                    gpioRxPin = GPIO_Pin_3;
                }

                /* Return TX to GPIO and leave it in the normal UART idle-high state. */
                GPIO_SetBits(GPIOD, gpioTxPin);
                GPIO_InitStructure.GPIO_Pin = gpioTxPin;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
                GPIO_Init(GPIOD, &GPIO_InitStructure);

                GPIO_InitStructure.GPIO_Pin = gpioRxPin;
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
                GPIO_Init(GPIOD, &GPIO_InitStructure);
            }
            break;

        //why does serial support  5 and 6? -  Answer define queues

        default:
            {
                error(SW_ERROR_INVALID_COMMAND);
            }
            break;
    }
}


void updateUARTHw()
{
    uartHw_t* uartHw = (uartHw_t*)CurrentPinRegister;
    USART_TypeDef *USARTx;
    uint8_t rxPin;
    uint8_t txPin;
    uint16_t bytesAvailable = 0;

    if (!getUARTHardware(CurrentPinRegister->generic.mode, &USARTx, &rxPin, &txPin))
    {
        return;
    }

    /* Match the SW18AB behavior: public data is the number of received bytes waiting. */
    USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);

    void* queueAddressstack = queueAddress;
    queueAddress = &uartHw->rxQueue;
    QueueGetBytesFilledInQueue(&bytesAvailable);
    queueAddress = queueAddressstack;

    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    CurrentPinRegister->generic.buffer = bytesAvailable;
}
