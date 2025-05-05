/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/25
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *
 */

#include <ch32v00x.h>
#include "serialWombat.h"
#include <string.h>
/* Global define */

/* Global Variable */
vu8 val;

/* FLASH Keys */
#define RDP_Key                    ((uint16_t)0x00A5)
#define FLASH_KEY1                 ((uint32_t)0x45670123)
#define FLASH_KEY2                 ((uint32_t)0xCDEF89AB)

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

uint16_t i2cAddress;
static void GPIO_Init_Small( GPIO_InitTypeDef *GPIO_InitStruct)
{
	uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
	uint32_t tmpreg = 0x00, pinmask = 0x00;

	currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);

	if((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
	{
		currentmode |= GPIO_Speed_30MHz;//(uint32_t)GPIO_InitStruct->GPIO_Speed;
	}

	if(((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
	{
		tmpreg = GPIOC->CFGLR;

		for(pinpos = 0x00; pinpos < 0x08; pinpos++)
		{
			pos = ((uint32_t)0x01) << pinpos;
			currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

			if(currentpin == pos)
			{
				pos = pinpos << 2;
				pinmask = ((uint32_t)0x0F) << pos;
				tmpreg &= ~pinmask;
				tmpreg |= (currentmode << pos);


				if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
				{
					GPIOC->BSHR = (((uint32_t)0x01) << pinpos);
				}
			}
		}
		GPIOC->CFGLR = tmpreg;
	}
	//TODO - Just run this and set up GPIOC according to the results.  Merge with other GPIO set below.
}

static void determineAddress()
{
	//GPIO_InitTypeDef GPIO_InitStructure = {0};

	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

	//GPIO_Init_Small(&GPIO_InitStructure);
    i2cAddress = (uint8_t)(0x60 *2);

	if ((GPIOC->INDR & GPIO_Pin_0) == 0)
	{
		i2cAddress += 1 * 2;
	}
	if ((GPIOC->INDR & GPIO_Pin_5) == 0)
	{
		i2cAddress += 2 * 2;
	}
	if ((GPIOC->INDR & GPIO_Pin_6) == 0)
	{
		i2cAddress += 4 * 2;
	}
	if ((GPIOC->INDR & GPIO_Pin_7) == 0)
	{
		i2cAddress += 8 * 2;
	}
}

uint16_t lastUserBufferIndex = 0;
uint8_t UserBuffer[SIZE_OF_USER_BUFFER];

static void I2C_InitSmall()
{



	// RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );
	RCC->APB1PCENR =RCC_APB1Periph_I2C1;


	{  // Set SDA and SCL pins to Alternate function
		uint32_t tmpreg;
		tmpreg = GPIOC->CFGLR;
		tmpreg &= ~0x0FF0;
		tmpreg |= ((0x1C | GPIO_Speed_30MHz) << 4) |((0x1C | GPIO_Speed_30MHz) << 8);
		GPIOC->CFGLR = tmpreg;
	}


	{  // Set up I2C Clock
		uint16_t tmpreg = 0;



		tmpreg = I2C1->CTLR2;
		tmpreg &= CTLR2_FREQ_Reset;

		tmpreg |= 48;
		I2C1->CTLR2 = tmpreg;
	}
	I2C1->CTLR1 &= CTLR1_PE_Reset;


	I2C1->CKCFGR = 50 ;//tmpreg;
	I2C1->CTLR1 |= CTLR1_PE_Set;
	{
		uint16_t tmpreg = 0;

		tmpreg = I2C1->CTLR1;
		tmpreg &= CTLR1_CLEAR_Mask;
		tmpreg |= (uint16_t)((uint32_t)I2C_Mode_I2C | I2C_Ack_Enable);
		I2C1->CTLR1 = tmpreg;
	}

	I2C1->OADDR1 = (I2C_AcknowledgedAddress_7bit | (i2cAddress * 2));

	I2C1->CTLR1 |=CTLR1_PE_Set;// I2C_Cmd( I2C1, ENABLE );
}


static FLASH_Status FLASH_GetBank1StatusLocal(void)
{
	FLASH_Status flashstatus = FLASH_COMPLETE;

	if((FLASH->STATR & FLASH_FLAG_BANK1_BSY) == FLASH_FLAG_BSY)
	{
		flashstatus = FLASH_BUSY;
	}
	else
	{
		/*
		   if((FLASH->STATR & FLASH_FLAG_BANK1_WRPRTERR) != 0)
		   {
		   flashstatus = FLASH_ERROR_WRP;
		   }
		   else */
		{
			flashstatus = FLASH_COMPLETE;
		}
	}
	return flashstatus;
}


static FLASH_Status FLASH_WaitForLastOperationLocal()
{

	while(FLASH_GetBank1StatusLocal() == FLASH_BUSY);

	return FLASH_COMPLETE;
}
/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */

u8 Rxbuffer[8];
u8 Txbuffer[8];

#define error(_errorcode) {Txbuffer[0] = 'E';}

static void processRx()
{
	memcpy(Txbuffer,Rxbuffer,8);

	switch (Rxbuffer[0])
	{

		case 'R':
			{
			    if ((*(uint32_t*)(0x8003FFC) == 0x20250111))  // Only jump to app if it looks like there's a program image
			    {
				NVIC_SystemReset();
			    }
			}
			break;
		case 'V':
			{
				((uint32_t*) Txbuffer)[0] = 0x38304256; //VB08
				((uint32_t*) Txbuffer)[1] = 0x33303242; //B203
			}
			break;

		case COMMAND_BINARY_WRITE_USER_BUFFER:
			{
				lastUserBufferIndex = RXBUFFER16(1);
				uint16_t count = Rxbuffer[3];
				memcpy(&UserBuffer[lastUserBufferIndex],&Rxbuffer[4],count);
				lastUserBufferIndex += count;
			}
			break;
		case COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE:
			{
				if (lastUserBufferIndex < SIZE_OF_USER_BUFFER)
				{
					uint16_t count = SIZE_OF_USER_BUFFER - lastUserBufferIndex - 1;
					if (count >= 7)
					{
						count = 7;
						memcpy(&UserBuffer[lastUserBufferIndex] ,&Rxbuffer[1],count);
						lastUserBufferIndex += count;

					}
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
							{ //FLASH_Unlock_Fast();
								FLASH->KEYR = FLASH_KEY1;
								FLASH->KEYR = FLASH_KEY2;

								/* Fast program mode unlock */
								FLASH->MODEKEYR = FLASH_KEY1;
								FLASH->MODEKEYR = FLASH_KEY2;
							}
							{// FLASH_EraseAllPages();
								FLASH_WaitForLastOperationLocal();
								//if(status == FLASH_COMPLETE)
								{
									FLASH->CTLR |= CR_MER_Set;
									FLASH->CTLR |= CR_STRT_Set;

									//status =
									FLASH_WaitForLastOperationLocal();

									FLASH->CTLR &= CR_MER_Reset;
								}

							}
						}
						break;

					case 1:
						{
							uint32_t address;
							memcpy( &address, &Rxbuffer[2],4);
							FProgram(address, (u32*) UserBuffer);
						}
						break;

					case 4:
						{

							RCC_ClearFlag();
							SystemReset_StartMode(Start_Mode_USER);
						}
						break;
				}
			}
	}
}

uint16_t __attribute__((section(".stayinboot"))) stayInBoot;

uint32_t txCount = 0;
uint16_t rxCount = 0;
uint16_t i2cMode = 0;

static void delayX()
{
    volatile uint16_t x;
                for (x = 0; x < 60000; ++x);
}
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    //Copied from SysInit
 //Already set by reset   RCC->CTLR |= (uint32_t)0x00000001;
    //  RCC->CFGR0 &= (uint32_t)0xF8FF0000;
    //  RCC->CTLR &= (uint32_t)0xFEF6FFFF;
    //  RCC->CTLR &= (uint32_t)0xFFFBFFFF;
    //  RCC->CFGR0 &= (uint32_t)0xFFFEFFFF;
    //  RCC->INTR = 0x009F0000;


    //RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
            RCC->APB2PCENR |=RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO;
            delayX();
    GPIOC->CFGLR = 0x88848448;

        GPIOC->BSHR = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
        delayX();
        //Jump to app if the stayInBoot Ram location isn't set to magic value and a "programmed" magic value is set at end of flash
        // and the boot pin is not being pulled low
	if (stayInBoot != 0xB00A && (*(uint32_t*)(0x8003FFC) == 0x20250111) && (GPIOC->INDR & GPIO_Pin_3))
	{
		NVIC_SystemReset();
	}

	i2cAddress = *(uint8_t*)0x1FFFF804;
	if (i2cAddress == 0xFF)
	{
	determineAddress();
	}
	I2C_InitSmall();
	while (1)
	{
		if (I2C1->STAR1 & 0x02)  //Address bit set
		{
			uint16_t tra  = I2C1->STAR2 & 0x04;  //Reading STAR1 and STAR 2 clears bit.
			rxCount = 0;
			txCount = 0;
			if (tra == 0)
			{

				i2cMode = 1;
			}
			else {

				i2cMode = 2;
				I2C1->DATAR = Rxbuffer[txCount];
				++txCount;
			}
		}

		if (i2cMode == 1 && (I2C1->STAR1 & 0x040)) // RxNE
		{
			Rxbuffer[rxCount] = I2C1->DATAR;
			++rxCount;
			if (rxCount == 8)
			{
			  processRx();
				rxCount = 0;
				txCount = 0;
			}
		}
		if (i2cMode == 2 && (I2C1->STAR1 & 0x80)) //TxE
		{
			I2C1->DATAR = Txbuffer[txCount];
			++txCount;
		}
	}
}
