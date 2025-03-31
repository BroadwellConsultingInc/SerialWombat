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
*/
#include "serialWombat.h"
#include <stdint.h>
#include "swI2cRoutines.h"




typedef struct i2cController_n{
	swI2cRoutines_t SWI2C; 
}i2cController_t;



/*!
    \brief Initialization routine for High Speed Clock

----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize High Speed Clock Output


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (TO HS Clock)|0x1D (HS Clock ) | Frequency LSB |Frequency MidLB | Frequency MidHB | Frequency MSB| 0x55|


 * Frequency :  Desired output frequency

Response:

Command is returned with frequency set to the hardware (due to integer round off error).  Actual output may vary up to an additional 2%
due to internal oscillator variation.

Examples:

Set pin 19 to HS Clock, 1 MHz (0x000F4240)

> `0xC0 0x13 0x1D 0x40 0x42 0x0F 0x00 0x55 `

----

CONFIGURE_CHANNEL_MODE_19:
---------------------

Disable High Speed Clock Output.  Turns off Clock generation output, and makes the pin Digital out low.


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (TO HS Clock)|0x1D (HS Clock ) | 0x55 |0x55 | 0x55 | 0x55| 0x55|



Response:

Echoed back

Examples:

Disable pin 19  HS Clock

> `0xDB 0x13 0x1D 0x55 0x55 0x55 0x55 0x55 `

----


*/

void initI2CController (void)
{
	i2cController_t* i2cController = (i2cController_t*)CurrentPinRegister;
	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_I2C_CONTROLLER)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	SWI2C = &i2cController->SWI2C;
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
				SWI2C->sdaPin = Rxbuffer[3];	
                
                InitializePinHigh(CurrentPin);
                InitializePinHigh(SWI2C->sdaPin);
                PinOD(CurrentPin);
                PinOD(SWI2C->sdaPin);
				SWI2C->bytesPerSWFrame = Rxbuffer[4];
				if (Rxbuffer[5])
				{
					//TODO Turn on Pull Ups
				}
				else
				{
					//Turn off Pull Ups
				}	
				CurrentPinRegister->generic.mode = PIN_MODE_I2C_CONTROLLER;
			}
			break;

		case CONFIGURE_CHANNEL_MODE_SWI2C: 
			{
				switch (Rxbuffer[3])
				{
					case 0:
						{
							SWI2C->sdaPin = Rxbuffer[4];	
							SWI2C->bytesPerSWFrame = Rxbuffer[5];
							if (Rxbuffer[6])
							{
								//TODO Turn on Pull Ups
							}
							else
							{
								//Turn off Pull Ups
							}	
						}
						break;

					case 1:
						{
							SWI2C_beginTransmission( Rxbuffer[4]);
						}
						break;
					case 2:
						{
							SWI2C_endTransmission( Rxbuffer[4]);
						}
						break;
					case 3:
						{
							SWI2C_writeByte( Rxbuffer[4]);
						}
						break;
					case 4:
						{
							SWI2C_requestFrom( Rxbuffer[4], Rxbuffer[5], Rxbuffer[6]);
							SWI2C->isize = Rxbuffer[7];
						}
						break;

					case 5:
						{
							SWI2C->iaddress = RXBUFFER32(4);

						}
						break;


					case 6:
						{
							//TODO copy from User Memory
							// index in RXBUFFER16(4), length in 6, maximum 8

						}
						break;
					case 7:
						{
							SWI2C->busy = Rxbuffer[4];
						}
						break;
					case 8:
						{
							Txbuffer[4] = SWI2C->busy;
							Txbuffer[5] = SWI2C->bytesTransmitted;
							Txbuffer[6] = SWI2C->bytesReceived;
							Txbuffer[7] = SWI2C->nackResult;
						}
						break;
					case 9:
						{ // Read 4 bytes starting at 0
							Txbuffer[4] = SWI2C->rx[0]; 
							Txbuffer[5] = SWI2C->rx[1]; 
							Txbuffer[6] = SWI2C->rx[2]; 
							Txbuffer[7] = SWI2C->rx[3]; 
						}
						break;
					case 10:
						{ // Read 4 bytes starting at 4
							Txbuffer[4] = SWI2C->rx[4]; 
							Txbuffer[5] = SWI2C->rx[5]; 
							Txbuffer[6] = SWI2C->rx[6]; 
							Txbuffer[7] = SWI2C->rx[7]; 
						}
						break;


					default:
						{
							error(SW_ERROR_INVALID_PARAMETER_3);
						}
						break;
				}
			}
			break;

		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}

}


/// \brief The function that updates I2CController
///
void updateI2CController()
{ 
i2cController_t* i2cController = (i2cController_t*)CurrentPinRegister;
    SWI2C = &i2cController->SWI2C;
    updateSWI2C();
}


