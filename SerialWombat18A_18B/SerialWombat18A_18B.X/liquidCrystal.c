/*
Copyright 2021 Broadwell Consulting Inc.

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

/*! \file liquidCrystal.c
 */
#include <stdint.h>
#include "serialWombat.h"
#include "outputScale.h"


typedef struct lcd_n{
       uint8_t rowIndexes[8];
    uint16_t bufferIndex;
	uint8_t state;
	uint8_t RSpin;
	uint8_t D4pin;
	uint8_t D5pin;
	uint8_t D6pin;
	uint8_t D7pin;
    uint8_t e2pin;
    uint8_t displayControl;
    uint8_t displayMode;
    uint8_t width;
    uint8_t rows;
 
}lcd_t;

#define  lcd ((lcd_t*) CurrentPinRegister)

void lcd_setdata(uint8_t a) {  
	CurrentPinHigh();
	SetPin(lcd->D4pin,(a & 0x10) > 0) ; 
	SetPin(lcd->D5pin,(a &0x20) > 0);
        SetPin(lcd->D6pin,(a & 0x40)> 0) ; 
	SetPin(lcd->D7pin,(a & 0x80) > 0);
	CurrentPinLow();

	CurrentPinHigh();
	SetPin(lcd->D4pin,(a & 0x01)> 0) ; 
	SetPin(lcd->D5pin,(a &0x02) > 0);
        SetPin(lcd->D6pin,(a & 0x04)> 0) ; 
	SetPin(lcd->D7pin,(a & 0x08)> 0 );
	CurrentPinLow();
}

void lcd_setdata2(uint8_t a) {  
	SetPin(lcd->e2pin,1);
	SetPin(lcd->D4pin,(a & 0x10) > 0) ; 
	SetPin(lcd->D5pin,(a &0x20) > 0);
        SetPin(lcd->D6pin,(a & 0x40)> 0) ; 
	SetPin(lcd->D7pin,(a & 0x80) > 0);
	SetPin(lcd->e2pin,0);

	SetPin(lcd->e2pin,1);
	SetPin(lcd->D4pin,(a & 0x01)> 0) ; 
	SetPin(lcd->D5pin,(a &0x02) > 0);
        SetPin(lcd->D6pin,(a & 0x04)> 0) ; 
	SetPin(lcd->D7pin,(a & 0x08)> 0 );
	SetPin(lcd->e2pin,0);
}


static void clock_data(uint8_t data);
static void clock_cmd(uint8_t data) ;
static void clock_data2(uint8_t data);
static void clock_cmd2(uint8_t data) ;

static void delay_cycles16(uint16_t i)
{
    volatile uint16_t x;
    for (x = 0; x < i; ++x);
}
void initLiquidCrystal(void)
{
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_LIQUID_CRYSTAL)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    
    switch (Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:
	{
            CurrentPinRegister->generic.mode = PIN_MODE_LIQUID_CRYSTAL;
		//Set up pins
		lcd->state = 161;
		lcd->RSpin = (Rxbuffer[3]);
		SetMode(lcd->RSpin, PIN_MODE_CONTROLLED);
        PinLow(Rxbuffer[3]);
		lcd->D4pin = (Rxbuffer[4]);
		SetMode(lcd->D4pin, PIN_MODE_CONTROLLED);
		lcd->D5pin = (Rxbuffer[5]);
		SetMode(lcd->D5pin, PIN_MODE_CONTROLLED);
		lcd->D6pin = (Rxbuffer[6]);
		SetMode(lcd->D6pin, PIN_MODE_CONTROLLED);
		lcd->D7pin = (Rxbuffer[7]);
		SetMode(lcd->D7pin, PIN_MODE_CONTROLLED);
        CurrentPinLow();
        PinLow(Rxbuffer[3]);
        PinLow(Rxbuffer[4]);
        PinLow(Rxbuffer[5]);
        PinLow(Rxbuffer[6]);
        PinLow(Rxbuffer[7]);
        lcd->displayControl = 0x04  ; //Display on, Cursor off, blink off, Entry left, decrement
        lcd->displayMode = 0x02 /*entryLeft*/ | 0x00 /*EntryShiftDecrement*/;
        lcd->bufferIndex = 0xFFFF;
        lcd->width = 40;
        lcd->e2pin = 255;
        
	}
        break;
        case CONFIGURE_CHANNEL_MODE_1:
	{
		//clock in address plus 4 bytes 
			    Rxbuffer[3] |= 0x80;
			    clock_cmd(Rxbuffer[3]);
			    delay_cycles16(500);
			    clock_data(Rxbuffer[4]);
			    delay_cycles16(500);
			    clock_data(Rxbuffer[5]);
			    delay_cycles16(500);
			    clock_data(Rxbuffer[6]);
			    delay_cycles16(500);
			    clock_data(Rxbuffer[7]);

			

	}
        break;
        case  CONFIGURE_CHANNEL_MODE_2:
	{
		uint8_t i = Rxbuffer[3];
			//Set CGRAM location
			clock_cmd(0x40 | (i & 0x3F));
			    delay_cycles16(500);
			clock_data(Rxbuffer[4]);
			    delay_cycles16(500);
			clock_data(Rxbuffer[5]);
			    delay_cycles16(500);
			clock_data(Rxbuffer[6]);
			    delay_cycles16(500);
			clock_data(Rxbuffer[7]);

	}
        break;
        
        case  CONFIGURE_CHANNEL_MODE_3:
	{
        if (Rxbuffer[3] == 0)
        {
		//Configure displayControl
        lcd->displayControl &= Rxbuffer[4];
        lcd->displayControl |= Rxbuffer[5];
        clock_cmd(lcd->displayControl | 0x08);
        }
        else if (Rxbuffer[3] == 1)
        {
             lcd->displayMode &= Rxbuffer[4];
        lcd->displayMode |= Rxbuffer[5];
        clock_cmd(lcd->displayMode | 0x04);
        }
	}
        break;
        case  CONFIGURE_CHANNEL_MODE_4:
	{
		if (Rxbuffer[3] == 1)
		{
			clock_cmd(Rxbuffer[4]);
		}
		else if (Rxbuffer[3] == 2)
		{
			clock_data(Rxbuffer[4]);
		}
			    delay_cycles16(500);
		if (Rxbuffer[5] == 1)
		{
			clock_cmd(Rxbuffer[6]);
		}
		else if (Rxbuffer[5] == 2)
		{
			clock_data(Rxbuffer[6]);
		}
	}
        break;
        case  CONFIGURE_CHANNEL_MODE_5:
	{
		
		
			clock_data(Rxbuffer[3]);
            clock_data(Rxbuffer[4]);
            clock_data(Rxbuffer[5]);
            clock_data(Rxbuffer[6]);
            clock_data(Rxbuffer[7]);
		

	}
        break;
        case  CONFIGURE_CHANNEL_MODE_6:
	{				
        if (RXBUFFER16(3) <= SIZE_OF_USER_BUFFER)
        {
lcd->bufferIndex    = RXBUFFER16(3);
        }
        else
        {
             error(SW_ERROR_INVALID_PARAMETER_3);
return;
        }
if (Rxbuffer[5] > 0 && Rxbuffer[5] <= 80)
{
lcd->width = Rxbuffer[5];
}
else
{
    error(SW_ERROR_INVALID_PARAMETER_5);
return;
}
			lcd->state = 0;	
	}
        break;
        
         case  CONFIGURE_CHANNEL_MODE_7:
	{				
        lcd->e2pin = Rxbuffer[3];
        	SetPin(lcd->e2pin,0);
            lcd->state = 171;	
	}
        break;
         case  CONFIGURE_CHANNEL_MODE_8:
	{				
        lcd->rowIndexes[Rxbuffer[3]] = Rxbuffer[4];
	}
        break;
    }

}

lcd_t* debugLiquidCrystal;
void updateLiquidCrystal(void)
{
#ifdef HD44780_GENERIC_BUFFER
     uint16 actual_offset;
#endif
     debugLiquidCrystal = lcd;

     switch (lcd->state)
     {
             case 161:
	        clock_cmd(0x20);  // 4 bit interface
		++ lcd->state;
		break;
             case 162:
	        clock_cmd(0x28);  // 4bit interface, two lines
		++ lcd->state;
		break;
             case 163:
	        clock_cmd(lcd->displayControl | 0x08);  // Display On
		++ lcd->state;
		break;
             case 164:
	        clock_cmd(0x04 | lcd->displayMode);//Entry Mode
		++ lcd->state;
		break;
             case 165:
	        clock_cmd(0x80);  // Display address 0 
		++ lcd->state;
		break;
             case 166:
		clock_cmd(0x02); //Cursor home
		++ lcd->state;
		break;
             case 167:
		 ++ lcd->state;
		 break;
             case 168:
                 lcd->state = 254;
		 break;
         
           case 171:
	        clock_cmd2(0x20);  // 4 bit interface
		++ lcd->state;
		break;
             case 172:
	        clock_cmd2(0x28);  // 4bit interface, two lines
		++ lcd->state;
		break;
             case 173:
	        clock_cmd2(lcd->displayControl | 0x08);  // Display On
		++ lcd->state;
		break;
             case 174:
	        clock_cmd2(0x04 | lcd->displayMode);//Entry Mode
		++ lcd->state;
		break;
             case 175:
	        clock_cmd2(0x80);  // Display address 0 
		++ lcd->state;
		break;
             case 176:
		clock_cmd2(0x02); //Cursor home
		++ lcd->state;
		break;
             case 177:
		 ++ lcd->state;
		 break;
    case 254:
    break;
    default: 	
        if (lcd->state < 80)
        {
            uint8_t x = lcd->state % lcd->width;
            if (  x == 0)
            {
                uint8_t rowIndex = lcd->state / lcd->width;
                clock_cmd(0x80 + lcd->rowIndexes[rowIndex]);
                    delay_cycles16(500);
            }
            clock_data(UserBuffer[ lcd->bufferIndex + lcd->state ]);
            ++lcd->state;
            
            if (lcd->state == 80 && lcd->e2pin == 255)
            {
                lcd->state = 0;
            }
        }
        else if (lcd->e2pin != 255)
        {
             uint8_t x = lcd->state % lcd->width;
            if (  x == 0)
            {
                clock_cmd2(0x80 + lcd->rowIndexes[lcd->state / lcd->width ]);
                    delay_cycles16(500);
            }
            clock_data2(UserBuffer[ lcd->bufferIndex + lcd->state ]);
            ++lcd->state;
            
            if (lcd->state == 160)
            {
                lcd->state = 0;
            }
        }

	break;
	
     }
}

void clock_data(uint8_t data)
{
    		PinHigh(lcd->RSpin) ;
		lcd_setdata(data);
}
void clock_cmd(uint8_t data)
{
    		PinLow(lcd->RSpin) ;
		lcd_setdata(data);
}

void clock_data2(uint8_t data)
{
    		PinHigh(lcd->RSpin) ;
		lcd_setdata2(data);
}
void clock_cmd2(uint8_t data)
{
    		PinLow(lcd->RSpin) ;
		lcd_setdata2(data);
}




