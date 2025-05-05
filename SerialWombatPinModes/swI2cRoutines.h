/*
Copyright 2024 Broadwell Consulting Inc.

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
 
 Serial Wombat is a trademark of Broadwell Consulting Inc.
*/

#ifndef _SW_I2C_ROUTINES_
#define _SW_I2C_ROUTINES_

#include <stdint.h>
#include "serialWombat.h"

#define SWI2C_TX_BUFFER_SIZE 8
#define SWI2C_RX_BUFFER_SIZE 8
typedef struct swI2C_n
{
	uint8_t tx[8];
	uint8_t rx[8];
	uint32_t iaddress;
	uint8_t bytesToTx;
	uint8_t bytesToRx;
	uint8_t bytesReceived;
	uint8_t bytesTransmitted;
	uint16_t bytesPerSWFrame:4;
	uint16_t bytesTransferredThisSWFrame:4;
	uint16_t lastSDA:2;
	uint16_t startSent:1;
	uint16_t txAddressSent:1;
	uint16_t rxAddressSent:1;
	uint16_t busy:1;
	uint16_t nackResult:1;
	uint16_t readStop:1;
	uint16_t writeStop:1;
	uint16_t isize:2;
    uint16_t isizeSent:2;
	uint8_t sdaPin;
	uint8_t address;
}swI2cRoutines_t;

extern swI2cRoutines_t* SWI2C;


void SWI2C_begin();
void SWI2C_end();
void SWI2C_requestFrom(uint8_t address, uint8_t quantity, uint8_t stop);
void SWI2C_beginTransmission(uint8_t address);
void SWI2C_endTransmission(uint8_t stop);
void SWI2C_writeByte(uint8_t val);
void SWI2C_writeArray(uint8_t* data, uint8_t length);

#endif
