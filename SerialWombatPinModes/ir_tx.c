/*
Copyright 2026 Broadwell Consulting Inc.

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

/* Serial Wombat is a registered trademark of Broadwell Consulting Inc. */
#include "serialWombat.h"
#include "inputProcess.h"



#define NEC_DMA_START_BURST_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY * 9.0 / 1000))  //9 MS Nominal
#define NEC_DMA_START_SPACE_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY * 4.5 / 1000))  //4.5 MS Nominal

#define NEC_PULSE_BIT_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY *.0005625))
#define NEC_ZERO_BIT_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY *.0005625))

#define NEC_ONE_BIT_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY *.001687))  //.001687 nominal
#define NEC_POST_MESSAGE_DELAY ((uint16_t)(DMA_FREQUENCY * .04))  //40 mS


#define NEC_DMA_REPEAT_SPACE_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY *.00225))
#define NEC_POST_REPEAT_DELAY_DMA_COUNTS ((uint16_t)(DMA_FREQUENCY * .096))  //96 mS

#define ONEANDQUARTER_MS_IDLE_DMACOUNTS  ((uint16_t)(DMA_FREQUENCY * .00125))

#define IRTX_MODE_NEC 0
#define IR_TXQUEUE_LENGTH 32
typedef struct uartSw_n{
    DMABitStream_t bitStream;
    uint8_t queueDataSpace[IR_TXQUEUE_LENGTH + 16]; // 16 to allow for queue overhead
    uint32_t txRemainingBitmap;
    uint16_t txRemainingDMACounts;
    uint8_t txRemainingRepeats;
    uint8_t txCurrentBit:1;
    uint8_t txRemainingBits;
    uint8_t txState;
}IRTx_t;


typedef enum
{
    IR_TXSTATE_IDLE = 0,
    IR_TXSTATE_NEC_SENDING_FIRST_BURST = 1,  ///< Waiting for the first start burst
    IR_TXSTATE_NEC_START_BURST_SPACE = 2, ///< In and timing the start burst
    IR_TXSTATE_NEC_SENDING_BITS = 3,  ///< In and timing the start space
    IR_TXState_NEC_EOM_PULSE = 4,
    IR_TXSTATE_NEC_POST_MESSAGE_DELAY = 5,
    IR_TXSTATE_NEC_SENDING_REPEAT_BURST = 6,
    IR_TXSTATE_NEC_REPEAT_BURST_SPACE = 7,
    IR_TXSTATE_NEC_REPEAT_PULSE = 8,
    IR_TXSTATE_NEC_POST_REPEAT_DELAY = 9,
}IR_TX_STATE_t;

IRTx_t* debug_IRTx;

static void enableCarrier(void);

void initIRTx()
{
	IRTx_t* IRTx = (IRTx_t*)CurrentPinRegister;
    debug_IRTx= IRTx;
  BUILD_BUG_ON( sizeof(IRTx_t) >  BYTES_PER_PIN_REGISTER );
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_IR_TX)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
			    InitializePinLow(CurrentPin);
			                        initializeBitStreamOutput(CurrentPin,  0, &IRTx->bitStream );
				CurrentPinRegister->generic.mode = PIN_MODE_IR_TX;
				
				queueAddress = IRTx->queueDataSpace;
				                    QueueByteInitialize(IR_TXQUEUE_LENGTH);
				                    CurrentPinRegister->generic.buffer = 0;
			}
			break;
        case CONFIGURE_CHANNEL_MODE_1:  //Transmit
            {
                    queueCONFIGURE_CHANNEL_MODE_1_transmit(NULL,IRTx->queueDataSpace);

            }
            break;
            case CONFIGURE_CHANNEL_MODE_2:
                /*

			{
				queueCONFIGURE_CHANNEL_MODE_2_receive(IRTx->queueDataSpace);
			}
			*/
                Txbuffer[3] = 0;
			break;


		case CONFIGURE_CHANNEL_MODE_3: // Peek RX
			{
				queueCONFIGURE_CHANNEL_MODE_3_peekRX(NULL,IRTx->queueDataSpace);
				
			}
			break; 

#ifdef SW8B
        case CONFIGURE_CHANNEL_MODE_HW_0:
        {
            enableCarrier();
        }
        break;
#endif

		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}


}




static bool irSendBit() // returns true when done
{
    IRTx_t* IRTx = (IRTx_t*)CurrentPinRegister;
    if (IRTx->txCurrentBit == 0)
    {
        // We just finished sending a space.  More bits to send?
        if (IRTx->txRemainingBits)
        {
            // Yes.  send a pulse
            IRTx->txCurrentBit = 1;
            IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_PULSE_BIT_DMA_COUNTS, &IRTx->bitStream);
        }
        else {
            // No.  Return true
            return(true);
        }
    }
    else {
        // We just finished sending a pulse.
        IRTx->txCurrentBit = 0;
        if ((IRTx->txRemainingBitmap & 0x01) > 0)
        {
            IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_ONE_BIT_DMA_COUNTS, &IRTx->bitStream);
        }
        else {
            IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_ZERO_BIT_DMA_COUNTS, &IRTx->bitStream);
        }
        --IRTx->txRemainingBits;
        IRTx->txRemainingBitmap >>= 1;
    }
    return (false);

}

void updateIRTx()
{
	IRTx_t* IRTx = (IRTx_t*)CurrentPinRegister;
	debug_IRTx= IRTx;


	    queueAddress = IRTx->queueDataSpace;


	    if (IRTx->txRemainingDMACounts)
	    {
	        IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, IRTx->txRemainingDMACounts, &IRTx->bitStream);
	    }
	    if (IRTx->txRemainingDMACounts)
	           {
	                return;
	           }


	    while (IRTx->txRemainingDMACounts == 0 )
	    {
	        // we still have room in the DMA
	        switch (IRTx->txState)
	        {
	        case IR_TXSTATE_IDLE:
	        {

	            uint16_t bytesInQueue = 0;
	            // If Repeat count != 0, send a repeat.
	            if (IRTx->txRemainingRepeats > 0)
	            {
	                -- IRTx->txRemainingRepeats;
	                IRTx->txCurrentBit = 1;
	                IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_DMA_START_BURST_DMA_COUNTS, &IRTx->bitStream);
	                IRTx->txState = IR_TXSTATE_NEC_SENDING_REPEAT_BURST;
	                ++CurrentPinRegister->generic.buffer;
	            }
	            else if (QueueGetBytesFilledInQueue(&bytesInQueue)== QUEUE_RESULT_SUCCESS && bytesInQueue >= 4)
	            {
	                uint8_t* data = (uint8_t*)&IRTx->txRemainingBitmap;
	                IRTx->txRemainingBitmap = 0;

	                QueueReadByte(data);
	                QueueReadByte(data + 1);
	                QueueReadByte(data+2);
	                QueueReadByte(&IRTx->txRemainingRepeats);
	                IRTx->txRemainingBitmap |=  (((~IRTx->txRemainingBitmap) << 8) & 0xFF000000);  // Add the inverse bytes
	                IRTx->txRemainingBits = 32;
	                IRTx->txCurrentBit = 1;
	                IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_DMA_START_BURST_DMA_COUNTS, &IRTx->bitStream);
	                ++IRTx->txState;
	                ++CurrentPinRegister->generic.buffer;

	            }
	            //else If command available, calcualte 32 bit packet and start a burst
	            // else stay in idle
	            else {

	            IRTx->txCurrentBit = 0;
	            IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, ONEANDQUARTER_MS_IDLE_DMACOUNTS, &IRTx->bitStream);
	            }
	        }
	        break;

	        case IR_TXSTATE_NEC_SENDING_FIRST_BURST:
            {
                //Start Burst Complete.   Delay.
                IRTx->txCurrentBit = 0;
                IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_DMA_START_SPACE_DMA_COUNTS, &IRTx->bitStream);
                ++IRTx->txState;
            }
            break;

	        case IR_TXSTATE_NEC_START_BURST_SPACE:
            {
                //Delay Complete.  Start Sending Bits
                irSendBit();
                ++IRTx->txState;

            }
            break;

	        case IR_TXSTATE_NEC_SENDING_BITS:
            {
                // Part of a bit complete.  If it was a pulse, queue a space proportional to 0 or 1

                // If it was a space, then see if additional bits need to be sent.  If not, EOM_Pulse
                if (irSendBit())
                {
                    //Complete.  Send EOM Pulse
                    ++IRTx->txState;
                    IRTx->txCurrentBit = 1;
                                   IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_PULSE_BIT_DMA_COUNTS, &IRTx->bitStream);
                }

            }
            break;

	        case IR_TXState_NEC_EOM_PULSE:
	                   {
	                       // End of message pulse complete
	                       // Start the post message delay
	                       ++IRTx->txState;
	                                           IRTx->txCurrentBit = 0;
	                                                          IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_POST_MESSAGE_DELAY, &IRTx->bitStream);

	                   }
	                   break;

	        case IR_TXSTATE_NEC_POST_MESSAGE_DELAY:
	        case IR_TXSTATE_NEC_POST_REPEAT_DELAY:
            {
                IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, ONEANDQUARTER_MS_IDLE_DMACOUNTS, &IRTx->bitStream);
                IRTx->txState = IR_TXSTATE_IDLE;
            }
            break;

	        case IR_TXSTATE_NEC_SENDING_REPEAT_BURST:
            {
                //Repeat burst finished.
                IRTx->txCurrentBit = 0;
                                IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_DMA_REPEAT_SPACE_DMA_COUNTS, &IRTx->bitStream);
                                ++IRTx->txState;

            }
            break;

	        case IR_TXSTATE_NEC_REPEAT_BURST_SPACE:
            {
                //Repeat space finished
                // Send final pulse
                IRTx->txCurrentBit = 1;
                                               IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_PULSE_BIT_DMA_COUNTS, &IRTx->bitStream);
                                               ++IRTx->txState;

            }
            break;

	        case IR_TXSTATE_NEC_REPEAT_PULSE:
            {
                //Final pulse finished.
                // Post Repeat delay
                ++IRTx->txState;
                                    IRTx->txCurrentBit = 0;
                                                   IRTx->txRemainingDMACounts = updateBitStreamOutput(CurrentPin, IRTx->txCurrentBit, NEC_POST_REPEAT_DELAY_DMA_COUNTS, &IRTx->bitStream);


            }
            break;

	        // see    case IR_TXSTATE_NEC_POST_REPEAT_DELAY: above



	        default:
	        {
	            IRTx->txState = IR_TXSTATE_IDLE;
	        }



	        }


	    }

}

#ifdef SW8B
#include "ch32v00x.h"

#define TIMCLK_HZ   48000000UL   // TIM1 clock (commonly 48 MHz on CH32V003 examples)
#define PWM_HZ      38000UL



static void enableCarrier()
{
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);
    RCC->APB2PCENR |= (RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1);


    // PA1 as Alternate Function Push-Pull for TIM1_CH1

    /*
    gpio.GPIO_Pin   = GPIO_Pin_1;
     gpio.GPIO_Mode  = GPIO_Mode_AF_PP;
     gpio.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &gpio);
     */
     GPIOA->CFGLR |= 0xB0;




    /*
    TIM_TimeBaseInitTypeDef tb = {0};
    tb.TIM_Prescaler         = (uint16_t)psc;
    tb.TIM_CounterMode       = TIM_CounterMode_Up;
    tb.TIM_Period            = (uint16_t)arr;
    tb.TIM_ClockDivision     = TIM_CKD_DIV1;
    tb.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &tb);
    */
    TIM1->CTLR1 = 0;
    TIM1->ATRLR = 1262;//TIM_TimeBaseInitStruct->TIM_Period;
    TIM1->PSC = 0;//TIM_TimeBaseInitStruct->TIM_Prescaler;
    TIM1->RPTCR = 0;
    TIM1->SWEVGR = TIM_PSCReloadMode_Immediate;

/*
    TIM_OCInitTypeDef oc = {0};
    oc.TIM_OCMode      = TIM_OCMode_PWM1;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_Pulse       = (uint16_t)ccr;
    oc.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OC2Init(TIM1, &oc);
*/
    TIM1->CCER &= (uint16_t)(~((uint16_t)TIM_CC2E));
    TIM1->CTLR2 = 0;
    TIM1->CHCTLR1 = 24576;
    TIM1->CH2CVR = 631;
    TIM1->CCER = 0x10;


     //TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    {
     int16_t tmpccmr1 = 0;

         tmpccmr1 = TIM1->CHCTLR1;
         tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC2PE);
         tmpccmr1 |= (uint16_t)(TIM_OCPreload_Enable << 8);
         TIM1->CHCTLR1 = tmpccmr1;
    }


    //TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM1->CTLR1 |= TIM_ARPE;

    // TIM1 is an "advanced" timer: must enable Main Output (MOE)
    //TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM1->BDTR |= TIM_MOE;

    //TIM_Cmd(TIM1, ENABLE);
    TIM1->CTLR1 |= TIM_CEN;
}
#endif



