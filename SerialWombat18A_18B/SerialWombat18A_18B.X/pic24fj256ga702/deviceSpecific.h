#ifndef DEVICE_SPECIFIC_H
#define DEVICE_SPECIFIC_H
#include <xc.h> 
#include "mcc.h"

#define NUMBER_OF_PHYSICAL_PINS 20
#define NUMBER_OF_VIRTUAL_PINS 0
#define NUMBER_OF_TOTAL_PINS (NUMBER_OF_PHYSICAL_PINS + NUMBER_OF_VIRTUAL_PINS)

#define DMA_FREQUENCY 57600
#define ADC_MAX_COUNTS 0xFFF0

#define SIZE_OF_USER_BUFFER 8192
#include "pinDigitalHwSpecific.h"

#endif
