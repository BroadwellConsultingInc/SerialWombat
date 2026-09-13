/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH / Broadwell Consulting
 * Version            : V1.0.0
 * Date               : 2026/09/04
 * Description        : Serial Wombat 8B CH32V006 bootloader.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include <ch32v00X.h>
#include "ch32v00X_flash.h"
#include "ch32v00X_gpio.h"
#include "ch32v00X_i2c.h"
#include "ch32v00X_rcc.h"
#include "serialWombat.h"
#include <string.h>

/*
 * Set these to 1 to compile the corresponding CH32V003-era implementation
 * for examination.  They are intentionally retained during the V006 port
 * and can be removed after the port is validated.
 */
#define KEEP_CH32V003_FLASH_IMPLEMENTATION       0
#define KEEP_CH32V003_MASS_ERASE_CODE            0
#define KEEP_CH32V003_IMAGE_MAGIC_CHECK          0
#define KEEP_CH32V003_RCC_REGISTER_NAMES         0
#define KEEP_CH32V003_I2C_GPIO_CONFIGURATION     0
#define KEEP_CH32V003_USER_BUFFER_DECLARATION    0
#define KEEP_UNUSED_V003_GPIO_INIT_SMALL          0

/* -------------------------------------------------------------------------
 * CH32V006 flash layout used by the Serial Wombat bootloader
 * -------------------------------------------------------------------------
 * Application image:       0x08000000 - 0x0800EBFF  (59 KiB)
 * Application valid word:  0x0800EBFC                  4 bytes
 * Startup configuration:   0x0800EC00 - 0x0800EFFF   (1 KiB)
 * Reserved above this:     0x0800F000 and above
 *
 * The image-valid word is deliberately located in the final word of the
 * application area.  The 1 KiB erase sector containing it is erased FIRST
 * when a bootload operation starts so a partially downloaded image cannot
 * subsequently be mistaken for a valid application.
 */
#define APPLICATION_FLASH_START              0x08000000UL
#define APPLICATION_FLASH_END                0x0800EC00UL /* exclusive */
#define APPLICATION_IMAGE_MAGIC_ADDRESS      0x0800EBFCUL
#define APPLICATION_IMAGE_MAGIC_VALUE        0x20260904UL

#define STARTUP_CONFIG_FLASH_START           0x0800EC00UL
#define STARTUP_CONFIG_FLASH_END             0x0800F000UL /* exclusive */

/* Standard erase size on CH32V006. */
#define FLASH_ERASE_SECTOR_SIZE              0x00000400UL /* 1 KiB */

/* Fast programming buffer/page size on CH32V006. */
#define FLASH_PROGRAM_LINE_SIZE              0x00000100UL /* 256 B */
#define FLASH_PROGRAM_WORDS_PER_LINE         (FLASH_PROGRAM_LINE_SIZE / sizeof(uint32_t))

#define APPLICATION_MAGIC_SECTOR_START       \
    (APPLICATION_IMAGE_MAGIC_ADDRESS & ~(FLASH_ERASE_SECTOR_SIZE - 1u))

#if (APPLICATION_FLASH_END != STARTUP_CONFIG_FLASH_START)
#error Application and startup configuration regions must be contiguous.
#endif

#if ((APPLICATION_IMAGE_MAGIC_ADDRESS + 4u) != APPLICATION_FLASH_END)
#error Application magic value must occupy the final 4 bytes of the application region.
#endif

#if ((STARTUP_CONFIG_FLASH_END - STARTUP_CONFIG_FLASH_START) != FLASH_ERASE_SECTOR_SIZE)
#error Startup configuration region must be exactly one 1 KiB erase sector.
#endif

/* Unused global retained from the V003 source for examination. */
#define KEEP_UNUSED_V003_GLOBALS 0
#if KEEP_UNUSED_V003_GLOBALS
vu8 val;
#endif

/* FLASH keys retained only for the old register-level V003 implementation. */
#if KEEP_CH32V003_FLASH_IMPLEMENTATION
#define RDP_Key                    ((uint16_t)0x00A5)
#define FLASH_KEY1                 ((uint32_t)0x45670123)
#define FLASH_KEY2                 ((uint32_t)0xCDEF89AB)

#define CR_PAGE_PG                 ((uint32_t)0x00010000)
#define CR_PAGE_ER                 ((uint32_t)0x00020000)
#define CR_BUF_LOAD                ((uint32_t)0x00040000)
#define CR_BUF_RST                 ((uint32_t)0x00080000)
#define CR_STRT_Set                ((uint32_t)0x00000040)
#define SR_BSY                     ((uint32_t)0x00000001)
#define EraseTimeout               ((uint32_t)0x000B0000)
#define CR_MER_Set                 ((uint32_t)0x00000004)
#define CR_MER_Reset               ((uint32_t)0xFFFFFFFB)

static void flashWait(void)
{
    while(FLASH->STATR & SR_BSY)
        ;
    FLASH->CTLR &= ~CR_PAGE_PG;
}

/*
 * Original CH32V003 64-byte fast programming routine.
 * Retained for comparison only.
 */
static void FProgram_CH32V003(u32 adr, u32 *buf)
{
    adr &= 0xFFFFFFC0u;

    /* FLASH_BufReset_Small(); */
    FLASH->CTLR |= CR_PAGE_PG;
    FLASH->CTLR |= CR_BUF_RST;
    flashWait();

    for(int j = 0; j < 16; ++j)
    {
        /* FLASH_BufLoad(adr + 4*j, buf[j]); */
        FLASH->CTLR |= CR_PAGE_PG;
        *(__IO uint32_t *)(adr + 4u * (uint32_t)j) = buf[j];
        FLASH->CTLR |= CR_BUF_LOAD;
        flashWait();
    }

    /* FLASH_ProgramPage_Fast(adr); */
    FLASH->CTLR |= CR_PAGE_PG;
    FLASH->ADDR = adr;
    FLASH->CTLR |= CR_STRT_Set;
    flashWait();
}
#endif

/* I2C register masks that remain valid for the current register-level setup. */
#define CTLR2_FREQ_Reset         ((uint16_t)0xFFC0)
#define CTLR1_PE_Reset           ((uint16_t)0xFFFE)
#define CTLR1_CLEAR_Mask         ((uint16_t)0xFBF5)
#define CTLR1_PE_Set             ((uint16_t)0x0001)

/* These were present in the V003 source but are unused. */
#define KEEP_UNUSED_V003_I2C_MASKS 0
#if KEEP_UNUSED_V003_I2C_MASKS
#define CKCFGR_CCR_Set           ((uint16_t)0x0FFF)
#define CKCFGR_FS_Set            ((uint16_t)0x8000)
#endif

static uint8_t ApplicationImagePresent(void)
{
    return (*(volatile const uint32_t *)APPLICATION_IMAGE_MAGIC_ADDRESS ==
            APPLICATION_IMAGE_MAGIC_VALUE);
}

/*
 * Erase the complete application region plus the 1 KiB startup-command area.
 *
 * Ordering is intentional:
 *   1. Erase 0x0800E800-0x0800EBFF FIRST.  This destroys the image-valid
 *      word at 0x0800EBFC immediately.
 *   2. Erase 0x0800EC00-0x0800EFFF SECOND.  This clears all startup commands.
 *   3. Erase the remaining application sectors from low address upward.
 *
 * FLASH_Unlock_Fast() performs both the normal FLASH unlock and the fast-mode
 * unlock, allowing the standard 1 KiB erase API and later 256-byte fast
 * programming API to be used.
 */
static uint8_t EraseApplicationAndStartupConfiguration(void)
{
    FLASH_Status status;
    uint32_t address;

    FLASH_Unlock_Fast();

    /* FIRST erase: invalidate any existing application image. */
    status = FLASH_ErasePage(APPLICATION_MAGIC_SECTOR_START);
    if(status != FLASH_COMPLETE)
    {
        FLASH_Lock_Fast();
        return 0u;
    }

    /* SECOND erase: remove all stored startup configuration commands. */
    status = FLASH_ErasePage(STARTUP_CONFIG_FLASH_START);
    if(status != FLASH_COMPLETE)
    {
        FLASH_Lock_Fast();
        return 0u;
    }

    /* Erase every remaining 1 KiB application sector. */
    for(address = APPLICATION_FLASH_START;
        address < APPLICATION_MAGIC_SECTOR_START;
        address += FLASH_ERASE_SECTOR_SIZE)
    {
        status = FLASH_ErasePage(address);
        if(status != FLASH_COMPLETE)
        {
            FLASH_Lock_Fast();
            return 0u;
        }
    }

    FLASH_Lock_Fast();
    return 1u;
}

/*
 * Program exactly one CH32V006 fast-programming line (256 bytes).
 * The address must be 256-byte aligned and entirely inside the application
 * region.  The host image contains the application-valid word in the final
 * line at address 0x0800EB00, so the magic word is not restored until that
 * line is successfully programmed.
 */
static uint8_t FProgram(uint32_t address, const uint32_t *buffer)
{
    uint32_t j;

    if((address & (FLASH_PROGRAM_LINE_SIZE - 1u)) != 0u)
    {
        return 0u;
    }

    if(address < APPLICATION_FLASH_START ||
       address > (APPLICATION_FLASH_END - FLASH_PROGRAM_LINE_SIZE))
    {
        return 0u;
    }

    FLASH_Unlock_Fast();

    FLASH_BufReset();

    for(j = 0; j < FLASH_PROGRAM_WORDS_PER_LINE; ++j)
    {
        FLASH_BufLoad(address + (j * sizeof(uint32_t)), buffer[j]);
    }

    FLASH_ProgramPage_Fast(address);
    FLASH_Lock_Fast();

    /* Verify the complete programmed line before reporting success. */
    for(j = 0; j < FLASH_PROGRAM_WORDS_PER_LINE; ++j)
    {
        if(*(volatile const uint32_t *)(address + (j * sizeof(uint32_t))) != buffer[j])
        {
            return 0u;
        }
    }

    return 1u;
}

/*
 * Return the number of consecutive erased 32-bit words (0xFFFFFFFF)
 * beginning at address.
 *
 * Used by COMMAND_BINARY_WRITE_FLASH subcommand 5 to accelerate host-side
 * verification of sparse/blank portions of the application image.
 *
 * The scan is restricted to the application region.  A non-word-aligned or
 * out-of-range address returns zero.  The complete 59 KiB application
 * contains only 15104 words, so a uint16_t count is sufficient.
 */
static uint16_t CountConsecutiveErasedWords(uint32_t address)
{
    uint32_t wordsRemaining;
    uint16_t count = 0;
    volatile const uint32_t *flashWord;

    if((address & (sizeof(uint32_t) - 1u)) != 0u)
    {
        return 0u;
    }

    if(address < APPLICATION_FLASH_START || address >= APPLICATION_FLASH_END)
    {
        return 0u;
    }

    wordsRemaining = (APPLICATION_FLASH_END - address) / sizeof(uint32_t);
    flashWord = (volatile const uint32_t *)address;

    while((uint32_t)count < wordsRemaining && flashWord[count] == 0xFFFFFFFFu)
    {
        ++count;
    }

    return count;
}

uint16_t i2cAddress;

#if KEEP_UNUSED_V003_GPIO_INIT_SMALL
static void GPIO_Init_Small(GPIO_InitTypeDef *GPIO_InitStruct)
{
    uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    uint32_t tmpreg = 0x00, pinmask = 0x00;

    currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);

    if((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
    {
        currentmode |= GPIO_Speed_30MHz;
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
}
#endif

static void determineAddress(void)
{
    i2cAddress = (uint8_t)0x60;

    if((GPIOC->INDR & GPIO_Pin_0) == 0)
    {
        i2cAddress += 1;
    }
    if((GPIOC->INDR & GPIO_Pin_5) == 0)
    {
        i2cAddress += 2;
    }
    if((GPIOC->INDR & GPIO_Pin_6) == 0)
    {
        i2cAddress += 4;
    }
    if((GPIOC->INDR & GPIO_Pin_7) == 0)
    {
        i2cAddress += 8;
    }
}

uint16_t lastUserBufferIndex = 0;

#if KEEP_CH32V003_USER_BUFFER_DECLARATION
/* Original V003 declaration; typically sized for a 64-byte fast-program line. */
uint8_t UserBuffer[SIZE_OF_USER_BUFFER];
#else
/*
 * CH32V006 fast programming requires a complete 256-byte line.  Explicit
 * 4-byte alignment makes the uint32_t access in FProgram() well defined.
 */
uint8_t UserBuffer[SIZE_OF_USER_BUFFER] __attribute__((aligned(4)));
#endif

static void I2C_InitSmall(void)
{
#if KEEP_CH32V003_RCC_REGISTER_NAMES
    /* Original CH32V003 peripheral clock register/name. */
    RCC->APB1PCENR = RCC_APB1Periph_I2C1;
#else
    /* CH32V006 names this bus/register PB1 rather than APB1. */
    RCC->PB1PCENR |= RCC_PB1Periph_I2C1;
#endif

#if KEEP_CH32V003_I2C_GPIO_CONFIGURATION
    /* Original CH32V003 SDA/SCL register expression. */
    {
        uint32_t tmpreg;
        tmpreg = GPIOC->CFGLR;
        tmpreg &= ~0x0FF0;
        tmpreg |= ((0x1C | GPIO_Speed_30MHz) << 4) |
                  ((0x1C | GPIO_Speed_30MHz) << 8);
        GPIOC->CFGLR = tmpreg;
    }
#else
    /*
     * CH32V006 I2C1 default pins:
     *   PC1 = SDA
     *   PC2 = SCL
     * Configure both AF open-drain at 30 MHz.  Each CFGLR nibble is 0xD.
     */
    {
        uint32_t tmpreg = GPIOC->CFGLR;
        tmpreg &= ~((0x0Fu << 4) | (0x0Fu << 8));
        tmpreg |=  ((0x0Du << 4) | (0x0Du << 8));
        GPIOC->CFGLR = tmpreg;
    }
#endif

    /* Set up I2C peripheral clock frequency field. */
    {
        uint16_t tmpreg = I2C1->CTLR2;
        tmpreg &= CTLR2_FREQ_Reset;
        tmpreg |= 48;
        I2C1->CTLR2 = tmpreg;
    }

    I2C1->CTLR1 &= CTLR1_PE_Reset;

    /* Retained from the V003 slave implementation. */
    I2C1->CKCFGR = 50;
    I2C1->CTLR1 |= CTLR1_PE_Set;

    {
        uint16_t tmpreg = I2C1->CTLR1;
        tmpreg &= CTLR1_CLEAR_Mask;
        tmpreg |= (uint16_t)((uint32_t)I2C_Mode_I2C | I2C_Ack_Enable);
        I2C1->CTLR1 = tmpreg;
    }

    /* Serial Wombat requires clock stretching; NOSTRETCH bit must be clear. */
    I2C1->CTLR1 &= ~(1u << 7);

    I2C1->OADDR1 = (I2C_AcknowledgedAddress_7bit | (i2cAddress * 2u));
    I2C1->CTLR1 |= CTLR1_PE_Set;
}

#if KEEP_CH32V003_FLASH_IMPLEMENTATION
/* Original local V003 FLASH status/wait helpers, no longer needed with library. */
static FLASH_Status FLASH_GetBank1StatusLocal(void)
{
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if((FLASH->STATR & FLASH_FLAG_BANK1_BSY) == FLASH_FLAG_BSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        flashstatus = FLASH_COMPLETE;
    }
    return flashstatus;
}

static FLASH_Status FLASH_WaitForLastOperationLocal(void)
{
    while(FLASH_GetBank1StatusLocal() == FLASH_BUSY)
        ;

    return FLASH_COMPLETE;
}
#endif

u8 Rxbuffer[8];
u8 Txbuffer[8];

#define error(_errorcode) { Txbuffer[0] = 'E'; }

static void processRx(void)
{
    memcpy(Txbuffer, Rxbuffer, 8);

    switch(Rxbuffer[0])
    {
        case 'R':
        {
#if KEEP_CH32V003_IMAGE_MAGIC_CHECK
            if((*(uint32_t *)(0x08003FFCu) == 0x20250111u))
            {
                NVIC_SystemReset();
            }
#else
            /* Only leave the bootloader if the V006 application image is valid. */
            if(ApplicationImagePresent())
            {
                NVIC_SystemReset();
            }
#endif
        }
        break;

        case 'V':
        {
            ((uint32_t *)Txbuffer)[0] = 0x38304256; /* VB08 */
            ((uint32_t *)Txbuffer)[1] = 0x34303243; /* C204 */
        }
        break;

        case COMMAND_BINARY_WRITE_USER_BUFFER:
        {
            uint16_t count;
            uint16_t available;

            lastUserBufferIndex = RXBUFFER16(1);
            count = Rxbuffer[3];

            if(lastUserBufferIndex >= FLASH_PROGRAM_LINE_SIZE)
            {
                error(1);
                break;
            }

            available = (uint16_t)(FLASH_PROGRAM_LINE_SIZE - lastUserBufferIndex);
            if(count > available)
            {
                count = available;
            }

            /* Only four payload bytes exist in this first 8-byte packet. */
            if(count > 4u)
            {
                count = 4u;
            }

            memcpy(&UserBuffer[lastUserBufferIndex], &Rxbuffer[4], count);
            lastUserBufferIndex += count;
        }
        break;

        case COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE:
        {
            if(lastUserBufferIndex < FLASH_PROGRAM_LINE_SIZE)
            {
                uint16_t count = (uint16_t)(FLASH_PROGRAM_LINE_SIZE - lastUserBufferIndex);

                if(count > 7u)
                {
                    count = 7u;
                }

                memcpy(&UserBuffer[lastUserBufferIndex], &Rxbuffer[1], count);
                lastUserBufferIndex += count;
            }
        }
        break;

        case COMMAND_BINARY_READ_FLASH:
        {
            uint32_t address;
            memcpy(&address, &Rxbuffer[1], 4);
            ((uint32_t *)Txbuffer)[1] = *((uint32_t *)address);
        }
        break;

        case COMMAND_BINARY_WRITE_FLASH:
        {
            switch(Rxbuffer[1])
            {
                case 0:
                {
#if KEEP_CH32V003_MASS_ERASE_CODE && KEEP_CH32V003_FLASH_IMPLEMENTATION
                    /*
                     * Original V003 implementation: unlock fast mode and issue
                     * a whole-user-flash mass erase.  Retained for comparison.
                     */
                    FLASH->KEYR = FLASH_KEY1;
                    FLASH->KEYR = FLASH_KEY2;
                    FLASH->MODEKEYR = FLASH_KEY1;
                    FLASH->MODEKEYR = FLASH_KEY2;

                    FLASH_WaitForLastOperationLocal();
                    FLASH->CTLR |= CR_MER_Set;
                    FLASH->CTLR |= CR_STRT_Set;
                    FLASH_WaitForLastOperationLocal();
                    FLASH->CTLR &= CR_MER_Reset;
#else
                    /*
                     * CH32V006 bootload erase operation.
                     * The magic-containing sector is the FIRST flash erase.
                     */
                    if(!EraseApplicationAndStartupConfiguration())
                    {
                        error(2);
                    }
#endif
                }
                break;

                case 1:
                {
                    uint32_t address;
                    memcpy(&address, &Rxbuffer[2], 4);

                    if(!FProgram(address, (const uint32_t *)UserBuffer))
                    {
                        error(3);
                    }
                }
                break;

                case 4:
                {
                    RCC_ClearFlag();
                    SystemReset_StartMode(Start_Mode_USER);
                }
                break;

                case 5:
                {
                    /*
                     * Accelerated erased-flash verification.
                     *
                     * Request:
                     *   Byte 0: COMMAND_BINARY_WRITE_FLASH (0xA4)
                     *   Byte 1: 5
                     *   Byte 2-5: starting flash address, little endian
                     *   Byte 6-7: 0x00, 0x00
                     *
                     * Response:
                     *   Byte 0: COMMAND_BINARY_WRITE_FLASH (0xA4)
                     *   Byte 1: 0x85 (supported-response marker for subcommand 5)
                     *   Byte 2-5: requested starting address echoed
                     *   Byte 6-7: number of consecutive 0xFFFFFFFF
                     *             32-bit words, little endian
                     *
                     * The count stops at the first non-erased word or at
                     * APPLICATION_FLASH_END.
                     */
                    uint32_t address;
                    uint16_t erasedWordCount;

                    memcpy(&address, &Rxbuffer[2], sizeof(address));
                    erasedWordCount = CountConsecutiveErasedWords(address);

                    /*
                     * Change byte 1 from 0x05 to 0x85 so a new host can tell
                     * this response from an older bootloader that merely echoed
                     * an unsupported subcommand-5 request.
                     */
                    Txbuffer[1] = 0x85u;
                    Txbuffer[6] = (uint8_t)(erasedWordCount & 0xFFu);
                    Txbuffer[7] = (uint8_t)(erasedWordCount >> 8);
                }
                break;
            }
        }
        break;
    }
}

uint16_t __attribute__((section(".stayinboot"))) stayInBoot;

uint32_t txCount = 0;
uint16_t rxCount = 0;
uint16_t i2cMode = 0;

static void delayX(void)
{
    volatile uint16_t x;
    for(x = 0; x < 60000; ++x)
        ;
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
#if KEEP_CH32V003_RCC_REGISTER_NAMES
    /* Original CH32V003 peripheral clock names. */
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO;
#else
    /* CH32V006 PB2 peripheral clock register/names. */
    RCC->PB2PCENR |= RCC_PB2Periph_GPIOC | RCC_PB2Periph_AFIO;
#endif

    delayX();

    /* Retain original GPIOC boot/address strap configuration. */
    GPIOC->CFGLR = 0x88848448;
    GPIOC->BSHR = GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

    delayX();

    /*
     * Jump/reset toward the user application only when:
     *   - software did not explicitly request staying in bootloader,
     *   - the image-valid word is present at 0x0800EBFC, and
     *   - the boot/recovery pin PC3 is not held low.
     */
#if KEEP_CH32V003_IMAGE_MAGIC_CHECK
    if(stayInBoot != 0xB00A &&
       (*(uint32_t *)(0x08003FFCu) == 0x20250111u) &&
       (GPIOC->INDR & GPIO_Pin_3))
    {
        NVIC_SystemReset();
    }
#else
    if(stayInBoot != 0xB00A &&
       ApplicationImagePresent() &&
       (GPIOC->INDR & GPIO_Pin_3))
    {
        NVIC_SystemReset();
    }
#endif

    /* Preserve the existing option-byte based I2C address override behavior. */
    i2cAddress = *(uint8_t *)0x1FFFF804u;
    if(i2cAddress == 0xFFu)
    {
        determineAddress();
    }

    I2C_InitSmall();

    while(1)
    {
        if(I2C1->STAR1 & 0x02) /* Address bit set */
        {
            uint16_t tra = I2C1->STAR2 & 0x04; /* Reading STAR1 then STAR2 clears ADDR. */
            rxCount = 0;
            txCount = 0;

            if(tra == 0)
            {
                i2cMode = 1;
            }
            else
            {
                i2cMode = 2;
                I2C1->DATAR = Rxbuffer[txCount];
                ++txCount;
            }
        }

        if(i2cMode == 1 && (I2C1->STAR1 & 0x040)) /* RxNE */
        {
            Rxbuffer[rxCount] = I2C1->DATAR;
            ++rxCount;

            if(rxCount == 8)
            {
                processRx();
                rxCount = 0;
                txCount = 0;
            }
        }

        if(i2cMode == 2 && (I2C1->STAR1 & 0x80)) /* TxE */
        {
            I2C1->DATAR = Txbuffer[txCount];
            ++txCount;
        }
    }
}
