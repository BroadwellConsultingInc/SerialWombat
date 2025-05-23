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



typedef struct matrixKeypad_n{
    uint8_t colPins[4];
    uint8_t rowPins[4];
    uint8_t asciiOut[16];
    KEYPAD_STATE_t state;
    uint16_t currentReading;
	uint16_t previousReading;
    uint16_t queueMask;
    uint8_t timingPinMemory; // Todo make this in column / row 0
    uint8_t queuePinMemory; // Todo make this in current pin
    uint8_t countPinMemory; // Todo make this in column / row 0
	uint8_t queueMode;
	uint8_t bufferMode;
	uint8_t delayPeriod;
	uint8_t delayRemaining;

} matrixKeypad_t;

matrixKeypad_t* debugMatrixKeypad;

//TODO make queue use standard queue handlers
#define SIZE_OF_KEYPAD_QUEUE 32
static uint8_t matrixKeypadQueueAvailable()  //TODO make standardized with other queues
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
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_MATRIX_KEYPAD)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
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
                matrixKeypad->delayPeriod = 5;
                matrixKeypad->delayRemaining = 0;

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
				matrixKeypad->asciiOut[0] = '1';
				matrixKeypad->asciiOut[1] = '2';
				matrixKeypad->asciiOut[2] = '3';
				matrixKeypad->asciiOut[3] = 'A';
				matrixKeypad->asciiOut[4] = '4';
				matrixKeypad->asciiOut[5] = '5';
				matrixKeypad->asciiOut[6] = '6';
				matrixKeypad->asciiOut[7] = 'B';
                matrixKeypad->asciiOut[8] = '7';
                matrixKeypad->asciiOut[9] = '8';
                matrixKeypad->asciiOut[10] = '9';
                matrixKeypad->asciiOut[11] = 'C';
                matrixKeypad->asciiOut[12] = '*';
                matrixKeypad->asciiOut[13] = '0';
                matrixKeypad->asciiOut[14] = '#';
                matrixKeypad->asciiOut[15] = 'D';


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
				
					Txbuffer[3] = 0 ; // No space to transmit...
					Txbuffer[4] = matrixKeypadQueueAvailable();
					Txbuffer[5] = (uint8_t)matrixKeypadQueuePeek();
				
			}
			break; 

			// CONFIGURE_CHANNEL_MODE_4 is used to close ports.  N/A

		case CONFIGURE_CHANNEL_MODE_5:
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
           
                matrixKeypad->queueMask = RXBUFFER16(3);
           
        }
        break;
         case CONFIGURE_CHANNEL_MODE_8:
        {
           
                matrixKeypad->delayPeriod = Rxbuffer[3];
           
        }
        break;
         case CONFIGURE_CHANNEL_MODE_9:
                {
                    if (Rxbuffer[3] < 16)
                    {

                        matrixKeypad->asciiOut[Rxbuffer[3]] = Rxbuffer[4];
                    }
                    else {
                        error(SW_ERROR_CMD_BYTE_3);
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
                                    CurrentPinRegister->generic.buffer = matrixKeypad->asciiOut[keyIndex];
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
                                    matrixKeypadQueueAdd(matrixKeypad->asciiOut[keyIndex]);
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


