/*
Copyright 2020 Broadwell Consulting Inc.

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

uint16_t asciiVal;
uint8_t asciiChar[5];
uint8_t ascii_to_val(uint8_t a)
{
	if ( a <= '0')
        {
		return (0);
        }
        if ( a <='9')
        {
		return ( a - '0');
        }
        if ( a >= 'A' && a <= 'F')
        {
                return ((a + 10) - 'A');
        }
        if ( a >= 'a' && a <= 'f')
        {
                return ((a + 10) - 'a');
        }
        return (0);
}


void uint16ToAscii5(uint16_t val, uint8_t* buffer)
{
	*buffer = val / 10000;
	val -= *buffer * 10000;
	*buffer += '0';
	++buffer;

	*buffer = val / 1000;
	val -= *buffer * 1000;
	*buffer += '0';
	++buffer;

	*buffer = (uint8_t)(val / 100);
	val -= *buffer * 100;
	*buffer += '0';
	++buffer;

	*buffer = (uint8_t)(val / 10);
	val -= *buffer * 10;
	*buffer += '0';
	++buffer;

	*buffer = (uint8_t)(val+ '0');
}

void uint16ToAscii5NoHWMath(uint16_t val, uint8_t* buffer)
{
    
    *buffer = '0';
    while (val >= 10000)
    {
        val -= 10000;
        ++*buffer;
    }
	++ buffer;
    *buffer = '0';
    while (val >= 1000)
    {
        val -= 1000;
        ++*buffer;
    }
    ++ buffer;
    *buffer = '0';
    while (val >= 100)
    {
        val -= 100;
        ++*buffer;
    }
    ++ buffer;
    *buffer = '0';
    while (val >= 10)
    {
        val -= 10;
        ++*buffer;
    }
    ++ buffer;
    *buffer = (uint8_t)('0' + val);
}


static void clearAsciiChar()
{
    asciiChar[0] = '0';
asciiChar[1] = '0';
asciiChar[2] = '0';
asciiChar[3] = '0';
asciiChar[4] = '0';
}
void uint16ToAscii5NoHWMathNoIndex()
{

    clearAsciiChar();
    while (asciiVal >= 10000)
    {
        asciiVal -= 10000;
        ++asciiChar[0];
    }
    while (asciiVal >= 1000)
    {
         asciiVal -= 1000;
        ++asciiChar[1];
    }
    while (asciiVal >= 100)
    {
        asciiVal -= 100;
        ++asciiChar[2];
    }
    while (asciiVal >= 10)
    {
        asciiVal -= 10;
        ++asciiChar[3];
    }

    asciiChar[4] = (uint8_t)('0' + asciiVal);
}
