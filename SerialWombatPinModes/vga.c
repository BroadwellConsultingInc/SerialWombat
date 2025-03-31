/*
Copyright 2023 Broadwell Consulting Inc.

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
#include "serialWombat.h"
#include <stdint.h>
#include "asciiConversion.h"

/**
\file vga.c

This file/pin mode  is designed to drive a VGA monitor RGB and H and V Sync lines.  The 
output is essentially 1 bit, with the ability to change the color between 8
colors (including black) by horizonal line.  

This pin mode is unusual among SW18AB pin modes because it requires specific pins to be
used for certain things.  Pins must be:

VGA VSYNC (VGA Pin 14) -> 100 ohm Resistor -> SW Pin 18
VGA HSYNC (VGA Pin 13) -> 100 ohm Resistor ->SW Pin 17
VGA Red	 (VGA Pin 1) -> 280 ohm Resistor -> SW Pin 16
VGA Green (VGA Pin 2) -> 280 ohm Resistor -> SW Pin 15
VGA Blue (VGA Pin 3) -> 280 ohm Resistor -> SW Pin 14

Thank you to Nick Gammon who published a very informative article on driving a VGA monitor here:
http://www.gammon.com.au/forum/?id=11608

See timingResource.c for additional important code int he MCCP3 interrupt handler.

A few notes based on Nick's info:
VSYNC:  60Hz, (16666.67 uS)  pulse is 63.9uS (2 sync lines)

Vertical is 525 lines.  Each line is 31.74uS or 31500Hz
"V Back porch" is 33 lines 
Image area is 480 lines

"V Front Porch" is 10 lines

Each line is made up of 800 pixels:
a hoizontal sync pulse (96 pixels, 3.8us)
Horizontal back porch (48 pixels, 1.9us)
640 pixels: 25.39 uS
Horizontal Front porch is 16 pixels, 635 nS


The Serial Wombat 18AB chip will use the SPI data line to output the brightness signal that will be fed to the monitor.

The SPI output maxes out at 8MHz, or 125nS per bit, so that will determine how many pixels we can display.  A VGA pixel at 640 by
480 is 25.39uS long, with a total of 800 pixels per line including front and back porch areas.  
We will display 160 pixels per line, essentially combining pixels 4 at a time.
We will output 120 vertical pixels to maintain a 4:3 aspect ratio.
We will start the image 21 pixels to the right and accept a black border around the screen.

Chip resources:
SPI - Output pixels
DMA5 - Feed the SPI
OC1 - Generate vSync pulse.  Resets the vgaNextLine variable to 0 in interrupt 
MCCP3 - Generate hSync Pulse and trigger DMA and update PPS for the R/G/B output in interrupt.  Highest priority interrupt.

Set up  OC PWM with a period of 16666uS (Acutally a perfect multiple of whatever HSync is) and a pulse of 63.9 uS for v sync
Set up OC PWM with a period of 31.74 uS  and a pulse of 3.8 uS
Set up OC PWM with a period of 31.74 us and a pulse of 96 + 48 + 21 pixels and use that interrupt to fire the DMA.  DMA is 20 bytes of data, plus 1 byte of blank
End of DMA fires an interrupt which resets and updates (every 4th line) the DMA.  DMA is pointed to empty array during porches

   */


#define VGA_BYTES_PER_LINE 21   ///< 160 bits, plus a 0 at the end to pull SPI line low

#define VGA_VSYNC_PIN 18
#define VGA_HSYNC_PIN 17
#define VGA_R_PIN 16
#define VGA_G_PIN 15
#define VGA_B_PIN 14
typedef struct vga_n{
	uint8_t zeroArray[VGA_BYTES_PER_LINE];  ///< for some parts of the SPI/DMA (eg Horz Back Porch or blank lines,  we need a string of zeros.  Store it here once instead of on each line
}vga_t;

bool vgaEnable = false; ///< This global variable signals to interrupt routines to go into VGA specific code.  This is required for high performance operation;  A calling a registered function pointer takes too long

void vga_SPI1_Initialize (void)
{
 // AUDEN disabled; FRMEN disabled; AUDMOD I2S; FRMSYPW One clock wide; AUDMONO stereo; FRMCNT 0; MSSEN disabled; FRMPOL disabled; IGNROV disabled; SPISGNEXT not sign-extended; FRMSYNC disabled; URDTEN disabled; IGNTUR disabled; 
    SPI1CON1H = 0x00;
    // WLENGTH 8; 
    SPI1CON2L = 0x07;
    // SPIROV disabled; FRMERR disabled; 
    SPI1STATL = 0x00;
    // SPI1BRGL 0; 
    SPI1BRGL = 0x00;
    // SPITBFEN disabled; SPITUREN disabled; FRMERREN disabled; SRMTEN disabled; SPIRBEN disabled; BUSYEN disabled; SPITBEN disabled; SPIROVEN disabled; SPIRBFEN disabled; 
    SPI1IMSKL = 0x08; //SPITBEN generates an interrupt.
    // RXMSK 0; TXWIEN disabled; TXMSK 0; RXWIEN disabled; 
    SPI1IMSKH = 0x00;
    // SPI1URDTL 0; 
    SPI1URDTL = 0x00;
    // SPI1URDTH 0; 
    SPI1URDTH = 0x00;
    // SPIEN enabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:Low, Active:High; SSEN disabled; MSTEN Master; MODE16 enabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse precedes; CKE Idle to Active; MODE32 disabled; SPISIDL disabled; ENHBUF enabled; DISSDI disabled; 
    SPI1CON1L = 0x8021;
}


void inline VGAStartDMA(volatile uint8_t* address)
{
    DMACH5bits.CHEN = 0;
    DMACNT5 = (uint16_t)VGA_BYTES_PER_LINE;
    DMADST5 =(uint16_t) &SPI1BUFL;
    DMASRC5 = (uint16_t) address;
    DMACH5 = 0x142 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL SPI1 Transmit Interrupt; HIGHIF disabled; 
    DMAINT5= 0x2700;
}

void VGAStopDMA()
{
    DMACH5bits.CHEN = 0;
}


volatile uint16_t vgaNextLine = 0;  ///< For this we're going to use global variables for items used in the interrupt
volatile uint8_t *vgaBufferAddress; ///< Pointer to the next line of pixels we're going to clock out.  Global to increase performance, not an issue because there can be only one instance
volatile uint8_t *vgaZeroBuffer; ///<Pointer to the zero array for blank lines and such.  Global to increase performance, not an issue because there can be only one instance
uint16_t vgaFrameBuffer = 0;  ///< Offset into the User buffer where the frame is stored. Global to increase performance, not an issue because there can be only one instance 
uint8_t *vgaColorBufferAddress; ///< Pointer to the buffer location where the line-color array is stored.
volatile uint8_t vgaNextColor = 7; ///< Global to store the next color output (0 to 7).  Used so we can figure next color at the end of a line where we have some free processing time.


static void setPixel(uint8_t x, uint8_t y, uint8_t color /* 0 or 1*/)
{
	if (x >= 160 || y >= 120) // Out of range.  
	{
		return;
	}
	uint16_t offset = y * VGA_BYTES_PER_LINE; // Find the beginning of the line
	offset += x/8; // Find the beginning of the bit.
	uint8_t bitx = 0x80 >> (x & 0x07); // Get the bit (high bits get clocked out first by SPI)
	if (color)
	{
		UserBuffer[vgaFrameBuffer + offset] |= bitx;
	}
	else
	{
		UserBuffer[vgaFrameBuffer + offset] &= ~bitx;
	}
}

/*!
    \brief Initialization routine for WS2812B driver 

----


CONFIGURE_CHANNEL_MODE_0:
---------------------

Initialize VGA Driver


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC0|Pin To Set (must be 18) |0x1F (VGA Mode)  | 0x55 | 0x55 |  Frame buffer index LSB |Frame buffer index MSB  |Unused 0x55* |

\*0x55 is recommended, but any byte is acceptable


Response:

Command is echoed back.

Examples:

Set pin 18 to VGA, user buffer index of 0x180

> `0xC0 0x12 0x1F 0x55 0x55 0x80 0x01 0x55 `


CONFIGURE_CHANNEL_MODE_1:
---------------------

Draw a Primiative (Primative based on Byte 3)


Set or clear a pixel:


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set (must be 18) |0x1F (VGA Mode)  | 0 (Set pixel)  | X (0-159) |  Y (0-119) |Color (0 for black, 1 for On)  |Unused 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set Pixel (59,111) on

> `0xC1 0x12 0x1F 0x0 0x3B 0x6F 0x01 0x55 `



Fill the Screen


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set (must be 18) |0x1F (VGA Mode)  | 1 (Fill Screen)  | Color (0 for black, 1 for On)  |Unused 0x55* |Unused 0x55* |Unused 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set the screen to all black

> `0xC1 0x12 0x1F 0x1 0x00 0x55 0x55 0x55 `



Fill A Rectangle


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set (must be 18) |0x1F (VGA Mode)  | 2 (Fill Rectangle)  | Upper Left X | Upper Left Y | Lower Right X inclusive | Lower Right Y inclusive| 


Response:

Command is echoed back.

Examples:

Set Fill A rectanle from (5,10) to (20,30)

> `0xC1 0x12 0x1F 0x2 0x05 0x5A 0x14 0x1E `

Clear A Rectangle


|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC1|Pin To Set (must be 18) |0x1F (VGA Mode)  | 3 (Clear Rectangle)  | Upper Left X | Upper Left Y | Lower Right X inclusive | Lower Right Y inclusive| 


Response:

Command is echoed back.

Examples:

Set Clear A rectanle from (5,10) to (20,30)

> `0xC1 0x12 0x1F 0x3 0x05 0x5A 0x14 0x1E `

----

CONFIGURE_CHANNEL_MODE_2:
---------------------

Set Line Colors.  Each line can turn On/Off the RGB channels



|BYTE 0          |BYTE 1          |BYTE 2          |BYTE 3          |BYTE 4          |BYTE 5          |BYTE 6          |BYTE 7          |
|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|:---------------|
|0xC2|Pin To Set (must be 18) |0x1F (VGA Mode)  | Top Line to Set (0-119) | Bottom Line to set (Byte 3 to 119) |  Color ( 0 to 7 where 0x04 is R, 0x02 is G, 0x01 B )  |Unused 0x55* |

\*0x55 is recommended, but any byte is acceptable

Response:

Command is echoed back.

Examples:

Set Lines 50 to 60 to Yellow (Red and Green)

> `0xC2 0x12 0x1F 0x03 0x32 0x3C 0x06 0x55 `



*/

void initVGA (void)
{

	vga_t* vga = (vga_t*) CurrentPinRegister;

	if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_VGA)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
	switch(Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
			{

				// Claim TIMING_RESOURCE_OC1 for 60 Hz Sync
				if (timingResourceGenericClaim(TIMING_RESOURCE_OC1) != TIMING_RESOURCE_OC1)
				{
					error (SW_ERROR_HW_RESOURCE_IN_USE);
					return;
				}

				// Claim TIMING_RESOURCE_MCCP3 for HSync // using that one because it's more precise at high speeds, but can't do things like external timing
				if (timingResourceGenericClaim(TIMING_RESOURCE_MCCP3) != TIMING_RESOURCE_MCCP3)
				{
					timingResourceRelease(TIMING_RESOURCE_OC1);
					error (SW_ERROR_HW_RESOURCE_IN_USE);
					return;
				}

				vgaEnable = true;
				timingResourceDefault(TIMING_RESOURCE_OC1);
				timingResourceGenericClaim(TIMING_RESOURCE_OC1);

				timingResourceDefault(TIMING_RESOURCE_MCCP3);
				timingResourceGenericClaim(TIMING_RESOURCE_MCCP3);

				// Set up OC1 for 60Hz (16667 uS)  63.9 (64) uS High time pulse.  We'll use 16672 because it's an even multiple of the 32 uS pulse we're using for HSync
				CurrentPinLow();
				uint8_t i;
				for (i = 0; i < VGA_BYTES_PER_LINE; ++i)
				{
					vga->zeroArray[i] = 0x00;
				}

				vgaNextLine = 0;
				vgaFrameBuffer =    RXBUFFER16(5); 
				vgaBufferAddress = &UserBuffer[vgaFrameBuffer];
				vgaZeroBuffer = vga->zeroArray;
				{
					uint32_t period_uS = 16800;
					period_uS *= 2;
					period_uS -= 1;
					uint32_t highTime = 64*2;

					OC1CON2 = 0x0000 | 0x1F;
					OC1RS = period_uS;
					OC1R = highTime;
					OC1TMR = 0;       
					IFS0bits.OC1IF = false;
					IEC0bits.OC1IE = true;

					SetPPSOutput(CurrentPin,13);  // Connect pin to OC1
				}


				//Set up pin HSync to 31.74 uS = 32, so we can have a VSync that is an even multiple of HSync .  This should keep them synced forever, because any variation in
				// system clock should affect both counters equally
				{ uint16_t period_uS  = 32 * 32 - 1;  // 32 counts per uS
					CCP3CON1L = 0x0000;
					CCP3TMRL = 0;
					CCP3RA = 0;
					CCP3PRH = 0;             
					CCP3PRL = period_uS;   
					CCP3RBL =   122; // HSync pulse width, 3.8 * 32 = 121.6 = 122
					CCP3RBL =   122; // HSync pulse width, 3.8 * 32 = 121.6 = 122


					// That should take care of the VSync and HSync.

					// We're going to clock out pixels with the SPI.   In order to do that we need to start clocking bits at about 96 + 48 + 21 pixels, or 6.546 uS.  We'll use 6.5, which 
					// yields an OC time of 13.  This will kick off the DMA.
					//
					// The end of the DMA will fire an interrupt that will point the DMA to the next (or same) line

					PinLow(VGA_HSYNC_PIN);
						SetPPSOutput(VGA_HSYNC_PIN, 18);  // CCP3

					vga_SPI1_Initialize();
					PinLow(VGA_G_PIN);
					PinLow(VGA_B_PIN);
					PinLow(VGA_R_PIN);
						SetPPSOutput(VGA_G_PIN,0x0007);    //SPI pin
					OC1CON1 = 0x0006;
					CCP3CON1L = 0x8405;

					VGAStartDMA(vgaZeroBuffer);

					IPC10bits.CCT3IP = 6; // 2nd highest
					IPC0bits.OC1IP = 6;
					IPC1bits.OC2IP = 6; // 2nd highest
					IPC15bits.DMA5IP = 6; // 2nd highest
					IEC2bits.CCT3IE = 1;

					CurrentPinRegister->generic.mode = PIN_MODE_VGA;

					vgaColorBufferAddress = &UserBuffer[120 * VGA_BYTES_PER_LINE];
					{
						int x;
						for (x = 0; x < 60; ++ x)  // 2 lines per byte, 120 lines
						{

							vgaColorBufferAddress[ x ] = 0x77; // White
						}
					}

				}

			}
			break;

		case CONFIGURE_CHANNEL_MODE_1:  //Drawing primatives
			{
				switch (Rxbuffer[3])
				{
					case 0: // Set pixel
						{
							setPixel(Rxbuffer[4],Rxbuffer[5], Rxbuffer[6]);
						}
						break;

					case 1: // Fill Screen
						{
							if (Rxbuffer[4])
							{
								uint8_t x,y;
								for (y = 0; y < 120; ++y)
								{
									for (x = 0; x < VGA_BYTES_PER_LINE - 1; ++x)
									{
										UserBuffer[vgaFrameBuffer + y * VGA_BYTES_PER_LINE  + x] = 0xFF;
									}
								}
							}
							else
							{
								uint8_t x,y;
								for (y = 0; y < 120; ++y)
								{
									for (x = 0; x < VGA_BYTES_PER_LINE - 1; ++x)
									{
										UserBuffer[vgaFrameBuffer + y * VGA_BYTES_PER_LINE  + x] = 0;
									}
								}
							}

						}
						break;

					case 2: // Fill rectangle
						{
							uint8_t x,y;
							for (y = Rxbuffer[5]; y <= Rxbuffer[7];++y)
							{
								for (x = Rxbuffer[4]; x <= Rxbuffer[6]; ++x)
								{
									setPixel(x,y,1);
								}
							}
						}
						break;

					case 3: // Clear rectangle
						{
							uint8_t x,y;
							for (y = Rxbuffer[5]; y <= Rxbuffer[7];++y)
							{
								for (x = Rxbuffer[4]; x <= Rxbuffer[6]; ++x)
								{
									setPixel(x,y,0);
								}
							}
						}
						break;
				}
			}
			break;

		case CONFIGURE_CHANNEL_MODE_2: //Set line colors
			{
				uint8_t start = Rxbuffer[3];
				uint8_t end = Rxbuffer[4];
				if (start >= 120)
				{
					error(SW_ERROR_INVALID_PARAMETER_3);
					return;
				}
				if (end >= 120)
				{
					error(SW_ERROR_INVALID_PARAMETER_4);
					return;
				}
				if (Rxbuffer[5] > 7)
				{
					error(SW_ERROR_INVALID_PARAMETER_5);
				}
				if (start > end)
				{
					start = Rxbuffer[4];
					end = Rxbuffer[3];
				}
				uint8_t y;
				for (y = start; y <= end; ++y)
				{
					if (y & 1)
					{
						// Odd line
						vgaColorBufferAddress[ y/2 ] &= 0x0F; 
						vgaColorBufferAddress[ y/2 ] |= (Rxbuffer[5] <<4); 
					}
					else
					{
						vgaColorBufferAddress[ y/2 ] &= 0xF0; 
						vgaColorBufferAddress[ y/2 ] |= (Rxbuffer[5]);

					}
				}

			}
			break;
		default:
			{
				error(SW_ERROR_INVALID_PIN_COMMAND);
			}
			break;
	}
}


void VGA_dma_interrupt(void );
/// \brief update the VGA state machine
void updateVGA()
{
        // Wow, All updates are interrupt driven.  Nothing to see here.
}


volatile uint8_t vgaLineCopy = 0;  // Each line is displayed 3 times.  
volatile uint8_t vgaDisplayLine = 0;  //The current line we're displaying.
void VGA_dma_interrupt()
{
    /*
	if (vgaNextLine >= 525)
	{
		// End of screen.  Reset 
		vgaNextLine = 0;
		vgaDisplayLine = 0;
	}
     */ 
	if (vgaNextLine < 36 + 60 ) // 2 lines sync, 33 lines back porch
	{
		// Set DMA to all low array
		VGAStartDMA(vgaZeroBuffer);
		vgaLineCopy = 3;
		vgaDisplayLine = 0;
	}

	else if (vgaNextLine < 36 + 360 + 60) 
	{
		// Clock out image  		
		VGAStartDMA(vgaBufferAddress);
		--vgaLineCopy;
		vgaNextColor = vgaColorBufferAddress[ vgaDisplayLine/2];
		if (vgaDisplayLine & 1)
		{
			vgaNextColor >>= 4;
		}
		if (vgaLineCopy == 0)
		{
			vgaBufferAddress += VGA_BYTES_PER_LINE; // We're duplicating each line 4 times, and starting on line 35.
			vgaLineCopy = 3;
			++vgaDisplayLine;
		}
     //   IEC0bits.OC1IE = 1;
	}
	else
	{
		vgaBufferAddress = & UserBuffer[vgaFrameBuffer];
		// Reset the buffer address to the beginning

		VGAStartDMA(vgaZeroBuffer);
	}
	++ vgaNextLine;

}

void VGA_dma_interrupt(void);

void __attribute__ ( ( interrupt, no_auto_psv ) ) _DMA5Interrupt( void )
{
	//Finished clocking out a line.  Shut off the DMA, and get it set up for the next line.
	IEC3bits.DMA5IE = 0;
	IFS3bits.DMA5IF = 0;
	VGA_dma_interrupt();	
}



