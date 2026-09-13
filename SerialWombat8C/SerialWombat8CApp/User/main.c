/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/08/22
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 *TIMER_INT
 *MODE 1 Timer count triggers update interrupt. Updata_time = psc*arr*RepetitionCounter/system
 *MODE 2 generates an update event and triggers an update interrupt.
 *
 */

#include "debug.h"
#include "serialWombat.h"
/* Global define */
uint16_t __attribute__((section(".stayinboot"))) stayInBoot;

/*
 * Retain the original WCH TIM1 interrupt/demo code for examination.
 * Set to 1 if it needs to be built again; otherwise it consumes no flash.
 */
#define KEEP_UNUSED_TIM1_TEST_CODE 0

#if KEEP_UNUSED_TIM1_TEST_CODE

/* Mode Selection */
#define MODE MODE1
//#define MODE MODE2

/*********************************************************************
 * @fn      TIM1_UP_IRQHandler
 *
 * @brief   This function handles TIM1 UP exception.
 *
 *
 * @return  none
 */
void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update)==SET)
    {

    }

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}

/*********************************************************************
 * @fn      TIM1_INT_Init
 *
 * @brief   Initializes TIM1 output compare.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *
 * @return  none
 */
void TIM1_INT_Init(u16 arr, u16 psc)
{
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
}

#endif /* KEEP_UNUSED_TIM1_TEST_CODE */
#define SYSTICK_CTLR_STE    (1U << 0)   // Counter enable
#define SYSTICK_CTLR_STIE   (1U << 1)   // Interrupt enable
#define SYSTICK_CTLR_STCLK  (1U << 2)   // HCLK clock source
#define SYSTICK_CTLR_STRE   (1U << 3)   // Auto reload
void SysTick_Init_1ms(void)
{
    SysTick->CTLR = 0;

    SysTick->SR = 0;
    SysTick->CNT = 0;

    SysTick->CMP = (SystemCoreClock / 1000) - 1;

    NVIC_EnableIRQ(SysTicK_IRQn);

    SysTick->CTLR =
        SYSTICK_CTLR_STE  |   // Enable SysTick
        SYSTICK_CTLR_STIE |   // Enable SysTick interrupt
        SYSTICK_CTLR_STCLK |   // Clock source = HCLK
        SYSTICK_CTLR_STRE;     // Auto reload
}


/*
 * TIM2 timed GPIO DMA
 *
 * CH32V006 fixed DMA request mapping:
 *   TIM2_UP  -> DMA1 Channel 2
 *   TIM2_CH1 -> DMA1 Channel 5
 *
 * Preserve the CH32V003 timing:
 *   TIM2 counts 0..832 at 48 MHz (833 clocks/period, ~57.623 kHz).
 *   TIM2_CH1 compare occurs at count 400.
 *
 * Per timer period:
 *   DMA1 Channel 5: OutputArrayAHigh[] -> GPIOD->BSHR on TIM2_CH1.
 *   DMA1 Channel 2: GPIOD->INDR -> InputArrayA[] on TIM2 update.
 */
#define TIM2_DMA_PERIOD_COUNTS           833u
#define TIM2_DMA_COMPARE_COUNTS          400u
#define TIM2_DMA_PRESCALER               0u

extern volatile uint8_t InputArrayA[SIZE_OF_DMA_ARRAY];
extern uint32_t OutputArrayAHigh[SIZE_OF_DMA_ARRAY];

static void TIM2_TimedDMA_TimerInit(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};

    RCC_PB1PeriphClockCmd(RCC_PB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = TIM2_DMA_PERIOD_COUNTS - 1u;
    TIM_TimeBaseInitStructure.TIM_Prescaler = TIM2_DMA_PRESCALER;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    /*
     * CH1 is used only to generate the second DMA request within the period.
     * Keep OutputState enabled to match the original V003 timer setup.
     * No TIM2_CH1 GPIO pin is configured here.
     */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = TIM2_DMA_COMPARE_COUNTS;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
}

static void TIM2_OutputDMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_HBPeriphClockCmd(RCC_HBPeriph_DMA1, ENABLE);

    /*
     * CH32V006 mapping:
     * TIM2_CH1 -> DMA1 Channel 5.
     *
     * One 32-bit BSHR value is written at every CH1 compare.
     */
    DMA_DeInit(DMA1_Channel5);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOD->BSHR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)OutputArrayAHigh;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = SIZE_OF_DMA_ARRAY;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel5, ENABLE);
}

static void TIM2_InputDMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_HBPeriphClockCmd(RCC_HBPeriph_DMA1, ENABLE);

    /*
     * CH32V006 mapping:
     * TIM2_UP -> DMA1 Channel 2.
     *
     * GPIOD->INDR is a 32-bit register, but Serial Wombat only needs
     * PD0..PD7 here, so preserve the original byte-sized DMA transfer.
     */
    DMA_DeInit(DMA1_Channel2);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&GPIOD->INDR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)InputArrayA;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = SIZE_OF_DMA_ARRAY;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel2, ENABLE);
}

static void TIM2_TimedDMA_Init(void)
{
    /*
     * Configure timer and both DMA channels before TIM2 is allowed to run.
     * This preserves the original startup ordering: the first hardware
     * request encountered after TIM2 starts is CH1 at count 400, followed
     * by the update request when the counter rolls over.
     */
    TIM2_TimedDMA_TimerInit();
    TIM2_InputDMA_Init();
    TIM2_OutputDMA_Init();

    TIM_DMACmd(TIM2, TIM_DMA_Update | TIM_DMA_CC1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

uint8_t i2cAddress = 0x60;

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

#define CTLR2_FREQ_Reset         ((uint16_t)0xFFC0)
#define CTLR1_PE_Reset           ((uint16_t)0xFFFE)
#define CTLR1_PE_Set             ((uint16_t)0x0001)
#define CTLR1_CLEAR_Mask         ((uint16_t)0xFBF5)

/*
 * These two V003-era I2C masks are not used by the current IIC_Init().
 * Retain them for examination and later removal without compiling them.
 */
#define KEEP_UNUSED_I2C_V003_DEFINES 0
#if KEEP_UNUSED_I2C_V003_DEFINES
#define CKCFGR_CCR_Set           ((uint16_t)0x0FFF)
#define CKCFGR_FS_Set            ((uint16_t)0x8000)
#endif

static void IIC_Init(void)
{
    /*
     * Enable GPIOC, AFIO, and I2C1 clocks.
     *
     * CH32V006 names these PB1/PB2 rather than APB1/APB2
     * in the peripheral structures and library definitions.
     */
    RCC->PB2PCENR |= RCC_PB2Periph_GPIOC |
                     RCC_PB2Periph_AFIO;

    RCC->PB1PCENR |= RCC_PB1Periph_I2C1;

    /*
     * I2C1 default pins:
     *
     * PC1 = SDA
     * PC2 = SCL
     *
     * Configure both as 30 MHz alternate-function
     * open-drain outputs.
     *
     * For CH32V006:
     *      AF_OD = CNF 11
     *      30MHz = MODE 01
     *
     * Therefore each pin configuration nibble = 0xD.
     */
    {
        uint32_t tmpreg = GPIOC->CFGLR;

        /* Clear PC1 and PC2 configuration fields */
        tmpreg &= ~((0x0FUL << 4) |
                    (0x0FUL << 8));

        /* PC1 SDA = AF open drain, 30 MHz */
        tmpreg |= (0x0DUL << 4);

        /* PC2 SCL = AF open drain, 30 MHz */
        tmpreg |= (0x0DUL << 8);

        GPIOC->CFGLR = tmpreg;
    }

    /*
     * Disable I2C peripheral while configuring it.
     */
    I2C1->CTLR1 &= CTLR1_PE_Reset;

    /*
     * CTLR2 FREQ field contains the APB1/PB1 peripheral
     * clock frequency in MHz.
     *
     * We're running PCLK1 at 48 MHz.
     */
    {
        uint16_t tmpreg = I2C1->CTLR2;

        tmpreg &= CTLR2_FREQ_Reset;
        tmpreg |= 48;

        I2C1->CTLR2 = tmpreg;
    }

    /*
     * Clock control register.
     *
     * For slave operation this does NOT set the incoming
     * I2C bus rate -- the external master generates SCL.
     *
     * Retaining the value from the V003 implementation.
     */
    I2C1->CKCFGR = 50;

    /*
     * Enable peripheral.
     */
    I2C1->CTLR1 |= CTLR1_PE_Set;

    /*
     * Configure I2C mode and enable ACK.
     */
    {
        uint16_t tmpreg = I2C1->CTLR1;

        tmpreg &= CTLR1_CLEAR_Mask;
        tmpreg |= (uint16_t)(
                (uint32_t)I2C_Mode_I2C |
                I2C_Ack_Enable);

        I2C1->CTLR1 = tmpreg;
    }

    /*
     * Explicitly enable clock stretching.
     *
     * CTLR1 bit 7 = NOSTRETCH
     *     0 = clock stretching allowed
     *     1 = clock stretching disabled
     *
     * It should already be zero after reset, but because
     * Serial Wombat relies heavily on clock stretching,
     * make this explicit.
     */
    I2C1->CTLR1 &= ~(1U << 7);

    /*
     * Configure 7-bit slave address.
     *
     * i2cAddress is assumed to contain the unshifted
     * 7-bit address, e.g. 0x60.
     */
    I2C1->OADDR1 =
        I2C_AcknowledgedAddress_7bit |
        ((uint16_t)i2cAddress << 1);

    /*
     * Enable I2C.
     */
    I2C1->CTLR1 |= CTLR1_PE_Set;
}


#define CH32V006_ADC_CHANNEL_COUNT        9u
#define CH32V006_ADC_MAX_LEFT_ALIGNED     0xFFF0u

uint16_t ADCBuffer[CH32V006_ADC_CHANNEL_COUNT];

static void ADC_MultiChannel_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    /* GPIO and ADC clocks.  Keep the same GPIO blocks enabled as the V003 code. */
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC |
                          RCC_PB2Periph_GPIOA |
                          RCC_PB2Periph_GPIOD |
                          RCC_PB2Periph_AFIO,
                          ENABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_ADC1, ENABLE);

    /* Preserve the V003 ADC clock divider. */
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
    ADC_InitStructure.ADC_NbrOfChannel = CH32V006_ADC_CHANNEL_COUNT;
    ADC_Init(ADC1, &ADC_InitStructure);

    /*
     * Preserve the original scan order:
     *   Buffer[0] = ADC2
     *   Buffer[1] = ADC3
     *   Buffer[2] = ADC4
     *   Buffer[3] = ADC7
     *   Buffer[4] = ADC5
     *   Buffer[5] = ADC6
     *   Buffer[6] = ADC1
     *   Buffer[7] = ADC0
     *   Buffer[8] = Vrefint
     *
     * CH32V003 used ADC_SampleTime_241Cycles.
     * CH32V006's longest library setting is CyclesMode7 = 239.5 cycles.
     */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2,       1, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3,       2, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4,       3, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7,       4, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5,       5, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6,       6, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1,       7, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0,       8, ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 9, ADC_SampleTime_CyclesMode7);

    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    /* Used by WCH's CH32V006 ADC examples. */
    ADC_BufferCmd(ADC1, DISABLE);

    /*
     * No ADC_ResetCalibration()/ADC_StartCalibration() sequence here.
     * The CH32V006 EVT ADC driver/example does not expose/use the V003-style
     * calibration sequence.
     */

    /* Preserve the GPIO analog configuration performed by the V003 source. */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; /* PA1, PA2 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;              /* PC4 */
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void ADC_DMA_Init(DMA_Channel_TypeDef *DMA_CHx,
                         uint32_t peripheralAddress,
                         uint32_t memoryAddress,
                         uint16_t bufferSize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_HBPeriphClockCmd(RCC_HBPeriph_DMA1, ENABLE);

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

/* Call once during startup. */
void ADC_ContinuousDMA_Init(void)
{
    ADC_MultiChannel_Init();

    ADC_DMA_Init(DMA1_Channel1,
                 (uint32_t)&ADC1->RDATAR,
                 (uint32_t)ADCBuffer,
                 CH32V006_ADC_CHANNEL_COUNT);

    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t GetADCConversion(uint8_t pin)
{
    if(pin >= 8u)
    {
        return 0xFFFFu;
    }

    /* 12-bit CH32V006 ADC, left aligned: full scale = 0xFFF0. */
    if(ADCBuffer[pin] >= CH32V006_ADC_MAX_LEFT_ALIGNED)
    {
        return 0xFFFFu;
    }

    return ADCBuffer[pin];
}

uint16_t GetSourceVoltage_mV(void)
{
    uint16_t VrefADC = ADCBuffer[8];
    uint32_t temp;

    if(VrefADC == 0u)
    {
        return 0xFFFFu;
    }

    /* Preserve the original code's 1.200 V internal-reference assumption. */
    temp = 65536UL * 1200UL;
    temp /= VrefADC;

    return (uint16_t)temp;
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
    SystemCoreClockUpdate();
    Delay_Init();
    SysTick_Init_1ms();

#if KEEP_UNUSED_TIM1_TEST_CODE
    /*
     * Original TIM1 test/demo startup retained for examination.
     * It is superseded by TIM2_TimedDMA_Init().
     */
    // TIM1_INT_Init(1000 - 1, 48 - 1);

#if (MODE == MODE1)
    // TIM_Cmd(TIM1, ENABLE);
#elif (MODE == MODE2)
    TIM_GenerateEvent(TIM1, TIM_IT_Update);
#endif
#endif /* KEEP_UNUSED_TIM1_TEST_CODE */

    /*
     * Timed GPIO DMA:
     *   TIM2_CH1 -> DMA1 Channel 5 -> GPIOD->BSHR
     *   TIM2_UP  -> DMA1 Channel 2 -> InputArrayA
     */
    TIM2_TimedDMA_Init();

    /*
     * ADC uses DMA1 Channel 1.  It can operate concurrently with the
     * TIM2 GPIO DMA channels.
     */
    ADC_ContinuousDMA_Init();
    determineAddress();
    IIC_Init();

	while(1)
	{
		extern void swLoop();
		swLoop();
	}
}

