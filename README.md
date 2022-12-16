# Serial Wombat

What is a Serial Wombat chip?  What is the Serial Wombat firmware?
------------------------

The Serial Wombat project is a line of microcontroller firmwares designed to extend the capabilities of single board computers such as Arduino boards and the Raspberry Pi or a PC or other smart device.  Support libraries are available for Arduino, Raspberry Pi (Python) and .Net (C#).

The Serial Wombat firmware is an open-source, MIT Licensed project developed by Broadwell Consulting Inc. to showcase and promote the embedded systems capabilities of the company.  

*Serial Wombat* is a registered trademark of Broadwell Consulting Inc. in the United States.  See SerialWombat.com for usage guidelines.

This page explains the inner workings of the Serial Wombat firmware.  If you just want to access it with the Arduino Library or Raspberry Pi Python Package (available soon) read the next few paragraphs then go to that area and read about the API.

A Serial Wombat chip is not programmed for a given application by the end user.  It is pre-programmed with general-purpose firmware, and configured at run time to make the hardware resources of the microcontroller available for command by the host in ways that solve common embedded systems problems.

Why would I use a Serial Wombat Chip?
--------------------------------

* Because you need more I/O
* Because you need more A/D Conversion channels
* Because trying to do multiple things at once is making your software hard to write
* Because you don't want to try to figure out how to merge multiple existing low-level/interrupt based Arduino libraries to make them work together
* Because your system doesn't have enough specialized pins like PWM or Interrupts
* Because you want to mimize the number of wires running somewhere like a front control panel to just power, ground and communications
* Because you want your hardware design to be easily portable between Arduino variants, Raspberry Pi, or any other platform with an I2C or UART interface

**The Serial Wombat does what other expansion chips do, but smarter**


A Serial Wombat chip could be used for many of the same tasks as an MCP3008 ADC converter, such as adding Analog to Digital Conversion to a Raspberry Pi.  Both have 10-Bit ADC capability.  However, only the Serial Wombat chip and firmware is capable of taking many sequential measurements and averaging or performing first-order filtering without additional effort by the host.

The Serial Wombat chip is also a potential replacement for the MCP23017.  Like the MCP23017, the Serial Wombat 4A and 4B (SW4A and SW4B) chips provide operation up to 5.5V with the ability to talk to a 3.0 or 3.3V host over I2C.  Both provide 25mA of sink and source current per pin, with open drain and weak pull up options available.  However, the Serial Wombat chip uses onboard firmware to allow functions like Quadrature Encoder reading, Servo driving, PWM output, and pulse width / duty cycle measurement without additional help from the host.  Serial Wombat 4A and 4B chips allow 4 pins to be added with each chip, with multiple chips possible on the same bus in the case of the I2C based SW4B.  The forthcoming Serial Wombat 18AB chip will provide 18 pins, 10 of which will be A/D capable.

**Serial Wombat Chips offload tasks your single-board computer could do itself so they're faster, smoother, or easier**

Pins on the Serial Wombat chip can be assigned tasks fairly independently.  A single Serial Wombat 4A chip could have 4 A/D pins, or 2 A/D pins and a quadrature encoder, or an A/D, a button, and two servo drivers or any other combination.  All your program has to do is configure the pins at startup, then only check in with the Serial Wombat chip when you want a status update on an input or need to change an output.  All the while, the Serial Wombat chip is doing what it takes to drive the output or process the input.  


What Serial Wombat Chips are Available?
---------------------------------

| Model                        | SW4A                                                                            | SW4B                                                                            | SW18AB                   |
|------------------------------|---------------------------------------------------------------------------------|---------------------------------------------------------------------------------|---------------------------------------------------------|
| Availability                 | Future                                                                         | Now                                                                             | April 11, 2022 KS Launch                                            |
| Interface                    | UART                                                                            | I2C                                                                             | UART  or I2C                                                    |
| Package                      | DIP 8                                                                           | DIP 8                                                                           | DIP 28 (300 mil)                                             |
| I/O Pins                     | 4 I/O                                                                           | 3 I/O, 1 input                                                                  | 18 I/0                                                            |
| A/D Pins                     | 4  (10-bit)                                                                     | 3 (10-bit)                                                                      | 7 in I2C mode,<BR> 9 in UART Mode                                         |
| D/A Pins                     | 0                                                                               | 0                                                                               | 1 (5-bit)                                                                                  |
| Operating Voltage            | 2.5-5.5V                                                                        | 2.7-3.3V                                                                        | 2.5-3.6                                                                                     |
| Current Per pin              | 25mA                                                                            | 25mA                                                                            | 25mA <BR> (200 mA max per chip)                                                   |
| Required External Components | 1x 100nF Capacitor                                                              | 1x 100nF Capacitor                                                              | 2x 100nF Capacitor<BR> 1x 10uF Capacitor<BR> 1x 10k Resistor<BR> | 
| Operating Current            | < 4mA                                                                           | < 4mA                                                                           | TBD                                                     | TBD                                                     |
| Sleep Current                | < 750 uA                                                                        | < 750 uA                                                                        | TBD                                                     | TBD                                                     |
| Internal Temperature Sensor  | No                                                                              | No                                                                              | Yes, Low Accuracy    |
| Pin Modes                    | Digital I/O<BR> ADC<BR> Debounce<BR> Protected Output<BR> Pulse Timer<BR> PWM<BR> Servo<BR> Watchdog | Digital I/O<BR> ADC<BR> Debounce<BR> Protected Output<BR> Pulse Timer<BR> PWM<BR> Servo<BR> Watchdog <BR>I2C to UART | All Classes listed<BR> in Arduino class list                            |                       
  
Resources
---------
**Many tutorial and cookbook videos are available on YouTube that demonstrate how to use the Serial Wombat family.**

[Check out the Serial Wombat Playlist on Broadwell Consulting Inc's YouTube Channel.](https://www.youtube.com/playlist?list=PL9_vji2WbJGjNSjp9rnOrdrNzMCQIjaj_)

**Integration with common platforms is easy with pre-written libraries.**

A full-featured Arduino library with multiple examples and tutorial videos is available now:

at https://broadwellconsultinginc.github.io/SerialWombatArdLib/
or download it from the Library Manager in the Arduino IDE .

A Raspberry Pi Python package is in development.

A C# library is also nearly finished and will be released soon.


SW4A / SW4B FIRMWARE ARCHITECTURE
=====================
The Serial Wombat 4A and 4B firmware runs on the PIC16F15214 microcontroller.  It is designed for the PRO version of the XC8 compiler, and the MPLAB X development environment.

You can compile the firmware yourself and program chips using a PICKIT or similar programming device, or you can buy preprogrammed kits from Broadwell Consulting Inc on Amazon.

The Serial Wombat binary image / Hex File is made up of two separate projects: A bootloader project and a Serial Wombat firmware project.
  
An overview of the bootloadwer is available here:

  [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/OfW4hHFVy3U/0.jpg)](https://www.youtube.com/watch?v=OfW4hHFVy3U)

SW18AB FIRMWARE ARCHITECTURE
=====================
The Serial Wombat 18AB firmware runs on the PIC24FJ256GA702 microcontroller.  It is designed for the free version of the XC16 compiler, and the MPLAB X development environment.

A video that goes over the Serial Wombat Code design and how to modify it is availale here:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/PNPlAaIrR1o/0.jpg)](https://www.youtube.com/watch?v=PNPlAaIrR1o)



You can compile the firmware yourself and program chips using a PICKIT4 or similar programming device, or you can buy preprogrammed kits from Broadwell Consulting Inc at https://www.SerialWombat.com .

The Serial Wombat binary image / Hex File is made up of two separate projects: A bootloader project and a Serial Wombat firmware project.

Executive Structure
-------------------

The Serial Wombat firmware is a foreground / background loop system.  Important hardware based events and communications Receive and Transmit to/from queues is done using interrupts.

The main loop runs a loop with a foreground subroutine that is run every 1 mS based on a flag which is set in a 1mS hardware timer.  Inbetween runs of the foreground subroutine the communication receive queue is checked to see if a new command from the host is ready to be processed.  If so, it is processed in its entirety and a response is generated and put into the transmit queue.  It is possiblefor the start of the foreground subroutine to be delayed by some microseconds by the communication processing routine.

The main job of the foreground subroutine is to service state machines for the Serial Wombat pins.  Each pin has its own state machine and memory area.  Each pin's state machine is serviced every 1 mS by the executive.  Actual time between servicings will vary due to execution time variation.  For instance, one call may be 1100 uS after the previous, then the next call 800 uS after that.  But over time it will average out to 1 mS.

The Serial Wombat 18AB firmware relies heavily on 4 DMA channels, one for reading PORTA, one for writing PORTA, one for Reading PORTB and one for writing PORTB.  These DMAs are triggered by a 57600 Hz timer interrupt, and copy to or from four 128-entry, 16 bit wide circular buffers.  Many 18AB pin modes read or write to these buffers every 1ms.  Each 1 ms the pin mode reads new data read into the buffer since the prior 1ms call, or writes data to the outgoing circular buffer until it is full.  In this way a 1mS call can generate or process wave forms that happen at 57600 Hz.  It is vital that the SW18AB executive process the 1mS state machines on time to prevent overflow or underflow of the DMA channels.

The Serial Wombat 4A/4B firmwares can run in any combination of pin modes without concern for processor throughput.

The Serial Wombat 18AB chip can in some cases have pin modes assigned to it in ways that overload the processer, causing unreliable pin mode operation.  This is not a concern for most users, but can be an issue when many pins are assigned to pin modes that require generation or inspection of DMA data, for example Software UART modes, or Quadrature encoder mode in high performance (DMA) mode.  Multiple different diagnostics are available for monitoring processor loading.  

Pin State Machines
------------------

Each pin has a limited, pre-allocated amount of memory allocated to it.  This memory is used to store the current pin mode choice, 16 bits of public data, and some private data used to configure or operate the state machine.

A pin is configured to a state machine by CONFIGURE_CHANNEL_MODE command.  This command includes the pin number to be configured, the mode that the pin is being commanded to, and an index indicating the meaning of bytes in the configuration packet.  Many pin modes can be configured with a single CONFIGURE_CHANNEL_MODE packet.  More complicated modes may require multiple packets, sent in a specific order.

For pin modes that take data from the host (Such as I2C -> UART TX on the SW4B) the CONFIGURE_CHANNEL_MODE commands are also used to load this data during operation.

For pin modes that generate data for the host (Such as the Pulse Width timer mode) the CONFIGURE_CHANNEL_MODE commands can be used to retreive the various different data made available by that mode.

Each Pin State machine has an init function, a process function, and a structure type which defines the state machine's data organization.  The init function is called whenever a CONFIGURE_CHANNEL_MODE command is sent by the host.  The init function processes the command, configures the state machine or Serial Wombat hardware as required, and generates a response as required.  Some init responses simply leave the echo default response unchanged.

Once a pin has been set to a mode, the process function is called every 1mS by the executive.  This is where real-time processing of the pin's state machine happens.

Each pin has a fixed amount of memory allocated to it.  There is an array of pin_register_t unions declared with at least as many elements as there are avaialble state machine pins on the Serial Wombat chip.

The size of pin_register_t varies by model to allow more powerful chips to allocate more ram to each state machine.  The pin_register_t.generic member is a structure that contains some number of general-purpose bytes that is consistent for all pin modes on that family of models, followed by the 16-bit public data for that statemachine, followed by an 8-bit mode byte.

On models with strong indexed addressing capability such as the PIC24FJ256GA702 based Serial Wombat 18AB chip, iteration through the pins is achieved by a single pointer, CurrentPinRegister, which is incremented prior to each process call to point to the pin currently being serviced.  The variable CurrentPin is updated to be the pin number currently being serviced.  Similarly, the pointer and index are updated prior to init calls.

On models with weak indexed addressing capability such as the PIC16F15214 based Serial Wombat 4 series, the array element is copied to a buffer of type pin_register_t prior to pin process execution.  The pin mode then executes against the fixed addresses of the buffered values.  After processing is complete, the buffer is copied back to the array.  This has processing time cost to do the copies, but greatly reduces the code space required for each pin mode, allowing much more functionality within the limited flash space of the chip.  For these chips, CurrentPinRegister becomes a #define  which defines CurrentPinRegister as the address of the buffer.

When a pin state machine needs to access data which is defined the same way across all state machines such as the 16-bit public data or pin mode value it accesses it using the pin_register_t defintion:

> switch( `CurrentPinRegister->generic.mode` )

When accessing the pin-mode specific area of the pin_register_t element the CurrentPinRegister is recast as a pointer to the structure type defined in the pin mode.  It is important that the structure not define variables that take up more space than is alloted for pin-mode specific data.


Public Data
-----------
The public data is typically a pin mode's input or output value that is most interesting to the host, or to other pin modes, expressed as a 16-bit value.  Some pin modes, such as Protected Output, can be configured to read and react to the public data of another pin.  For instance, for a PWM pin, the public data is its Duty Cycle.  Changing that Pin's public data will change its duty cycle.   For a Pulse Measurement pin, the high time of the last pulse is its public data.   For an A/D converter pin, the latest Raw A/D conversion is its public data.  For a Servo, the servo's position is its public data.  

The SW4A and SW4B are limited in their configuration of public data options due to limited flash space for programming logic.  The forthcoming SW19 series will be more configurable.  In that case, the public data for an A/D can be configured to be a raw, averaged, or filtered value.  More sophisticated pin modes will be available, such as a hystersis mode which turns an ouput on and off based on another pin such as an A/D, or a PID controller which can control a proportional output such as a servo, or PWM output based on specified constants.

For digital values, Public data typically use 0 and 1 for False and True, or for Low and High.

Proportial public data is always scaled to be a 16-bit value.  0 is the lowest possible value and 65535 (0xFFFF) is the highest for any proportional value.  This is regardless of resolution.  For example. the SW4A and SW4B have 10 bit A/D converters.  The 0-1023 output of this converter is scaled to a 0-65535 output that moves in 64 count steps.  Note that the maximum output is scaled differently from 1023 to 65535 (rather than 1023 * 64 = 65472).  65535 always represents "Maximum measurable value".  The SW19 series has a 12-bit A/D converter, so its internal resolution is 0-4095, but this is scaled to 0-65535 in 16 count steps.  A servo outputs its shortest pulse (typically 500uS) when its public data is 0, and longest( typically 2500 uS) when its public data is 65535.  The SW19's 32 step true analog output takes an input of 0-65535 and divides it by 2048 to determine which of the 32 output steps should be output.  In this way all Serial Wombat proportial inputs and outputs can be compared or linked together regardless of their native resolution. 

Special Public Data Values
--------------------------
Public data is requested or written by pins or Serial Wombat Communication Protocol commands, and is indexed by the pin whose data it is.  Up to 64 pins are allowed per Serial Wombat chip with this architecture, correpsonding to indexes 0-63.  

Values of 64 or higher correspond to special values.  

For instance, public data 64 is the number of frames that have been run.  This increments every mS when the Serial Wombat firmware is running correctly.
  
Public data 65 is the frame overflow count.  A frame overflow occurs if the prior forground subroutine call is still executing when it's time to start the next one.  This can occur if the CPU processing requirements of the selected pin modes exceed the CPU processing capacity of the microcontroller, or if too many interrupts are being generated to allow sufficient processing time for state machines and communications.

Public data 66 is the measured value of an internal 1.024v reference voltage, scaled to counts from 0 to 65535.  By examining this value it is possible to determine the Serial Wombat chip's source voltage.



Communication Protocol
======================

The Serial Wombat Communication Protocol (SWCP) is based on 8-byte packets of data regardless of the data bus being used.  The Serial Wombat expects an 8 byte command from the Host, and will respond with an 8 byte response.  The Serial Wombat chip will never send unsolicited data to the host.

See the protocol.c file documentation for each Serial Wombat firmware build for a list of supported commands by that Serial Wombat build.

I2C
---

Packet framing on I2C relies on the Start and Stop of the I2C packet.  Packets sent with less than 8 bytes will be ignored.  Any byte beyond 8 in a packet will be discarded.  
An I2C packet of 8 bytes is sent to the Serial Wombat chip.   The host may then optionally read an 8 byte response from the Serial Wombat chip in a second read packet.  The Serial Wombat chip's device address is used, but there is no concept of a register address.  Sending a register address before a read will clear the prior packet response due to the address being seen as a 1-byte, incomplete packet.  See the Arduino Library or Raspberry Pi package send or send/receive methods for examples.

The Serial Wombat chip makes use of I2C clock stretching to allow time for responses to be generated if a read immediately follows a write, or if a second write is sent before the prior write has been processed.  This may introduce a few-hundred uS of delay into transactions during which the SCL line of the I2C bus will be held low by the Serial Wombat.  The host must ensure at least 20 uS of delay between end and next start of  writes or writes and reads to allow the Serial Wombat chip's I2C hardware to prepare for the next packet.

UART
----

UART communication occurs at 115200 baud and 8 bits, no stop bits, no parity, no flow control.

The Host sends a packet of 8 bytes.  The Serial Wombat firmware processes those 8 bytes and sends an 8 byte response.  The host should wait until the 8 byte response has been received before sending another packet.

The UART protocol has no inherent framing.  It relies on synchronization between host and Serial Wombat chip so that the proper number of bytes are sent and both sides.  Sending of an incomplete packet, sending of characters in excess of 8 per packet, unexpected reset of the Host or Serial Wombat chip while a packet is in progress, or noise on the line can result in loss of Synchronization.

Loss of synchronization typically becomes evident when the Serial Wombat chip does not return a packet or returns a packet which is incorrect.  Every response packet begins with the same first byte as the command packet from the host.  This should be checked for maximum reliability.  In the event of a suspected synchronization loss, the user should consider resetting the Serial Wombat chip in case unexpected configuration changes resulted.

When synchronization is lost, it can be regained by sending eight or more 0x55 ('U') bytes. These values are discarded if received as the first byte of a packet.  When sending a packet, unused bytes should be filled with 0x55 so that they will be discarded if accidentally received as the beginning of a new packet rather than the end of the prior packet.

Serial Wombat chips based on a UART interface allow both binary and ASCII communication.  This allows a user to experiment by manually typing commands into a serial terminal connected to the Serial Wombat chip.  A simplified subset of the binary commands available can be accessed through ASCII commands.  These commands are still 8 byte packets.  The Serial Wombat chip can optionally be configured to echo back incoming bytes and add newlines between packets.  Enabling echos and newlines will break compatability with binary operations until they are turned off or the Serial Wombat chip is reset.


