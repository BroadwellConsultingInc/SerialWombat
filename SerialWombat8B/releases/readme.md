<h1>Serial Wombat Revision History</h1>

<h2>2.2.2</h2>
<h3>Firmware</h3>
* Updated Version to 2.2.2
* Added ability to ask for I2C address as public data
* Added Blink Pin Mode to all SW8B builds and SW18AB
* Unified Queue code across 18AB and 8B .  Queues now use pointers rather than array indexes, allowing queues to be placed in pin memory
* Software based UARTS can now store their queues in Pin memory (User Buffer allocation optional)
* Removed Frame Overflow tracking from SW8B to save flash (can be recompiled in with #define)
* Added protocol code to check if a specified pin mode is supported in firmware
* Input processing does not support queueing of incoming data on SW8B
* Optimized counts-to-microseconds calculator in pulseTimer
* Fixed a bug in pulse timer where pulse period timing on low to high transitions was wrong in uS
* Added error code check in Quadrature Encoder if SW18AB pins are on different microcontroller ports in DMA mode
* Unified Pull up commands in Quadrature Encoder

<h3>Arduino Code</h3>
* Library compiles without warnings on ESP32, ESP8266, SAMD21 and Atmega
* All Doxygen undocumented elements warnings resolved
* Added Blink Class
* Added new method to ask if a pin mode is supported by firmware
* Added support for differing increment and decrement rates for Output Scaling rate control
* Changed Queue Write Timeout to be based on time since last byte transfer rather than overall time.  
* Fixed a bug assigning transition type in the Quad Enc simulator
* Added a bytesRemainingToTransmit to software Uart
* Made new begin method for Software Uart that overrides HW Uart version since it’s not required to allocate buffers in User Ram any more

<h3>Arduino Examples</h3>
* Greatly improved the reliability of the 18AB bootloader if interrupted during download
* Dropped Arduino Update 18AB Firmware over UART
* Added error handler calls to many examples
* Renamed pulseMeasurement examples to pulseTimer
* Revised some examples to use pins common to SW8B and SW18AB
* Added blink mode to SerialWombatChipFinder, reduced time between queries to 10 seconds
* Added example code for Bridge, Grip, and Backpack boards
 
