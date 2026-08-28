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
#include <stdint.h>

typedef struct matrixKeypadSimulator_n{
    uint8_t rowPins[4];  
    uint8_t colPins[4];
    uint8_t ready;
} matrixKeypadSimulator_t;

#define matrixKeypadSimulator  ((matrixKeypadSimulator_t*) CurrentPinRegister)

/*! \brief Initialize Matrix Keypad Simulator Pin Mode

The Matrix Keypad Simulator pin mode allows a Serial Wombat chip to be placed
in parallel with an existing 4x4 matrix keypad.  The current pin is row 0.  The
other three row pins and the four column pins are provided as parameters.  Row
pins are configured as inputs with weak pull ups.  Column pins are normally high
impedance and are driven low only when a row input is low and the corresponding
key bit is set in the pin mode public data.

The pin mode public data is a 16-bit bitmap of simulated pressed keys.  The bit
mapping is row-major and matches the existing matrixKeypad pin mode:

| Bit | Key position |
|:---:|:-------------|
|0|Row 0, Column 0|
|1|Row 0, Column 1|
|2|Row 0, Column 2|
|3|Row 0, Column 3|
|4|Row 1, Column 0|
|...|...|
|15|Row 3, Column 3|

The public data bitmap is read and written using the standard Serial Wombat
public data commands.

CONFIGURE_CHANNEL_MODE_0:
-------------------------

Initialize rows 1 through 3 and columns 0 through 1.  Row 0 is Pin To Set.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC0|Row 0 Pin|PIN_MODE_MATRIX_KEYPAD_SIMULATOR|Row 1 Pin|Row 2 Pin|Row 3 Pin|Column 0 Pin|Column 1 Pin|

CONFIGURE_CHANNEL_MODE_1:
-------------------------

Initialize remaining columns.

|BYTE 0|BYTE 1|BYTE 2|BYTE 3|BYTE 4|BYTE 5|BYTE 6|BYTE 7|
|:-----|:-----|:-----|:-----|:-----|:-----|:-----|:-----|
|0xC1|Row 0 Pin|PIN_MODE_MATRIX_KEYPAD_SIMULATOR|Column 2 Pin|Column 3 Pin|Unused 0x55*|Unused 0x55*|Unused 0x55*|

\*0x55 is recommended, but any byte is acceptable.
*/

void initMatrixKeypadSimulator(void)
{
    BUILD_BUG_ON(sizeof(matrixKeypadSimulator_t) > BYTES_PER_PIN_REGISTER);

    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 &&
        CurrentPinRegister->generic.mode != PIN_MODE_MATRIX_KEYPAD_SIMULATOR)
    {
        error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
        return;
    }

    switch (Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:
        {
            uint8_t i;

            for (i = 3; i < 8; ++i)
            {
                if (Rxbuffer[i] >= NUMBER_OF_PHYSICAL_PINS && Rxbuffer[i] != 255)
                {
                    error(SW_ERROR_INVALID_PARAMETER_3 + i - 3);
                    return;
                }
            }

            CurrentPinRegister->generic.mode = PIN_MODE_MATRIX_KEYPAD_SIMULATOR;
            CurrentPinRegister->generic.buffer = 0;
            matrixKeypadSimulator->ready = 0;

            matrixKeypadSimulator->rowPins[0] = CurrentPin; 
            matrixKeypadSimulator->rowPins[1] = Rxbuffer[3];
            matrixKeypadSimulator->rowPins[2] = Rxbuffer[4];
            matrixKeypadSimulator->rowPins[3] = Rxbuffer[5];
            matrixKeypadSimulator->colPins[0] = Rxbuffer[6];
            matrixKeypadSimulator->colPins[1] = Rxbuffer[7];

            PinInput(CurrentPin);
            SetPinPullUp(CurrentPin, 1);

            for (i = 1; i < 4; ++i)
            {
                PinUpdateRegisters[matrixKeypadSimulator->rowPins[i]].generic.mode = PIN_MODE_CONTROLLED;
                PinInput(matrixKeypadSimulator->rowPins[i]);
                SetPinPullUp(matrixKeypadSimulator->rowPins[i], 1);
            }

            for (i = 0; i < 2; ++i)
            {
                PinUpdateRegisters[matrixKeypadSimulator->colPins[i]].generic.mode = PIN_MODE_CONTROLLED;
                PinInput(matrixKeypadSimulator->colPins[i]);
            }
        }
        break;

        case CONFIGURE_CHANNEL_MODE_1:
        {
            uint8_t i;

            for (i = 3; i < 5; ++i)
            {
                if (Rxbuffer[i] >= NUMBER_OF_PHYSICAL_PINS && Rxbuffer[i] != 255)
                {
                    error(SW_ERROR_INVALID_PARAMETER_3 + i - 3);
                    return;
                }
            }

            matrixKeypadSimulator->colPins[2] = Rxbuffer[3];
            matrixKeypadSimulator->colPins[3] = Rxbuffer[4];

                PinUpdateRegisters[Rxbuffer[3]].generic.mode = PIN_MODE_CONTROLLED;
                PinInput(Rxbuffer[3]);
                PinUpdateRegisters[Rxbuffer[4]].generic.mode = PIN_MODE_CONTROLLED;
                PinInput(Rxbuffer[4]);
            matrixKeypadSimulator->ready = 1;
        }
        break;

        default:
        {
            error(SW_ERROR_INVALID_COMMAND);
        }
        break;
    }
}

/*
    This pin mode assumes the Serial Wombat chip is connected in parallel
    with an existing 4x4 matrix keypad.  The row pins are inputs with weak
    pull-ups.  The column pins are normally high impedance.

    On each update, the firmware reads the four row pins.  If a row is low,
    then the external keypad scanner is assumed to be actively testing that
    row, or that row has otherwise been pulled low by the keypad circuit.
    The corresponding 4-bit slice of this pin mode's public data bitmap is
    then ORed into an active-column mask.

    Public data bits are arranged in row-major order:

        bit = row * 4 + column

    Therefore:
        bits  0..3  correspond to row 0, columns 0..3
        bits  4..7  correspond to row 1, columns 0..3
        bits  8..11 correspond to row 2, columns 0..3
        bits 12..15 correspond to row 3, columns 0..3

    After all rows are checked, any column whose bit is set in the
    active-column mask is driven low.  Columns whose bits are not set are
    released to high impedance.  This simulates pressing keys by pulling
    selected columns low only while the matching row is active, while leaving
    the physical keypad and the external scanner free to operate normally.
*/
void updateMatrixKeypadSimulator(void)
{
    uint16_t keyBitmap = CurrentPinRegister->generic.buffer;
    uint8_t columnsToPullLow = 0;
    uint8_t col;

    if (matrixKeypadSimulator->ready == 0)
    {
        return;
    }

    if (ReadPin(CurrentPin) == 0)
    {
        columnsToPullLow = (uint8_t)keyBitmap;
    }
    keyBitmap >>= 4;

    if (ReadPin(matrixKeypadSimulator->rowPins[0]) == 0)
    {
        columnsToPullLow |= (uint8_t)keyBitmap;
    }
    keyBitmap >>= 4;

    if (ReadPin(matrixKeypadSimulator->rowPins[1]) == 0)
    {
        columnsToPullLow |= (uint8_t)keyBitmap;
    }
    keyBitmap >>= 4;

    if (ReadPin(matrixKeypadSimulator->rowPins[2]) == 0)
    {
        columnsToPullLow |= (uint8_t)keyBitmap;
    }

    for (col = 0; col < 4; ++col)
    {
        if (columnsToPullLow & 1)
        {
            PinLow(matrixKeypadSimulator->colPins[col]);
        }
        else
        {
            PinInput(matrixKeypadSimulator->colPins[col]);
        }
        columnsToPullLow >>= 1;
    }
}
