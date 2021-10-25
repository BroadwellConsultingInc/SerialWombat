#ifndef COMPILING_FIRMWARE
#include <stdio.h>
#endif
#include "types.h"
#include "utilities.h"
#include "global_data.h"
#include "kp.h"
#pragma code APPLICATION

//RX
// 0 - CONFIGURE D I/O
// 1 - PIN NUMBER
// 2 - Mode - Keypad Scan Row 0
// 3 - Pin # for Column 1
// 4 - QUEUE ADDRESS (H)
// 5 - (L)
// 6 - Scan Delay States
// 7 - Mode : 0x0F = 0: queue nothing
//                   1: queue button push numbers, binary
//                   2: queue button push numbers, Ascii 
//                   3: queue bitmap changes 
//            0xF0   
//                   2: Buffer = last button pressed, held
//                   1: Buffer = current button number, 255 for none
//                   0: Buffer = current bitmap, 
// Registers
// This Pin:
// R0 - Pin for Column 1 of 4
// R1 - QUEUE ADDRESS (H)
// R2 - (L)
// R3 - Current Reading Bitmap (High)
// R4 - Current Reading Bitmap (Low)
// R5 - Previous Reading Bitmap (H)
// R6 - Previous Reading Bitmap (L)
// R7 - Current State 
// This pin + 1:
// R0 - Currently pressed button 0-15, or 255 for none
#define NO_KEY_PRESSED 0xFF
// R1 - Previously pressed button 
// R2 - Scan Delay States
// R3 - Mode 
// R4 - Current Delay

#define KEYPAD_STATE_SETUP_ALL_LOW 0
#define KEYPAD_STATE_WAIT_FOR_PRESS 1
#define KEYPAD_STATE_SETUP_ROW_1 2
#define KEYPAD_STATE_SETUP_ROW_1_WAIT 3
#define KEYPAD_STATE_READ_ROW_1  4
#define KEYPAD_STATE_SETUP_ROW_2 5
#define KEYPAD_STATE_SETUP_ROW_2_WAIT 6
#define KEYPAD_STATE_READ_ROW_2  7
#define KEYPAD_STATE_SETUP_ROW_3 8
#define KEYPAD_STATE_SETUP_ROW_3_WAIT 9
#define KEYPAD_STATE_READ_ROW_3  10
#define KEYPAD_STATE_SETUP_ROW_4 11
#define KEYPAD_STATE_SETUP_ROW_4_WAIT 12
#define KEYPAD_STATE_READ_ROW_4  13
#define KEYPAD_STATE_DELAY       14
#define KEYPAD_STATE_IDLE        15

#define KEYPAD_BUFFER_MODE_BINARY 0
#define KEYPAD_BUFFER_MODE_LAST_BUTTON 1
#define KEYPAD_BUFFER_MODE_CURRENT_BUTTON 2

#define KEYPAD_QUEUE_MODE_NONE 0
#define KEYPAD_QUEUE_MODE_BUTTON_DOWN 1
#define KEYPAD_QUEUE_MODE_BUTTON_ASCII 2
#define KEYPAD_QUEUE_MODE_BINARY_CHANGE 3

typedef struct matrixKeypad_n{
	uint8_t current_button;
	uint8_t previous_button;
	uint8_t queue_mode:3;
	uint8_t buffer_mode:3;
	uint8_t testing_button;
	uint8_t rows:4;
	uint8_t columns:4;
	uint8_t current_row;
	uint8_t column_pin;
	uint16_t queue;
	uint16_t current_reading;
	uint16_t previous_reading;
	uint8_t state;
} matrixKeypad_t;

void initMatrixKeypad (void)
{
	      local_j = map_pin(map_next_physical_pin[Rxbuffer[1]]);
	      get_tp2(local_j);
      	      if (Rxbuffer[0] == CONFIGURE_CHANNEL_MODE_0)
	      {
		      
		      matrixKeypad->.column_pin = Rxbuffer[3];	
		       matrixKeypad->.queue = RXBUFFER16(4);	
		       matrixKeypad->.queue_mode = Rxbuffer[6]; 
		       matrixKeypad->.buffer_mode = Rxbuffer[7]; 
		       matrixKeypad->.current_reading = 0;
		       matrixKeypad->.previous_reading= 0;
		       matrixKeypad->.state=  KEYPAD_STATE_IDLE;
		       matrixKeypad->.current_button = NO_KEY_PRESSED;
		       matrixKeypad->.previous_button = NO_KEY_PRESSED;
		 }
		 else if (Rxbuffer[0] == CONFIGURE_CHANNEL_MODE_1)
		 {
		      matrixKeypad->.rows = Rxbuffer[3];
		      matrixKeypad->.columns = Rxbuffer[4];
		      local_j = Rxbuffer[1];
		      for (local_i = 0; local_i <  Rxbuffer[3]; ++local_i)
		      {
			local_k = map_pin(local_j);
			set_pin(local_k,INPUT);
			set_mode(local_k, PIN_MODE_CONTROLLED);
			local_j = map_next_physical_pin[local_j];
		      }
		      local_j = matrixKeypad->.column_pin;
		      for (local_i = 0; local_i < Rxbuffer[4]; ++local_i)
		      {
			local_k = map_pin(local_j);
			set_pin(local_k,INPUT);
			set_mode(local_k, PIN_MODE_CONTROLLED);
			local_j = map_next_physical_pin[local_j];
		      }
		      matrixKeypad->.state = KEYPAD_STATE_SETUP_ALL_LOW;
                 }
		 local_j = map_pin(map_next_physical_pin[Rxbuffer[1]]);
                 put_tp2(local_j);
}


void updateMatrixkeypad(void)
{
    uint8_t  temp8_1;
    uint16_t temp1_16;



              if (matrixKeypad->.state == KEYPAD_STATE_IDLE)
	      {
		      return;
	      }
              local_i = unmap_pin(virtual_pin);
      	      local_j = map_pin(map_next_physical_pin[local_i]);
              get_tp2(local_j);
	      
	      switch (matrixKeypad->.state)
	      {

		      case KEYPAD_STATE_SETUP_ROW_1_WAIT:
			      matrixKeypad->.state = KEYPAD_STATE_READ_ROW_1;
		      break;

		      case KEYPAD_STATE_SETUP_ALL_LOW:
		      default:
		      {
			   local_j = unmap_pin(virtual_pin);
			   for (local_i = 0; local_i < matrixKeypad->.rows; ++local_i)
			   {
				     set_pin(map_pin(local_j ), LOW);
				     local_j = map_next_physical_pin[local_j];
			   }      
		           matrixKeypad->.state = KEYPAD_STATE_WAIT_FOR_PRESS;
		      }
		      break;

		      case KEYPAD_STATE_WAIT_FOR_PRESS:
		      {
			   matrixKeypad->.testing_button  = 0;
			   matrixKeypad->.current_reading = 0;   //Current bitmap = 0
			   matrixKeypad->.current_button = NO_KEY_PRESSED; //No key pressed
			   matrixKeypad->.current_row = 0;
			      local_j = matrixKeypad->.column_pin;
			      for (local_i = 0; local_i < matrixKeypad->.columns; ++ local_i)
			      {
				      if  (! read_pin( map_pin(local_j) )) 
				      {
					      matrixKeypad->.state = KEYPAD_STATE_SETUP_ROW_1;
				      }

				      local_j = map_next_physical_pin[local_j];
			      }
			      if (matrixKeypad->.state != KEYPAD_STATE_SETUP_ROW_1) 
			      {
				   matrixKeypad->.state = KEYPAD_STATE_DELAY;
			      }
		     }
		      break;


		case KEYPAD_STATE_SETUP_ROW_1:
		case KEYPAD_STATE_SETUP_ROW_2:
		case KEYPAD_STATE_SETUP_ROW_3:
		case KEYPAD_STATE_SETUP_ROW_4:
		   local_j = unmap_pin(virtual_pin);
		   for (local_i = 0; local_i < matrixKeypad->.rows; ++local_i)
		   {
			  if (local_i == matrixKeypad->.current_row)
	                  {
			     set_pin(map_pin(local_j ), LOW);
			  }
			  else
	                  {
			     set_pin(map_pin(local_j ), INPUT);
			  }
			  local_j = map_next_physical_pin[local_j];
		   }      
		   ++matrixKeypad->.current_row;
		   matrixKeypad->.state  = KEYPAD_STATE_SETUP_ROW_1_WAIT;
		    
		break;

		case KEYPAD_STATE_READ_ROW_1:
		case KEYPAD_STATE_READ_ROW_2:
		case KEYPAD_STATE_READ_ROW_3:
		case KEYPAD_STATE_READ_ROW_4:

		   local_j = matrixKeypad->.column_pin;
		   for (local_k = 0; local_k < matrixKeypad->.columns; ++ local_k)
		   {
		      local_i = map_pin(local_j);
		      if (!read_pin(local_i))
		      {
                           matrixKeypad->.current_button = matrixKeypad->.testing_button;
			   if (matrixKeypad->.testing_button < 16)
			   {
				   matrixKeypad->.current_reading |= uint16_bitfield[matrixKeypad->.testing_button];
			   }
		      }	
		      local_j = map_next_physical_pin[local_j];
		      ++matrixKeypad->.testing_button; 
		   }

		   if (matrixKeypad->.current_row == matrixKeypad->.rows)
		   {
			  matrixKeypad->.state = KEYPAD_STATE_DELAY;
		   }
		   else 
		   {
			  matrixKeypad->.state = KEYPAD_STATE_SETUP_ROW_1;
		   }
		   
		break;







		case KEYPAD_STATE_DELAY:
                   queue_address = matrixKeypad->.queue;
		   
                   if (matrixKeypad->.buffer_mode == KEYPAD_BUFFER_MODE_CURRENT_BUTTON)
                   {
                        tp.generic.buffer = matrixKeypad->.current_button;
                   }
		   else if (matrixKeypad->.buffer_mode == KEYPAD_BUFFER_MODE_LAST_BUTTON && matrixKeypad->.current_button != NO_KEY_PRESSED)
                   {
				tp.generic.buffer = matrixKeypad->.current_button;
                   }
                   else if (matrixKeypad->.buffer_mode == KEYPAD_BUFFER_MODE_BINARY)
                   {
                        tp.generic.buffer = matrixKeypad->.current_reading;
                   }

                   if (matrixKeypad->.queue_mode == KEYPAD_QUEUE_MODE_BUTTON_DOWN)
                   {

                       if (matrixKeypad->.current_button != NO_KEY_PRESSED  &&
                           matrixKeypad->.previous_button == NO_KEY_PRESSED)
                       {
			   push_byte(matrixKeypad->.current_button);
                       }
                   }
                   if (matrixKeypad->.queue_mode == 2)
                   {
                       if (matrixKeypad->.current_button != NO_KEY_PRESSED  &&
                           matrixKeypad->.previous_button == NO_KEY_PRESSED)
                       {
                           push_byte(val_to_ascii(matrixKeypad->.current_button));
                       }
                   }
                   else if (matrixKeypad->.queue_mode == 3)
                   {
                       if ( matrixKeypad->.current_reading != matrixKeypad->.previous_reading)
                       {
                           push_word(matrixKeypad->.current_reading);
                       }
                 }
       
		 if (matrixKeypad->.current_reading != matrixKeypad->.previous_reading)
		 {
		    matrixKeypad->.previous_reading = matrixKeypad->.current_reading;
		 }
		 if (matrixKeypad->.current_button != matrixKeypad->.previous_button)
		 {
		    matrixKeypad->.previous_button = matrixKeypad->.current_button;
		 }
		 matrixKeypad->.state = KEYPAD_STATE_SETUP_ALL_LOW;
		break;
		case KEYPAD_STATE_IDLE:
		break;
              } // end keypad switch
      	      local_i = map_pin(map_next_physical_pin[unmap_pin(virtual_pin) ]);
              put_tp2(local_i);
}


