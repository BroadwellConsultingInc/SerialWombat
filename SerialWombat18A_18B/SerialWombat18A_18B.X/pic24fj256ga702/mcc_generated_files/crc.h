/**
  CRC Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    crc.h

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

#ifndef _CRC_H
#define _CRC_H

/**
    Section: Includes
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
    Section: Enumerations
*/

/**
  @Summary
    The seed method that is used, direct or indirect

  @Description
    The seed method that is used, direct or indirect.  The direct method
    refers to the seed being placed before the shifters with the result being
    shifted through the polynomial.  The indirect method refers to the seed being
    placed after the shifters with the result not being shifted through the polynomial.
    
  @Example
    With a polynomial CRC-16-CCITT (0x1021) and a seed/initial value of 0xFFFF
    Direct - the result of 0xFFFF shifted, 0x84CF, will be in the CRC result register
    Indirect - the value of 0xFFFF will be placed in the CRC result register
*/
typedef enum
{
    CRC_SEED_METHOD_DIRECT,
    CRC_SEED_METHOD_INDIRECT
}CRC_SEED_METHOD;
/**
  @Summary
    The seed shift direction that is used in the direct method

  @Description
    The seed shift direction that is used in the direct method.  The seed will be 
    shift direction is independent of the data direction.  This setting is only used
    when the seed method is direct.
*/
typedef enum
{
    CRC_SEED_DIRECTION_Msb,
    CRC_SEED_DIRECTION_Lsb,
}CRC_SEED_DIRECTION;


// Provide C++ Compatibility
#ifdef __cplusplus  

extern "C" {

#endif

/**
  @Summary
    Initializes the CRC module

  @Description
    This routine sets the polynomial and data width; data and seed shift;
    updates the polynomial and shifts the seed value.

    After the routine is called, the CRC module is ready to calculate the
    CRC of a data buffer.
 

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // Initialize the CRC module
    CRC_Initialize();
    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // perform the CRC task
        CRC_Task();
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
void CRC_Initialize(void);
/**
  @Summary
    Sets the CRC seed

  @Description
    This routine sets the CRC seed with the data direction of the current seed direction.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

  @Returns
    None.

  @Param
    seed - the seed value of the CRC calculation.
    method - if the seed method is direct or indirect
    direction - if the seed method is direct, the direction that the seed is shifted

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;
    
    // CRC module has been initialized 

    // Set the seed as 0xFFFF, the method as direct and direction Msb
    CRC_SeedSet(0xFFFF, CRC_SEED_METHOD_DIRECT, CRC_SEED_DIRECTION_Msb);
    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
void CRC_SeedSet(uint32_t seed, CRC_SEED_METHOD seedMethod, CRC_SEED_DIRECTION seedDirection);
/**
  @Summary
    Starts the CRC calculation

  @Description
    This routine starts the CRC calculation on a buffer in data space.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

  @Returns
    None.

  @Param
    buffer - a pointer to the desired data, in data space, to have the CRC calculation.
    It is the caller's duty to ensure that the data starts on the proper 
    boundary.

  @Param
    sizeBytes - the size, in bytes, of the buffer

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
void CRC_CalculateBufferStart(void *buffer, uint32_t sizeBytes);
/**
  @Summary
    Starts the CRC calculation

  @Description
    This routine starts the CRC calculation on a buffer in program space.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

  @Returns
    None.

  @Param
    startAddr - the starting address, in program space.  Each program instruction is 3 bytes, the
    caller should account for that in the size.

  @Param
    sizeBytes - the size, in bytes, of the program size.  It is a multiple of 3.

  @Example
    <code>
    uint32_t bufferCRC;
    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateProgramStart(APP_PROGRAM_START_ADDR, APP_PROGRAM_SIZE);
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
void CRC_CalculateProgramStart(uint32_t startAddr, uint32_t sizeBytes);

/**
  @Summary
    Callback for CRC.

  @Description
    This routine is callback for CRC

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to CRC_Initialize(); for an example
*/
void CRC_CallBack(void);

/**
  @Summary
    performs the CRC calculation

  @Description
    This routine cycles through the CRC calculations.  This routine will load the
    CRC module FIFO with the buffer data.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

    The caller needs to call the routine to start the calculation.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
void CRC_Task(void);
/**
  @Summary
    Checks to see if the CRC calculation has completed.

  @Description
    This routine is used to determine if the CRC calculation has been completed. 
    Only after the CRC calculation has been completed should the caller get the
    CRC result.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

  @Returns
    true if the CRC calculation has completed and the result is ready to retrieve,
    else false.

  @Param
    None.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
bool CRC_CalculationIsDone(void);
/**
  @Summary
    Gets the CRC result.

  @Description
    This routine returns the CRC result from the module.  If this routine is called
    before the routine, CRC_CalculationIsDone, has 
    returned true, the result will be incorrect.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

    The routine, CRC_CalculationIsDone, has
    returned true.

  @Returns
    The CRC result for the module, reversed and XOR'd if desired.

  @Param
    reverse - if the CRC result from the module is bit reversed
    
  @Param
    xorValue - a value that will be XOR'd with the CRC result, after reversed if desired.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0
    bufferCRC = CRC_CalculationResultGet(false, 0);
    </code>

*/
uint32_t CRC_CalculationResultGet(bool reverse, uint32_t xorValue);
/**
  @Summary
    Gets the CRC result.

  @Description
    This routine returns the CRC result from the module.  If this routine is called
    before the routine, CRC_CalculationIsDone, has 
    returned true, the result will be incorrect.  This routine will not preform any modification
    to the result read from the CRC SFR.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

    The routine, CRC_CalculationIsDone, has
    returned true.

  @Returns
    The CRC result for the module.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value
    bufferCRC = CRC_CalculationResultRawGet();
    </code>

*/
uint32_t CRC_CalculationResultRawGet(void);
/**
  @Summary
    Gets the CRC result.

  @Description
    This routine returns the CRC result from the module.  If this routine is called
    before the routine, CRC_CalculationIsDone, has 
    returned true, the result will be incorrect.  This routine will reverse the bits, MSb to MSb,
    to the result read from the CRC SFR.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

    The routine, CRC_CalculationIsDone, has
    returned true.

  @Returns
    The CRC result for the module.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: reverse
    bufferCRC = CRC_CalculationResultReverseGet();
    </code>

*/
uint32_t CRC_CalculationResultReverseGet(void);
/**
  @Summary
    Gets the CRC result.

  @Description
    This routine returns the CRC result from the module.  If this routine is called
    before the routine, CRC_CalculationIsDone, has 
    returned true, the result will be incorrect.  This routine will XOR the passed value with the
    CRC result from the CRC SFR.

  @Preconditions
    The CRC module needs to be initialized with the desired settings.  Please
    refer to the CRC initialization routines.

    The routine, CRC_CalculationIsDone, has
    returned true.

  @Returns
    The CRC result for the module, reversed and XOR'd if desired.

  @Param
    xorValue - a value that will be XOR'd with the CRC result, after reversed if desired.

  @Example
    <code>
    uint8_t buffer [] = "Hello";
    uint32_t bufferCRC;

    // CRC module has been initialized 

    // Start the CRC
    CRC_CalculateBufferStart(buffer, sizeof(buffer));
    // wait until done
    while(CRC_CalculationIsDone() == false)
    {
        // Let the interrupt complete the calculation
    }
    // get the CRC value: do not reverse and XOR = 0xFFFF
    bufferCRC = CRC_CalculationResultGet(0xFFFF);
    </code>

*/
uint32_t CRC_CalculationResultXORGet(uint32_t xorValue);

// Provide C++ Compatibility
#ifdef __cplusplus  

}

#endif
#endif