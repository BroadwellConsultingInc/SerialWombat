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

#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef enum
{
	COMMAND_ASCII_ECHO = '!', //33
	COMMAND_ASCII_LINEFEED = '^',
            COMMAND_DIAGNOSTIC_MESSAGE = '@', //0x40
    COMMAND_BOOTLOAD = 'B',
	COMMAND_ASCII_RESET = 'R',
    COMMAND_ASCII_SLEEP = 'S',
	COMMAND_ASCII_VERSION = 'V',
	COMMAND_ASCII_PWM = 'W',
            	COMMAND_ASCII_SET_PUBLIC_DATA = 'd',
	COMMAND_ASCII_GET_PUBLIC_DATA = 'g',
            COMMAND_ASCII_SET_PIN = 'p',
	COMMAND_BINARY_READ_PIN_BUFFFER = 0x81,
	COMMAND_BINARY_SET_PIN_BUFFFER = 0x82,
	COMMAND_BINARY_READ_USER_BUFFER = 0x83,
	COMMAND_BINARY_WRITE_USER_BUFFER = 0x84,
	COMMAND_BINARY_WRITE_USER_BUFFER_CONTINUE = 0x85,
	COMMAND_BINARY_QUEUE_INITIALIZE= 0x90,
	COMMAND_BINARY_QUEUE_ADD_BYTES= 0x91,
	COMMAND_BINARY_QUEUE_ADD_7BYTES= 0x92,
	COMMAND_BINARY_QUEUE_READ_BYTES= 0x93,
    COMMAND_BINARY_QUEUE_GET_INFO = 0x94,
                COMMAND_BINARY_QUEUE_CLONE = 0x95,
            COMMAND_BINARY_CONFIGURE = 0x9F,
            COMMAND_BINARY_READ_RAM = 0xA0,
            COMMAND_BINARY_READ_FLASH = 0xA1,
            COMMAND_BINARY_READ_EEPROM = 0xA2,
            COMMAND_BINARY_WRITE_RAM = 0xA3,
            COMMAND_BINARY_WRITE_FLASH = 0xA4,
            COMMAND_CALIBRATE_ANALOG = 0xA5,
            COMMAND_ENABLE_2ND_UART = 0xA6,
            COMMAND_READ_LAST_ERROR_PACKET = 0xA7,
            COMMAND_UART0_TX_7BYTES = 0xB0,
            COMMAND_UART0_RX_7BYTES = 0xB1,
            COMMAND_UART1_TX_7BYTES = 0xB2,
            COMMAND_UART1_RX_7BYTES = 0xB3,
            COMMAND_BINARY_TEST_SEQUENCE = 0xB4,
            COMMAND_BINARY_RW_PIN_MEMORY = 0xB5,
            COMMAND_CAPTURE_STARTUP_SEQUENCE = 0xB6,
            COMMAND_ADJUST_FREQUENCY = 0xB7,
	CONFIGURE_CHANNEL_MODE_0 = 200, // 0xC8
	CONFIGURE_CHANNEL_MODE_1 = 201,
	CONFIGURE_CHANNEL_MODE_2 = 202,
	CONFIGURE_CHANNEL_MODE_3 = 203,
	CONFIGURE_CHANNEL_MODE_4 = 204,
	CONFIGURE_CHANNEL_MODE_5 = 205,
	CONFIGURE_CHANNEL_MODE_6 = 206,
	CONFIGURE_CHANNEL_MODE_7 = 207,
	CONFIGURE_CHANNEL_MODE_8 = 208,
	CONFIGURE_CHANNEL_MODE_9 = 209,
	CONFIGURE_CHANNEL_MODE_10 = 210,
            CONFIGURE_CHANNEL_MODE_SCALED_OUTPUT = 210,
            CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING = 211,
	CONFIGURE_CHANNEL_MODE_11 = 211,
	CONFIGURE_CHANNEL_MODE_12 = 212,
	CONFIGURE_CHANNEL_MODE_13 = 213,
	CONFIGURE_CHANNEL_MODE_14 = 214,
	CONFIGURE_CHANNEL_MODE_15 = 215,
	CONFIGURE_CHANNEL_MODE_16 = 216,
	CONFIGURE_CHANNEL_MODE_17 = 217,
	CONFIGURE_CHANNEL_MODE_18 = 218,
	CONFIGURE_CHANNEL_MODE_DISABLE = 219,
	CONFIGURE_CHANNEL_MODE_HW_0 = 220,
	CONFIGURE_CHANNEL_MODE_HW_1 = 221,
	CONFIGURE_CHANNEL_MODE_HW_2 = 222,
	CONFIGURE_CHANNEL_MODE_HW_3 = 223,
}CONFIGURE_CHANNEL_MODE_t;

#define RXBUFFER16(_a) ((uint16_t)Rxbuffer[_a] + (((uint16_t)Rxbuffer[_a+1]) <<8))
#define TXBUFFER16(_index, _value) {Txbuffer[_index] = (uint8_t)(_value & 0xFF);  Txbuffer[_index + 1] = (uint8_t)(_value >>8);}
#define RXBUFFER32(_a) ((uint32_t)Rxbuffer[_a] + (((uint32_t)Rxbuffer[_a+1]) <<8)+ (((uint32_t)Rxbuffer[_a+2]) <<16)+ (((uint32_t)Rxbuffer[_a+3]) <<24))
#define TXBUFFER32(_index, _value) {Txbuffer[_index] = (uint8_t)(_value & 0xFF);  Txbuffer[_index + 1] = (uint8_t)(_value >>8);Txbuffer[_index + 2] = (uint8_t)(_value >>16);Txbuffer[_index + 3] = (uint8_t)(_value >>24);}
#endif
