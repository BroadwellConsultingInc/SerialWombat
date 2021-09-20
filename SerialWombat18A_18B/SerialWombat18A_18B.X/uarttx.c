#ifndef COMPILING_FIRMWARE

#include <stdio.h>

#endif
#include "types.h"
#include "utilities.h"
//#include "global_data.h"
//#pragma code APPLICATION
//#pragma romdata APPLICATION_DATA

#define UART_ACTIVE()  { if (tp->uart_tx.output) { OutputArrayA[lastportbcounter] |= bitfield;} else {OutputArrayA[lastportbcounter] &= bitfieldInvert;}} // TODO genericize for both ports
#define UART_INACTIVE()  { if (tp->uart_tx.output) { OutputArrayA[lastportbcounter] &= bitfieldInvert;} else {OutputArrayA[lastportbcounter] |= bitfield;}}




void init_uart_tx(void)
{
	//printf ("Initializing uart_tx\n");
        if (rxbuffer[0] == CONFIGURE_CHANNEL_MODE_0)
        {
		ASSIGN_RXBUFFER16(tp->uart_tx.queue,3);
		tp->uart_tx.invert = (rxbuffer[5] > 0);
		tp->uart_tx.output = (rxbuffer[6] > 0);
		tp->uart_tx.persistentdivisor = 1;
		tp->uart_tx.lastportbcounter = OUTPUT_ARRAY_A_DMA_INDEX;  // TODO make work for either PORT
        vpin_set(!tp->uart_tx.invert);
	}
	else if (rxbuffer[0] == CONFIGURE_CHANNEL_MODE_1)
        {
		tp->uart_tx.persistentdivisor = rxbuffer[3];
        }

}


#define STATE_IDLE 0
#define STATE_START_BIT 1
#define STATE_DATA 2
#define STATE_STOP_BIT 3

#define START_BIT_VALUE 0

#define STOP_BIT_VALUE 1

#define OUTPUT_CHARACTER 1

void update_uart_tx(void)
{
  	uint8_t lastportbcounter; 
	uint8_t divisor;
	uint8_t persistentdatacounter;
	uint8_t bitstowrite;
	uint8_t bitfield = 0x10 ;
	uint8_t bitfieldInvert = 0xEF;
	uint8_t data;
	uint8_t current_output;

	divisor = tp->uart_tx.persistentdivisor;
  	lastportbcounter = tp->uart_tx.lastportbcounter; 
	persistentdatacounter = tp->uart_tx.persistentdatacounter;
	bitstowrite = tp->uart_tx.bitstowrite;
	data = tp->uart_tx.data;
	current_output = tp->uart_tx.current_output;
   while (  OUTPUT_ARRAY_A_DMA_INDEX != lastportbcounter)   //TODO generalize for both ports
   { 

	   if (bitstowrite > 0)
	   {
		   --bitstowrite;
	   }
	   else if (persistentdatacounter > 0 )  // still have bits left to send
	   {
		   if (persistentdatacounter == 9)
		   {
			   //Start bit. tp->uart_tx.current_output = 0;
			   current_output = 0;
		   }
		   else if (data & 0x01)
		   {
			   current_output = 1;
			   data >>=  1;  // Starting  1 bit.
		   }
		   else
		   {
			   current_output  = 0;
			   data >>=  1;  // Starting 0 bit.
		   }
		   bitstowrite = divisor - 1;

		   --persistentdatacounter;

	   }

	   else
	   {
		   // Finished sending one byte.  Do a stop bit, and load the next character

		   current_output = 1;
		   bitstowrite = divisor + 3 ; 

		   
//TODO		   if (shift_byte(tp->uart_tx.queue,&tp.uart_tx.data) == QUEUE_BYTE_SHIFTED)
		   data = 'T';
		   {
			   persistentdatacounter = 9; //eight bits left, plus start

		   }
	   }

	   if (current_output)
	   {
		   UART_INACTIVE();
	   }
	   else
	   {
		   UART_ACTIVE();
	   }

	   ++lastportbcounter;
	   if (lastportbcounter >= SIZE_OF_DMA_ARRAY)
	   {
		   lastportbcounter = 0;
	   }
   }
	tp->uart_tx.data = data;
   	tp->uart_tx.persistentdatacounter = persistentdatacounter;
  	tp->uart_tx.lastportbcounter = lastportbcounter ; 
	tp->uart_tx.bitstowrite = bitstowrite;
	tp->uart_tx.current_output = current_output;

}


#ifndef COMPILING_FIRMWARE


#ifdef TEST_UARTRX


int main(void)
{
     
     int i;
     uint8 c;
     int final_result = 0;

     printf ("Testing uarttx\n");
     system_init();

	return (final_result);

}

#endif
#endif
