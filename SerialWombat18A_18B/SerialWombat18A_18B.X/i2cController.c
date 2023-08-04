/*
Copyright 2023 Broadwell Consulting Inc.

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
#include "pic24fj256ga702/mcc_generated_files/mcc.h"
#include "pic24fj256ga702/mcc_generated_files/i2c2Controller.h"





typedef struct i2cController_n{
	uint8_t dummy;  // No pin mode data for this mode except the standard generic items.  
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

void initi2cController (void)
{
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_I2C_CONTROLLER)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
                if (CurrentPin != 4)
                {
                    error(SW_ERROR_PIN_NOT_CAPABLE);
                }
                
                I2C2_Controller_Initialize();
                
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
void updatei2cController()
{ 

}


