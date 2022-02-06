
#include "serialWombat.h"
#include <stdint.h>

typedef enum {
	KEYPAD_STATE_SETUP_ROW_0 = 0,
	KEYPAD_STATE_WAIT_ROW_0,
	KEYPAD_STATE_READ_ROW_0,
	KEYPAD_STATE_SETUP_ROW_1 ,
	KEYPAD_STATE_WAIT_ROW_1,
	KEYPAD_STATE_READ_ROW_1,
	KEYPAD_STATE_SETUP_ROW_2 ,
	KEYPAD_STATE_WAIT_ROW_2,
	KEYPAD_STATE_READ_ROW_2,
	KEYPAD_STATE_SETUP_ROW_3 ,
	KEYPAD_STATE_WAIT_ROW_3,
	KEYPAD_STATE_READ_ROW_3,
	KEYPAD_STATE_IDLE,
}KEYPAD_STATE_t;

#define KEYPAD_BUFFER_MODE_BINARY 0
#define KEYPAD_BUFFER_CURRENT_BUTTON 1
#define KEYPAD_BUFFER_MODE_LAST_BUTTON 2
#define KEYPAD_BUFFER_MODE_LAST_ASCII 3

#define KEYPAD_QUEUE_MODE_BUTTON_INDEX 0
#define KEYPAD_QUEUE_MODE_BUTTON_ASCII 1

static const uint8_t KeypadAscii[] =
{
  '1',
  '2',
  '3',
  'A',
  '4',
  '5',
  '6',
  'B',
  '7',
  '8',
  '9',
  'C',
  '*',
  '0',
  '#',
  'D',
};

typedef struct matrixKeypad_n{
	uint16_t currentReading;
	uint16_t previousReading;
    uint16_t queueMask;
	uint8_t colPins[4];
	uint8_t rowPins[4];
    KEYPAD_STATE_t state;
    uint8_t timingPinMemory;
    uint8_t queuePinMemory;
    uint8_t countPinMemory;
	uint8_t queueMode;
	uint8_t bufferMode;
	uint8_t delayPeriod;
	uint8_t delayRemaining;

} matrixKeypad_t;

matrixKeypad_t* debugMatrixKeypad;

#define SIZE_OF_KEYPAD_QUEUE 32
static uint8_t matrixKeypadQueueAvailable()
{
    matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
    if (matrixKeypad->queuePinMemory == 0xFF)
    {
        return 0;
    }
    uint8_t* queueArray = (uint8_t*) &PinUpdateRegisters[matrixKeypad->queuePinMemory];
    
     uint8_t i;
        for (i = 0; i < SIZE_OF_KEYPAD_QUEUE - 1 ; ++i)
        {
            if (queueArray[i] == 0xFF)
            {
                break;
            }
        }
     return (i);
}

static void matrixKeypadQueueAdd(uint8_t valueToAdd)
{
    matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
    if (matrixKeypad->queuePinMemory == 0xFF)
    {
        return;
    }
    uint8_t* queueArray = (uint8_t*) &PinUpdateRegisters[matrixKeypad->queuePinMemory];
    
     uint8_t i;
        for (i = 0; i < SIZE_OF_KEYPAD_QUEUE - 1 ; ++i)
        {
            if (queueArray[i] == 0xFF)
            {
                queueArray[i] = valueToAdd;
                break;
            }
        }
}

static int16_t matrixKeypadQueueRead()
{
    matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
    if (matrixKeypad->queuePinMemory == 0xFF)
    {
        return -1;
    }
    uint8_t* queueArray = (uint8_t*) &PinUpdateRegisters[matrixKeypad->queuePinMemory];
    
    if (queueArray[0] == 0xFF)
    {
        return (-1);
    }
   
        uint8_t returnVal = queueArray[0];
        uint8_t i;
        for (i = 0; i < SIZE_OF_KEYPAD_QUEUE - 1 ; ++i)
        {
            queueArray[i] = queueArray[i + 1];
        }
        queueArray[SIZE_OF_KEYPAD_QUEUE - 1] = 0xFF;
        return (returnVal);
    
}

static int16_t matrixKeypadQueuePeek()
{
     matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
    if (matrixKeypad->queuePinMemory == 0xFF)
    {
        return -1 ;
    }
    uint8_t* queueArray = (uint8_t*) &PinUpdateRegisters[matrixKeypad->queuePinMemory];
    
    if (queueArray[0] == 0xFF)
    {
        return (-1);
    }
    else
    {
        return (queueArray[0]);
    }
}

static void matrixKeypadQueueInit()
{
    matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
    if (matrixKeypad->queuePinMemory == 0xFF)
    {
        return;
    }
    uint8_t* queueArray = (uint8_t*) &PinUpdateRegisters[matrixKeypad->queuePinMemory];
    
    uint8_t i;
    for (i = 0; i < SIZE_OF_KEYPAD_QUEUE; ++i)
    {
        queueArray[i] = 0;
    }
    
}

void initMatrixKeypad (void)
{
	matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
	debugMatrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinRegister->generic.mode = PIN_MODE_MATRIX_KEYPAD;
				matrixKeypad->timingPinMemory = 0xFF;
				matrixKeypad->queuePinMemory = 0xFF;
                matrixKeypad->queueMask = 0xFFFF;
				matrixKeypad->state=  KEYPAD_STATE_IDLE;
				matrixKeypad->rowPins[0] = Rxbuffer[3];
				matrixKeypad->rowPins[1]  = Rxbuffer[4];
				matrixKeypad->rowPins[2]  = Rxbuffer[5];
				matrixKeypad->rowPins[3]  = Rxbuffer[6];
				matrixKeypad->colPins[0] = Rxbuffer[7];

				uint8_t i;
				for (i = 0; i < 4; ++i)
				{
					if (matrixKeypad->rowPins[i] < NUMBER_OF_PHYSICAL_PINS)
					{
						if (matrixKeypad->rowPins[i] != CurrentPin)
						{
							PinUpdateRegisters[matrixKeypad->rowPins[i]].generic.mode = PIN_MODE_CONTROLLED;
						}     
						PinInput(matrixKeypad->rowPins[i]);
					}
				}
				if (matrixKeypad->colPins[0] != CurrentPin)
				{
					PinUpdateRegisters[matrixKeypad->colPins[0]].generic.mode = PIN_MODE_CONTROLLED;
				}

				SetPinPullUp(matrixKeypad->colPins[0],1);


			}
			break;
			/* Not applicable.  Reserved to be consistent with other stream interfaces
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
			   */
		case CONFIGURE_CHANNEL_MODE_2:
			{
				Txbuffer[3] = 0;
				Rxbuffer[3] += 4;
				uint8_t i;

				for (i = 4; i < Rxbuffer[3] && (matrixKeypadQueueAvailable()) != 0 ; ++i)
				{
					Txbuffer[i] = matrixKeypadQueueRead();
					++Txbuffer[3];
				}

			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				if (CurrentPinRegister->generic.mode == PIN_MODE_UART0_TXRX)
				{    
					Txbuffer[3] = 0 ; // No space to transmit...
					Txbuffer[4] = matrixKeypadQueueAvailable();
					Txbuffer[5] = (uint8_t)matrixKeypadQueuePeek();
				}
			}
			break; 

			// CONFIGURE_CHANNEL_MODE_4 is used to close ports.  N/A

		case CONFIGURE_CHANNEL_MODE_5:
			{

				if (CurrentPinRegister->generic.mode == PIN_MODE_MATRIX_KEYPAD)
				{
					matrixKeypad->colPins[1] = Rxbuffer[3];
					matrixKeypad->colPins[2] = Rxbuffer[4];
					matrixKeypad->colPins[3] = Rxbuffer[5];
					matrixKeypad->bufferMode = Rxbuffer[6];
					matrixKeypad->queueMode = Rxbuffer[7];

					uint8_t i;
					for (i= 1; i < 4; ++i)
					{
						if (matrixKeypad->colPins[i] < NUMBER_OF_PHYSICAL_PINS)
						{
							if (matrixKeypad->colPins[i] != CurrentPin)
							{
								PinUpdateRegisters[matrixKeypad->colPins[i]].generic.mode = PIN_MODE_CONTROLLED;
							}     
							PinInput(matrixKeypad->colPins[i]);
							SetPinPullUp(matrixKeypad->colPins[i],1);
						}
					}
					matrixKeypad->state = KEYPAD_STATE_SETUP_ROW_0;

					for (i = 0; i < 4; ++ i)
					{
						if (matrixKeypad->colPins[i] != 0xFF &&
								matrixKeypad->colPins[i] != CurrentPin)
						{
							matrixKeypad->queuePinMemory = matrixKeypad->colPins[i];
							break;
						}
					}
					if ( matrixKeypad->queuePinMemory == 0xFF)
					{
						for (i = 0; i < 4; ++ i)
						{
							if (matrixKeypad->rowPins[i] != 0xFF &&
									matrixKeypad->rowPins[i] != CurrentPin)
							{
								matrixKeypad->queuePinMemory = matrixKeypad->rowPins[i];
								break;
							}
						}
					}

					for (i = 0; i < 4; ++ i)
					{
						if (matrixKeypad->colPins[i] != 0xFF &&
								matrixKeypad->colPins[i] != CurrentPin &&
								matrixKeypad->colPins[i] != matrixKeypad->queuePinMemory)
						{
							matrixKeypad->timingPinMemory = matrixKeypad->colPins[i];
							break;
						}
					}
					if ( matrixKeypad->timingPinMemory == 0xFF)
					{
						for (i = 0; i < 4; ++ i)
						{
							if (matrixKeypad->rowPins[i] != 0xFF &&
									matrixKeypad->rowPins[i] != CurrentPin&&
									matrixKeypad->rowPins[i] != matrixKeypad->queuePinMemory)
							{
								matrixKeypad->timingPinMemory = matrixKeypad->rowPins[i];
								break;
							}
						}
					}

					for (i = 0; i < 4; ++ i)
					{
						if (matrixKeypad->colPins[i] != 0xFF &&
								matrixKeypad->colPins[i] != CurrentPin &&
								matrixKeypad->colPins[i] != matrixKeypad->queuePinMemory &&
								matrixKeypad->colPins[i] != matrixKeypad->timingPinMemory)
						{
							matrixKeypad->countPinMemory = matrixKeypad->colPins[i];
							break;
						}
					}
					if ( matrixKeypad->timingPinMemory == 0xFF)
					{
						for (i = 0; i < 4; ++ i)
						{
							if (matrixKeypad->rowPins[i] != 0xFF &&
									matrixKeypad->rowPins[i] != CurrentPin&&
									matrixKeypad->rowPins[i] != matrixKeypad->queuePinMemory &&
									matrixKeypad->colPins[i] != matrixKeypad->timingPinMemory)
							{
								matrixKeypad->countPinMemory = matrixKeypad->rowPins[i];
								break;
							}
						}
					}

					matrixKeypadQueueInit();

					if (matrixKeypad->timingPinMemory != 0xFF)
					{
						uint16_t* changeTimeArray = (uint16_t*)&PinUpdateRegisters[matrixKeypad->timingPinMemory];
						for (i = 0; i <16; ++i)   
						{
							changeTimeArray[i] = 0;
						}
					}

					if (matrixKeypad->countPinMemory != 0xFF)
					{
						uint16_t* changeCountArray = (uint16_t*)&PinUpdateRegisters[matrixKeypad->countPinMemory];
						for (i = 0; i <16; ++i)   
						{
							changeCountArray[i] = 0;
						}
					}
				}
				else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
			}
			break;
		case CONFIGURE_CHANNEL_MODE_6:
			{
				uint8_t keyIndex = Rxbuffer[4];
				if (keyIndex >= 16)
				{
					error(SW_ERROR_INVALID_PARAMETER_4);
					return;
				}
				if (matrixKeypad->timingPinMemory < NUMBER_OF_PHYSICAL_PINS && matrixKeypad->countPinMemory < NUMBER_OF_PHYSICAL_PINS)
				{
					uint16_t* changeTimeArray = (uint16_t*)&PinUpdateRegisters[matrixKeypad->timingPinMemory];
					uint16_t* changeCountArray = (uint16_t*)&PinUpdateRegisters[matrixKeypad->countPinMemory];
					Txbuffer[3] =  (matrixKeypad->previousReading >> keyIndex) & 0x01;
					TXBUFFER16(4, changeCountArray[keyIndex]);
					TXBUFFER16(6, changeTimeArray[keyIndex]);
					if (Rxbuffer[3] != 0)
					{
						changeCountArray[keyIndex] = 0;
					}
				}
				else
				{
					error(SW_ERROR_DATA_NOT_AVAILABLE);
				}
			}
			break;
            
        case CONFIGURE_CHANNEL_MODE_7:
        {
            if (CurrentPinRegister->generic.mode == PIN_MODE_MATRIX_KEYPAD)
            {
                matrixKeypad->queueMask = RXBUFFER16(3);
            }
            	else
				{
					error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
				}
        }
        break;
	}
}



void updateMatrixKeypad(void)
{
	matrixKeypad_t* matrixKeypad = (matrixKeypad_t*) CurrentPinRegister;
	debugMatrixKeypad = (matrixKeypad_t*) CurrentPinRegister;

	if (matrixKeypad->state == KEYPAD_STATE_IDLE)
	{
		return;
	}

	switch (matrixKeypad->state)
	{

		case KEYPAD_STATE_SETUP_ROW_0:
		case KEYPAD_STATE_SETUP_ROW_1:
		case KEYPAD_STATE_SETUP_ROW_2:
		case KEYPAD_STATE_SETUP_ROW_3:
			{
				uint8_t i;
				for (i = 0; i < 4; ++i)
				{
					PinInput(matrixKeypad->rowPins[i]);
				}			

				PinLow(matrixKeypad->rowPins[(matrixKeypad->state / 3)]);
				matrixKeypad->delayRemaining = matrixKeypad->delayPeriod;
				++matrixKeypad->state;
			}
			break;

		case KEYPAD_STATE_WAIT_ROW_0:
		case KEYPAD_STATE_WAIT_ROW_1:
		case KEYPAD_STATE_WAIT_ROW_2:
		case KEYPAD_STATE_WAIT_ROW_3:
			{
				if (matrixKeypad->delayRemaining)
				{
					-- matrixKeypad->delayRemaining;
				}
				else
				{
					++matrixKeypad->state;
				}
			}
			break;

		case KEYPAD_STATE_READ_ROW_0:
		case KEYPAD_STATE_READ_ROW_1:
		case KEYPAD_STATE_READ_ROW_2:
		case KEYPAD_STATE_READ_ROW_3:
			{
				if (matrixKeypad->state == KEYPAD_STATE_READ_ROW_0)
				{
					matrixKeypad->currentReading = 0;
				}

				uint16_t result = 0;
				uint8_t i; 
				for (i = 0; i < 4; ++i)
				{
					uint8_t pin = matrixKeypad->colPins[i];
					if (pin == 255)
					{  
						continue;
					}
					else if (ReadPin(pin) == 0)
					{
						result |= (0x8000 >> (3 - i));
					}
				}
				result >>= (3 - (matrixKeypad->state / 3)) * 4;

				matrixKeypad->currentReading |= result;

				if (matrixKeypad->state == KEYPAD_STATE_READ_ROW_3)
				{
                    if (matrixKeypad->timingPinMemory < NUMBER_OF_PHYSICAL_PINS && matrixKeypad->countPinMemory < NUMBER_OF_PHYSICAL_PINS)
                    {
                        uint16_t* changeTimeArray = (uint16_t*)&PinUpdateRegisters[matrixKeypad->timingPinMemory];
			uint16_t* changeCountArray = (uint16_t*)&PinUpdateRegisters[matrixKeypad->countPinMemory];
                                uint8_t keyIndex;
                                for (keyIndex = 0; keyIndex < 16 ; ++ keyIndex)
                                {
                              
                                    
                                    if (((0x0001 << keyIndex)& matrixKeypad->currentReading) !=
                                            ((0x0001 << keyIndex)& matrixKeypad->previousReading))
                                    {
                                        changeTimeArray[keyIndex] = 0;
				        ++ changeCountArray[keyIndex];	
                                    }
                                    else
                                    {
                                        if (changeTimeArray[keyIndex] < 65535)
                                        {
                                            ++ changeTimeArray[keyIndex];
                                        }
                                    }
                                }
                    }
                    if (matrixKeypad->currentReading != matrixKeypad->previousReading)
                    {
                            uint8_t keyIndex;
                                for (keyIndex = 0; keyIndex < 16 ; ++ keyIndex)
                                {
                                    
                                    if (((0x0001 << keyIndex)& matrixKeypad->currentReading) != 0)
                                    {

                                        break;
                                    }
                                }
                        switch (matrixKeypad->bufferMode)
                        {
                            case KEYPAD_BUFFER_MODE_BINARY:
                            {
                                CurrentPinRegister->generic.buffer = matrixKeypad->currentReading;
                            }
                            break;
                            
                           
                            case KEYPAD_BUFFER_MODE_LAST_ASCII:
                            {
                                if (keyIndex < 16 )
                                {
                                    CurrentPinRegister->generic.buffer = KeypadAscii[keyIndex];
                                }
                            }
                            break;
                            case KEYPAD_BUFFER_CURRENT_BUTTON:
                            {
                                 CurrentPinRegister->generic.buffer = keyIndex;
                             }
                            break;
                            case KEYPAD_BUFFER_MODE_LAST_BUTTON:
                            {
                              
                                 if (keyIndex < 16)
                                {
                                CurrentPinRegister->generic.buffer = keyIndex;
                                }
                            }
                            break;
                        }
                        
                        switch (matrixKeypad->queueMode)
                        {
                            case KEYPAD_QUEUE_MODE_BUTTON_INDEX:
                            {
                                if (keyIndex < 16)
                                {
                                    if ((((uint16_t)1)<<keyIndex) & matrixKeypad->queueMask)
                                    {
                                    matrixKeypadQueueAdd(keyIndex);
                                    }
                                }
                            }
                            break;
                            case KEYPAD_QUEUE_MODE_BUTTON_ASCII:
                            {
                                if (keyIndex < 16)
                                {
                                     if ((((uint16_t)1)<<keyIndex) & matrixKeypad->queueMask)
                                    {
                                    matrixKeypadQueueAdd(KeypadAscii[keyIndex]);
                                     }
                                }
                            }
                            break;
                         
                        }
                        matrixKeypad->previousReading = matrixKeypad->currentReading;
                       
                    }
                    matrixKeypad->state = KEYPAD_STATE_SETUP_ROW_0;
				}
                else
                {
                    ++matrixKeypad->state;
                }


			}
			break;


		case KEYPAD_STATE_IDLE:
			break;
	} 
}


