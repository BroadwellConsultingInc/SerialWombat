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

#include "debug.h"
#include "serialWombat.h"
/* Global define */

/* Global Variable */
vu8 val;

uint16_t __attribute__((section(".stayinboot"))) stayInBoot;

#define CTLR2_FREQ_Reset         ((uint16_t)0xFFC0)
#define CTLR1_PE_Reset           ((uint16_t)0xFFFE)
#define CKCFGR_CCR_Set           ((uint16_t)0x0FFF)
#define CKCFGR_FS_Set            ((uint16_t)0x8000)
#define CTLR1_PE_Set             ((uint16_t)0x0001)
#define CTLR1_CLEAR_Mask         ((uint16_t)0xFBF5)



uint8_t i2cAddress;



static void determineAddress()
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIOC->BSHR = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	i2cAddress = 0x60 ;//
	{volatile uint16_t x;
		for (x = 0; x < 60000; ++x);
	}
	if ((GPIOC->INDR & GPIO_Pin_0) == 0)
	{
		i2cAddress ++;
	}
	if ((GPIOC->INDR & GPIO_Pin_5) == 0)
	{
		i2cAddress += 2;
	}
	if ((GPIOC->INDR & GPIO_Pin_6) == 0)
	{
		i2cAddress += 4;
	}
	if ((GPIOC->INDR & GPIO_Pin_7) == 0)
	{
		i2cAddress += 8;
	}
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // Pull Down to save power
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIOC->BCR = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
}

static void IIC_Init()
{
	RCC->APB2PCENR |=RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO;
	RCC->APB1PCENR |=RCC_APB1Periph_I2C1;

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
	I2C1->CTLR1 |=CTLR1_PE_Set;
}




static void TIM2_INT_Init( u16 arr, u16 psc)
{
    NVIC_InitTypeDef NVIC_InitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 1;
    TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);

    TIM_ClearITPendingBit( TIM2, TIM_IT_Update );

    NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
static void ADC_MultiChannel_Init(void) //TODO optimize
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);

	ADC_DeInit(ADC1);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
	ADC_InitStructure.ADC_NbrOfChannel = 9;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_241Cycles); //WP0, PD1, PC4
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_241Cycles); //WP1, PD2, A3
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_241Cycles); //WP2, PD3, A4
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_241Cycles); //WP3, PD4, A7
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_241Cycles); //WP4, PD5, A5
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_241Cycles); //WP5, PD6, A6
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 7, ADC_SampleTime_241Cycles);// WP6, PD7,PA1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 8, ADC_SampleTime_241Cycles); // WP7, PD0, PA2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 9, ADC_SampleTime_241Cycles);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));

	// Enable ADCs on matching pins

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  //PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  //PA2
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  //PC4
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, uint32_t peripheralAddress, uint32_t memoryAddress, uint16_t bufferSize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = peripheralAddress;
    DMA_InitStructure.DMA_MemoryBaseAddr = memoryAddress;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);
}

uint16_t ADCBuffer[9]; //8 channels plus vref

static void TIM2_DMA_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_Cmd(DMA_CHx, ENABLE);
}

static void TIM2_DMA_InitP2M(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_Cmd(DMA_CHx, ENABLE);
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//SystemCoreClockUpdate();  //TODO  Maybe don't need this.
	//Delay_Init();   //TODO Comment out and retest
	TIM2_INT_Init( 833-1, 1-1);

     //TODO make SystemCoreClock a #define

	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 400;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init( TIM2, &TIM_OCInitStructure );

	TIM_CtrlPWMOutputs(TIM2, ENABLE );
	TIM_OC1PreloadConfig( TIM2, TIM_OCPreload_Disable );
	TIM_ARRPreloadConfig( TIM2, ENABLE );

	extern volatile uint8_t InputArrayA[SIZE_OF_DMA_ARRAY];
	extern uint32_t OutputArrayAHigh[SIZE_OF_DMA_ARRAY];  // High bytes are Set bits, low bytes are clear bits
	TIM2_DMA_Init(DMA1_Channel5, (u32)&GPIOD->BSHR, (u32)OutputArrayAHigh, SIZE_OF_DMA_ARRAY );
	TIM2_DMA_InitP2M(DMA1_Channel2, (u32)&GPIOD->INDR, (u32)InputArrayA, SIZE_OF_DMA_ARRAY);


	TIM_Cmd( TIM2, ENABLE );
	TIM2->DMAINTENR |= (TIM_DMA_CC1 | TIM_DMA_Update);

	AFIO->PCFR1 &= ~AFIO_PCFR1_PA12_REMAP;
	ADC_MultiChannel_Init();
	//TODO make ADC conditional compile
	DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)ADCBuffer, 9);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	i2cAddress = *(uint8_t*)0x1FFFF804;
	if (i2cAddress == 0xFF)
	{
		determineAddress();
	}

	IIC_Init( );

	extern void swSetup();
	swSetup();

	NVIC_EnableIRQ(SysTicK_IRQn);
	SysTick->SR &= ~(1 << 0);
	SysTick->CMP = SystemCoreClock/1000-1;
	SysTick->CNT = 0;
	SysTick->CTLR = 0xF;

	while(1)
	{
		extern void swLoop();
		swLoop();
	}
}


uint16_t GetADCConversion(uint8_t pin)
{
    if (ADCBuffer[pin] >= ADC_MAX_COUNTS)
    {
         return 0xFFFF;
    }
    return ADCBuffer[pin];
}

uint16_t GetSourceVoltage_mV()
{
	uint16_t VrefADC = ADCBuffer[8];

	uint32_t temp = 65536 * 1200;
	temp /= VrefADC;
	return ((uint16_t)temp);
}
