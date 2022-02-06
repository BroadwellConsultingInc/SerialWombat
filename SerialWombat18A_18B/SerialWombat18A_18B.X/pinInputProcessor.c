/*
Copyright 2020-2021 Broadwell Consulting Inc.

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

/* Serial Wombat is a trademark of Broadwell Consulting Inc. */

#include "SerialWombat.h"
#include "inputProcess.h"
#include <stdint.h>

typedef struct pulseTimer_n{
    inputProcess_t inputProcess;
	uint8_t sourcePin;	
	uint16_t defaultValue;
}pinInputProcessor_t;


void initPinInputProcessor()
{
    BUILD_BUG_ON( sizeof(pinInputProcessor_t) >  BYTES_AVAILABLE_INPUT_DMA ); 
	pinInputProcessor_t* pinInputProcessor = (pinInputProcessor_t*) CurrentPinRegister;

	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:

			{
				pinInputProcessor->sourcePin = Rxbuffer[3];
				pinInputProcessor->defaultValue = RXBUFFER16(4);
				CurrentPinRegister->generic.mode = PIN_MODE_INPUT_PROCESSOR;	
			}
			break;


		case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&pinInputProcessor->inputProcess);
			}
			break;
	}


} 
pinInputProcessor_t*  debugPinInputProcessor;
void updatePinInputProcessor()
{
	pinInputProcessor_t* pinInputProcessor = (pinInputProcessor_t*) CurrentPinRegister;
	debugPinInputProcessor = pinInputProcessor;

	uint16_t inputvalue;
	if (pinInputProcessor->sourcePin == 255)
	{
		inputvalue = pinInputProcessor->defaultValue;
	}
	else
	{
		inputvalue = GetBuffer(pinInputProcessor->sourcePin);
	}


           CurrentPinRegister->generic.buffer = inputProcessProcess(&pinInputProcessor->inputProcess,inputvalue);
}

