/*
Copyright 2024 Broadwell Consulting Inc.

Serial Wombat is a registered trademark of Broadwell Consulting Inc in
the United States.  See SerialWombat.com for usage guidelines.

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

#include <stdint.h>
#include "serialWombat.h"
#include "inputProcess.h"
#include "outputScale.h"

typedef struct digitalIO_n{
	union{
         inputProcess_t inputProcess;
	 outputScale_t outputScale;
     	};
	 bool isOutput;

}digitalIO_t;

#define digitalIO ((digitalIO_t*) CurrentPinRegister)

void initDigitalIO (void)
{
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_DIGITAL_IO)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				switch (Rxbuffer[3])
				{
					case 0: // Output Low
						InitializePinLow(CurrentPin);
						digitalIO->isOutput = true;
						outputScaleInit(&digitalIO->outputScale);
						CurrentPinRegister->generic.buffer = 0;
						break;
					case 1: // Output High
						InitializePinHigh(CurrentPin);
						CurrentPinHigh();
						digitalIO->isOutput = true;
						outputScaleInit(&digitalIO->outputScale);
						CurrentPinRegister->generic.buffer = 65535;
						break;
					case 2: // Input
						digitalIO->isOutput = false;
						CurrentPinInput();
						inputProcessInit(&digitalIO->inputProcess);
						break;
					default:
						{
							error(SW_ERROR_INVALID_PARAMETER_3);
							return;
						}
						break;
				}

				if (Rxbuffer[4] == 1)
				{
					PinPullUp(CurrentPin);
				}
				else
				{
					PinNoPullUp(CurrentPin);
				}
				if (Rxbuffer[5] == 1)
				{
					PinPullDown(CurrentPin);
				}
				else
				{
					PinNoPullDown(CurrentPin);
				}
				if (Rxbuffer[6] == 1)
				{
					PinOD(CurrentPin);
				}
				else
				{
					PinNoOD(CurrentPin);
				}
				CurrentPinRegister->generic.mode = PIN_MODE_DIGITAL_IO;
			}
			break;
		case CONFIGURE_CHANNEL_MODE_SCALED_OUTPUT:
			{
				if (digitalIO->isOutput)
				{
					outputScaleCommProcess(&digitalIO->outputScale);
				}
				else
				{
					error(SW_ERROR_PIN_IS_NOT_OUTPUT);
				}
			}
			break;
		case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				if (digitalIO->isOutput)
				{
					error(SW_ERROR_PIN_IS_NOT_INPUT);
				}
				else
				{
					inputProcessCommProcess(&digitalIO->inputProcess);
				}
				break;
			}

			break;
		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}
}


void updateDigitalIO()
{ 
    if (digitalIO->isOutput)
    {

	    uint16_t outputValue = outputScaleProcess(&digitalIO->outputScale);
	    if (digitalIO->outputScale.sourcePin != CurrentPin)
	    {
		    CurrentPinRegister->generic.buffer = outputValue;  
	    }
	    SetCurrentPin(outputValue > 0);
    }
    else
    {
	    uint16_t pd;
	   pd  = CurrentPinRead()?65535:0;
            CurrentPinRegister->generic.buffer = inputProcessProcess(&digitalIO->inputProcess,pd);
    }
    
}

