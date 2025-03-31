/*
Copyright 2021-2023 Broadwell Consulting Inc.

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
#ifndef PIN_DIGITAL_HW_SPECIFIC_H
#define PIN_DIGITAL_HW_SPECIFIC_H
#include <stdint.h>
#include "deviceSpecific.h"

#ifdef __XC16_VERSION__ 
#define PIC24
#endif
#define SIZE_OF_DMA_ARRAY 128

#define OUTPUT_ARRAY_A_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT0) 
#define OUTPUT_ARRAY_B_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT1) 
#define INPUT_ARRAY_A_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT2) 
#define INPUT_ARRAY_B_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT3) 


#ifdef PIC24
extern uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t OutputArrayB[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayB[SIZE_OF_DMA_ARRAY];
#else
extern uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY];
extern volatile uint8_t InputArrayA[SIZE_OF_DMA_ARRAY];
#endif

extern const uint8_t WombatPinToADCChannel[NUMBER_OF_PHYSICAL_PINS];
extern const uint8_t pinPPSInputMap[NUMBER_OF_PHYSICAL_PINS];


#define NOTDMAONLY

typedef void (*timingResourceCallback_t) (void);
typedef struct
{
    timingResourceCallback_t callBack;
    uint32_t period_uS;
    uint16_t highTime_uS;
    uint16_t lowTime_uS;
    uint16_t pwmDutyCycle;
    uint8_t resourceHolder;    
}timingResourceManager_t;

typedef struct DMABitStream_n{
uint8_t nextLocationToQueue;
uint8_t initialize;
}DMABitStream_t;
/// Structure containing data for generalized pulse output
/// Include in pin mode structure
typedef struct pulse_output_n
    {
    DMABitStream_t bitStream;
    uint16_t highRemaining;
    uint16_t lowRemaining;
    uint16_t highReload;
    uint16_t lowReload;
    uint8_t resource;
    } pulse_output_t;

    
#define DIGITAL_LOW 0
#define DIGITAL_HIGH 1
#define DIGITAL_INPUT 2
void PinInput(uint8_t pin);
void PinOutput(uint8_t pin);
void PinHigh(uint8_t pin);
void PinLow(uint8_t pin);
void SetPin(uint8_t pin, uint8_t pinState); 
void InitializePinLow(uint8_t pin);
void InitializePinHigh(uint8_t pin);
void InitializePinInput(uint8_t pin);

void SetPinPullUp(uint8_t pin, bool isPulledUp);
void SetPinPullDown(uint8_t pin, bool isPulledDown);
void PinPullUp(uint8_t pin);
void PinNoPullUp(uint8_t pin);
void PinPullDown(uint8_t pin);
void PinNoPullDown(uint8_t pin);

void SetPinOD(uint8_t pin, bool isOpenDrain);
void PinOD(uint8_t pin);
void PinNoOD(uint8_t pin);

extern const uint16_t pinBitmap[];
extern const uint8_t pinPort[];
#define RESOURCE_AVAILABLE 0xFF
#define RESOURCE_USED_BY_SYSTEM 0xFE
extern uint8_t ADC1Semaphore;
extern uint8_t DMA5Semaphore;
extern uint8_t SPI1Semaphore;
extern uint8_t TMR1Semaphore;
extern uint8_t TMR3Semaphore;
extern uint8_t UART1Semaphore;
extern uint8_t UART2Semaphore;

#ifdef PIC24
void orCount(uint16_t* buffer, uint16_t bitmap, uint16_t count);
void andCount(uint16_t* buffer, uint16_t bitmap, uint16_t count);
#else
void orCount(uint8_t buffer, uint16_t bitmap, uint16_t count);
void andCount(uint8_t buffer, uint16_t bitmap, uint16_t count);
#endif

void updatePulseOutput(uint8_t pin, pulse_output_t* pulse);
uint8_t  PulseInGetOldestDMABit(uint8_t pin);
bool  PulseInGetOldestDMASample(uint8_t pin, uint16_t* value);
uint8_t  PulseInSkipDMABits(uint8_t pin, uint8_t count);
uint8_t PulseInDiscardUntilLow(uint8_t pin);
uint8_t PulseInDiscardUntilHigh(uint8_t pin);
void SetPinQuick(uint8_t pin, uint8_t pinState);
void SetPPSOutput(uint8_t pin, uint8_t value);
void SetPPSInput(uint8_t pin, uint8_t peripheral);

#ifdef PIC24
uint8_t pinIsPPSCapable(uint8_t pin);
#else
#define pinIsPPSCapable(_pin) (0==1)
#endif


typedef enum
{
	TIMING_RESOURCE_MCCP2,
	TIMING_RESOURCE_MCCP3,
	TIMING_RESOURCE_MCCP4,
	TIMING_RESOURCE_OC1,
	TIMING_RESOURCE_OC2,
	TIMING_RESOURCE_OC3,
	TIMING_RESOURCE_PORT_DMA,
	TIMING_RESOURCE_MCCP1,  // Place after DMA
	TIMING_RESOURCE_IC1,
	TIMING_RESOURCE_IC2,
	TIMING_RESOURCE_IC3,
	TIMING_RESOURCE_NUMBER_OF_RESOURCES,
	TIMING_RESOURCE_ANY,
	TIMING_RESOURCE_ALL,
	TIMING_RESOURCE_ANY_HARDWARE_OC,
	TIMING_RESOURCE_ANY_HARDWARE_IC,
	TIMING_RESOURCE_NONE = 0xFF,
} TIMING_RESOURCE_t;



    

TIMING_RESOURCE_t timingResourceHighPulseClaim(TIMING_RESOURCE_t resource,pulse_output_t* pulse);
TIMING_RESOURCE_t timingResourcePWMClaim(TIMING_RESOURCE_t resource, uint32_t period_uS);
void timingResourceSetInterrupt(TIMING_RESOURCE_t resource, uint16_t timeout_uS, timingResourceCallback_t callBack);
void timingResourcesHighPulse(pulse_output_t* pulse, uint16_t pulseTime_uS);
void timingResourcesLowPulse(TIMING_RESOURCE_t resource, uint16_t pulseTime_uS);
void timingResourcePWM(pulse_output_t *pulse, uint32_t period_uS, uint16_t dutyCycle);
bool timingResourceHighPulseBusy(pulse_output_t* pulse );
void deactivateOutputDMA(uint8_t pin);

#ifdef PIC24
void timingResourceService(pulse_output_t* pulse);
#else
#define timingResourceService(_pulse) {updatePulseOutput(CurrentPin, _pulse);}
#endif



TIMING_RESOURCE_t timingResourceGenericClaim(TIMING_RESOURCE_t request);

#ifdef NOTDMAONLY
void timingResourceRelease(TIMING_RESOURCE_t resource);
#else
#define timingResourceRelease(_resource) {deactivateOutputDMA(CurrentPin);}
#endif
void timingResourceManagerInit();

TIMING_RESOURCE_t timingResourceInterruptClaim(TIMING_RESOURCE_t resource, uint16_t counts, uint16_t uS, void (*callBack)(void));
void timingResourceInterruptActivate(TIMING_RESOURCE_t resource);
void timingResourceBusyWait(uint16_t uS);
TIMING_RESOURCE_t timingResourceCounterClaim(TIMING_RESOURCE_t resource);
uint32_t timingResourceReadCounter(TIMING_RESOURCE_t resource);
void timingResourceResetCounter(TIMING_RESOURCE_t resource);
void timingResourceDefault(TIMING_RESOURCE_t resource);

TIMING_RESOURCE_t timingResourceInputCaptureClaim(TIMING_RESOURCE_t resource);
int32_t timingResourceInputCaptureRead(TIMING_RESOURCE_t resource);


void initializeBitStreamOutput(uint8_t pin, uint8_t level,  DMABitStream_t* bitStream );
uint16_t updateBitStreamOutput(uint8_t pin, uint8_t level, uint16_t count, DMABitStream_t* bitStream );
uint16_t removeBitStreamOutput(uint8_t pin, uint16_t count, uint16_t margin, DMABitStream_t* bitStream );

#endif
