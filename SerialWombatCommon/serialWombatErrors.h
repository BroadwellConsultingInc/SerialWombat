/*
Copyright 2020-2021 Broadwell Consulting Inc.

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
#ifndef _SERIAL_WOMBAT_ERROR_
#define _SERIAL_WOMBAT_ERROR_
typedef enum {
    SW_ERROR_UNNUMBERED_ERROR = 32767,
    SW_ERROR_PINS_MUST_BE_ON_SAME_PORT = 1, ///< Pins must be on the same microcontroller part (e.g. PORTA, PORTB, etc.).  See datasheet of micro for port assignments.
    SW_ERROR_ASCII_NUMBER_TOO_BIG_16 = 2, ///<A number bigger than 65535 was provided to convert to a 16 bit value
            SW_ERROR_UNKNOWN_PIN_MODE = 3, ///< A Pin mode was indicated that is not avaialble on this model or version of Serial Wombat chip
            SW_ERROR_RESET_STRING_INCORRECT = 4, ///<A Packet starting with 'R' was received but didn't have the correct following bytes to cause a reset
            SW_ERROR_INVALID_COMMAND = 5, ///< The first byte of a received packet does not correspond with a command supported by this model of Serial Wombat chip
            SW_ERROR_INSUFFICIENT_SPACE = 6,  ///< There was not sufficient space in the queue or user area to complete the command.
            SW_ERROR_WUB_COUNT_GT_4 = 7, ///< A count greater than 4 was provided as a number of bytes to write to count user buffer
            SW_ERROR_WUB_INVALID_ADDRESS = 8, ///<An attempt to write to a user buffer address outside the user buffer was attempted.
            SW_ERROR_WUB_CONTINUE_OUTOFBOUNDS = 9, ///<  A call to Write User Buffer Continue would have written out of bounds.
            SW_ERROR_RF_ODD_ADDRESS = 10, ///< Addresses Read From Flash must be even.
            SW_ERROR_FLASH_WRITE_INVALID_ADDRESS = 11, ///<An attempt to write or erase flash was made to a protected or non-existant area
	    SW_ERROR_INVALID_PIN_COMMAND = 12, ///< The pin command 0xC1, 0xC2, etc is not suported by this pin mode (May vary by model)
            SW_ERROR_PIN_CONFIG_WRONG_ORDER = 13, ///<The called pin command 0xC1, 0xC2 was called before other required prior commands (e.g. 0xC0)
            SW_ERROR_WS2812_INDEX_GT_LEDS = 14, ///<The command references an index that is greater or equal to the number of leds
            SW_ERROR_PIN_NOT_CAPABLE = 15, ///<The commanded pin does not have the hardware support to perform the commanded pin mode
	    SW_ERROR_HW_RESOURCE_IN_USE = 16, ///<The requested hardware or software resource in use has already been exclusively claimed by another pin
            SW_ERROR_INVALID_PARAMETER_3 = 17, ///<The pin configuration parameter in Byte 3 was invalid
            SW_ERROR_INVALID_PARAMETER_4 = 18, ///<The pin configuration parameter in Byte 4 was invalid
            SW_ERROR_INVALID_PARAMETER_5 = 19, ///<The pin configuration parameter in Byte 5 was invalid
            SW_ERROR_INVALID_PARAMETER_6 = 20, ///<The pin configuration parameter in Byte 6 was invalid
            SW_ERROR_INVALID_PARAMETER_7 = 21, ///<The pin configuration parameter in Byte 7 was invalid
            SW_ERROR_PIN_NUMBER_TOO_HIGH = 22, ///<The pin number indicated was greater than the greatest avaialable pin
            SW_ERROR_PIN_IS_COMM_INTERFACE = 23, ///<The pin number indicated is currently being used for Serial Wombat protocol communicaitons
            SW_ERROR_ANALOG_CAL_WRONG_UNLOCK = 24, ///<The unlock value provided to write analog calibration was incorrect.
            SW_ERROR_2ND_INF_WRONG_UNLOCK = 25, ///<The unlock value provided to enable the 2nd interface was incorrect.
            SW_ERROR_2ND_INF_UNAVAILABLE = 26, ///<The 2nd interface hardware was not avaialble to claim
            SW_ERROR_UART_NOT_INITIALIZED = 27, ///<A UART operation was requested but the UART was not intialized
            SW_ERROR_CMD_BYTE_1 = 28, ///< Byte 1 of the command was invalid
            SW_ERROR_CMD_BYTE_2 = 29, ///< Byte 2 of the command was invalid
            SW_ERROR_CMD_BYTE_3 = 30, ///< Byte 3 of the command was invalid
            SW_ERROR_CMD_BYTE_4 = 31, ///< Byte 4 of the command was invalid
            SW_ERROR_CMD_BYTE_5 = 32, ///< Byte 5 of the command was invalid
            SW_ERROR_CMD_BYTE_6 = 33, ///< Byte 6 of the command was invalid
            SW_ERROR_CMD_BYTE_7 = 34, ///< Byte 7 of the command was invalid
            SW_ERROR_CMD_UNSUPPORTED_BAUD_RATE = 35, ///< invalid baud rate enumeration    
            SW_ERROR_QUEUE_RESULT_INSUFFICIENT_USER_SPACE = 36,
	SW_ERROR_QUEUE_RESULT_UNALIGNED_ADDRESS = 37,
	SW_ERROR_QUEUE_RESULT_INVALID_QUEUE = 38,
	SW_ERROR_QUEUE_RESULT_FULL = 39,
	SW_ERROR_QUEUE_RESULT_EMPTY = 40,
	SW_ERROR_DATA_NOT_AVAILABLE = 41,
            SW_ERROR_TM1637_WRONG_MODE = 42, ///< The TM1637 pin is configured for the wrong TM1637 mode to process the command
           SW_ERROR_RUB_INVALID_ADDRESS = 43, ///<An attempt to read user buffer address outside the user buffer was attempted.
            SW_ERROR_UNKNOWN_OUTPUTSCALE_COMMAND = 44, ///< The command index for an output scaling command is not supported on this firmware
            SW_ERROR_UNKNOWN_INPUT_PROCESS_COMMAND = 45, ///< The command index for an inputProcess command is not supported on this firmware
	    SW_ERROR_PULSE_ON_CHANGE_ENTRY_OUT_OF_RANGE = 46, ///< The pulse on change entry number exceeded the number of entries
	    SW_ERROR_PULSE_ON_CHANGE_UNKNOWN_MODE = 47, // The pulse on change Mode requested is unknown
            SW_ERROR_UNKNOWN_QUEUE_TYPE = 48, ///< This Queue type is not supported on this firwmare
            SW_ERROR_CAPTURE_PACKET_WRONG = 49, ///< The capture packet did not have the correct protection bytes
	    SW_ERROR_PS2KB_WRONG_MODE = 50, ///< The command issued is not available for the current Queue mode
}SW_ERROR_t;

#endif
