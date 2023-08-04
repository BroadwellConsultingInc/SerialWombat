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
#include "asciiConversion.h"
#include "pic24fj256ga702/mcc_generated_files/mcc.h"





typedef struct HSClock_n{
	uint8_t dummy;  // No pin mode data for this mode except the standard generic items.  
}HSClock_t;



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

void initHSClock (void)
{
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_HS_CLOCK)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
                uint32_t desiredFrequency = 32000000;
             REFOCONLbits.ROOUT = 0;
             REFOCONL = 0;
				desiredFrequency = RXBUFFER32(3);
                
                if ((desiredFrequency > 16000000 && desiredFrequency != 32000000) || desiredFrequency == 0)
                {
                    error(SW_ERROR_INVALID_PARAMETER_3);
                    return;
                }
                
                uint32_t divisor = 32000000 / desiredFrequency;
                divisor /= 2;
                if (divisor > 32767)
                {
                    divisor = 32767;
                }
                REFOCONH = (uint16_t) divisor;
				REFOCONL = 0x9806;
				SetPin(CurrentPin,DIGITAL_HIGH);
				SetPPSOutput(CurrentPin, 28); //Reference output
                CurrentPinRegister->generic.mode = PIN_MODE_HS_CLOCK;
                
                if (REFOCONH == 0)
                {
                    TXBUFFER32(3,32000000); 
                }
                else
                {
                    uint32_t actual = 32000000;
                    actual /= (2ul * REFOCONH);
                    TXBUFFER32(3,actual);
                }
                

			}
			break;
 case CONFIGURE_CHANNEL_MODE_DISABLE:
			{
             REFOCONLbits.ROOUT = 0;
             REFOCONL = 0;

				SetPPSOutput(CurrentPin, 0); //Reference output
                InitializePinLow(CurrentPin);
 }
 break;

		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}
}


/// \brief The function that updates High Speed Clock mode
///
/// On the Serial Wombat 18AB chip the HS Clock mode is simply a wrapper around the
/// PIC24FJ256GA702's Ref Clock output capability.  Therefore only one pin can use the 
/// High Speed out function.  Only Enhanced Digitial Capability pins can be used. 
void updateHSClock()
{ 

}


