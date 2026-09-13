/*
Copyright 2021-2026 Broadwell Consulting Inc.

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
#include "debug.h"
#include <stdint.h>
#include <string.h>

/*
 * CH32V006 WS2812 implementation
 * -----------------------------
 *
 * This implementation preserves the Serial Wombat 18AB WS2812 protocol as
 * closely as possible, while changing the hardware rendering backend to
 * CH32V006 SPI1 + DMA1 Channel 3.
 *
 * Hardware output is fixed to Serial Wombat pin WP2 / CH32V006 PD3.
 * SPI1 remap value 010 routes SPI1 MOSI to PD3.  PD2 is the corresponding
 * remapped SCK pin, but it is intentionally left configured as GPIO; the
 * WS2812 interface only needs MOSI.
 *
 * SPI1 is operated at PCLK2 / 16.  With the normal 48 MHz clock this is
 * 3 MHz.  Each WS2812 data bit is encoded into four SPI bits:
 *
 *      WS2812 0 -> 1000
 *      WS2812 1 -> 1110
 *
 * Two WS2812 bits therefore fit in each SPI byte.
 *
 * UserBuffer runtime allocation beginning at userBufferIndex:
 *
 *      12 * numLEDs bytes     Encoded SPI/DMA waveform
 *      32 bytes               Zero tail for WS2812 reset/latch
 *       3 * numLEDs bytes     Current LED colors, stored B,G,R
 *
 * Total runtime allocation returned by CONFIGURE_CHANNEL_MODE_2:
 *
 *      15 * numLEDs + 32 bytes
 *
 * Animation storage remains protocol-compatible with the 18AB version and
 * is separately allocated with CONFIGURE_CHANNEL_MODE_4:
 *
 *      Per frame: 2-byte delay + 3 bytes B,G,R per LED
 */

#define WS2812_WOMBAT_PIN                   2u  /* WP2 = PD3 */
#define WS2812_GPIO_PIN                     GPIO_Pin_3

#define WS2812_SPI_BYTES_PER_LED            12u
#define WS2812_COLOR_BYTES_PER_LED          3u
#define WS2812_RESET_BYTES                  32u

#define WS2812_SPI1_RM_MASK                 0x00000007u
#define WS2812_SPI1_RM_PD3                  0x00000002u

#define WS2812_DMA_CHANNEL                  DMA1_Channel3
#define WS2812_DMA_TC_FLAG                  DMA1_FLAG_TC3
#define WS2812_DMA_GL_FLAG                  DMA1_FLAG_GL3

#define WS2812_RUNTIME_BYTES(_leds) \
    ((uint16_t)((uint16_t)(_leds) * \
    (WS2812_SPI_BYTES_PER_LED + WS2812_COLOR_BYTES_PER_LED) + \
    WS2812_RESET_BYTES))

#define WS2812_DMA_BYTES(_leds) \
    ((uint16_t)((uint16_t)(_leds) * WS2812_SPI_BYTES_PER_LED + \
    WS2812_RESET_BYTES))

#define WS2812_COLOR_OFFSET(_leds) \
    ((uint16_t)((uint16_t)(_leds) * WS2812_SPI_BYTES_PER_LED + \
    WS2812_RESET_BYTES))

#define WS2812_DEFAULT_REFRESH_DELAY(_leds) \
    ((uint16_t)(_leds) + 10u)

#define WS2812_CHASE_DELAY_MS               200u


typedef enum
{
    WS2812_MODE_BUFFERED = 0,
    WS2812_MODE_ANIMATION = 1,
    WS2812_MODE_CHASE = 2,
    WS2812_MODE_BARGRAPH = 3,
} ws2812_mode_t;


typedef struct ws2812
{
    uint32_t offColor;
    uint32_t onColor;
    uint16_t userBufferIndex;
    uint16_t animationLedsIndex;
    uint16_t delay;
    uint16_t bgMax;
    uint16_t bgMin;
    uint8_t numOfLEDS;
    uint8_t chaseColor;
    uint8_t chaseLED;
    uint8_t mode;
    uint8_t animationFrames;
    uint8_t currentAnimationFrame;
    uint8_t bgSourcePin;
    uint8_t bgOnLEDs;
    uint8_t dmaActive;
    uint8_t refreshPending;
} ws2812_t;

#define ws2812 ((ws2812_t*)CurrentPinRegister)

static ws2812_t* debugWS2812;


/*
 * The original PIC24FJ256GA702 implementation expanded each WS2812 bit to
 * one 16-bit SPI word and used DMA channel 5.  Keep the important hardware
 * portion here as compile-disabled reference while the CH32V006 port is
 * being evaluated.
 */
#define KEEP_PIC24_WS2812_HARDWARE_REFERENCE 0
#if KEEP_PIC24_WS2812_HARDWARE_REFERENCE
#define PIC24_SPI_1_BIT 0xFC00
#define PIC24_SPI_0_BIT 0xE000
/*
void StartDMA()
{
    DMACH5bits.CHEN = 0;
    DMACNT5 = (uint16_t)ws2812->numOfLEDS * 24 * 2;
    DMADST5 = (uint16_t)&SPI1BUFL;
    DMASRC5 = (uint16_t)dmaBuffer;
    DMACH5 = 0x140 & 0xFFFE;
    DMAINT5 = 0x2700;
    DMACH5bits.CHEN = 1;
}

void StopDMA()
{
    DMACH5bits.CHEN = 0;
}
*/
#endif


#define NUMBER_OF_COLORS 6
static const uint32_t ColorTable[NUMBER_OF_COLORS] =
{
    0x00FF0000, /* Red */
    0x0000FF00, /* Green */
    0x000000FF, /* Blue */
    0x00FFFFFF, /* White */
    0x00FFFF00, /* Yellow */
    0x00800080, /* Purple */
};


/*
 * Each nibble below represents one WS2812 data bit at a 3 MHz SPI clock.
 * The table converts four WS2812 bits to a 16-bit SPI stream.
 */
static const uint16_t WS2812NibbleEncode[16] =
{
    0x8888, 0x888E, 0x88E8, 0x88EE,
    0x8E88, 0x8E8E, 0x8EE8, 0x8EEE,
    0xE888, 0xE88E, 0xE8E8, 0xE8EE,
    0xEE88, 0xEE8E, 0xEEE8, 0xEEEE,
};


static uint16_t ws2812ColorBufferIndex(void)
{
    return (uint16_t)(ws2812->userBufferIndex +
        WS2812_COLOR_OFFSET(ws2812->numOfLEDS));
}


static uint8_t* ws2812DMABuffer(void)
{
    return &UserBuffer[ws2812->userBufferIndex];
}


static uint8_t* ws2812ColorBuffer(void)
{
    return &UserBuffer[ws2812ColorBufferIndex()];
}


static uint8_t ws2812RuntimeBufferValid(uint16_t userBufferIndex,
                                        uint8_t numberOfLEDs)
{
    uint32_t end = (uint32_t)userBufferIndex +
        (uint32_t)WS2812_RUNTIME_BYTES(numberOfLEDs);

    return (end <= SIZE_OF_USER_BUFFER);
}


static uint32_t ws2812AnimationFrameSize(void)
{
    return 2u + 3u * (uint32_t)ws2812->numOfLEDS;
}


static uint8_t ws2812AnimationBufferValid(uint16_t index, uint8_t frames)
{
    uint32_t bytes = ws2812AnimationFrameSize() * (uint32_t)frames;
    uint32_t end = (uint32_t)index + bytes;

    if (end > SIZE_OF_USER_BUFFER)
    {
        return 0;
    }

    if (frames != 0u)
    {
        uint32_t runtimeStart = ws2812->userBufferIndex;
        uint32_t runtimeEnd = runtimeStart +
            WS2812_RUNTIME_BYTES(ws2812->numOfLEDS);
        uint32_t animationStart = index;
        uint32_t animationEnd = end;

        if (animationStart < runtimeEnd && animationEnd > runtimeStart)
        {
            return 0;
        }
    }

    return 1;
}


static void ws2812StoreColor(uint8_t led, uint32_t rgb)
{
    uint16_t index = (uint16_t)led * WS2812_COLOR_BYTES_PER_LED;
    uint8_t* colors = ws2812ColorBuffer();

    colors[index] = (uint8_t)rgb;          /* B */
    colors[index + 1u] = (uint8_t)(rgb >> 8);  /* G */
    colors[index + 2u] = (uint8_t)(rgb >> 16); /* R */
}


static void ws2812EncodeByte(uint8_t value, uint8_t** destination)
{
    uint16_t upper = WS2812NibbleEncode[value >> 4];
    uint16_t lower = WS2812NibbleEncode[value & 0x0F];

    *(*destination)++ = (uint8_t)(upper >> 8);
    *(*destination)++ = (uint8_t)upper;
    *(*destination)++ = (uint8_t)(lower >> 8);
    *(*destination)++ = (uint8_t)lower;
}


static void ws2812BuildDMABuffer(void)
{
    uint8_t* destination = ws2812DMABuffer();
    uint8_t* colors = ws2812ColorBuffer();
    uint8_t led;

    for (led = 0; led < ws2812->numOfLEDS; ++led)
    {
        /* Current color storage is B,G,R; WS2812 transmission is G,R,B. */
        uint8_t blue = colors[0];
        uint8_t green = colors[1];
        uint8_t red = colors[2];

        ws2812EncodeByte(green, &destination);
        ws2812EncodeByte(red, &destination);
        ws2812EncodeByte(blue, &destination);

        colors += WS2812_COLOR_BYTES_PER_LED;
    }

    /*
     * 32 zero SPI bytes at 3 MHz are about 85.3 us low.  This provides the
     * WS2812 reset/latch interval as part of the DMA transaction itself.
     */
    memset(destination, 0, WS2812_RESET_BYTES);
}


static void ws2812ConfigHardware(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_AFIO |
                          RCC_PB2Periph_GPIOD |
                          RCC_PB2Periph_SPI1,
                          ENABLE);
    RCC_HBPeriphClockCmd(RCC_HBPeriph_DMA1, ENABLE);

    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE);
    SPI_Cmd(SPI1, DISABLE);

    /*
     * CH32V006 has a 3-bit SPI1 remap selection.  SPI1_RM = 010 routes:
     *     SCK  -> PD2
     *     MOSI -> PD3
     * Only PD3 is configured for alternate-function output here.
     *
     * GPIO_PinRemapConfig() in some CH32V00x library revisions only exposes
     * the older one-bit SPI1 remap symbol, so set just the V006 SPI1_RM bits
     * directly while leaving every other AFIO remap field unchanged.
     */
    AFIO->PCFR1 = (AFIO->PCFR1 & ~WS2812_SPI1_RM_MASK) |
                  WS2812_SPI1_RM_PD3;

    /* Put the GPIO output latch low before handing PD3 to SPI1. */
    GPIOD->BCR = WS2812_GPIO_PIN;

    GPIO_InitStructure.GPIO_Pin = WS2812_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    SPI_Cmd(SPI1, ENABLE);
}


static void ws2812StartDMA(void)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    ws2812BuildDMABuffer();
    ws2812ConfigHardware();

    DMA_Cmd(WS2812_DMA_CHANNEL, DISABLE);
    DMA_DeInit(WS2812_DMA_CHANNEL);
    DMA_ClearFlag(WS2812_DMA_GL_FLAG);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DATAR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ws2812DMABuffer();
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = WS2812_DMA_BYTES(ws2812->numOfLEDS);
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(WS2812_DMA_CHANNEL, &DMA_InitStructure);
    DMA_Cmd(WS2812_DMA_CHANNEL, ENABLE);

    ws2812->dmaActive = 1u;
    ws2812->refreshPending = 0u;
}


static void ws2812ServiceDMAComplete(void)
{
    if (ws2812->dmaActive &&
        DMA_GetFlagStatus(WS2812_DMA_TC_FLAG) != RESET)
    {
        /* DMA completion means the last byte has reached DATAR. */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET)
        {
        }

        DMA_Cmd(WS2812_DMA_CHANNEL, DISABLE);
        DMA_ClearFlag(WS2812_DMA_GL_FLAG);
        ws2812->dmaActive = 0u;
    }
}


static void ws2812BuildChaseFrame(void)
{
    uint8_t led;

    for (led = 0; led < ws2812->numOfLEDS; ++led)
    {
        if (led == ws2812->chaseLED)
        {
            ws2812StoreColor(led, ColorTable[ws2812->chaseColor]);
        }
        else
        {
            ws2812StoreColor(led, 0);
        }
    }

    ++ws2812->chaseLED;
    if (ws2812->chaseLED >= ws2812->numOfLEDS)
    {
        ws2812->chaseLED = 0;
        ++ws2812->chaseColor;
        if (ws2812->chaseColor >= NUMBER_OF_COLORS)
        {
            ws2812->chaseColor = 0;
        }
    }
}


static void ws2812BuildAnimationFrame(void)
{
    uint32_t frameSize = ws2812AnimationFrameSize();
    uint32_t index = (uint32_t)ws2812->animationLedsIndex +
        (uint32_t)ws2812->currentAnimationFrame * frameSize;

    if (ws2812->animationFrames == 0u ||
        !ws2812AnimationBufferValid(ws2812->animationLedsIndex,
                                    ws2812->animationFrames))
    {
        return;
    }

    ws2812->delay = (uint16_t)UserBuffer[index] |
                    ((uint16_t)UserBuffer[index + 1u] << 8);

    memcpy(ws2812ColorBuffer(),
           &UserBuffer[index + 2u],
           (uint16_t)ws2812->numOfLEDS * WS2812_COLOR_BYTES_PER_LED);

    ++ws2812->currentAnimationFrame;
    if (ws2812->currentAnimationFrame >= ws2812->animationFrames)
    {
        ws2812->currentAnimationFrame = 0;
    }
}


static void ws2812BuildBarGraphFrame(void)
{
    uint8_t led;
    uint32_t value = GetBuffer(ws2812->bgSourcePin);

    ws2812->bgOnLEDs = 0;

    if (value >= ws2812->bgMax)
    {
        ws2812->bgOnLEDs = ws2812->numOfLEDS;
    }
    else if (value <= ws2812->bgMin)
    {
        ws2812->bgOnLEDs = 0;
    }
    else if ((ws2812->bgMin == 0u && ws2812->bgMax == 65535u) ||
             ws2812->bgMax == ws2812->bgMin)
    {
        value *= ws2812->numOfLEDS;
        value >>= 16;
        ws2812->bgOnLEDs = (uint8_t)value;
    }
    else
    {
        value -= ws2812->bgMin;
        value <<= 16;
        value /= (ws2812->bgMax - ws2812->bgMin);
        value *= ws2812->numOfLEDS;
        value >>= 16;
        ws2812->bgOnLEDs = (uint8_t)value;
    }

    for (led = 0; led < ws2812->numOfLEDS; ++led)
    {
        ws2812StoreColor(led,
            (led < ws2812->bgOnLEDs) ? ws2812->onColor : ws2812->offColor);
    }
}


/*!
 * \brief Initialization / protocol handler for the WS2812 pin mode.
 *
 * Protocol compatibility with the SW18AB implementation is retained:
 *
 * CONFIGURE_CHANNEL_MODE_0 (0xC8):
 *   Byte 1 = pin.  CH32V006 implementation requires WP2 / PD3.
 *   Byte 2 = PIN_MODE_WS2812 (12)
 *   Bytes 3-4 = runtime UserBuffer index
 *   Byte 5 = number of LEDs
 *
 * CONFIGURE_CHANNEL_MODE_1 (0xC9): set one LED color.
 * CONFIGURE_CHANNEL_MODE_2 (0xCA): query runtime UserBuffer bytes.
 * CONFIGURE_CHANNEL_MODE_3 (0xCB): set one animation LED.
 * CONFIGURE_CHANNEL_MODE_4 (0xCC): set animation UserBuffer index/frames.
 * CONFIGURE_CHANNEL_MODE_5 (0xCD): set animation frame delay.
 * CONFIGURE_CHANNEL_MODE_6 (0xCE): set mode.
 * CONFIGURE_CHANNEL_MODE_7 (0xCF): set bargraph min/max.
 */
void initWS2812(void)
{
    debugWS2812 = (ws2812_t*)CurrentPinRegister;

    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 &&
        CurrentPinRegister->generic.mode != PIN_MODE_WS2812)
    {
        error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
        return;
    }

    switch (Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:
        {
            uint16_t userBufferIndex = RXBUFFER16(3);
            uint8_t numberOfLEDs = Rxbuffer[5];

            /* Stop an earlier WS2812 transfer before reinitializing its buffers. */
            if (CurrentPinRegister->generic.mode == PIN_MODE_WS2812)
            {
                DMA_Cmd(WS2812_DMA_CHANNEL, DISABLE);
                DMA_ClearFlag(WS2812_DMA_GL_FLAG);
                SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE);
                SPI_Cmd(SPI1, DISABLE);
            }

            if (Rxbuffer[1] != WS2812_WOMBAT_PIN)
            {
                error(SW_ERROR_PIN_NOT_CAPABLE);
                return;
            }

            if (!ws2812RuntimeBufferValid(userBufferIndex, numberOfLEDs))
            {
                error(SW_ERROR_WUB_INVALID_ADDRESS);
                return;
            }

            ws2812->userBufferIndex = userBufferIndex;
            ws2812->animationLedsIndex = 0;
            ws2812->animationFrames = 0;
            ws2812->numOfLEDS = numberOfLEDs;
            ws2812->chaseColor = 0;
            ws2812->chaseLED = 0;
            ws2812->delay = 0;
            ws2812->mode = WS2812_MODE_BUFFERED;
            ws2812->bgMax = 65535;
            ws2812->bgMin = 0;
            ws2812->bgSourcePin = 0;
            ws2812->bgOnLEDs = 0;
            ws2812->offColor = 0;
            ws2812->onColor = 0;
            ws2812->currentAnimationFrame = 0;
            ws2812->dmaActive = 0;
            ws2812->refreshPending = 1;

            memset(ws2812DMABuffer(),
                   0,
                   WS2812_RUNTIME_BYTES(ws2812->numOfLEDS));

            CurrentPinRegister->generic.mode = PIN_MODE_WS2812;
            ws2812ConfigHardware();
        }
        break;

        case CONFIGURE_CHANNEL_MODE_1:
        {
            uint32_t rgb = RXBUFFER32(4) & 0x00FFFFFFu;

            if (Rxbuffer[3] >= ws2812->numOfLEDS)
            {
                error(SW_ERROR_WS2812_INDEX_GT_LEDS);
                return;
            }

            if (Rxbuffer[3] == 0u)
            {
                ws2812->offColor = rgb;
            }
            else if (Rxbuffer[3] == 1u)
            {
                ws2812->onColor = rgb;
            }

            ws2812StoreColor(Rxbuffer[3], rgb);
            ws2812->refreshPending = 1u;
            ws2812->delay = 0;
        }
        break;

        case CONFIGURE_CHANNEL_MODE_2:
        {
            TXBUFFER16(3, WS2812_RUNTIME_BYTES(Rxbuffer[3]));
        }
        break;

        case CONFIGURE_CHANNEL_MODE_3:
        {
            uint32_t frameSize = ws2812AnimationFrameSize();
            uint32_t index;

            if (Rxbuffer[4] >= ws2812->numOfLEDS)
            {
                error(SW_ERROR_WS2812_INDEX_GT_LEDS);
                return;
            }

            if (ws2812->animationFrames == 0u ||
                Rxbuffer[3] >= ws2812->animationFrames)
            {
                error(SW_ERROR_INVALID_PARAMETER_3);
                return;
            }

            if (!ws2812AnimationBufferValid(ws2812->animationLedsIndex,
                                             ws2812->animationFrames))
            {
                error(SW_ERROR_WUB_INVALID_ADDRESS);
                return;
            }

            index = (uint32_t)ws2812->animationLedsIndex +
                    (uint32_t)Rxbuffer[3] * frameSize +
                    2u + (uint32_t)Rxbuffer[4] * 3u;

            /* Preserve SW18AB animation storage format: B,G,R. */
            UserBuffer[index] = Rxbuffer[7];
            UserBuffer[index + 1u] = Rxbuffer[6];
            UserBuffer[index + 2u] = Rxbuffer[5];
        }
        break;

        case CONFIGURE_CHANNEL_MODE_4:
        {
            uint16_t index = RXBUFFER16(3);
            uint8_t frames = Rxbuffer[5];

            if (!ws2812AnimationBufferValid(index, frames))
            {
                error(SW_ERROR_WUB_INVALID_ADDRESS);
                return;
            }

            ws2812->animationLedsIndex = index;
            ws2812->animationFrames = frames;
            ws2812->currentAnimationFrame = 0;
            ws2812->delay = 0;
        }
        break;

        case CONFIGURE_CHANNEL_MODE_5:
        {
            uint32_t index;

            if (ws2812->animationFrames == 0u ||
                Rxbuffer[3] >= ws2812->animationFrames)
            {
                error(SW_ERROR_INVALID_PARAMETER_3);
                return;
            }

            if (!ws2812AnimationBufferValid(ws2812->animationLedsIndex,
                                             ws2812->animationFrames))
            {
                error(SW_ERROR_WUB_INVALID_ADDRESS);
                return;
            }

            index = (uint32_t)ws2812->animationLedsIndex +
                    (uint32_t)Rxbuffer[3] * ws2812AnimationFrameSize();

            UserBuffer[index] = Rxbuffer[4];
            UserBuffer[index + 1u] = Rxbuffer[5];
        }
        break;

        case CONFIGURE_CHANNEL_MODE_6:
        {
            if (Rxbuffer[3] > WS2812_MODE_BARGRAPH)
            {
                error(SW_ERROR_INVALID_PARAMETER_3);
                return;
            }

            ws2812->mode = Rxbuffer[3];
            ws2812->delay = 0;
            ws2812->refreshPending = 1;

            if (ws2812->mode == WS2812_MODE_BARGRAPH)
            {
                ws2812->bgSourcePin = Rxbuffer[4];
            }
            else if (ws2812->mode == WS2812_MODE_ANIMATION)
            {
                ws2812->currentAnimationFrame = 0;
            }
            else if (ws2812->mode == WS2812_MODE_CHASE)
            {
                ws2812->chaseLED = 0;
                ws2812->chaseColor = 0;
            }
        }
        break;

        case CONFIGURE_CHANNEL_MODE_7:
        {
            ws2812->bgMin = RXBUFFER16(3);
            ws2812->bgMax = RXBUFFER16(5);
            ws2812->delay = 0;
            ws2812->refreshPending = 1;
        }
        break;

        default:
        {
            error(SW_ERROR_INVALID_PIN_COMMAND);
        }
        break;
    }
}


/// \brief Update the CH32V006 WS2812 pin state machine from the 1 ms scheduler.
void updateWS2812(void)
{
    debugWS2812 = (ws2812_t*)CurrentPinRegister;

    ws2812ServiceDMAComplete();

    if (ws2812->dmaActive)
    {
        return;
    }

    if (ws2812->delay != 0u)
    {
        --ws2812->delay;
        if (ws2812->delay != 0u)
        {
            return;
        }
    }

    switch (ws2812->mode)
    {
        case WS2812_MODE_BUFFERED:
        {
            if (!ws2812->refreshPending)
            {
                return;
            }

            ws2812->delay = WS2812_DEFAULT_REFRESH_DELAY(ws2812->numOfLEDS);
        }
        break;

        case WS2812_MODE_ANIMATION:
        {
            if (ws2812->animationFrames == 0u)
            {
                return;
            }

            ws2812BuildAnimationFrame();
        }
        break;

        case WS2812_MODE_CHASE:
        {
            ws2812BuildChaseFrame();
            ws2812->delay = WS2812_CHASE_DELAY_MS;
        }
        break;

        case WS2812_MODE_BARGRAPH:
        {
            ws2812BuildBarGraphFrame();
            ws2812->delay = WS2812_DEFAULT_REFRESH_DELAY(ws2812->numOfLEDS);
        }
        break;

        default:
        {
            return;
        }
    }

    ws2812StartDMA();
}


/*
 * Optional release hook for protocol.c / ProcessSetPin().  Calling this
 * before another mode takes over WP2 cleanly disables the WS2812 DMA/SPI
 * backend and returns PD3 to a floating input.
 */
void ws2812ReleaseIfOwner(uint8_t pin)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    ws2812_t* owner;

    if (pin != WS2812_WOMBAT_PIN ||
        PinUpdateRegisters[pin].generic.mode != PIN_MODE_WS2812)
    {
        return;
    }

    owner = (ws2812_t*)&PinUpdateRegisters[pin];

    DMA_Cmd(WS2812_DMA_CHANNEL, DISABLE);
    DMA_ClearFlag(WS2812_DMA_GL_FLAG);
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE);
    SPI_Cmd(SPI1, DISABLE);

    GPIO_InitStructure.GPIO_Pin = WS2812_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    owner->dmaActive = 0;
}
