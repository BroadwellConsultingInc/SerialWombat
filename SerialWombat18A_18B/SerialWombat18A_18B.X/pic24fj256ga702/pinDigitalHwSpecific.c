/*
Copyright 2021-2023 Broadwell Consulting Inc.

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

#include "mcc_generated_files/system.h"
#include "deviceSpecific.h"
#include "serialWombat.h"

void or128(uint16_t* array, uint16_t value); 
void and128(uint16_t* array, uint16_t value); 
uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t OutputArrayB[SIZE_OF_DMA_ARRAY] = {  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t InputArrayA[SIZE_OF_DMA_ARRAY];
uint16_t InputArrayB[SIZE_OF_DMA_ARRAY];

#define PIN_QUICK_SET_DMA_COUNTS 15  //How many DMA counts into the future to set the current state.   This has to last until the pin gets set again. 
/*
const uint16_t PinBitmapB[NUMBER_OF_PHYSICAL_PINS] = 
{
    //Skip RA0, it's address pin, not WP.
	0x0000 , // 0 RA1
	0x0001 , // 1 RB0
	0x0002 , // 2 RB1
	0x0004 , // 3 RB2
	0x0008 , // 4 RB3
	0x0000 , // 5 RA2
	0x0000 , // 6 RA3
    0x0010 , // 7 RB4
	0x0000 , // 8 RA4
	0x0020 , // 9 RB5
	0x0040 , // 10 RB6
	0x0080 , // 11 RB7
	0x0100 , // 12 RB8
	0x0200 , // 13 RB9
	0x0400 , // 14 RB10
	0x0800 , // 15 RB11
	0x1000 , // 16 RB12
	0x2000 , // 17 RB13
	0x4000 , // 18 RB14
	0x8000 , // 19 RB15
};


const uint16_t PinBitmapA[NUMBER_OF_PHYSICAL_PINS] = 
{

	0x0001 , // 0 RA0
	0x0000 , // 1 RB0
	0x0000 , // 2 RB1
	0x0000 , // 3 RB2
	0x0000 , // 4 RB3
	0x0004 , // 5 RA2
	0x0008 , // 6 RA3
    0x0000 , // 7 RB4
	0x0010 , // 8 RA4
	0x0000 , // 9 RB5
	0x0000 , // 10 RB6
	0x0000 , // 11 RB7
	0x0000 , // 12 RB8
	0x0000 , // 13 RB9
	0x0000 , // 14 RB10
	0x0000 , // 15 RB11
	0x0000 , // 16 RB12
	0x0000 , // 17 RB13
	0x0000 , // 18 RB14
	0x0000 , // 19 RB15
};
*/
const uint8_t pinPort[NUMBER_OF_PHYSICAL_PINS] =
{
	//Skip RA0, it's address pin, not WP.
	0x00 , // 0 RA0
	0x01 , // 1 RB0
	0x01 , // 2 RB1
	0x01 , // 3 RB2
	0x01 , // 4 RB3
	0x00 , // 5 RA2
	0x00 , // 6 RA3
        0x01 , // 7 RB4
	0x00 , // 8 RA4
	0x01 , // 9 RB5
	0x01 , // 10 RB6
	0x01 , // 11 RB7
	0x01 , // 12 RB8
	0x01 , // 13 RB9
	0x01 , // 14 RB10
	0x01 , // 15 RB11
	0x01 , // 16 RB12
	0x01 , // 17 RB13
	0x01 , // 18 RB14
	0x01 , // 19 RB15
};

bool PINS_ON_DIFFERENT_PORTS (uint8_t p1, uint8_t p2)
{
    return(pinPort[p1] != pinPort[p2]);
}
const uint16_t pinBitmap[NUMBER_OF_PHYSICAL_PINS] =
{
    //Skip RA1, it's address pin, not WP.
	0x0001 , // 0 RA0
	0x0001 , // 1 RB0
	0x0002 , // 2 RB1
	0x0004 , // 3 RB2
	0x0008 , // 4 RB3
	0x0004 , // 5 RA2
	0x0008 , // 6 RA3
        0x0010 , // 7 RB4
	0x0010 , // 8 RA4
	0x0020 , // 9 RB5
	0x0040 , // 10 RB6
	0x0080 , // 11 RB7
	0x0100 , // 12 RB8
	0x0200 , // 13 RB9
	0x0400 , // 14 RB10
	0x0800 , // 15 RB11
	0x1000 , // 16 RB12
	0x2000 , // 17 RB13
	0x4000 , // 18 RB14
	0x8000 , // 19 RB15
};
const uint8_t pinPPSInputMap[NUMBER_OF_PHYSICAL_PINS] =
{
    //Skip RA1, it's address pin, not WP.
	26 , // 0 RA0
	0 , // 1 RB0
	1 , // 2 RB1
	2 , // 3 RB2
	3 , // 4 RB3
	0xFF , // 5 RA2
	0xFF , // 6 RA3
        4 , // 7 RB4
	0xFF , // 8 RA4
	5 , // 9 RB5
	6 , // 10 RB6
	7 , // 11 RB7
	8 , // 12 RB8
	9 , // 13 RB9
	10 , // 14 RB10
	11 , // 15 RB11
	12 , // 16 RB12
	13 , // 17 RB13
	14 , // 18 RB14
	15 , // 19 RB15
};

uint8_t ADC1Semaphore = RESOURCE_AVAILABLE;
uint8_t DMA5Semaphore = RESOURCE_AVAILABLE;
uint8_t SPI1Semaphore = RESOURCE_AVAILABLE;
uint8_t TMR1Semaphore = RESOURCE_AVAILABLE;
uint8_t TMR3Semaphore = RESOURCE_AVAILABLE;
uint8_t UART1Semaphore = RESOURCE_AVAILABLE;
uint8_t UART2Semaphore = RESOURCE_AVAILABLE;



void SetPPSOutput(uint8_t pin, uint8_t value)
{
    switch (pin)
    {

    	case 0:
	{
		RPOR13bits.RP26R = value;
	}
	break;


    	case 1:
	{
		RPOR0bits.RP0R = value;
	}
	break;
	case 2:
	{
		RPOR0bits.RP1R = value;
	}
	break;

    	case 3:
	{
		RPOR1bits.RP2R = value;
	}
	break;


    	case 4:
	{
		RPOR1bits.RP3R = value;
	}
	break;


    	case 7:
	{
		RPOR2bits.RP4R = value;
	}
	break;


    	case 9:
	{
		RPOR2bits.RP5R = value;
	}
	break;


    	case 10:
	{
		RPOR3bits.RP6R = value;
	}
	break;


    	case 11:
	{
		RPOR3bits.RP7R = value;
	}
	break;


    	case 12:
	{
		RPOR4bits.RP8R = value;
	}
	break;


    	case 13:
	{
		RPOR4bits.RP9R = value;
	}
	break;


    	case 14:
	{
		RPOR5bits.RP10R = value;
	}
	break;


    	case 15:
	{
		RPOR5bits.RP11R = value;
	}
	break;


    	case 16:
	{
		RPOR6bits.RP12R = value;
	}
	break;


    	case 17:
	{
		RPOR6bits.RP13R = value;
	}
	break;


    	case 18:
	{
		RPOR7bits.RP14R = value;
	}
	break;


	case 19:
	{
		RPOR7bits.RP15R = value;
	}
	break;

	default:
	{
		//DO nothing
	}
	break;


    }
    
}
uint16_t CurrentPinBitmap(void)
{
	if (CurrentPin >= NUMBER_OF_PHYSICAL_PINS)
	{

		return (0);
	}
	return (pinBitmap[CurrentPin]);

}
bool PinIsAnalogCapable(uint8_t pin);
void ConfigurePinAnalog(uint8_t pin, bool makeAnalog)
{
	if (!PinIsAnalogCapable(pin))
	{
		return;
	}
	switch (pinPort[pin])
	{
		case 0: // Port A
		{
			if (makeAnalog)
			{
				ANSELA |= pinBitmap[pin];
			}
			else
			{
				ANSELA &= ~pinBitmap[pin];
			}
		}
		break;

		case 1: //Port B
		{
			if (makeAnalog)
			{
				ANSELB |= pinBitmap[pin];
			}
			else
			{
				ANSELB &= ~pinBitmap[pin];
			}

		}
		break;
    }
}

bool PinIsAnalogCapable(uint8_t pin)
{
	switch (pin)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 17:
		case 18:
		case 19:
		case 20:
			return true;

	}

	return false;
}


uint8_t CurrentPinPort(void)
{
	if (CurrentPin >= NUMBER_OF_PHYSICAL_PINS)
	{

		return (0xFF);
	}
	return (pinPort[CurrentPin]);

}



bool ReadPin(uint8_t pin)
{
	uint16_t pinMask = 0;
	uint8_t inB = 1;
	if (pin < NUMBER_OF_PHYSICAL_PINS)
	{
		pinMask = pinBitmap[pin];
		
	     inB = pinPort[pin];
		
	}
    else
    {
        return(0);
    }

	if (inB)
	{
		if(PORTB & pinMask)
		{
			return (1);
		}
		else
		{
			return(0);
		}
	}
	else
	{
		if(PORTA & pinMask)
		{
			return (1);
		}
		else
		{
			return(0);
		}
	}


}
void PinOutput(uint8_t pin)
{
	uint16_t bitmap = pinBitmap[pin];
	uint8_t port = pinPort[pin];
	if (port == 0)
	{
		TRISA &= ~bitmap;
		ANSELA &= ~bitmap;
	}
	else if (port == 1)
	{
		TRISB &= ~bitmap;
		ANSELB &= ~bitmap;
	}

}

void PinInput(uint8_t pin)
{
	uint16_t bitmap = pinBitmap[pin];
	uint8_t port = pinPort[pin];
	if (port == 0)
	{
		TRISA |= bitmap;
		ANSELA &= ~bitmap;
	}
	else if (port == 1)
	{
		TRISB |= bitmap;
		ANSELB &= ~bitmap;
	}

}

bool CurrentPinRead()
{
	return(ReadPin(CurrentPin));
}

uint8_t pinIsPPSCapable(uint8_t pin)
{
    //TODO Future Optimization: optimize with switch
    if (pin >=9 && pin <= 19)
	{
		return (1);
	}
	if (pin >= 0 && pin <=4)
	{
		return (1);
	}
    if (pin == 7)
    {
        return(1);
    }
	
	return (0);

}


void SetPin(uint8_t pin, uint8_t pinState)
{
	uint16_t pinMask = 0;
	bool inB ;

	if (pin >= NUMBER_OF_PHYSICAL_PINS)
	{
		return;
	}

	pinMask = pinBitmap[pin];
	
		inB = pinPort[pin];

	if (pinState == DIGITAL_INPUT)
	{


		if (inB)
		{
			TRISB |= pinMask;
		}
		else
		{
			TRISA |= pinMask;
		}
	}
	else 

	if (pinState == DIGITAL_LOW)
	{
		pinMask = ~pinMask;
		if (pinIsPPSCapable(pin))
		{
			SetPPSOutput(pin,0);
			if (inB)
			{
				TRISB &= pinMask;
			}
			else
			{
				TRISA &= pinMask;
			}
		}
		else
		{

			if (inB)
			{
				and128(OutputArrayB,pinMask);
				LATB &= pinMask;
				TRISB &= pinMask;
			}
			else
			{
				and128(OutputArrayA,pinMask);
				LATA &= pinMask;
				TRISA &= pinMask;
			}
		}
	}
	else if (pinState == DIGITAL_HIGH)
	{
		if (pinIsPPSCapable(pin))
		{
			SetPPSOutput(pin,25);
			if (inB)
			{
				TRISB &= ~pinMask;
			}
			else
			{
				TRISA &= ~pinMask;
			}
		}
		
		else
		{	
			if (inB)
			{
				or128(OutputArrayB,pinMask);
				LATB |= pinMask;
				TRISB &= ~pinMask;
			}
			else
			{
				or128(OutputArrayA,pinMask);
				LATA |= pinMask;
				TRISA &= ~pinMask;
			}
		}
	}
}

void CurrentPinInput()
{
    PinInput(CurrentPin);
}

void CurrentPinAnalog()
{
    uint16_t bitmap = CurrentPinBitmap();
	uint8_t port = CurrentPinPort();
	if (port == 0)
	{
		TRISA |= bitmap;
		ANSELA |= bitmap;
	}
	else if (port == 1)
	{
		TRISB |= bitmap;
		ANSELB |= bitmap;
	}
}


void SetPinQuick(uint8_t pin, uint8_t pinState)
{
    SetPin(pin,pinState);
    
}

void SetCurrentPin(uint8_t pinState)
{
    SetPin(CurrentPin,pinState);
}
void PinLow(uint8_t pin)
{
	SetPin(pin,DIGITAL_LOW);
}

void PinHigh(uint8_t pin)
{
	SetPin(pin,DIGITAL_HIGH);
}


void SetPinPullUp(uint8_t pin, bool isPulledUp)
{
    if (pin >= NUMBER_OF_PHYSICAL_PINS)
    {
        return;
    }
    switch (pinPort[pin])
    {
        case 0:
            //PORT A
            if (isPulledUp)
            {
                IOCPUA |= pinBitmap[pin];
            }
            else
            {
                IOCPUA &= ~pinBitmap[pin];
            }
            break;
        case 1:
            //PORT B
            if (isPulledUp)
            {
                IOCPUB |= pinBitmap[pin];
            }
            else
            {
                IOCPUB &= ~pinBitmap[pin];
            }
        break;
    }
}

void SetPinPullDown(uint8_t pin, bool isPulledDown)
{
     if (pin >= NUMBER_OF_PHYSICAL_PINS)
    {
        return;
    }
    switch (pinPort[pin])
    {
        case 0:
            //PORT A
            if (isPulledDown)
            {
                IOCPDA |= pinBitmap[pin];
            }
            else
            {
                IOCPDA &= ~pinBitmap[pin];
            }
            break;
        case 1:
            //PORT B
            if (isPulledDown)
            {
                IOCPDB |= pinBitmap[pin];
            }
            else
            {
                IOCPDB &= ~pinBitmap[pin];
            }
        break;
    }
}

void SetPinOpenDrain(uint8_t pin, bool isOpenDrain)
{
     if (pin >= NUMBER_OF_PHYSICAL_PINS)
    {
        return;
    }
    switch (pinPort[pin])
    {
        case 0:
            //PORT A
            if (isOpenDrain)
            {
                ODCA |= pinBitmap[pin];
            }
            else
            {
                ODCA &= ~pinBitmap[pin];
            }
            break;
        case 1:
            //PORT B
            if (isOpenDrain)
            {
                ODCB |= pinBitmap[pin];
            }
            else
            {
                ODCB &= ~pinBitmap[pin];
            }
        break;
    }
}
void PinPullUp(uint8_t pin)
{
    SetPinPullDown(pin,false);
    SetPinPullUp(pin,true);
}
void PinNoPullUp(uint8_t pin)
{
    SetPinPullUp(pin,false);
}
void PinPullDown(uint8_t pin)
{
    SetPinPullUp(pin,false);
    SetPinPullDown(pin,true);    
}



void PinNoPullDown(uint8_t pin)
{
    SetPinPullDown(pin,false);
}

void PinOD(uint8_t pin)
{
    SetPinOpenDrain(pin,true);
}

void PinNoOD(uint8_t pin)
{
    SetPinOpenDrain(pin,false);
}


void CurrentPinHigh()
{
    PinHigh(CurrentPin);
}

void InitializePinLow(uint8_t pin)
{
   
	uint16_t pinMask = 0;
	bool inB ;

	if (pin >= NUMBER_OF_PHYSICAL_PINS)
	{
		return;
	}

	pinMask = pinBitmap[pin];
	
		inB = pinPort[pin];

	
		pinMask = ~pinMask;
        {

			if (inB)
			{
				and128(OutputArrayB,pinMask);
				LATB &= pinMask;
				TRISB &= pinMask;
			}
			else
			{
				and128(OutputArrayA,pinMask);
				LATA &= pinMask;
				TRISA &= pinMask;
			}
		}
		if (pinIsPPSCapable(pin))
		{
			SetPPSOutput(pin,0);
		
		}
        PinOutput(pin);	
}

void InitializePinHigh(uint8_t pin)
{

	uint16_t pinMask = 0;
	bool inB ;

	if (pin >= NUMBER_OF_PHYSICAL_PINS)
	{
		return;
	}

	pinMask = pinBitmap[pin];
	
		inB = pinPort[pin];

	
		
        {

			if (inB)
			{
				or128(OutputArrayB,pinMask);
                LATB |= pinMask;
			}
			else
			{
				or128(OutputArrayA,pinMask);
                LATA |= pinMask;
			}
		}
        if (pinIsPPSCapable(pin))
		{
			SetPPSOutput(pin,0);
		
		}
        PinOutput(pin);	
}

void CurrentPinLow()
{
    PinLow(CurrentPin);
}
void CurrentPinPullUp()
{
    PinPullUp(CurrentPin);
}

void CurrentPinNoPullUp()
{
    SetPinPullUp(CurrentPin,false);

}

void CurrentPinPullDown()
{
    PinPullDown(CurrentPin);
}

void CurrentPinNoPullDown()
{
        SetPinPullDown(CurrentPin,false);
}

const uint8_t WombatPinToADCChannel[NUMBER_OF_PHYSICAL_PINS] =
{
    0, //WP0
    2,
    3,
    4,
    5,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    8,
    7,
   6, 
    9,
};

void InitializePinInput(uint8_t pin)
{
    // TODO anything to do here for SW18AB?
}

void deactivateOutputDMA(uint8_t pin)
{
    // TODO anything to do here for SW18AB?
}