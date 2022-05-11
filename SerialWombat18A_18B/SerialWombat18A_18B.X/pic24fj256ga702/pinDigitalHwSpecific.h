#ifndef PIN_DIGITAL_HW_SPECIFIC_H
#define PIN_DIGITAL_HW_SPECIFIC_H
#include <stdint.h>
#include "deviceSpecific.h"
#define SIZE_OF_DMA_ARRAY 128

#define OUTPUT_ARRAY_A_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT0) 
#define OUTPUT_ARRAY_B_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT1) 
#define INPUT_ARRAY_A_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT2) 
#define INPUT_ARRAY_B_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT3) 

extern uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t OutputArrayB[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayB[SIZE_OF_DMA_ARRAY];
extern const uint8_t WombatPinToADCChannel[NUMBER_OF_PHYSICAL_PINS];
extern const uint8_t pinPPSInputMap[NUMBER_OF_PHYSICAL_PINS];

#define DIGITAL_LOW 0
#define DIGITAL_HIGH 1
#define DIGITAL_INPUT 2
void PinInput(uint8_t pin);
void PinOutput(uint8_t pin);
void PinHigh(uint8_t pin);
void PinLow(uint8_t pin);
void SetPin(uint8_t pin, uint8_t pinState); 
void InitializePinLow(uint8_t pin);

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


void orCount(uint16_t* buffer, uint16_t bitmap, uint16_t count);
void andCount(uint16_t* buffer, uint16_t bitmap, uint16_t count);
void updatePulseOutput(uint8_t pin);
uint8_t  PulseInGetOldestDMABit(uint8_t pin);
bool  PulseInGetOldestDMASample(uint8_t pin, uint16_t* value);
uint8_t  PulseInSkipDMABits(uint8_t pin, uint8_t count);
void PulseInDiscardUntilLow(uint8_t pin);
void SetPinQuick(uint8_t pin, uint8_t pinState);
void SetPPSOutput(uint8_t pin, uint8_t value);
void SetPPSInput(uint8_t pin, uint8_t peripheral);
uint8_t pinIsPPSCapable(uint8_t pin);


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
	TIMING_RESOURCE_NUMBER_OF_RESOURCES,
	TIMING_RESOURCE_ANY,
	TIMING_RESOURCE_ALL,
	TIMING_RESOURCE_ANY_HARDWARE,
	TIMING_RESOURCE_NONE = 0xFF,
} TIMING_RESOURCE_t;

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


TIMING_RESOURCE_t timingResourceHighPulseClaim(TIMING_RESOURCE_t resource);
TIMING_RESOURCE_t timingResourcePWMClaim(TIMING_RESOURCE_t resource, uint32_t period_uS);
void timingResourceSetInterrupt(TIMING_RESOURCE_t resource, uint16_t timeout_uS, timingResourceCallback_t callBack);
void timingResourcesHighPulse(TIMING_RESOURCE_t resource, uint16_t pulseTime_uS);
void timingResourcesLowPulse(TIMING_RESOURCE_t resource, uint16_t pulseTime_uS);
void timingResourcePWM(TIMING_RESOURCE_t resource, uint32_t period_uS, uint16_t dutyCycle);
bool timingResourceHighPulseBusy(TIMING_RESOURCE_t resource );
void timingResourceService(TIMING_RESOURCE_t resource);
void timingResourceRelease(TIMING_RESOURCE_t resource);
void timingResourceManagerInit();

TIMING_RESOURCE_t timingResourceInterruptClaim(TIMING_RESOURCE_t resource, uint16_t counts, uint16_t uS, void (*callBack)(void));
void timingResourceInterruptActivate(TIMING_RESOURCE_t resource);
void timingResourceBusyWait(uint16_t uS);

typedef struct DMABitStream_n{
uint8_t nextLocationToQueue;
uint8_t lastDMA;
}DMABitStream_t;
void initializeBitStreamOutput(uint8_t pin, uint8_t level,  DMABitStream_t* bitStream );
uint16_t updateBitStreamOutput(uint8_t pin, uint8_t level, uint16_t count, DMABitStream_t* bitStream );
uint16_t removeBitStreamOutput(uint8_t pin, uint16_t count, uint16_t margin, DMABitStream_t* bitStream );

#endif
