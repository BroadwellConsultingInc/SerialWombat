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

#ifndef PINMODES_H
#define PINMODES_H

typedef enum 
{
	PIN_MODE_DIGITAL_IO = 0,
	PIN_MODE_CONTROLLED = 1,
	PIN_MODE_ANALOGINPUT = 2,
	PIN_MODE_SERVO = 3,
	PIN_MODE_THROUGHPUT_CONSUMER = 4,
	PIN_MODE_QUADRATURE_ENC = 5,
	PIN_MODE_HYSTERESIS = 6,
	PIN_MODE_WATCHDOG = 7,
	PIN_MODE_PROTECTEDOUTPUT = 8,
	PIN_MODE_COUNTER = 9,
	PIN_MODE_DEBOUNCE = 10,
	PIN_MODE_TM1637 = 11,
	PIN_MODE_WS2812 = 12,
	PIN_MODE_SW_UART = 13,
    PIN_MODE_INPUT_PROCESSOR = 14,
	PIN_MODE_MATRIX_KEYPAD = 15,
	PIN_MODE_PWM = 16,
	PIN_MODE_UART0_TXRX = 17,
	PIN_MODE_PULSE_TIMER = 18,
	PIN_MODE_DMA_PULSE_OUTPUT = 19,
	PIN_MODE_ANALOG_THROUGHPUT = 20,
	PIN_MODE_FRAME_TIMER = 21,
	PIN_MODE_TOUCH = 22,
	PIN_MODE_UART1_TXRX = 23,
	PIN_MODE_RESISTANCE_INPUT = 24,
            PIN_MODE_PULSE_ON_CHANGE = 25,
	    PIN_MODE_HF_SERVO = 26,
            PIN_MODE_ULTRASONIC_DISTANCE =27,
            PIN_MODE_LIQUID_CRYSTAL = 28,
}
pinMode_t;

#endif
