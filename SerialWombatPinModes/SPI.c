/*
Copyright 2026 Broadwell Consulting Inc.

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

/* Serial Wombat is a registered trademark of Broadwell Consulting Inc. */
#include "serialWombat.h"


typedef struct spi_n{
	uint8_t inputPin;
	uint8_t outputPin; 	
	uint8_t chipSelectPin;
	uint8_t mode;

}spi_t;



void  spiTransfer(uint8_t numOfBits, uint8_t* output, uint8_t *input)
{
	spi_t* spi = (spi_t*)CurrentPinRegister;
	unsigned int currentOutput = 0;
	unsigned int lastOutput = 0x55;

	* input = 0;
	if (spi->mode == 0)
	{
		CurrentPinLow();
		PinLow(spi->chipSelectPin);

		for (int bit = 0; bit <= numOfBits; ++bit)
		{

			CurrentPinLow();
			currentOutput = *output & 0x80;
			if (currentOutput != lastOutput)
			{
				if (currentOutput)
				{
					PinHigh(spi->outputPin);
				}
				else {
					PinLow(spi->outputPin);
				}
				lastOutput = currentOutput;
			}

			*output <<= 1;
			if (bit   < numOfBits)
			{
			CurrentPinHigh();
			}
			if (spi->inputPin != 255 )
			{
				*input <<= 1;
				if (ReadPin(spi->inputPin))
				{
					*input |= 1;
				}
			}


			if ((bit &0x7) == 7)
			{
				++ output;
				++ input;
				*input = 0;
			}
		}
		CurrentPinLow();
	}
	else if (spi->mode == 1)
	        {
	            CurrentPinLow();
	            PinLow(spi->chipSelectPin);

	            for (int bit = 0; bit <= numOfBits; ++bit)
	            {

	                CurrentPinHigh();
	                currentOutput = *output & 0x80;
	                if (currentOutput != lastOutput)
	                {
	                    if (currentOutput)
	                    {
	                        PinHigh(spi->outputPin);
	                    }
	                    else {
	                        PinLow(spi->outputPin);
	                    }
	                    lastOutput = currentOutput;
	                }

	                *output <<= 1;
	                CurrentPinLow();
	                if (spi->inputPin != 255)
	                {
	                    *input <<= 1;
	                    if (ReadPin(spi->inputPin))
	                    {
	                        *input |= 1;
	                    }
	                }


	                if ((bit &0x7) == 7)
	                {
	                    ++ output;
	                    ++ input;
	                    *input = 0;
	                }
	            }
	            CurrentPinLow();
	        }
	else if (spi->mode == 3)
	            {
	                CurrentPinHigh();
	                PinLow(spi->chipSelectPin);

	                for (int bit = 0; bit < numOfBits; ++bit)
	                {

	                    CurrentPinLow();
	                    currentOutput = *output & 0x80;
	                    if (currentOutput != lastOutput)
	                    {
	                        if (currentOutput)
	                        {
	                            PinHigh(spi->outputPin);
	                        }
	                        else {
	                            PinLow(spi->outputPin);
	                        }
	                        lastOutput = currentOutput;
	                    }

	                    *output <<= 1;
	                    CurrentPinHigh();
	                    if (spi->inputPin != 255 )
	                    {
	                        *input <<= 1;
	                        if (ReadPin(spi->inputPin))
	                        {
	                            *input |= 1;
	                        }
	                    }


	                    if ((bit &0x7) == 7)
	                    {
	                        ++ output;
	                        ++ input;
	                        *input = 0;
	                    }
	                }
	                CurrentPinHigh();
	            }
	if ((Rxbuffer[0] & 0x01) > 0)
	{
		PinHigh(spi->chipSelectPin);
	}


}
void initSPI()
{
	spi_t* spi = (spi_t*)CurrentPinRegister;
  BUILD_BUG_ON( sizeof(spi_t) >  BYTES_PER_PIN_REGISTER );
if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_SPI)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{
			    spi->mode = Rxbuffer[3];
			                    spi->outputPin = Rxbuffer[4];
                                SetPinMode(spi->outputPin,PIN_MODE_CONTROLLED);
			                    spi->inputPin = Rxbuffer[5];
                                SetPinMode(spi->inputPin,PIN_MODE_CONTROLLED);
			                    spi->chipSelectPin = Rxbuffer[6];
                                SetPinMode(spi->chipSelectPin,PIN_MODE_CONTROLLED);

				switch (Rxbuffer[3])
				{
					case 0:
					case 1:
					    InitializePinHighPPSLow(spi->chipSelectPin);
					    InitializePinLow(CurrentPin);
					    InitializePinLow(spi->outputPin);
					break;

					case 2:
					case 3:
					    InitializePinHighPPSLow(spi->chipSelectPin);
					    InitializePinLow(spi->outputPin);
					    InitializePinHighPPSLow(CurrentPin);
					
					break;

					
				}

				CurrentPinRegister->generic.mode = PIN_MODE_SPI;
				PinInput(spi->inputPin);
				
			}
			break;
			// send arbitrary number of bits (up to 32)
		case CONFIGURE_CHANNEL_MODE_1: //Set cs high at end of transaction
		case CONFIGURE_CHANNEL_MODE_2: // Leave cs low at end of transaction
			{
				if (Rxbuffer[3] <= 32 && Rxbuffer[3] >= 1)
				{
					spiTransfer(Rxbuffer[3], &Rxbuffer[4], &Txbuffer[4]);
				}
				else
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
				}
			}
			break;
			// send 5 bytes 
		case CONFIGURE_CHANNEL_MODE_3: //Set cs high at end of transaction
		case CONFIGURE_CHANNEL_MODE_4: // Leave cs low at end of transaction
			{
					spiTransfer(40, &Rxbuffer[3], &Txbuffer[3]);
			}
			break;
        case CONFIGURE_CHANNEL_MODE_5:
        {
            // Set CS high
            PinHigh(spi->chipSelectPin);
        }
        break;

		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}


}

void updateSPI()
{

}

