/*
Copyright 2020-2025 Broadwell Consulting Inc.

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

/* Serial Wombat is a trademark of Broadwell Consulting Inc. registered
 * in the United States. */


#ifndef SERIALWOMBAT_H
#define SERIALWOMBAT_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "pinModes.h"
#include "deviceSpecific.h"
#include "pinRegisters.h"
#include "protocol.h"
#include "queue.h"
#include "serialWombatErrors.h"

extern  uint8_t CurrentPin;

extern pinRegister_t PinUpdateRegisters[NUMBER_OF_TOTAL_PINS];

extern bool RunForeground;

#define RXBUFFER_LENGTH 8
extern uint8_t Rxbuffer[RXBUFFER_LENGTH];

#define TXBUFFER_LENGTH 8
extern uint8_t Txbuffer[TXBUFFER_LENGTH];

#if SIZE_OF_USER_BUFFER > 0
extern uint8_t UserBuffer[SIZE_OF_USER_BUFFER];
#endif

#define CLOCK_STRETCHING_MAX 10
#define DIGITAL_LOW 0
#define DIGITAL_HIGH 1
#define DIGITAL_INPUT 2
uint8_t CurrentPinPort(void);
uint16_t CurrentPinBitmap(void);
bool CurrentPinRead(void);
bool ReadPin(uint8_t pin);
void ConfigurePinAnalog(uint8_t pin, bool makeAnalog);
void CurrentPinAnalog(void);
void CurrentPinNotAnalog(void);
void CurrentPinPullUp(void);
void CurrentPinNoPullUp(void);

void PinInput(uint8_t pin);
void PinOutput(uint8_t pin);
void PinHigh(uint8_t pin);
void PinLow(uint8_t pin);
void SetPin(uint8_t pin, uint8_t pinState); 
void CurrentPinInput(void);
void CurrentPinOutput(void);
void CurrentPinHigh(void);
void CurrentPinLow(void);
void SetCurrentPin(uint8_t pinState);
void CurrentPinPullup(void);
void CurrentPinNoPullup(void);
void PinPullUp(uint8_t pin);
void PinNoPullUp(uint8_t pin);
bool ReadPin(uint8_t pin);
void CurrentPinOpenDrain(void);
void CurrentPinNotOpenDrain(void);

void ProcessRx(void);
void ProcessPins(void);
void reset(void);


typedef enum {

	SW_DATA_SOURCE_PIN_0 = 0,
	SW_DATA_SOURCE_PIN_1 = 1,
	SW_DATA_SOURCE_PIN_2 = 2,
	SW_DATA_SOURCE_PIN_3 = 3,
	SW_DATA_SOURCE_PIN_4 = 4,
	SW_DATA_SOURCE_PIN_5 = 5,
	SW_DATA_SOURCE_PIN_6 = 6,
	SW_DATA_SOURCE_PIN_7 = 7,
	SW_DATA_SOURCE_PIN_8 = 8,
	SW_DATA_SOURCE_PIN_9 = 9,
	SW_DATA_SOURCE_PIN_10 = 10,
	SW_DATA_SOURCE_PIN_11 = 11,
	SW_DATA_SOURCE_PIN_12 = 12,
	SW_DATA_SOURCE_PIN_13 = 13,
	SW_DATA_SOURCE_PIN_14 = 14,
	SW_DATA_SOURCE_PIN_15 = 15,
	SW_DATA_SOURCE_PIN_16 = 16,
	SW_DATA_SOURCE_PIN_17 = 17,
	SW_DATA_SOURCE_PIN_18 = 18,
	SW_DATA_SOURCE_PIN_19 = 19,
//	SW_DATA_SOURCE_PIN_20 = 20,
//	SW_DATA_SOURCE_PIN_21 = 21,
//	SW_DATA_SOURCE_PIN_22 = 22,
//	SW_DATA_SOURCE_PIN_23 = 23,
//	SW_DATA_SOURCE_PIN_24 = 24,
//	SW_DATA_SOURCE_PIN_25 = 25,
//	SW_DATA_SOURCE_PIN_26 = 26,
//	SW_DATA_SOURCE_PIN_27 = 27,
//	SW_DATA_SOURCE_PIN_28 = 28,
//	SW_DATA_SOURCE_PIN_29 = 29,
//	SW_DATA_SOURCE_PIN_30 = 30,
//	SW_DATA_SOURCE_PIN_31 = 31,
//	SW_DATA_SOURCE_PIN_32 = 32,
//	SW_DATA_SOURCE_PIN_33 = 33,
//	SW_DATA_SOURCE_PIN_34 = 34,
//	SW_DATA_SOURCE_PIN_35 = 35,
//	SW_DATA_SOURCE_PIN_36 = 36,
//	SW_DATA_SOURCE_PIN_37 = 37,
//	SW_DATA_SOURCE_PIN_38 = 38,
//	SW_DATA_SOURCE_PIN_39 = 39,
//	SW_DATA_SOURCE_PIN_40 = 40,
//	SW_DATA_SOURCE_PIN_41 = 41,
//	SW_DATA_SOURCE_PIN_42 = 42,
//	SW_DATA_SOURCE_PIN_43 = 43,
//	SW_DATA_SOURCE_PIN_44 = 44,
//	SW_DATA_SOURCE_PIN_45 = 45,
//	SW_DATA_SOURCE_PIN_46 = 46,
//	SW_DATA_SOURCE_PIN_47 = 47,
//	SW_DATA_SOURCE_PIN_48 = 48,
//	SW_DATA_SOURCE_PIN_49 = 49,
//	SW_DATA_SOURCE_PIN_50 = 50,
//	SW_DATA_SOURCE_PIN_51 = 51,
//	SW_DATA_SOURCE_PIN_52 = 52,
//	SW_DATA_SOURCE_PIN_53 = 53,
//	SW_DATA_SOURCE_PIN_54 = 54,
//	SW_DATA_SOURCE_PIN_55 = 55,
//	SW_DATA_SOURCE_PIN_56 = 56,
//	SW_DATA_SOURCE_PIN_57 = 57,
//	SW_DATA_SOURCE_PIN_58 = 58,
//	SW_DATA_SOURCE_PIN_59 = 59,
//	SW_DATA_SOURCE_PIN_60 = 60,
//	SW_DATA_SOURCE_PIN_61 = 61,
//	SW_DATA_SOURCE_PIN_62 = 62,
//	SW_DATA_SOURCE_PIN_63 = 63,
	SW_DATA_SOURCE_INCREMENTING_NUMBER = 65, ///< An number that increments each time it is accessed.
	SW_DATA_SOURCE_1024mvCounts = 66 , ///< The number of ADC counts that result from a 1.024V reading
	SW_DATA_SOURCE_FRAMES_RUN_LSW = 67, ///< The number of frames run since reset, least significant 16 bits
	SW_DATA_SOURCE_FRAMES_RUN_MSW = 68, ///< The number of frames run since reset, most significant 16 bits
	SW_DATA_SOURCE_OVERRUN_FRAMES = 69, ///< The number of frames that ran more than 1mS
	SW_DATA_SOURCE_TEMPERATURE = 70, ///<The internal core temperature expressed in 100ths deg C
	SW_DATA_SOURCE_PACKETS_RECEIVED = 71,  ///<The nubmer of incoming command packets that have been processed since reset (rolls over at 65535)
	SW_DATA_SOURCE_ERRORS = 72,  ///<The number of incoming packets that have caused errors since reset (rolls over at 65535)  
	SW_DATA_SOURCE_FRAMES_DROPPED = 73 , ///<The number of times since reset that a frame ran so far behind that it crossed two subsequent 1ms boundaries, causing a permanent lost frame
	SW_DATA_SOURCE_SYSTEM_UTILIZATION = 74 , ///< A number between 0 and 65535 that scales to the average length of pin processing frames between 0 and 1000mS
            SW_DATA_SOURCE_VCC_mVOLTS = 75, ///<The system source voltage in mV
            SW_DATA_SOURCE_VBG_COUNTS_VS_VREF = 76, ///< A/D conversion of VBG against VRef .  Used for mfg calibration
            SW_DATA_SOURCE_RESET_REGISTER = 77, ///< Hardware dependent reset reason register contents
            SW_DATA_SOURCE_LFSR = 78, ///< A Linear FeedBack Shift register (32,7,5,3,2,1) based pseudo-random number generator
            SW_DATA_SOURCE_PIN_0_MV = 100, ///< The public data of Pin 0 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_1_MV = 101, ///< The public data of Pin 1 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_2_MV = 102, ///< The public data of Pin 2 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_3_MV = 103, ///< The public data of Pin 3 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_4_MV = 104, ///< The public data of Pin 4 expressed as mV.  Only applicable to Analog Input mode
//NOT ANALOG            SW_DATA_SOURCE_PIN_5_MV = 105,
//NOT ANALOG            SW_DATA_SOURCE_PIN_6_MV = 106,
//NOT ANALOG            SW_DATA_SOURCE_PIN_7_MV = 107,
//NOT ANALOG            SW_DATA_SOURCE_PIN_8_MV = 108,
//NOT ANALOG            SW_DATA_SOURCE_PIN_9_MV = 109,
//NOT ANALOG            SW_DATA_SOURCE_PIN_10_MV = 110,
//NOT ANALOG            SW_DATA_SOURCE_PIN_11_MV = 111,
//NOT ANALOG            SW_DATA_SOURCE_PIN_12_MV = 112,
//NOT ANALOG            SW_DATA_SOURCE_PIN_13_MV = 113,
//NOT ANALOG            SW_DATA_SOURCE_PIN_14_MV = 114,
//NOT ANALOG            SW_DATA_SOURCE_PIN_15_MV = 115,
            SW_DATA_SOURCE_PIN_16_MV = 116, ///< The public data of Pin 16 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_17_MV = 117, ///< The public data of Pin 17 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_18_MV = 118, ///< The public data of Pin 18 expressed as mV.  Only applicable to Analog Input mode
            SW_DATA_SOURCE_PIN_19_MV = 119, ///< The public data of Pin 19 expressed as mV.  Only applicable to Analog Input mode
            
            SW_DATA_SOURCE_2HZ_SQUARE = 164, ///< Square wave that alternates between 0 and 65535 every 256 frames
            SW_DATA_SOURCE_2HZ_SAW = 165,///< Sawtooth wave that goes from  0 to 65535 to 0 every  512 frames
//            SW_DATA_SOURCE_2HZ_SIN = 166,
            SW_DATA_SOURCE_1HZ_SQUARE = 167,///< Square wave that alternates between 0 and 65535 every 512 frames
            SW_DATA_SOURCE_1HZ_SAW = 168,///< Sawtooth wave that goes from  0 to 65535 to 0 every  1024 frames
 //           SW_DATA_SOURCE_1HZ_SIN = 169,
            SW_DATA_SOURCE_2SEC_SQUARE = 170,///< Square wave that alternates between 0 and 65535 every 1024 frames
            SW_DATA_SOURCE_2SEC_SAW = 171,///< Sawtooth wave that goes from  0 to 65535 to 0 every  2048 frames
  //          SW_DATA_SOURCE_2SEC_SIN = 172,
            SW_DATA_SOURCE_8SEC_SQUARE = 173,///< Square wave that alternates between 0 and 65535 every 4096 frames
            SW_DATA_SOURCE_8SEC_SAW = 174,///< Sawtooth wave that goes from  0 to 65535 to 0 every  8192 frames
   //         SW_DATA_SOURCE_8SEC_SIN = 175,
            SW_DATA_SOURCE_65SEC_SQUARE = 176,///< Square wave that alternates between 0 and 65535 every 32768 frames
            SW_DATA_SOURCE_65SEC_SAW = 177,///< Sawtooth wave that goes from  0 to 65535 to 0 every  65536 frames
    //        SW_DATA_SOURCE_65SEC_SIN = 178,
}SW_DATA_SOURCE_t;
 


void error (SW_ERROR_t errorCode);

extern uint32_t FramesRun;

#endif

