/*
Copyright 2024-2025 Broadwell Consulting Inc.

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
#include "swMath.h"
#include <stdint.h>

uint16_t xyInterpolationU16(uint16_t x, uint16_t xl,uint16_t yl, uint16_t xh, uint16_t yh)
{
	if (x <= xl)
	{
		return yl;
	}
	if (x >= xh)
	{
		return (yh);
	}
	 int32_t rise = ((int32_t)yh)- yl;
	 int32_t run = ((int32_t)xh)-xl;
	 int32_t val = ((int32_t)x)-xl;
	if ((val & 0x8000) && (rise & 0x8000))
	{
	    rise >>= 1; // Prevent multiplication overflow
	    run >>= 1;
	}
	val *= rise;
	val /= run;
	val += yl;
	return val;
		

}

