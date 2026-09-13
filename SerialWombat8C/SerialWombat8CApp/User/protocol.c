/*
Copyright 2021-2025 Broadwell Consulting Inc.


"Serial Wombat" is a registered trademark in the United States of Broadwell
Consulting Inc.

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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "serialWombat.h"
#include "asciiConversion.h"
#include "debug.h"

extern uint16_t stayInBoot;


uint8_t i2cRxCount = 0;
uint8_t i2cTxCount = 0;
uint8_t Rxbuffer[RXBUFFER_LENGTH];
uint8_t Txbuffer[TXBUFFER_LENGTH];


#define CTLR2_FREQ_Reset         ((uint16_t)0xFFC0)
#define CTLR1_PE_Reset           ((uint16_t)0xFFFE)
#define CKCFGR_CCR_Set           ((uint16_t)0x0FFF)
#define CKCFGR_FS_Set            ((uint16_t)0x8000)
#define CTLR1_CLEAR_Mask         ((uint16_t)0xFBF5)
#define CTLR1_PE_Set             ((uint16_t)0x0001)

#define CR_PAGE_PG                 ((uint32_t)0x00010000)
#define CR_PAGE_ER                 ((uint32_t)0x00020000)
#define CR_BUF_LOAD                ((uint32_t)0x00040000)
#define CR_BUF_RST                 ((uint32_t)0x00080000)
#define CR_STRT_Set                ((uint32_t)0x00000040)
#define SR_BSY                     ((uint32_t)0x00000001)
#define EraseTimeout               ((uint32_t)0x000B0000)
#define CR_MER_Set                 ((uint32_t)0x00000004)
#define CR_MER_Reset               ((uint32_t)0xFFFFFFFB)

static void flashWait()
{
    while(FLASH->STATR & SR_BSY)
                ;
            FLASH->CTLR &= ~CR_PAGE_PG;
}
static void FProgram(u32 adr, u32* buf)
{
    adr &= 0xFFFFFFC0;
    {// FLASH_BufReset_Small();
        FLASH->CTLR |= CR_PAGE_PG;
        FLASH->CTLR |= CR_BUF_RST;
        flashWait();
    }
    for(int j=0;j<16;j++)
    {
        // FLASH_BufLoad(adr+4*j, buf[j]);
        FLASH->CTLR |= CR_PAGE_PG;
        *(__IO uint32_t *)(adr+4*j) = buf[j];
        FLASH->CTLR |= CR_BUF_LOAD;
        flashWait();
    }

    {//FLASH_ProgramPage_Fast(adr);

        FLASH->CTLR |= CR_PAGE_PG;
        FLASH->ADDR = adr;
        FLASH->CTLR |= CR_STRT_Set;
        flashWait();
    }
}



uint16_t PacketsProcessed = 0;
void ProcessRxbuffer( void )
{
	PacketsProcessed++;
	Txbuffer[0] = Rxbuffer[0];
	Txbuffer[1] = Rxbuffer[1];
	Txbuffer[2] = Rxbuffer[2];
	Txbuffer[3] = Rxbuffer[3];
	Txbuffer[4] = Rxbuffer[4];
	Txbuffer[5] = Rxbuffer[5];
	Txbuffer[6] = Rxbuffer[6];
	Txbuffer[7] = Rxbuffer[7];

	switch (Rxbuffer[0])
	{
		case COMMAND_BOOTLOAD:
			{
				if (((uint32_t*)Rxbuffer)[0] == 0x744F6F42 &&  // BoOt
						((uint32_t*)Rxbuffer)[1] == 0x64416F4C) //LoAd
				{
					stayInBoot = 0xB00A;
					RCC_ClearFlag();
					SystemReset_StartMode(Start_Mode_BOOT);
					NVIC_SystemReset();
				}
				else 
				{
					error(SW_ERROR_BOOT_STRING_INCORRECT);
				}
			}
			break;



	       case COMMAND_ASCII_SLEEP:
	        {
	/** \addtogroup ProtocolAsciiCommands
	\{

	----

	ASCII Sleep Command
	---------------------

	This command causes the Serial Wombat to go in a low power mode.  Most Serial Wombat functions and pin modes stop.
	The host should ensure all pins are in a desired state before sleep.


	Transition of the SCL line will wake up the Serial Wombat chip.

	|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
	|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
	|'S'|'l'|'E'|'e'|'P'|'!'|delay LSB|delay MSB|


	Example:

	> `SlEeP!#*`

	Command is echoed back before sleeping.


	\}
	**/
	            if (Rxbuffer[1] == 'l' &&
	                        Rxbuffer[2] == 'E' && Rxbuffer[3] == 'e' &&
	                        Rxbuffer[4] == 'P' && Rxbuffer[5] == '!' )
	            {
	                extern uint16_t shutdownTimer_mS;
	                shutdownTimer_mS = RXBUFFER16(6);

	            }
	            else
	                {
	                    error(SW_ERROR_SLEEP_STRING_INCORRECT);
	                }
	        }
	        break;

		case COMMAND_BINARY_READ_FLASH:
		            {
		                uint32_t address;
		                memcpy( &address, &Rxbuffer[1],4);
		                ((uint32_t*)Txbuffer)[1] = *((uint32_t*)address);
		            }
		            break;
	    case COMMAND_BINARY_WRITE_FLASH:
	            {
	                switch (Rxbuffer[1])
	                {
	                        case 0:
	                        {
uint32_t FLASH_KEY1_     =              ((uint32_t)0x45670123);
uint32_t FLASH_KEY2_     =            ((uint32_t)0xCDEF89AB);

	                                FLASH->KEYR = FLASH_KEY1_;
	                                FLASH->KEYR = FLASH_KEY2_;


	                                FLASH->MODEKEYR = FLASH_KEY1_;
	                                FLASH->MODEKEYR = FLASH_KEY2_;

	                        }
	                        break;

	                    case 1:
	                        {
	                            uint32_t address;
	                            memcpy( &address, &Rxbuffer[2],4);
	                            FProgram(address, (u32*) UserBuffer);
	                        }
	                        break;

	                }
	            }
	    break;
#ifdef PIN_MODE_UART0_TXRX_ENABLE
            /** \addtogroup ProtocolBinaryCommands
              \{

              ----

              Binary Send 7 bytes out first UART
              ---------------------

              Queues 7 bytes to be sent out of the first avaialble Hardware UART.  Assumes a UART pin mode has already been set up.  The host should
              query avaialble space before using this command.


              |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
              |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
              |0xB0|1st Byte to Send |2nd Byte To send |3rd Byte To send | 4th Byte To send | 5th Byte To send |  6th Byte To send | 7th Byte To send |

Response:

Packet is echoed back to the host.

Examples:

Send *WOMBAT!* out of the UART

> `0xB0 0x57 0x4F 0x4D 0x42 0x41 0x54 0x21`

\}
             **/

        case COMMAND_UART0_TX_7BYTES:
            {
                queueAddress =  &PinUpdateRegisters[4];   //Hard Coded to TX pin

                USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
                {
                    int16_t i;
                    for (i = 1; i <= 7; ++i)
                    {
                        QueueAddByte(Rxbuffer[i]);
                    }
                }
                USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
            }
            break;


            /** \addtogroup ProtocolBinaryCommands
              \{

              ----

              Binary Read 7 bytes from first UART
              ---------------------

              Read 7 bytes from the queue of the  first avaialble Hardware UART.  Assumes a UART pin mode has already been set up.  The host should
              query avaialble bytes to determine the nubmer of bytes avaiable before using this command.  This command should only be called if at
              least 7 bytes are available.


              |BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
              |:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
              |0xB1| 0x55* | 0x55* | 0x55* | 0x55* | 0x55* | 0x55* | 0x55* |
             *0x55 is recommended, but any byte is acceptable

Response:

|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xB1|  1st byte read from UART queue |2nd byte read from UART queue |3rd byte read from UART queue |4th byte read from UART queue |5th byte read from UART queue |6th byte read from UART queue |7th byte read from UART queue |


Examples:

Assuming *GHIJKLM* are the first 7 bytes in the UART RX QUEUE:

Sent:
> `0xB1 0x55 0x55 0x55 0x55 0x55 0x55 0x55`

Received:

> `0xB1 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D`

\}
             **/

        case COMMAND_UART0_RX_7BYTES:
            {
                USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
                queueAddress =  &PinUpdateRegisters[5];   //Hard Coded to RX pin
                {
                    int16_t i;
                    for (i = 1; i <=7; ++i)
                    {
                        QueueReadByte(&Txbuffer[i]);
                    }
                }

                USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
            }
            break;
#endif
		default:
		{
		    void ProcessRxBufferCommon(void);
			ProcessRxBufferCommon();
		}
		break;
	}
} // end ProcessRxbuffer


#define FLAG_Mask                ((uint32_t)0x00FFFFFF)
#define ITEN_Mask                ((uint32_t)0x07000000)

#define I2C_GetITStatusSmall(I2C_IT )  (( (I2C1->STAR1 & I2C_IT) ) && ((uint32_t)(((I2C_IT & ITEN_Mask) >> 16) & (I2C1->CTLR2))))

#define I2C_ReceiveData(_dummy) ((uint8_t)I2C1->DATAR)

volatile uint8_t debugLastInterruptAction = 2;

#define I2C_MODE_INIT 0
#define I2C_MODE_RECEIVING 1
#define I2C_MODE_TRANSMITTING 2
uint16_t i2cMode = 0; // 0 = INIT, 1 = Receiving, 2 = Transmitting

volatile I2C_TypeDef *i2cDebugPtr;
uint16_t star1;
#define SW_I2C_STAR1_AF       0x0400
void ProcessRx(void)
{
	i2cDebugPtr = I2C1;
	volatile uint16_t x; // Used for delay


	uint8_t loop = 1;
	while (loop)
	{
		//  for (x = 0; x < 500; ++x); //Debug
		star1 = I2C1->STAR1;
		 if (star1 & I2C_STAR1_STOPF  )
		                                        {

		                        debugLastInterruptAction = 0;
		                        I2C1->CTLR1 = I2C1->CTLR1;
		                                        }



		while (i2cMode == I2C_MODE_RECEIVING && (star1 & 0x040)) // RxNE
		{

			if (i2cRxCount > 5)
			{
				for (x = 0; x < 1000; ++x); //  This delay seems to help prevent bus lockups due to missed last byte before stop
			}
			Rxbuffer[i2cRxCount] = I2C1->DATAR;

			++i2cRxCount;
			if (i2cRxCount == 8)
			{
				ProcessRxbuffer();
				i2cRxCount = 0;
				i2cTxCount = 0;
			}


			star1 = I2C1->STAR1;
		}


		if (i2cMode == I2C_MODE_TRANSMITTING && (star1 & 0x80)) //TxE
		{
		    if (i2cTxCount < TXBUFFER_LENGTH)
		    {
		        I2C1->DATAR = Txbuffer[i2cTxCount++];
		    }
		    else
		    {
		        I2C1->DATAR = 0x55;
		    }
		    if (i2cTxCount == TXBUFFER_LENGTH)
		    {
		        Txbuffer[0] = 'E';
		    }
		}
		else if ((star1 & 0x02) && !(star1 & 0x040))  //Address bit set  and RXNE not
		{
			if (i2cRxCount == 7)
			{
				for (x = 0; x < 500; ++x); //Debug
			}
			if ( i2cRxCount == 0)
			{
				uint16_t tra  = I2C1->STAR2 & 0x04;  //Reading STAR1 and STAR 2 clears bit.
				i2cRxCount = 0;
				i2cTxCount = 0;

				if (tra == 0)
				{
					i2cMode = I2C_MODE_RECEIVING;
				}
				else 
				{
					i2cMode = I2C_MODE_TRANSMITTING;
					if (i2cTxCount < TXBUFFER_LENGTH)
					{
					    I2C1->DATAR = Txbuffer[i2cTxCount++];
					}
					else
					{
					    I2C1->DATAR = 0x55;
					}
				}
			}
		}
		else {
			loop = 0;
		}

		 if (star1 & I2C_STAR1_STOPF  )
		                                                {

		                                i2cRxCount = 0;  // CLear out any small packets.

		                                                }

	}

}




