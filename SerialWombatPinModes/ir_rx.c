#include "serialWombat.h"
#include "mcc_generated_files/mcc.h"
#include "inputProcess.h"

//TODO, consider lower sampling rate

#define NEC_PULSE_BIT_DMA_COUNTS_SHORT_LIMIT ((uint16_t)(DMA_FREQUENCY *.000400))  //.000562 nominal
#define NEC_PULSE_BIT_DMA_COUNTS_LONG_LIMIT ((uint16_t)(DMA_FREQUENCY *.000700))  //.000562 nominal
#define NEC_ZERO_BIT_DMA_COUNTS_SHORT_LIMIT ((uint16_t)(DMA_FREQUENCY *.000400))  //.000562 nominal
#define NEC_ZERO_BIT_DMA_COUNTS_LONG_LIMIT ((uint16_t)(DMA_FREQUENCY *.000700))  //.000562 nominal
#define NEC_ONE_BIT_DMA_COUNTS_SHORT_LIMIT ((uint16_t)(DMA_FREQUENCY *.001200))  //.001687 nominal
#define NEC_ONE_BIT_DMA_COUNTS_LONG_LIMIT ((uint16_t)(DMA_FREQUENCY *.002000))  //.001686 nominal
#define NEC_DMA_START_BURST_DMA_COUNTS_LONG_LIMIT ((uint16_t)(DMA_FREQUENCY * 9.5 / 1000))  //9 MS Nominal
#define NEC_DMA_START_BURST_DMA_COUNTS_SHORT_LIMIT ((uint16_t)(DMA_FREQUENCY * 8.5 / 1000))  //9 MS Nominal
#define NEC_DMA_START_SPACE_DMA_COUNTS_SHORT_LIMIT (DMA_FREQUENCY * 4 / 1000)  //4.5 MS Nominal
#define NEC_DMA_START_SPACE_DMA_COUNTS_LONG_LIMIT (DMA_FREQUENCY * 5 / 1000)  //4.5 MS Nominal
#define NEC_DMA_REPEAT_SPACE_DMA_COUNTS_SHORT_LIMIT (DMA_FREQUENCY * 2 / 1000)  //2.5 MS Nominal
#define NEC_DMA_REPEAT_SPACE_DMA_COUNTS_LONG_LIMIT (DMA_FREQUENCY * 3 / 1000)  //2.5 MS Nominal

#define IRRX_MODE_NEC 0
#define IR_RX_QUEUE_LENGTH 16
typedef struct IRRx_n{
	
		uint32_t incomingData;
		/*struct
		{
            uint8_t address;
			uint8_t invAddress;
            uint8_t command;
            uint8_t invCommand;
		};
         */
   
    uint8_t queueDataSpace[IR_RX_QUEUE_LENGTH + 10]; // 16 to allow for queue overhead
    uint16_t timeoutPeriod;
    uint16_t timeoutValue;
    uint16_t timeoutCounter ;
    uint16_t bitCount;
	uint8_t mode;
	uint8_t state;
	uint16_t addressFilter;
	uint8_t incomingDataBits;
	uint8_t pulseLogicLevel:1; // Typical is 0, low defines bit 
    uint8_t useRepeat:1;
    uint8_t useAddressFilter:1;
    uint16_t lastAddress;
    uint16_t bytesQueued;
    uint8_t publicDataOutput; 

    
}IRRx_t;

typedef enum
{
    IR_RX_PUBLIC_DATA_OUTPUT_COMMAND = 0,
    IR_RX_PUBLIC_DATA_OUTPUT_ADDRESS = 1,
            IRRX_PUBLIC_DATA_OUTPUT_COUNT = 2,
    
}IRRx_publicDataOutput;

typedef enum
{
    IR_RX_STATE_IDLE = 0,
    IR_RX_STATE_NEC_WAIT_START = 1,  ///< Waiting for the first start burst
    IR_RX_STATE_NEC_START_BURST_COUNT = 2, ///< In and timing the start burst
    IR_RX_STATE_NEC_START_SPACE_COUNT = 3,  ///< In and timing the start space
    IR_RX_STATE_NEC_RX_BIT_PULSE = 4,
    IR_RX_STATE_NEC_RX_BIT_SPACE = 5,
    IR_RX_STATE_NEC_RX_FINAL_PULSE = 6,
    IR_RX_STATE_NEC_RX_REPEAT_PULSE = 7,
}IR_RX_STATE_t;

IRRx_t* debug_IRRx; 
void initIRRx()
{
	IRRx_t* IRRx = (IRRx_t*)CurrentPinRegister;
    debug_IRRx= IRRx;
  BUILD_BUG_ON( sizeof(IRRx_t) >  BYTES_PER_PIN_REGISTER );
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_IR_RX)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				CurrentPinInput();
				CurrentPinRegister->generic.mode = PIN_MODE_IR_RX;
				IRRx->mode = Rxbuffer[3];
				IRRx->useRepeat = Rxbuffer[4];
				IRRx->pulseLogicLevel = Rxbuffer[5];
                IRRx->addressFilter = RXBUFFER16(6);
                IRRx->useAddressFilter = 0;
				IRRx->state = IR_RX_STATE_NEC_WAIT_START ; 
				IRRx->bitCount = 0;
                IRRx->timeoutCounter = 0;
                IRRx->timeoutPeriod = 0;
                IRRx->lastAddress = 0;
                IRRx->publicDataOutput = IR_RX_PUBLIC_DATA_OUTPUT_COMMAND;
                IRRx->bytesQueued = 0;
					queueAddress = IRRx->queueDataSpace;
					QueueByteInitialize(IR_RX_QUEUE_LENGTH);
					PulseInSkipDMABits(CurrentPin,SIZE_OF_DMA_ARRAY);
                 //   inputProcessInit(&IRRx->inputProcess);
			}
			break;
		case CONFIGURE_CHANNEL_MODE_1:
			{
				
				IRRx->timeoutPeriod = RXBUFFER16(3);
                IRRx->timeoutCounter = 0;
                IRRx->timeoutValue = RXBUFFER16(5);
                IRRx->useAddressFilter = Rxbuffer[7];
				
			}
			break;
case CONFIGURE_CHANNEL_MODE_2:
			{
				queueCONFIGURE_CHANNEL_MODE_2_receive(IRRx->queueDataSpace);
			}
			break;

		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				queueCONFIGURE_CHANNEL_MODE_3_peekRX(IRRx->queueDataSpace,IRRx->queueDataSpace);
				
			}
			break; 
        case CONFIGURE_CHANNEL_MODE_4:
        {
            TXBUFFER16(3,(uint16_t)IRRx->lastAddress);
            TXBUFFER16(5,IRRx->bytesQueued);
        }
        break;
        case CONFIGURE_CHANNEL_MODE_5:
        {
            IRRx->publicDataOutput = Rxbuffer[3];
        }
        break;
        

		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}


}

IRRx_t* debugIRRx;




void updateIRRx()
{
	IRRx_t* IRRx = (IRRx_t*)CurrentPinRegister;
	debug_IRRx= IRRx;
    uint8_t inputBit;
	inputBit = PulseInGetOldestDMABit(CurrentPin);
    int32_t publicDataOut = -1;
	while (inputBit != 2)
	{
		if (IRRx->pulseLogicLevel == 0)
		{
			// Code below assumes logic level 1 is active pulse.  Invert to make this so
			if (inputBit)
			{
				inputBit = 0;
			}
			else
			{
				inputBit = 1;
			}
		}

		switch (IRRx->state)
		{
			case IR_RX_STATE_NEC_WAIT_START:
				{
					if (inputBit == 1)
					{
						IRRx->state = IR_RX_STATE_NEC_START_BURST_COUNT;
						IRRx->bitCount = 1;
					}
				}
				break;

			case IR_RX_STATE_NEC_START_BURST_COUNT:
				{
					if (inputBit == 1)
					{
						//Still Active
						if (IRRx->bitCount<65535)
						{
							++IRRx->bitCount;
						}
					}
					else 
					{
						//Inactive
						if (IRRx->bitCount > NEC_DMA_START_BURST_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_DMA_START_BURST_DMA_COUNTS_LONG_LIMIT)
						{
							IRRx->state = IR_RX_STATE_NEC_START_SPACE_COUNT;
							IRRx->bitCount = 1;
						}
						else
						{
							IRRx->state = IR_RX_STATE_NEC_WAIT_START;
							IRRx->bitCount = 0;
						}
					}
				}
				break;
			case IR_RX_STATE_NEC_START_SPACE_COUNT:
				{
					if (inputBit == 0)
					{
						//Still inactive
						if (IRRx->bitCount<65535)
						{
							++IRRx->bitCount;
						}
					}
					else 
					{
						//Pulse.
						if (IRRx->bitCount > NEC_DMA_START_SPACE_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_DMA_START_SPACE_DMA_COUNTS_LONG_LIMIT)
						{
							IRRx->state = IR_RX_STATE_NEC_RX_BIT_PULSE;
							IRRx->bitCount = 1;
							IRRx->incomingData = 0;
							IRRx->incomingDataBits = 0;
						}
						else if (IRRx->bitCount > NEC_DMA_REPEAT_SPACE_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_DMA_REPEAT_SPACE_DMA_COUNTS_LONG_LIMIT)
						{
							IRRx->state = IR_RX_STATE_NEC_RX_REPEAT_PULSE;
							IRRx->bitCount = 0;
						}
					}
				}
				break;
			case IR_RX_STATE_NEC_RX_BIT_PULSE:
				{
					if (inputBit == 1)
					{
						//Still Pulse
						if (IRRx->bitCount<65535)
						{
							++IRRx->bitCount;
						}
					}
					else 
					{
						//Space.
						if (IRRx->bitCount > NEC_PULSE_BIT_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_PULSE_BIT_DMA_COUNTS_LONG_LIMIT)
						{
							IRRx->state = IR_RX_STATE_NEC_RX_BIT_SPACE;
							IRRx->bitCount = 1;
						}
						else
						{
							IRRx->state = IR_RX_STATE_NEC_WAIT_START;
							IRRx->bitCount = 0;
						}

					}
				}
				break;
			case IR_RX_STATE_NEC_RX_BIT_SPACE:
				{
					if (inputBit == 0)
					{
						//Still Space
						if (IRRx->bitCount<65535)
						{
							++IRRx->bitCount;
						}
					}
					else 
					{
						//HIGH.
						if (IRRx->bitCount > NEC_ZERO_BIT_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_ZERO_BIT_DMA_COUNTS_LONG_LIMIT)
						{
							++IRRx->incomingDataBits;
							IRRx->state = IR_RX_STATE_NEC_RX_FINAL_PULSE;
							IRRx->bitCount = 1;
                            if (IRRx->incomingDataBits == 32)
                            {
                            IRRx->state = IR_RX_STATE_NEC_RX_FINAL_PULSE;    
                            }
                            else
                            {
                                IRRx->state = IR_RX_STATE_NEC_RX_BIT_PULSE;
                            }
						}
						else if (IRRx->bitCount > NEC_ONE_BIT_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_ONE_BIT_DMA_COUNTS_LONG_LIMIT)
						{
							//One bit.  Set the bit in incoming data.
							IRRx->incomingData |= (((uint32_t)0x01) << IRRx->incomingDataBits);
								++IRRx->incomingDataBits;
							
							IRRx->bitCount = 1;
                            if (IRRx->incomingDataBits == 32)
                            {
                            IRRx->state = IR_RX_STATE_NEC_RX_FINAL_PULSE;    
                            }
                            else
                            {
                                IRRx->state = IR_RX_STATE_NEC_RX_BIT_PULSE;
                            }
						}
						else
						{
							IRRx->state = IR_RX_STATE_NEC_WAIT_START;
							IRRx->bitCount = 0;
						}

					}
				}
				break;
			case IR_RX_STATE_NEC_RX_FINAL_PULSE: //TODO, does it actually go low?
				{
					if (inputBit == 1)
					{
						//Still Pulse
						if (IRRx->bitCount<65535)
						{
							++IRRx->bitCount;
						}
					}
					else 
					{
						//LOW
						if (IRRx->bitCount > NEC_PULSE_BIT_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_PULSE_BIT_DMA_COUNTS_LONG_LIMIT)
						{
							// Should be 32 bits in the IRRx->incomingData value
							// LSB: Logical Inverse of Command
							// LMB: Command
							// MMB: Logical Inverse of Address
							// MSB: Address
                            uint8_t Address = (uint8_t)(IRRx->incomingData );
                            uint8_t INVAddress = (uint8_t)(IRRx->incomingData >> 8);
                            uint8_t Command = (uint8_t)(IRRx->incomingData >> 16);
                            uint8_t InvCommand = (uint8_t)(IRRx->incomingData >> 24);
                            IRRx->lastAddress = (uint16_t) IRRx->incomingData;
                            if (!IRRx->useAddressFilter || (IRRx->lastAddress == IRRx->addressFilter))
                            {
							if ((InvCommand + Command) == 0xFF )
							{
								//if (IRRx->address == IRRx->addressFilter)
								{
									publicDataOut = Command;
								}
                                queueAddress = IRRx->queueDataSpace;
                QueueAddByte(Command);
                ++IRRx->bytesQueued;
                IRRx->timeoutCounter = IRRx->timeoutPeriod;
							}
                            }
							IRRx->state = IR_RX_STATE_NEC_WAIT_START;
							IRRx->bitCount = 1;
						}
						else
						{
							IRRx->state = IR_RX_STATE_NEC_WAIT_START;
							IRRx->bitCount = 0;
						}

					}
				}
				break;

			case IR_RX_STATE_NEC_RX_REPEAT_PULSE:
				{
					if (inputBit == 1)
					{
						//Still Pulse
						if (IRRx->bitCount<65535)
						{
							++IRRx->bitCount;
						}
					}
					else 
					{
						//Space.
						if (IRRx->bitCount > NEC_PULSE_BIT_DMA_COUNTS_SHORT_LIMIT &&
								IRRx->bitCount < NEC_PULSE_BIT_DMA_COUNTS_LONG_LIMIT)
						{
                            if (IRRx->useRepeat)
                            {
                            
                            if (!IRRx->useAddressFilter || (IRRx->lastAddress == IRRx->addressFilter))
                            {
							  queueAddress = IRRx->queueDataSpace;
                QueueAddByte((uint8_t)(IRRx->incomingData >> 16));
                ++IRRx->bytesQueued;
                IRRx->timeoutCounter = IRRx->timeoutPeriod;
                            }
                            }
						}
							IRRx->state = IR_RX_STATE_NEC_WAIT_START;
							IRRx->bitCount = 0;

					}
				}
				break;

			default:
				IRRx->state = IR_RX_STATE_NEC_WAIT_START;
				break;



		}
		inputBit = PulseInGetOldestDMABit(CurrentPin);
	}
    if (IRRx->timeoutCounter > 0)
    {
        --IRRx->timeoutCounter;
    }
    switch (IRRx->publicDataOutput)
    {
        
        case IR_RX_PUBLIC_DATA_OUTPUT_COMMAND:
        {
    if(IRRx->timeoutPeriod != 0 && IRRx->timeoutCounter == 0)
    {
       publicDataOut = IRRx->timeoutValue;
    }
    if (publicDataOut == -1)
    {
        publicDataOut = CurrentPinRegister->generic.buffer;
    }
            
        }
        break;
        
        case IR_RX_PUBLIC_DATA_OUTPUT_ADDRESS :
        {
            publicDataOut = IRRx->lastAddress;
        }
        break;
        case  IRRX_PUBLIC_DATA_OUTPUT_COUNT :
        {
            publicDataOut = IRRx->bytesQueued;
        }
        break;
    }
    CurrentPinRegister->generic.buffer =  publicDataOut;//  inputProcessProcess(&IRRx->inputProcess,(uint16_t) publicDataOut);
}

