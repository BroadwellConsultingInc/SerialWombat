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

#ifndef SW_FEATURE_ENABLE_H
#define SW_FEATURE_ENABLE_H

// Note that byte sizes are approximate.  Functions that call in new
// other modules such as queue or timing resources may vary depending on
// if other pin modes are already using those modules or if they need
// to be added

	#define	PIN_MODE_DIGITAL_IO_ENABLE
//	#define	PIN_MODE_ANALOGINPUT_ENABLE
//	#define	PIN_MODE_SERVO_ENABLE // 672 bytes
//	#define	PIN_MODE_THROUGHPUT_CONSUMER_ENABLE
// 	#define	PIN_MODE_QUADRATURE_ENC_ENABLE  //634 bytes
// 	#define	PIN_MODE_HBRIDGE_ENABLE   //956 bytes
//	#define	PIN_MODE_WATCHDOG_ENABLE
//	#define	PIN_MODE_PROTECTEDOUTPUT_ENABLE
//	#define	PIN_MODE_COUNTER_ENABLE
//	#define	PIN_MODE_DEBOUNCE_ENABLE  //320 bytes
//     #define	PIN_MODE_TM1637_ENABLE  //1804 bytes
//	#define	PIN_MODE_WS2812_ENABLE
//  	#define	PIN_MODE_SW_UART_ENABLE  //1572 bytes
//	#define	PIN_MODE_INPUT_PROCESSOR_ENABLE
//	#define	PIN_MODE_MATRIX_KEYPAD_ENABLE
//	#define	PIN_MODE_PWM_ENABLE  //456 bytes
//#define	PIN_MODE_UART0_TXRX_ENABLE  //1440
//	#define	PIN_MODE_PULSE_TIMER_ENABLE  //1252 bytes
//	#define	PIN_MODE_DMA_PULSE_OUTPUT_ENABLE
//	#define	PIN_MODE_ANALOG_THROUGHPUT_ENABLE
//	#define	PIN_MODE_FRAME_TIMER_ENABLE
//	#define	PIN_MODE_TOUCH_ENABLE
//	#define	PIN_MODE_UART1_TXRX_ENABLE
//	#define	PIN_MODE_RESISTANCE_INPUT_ENABLE
//	#define	PIN_MODE_PULSE_ON_CHANGE_ENABLE  //800 Bytes
//	#define	PIN_MODE_HF_SERVO_ENABLE
//	#define	PIN_MODE_ULTRASONIC_DISTANCE_ENABLE //1048 bytes
//	#define	PIN_MODE_LIQUID_CRYSTAL_ENABLE  //1384 bytes
//	#define	PIN_MODE_HS_CLOCK_ENABLE
//	#define	PIN_MODE_HS_COUNTER_ENABLE
//	#define	PIN_MODE_VGA_ENABLE
//	#define	PIN_MODE_PS2_KEYBOARD_ENABLE  //2016 Bytes
//	#define	PIN_MODE_I2C_CONTROLLER_ENABLE
//	#define	PIN_MODE_QUEUED_PULSE_OUTPUT_ENABLE  //748 bytes
//	#define	PIN_MODE_MAX7219MATRIX_ENABLE
//	#define	PIN_MODE_FREQUENCY_OUTPUT_ENABLE



#define MOTOR_BUILD
#ifdef MOTOR_BUILD
#define PIN_MODE_ANALOGINPUT_ENABLE
#define PIN_MODE_SERVO_ENABLE // 672 bytes
#define PIN_MODE_QUADRATURE_ENC_ENABLE  //634 bytes
#define PIN_MODE_HBRIDGE_ENABLE   //956 bytes
#define PIN_MODE_PWM_ENABLE  //456 bytes
#define PIN_MODE_WATCHDOG_ENABLE
#define PIN_MODE_INPUT_PROCESSOR_ENABLE
#define PIN_MODE_FREQUENCY_OUTPUT_ENABLE
#endif

//#define FRONT_PANEL_BUILD
#ifdef FRONT_PANEL_BUILD
#define PIN_MODE_ANALOGINPUT_ENABLE
#define PIN_MODE_QUADRATURE_ENC_ENABLE
#define PIN_MODE_DEBOUNCE_ENABLE
#define PIN_MODE_PULSE_ON_CHANGE_ENABLE
#define PIN_MODE_INPUT_PROCESSOR_ENABLE
#define PIN_MODE_PWM_ENABLE
#define PIN_MODE_FREQUENCY_OUTPUT_ENABLE
#endif

//#define CAMERON_S_BUILD
#ifdef CAMERON_S_BUILD
#define PIN_MODE_QUADRATURE_ENC_ENABLE
#define PIN_MODE_DEBOUNCE_ENABLE
#define PIN_MODE_PULSE_ON_CHANGE_ENABLE
#define PIN_MODE_PWM_ENABLE
#define PIN_MODE_FREQUENCY_OUTPUT_ENABLE
#endif


//#define TM1637MATRIX_BUILD
#ifdef TM1637MATRIX_BUILD
#define PIN_MODE_TM1637_ENABLE
#define PIN_MODE_MATRIX_KEYPAD_ENABLE
#define PIN_MODE_ANALOGINPUT_ENABLE
#define PIN_MODE_QUADRATURE_ENC_ENABLE
#define PIN_MODE_DEBOUNCE_ENABLE
#endif

//#define COMMUNICATIONS_BUILD
#ifdef COMMUNICATIONS_BUILD
#define PIN_MODE_SW_UART_ENABLE
#define PIN_MODE_UART0_TXRX_ENABLE
#define PIN_MODE_QUEUED_PULSE_OUTPUT_ENABLE
#endif
 #define QUEUE_ENABLE
// #define QUEUESIMPLE

//#define SW8B_HW_PWM_ENABLE

#define OUTPUT_SCALE_ENABLE
#define OUTPUT_SCALE_HYSTERESIS_ENABLE
#define OUTPUT_SCALE_PID_ENABLE
#define OUTPUT_SCALE_RAMP_ENABLE
#define OUTPUT_SCALE_OUTPUT_FILTER_CHANGE_LIMIT_ENABLE
#define OUTPUT_SCALE_OUTPUT_FILTER_MODE_FIRST_ORDER_ENABLE



#define INPUT_PROCESS_ENABLE




#define PROTOCOL_BINARY_TEST_SEQUENCE_ENABLE
#endif

