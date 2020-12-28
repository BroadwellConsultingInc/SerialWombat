#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "serialWombat.h"


#define EUSART1_TX_BUFFER_SIZE 64
#define EUSART1_RX_BUFFER_SIZE 128

/**
  Section: Global Variables
*/
volatile uint8_t eusart1TxHead = 0;
volatile uint8_t eusart1TxTail = 0;
volatile uint8_t eusart1TxBufferRemaining;
volatile uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];

volatile uint8_t eusart1RxHead = 0;
volatile uint8_t eusart1RxTail = 0;
volatile uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
volatile uint8_t eusart1RxCount;
volatile eusart1_status_t eusart1RxLastError;

/**
  Section: EUSART1 APIs
*/





void EUSART1_DefaultFramingErrorHandler(void);
void EUSART1_DefaultOverrunErrorHandler(void);
void EUSART1_DefaultErrorHandler(void);

void EUSART1_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
   
    PIE1bits.TX1IE = 0;
    // Set the EUSART1 module to the options selected in the user interface.
    TX1STA = 0;
    RC1STA = 0;
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE enabled; ABDEN disabled; 
    BAUD1CON = 0x0A;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;

   
   

    
    eusart1RxLastError.status = 0;

    // initializing the driver state
    eusart1TxHead = 0;
    eusart1TxTail = 0;
    eusart1TxBufferRemaining = sizeof(eusart1TxBuffer);

    eusart1RxHead = 0;
    eusart1RxTail = 0;
    eusart1RxCount = 0;  
    RC1REG; // Clear any stored characters.
    RC1REG; 
    // enable receive interrupt
    PIE1bits.RC1IE = 1;
}

/*
bool EUSART1_is_tx_ready(void)
{
    return (eusart1TxBufferRemaining ? true : false);
}

bool EUSART1_is_rx_ready(void)
{
    return (eusart1RxCount ? true : false);
}

bool EUSART1_is_tx_done(void)
{
    return TX1STAbits.TRMT;
}

eusart1_status_t EUSART1_get_last_status(void){
    return eusart1RxLastError;
}
*/
uint8_t EUSART1_Read(void)
{
    uint8_t readValue  = 0;
    
    if (0 == eusart1RxCount)
    {
        return(0x55);
    }


    readValue = eusart1RxBuffer[eusart1RxTail++];
    if(sizeof(eusart1RxBuffer) <= eusart1RxTail)
    {
        eusart1RxTail = 0;
    }
    PIE1bits.RC1IE = 0;
    eusart1RxCount--;
    PIE1bits.RC1IE = 1;

    return readValue;
}

void EUSART1_Write(uint8_t txData)
{
    if(0 == eusart1TxBufferRemaining)
    {
        return;
    }

    if(0 == PIE1bits.TX1IE)
    {
        TX1REG = txData;
    }
    else
    {
        PIE1bits.TX1IE = 0;
        eusart1TxBuffer[eusart1TxHead++] = txData;
        if(sizeof(eusart1TxBuffer) <= eusart1TxHead)
        {
            eusart1TxHead = 0;
        }
        eusart1TxBufferRemaining--;
    }
    PIE1bits.TX1IE = 1;
}


void EUSART1_Transmit_ISR(void)
{

    // add your EUSART1 interrupt custom code
    if(sizeof(eusart1TxBuffer) > eusart1TxBufferRemaining)
    {
        TX1REG = eusart1TxBuffer[eusart1TxTail++];
        if(sizeof(eusart1TxBuffer) <= eusart1TxTail)
        {
            eusart1TxTail = 0;
        }
        eusart1TxBufferRemaining++;
    }
    else
    {
        PIE1bits.TX1IE = 0;
    }
}

void EUSART1_Receive_ISR(void)
{
    
    if(RC1STAbits.FERR){
        // EUSART1 error - restart

    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;
    }

       eusart1RxBuffer[eusart1RxHead++] = RC1REG;
    if(sizeof(eusart1RxBuffer) <= eusart1RxHead)
    {
        eusart1RxHead = 0;
    }
    eusart1RxCount++;
}







/**
  End of File
*/
                               //300  1200 2400  4800  9600  19.2  38.4  57.6  115.2
const uint8_t baudDivisorL[] = { 0x2A,0x0A,0x04, 0x82, 0x40, 0xA0, 0xCF, 0x8A, 0x43  };
const uint8_t baudDivisorH[] = { 0x68,0x1A,0x0D, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00};

void initUART()
{
    switch (Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:
        {
            CurrentPinRegister->generic.mode = PIN_MODE_UART_TXRX;
            if (Rxbuffer[3] >8)
            {
                Rxbuffer[3] = 8;
            }
           
            SP1BRGL = baudDivisorL[Rxbuffer[3]];
            SP1BRGH = baudDivisorH[Rxbuffer[3]];    
             
            if (Rxbuffer[4] < NUMBER_OF_PHYSICAL_PINS)
            {
            SetPin(Rxbuffer[4], DIGITAL_INPUT);
            
                RX1PPS = PPS_PORT | PinToPort[Rxbuffer[4]];
                
             
            }
            if (Rxbuffer[5] < NUMBER_OF_PHYSICAL_PINS)
            {
                SetPin(Rxbuffer[5], DIGITAL_LOW);
                
                PPS_ARRAY[PinToPort[Rxbuffer[5]]] = 0x05;   //RA2->EUSART1:TX1;
                
            }
            
            EUSART1_Initialize();
        }

        break;
         case CONFIGURE_CHANNEL_MODE_1:  //Transmit 
        {
            uint8_t i;
            for (i = 0; i < Rxbuffer[3]; ++i)
            {
                EUSART1_Write(Rxbuffer[4 + i]);
            }
            Txbuffer[3] = eusart1TxBufferRemaining;
            Txbuffer[4] = eusart1RxCount;
  
        }
         break;
        case CONFIGURE_CHANNEL_MODE_2:
        {
            Txbuffer[3] = 0;
            Rxbuffer[3] += 4;
            uint8_t i;
            for (i = 4; i < Rxbuffer[3] && eusart1RxCount != 0 ; ++i)
            {
               Txbuffer[i] = EUSART1_Read();
               ++Txbuffer[3];
            }
            
        }
        break;
        
        case CONFIGURE_CHANNEL_MODE_3: // Peek RX
        {
            Txbuffer[3] = eusart1TxBufferRemaining;
            Txbuffer[4] = eusart1RxCount;
            Txbuffer[5] = eusart1RxBuffer[eusart1RxTail];
        }
        break; 
        
    }
    
    
}
