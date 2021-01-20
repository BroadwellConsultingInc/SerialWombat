# Serial Wombat

The Serial Wombat project is a line of microcontrollers with firmware designed to extend the capabilities of single board computers such as Arduino boards and the Raspberry Pi or a PC or other device.

The Serial Wombat is an open-source, MIT Licensed project developed by Broadwell Consulting Inc. to showcase and promote the embedded systems capabilities of the company.  

A Serial Wombat is not programmed for a given application by the end user.  It is pre-programmed with general-purpose firmware, and configured at run time to make the hardware resources of the microcontroller available for command by the host in ways that solve common embedded systems problems.

For example, a Serial Wombat could be used for many of the same tasks as an MCP3008 ADC converter, such as adding Analog to Digital Conversion to a Raspberry Pi.  Both have 10-Bit ADC capability.  However, only the Serial Wombat is capable of taking many sequential measurements and averaging or performing first-order filtering without additional effort by the host.

The Serial Wombat is also a potential replacement for the MCP23017.  Like the MCP23017, the Serial Wombat 4A and 4B provide operation up to 5.5V with the ability to talk to a 3.0 or 3.3V host over I2C.  Both provide 25mA of sink and source current per pin, with open drain and weak pull up options available.  However, the Serial Wombat uses onboard firmware to allow functions like Quadrature Encoder reading, Servo driving, PWM output, and pulse width / duty cycle measurement without additional help from the host.  Serial Wombat 4A and 4B allow 4 pins to be added with each chip, with multiple chips possible on the same bus in the case of the I2C based SW4B.  The forthcoming Serial Wombat 19 series will provide 19 pins, 10 of which will be A/D capable.

Pins on the Serial Wombat can be assigned tasks fairly independently.  A single Serial Wombat 4A could have 4 A/D pins, or 2 A/D pins and a quadrature encoder, or an A/D, a button, and two servo drivers.

Integration with common platforms is easy with pre-written libraries.  

Many tutorial and cookbook videos are available on YouTube that demonstrate how to use the Serial Wombat family.

https://www.youtube.com/watch?v=UZOnq2FdrvU&list=PL9_vji2WbJGjNSjp9rnOrdrNzMCQIjaj_

An Arduino library is available now:

https://broadwellconsultinginc.github.io/SerialWombatArdLib/

And a Raspberry Pi Python package is in development.

A C# library is also nearly finished and will be released soon.

The Serial Wombat 4A and 4B firmware runs on the PIC16F15214 microcontroller.  It is designed for the PRO version of the XC8 compiler, and the MPLAB X development environment.

You can compile the firmware yourself and program chips using a PICKIT or similar programming device, or you can buy preprogrammed kits from Broadwell Consulting Inc on 
