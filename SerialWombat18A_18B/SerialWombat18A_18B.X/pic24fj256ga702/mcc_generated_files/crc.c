
/**
  CRC Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    crc.c

  @Summary:
    This is the generated driver implementation file for the CRC 
    driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for driver APIs for CRC. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC24FJ256GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
*/
/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
   Section: Includes
 */

#include "crc.h"

/**
   Section: Enumerations
 */
/* CRC Calculation States

  @Summary
    The CRC calculation states.

  @Description
    This enumeration defines the CRC calculation states.  The user
    should not start a CRC calculation until the previous CRC calculation
    has completed.
*/
typedef enum
{
    CRC_STATE_CALCULATE,
    CRC_STATE_FLUSH,
    CRC_STATE_CLEANUP,
    CRC_STATE_DONE
}CRC_STATE;
/**
   Section: Structures
 */
/* CRC Calculation Object

  @Summary
    The CRC calculation object used to calculate the CRC of a buffer of data.

  @Description
    This CRC calculation object contains the data needed to properly perform a
    CRC calculation.
*/
typedef struct
{
    uint8_t dataWidth;
    uint8_t polyWidth;
    CRC_STATE state;
    bool program;
    uint32_t remainingSize;
    union
    {
        uint8_t *data8bit;
        uint16_t *data16bit;
        uint32_t *data32bit;
        void *data;
        uint32_t program;
    }ptr;
}CRC_OBJ;
/**
   Section: Private Data
 */
static CRC_OBJ crcObj;

/**
    Section: CRC Initializers
 */
/**
    void CRC_Initialize(void)
*/
void CRC_Initialize(void)
{

    // reset the module
    CRCCON1 = 0;
    CRCCON2 = 0;
    CRCXORH = 0;
    CRCXORL = 0;
    CRCWDATH = 0;
    CRCWDATL = 0;
    

    // initials the module - it will not be enabled until the end of the routine
    // LENDIAN Start with MSb; CRCISEL Interrupt on shift complete and results ready; CSIDL disabled; CRCGO CRC is turned off; CRCEN disabled; 
    CRCCON1 = 0x00;
    // PLEN 16; DWIDTH 1; 
    CRCCON2 = 0x0F;
    
    // enable module
    CRCCON1bits.CRCEN = 1;

    // some polynomial
    CRCXORL = 0x1021;
    CRCXORH = 0x00;
    
    // some seed
    CRCWDATL = 0x84CF;
    CRCWDATH = 0x00;

    // set module state
    crcObj.remainingSize = 0;
    crcObj.state = CRC_STATE_CALCULATE;

}
/**
    Section: Private CRC Driver Functions
 */
/**
    static bool CRC_ProgramTask(void)
*/
static bool CRC_ProgramTask(void)
{
    uint16_t size;
    uint16_t tempTbl;
    uint16_t lowWord;
    uint16_t highWord;

    size = 0xFFFF - (uint16_t)(crcObj.ptr.program & 0xFFFF);
    tempTbl = TBLPAG;

    CRCCON1bits.CRCGO = false;
    IFS4bits.CRCIF = false;

    TBLPAG = (uint16_t)(crcObj.ptr.program >> 16);

    while((!CRCCON1bits.CRCFUL) && (crcObj.remainingSize) && (size))
    {
        lowWord = __builtin_tblrdl((uint16_t)(crcObj.ptr.program & 0xFFFF));
        crcObj.ptr.program++;
        highWord  = __builtin_tblrdh((uint16_t)(crcObj.ptr.program & 0xFFFF));
        crcObj.ptr.program++;
        
        CRCDATL = lowWord;
        CRCDATH = highWord;

        crcObj.remainingSize -= 3;
        size -= 2;
    }

    TBLPAG = tempTbl;
    
    CRCCON1bits.CRCGO = true;
    
    if(crcObj.remainingSize == 0)
        return true;

    return false;
}
/**
    static bool CRC_BufferTask(void)
*/
static bool CRC_BufferTask(void)
{
    if(CRCCON1bits.CRCFUL)
        return false;

    IFS4bits.CRCIF = false;

    if(crcObj.dataWidth <= 8)
    {
        while((!CRCCON1bits.CRCFUL) && (crcObj.remainingSize))
        {
            *((uint8_t *)&CRCDATL) = *crcObj.ptr.data8bit++;
            crcObj.remainingSize--;

        }
    }else if(crcObj.dataWidth <= 16)
    {
        while((!CRCCON1bits.CRCFUL) && (crcObj.remainingSize))
        {
            CRCDATL = *crcObj.ptr.data16bit++;
            crcObj.remainingSize -= 2;

        }
    }else
    {
        while((!CRCCON1bits.CRCFUL) && (crcObj.remainingSize))
        {
            CRCDATL = *crcObj.ptr.data16bit++;
            CRCDATH = *crcObj.ptr.data16bit++;
            crcObj.remainingSize -= 4;
        }
    }

    CRCCON1bits.CRCGO = true;

    if(crcObj.remainingSize == 0)
        return true;

    return false;
}
/**
    static bool CRC_FlushTask(void)
*/
static bool CRC_FlushTask(void)
{
    if(IFS4bits.CRCIF)
    {

        CRCCON1bits.CRCGO = false;
        IFS4bits.CRCIF = false;

        CRCCON2bits.DWIDTH = crcObj.polyWidth - 1;
        
        if(crcObj.polyWidth <= 8)
        {
            *((uint8_t *)&CRCDATL) = 0;
        }else if(crcObj.polyWidth <= 16)
        {
            CRCDATL = 0;
        }else
        {
            CRCDATL = 0;
            CRCDATH = 0;
        }

        CRCCON1bits.CRCGO = true;
        
        return true;
    }

    return false;
}
/**
    static bool CRC_CleanUpTask(void)
*/
static bool CRC_CleanUpTask(void)
{
    if(IFS4bits.CRCIF)
    {

        CRCCON2bits.DWIDTH = crcObj.dataWidth - 1;
        CRCCON1bits.CRCGO = false;
        IFS4bits.CRCIF = false;

        return true;
    }
    
    return false;
}
/**
    static uint32_t CRC_ReverseValue(uint32_t crc)
*/
static uint32_t CRC_ReverseValue(uint32_t crc)
{
    uint32_t mask;
    uint32_t reverse;

    mask = 1;
    mask <<= (crcObj.polyWidth - 1);
    reverse = 0;

    while(crc)
    {
        if(crc & 0x01)
            reverse |= mask;

        mask >>= 1;
        crc >>= 1;
    }

    return reverse;

}
/**
    static uint32_t CRC_PolynomialMask(void)
*/
static uint32_t CRC_PolynomialMask(void)
{
    uint32_t mask = 0;
    uint32_t idx;

    for(idx = 0; idx < crcObj.polyWidth; idx++)
    {
        mask <<= 1;
        mask |= 1;
    }

    return mask;

}

/**
    Section: Public CRC Driver Functions
 */
/**
    void CRC_SeedSet(uint32_t seed, CRC_SEED_METHOD seedMethod, CRC_SEED_DIRECTION seedDirection)
*/
void CRC_SeedSet(uint32_t seed, CRC_SEED_METHOD seedMethod, CRC_SEED_DIRECTION seedDirection)
{
    uint8_t direction = CRCCON1bits.LENDIAN;
    uint8_t dataWidth = CRCCON2bits.DWIDTH;


    if(seedMethod == CRC_SEED_METHOD_INDIRECT)
    {
        CRCWDATL = (uint16_t)seed;
        CRCWDATH = (uint16_t)(seed >> 16);
    }else
    {

        CRCCON2bits.DWIDTH = CRCCON2bits.PLEN; 
        CRCCON1bits.LENDIAN = seedDirection;

        if(crcObj.polyWidth <= 8)
        {
            *((uint8_t *)&CRCDATL) = (uint8_t)seed;
        }else if(crcObj.polyWidth <= 16)
        {
            CRCDATL = (uint16_t)seed;
        }else
        {
            CRCDATL = (uint16_t)seed;
            CRCDATH = (uint16_t)(seed >> 16);
        }

        // Run the seed through the shift register
        IFS4bits.CRCIF = false;

        CRCCON1bits.CRCGO = true;
        while(IFS4bits.CRCIF == false)
            ;

        CRCCON1bits.CRCGO = false;

        CRCCON1bits.LENDIAN = direction;
        IFS4bits.CRCIF = false;
        CRCCON2bits.DWIDTH = dataWidth; 
    }
    

}
/**
    void CRC_CalculateBufferStart(void *buffer, uint32_t sizeBytes)
*/
void CRC_CalculateBufferStart(void *buffer, uint32_t sizeBytes)
{
    crcObj.dataWidth = CRCCON2bits.DWIDTH + 1;
    crcObj.polyWidth = CRCCON2bits.PLEN + 1;
    crcObj.remainingSize = sizeBytes;
    crcObj.ptr.data = buffer;
    crcObj.state = CRC_STATE_CALCULATE;
    crcObj.program = false;

    CRCCON1bits.CRCGO = true;

}

/**
    void CRC_CalculateProgramStart(uint32_t startAddr, uint32_t sizeBytes)
*/
void CRC_CalculateProgramStart(uint32_t startAddr, uint32_t sizeBytes)
{
    crcObj.dataWidth = CRCCON2bits.DWIDTH + 1;
    crcObj.polyWidth = CRCCON2bits.PLEN + 1;
    crcObj.remainingSize = sizeBytes;
    crcObj.ptr.program = startAddr;
    crcObj.state = CRC_STATE_CALCULATE;
    crcObj.program = true;
    
    CRCCON2bits.DWIDTH = 32 - 1;

    CRCCON1bits.CRCGO = true;

}

void __attribute__ ((weak)) CRC_CallBack(void)
{
    // Add your custom callback code here
}

/**
    void CRC_Task(void)
*/
void CRC_Task(void)
{
    switch(crcObj.state)
    {
        case CRC_STATE_CALCULATE:
            if(crcObj.program)
            {
                if(CRC_ProgramTask())
                    crcObj.state = CRC_STATE_FLUSH;
            }else
            {
                if(CRC_BufferTask())
                    crcObj.state = CRC_STATE_FLUSH;
            }    
            break;

        case CRC_STATE_FLUSH:
            if(CRC_FlushTask())
                crcObj.state = CRC_STATE_CLEANUP;
            break;

        case CRC_STATE_CLEANUP:
            if(CRC_CleanUpTask())
                crcObj.state = CRC_STATE_DONE;
            break;

        case CRC_STATE_DONE:
            break;
        
        default:
            CRCCON1 = 0;
            CRCCON2 = 0;
            break;
    }
	
	if(IFS4bits.CRCIF)
	{
		// CRC callback function 
		CRC_CallBack();
	}
}
/**
    bool CRC_CalculationIsDone(void)
*/
bool CRC_CalculationIsDone(void)
{
    return crcObj.state == CRC_STATE_DONE;
}

/**
    uint32_t CRC_CalculationResultRawGet(void)
*/
uint32_t CRC_CalculationResultRawGet(void)
{
    uint32_t result;

    if(crcObj.polyWidth <= 8)
    {
        result = (uint32_t)CRCWDATL & 0xFF;
    }else if(crcObj.polyWidth <= 16)
    {
        result = (uint32_t)CRCWDATL;
    }else
    {
        result = (uint32_t)CRCWDATH;
        result <<= 16;
        result |= (uint32_t)CRCWDATL;
    }
    
    return result;
}
/**
    uint32_t CRC_CalculationResultReverseGet(void)
*/
uint32_t CRC_CalculationResultReverseGet(void)
{
    uint32_t result;

    result = CRC_CalculationResultRawGet();

    return CRC_ReverseValue(result);
}
/**
    uint32_t CRC_CalculationResultXORGet(uint32_t xorValue)
*/
uint32_t CRC_CalculationResultXORGet(uint32_t xorValue)
{
    uint32_t result;

    result = CRC_CalculationResultRawGet();

    result ^= xorValue;

    return result & CRC_PolynomialMask();
}
/**
    uint32_t CRC_CalculationResultGet(bool reverse, uint32_t xorValue)
*/
uint32_t CRC_CalculationResultGet(bool reverse, uint32_t xorValue)
{
    uint32_t result;

    result = CRC_CalculationResultRawGet();

    if(reverse)
        result = CRC_CalculationResultReverseGet();
    else
        result = CRC_CalculationResultRawGet();

    result ^= xorValue;

    return result & CRC_PolynomialMask();
}