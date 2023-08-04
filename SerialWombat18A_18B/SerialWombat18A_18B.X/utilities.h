/*
Copyright 2021-2023 Broadwell Consulting Inc.

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
#if (!defined (_utilities_h))
#define _utilities_h
#define NUMBER_OF_PHYSICAL_PINS 19
#define NUMBER_OF_VIRTUAL_PINS NUMBER_OF_PHYSICAL_PINS
#define COMPILING_FIRMWARE
#define SIZE_OF_DMA_ARRAY 128
#include "mcc_generated_files/system.h"
#include "types.h"


#define PHYSICALEQUALSVIRTUALPIN
#define RANDOM_ENABLE

//#include "global_data.h"
//#include "eeprom_map.h"
#define PHYSICALEQUALSVIRTUALPIN

#define SIZE_OF_USER_BUFFER 4096



uint8_t map_physical_pin_ad(uint8_t pin);
uint8_t read_pin (uint8_t pin);
void set_pin (uint8_t pin, uint8_t mode);
#define toggle_pin(_a) {set_pin (_a, !read_pin(_a));}
//#define vpin_high() {set_pin(virtual_pin,HIGH);}
void vpin_high(void);

void delay_timer3_ticks(uint16_t ticks);
//#define vpin_low() {set_pin(virtual_pin,LOW);}
void vpin_low(void);
//#define vpin_input() {set_pin(virtual_pin,INPUT);}
void vpin_input(void);
void vpin_set(uint8_t state);
void pin_high(uint8_t pin);
void pin_low(uint8_t pin);
void pin_input(uint8_t pin);
//#define vpin_set(_a) {set_pin(virtual_pin,_a);}
//#define vpin_read() read_pin(virtual_pin)

void EEPROM_WRITE(uint16_t address, uint8_t value) ;

#ifdef CACHED_ADREADINGS
#define read_ad(_a) ADbuffer[map_physical_pin_ad(_a)].u
#else
uint16_t read_ad(uint8_t virtual_pin);
#endif



uint16_t vread_ad(void);

uint8_t vpin_read(void);
uint8_t ascii_to_val(uint8_t);
uint8_t val_to_ascii(uint8_t);
void val16_to_hex(mixed16_t val, uint8_t* string);
uint16_t hex_ascii_to_val16(uint8_t* ptr,uint8_t counter);
uint32_t hex_ascii_to_val32(uint8_t* ptr,uint8_t counter);
uint16_t rx_dec_ascii_to_val16(uint8_t rxbufferindex,uint8_t counter);
uint32_t dec_ascii_to_val32(uint8_t* ptr,uint8_t counter);
uint32_t read_free_running_timer(void);
uint8_t get_user_buffer(uint16_t offset);
void put_user_buffer(uint16_t offset, uint8_t data);
void get_user_buffer_block(uint16_t offset, uint16_t length, uint8_t* dest);
void put_user_buffer_block(uint16_t offset, uint16_t length, uint8_t* source);
void set_pwm(uint8_t virtual_pin, uint16_t width);
void vset_pwm(uint16_t width);
void update_pwm(void);
uint16_t get_buffer(uint8_t);
void put_buffer(uint8_t,uint16_t);
uint8_t get_pin_registers(void);
void put_pin_registers(void);
void vpulse_high(uint16_t cycles);
uint8_t slow_SPI00_send(uint8_t data,uint8_t delay,uint8_t clkpin,uint8_t sdipin,uint8_t sdopin);
void delay_cycles16(uint16_t cycles);
#define DELAY_CYCLES(_a) { delay_cycles16(_a);}
#define DELAY_1MS() {delay_cycles16(CRYSTAL_SPEED / 1000); }
#define get_tp2(_a)  {get_tp2_asm(_a);}
#define put_tp2(_a)  {put_tp2_asm(_a); }
void put_tp2_asm(uint8_t pin);
void get_tp2_asm(uint8_t pin);

uint16_t random(void);
void random_seed(uint32_t);
uint16_t gen_sin_wave (uint8_t wavenum);

#define LOW 0
#define HIGH 1
#define INPUT 2

#define HIGH_BYTE_16(a) ( (uint8_t) ( a >> 8 ) )
#define LOW_BYTE_16(a) ( (uint8_t)  a )

#define HIGH_BYTE_32(a) ( (uint8_t) ( a >> 24 ) )
#define MH_BYTE_32(a) ( (uint8_t) ( (a >> 16) & 0xFF ) )
#define ML_BYTE_32(a) ( (uint8_t) ( (a >> 8) & 0xFF ) )
#define LOW_BYTE_32(a) ( (uint8_t)  a )
#define set_register_memory(pin,field,value) {pin_update_registers[pin].field = value;}
#define set_register_memory2(pin,field,value) {((pin_register2_t*)pin_update_registers)[pin].field = value;}
#define get_register_memory(pin,field) pin_update_registers[pin].field 
#define get_register_memory2(pin,field) ((pin_register2_t*)pin_update_registers)[pin].field 
#define set_mode(_a,_b) {pin_update_registers[_a].generic.mode = _b;}
#define get_mode(pin) pin_update_registers[pin].generic.mode 
#define set_hw_mode(_a,_b) {pin_update_registers[_a].generic.hw_mode = _b;}
#define set_hw_option(_a,_b) {pin_update_registers[_a].generic.duty_cycle = _b;}
#define get_hw_option(_a) pin_update_registers[_a].generic.duty_cycle 
#define set_buffer(a,b) {pin_update_registers[a].generic.buffer = b;}

#define ENABLE_CCP1_CAPTURE() {   PIE1bits.CCP1IE = 1; }
#define DISABLE_CCP1_CAPTURE() {  PIE1bits.CCP1IE = 0; }
#define ENABLE_CCP2_CAPTURE() {   PIE2bits.CCP2IE = 1; }
#define DISABLE_CCP2_CAPTURE() {  PIE2bits.CCP2IE = 0; }
#define ENABLE_INT0_CAPTURE() {  INTCONbits.INT0IE = 1;  }
#define DISABLE_INT0_CAPTURE() {  INTCONbits.INT0IE = 0; }
#define ENABLE_INT1_CAPTURE() {  INTCON3bits.INT1IE = 1;  }
#define DISABLE_INT1_CAPTURE() {  INTCON3bits.INT1IE = 0; }
#define ENABLE_INT2_CAPTURE() {  INTCON3bits.INT2IE = 1;  }
#define DISABLE_INT2_CAPTURE() {  INTCON3bits.INT2IE = 0; }
#define RXBUFFER16(a) ((((uint16_t)rxbuffer[a]) <<8) + rxbuffer[a + 1])
#define ASSIGN_RXBUFFER16(dest,a)\
{                                \
	((mixed16_t*)&dest)->bytes.highbyte = rxbuffer[a]; \
	((mixed16_t*)&dest)->bytes.lowbyte  = rxbuffer[a+1]; \
}
extern rom const uint8_t uint8_bitfield_invert[8] ;
extern rom const uint16_t uint16_bitfield[16];
extern rom const uint8_t uint8_bitfield[8]; // = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
extern rom const uint8_t uint8_bitlowermask[8]; // = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

extern rom const uint8_t map_next_physical_pin[NUMBER_OF_PHYSICAL_PINS + 1];
#ifndef PHYSICALEQUALSVIRTUALPIN
extern rom const uint8_t map_pin_table[NUMBER_OF_PHYSICAL_PINS + 1];
#endif

#ifdef PHYSICALEQUALSVIRTUALPIN
#define map_pin(_a) (_a) 
#define unmap_pin(_a) _a
#else
#define map_pin(_a) ((_a <= LAST_VIRTUALIZED_PIN)?map_pin_table[_a]:_a)
#endif

extern void error(void);
#ifdef COMPILING_FIRMWARE
#define DISABLE_ALL_INTERRUPTS() {INTCONbits.GIEL = 0; INTCONbits.GIEH = 0; }
#define ENABLE_ALL_INTERRUPTS() {INTCONbits.GIEL = 1; INTCONbits.GIEH = 1; }

#else

#define DISABLE_ALL_INTERRUPTS() { }
#define ENABLE_ALL_INTERRUPTS() { }

#endif

#ifdef EUSART
#define SET_BAUD_RATE(_a) { SPBRG = ((CRYSTAL_SPEED  / ((uint32_t)_a) / 16 * PLL_MULTIPLIER) - 1) & 0x00FF; SPBRGH = ((CRYSTAL_SPEED  / ((uint32_t)_a)/ 16 * PLL_MULTIPLIER) - 1) >>8; }
#else
#define SET_BAUD_RATE(_a) { SPBRG = (CRYSTAL_SPEED  / ((uint32_t)_a) / 64  - 1) & 0x00FF; }
#endif

#ifndef COMPILING_FIRMWARE

extern void print_pin(int pin,unsigned char high,unsigned char low);
#endif

typedef enum 
{
	PPS_OUTPUT_None = 0, //(Pin Disabled) —
	PPS_OUTPUT_C1OUT = 1, //Comparator 1 Output
	PPS_OUTPUT_C2OUT = 2, //Comparator 2 Output
	PPS_OUTPUT_U1TX = 3, //UART1 Transmit
	PPS_OUTPUT_U1RTS = 4, //UART1 Request-to-Send
	PPS_OUTPUT_U2TX = 5, //UART2 Transmit
	PPS_OUTPUT_U2RTS = 6, //UART2 Request-to-Send
	PPS_OUTPUT_SDO1 = 7, //SPI1 Data Output
	PPS_OUTPUT_SCK1OUT = 8, //SPI1 Clock Output
	PPS_OUTPUT_SS1OUT = 9, //SPI1 Chip Select Output
	PPS_OUTPUT_SDO2 = 10, //SPI2 Data Output
	PPS_OUTPUT_SCK2OUT = 11, //SPI2 Clock Output
	PPS_OUTPUT_SS2OUT = 12, //SPI2 Chip Select Output
	PPS_OUTPUT_OC1 = 13, //Output Compare 1
	PPS_OUTPUT_OC2 = 14, //Output Compare 2
	PPS_OUTPUT_OC3 = 15, //Output Compare 3
	PPS_OUTPUT_OCM2A = 16, //CCP2A Output Compare
	PPS_OUTPUT_OCM2B = 17, //CCP2B Output Compare
	PPS_OUTPUT_OCM3A = 18, //CCP3A Output Compare
	PPS_OUTPUT_OCM3B = 19, //CCP3B Output Compare
	PPS_OUTPUT_OCM4A = 20, //CCP4A Output Compare
	PPS_OUTPUT_OCM4B = 21, //CCP4B Output Compare
	PPS_OUTPUT_Reserved = 22, //—
	PPS_OUTPUT_SDO3 = 23, //SPI3 Data Output
	PPS_OUTPUT_SCK3OUT = 24, //SPI3 Clock Output
	PPS_OUTPUT_SS3OUT = 25, //SPI3 Chip Select Output
	PPS_OUTPUT_C3OUT = 26, //Comparator 3 Output
	PPS_OUTPUT_PWRGT = 27, //RTCC Power Control
	PPS_OUTPUT_REFO = 28, //Reference Clock Output
	PPS_OUTPUT_CLC1OUT = 29, //CLC1 Output
	PPS_OUTPUT_CLC2OUT = 30, //CLC2 Output
	PPS_OUTPUT_RTCC = 31, //RTCC Clock Output
}PPSOutputVal_t;


#define OUTPUT_ARRAY_A_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT0) 
#define OUTPUT_ARRAY_B_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT1) 
#define INPUT_ARRAY_A_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT2) 
#define INPUT_ARRAY_B_DMA_INDEX (SIZE_OF_DMA_ARRAY - DMACNT3) 


#define BROADCAST_ADDRESS 0xFF

#define BUFFER_RANDOM_NUMBER 253
#define BUFFER_ZERO_VALUE 252
#define BUFFER_UART_RX_OVERFLOWS 251
#define BUFFER_CLOCK_SECONDS 250
#define BUFFER_CLOCK_MINUTES 249
#define BUFFER_CLOCK_HOURS 248
#define BUFFER_CLOCK_DAYS 247
#define BUFFER_RX_INTERRUPTS 246
#define BUFFER_TX_INTERRUPTS 245
#define BUFFER_SINE_SUM_3 244
#define BUFFER_SINE_SUM_2 243
#define BUFFER_SINE_3 242
#define BUFFER_SINE_2 241
#define BUFFER_SINE_1 240
#define BUFFER_INCREMENTING_NUMBER 239
#define BUFFER_LAST_QUEUE_UNDERFLOW 238
#define BUFFER_LAST_QUEUE_OVERFLOW 237
#define BUFFER_PINS2345671413 236
#define BUFFER_PINS1516171823242526 235
#define BUFFER_PINS1920212227282930 234
#define BUFFER_PINS3334353637383940 233
#define BUFFER_FREE_RUNNING_TIMER 232
#define BUFFER_INTERRUPT_OCCURRED 231
#define BUFFER_NUM_OF_DROPPED_FRAMES 230
#define BUFFER_TO_USER_RAM       160
#define BUFFER_TO_USER_RAM_MAX    200

#define SYSINFO_VERSION 0 
#define SYSINFO_CONFIG_BITS_1 1
#define SYSINFO_CONFIG_BITS_2 2
#define SYSINFO_CONFIG_BITS_3 3
#define SYSINFO_FRAME_COUNTER 4
#define SYSINFO_RX_INTERRUPTS 5
#define SYSINFO_TX_INTERRUPTS 6
#define SYSINFO_AD_INTERRUPTS 7
#define SYSINFO_THROUGHPUT_INFO 8
#define SYSINFO_FREE_RUNNING_TIMER 9
#define SYSINFO_CHIP_ID       10
#define SYSINFO_FRAME_DATA 11
#define SYSINFO_BAUD_RATE 12
#define SYSINFO_RESET_REGISTER 13
#define SYSINFO_USER_RAM_SIZE 14

extern uint8_t virtual_pin;
 extern pin_register_t* tp;
extern  pin_register2_t* tp2;
extern pin_register_t pin_update_registers[NUMBER_OF_PHYSICAL_PINS ];
extern uint16_t OutputArrayA[SIZE_OF_DMA_ARRAY]; 
extern uint16_t OutputArrayB[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayA[SIZE_OF_DMA_ARRAY];
extern uint16_t InputArrayB[SIZE_OF_DMA_ARRAY];
extern const uint16_t PinBitmapA[NUMBER_OF_PHYSICAL_PINS] ;
extern const uint16_t PinBitmapB[NUMBER_OF_PHYSICAL_PINS]; 
extern uint8_t rxbuffer[];
extern uint8_t txbuffer[];
extern executive_settings_t executive_settings;
extern uint8_t user_buffer[SIZE_OF_USER_BUFFER];
extern uint16_t vpinBitmap(void);
extern uint8_t vpinPort(void);
extern uint8_t getDMAInputSample(uint8_t pin, uint8_t sample);
extern void updatePulseOutput(uint8_t pin);
extern void SPI_Transfer(uint8_t cs_pin,uint8_t clk_pin, uint8_t MOSI_pin, uint8_t MISO_pin, uint8_t* MOSI_Buffer, uint8_t* MISO_Buffer, uint16_t Count);

#endif
