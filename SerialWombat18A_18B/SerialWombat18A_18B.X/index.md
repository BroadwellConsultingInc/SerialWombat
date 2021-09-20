///\mainpage Serial Wombat

What's a Serial Wombat?
========================


A Serial Wombat:

- Is a microcontroller programmed with custom, open-source firmware
- Connects to a PC, Raspberry Pi, Arduino, or other "Smart" Host device through a UART or I2C connection
- Acts as "Arms and Legs" by giving the host device Digital and Analog I/O capabilities
- Uses a simple 8 byte protocol
- Is designed to be attached to the host device during operation
- Provides up to 19 digial I/O pins (Pic24FJ256GA702 version)
- Provides up to 10 Analog Inputs
- Runs on 3.3V, but also has a few 5v Tolerant inputs, including UART RX
- Comes pre-programmed. You don't download any program to the Wombat; you send it commands in real-time
- Includes functions to reduce the work of the host device, including servo control, stepper motor control, LCD display control, keypad scanning, filtering, averaging, rotary-encoder and many other pin-modes.
- Can be upgraded by the user when new firmware comes out using a bootloader

The Serial Wombat is a 28 pin, Microchip 24FJ256GA702 PIC which comes preprogrammed with firmware to solve many common interface problems. The Serial Wombat makes it easy for people to interface things to their computer without ever programming a byte of code into a microcontroller.
It makes it easy to add IO to devices with limited inputs and outputs, such as inexpensive ESP-01 ESP8266 based boards.
 It talks to the host via UART or I2c. 

See the principles section of the Overview page for more detail on the ideas which drove the creation of the Serial Wombat. 

The Serial Wombat makes it easy to write software to do more complicated things which can only be achieved on a PC with the help of
embedded firmware.  

If you're using an Arduino or Raspberry Pi, this same embedded firmware can handle I/O focused tasks leaving your main program free to worry about higher level logic. 

For instance, you could simultaneously:
- Control up to 19 Servos from the host computer, or set up a servo to respond to other Wombat inputs
- Scan a matrix encoded keypad, and report and remember button pushes for reporting to the host
- Monitor a rotary encoder and report the net number of clockwise or counterclockwise turns to the host
- Configure the Wombat to monitor for short circuits of a FET driver and shut off an output within milliseconds of a short condition, preventing damage

The Serial Wombat has a built in bootloader. This means that when a new version of firmware comes out, you can download it into the chip yourself without needing an embedded programmer.

Serial Wombat Overview
======================

The Serial Wombat is designed to provide low-to-medium speed
Digital I/O (up to about 50kHz) and analog to digital data aquisition, while taking
advantage of the potential available in an external
microcontroller. 

The Serial Wombat's internal firmware does a lot more than just set pins high or low.  Each pin is assigned an independed state machine capable of doing lots of different things, which preprocess data or manipulate outputs to achieve higher level functionality on behalf of the host.

- Why waste precious bandwidth sending data from a device
        to its host when this data will simply be averaged
        or filtered when it gets there? Filtering and averaging
        should often be done before data is sent to the host.
- Why make decisions on the host which could be made faster
        and more efficiently on the microcontroller? For example,
        if a temperature of an aquarium is being controlled by a
        heater and a host, there are two ways this could be done:
             + The host could constantly ask the Wombat what the
                temperature of the aquarium is, then tell the
                Wombat to turn on or turn off the heater
                accordingly. This method uses lots of bandwidth
                over the serial link, and may kill your tropical
                fish if your host crashes or locks up.</li>
            + Or....The host can tell the Wombat, "Wombat, please
                set pin number 6 as a digital output. Set it
                high when the voltage on pin 2 (from a
                temperature sensor) drops below 350, and set it
                low when the voltage rises above 400."; The
                Wombat will then take responsibility for holding
                the temperature between 350 and 400. This can be
                done with a couple of simple serial commands.
- Some events happen too fast to be communicated in
        real-time to the host. For example, a rotary encoder knob
        (such as the ones on many car radios) which is turned by
        a human typically can change states at around every 500
        microseconds. This is far too often to be polled by the
        host. However, it can be easily monitored by the Wombat.
        The Wombat then simply tells the host the net number of
        "clicks" clockwise or counter-clockwise have
        happened since the last time the host asked.

Many of these problems can also be solved by programming directly on an Arduino or Raspberry Pi. 
However, this often takes a substantial time investment, and may rely on libraries that are specific to a particular platform.
The Serial Wombat is designed to allow many common embedded problems without needing a hardware specific library.  The Wombat will work good with any platform that has a UART.  Some
problems, such as the Aquarium example above, can be solved by
simply sending a few commands to the Wombat from a terminal such
as Putty or Hyperterminal.

Principals
==========
The Serial Wombat design is based on the following
principles:

- The communication protocol between the Serial Wombat and its host should be simple,
        efficient, and robust. Loss of synchronization with
        the host should be unlikely to cause incorrect commands
        to be executed. When synchronization is lost it
        should be detectable by the host after one command, and
        should be easily resynchronized. 

- The processing power of the microcontroller should be
        used to relieve the host of mundane tasks, and to make
        optimal use of host/Serial Wombat communication
        bandwidth. 

- As much as possible, every pin should be capable of every
        function (Digital I/O, pwm, frequency measurement,
        Analog/Digital conversion, communications).  If
        functionality is not provided by microcontroller hardware
        resource for a given pin, then it should be implemented in software.

- The user should require little to no understanding of the
        microcontroller inner workings to implement simple
        projects.Pins should be refered to by their pin
        number. The user should not have to distinguish
        between pins on different logical ports. 
        
- The user should be able to access as many of the
        microcontroller special hardware functions as
        possible. In some rare cases, this may require
        understanding of the microcontroller's special function
        registers. To borrow a quote from Perl, Easy things
        should be easy, and hard things should be possible.
- The user should determine how to best use available
        memory and processor throughput The user should be
        able to determine the most desireable trade-off between
        pin sampling/update rate and CPU utilization/function
        complexity.   However, most common uses should "Just Work" without futzing with this.

- The Serial Wombat should make system level debugging as
        easy as possible. The ability to issue typed
        commands to the hardware through an ASCII terminal such
        as Windows Hyperterminal allows the user to manipulate
        hardware before application software is written.
        Comprehensive error checking, the availability of an Echo
        function, and access to numerous internal system state
        variables allows the user to quickly diagnose problems. 

- The Serial Wombat should use software as possible to
        eliminate physical components. Examples include
        digital filtering of analog inputs and debouncing of
        switch inputs, as well as ability to individually set internal pin pull-ups and pull-downs. 

-  The Serial Wombat should be expandable. The user
        should be able to develop firmware to run in the
        microcontroller in partnership with the existing Serial Wombat
        pin modes.</li>

Why the PIC24FJ256GA702?
========================

Of all of the microcontrollers in the world, why the PIC24FJ256GA702?

This micro has a few properties that make it particularly well suited to become the new Serial Wombat:

-  It comes in multiple packages, including DIP.  The 28 pin dip package makes it easy for people who like to build their own hardware, but are uncomfortable with surface mount soldering of IC's.
-  It's cheap.  On microchip's site the DIP package is currently about 2 bucks, dropping down to $1.50 in quantity.  SOIC's and QFN's are even a little bit cheaper.
-  Cheap, functional programming adapters avaialble to flash the Serial Wombat firmware into the chip.  Aliexpress has PicKit3 knock-offs for about 10 bucks, shipped.  I use one frequently.
-  3.3v operation, with 5v tolerant pins.   This means that the Serial Wombat can communicate with nearly any Arduino device with a UART, since it's RX pin is directly 5v tollerant, and a 5V device will accept 3 v input.  5 additonal pins on the PIC24FJ256GA702 are 5v tollerant
-  Internal DMA capability - Many pin modes of the serial wombat rely on periodic, relatively high speed updates (57,600 updates per second).  The use of timer based DMA allows the Serial Wombat to provide very precisely timed updates on all 19 pins.
- 10 pins have 12 bit A/D converters, and an internal bandgap reference allows measurement of supply voltage +/- 5%.  
- Each digital IO pin can sink or source up to 25mA of current, with a cap of 200ma total for the entire chip.
- Wide operating range of 2.2V to 3.6V
-  Peripheral Pin Select -  This feature of a micro allows remapping of hardware peripherals from one pin to another.  This allows, for instance, the hardware spi capability to be routed to selectable pins on the Serial Wombat.  14 of the Serial Wombat's 19 configurable pins have this function.
-  Microchip is better than most companies about not discontinuing aging products

Among the concerns with this chip:

-  No open source compiler
-  Requires a 10uF cap on vCAP, in addtion to typical .1uf Decoupling Caps



