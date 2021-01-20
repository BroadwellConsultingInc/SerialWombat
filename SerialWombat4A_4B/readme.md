The directory Wombat16F15214.X contains the MPLAB X project for the SerialWombat 4A and 4B.  
Included are 4 project configurations, 2 each for I2C (SW4B) and UART (SW4A).  
The two versions are a standard version that targets the PIC16F15214 and a debug version
that targets the PIC16F15224, and shifts the pins from PORT A to PORT C in order to facilitate
having all 4 pins and communications attached while using an ICD4 or PICKIT4 for debugging.

The Serial Wombat 4A connects to the host via UART and supports I/O and A/D conversion on all 4 Wombat Pins.  
DIP pins 4 (RX/in) and 5(TX/out) are used for UART communication at 8-N-1.

The Serial Wombat 4B connects to the host via I2C and supports digital input functions on Wombat Pin 0, and 
I/O and A/D conversion on Wombat Pins 1-3 .  I2C SDA is on DIP pin 2, and I2C SCA is on DIP pin 3.

The Serial Wombat 4A includes ASCII based commands in addition to the binary based commands present in the Serial Wombat 4B.
This allows a human to command the Serial Wombat 4A directly from a terminal window.

The Serial Wombat 4B can act as an I2C to UART converter.

Other functionality is the same across the Serial Wombat 4A and 4B.

Pin modes for the Serial Wombat 4A and 4B include:

 - Analog to Digital Conversion with on-chip averaging and filtering
 - Input debouncing with on chip button hold time and transition count tracking
 - Protected Output mode which can quickly shut off an output if a fault is detected
 - Pulse Timer which can measure pulse or waveform high and low times with sub 8 uS precision
 - PWM output at various frequencies ranging from 31kHz to 1 Hz at 8 or 10 bit resolution depending on frequency
 - A quadrature encoder reading mode which does on-chip decoding of quadrature encoder / rotary encoder inputs
 - A servo mode which outputs servo pulses with 10 bit or bettter resolution depending on pulse length
 - A watchdog mode which can change a Serial Wombat pin and optionally reset the Serial Wombat if a countdown is not periodically serviced by the host.
 
 The Serial Wombat 4A and 4B use the PIC16F15214 bootloader developed by Broadwell Consulting Inc to allow updating the Serial Wombat firmware,
 or changing a Serial Wombat from 4A to 4B or vice-versa.
 https://github.com/BroadwellConsultingInc/BootloaderPIC16F15214
 
 


