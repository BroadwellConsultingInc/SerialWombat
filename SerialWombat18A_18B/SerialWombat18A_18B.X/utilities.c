#ifndef COMPILING_FIRMWARE
   #include <stdio.h>
#endif

#include <stdint.h>


//#include "types.h"
#define COMPILING_UTILITIES
#include "utilities.h"
//#include "global_data.h"
#ifndef COMPILING_FIRMWARE
 #include "test.h"
#endif


uint8_t user_buffer[SIZE_OF_USER_BUFFER];


#ifdef RANDOM_ENABLE
mixed32_t random_number;
#endif
mixed32_t util_local_temp32_1;
uint16_t util_local_temp16_1;
mixed16_t util_local_temp16_2;
uint8_t util_local_i, util_local_j, util_local_k;
uint16_t utility_incrementing_number;

#ifdef UTILITY_SINE_WAVE_GENERATOR_ENABLE
sin_data_t sin_data[3];
#endif


#pragma udata




#ifndef COMPILING_FIRMWARE

void error (void)
{
    //printf("ERROR THROWN!  Error: %d\n",error);
    txbuffer[0] = 'E';
}

void delay_cycles16(uint16_t cyclestodelay)
{
   return;
}


rom const uint8_t map_physical_pin_ad_table[NUMBER_OF_PHYSICAL_PINS + 1]=
{
      /* 1 */	39,  //TODO check into port RE3 on this pin
      /* 2 */	38,
      /* 3 */	37,
      /* 4 */	36,
      /* 5 */	35,
      /* 6 */	34,
      /* 7 */	33,
      /* 8 */   32,
      /* 9 */ 	31,
      /* 10*/	30,
      /* 11 */	29,
      /* 12 */	28, 
      /* 13 */	27,
      /* 14 */	26,
      /* 15 */	25,
      /* 16 */	24,
      /* 17 */	23,
      /* 18 */	22,
      /* 19 */	21,
      /* 20 */	20,
      /* 21 */	19,
      /* 22 */	18,
      /* 23 */	17,
      /* 24 */	16,
      /* 25 */	15, 
      /* 26 */	14, 
      /* 27 */	13,
      /* 28 */	12,
      /* 29 */	11,
      /* 30 */  10,
      /* 31 */	 9,
      /* 32 */	 8,
      /* 33 */	 7,
      /* 34 */	 6,
      /* 35 */	 5,
      /* 36 */	 4,
      /* 37 */	 3,
      /* 38 */	 2,
      /* 39 */	 1,
      /* 40 */	 0
    };

rom const uint8_t map_next_physical_pin[NUMBER_OF_PHYSICAL_PINS + 1] =
{
      /* 0 */	0,  //Pins are indexed from 1.
      /* 1 */	2, 
      /* 2 */	3,
      /* 3 */	4,
      /* 4 */	5,
      /* 5 */	7,
      /* 6 */	7,
      /* 7 */	8,
      /* 8 */   9,
      /* 9 */ 	10,
      /* 10*/	15,
      /* 11 */	15,
      /* 12 */	15,
      /* 13 */	15,
      /* 14 */	15,
      /* 15 */	19,
      /* 16 */	19,
      /* 17 */	19,
      /* 18 */	19,
      /* 19 */	20,
      /* 20 */	21,
      /* 21 */	22,
      /* 22 */	27,
      /* 23 */	27,
      /* 24 */	27,
      /* 25 */	27,
      /* 26 */	27,
      /* 27 */	28,
      /* 28 */	29,
      /* 29 */	30,
      /* 30 */  33,
      /* 31 */	33,
      /* 32 */	33,
      /* 33 */	34,
      /* 34 */	35,
      /* 35 */	36,
      /* 36 */	37,
      /* 37 */	38,
      /* 38 */	39,
      /* 39 */	40,
      /* 40 */	0
    };

#endif



uint16_t vread_ad(void)
{
    return (read_ad(virtual_pin));  //TODO
}

uint8_t PinToAdBuffer[NUMBER_OF_PHYSICAL_PINS] =
{
	0,//0
	1,//1
	2,//2
	3,//3
	4,//4
	5,//5
	255,//6
	255,//7
	255,//8
	255,//9
	255,//10
	255,//11
	255,//12
	255,//13
	255,//14
	8,//15
	7,//16
	6,//17
	9,//18
};

const uint16_t pinBitmap[] =
{
	0x0001,  // RA0
	0x0002,  // RA1
	0x0001,  // RB0
	0x0002,  // RB1
	0x0004,  // RB2
	0x0008,  // RB3
	0x0004,  // RA2
	0x0008,  // RA3
	0x0010,  // RA4
	0x0040,  // RB6
	0x0080,  // RB7
	0x0100,  // RB8
	0x0200,  // RB9
	0x0400,  // RB10
	0x0800,  // RB11
	0x1000,  // RB12
	0x2000,  // RB13
	0x4000,  // RB14
	0x8000,  // RB15
};

const uint8_t pinPort[] =
{
	0x00,  // RA0
	0x00,  // RA1
	0x01,  // RB0
	0x01,  // RB1
	0x01,  // RB2
	0x01,  // RB3
	0x00,  // RA2
	0x00,  // RA3
	0x00,  // RA4
	0x01,  // RB6
	0x01,  // RB7
	0x01,  // RB8
	0x01,  // RB9
	0x01,  // RB10
	0x01,  // RB11
	0x01,  // RB12
	0x01,  // RB13
	0x01,  // RB14
	0x01,  // RB15
};


uint16_t vpinBitmap(void)
{
	if (virtual_pin >= NUMBER_OF_VIRTUAL_PINS)
	{

		return (0);
	}
	return (pinBitmap[virtual_pin]);

}

uint8_t getDMAInputSample(uint8_t pin, uint8_t sample)
{
	uint16_t bitmap = pinBitmap[pin];
	if (pinPort[pin])
	{
		// Port B
		return ( (InputArrayB[sample] & bitmap) > 0);
	}
	else
	{
		// Port A
		return ( (InputArrayA[sample] & bitmap) > 0);
	}

}
uint8_t vpinPort(void)
{
	if (virtual_pin >= NUMBER_OF_VIRTUAL_PINS)
	{

		return (0xFF);
	}
	return (pinPort[virtual_pin]);

}

#ifndef CACHED_ADREADINGS
uint16_t read_ad(uint8_t vpin)
{
	switch (vpin)
	{
		case 0: // RA0, AN0
			return(ADC1BUF0);
		break;

		case 1: // RA1, AN1
			return(ADC1BUF1);
		break;

		case 2: //RB0, AN2
			return(ADC1BUF2);
		break;

		case 3: //RB1, AN3
			return(ADC1BUF3);
		break;

		case 4: //RB2, AN4
			return(ADC1BUF4);
		break; 

		case 5:// RB3, AN5
			return(ADC1BUF5);
		break;
		case 15: // RB12, AN 8
			return(ADC1BUF8);
		break;  

		case 16: // RB13, AN 7
			return(ADC1BUF7);
		break;

		case 17:  // RB14, An6
			return(ADC1BUF6);
		break;

		case 18:  // RB15, AN9
			return(ADC1BUF9);
		break;
		
		default:
		{
			if (read_pin(vpin))
			{
				return (0xFFFF);
			}
			else
			{
				return(0);
			}
		}
		break;


	}
}
#endif



void delay_timer3_ticks(uint16_t ticks)
{
#ifdef OLDWOMBATSTUFF
	util_local_temp32_1.s = ticks;
	util_local_j = TMR3L;
	while( util_local_temp32_1.s > 0)
	{
		util_local_i = TMR3L;
		util_local_k = util_local_i - util_local_j;
		util_local_temp32_1.s -= util_local_k;
		util_local_j = util_local_i;
	}
#endif
}

uint32_t read_free_running_timer()
{
	extern volatile uint32_t System1msCount;
	uint32_t read1 = System1msCount;
	uint32_t read2 = System1msCount;
	while (read1 != read2)
	{
		read1 = System1msCount;
		read2 = System1msCount;
	}
	return (read1);
}

#ifdef COMPILING_FIRMWARE

#else

void pin_low(uint8_t pin)
{
	set_pin(pin,LOW);
}

void pin_high(uint8_t pin)
{
	set_pin(pin,HIGH);
}

void pin_input(uint8_t pin)
{
	set_pin(pin,INPUT);
}

void set_pin(uint8_t pin, uint8_t mode)
{
   static uint8_t in_processing = 0;
   if (pin >= NUMBER_OF_VIRTUAL_PINS)
   {
       //printf ("ERROR: set_pin on pin greater than virtual pins: pin %d mode %d test %d\n",pin,mode,global_test_number);
   } 
   else if (mode > 2)
   {
       //printf ("ERROR: set_pin on invalid mode: pin %d mode %d test %d\n",pin,mode,global_test_number);
   }
   else
   {
     	pin_output_array[pin] = mode;
   }
   if (! in_processing)
   {
	   in_processing = 1;
	   call_update_functions();
	   in_processing = 0;
   }
}

uint8_t read_pin(uint8_t pin_to_read)
{
   if (pin_output_array[pin_to_read])
   {
      return (1);
   }
   else
   {
      return(0);
   }
}
#endif

uint8_t ascii_to_val(uint8_t a)
{
	util_local_j = a;
	if ( util_local_j <= '0')
        {
		return (0);
        }
        if ( util_local_j <='9')
        {
		return ( util_local_j - '0');
        }
        if ( util_local_j >= 'A' && util_local_j <= 'F')
        {
                return ((util_local_j + 10) - 'A');
        }
        if ( util_local_j >= 'a' && util_local_j <= 'f')
        {
                return ((util_local_j + 10) - 'a');
        }
        return (0);
}

uint16_t hex_ascii_to_val16(uint8_t* a, uint8_t count)
{
	util_local_temp16_2.u = 0; 
  
  
  for (util_local_i = 0; util_local_i < count; ++util_local_i)
  {
	util_local_temp16_2.u *= 16; 
        util_local_j = *a;	
	util_local_temp16_2.u += ascii_to_val(util_local_j);
	
	++a; 
    }
    return (util_local_temp16_2.u);
}
uint32_t hex_ascii_to_val32(uint8_t* a, uint8_t count)
{
  uint32_t temp32;
  temp32 = 0;
  uint8_t util_local_i, util_local_j;
  for (util_local_i = 0; util_local_i < count; ++util_local_i)
  {
	temp32 *= 16; 
        util_local_j = *a;	
	if (util_local_j == ' ')
	{
	     //do nothing
	}
	if ( util_local_j < '0')
        {
            return(0);
	}
	else if ( util_local_j <='9')
        {
		temp32 += util_local_j - '0';
        }
	else if ( util_local_j >= 'A' && util_local_j <= 'F')
        {
                temp32 += util_local_j + 10 - 'A';
        }
	else if ( util_local_j >= 'a' && util_local_j <= 'f')
        {
                temp32+= (util_local_j + 10 - 'a');
        }
	else
	{
		return (0);
	}
	++a; 
    }
    return (temp32);
}

uint16_t rx_dec_ascii_to_val16(uint8_t rxbuffer_index, uint8_t count)
{
  util_local_temp16_1  = 0;
  util_local_k = count + rxbuffer_index;
  
  for (util_local_j = rxbuffer_index; util_local_j < util_local_k; ++util_local_j)
  {
	util_local_temp16_1 *= 10; 
	
	if (rxbuffer[util_local_j] == ' ')
	{
	     //do nothing
	}
	if ( rxbuffer[util_local_j] < '0')
        {
            return(0);
	}
	else if ( rxbuffer[util_local_j] <='9')
        {
		util_local_temp16_1 += rxbuffer[util_local_j] - '0';
        }
	else
	{
		return (0);
	}
    }
    return (util_local_temp16_1);
}

uint32_t dec_ascii_to_val32(uint8_t* a,uint8_t count)
{
  uint32_t val =0;
  uint8_t i;
  
  for (i = 0; i < count; ++i)
  {
	val *= 10; 
	
	if (*a == ' ')
	{
	     //do nothing
	}
	if ( *a < '0')
        {
            return(0);
	}
	else if ( *a <='9')
        {
		val += *a - '0';
        }
	else
	{
		return (0);
	}
	++a; 
    }
    return (val);
}
uint8_t dec_ascii_to_val8(uint8_t* a,uint8_t count)
{
  
  util_local_j = 0; 
  
  for (util_local_i = 0; util_local_i < count; ++util_local_i)
  {
	util_local_j *= 10; 
	
	if (*a == ' ')
	{
	     //do nothing
	}
	if ( *a < '0')
        {
            return(0);
	}
	else if ( *a <='9')
        {
		util_local_j += *a - '0';
        }
	else
	{
		return (0);
	}
	++a; 
    }
    return (util_local_j);
}


uint8_t val_to_ascii(uint8_t a)
{
        util_local_j = a;	
	util_local_j &= 0x0F;
        if ( util_local_j <= 9)
        {
		return ( util_local_j + '0');
        }
        return (util_local_j + ('A' - 10));
}

void val16_to_hex(mixed16_t val, uint8_t* string)
{
    util_local_temp16_2 = val;
   //Expects string to be 4 bytes long, no null terminator
   string[3] = val_to_ascii(util_local_temp16_2.bytes.lowbyte);
   util_local_temp16_2.bytes.lowbyte >>= 4;
   string[2] = val_to_ascii(util_local_temp16_2.bytes.lowbyte);
   string[1] = val_to_ascii(util_local_temp16_2.bytes.highbyte);
   util_local_temp16_2.bytes.highbyte >>= 4;
   string[0] = val_to_ascii(util_local_temp16_2.bytes.highbyte);
}

void put_buffer(uint8_t id,uint16_t value)
{
   if (id < NUMBER_OF_PHYSICAL_PINS)
   {
      if (id == virtual_pin)
      {
	 tp->generic.buffer = value;
      }
      else
      {
        pin_update_registers[id].generic.buffer = value;
      }
   }

}

    
uint16_t get_buffer(uint8_t id)
{
   
  
   util_local_j = id;
   if (util_local_j < NUMBER_OF_VIRTUAL_PINS)
   {
	return (pin_update_registers[util_local_j].generic.buffer);
   }
#if 0
   else if (util_local_j <= BUFFER_TO_USER_RAM_MAX && 
		   util_local_j >= BUFFER_TO_USER_RAM)
   {
	   util_local_temp16_2.bytes.lowbyte =  (user_buffer[buffer_to_pin_offset + ((util_local_j - BUFFER_TO_USER_RAM ) * 2)]);
	   util_local_temp16_2.bytes.highbyte =  (user_buffer[buffer_to_pin_offset + ((util_local_j - BUFFER_TO_USER_RAM ) * 2) + 1]);
	   return(util_local_temp16_2.u);
   }
#endif
   else
   {
	   switch (util_local_j)
	   {
#if 0
		   case BUFFER_NUM_OF_DROPPED_FRAMES:
			   return (dropped_frames.uwords.l);
		   case BUFFER_FREE_RUNNING_TIMER:
		   {
			DISABLE_ALL_INTERRUPTS();
#ifdef COMPILING_FIRMWARE				   
			util_local_temp16_2.bytes.lowbyte = TMR3L;
			   util_local_temp16_2.bytes.highbyte = TMR3H;
#endif
			ENABLE_ALL_INTERRUPTS();
			return (util_local_temp16_2.u);
		   }
		   break;

		   case BUFFER_INTERRUPT_OCCURRED:
		   {
			   if (Interrupt_Occurred & 0x01)
		           {
				   Interrupt_Occurred = 0;
				   return (1);
			   }
			   else
			   {
				   return 0;
			   }
		   }

	           break;
#endif
#ifdef UTILITY_SINE_WAVE_GENERATOR_ENABLE
		   case BUFFER_SINE_1:
		       return (gen_sin_wave(0)); 
		   break;  
		   case BUFFER_SINE_2:
		       return (gen_sin_wave(1)); 
		   break;  
		   case BUFFER_SINE_3:
		       return (gen_sin_wave(2)); 
		   break;  
		   case BUFFER_SINE_SUM_2:
		       return ( (((uint24)gen_sin_wave(0)) + gen_sin_wave(1))>> 1); 
		   break;  
		   case BUFFER_SINE_SUM_3:
		       return ( (((uint24)gen_sin_wave(0)) + gen_sin_wave(1) + gen_sin_wave(2))>> 2); 
		   break;  
#endif
#ifdef USAGE_TRACKING_ENABLE
		   case BUFFER_TX_INTERRUPTS:
		       return ((uint16_t)tx_interrupts.u); 
		   break;  
		   case BUFFER_RX_INTERRUPTS:
		       return ((uint16_t)rx_interrupts.u); 
		   break;  
#endif

#ifdef CLOCK_TIME_ENABLE
		   case BUFFER_CLOCK_SECONDS:
                      return(clock_seconds);
                      break;
		  case BUFFER_CLOCK_MINUTES:
                      return(clock_minutes);
                      break;
		  case BUFFER_CLOCK_HOURS:
                       return(clock_hours);
                      break;
		  case BUFFER_CLOCK_DAYS:
                       return(clock_days);
                      break;
#endif


	       case BUFFER_INCREMENTING_NUMBER:
		       return (++utility_incrementing_number);
	       break;
#if 0
#ifdef COMPILING_FIRMWARE
	       case BUFFER_PINS2345671413:
	            return(PORTA);
		break;
	       case BUFFER_PINS1516171823242526:
		    return (PORTC);
		break;
	       case BUFFER_PINS1920212227282930:
		    return (PORTD);
	       break;
	       case BUFFER_PINS3334353637383940:
		    return (PORTB);
	       break;
#endif
#endif

#ifdef RANDOM_ENABLE

	       case BUFFER_RANDOM_NUMBER:
		       return (random());
	       break;
#endif
	       case BUFFER_ZERO_VALUE:
	               return (0);
	       break;
#if 0
	       case  BUFFER_UART_RX_OVERFLOWS:
	             return (rxbuffer_overflow);
	       break;
#endif
	       default:
	         return (0);
	       break;
	   }
    }
}

#ifdef UTILITY_SPI_ENABLE
uint8_t slow_SPI00_send(uint8_t data,uint8_t delay, uint8_t clkpin, uint8_t sdipin, uint8_t sdopin)
{
	util_local_i = data;
        util_local_k = 0;

	if (delay)
	{

		for(util_local_j = 0; util_local_j < 8; ++util_local_j)
		{
			util_local_temp16_2.bytes.lowbyte = delay;
			while (util_local_temp16_2.bytes.lowbyte--);
			pin_low(clkpin);
			if (util_local_i & 0x80)
			{
			  pin_high(sdopin);
			}
			else
			{	
			  pin_low(sdopin);
			}
			util_local_i <<= 1;

			util_local_temp16_2.bytes.lowbyte = delay;
			while (util_local_temp16_2.bytes.lowbyte--);
			pin_high(clkpin);
			util_local_k <<= 1;
			if (read_pin(sdipin))
			{
				util_local_k |= 0x01;
			}
			
		}
	}
	else
	{
		for(util_local_j = 0; util_local_j < 8; ++util_local_j)
		{
			pin_low(clkpin);
			if (util_local_i & 0x80)
			{
			  pin_high(sdopin);
			}
			else
			{	
			  pin_low(sdopin);
			}
			util_local_i <<= 1;

			pin_high(clkpin);
			if (read_pin(sdipin))
			{
				util_local_k |= 0x01;
			}
		}
	}
	pin_low(clkpin);

	return(util_local_k);
}

void set_MCP4821(uint8_t pin,uint16_t width)
{
#ifdef COMPILING_FIRMWARE
       pin_high(SDO_VIRTUAL_PIN);
       pin_low(SCK_VIRTUAL_PIN);
       SSPSTAT = 0;
       SSPSTATbits.SMP = 1;
       SSPSTATbits.CKE = 0; //transfer on Idle to active
       SSPCON1 = 0x30;
       PIR1bits.SSPIF = 0;	
       pin_low(pin);
       util_local_temp16_2.u = width;
       util_local_temp16_2.u >>= 4;
       util_local_temp16_2.bytes.highbyte |= 0x10; //Disable chip shutdown
       SSPBUF = util_local_temp16_2.bytes.highbyte;
       while(PIR1bits.SSPIF == 0);

       SSPBUF =  util_local_temp16_2.bytes.lowbyte;
       while(PIR1bits.SSPIF == 0);
       pin_high(pin);
#endif
}

void set_MCP41XXX(uint8_t pin, uint8_t width)
{
#ifdef COMPILING_FIRMWARE
   pin_high(SDO_VIRTUAL_PIN);
   pin_low(SCK_VIRTUAL_PIN);
   SSPSTAT = 0;
   SSPSTATbits.SMP = 1;
   SSPSTATbits.CKE = 0; //transfer on Idle to active
   SSPCON1 = 0x30;
   PIR1bits.SSPIF = 0;	
   pin_low(pin); 
   SSPBUF = 0x11; //Command byte:  Write to pot0


   while(PIR1bits.SSPIF == 0);
   SSPBUF = width; 
   while(PIR1bits.SSPIF == 0);
   pin_low(pin);
#endif
}
#endif

void set_pwm(uint8_t pin, uint16_t width)
{
	uint16_t pinMask = 0;
	uint8_t inB = 1;
	uint32_t width32;

		if (width == 0)
		{
			pin_low(pin);
			return;
		}
		else if (width >= 65500u)
		{
			pin_high(pin);
			return;
		}

	
	width32 = (uint32_t)width * SIZE_OF_DMA_ARRAY;
	width32 >>= 16;
	width = (uint16_t) width32;
	
	if (pin < NUMBER_OF_PHYSICAL_PINS)
	{
		 pinMask = PinBitmapB[pin];
		 if (pinMask == 0)
		 {
			 pinMask = PinBitmapA[pin];
			 inB = 0;
             
		 }
         
	}

	{
		uint8_t i;
		if (inB)
		{
			for (i = 0; i < width; ++ i) 
			{
				OutputArrayB[ i] |= pinMask;
			}
			for (; i <SIZE_OF_DMA_ARRAY ; ++ i) 
			{
				OutputArrayB[ i] &= ~pinMask;
			}
			TRISB &= ~pinMask;
		}
		else
		{
			for (i = 0; i < width; ++ i) 
			{
				OutputArrayA[ i] |= pinMask;
			}
			for (; i <SIZE_OF_DMA_ARRAY ; ++ i) 
			{
				OutputArrayA[ i] &= ~pinMask;
			}
			TRISA &= ~pinMask;
		}
	}
}
void vset_pwm( uint16_t width)
{
	set_pwm(virtual_pin,width);
}


void update_pwm(void)
{
#ifdef SOFTWAREPWM_ENABLE
     if (tp.generic.hw_mode == 0 || tp.generic.hw_mode > 8)
     {
         return;
     }
     
     if (tp.generic.duty_cycle != 0 && tp.generic.duty_cycle != 255)
     {
          ++tp.generic.hw_counter ;
          if (tp.generic.hw_counter >= tp.generic.duty_cycle)
          {
              vpin_low();
          }
          if (tp.generic.hw_counter >= uint8_bitfield[tp.generic.hw_mode] )
          {
             vpin_high();
             tp.generic.hw_counter = 0;
          }
      }
#endif
}

#ifdef CACHED_ADREADINGS
uint8_t map_physical_pin_ad(uint8_t pin)
{
    if (pin > NUMBER_OF_PHYSICAL_PINS)
    {
        return (255);
    }
    return (map_physical_pin_ad_table[pin]);
}
#endif

#ifdef RANDOM_ENABLE
        //32,7,5,3,2,1
         #define MASK 0x80000057
uint16_t random(void)
{
  
	   for (util_local_i = 0; util_local_i < 16; ++util_local_i)
           {
              if ( random_number.u & 0x00000001)
              {
                   random_number.u = (((random_number.u ^ MASK) >> 1) | 0x80000000);
              }
              else
              {
                    random_number.u >>=1;
              }
           }
	   return( (uint16_t) random_number.u);
}

void random_seed(uint32_t seed)
{
	if (seed == 0)
	{
		random_number.u = 1;
	}
	else
	{
		random_number.u = seed;
	}
}
#endif

rom const uint8_t uint8_bitfield[8] = {
        0x01,
        0x02,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80,
        };
rom const uint8_t uint8_bitlowermask[8] = {
        0x01,
        0x03,
        0x07,
        0x0F,
        0x1F,
        0x3F,
        0x7F,
        0xFF,
        };
rom const uint8_t uint8_bitfield_invert[8] = {
        0xFE,
        0xFD,
        0xFB,
        0xF7,
        0xEF,
        0xDF,
        0xBF,
        0x7F,
        };
rom const uint16_t uint16_bitfield[16] = {
        0x0001,
        0x0002,
        0x0004,
        0x0008,
        0x0010,
        0x0020,
        0x0040,
        0x0080,
        0x0100,
        0x0200,
        0x0400,
        0x0800,
        0x1000,
        0x2000,
        0x4000,
        0x8000,
        };
#ifdef UTILITY_SINE_WAVE_GENERATOR_ENABLE
uint16_t gen_sin_wave (uint8_t wavenum)
{
     //TODO not tested
     //TODO not documented
     // w = freq in hz * 2 * pi
     // t = sample time 
     // K =    cos (w * T) ; K1 can range -1 <-> 1, exclusive
     // Example, 697 Hz, 10 kHz sampling rate
     // cos (.0001 * 2 * pi * 697) = 
     //  = 29676 / 2 ^ 15
     //signed short data1 = 0;
     // data 2 = sin(w*T) = sin (.0001 *2 * pi * 697) = .424 = 6848 / 2 ^ 14
        //signed short data2 =   6948;

//50 hz at  1ms frames sin_data[0].k = 31165;
//		       sin_data[0].data1 = 0;
//		       sin_data[0].data2 = 5060;


    util_local_temp32_1.s = sin_data[wavenum].k * (int32) sin_data[wavenum].data2  ;
    if (util_local_temp32_1.s < 0)
    {
	   util_local_temp32_1.s *= -1;
	   util_local_temp32_1.u >>= 14; 
	   util_local_temp32_1.s *= -1;
    }
    else
    {
	   util_local_temp32_1.s >>= 14; 
    }
    util_local_temp32_1.s -= sin_data[wavenum].data1;
    sin_data[wavenum].data1 = sin_data[wavenum].data2;
    sin_data[wavenum].data2 = (signed short) util_local_temp32_1.s;
    util_local_temp32_1.s *=2;
    util_local_temp32_1.s += 65536 / 2;
    if (util_local_temp32_1.s > 65535)
    {
         util_local_temp32_1.uwords.l = 65535;
    }
    else if (util_local_temp32_1.s < 0)
    {
         util_local_temp32_1.uwords.l = 0;
    }
    return ( (uint16_t) util_local_temp32_1.uwords.l);
    

}
#endif

//Application Function


uint8_t get_user_buffer(uint16_t offset)
{
		if (offset > sizeof (user_buffer))
		{
    return(0);
		}

		return (user_buffer[offset]);
}


//Application Function

#ifdef __18CXX
#ifdef SIZE_OF_USER_BUFFER
void put_user_buffer(uint16_t offset, uint8_t data)
{
	if (offset < sizeof(user_buffer))
	{
		user_buffer[offset] = data;
	}
        return ;
}
#endif
#else

void put_user_buffer(uint16_t offset, uint8_t data)
{
    
	
		user_buffer[offset] = data;

}
#endif

#ifdef __18CXX

#ifdef SIZE_OF_USER_BUFFER
void get_user_buffer_block(uint16_t offset, uint16_t length, uint8_t* dest)
{
	while (offset < sizeof(user_buffer) && length > 0)
	{
             *(dest++) = user_buffer[offset++];
	     --length;
	}
        return;
}
#endif
#else
uint32_t get_user_buffer_block_calls = 0;
void get_user_buffer_block(uint16_t offset, uint16_t length, uint8_t* dest)
{

        ++get_user_buffer_block_calls; 
	while (offset < sizeof(user_buffer) && length > 0)
	{
             *(dest++) = user_buffer[offset++];
	     --length;
	}

}
#endif

void orCount(uint16_t* ptr, uint16_t bitmap, uint8_t count);
/*
void orCount(uint16_t* ptr, uint16_t bitmap, uint8_t count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		*ptr |= bitmap;
		++ptr;
	}
}
*/
void andCount(uint16_t* ptr, uint16_t bitmap, uint8_t count);
/*
void AndCount(uint16_t* ptr, uint16_t bitmap, uint8_t count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		*ptr &= bitmap;
		++ptr;
	}
}*/

void updatePulse(uint8_t pin)
{
	pin_register_t* pinPtr = &pin_update_registers[pin];
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	uint8_t nextLocationToQueue = pinPtr->pulse_output.lastDMA;
	uint16_t* baseAddress;

	int nextDMAHWTransfer ; // The next DMA location that will be transferred by Hardware.  Don't overwrite this one.  We need to catch up to this.

	if (pinPort[pin] == 0)
	{
		baseAddress = OutputArrayA;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT0 ; 
	}
	else
	{
		baseAddress = OutputArrayB;
		nextDMAHWTransfer = SIZE_OF_DMA_ARRAY - DMACNT1 ;
	}

	// This can go a few ways:
	
	//1: The DMA pointer is at a lower address than the last byte we queued.  If this is the case, go to case 2.  Otherwise, skip to case 6
	//2: Are there enough high bits left to fill the DMA to the end? yes  Do that, subtract the nubmer from the high count, and skip to case 6 , else go to 3
	//3: There wasn't enough to fill the DMA to the end.  Put them all in there.  Go to 4.
	//4: Are there enough low bits to fill the DMA to the end?  Yes: Do that, subtract the nubmer from the low count, and skip to case 7, else go to step 5
	//5: There weren't enough low bits to fill the DMA to the end. Fill them all  Reset the high and low counters, and go to state 1.
	//6:  Are there enough High bits to fill the DMA from the beginning to the DMA pointer? Yes:  Do that, subtract from counter.  Done.  No:  Put them all in and go to step 7.
	//7:  Are there enough Low bits to fill the DMA from the beginning to the DMA pointer? Yes:  Do that, subtract from counter.  Done.  No:  Put them all in, reset counters and go to step 6. 
	//8: Done


	uint8_t state = 1;


	while (state < 8)
	{
		switch (state)
		{
			case 1:
				{

					if (nextDMAHWTransfer < nextLocationToQueue)
					{
						// DMA counter rolled over.
						state = 2;
					}
					else
					{
						state = 6;
					}	

				}
				break;
			case 2:
			{
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (pinPtr->pulse_output.highRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.highRemaining -= AvailableDMASpace;
					orCount(&OutputArrayB[nextLocationToQueue],bitmap,AvailableDMASpace);
					nextLocationToQueue = 0;
					state = 6;
				}
				else
				{
					state = 3;
				}


			}
			break;

			case 3:
			{
					orCount(&OutputArrayB[nextLocationToQueue],bitmap,pinPtr->pulse_output.highRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.highRemaining;
					pinPtr->pulse_output.highRemaining = 0;
					state = 4;

			}
			break;

			case 4:
			{
				uint8_t AvailableDMASpace = SIZE_OF_DMA_ARRAY - nextLocationToQueue ;
				if (pinPtr->pulse_output.lowRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.lowRemaining -= AvailableDMASpace;
					andCount(&OutputArrayB[nextLocationToQueue],invbitmap,AvailableDMASpace);
					nextLocationToQueue = 0;
					state = 7;
				}
				else
				{
					state = 5;
				}

			}
			break;

			case 5:
			{
					andCount(&OutputArrayB[nextLocationToQueue],invbitmap,pinPtr->pulse_output.lowRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.lowRemaining;
					pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
					pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
					state = 1;

			}
			break;

			case 6:
			{
				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (pinPtr->pulse_output.highRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.highRemaining -= AvailableDMASpace;
					orCount(&OutputArrayB[nextLocationToQueue],bitmap,AvailableDMASpace);
					nextLocationToQueue  += AvailableDMASpace;
					state = 8;
				}
				else
				{
					orCount(&OutputArrayB[nextLocationToQueue],bitmap,pinPtr->pulse_output.highRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.highRemaining;
					pinPtr->pulse_output.highRemaining = 0;
					state = 7;
				}

			}
			break;

			case 7:
			{
				uint8_t AvailableDMASpace = nextDMAHWTransfer -  nextLocationToQueue ;
				if (pinPtr->pulse_output.lowRemaining > AvailableDMASpace)
				{
					pinPtr->pulse_output.lowRemaining -= AvailableDMASpace;
					andCount(&OutputArrayB[nextLocationToQueue],invbitmap,AvailableDMASpace);
					nextLocationToQueue += AvailableDMASpace;
					state = 8;
				}
				else
				{
					andCount(&OutputArrayB[nextLocationToQueue],invbitmap,pinPtr->pulse_output.lowRemaining);
					nextLocationToQueue+= pinPtr->pulse_output.lowRemaining;
					pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
					pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
					state = 6;
				}

			}
			break;

			default:
			{
				state = 8;
			}
			break;
		

		}
	}

	
	pinPtr->pulse_output.lastDMA = nextLocationToQueue;
}
/*
void updatePulse(uint8_t pin)
{
	pin_register_t* pinPtr = &pin_update_registers[pin];
	uint16_t bitmap = pinBitmap[pin];
	uint16_t invbitmap = ~bitmap;
	uint8_t lastDMA = pinPtr->pulse_output.lastDMA;
	switch (pinPort[pin])
	{
		case 0:
		{
			//A
		}
		break;

		case 1:
		{
			//B
			while (DMACNT1 == 0); // Wait for reload
			int currentNextDMALocation = SIZE_OF_DMA_ARRAY - DMACNT1 ; // The next DMA location that will be written
			if (currentNextDMALocation < lastDMA)
			{
				// DMA rolled over.  Finish the end.
				for (;lastDMA < SIZE_OF_DMA_ARRAY; ++lastDMA)
				{
					
					//Process data
					if (pinPtr->pulse_output.highRemaining)
					{
						-- pinPtr->pulse_output.highRemaining;
						OutputArrayB[lastDMA] |= bitmap;
					}
					else if (pinPtr->pulse_output.lowRemaining)
					{
						-- pinPtr->pulse_output.lowRemaining;
						OutputArrayB[lastDMA] &= invbitmap;
						if (pinPtr->pulse_output.lowRemaining == 0)
						{
							pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
							pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
						}
					}
				}
                lastDMA = 0;
			}
			for (; lastDMA < currentNextDMALocation; ++lastDMA)
			{
					//Process data
					if (pinPtr->pulse_output.highRemaining)
					{
						-- pinPtr->pulse_output.highRemaining;
						OutputArrayB[lastDMA] |= bitmap;
					}
					else if (pinPtr->pulse_output.lowRemaining)
					{
						-- pinPtr->pulse_output.lowRemaining;
						OutputArrayB[lastDMA] &= invbitmap;
						if (pinPtr->pulse_output.lowRemaining == 0)
						{
							pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
							pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
						}
					}
                    else
                    {
                        pinPtr->pulse_output.lowRemaining = pinPtr->pulse_output.lowReload;
							pinPtr->pulse_output.highRemaining = pinPtr->pulse_output.highReload;
                        
                    }
			}
		}
		break;

	}
	pinPtr->pulse_output.lastDMA = lastDMA;
}
*/
#ifdef COMPILING_FIRMWARE
#ifdef SIZE_OF_USER_BUFFER
void put_user_buffer_block(uint16_t offset, uint16_t length, uint8_t* source)
{
	while (offset < sizeof(user_buffer) && length > 0)
	{
             user_buffer[offset++] = *(source++);
	     --length;
	}
        return;
}
#endif
#else
uint32_t put_user_buffer_block_calls = 0;
void put_user_buffer_block(uint16_t offset, uint16_t length, uint8_t* source)
{
	++put_user_buffer_block_calls;
	while (offset < sizeof(user_buffer) && length > 0)
	{
             user_buffer[offset++] = *(source++);
	     --length;
	}
}
#endif

#ifdef COMPILING_FIRMWARE
void EEPROM_WRITE(uint16_t address, uint8_t value) 
   {  
    #ifdef OLDWOMBATSTUFF
      uint8_t ie;
        if (INTCONbits.GIE)
	{
	   ie = 1;
	}
	else
	{
	   ie = 0;
	}
        PIR2bits.EEIF = 0; 
#if (LAST_EEPROM_ADDRESS > 255)
        EEADRH = ((uint8_t)(((uint16_t) (address)) >> 8 )); 
#endif
        EEADR  = ((uint8_t) (address)); 
        EEDATA = value;      
        EECON1bits.EEPGD = 0; 
        EECON1bits.CFGS  = 0; 
        EECON1bits.WREN  = 1; 
        INTCONbits.GIE = 0;
        EECON2 = 0x55; 
        EECON2 = 0xAA; 
        EECON1bits.WR  = 1; 
        EECON1bits.WREN  = 0; 
        while (!PIR2bits.EEIF); 
        PIR2bits.EEIF = 0 ; 
        if (ie) INTCONbits.GIE = 1; 
#endif
}
#endif

#ifndef COMPILING_FIRMWARE

void vpin_high(void)
{
   pin_output_array[virtual_pin] = 1;
   call_update_functions();
}
void vpin_low(void)
{
   pin_output_array[virtual_pin] = 0;
   call_update_functions();
}
void vpin_input(void)
{
   call_update_functions();
}
uint8_t vpin_read(void)
{
   return(pin_output_array[virtual_pin] >0);
}
#endif

#ifndef COMPILING_FIRMWARE

void get_tp2_asm(uint8_t pin)
{
   memcpy(&tp2,&pin_update_registers[pin], sizeof(pin_register2_t)); 
}
void put_tp2_asm(uint8_t pin)
{
   memcpy(&pin_update_registers[pin],&tp2, sizeof(pin_register2_t));
}

void print_pin(int pin,unsigned char high,unsigned char low)
{
   if (read_pin(pin))
   {
        //printf("%c",high);
   }
   else
   {
      //printf("%c",low);
   }
}
void print_pin_block(int pin)
{
   if (read_pin(pin))
   {
        //printf("#");
   }
   else
   {
      //printf(" ");
   }
}
#endif
uint8_t overall_result = 0;
volatile uint8_t test_stage = 0;
#define TEST_UTILITIES
#ifdef TEST_UTILITIES 
#include <string.h>
#include "mcc_generated_files/uart1.h"
#include "queue.h"
int unit_test_main (void)
{
   uint8_t temp, c1, c2;
   uint16_t temp16;
   uint16_t len, size,freesize;
   uint32_t i,j;
   uint32_t tests = 10000;
   uint16_t current_char = 'A';
   uint16_t expected_char = 'A';
   uint8_t result;
   uint32_t func;
   uint8_t flags;
   uint32_t passedCount = 0;
   uint8_t string[100];
//   int16_t data1,data2;
   uint16_t queue_address;
   mixed16_t mixed16;
   #define QUEUE_ADDRESS 253 
   #define QUEUE_SIZE 90
   const uint8_t pattern[] = "asdljkejjjj0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000siviwojjasdfDDDDDDDDD93nsv9s0ebbbjdjiieosE";
   //const uint8_t pattern[] = "adjk23ijEasdljkn3r2fa0-sd=23rjjasdjfkkkJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJsadjfaaaaEEEEEsdfBBBBbbbbBBBBbb";

  const uint16_t pattern16[] = { 1,2,3,4,5,12345,12345,23456,34567,45678,56789,11111,11111,11111,11111};
   queue_address = QUEUE_ADDRESS;

                  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Starting Utilities Self Test Sequence");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

   //RAM_QUEUE test

  if (sizeof(queue_header_t) != QUEUE_HEADER_SIZE)
  {
      { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Error: queue_header_t is not %d bytes long.  It is %d bytes long\n",QUEUE_HEADER_SIZE,sizeof(queue_header_t));
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); } 
   }
   random_number.u = 1; 
   initialize_queue(queue_address, QUEUE_SIZE);

    

   for (i = 0; i < tests; ++i)
   {
       func = random() & 0x03;
       
       if (func ==  0 )
       {
           result = push_byte (queue_address, current_char );
           if (result == QUEUE_BYTE_STORED)
           {
		  flags = get_queue_flags(queue_address );
 if(0)                 { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lud  +%c %2d 0x%02X\n",i, current_char,get_queue_length(queue_address), get_queue_flags(queue_address));
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   ++current_char;
                   if (current_char> 'Z')
                   {
                       current_char = 'A';
                   }
             }
             else
             {
		  flags = get_queue_flags(queue_address);
 if(0)                 { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lud  +  %2d 0x%02X %d\n",i, get_queue_length(queue_address),flags,result);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }

       }
       if (func ==  1 )
       {
           result = shift_byte (queue_address, &temp);
           if (result == QUEUE_BYTE_SHIFTED)
           {
                   if ( expected_char != temp)
                   {
                        { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nError shift byte: Got %X, expected %X in test %lu\n", temp, expected_char, i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   else
                   {
                         flags = get_queue_flags(queue_address);
			 ++passedCount;
if(0)			 { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu -%c %2d 0x%02X\n",i, temp,get_queue_length(queue_address),flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   ++expected_char;
                   if (expected_char > 'Z')
                   {
                       expected_char = 'A';
                   }
             }
             else
             {
                  flags = get_queue_flags(queue_address);
		
    if(0)              { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu -  %2d 0x%02X\n",i, get_queue_length(queue_address),flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }
       }
       if (func ==  2 )
       {
           temp16 = current_char;
           temp16 <<= 8;
           if (current_char == 'Z')
           {
              temp16 += 'A';
           }
           else
           {
              temp16 += current_char + 1;
           }
           mixed16.u = temp16;
           result = push_word (queue_address, mixed16.u);
           if (result == QUEUE_BYTE_STORED)
           {
		  flags = get_queue_flags(queue_address);
        if(0)          { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu+%c%c %2d 0x%02X\n",i, temp16>>8,temp16 & 0xFF,get_queue_length(queue_address),flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   ++current_char;
                   if (current_char> 'Z')
                   {
                       current_char = 'A';
                   }
                   ++current_char;
                   if (current_char> 'Z')
                   {
                       current_char = 'A';
                   }
             }
             else
             {
		  flags = get_queue_flags(queue_address);
            if(0)      { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu ++ %2d 0x%02X\n",i, get_queue_length(queue_address),flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }
       }
       if (func ==  3 )
       {
           result = shift_word (queue_address, (uint16_t*) &mixed16);
           if (result == QUEUE_BYTE_SHIFTED)
           {
                   if ( 0 && expected_char != temp)
                   {
                        { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nError shift word: Got %X, expected %X in test %lu\n", mixed16.u, expected_char, i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   else
                   {
		         flags = get_queue_flags(queue_address);
			 ++passedCount;
                if(0)         { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu-%c%c %2d 0x%02X\n",i, temp16>>8,temp16 & 0xFF,get_queue_length(queue_address),flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   ++expected_char;
                   if (expected_char > 'Z')
                   {
                       expected_char = 'A';
                   }
                   ++expected_char;
                   if (expected_char > 'Z')
                   {
                       expected_char = 'A';
                   }
             }
             else
             {
		  flags = get_queue_flags(queue_address);
if(0)                  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu -- %2d 0x%02X\n",i, get_queue_length(queue_address),flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }
       }
    }
   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Basic Queue Test Complete.  Passed iterations: %lu\n", passedCount);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

   //RAM_RLE_BYTE test

   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"RAM RLE TEST\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
#ifdef  UTILITY_QUEUE_RLE_ENABLE
   initialize_ram_rle_queue(QUEUE_SIZE, 0);
   current_char = 0;
   expected_char = 0;
    
   if(0)
   //for (i = 0; i < tests; ++i)
   {
       func = random() & 0x01;
       
       if (func ==  0 )
       {
           result = push_byte (queue_address, pattern[current_char]);
           if (result == QUEUE_BYTE_STORED)
           {
		  flags = get_queue_flags(queue_address);
    if(0)              { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu +%c %2d %8u 0x%02X\n",i, pattern[current_char],get_queue_length(queue_address),freesize,flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   ++current_char;
                   if (current_char >= sizeof(pattern) - 1)
                   {
                       current_char = 0;
                   }
             }
             else
             {
		  flags = get_queue_flags(queue_address);
        if(0)          { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  +  %2d %8u 0x%02X\n",i, get_queue_length(queue_address),freesize,flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }

       }
       if (func ==  1 )
       {
           result = shift_byte (queue_address, &temp);
           if (result == QUEUE_BYTE_SHIFTED)
           {
                   if ( pattern[expected_char] != temp)
                   {
                        { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nError: Got %c, expected %c in test %lu\n", temp, pattern[expected_char], i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   else
                   {
                         flags = get_queue_flags(queue_address);
			 ++passedCount;
	if(0)		 { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  -%c %2d %8u 0x%02X\n",i, temp,get_queue_length(queue_address),freesize,flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   ++expected_char;
                   if (expected_char >= sizeof(pattern) - 1)
                   {
                       expected_char = 0;
                   }
             }
             else
             {
                  flags = get_queue_flags(queue_address);
		
            if(0)      { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  -  %2d %8u 0x%02X\n",i, get_queue_length(queue_address),freesize,flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }
       }
    }
#else
   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"WARNING:  RAM RLE DISABLED!\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
#endif



   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"RAM RLE WORD TEST\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
#ifdef UTILITY_QUEUE_RLE_ENABLE
   initialize_ram_rle_word_queue(queue_address,QUEUE_SIZE, 57);
   current_char = 0;
   expected_char = 0;
    

   for (i = 0; i < tests; ++i)
   {
       func = random() & 0x01;
       
       if (func ==  0 )
       {
           mixed16.u = pattern16[current_char];
           result = push_word (queue_address, mixed16.u );
           if (result == QUEUE_BYTE_STORED)
           {
		  flags = get_queue_flags(queue_address);
                if(0)  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  +%5d %2d %8u 0x%02X\n",i, pattern16[current_char],get_queue_length(queue_address),freesize,flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   ++current_char;
                   if (current_char>= sizeof(pattern16)/ sizeof (pattern16[0]))
                   {
                       current_char = 0;
                   }
             }
             else
             {
		  flags = get_queue_flags(queue_address);
if(0)                  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  +  %2d %8u 0x%02X %d\n",i, get_queue_length(queue_address),freesize,flags,result);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }

       }
       if (func ==  1 )
       {
           result = shift_word ( queue_address,(uint16_t*) &mixed16);
           if (result == QUEUE_BYTE_SHIFTED)
           {
                   if ( pattern16[expected_char] != mixed16.u)
                   {
                        { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nError: Got %5d, expected %5d in test %lu\n", mixed16.u, pattern16[expected_char], i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   else
                   {
                         flags = get_queue_flags(queue_address);
			 ++passedCount;
if(0)			 { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  -%5d %2d %8u 0x%02X\n",i, mixed16.u,get_queue_length(queue_address),freesize,flags);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
                   }
                   ++expected_char;
                   if (expected_char >= sizeof(pattern16)/sizeof (pattern16[0]) )
                   {
                       expected_char = 0;
                   }
             }
             else
             {
                  flags = get_queue_flags(queue_address);
		
    if(0)              { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%8lu  -  %2d %8u 0x%02X %d\n",i, get_queue_length(queue_address),freesize,flags, result);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
             }
       }
    }
#else
   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"WARNING: RAM RLE DISABLED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
#endif

#define STRING_QUEUE_SIZE 26 
{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nString queue tests\nFollowing four lines should be all x's, a and x's, ba and x's, Z through A\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    initialize_string_queue(queue_address, STRING_QUEUE_SIZE, RAM_STRING_MODE_RAW, 'x',RAM_STRING_UP);
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 
 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
       push_byte(queue_address, 'a') ;
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    push_byte(queue_address, 'b') ;
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
    random_number.u = 1;
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       push_byte(queue_address, i+'A') ;
    }
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Following four lines should be all x's, x's and a,  x's and ab, A through Z\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
    initialize_string_queue(queue_address, STRING_QUEUE_SIZE, RAM_STRING_MODE_RAW, 'x',RAM_STRING_DOWN);
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
       push_byte(queue_address, 'a' ) ;
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    push_byte(queue_address, 'b') ;
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
    random_number.u = 1;
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       push_byte(queue_address, i+'A') ;
    }
    for (i = 0; i < STRING_QUEUE_SIZE; ++i)  
    {
       c2 = get_user_buffer(i + QUEUE_HEADER_SIZE + QUEUE_ADDRESS);
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%c",c2);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }

    // Bit queue test

   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n\nBit queue test\n:");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 

 }
   result = 0;
   initialize_queue(queue_address,QUEUE_SIZE);
   test_stage = 1;
   for (i = 0; i < QUEUE_SIZE; ++i)
   {
	   push_byte(queue_address, i);
   }
   for (i = 0; i < QUEUE_SIZE * 8; ++i)
   {
	   if ( read_bit(queue_address,&temp) != QUEUE_BYTE_SHIFTED)
	   {
		   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Error: bit didn't read, i = %lu\n", i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
while(1);		   result = 1;
	   }
	   else
	   {
		  c1 = i / 8;
		  c1 = (c1 >> (7 - (i%8)) ) & 0x01;
		  if (temp != c1)
		  {
			  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Error: Bit queue read: Expected %d but got %d at entry %lu\n", c1, temp, i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
			  result = 1;
		  }
	   }
   }
   
   for (i = 0; i < QUEUE_SIZE * 8; ++i)
   {
	   if ( shift_bit(queue_address,&temp) != QUEUE_BYTE_SHIFTED)
	   {
		   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Error: bit didn't shift, i = %lu\n", i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
		   while(1);result = 1;
	   }
	   else
	   {
		  c1 = i / 8;
		  c1 = (c1 >> (7 - (i%8)) ) & 0x01;
		  if (temp != c1)
		  {
			  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Error: Bit queue: Expected %d but got %d at entry %lu\n", c1, temp, i);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
			  while(1);result = 1;
		  }
	   }
   }
	  if (shift_bit(queue_address,&temp) != QUEUE_EMPTY)
	  {
		  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Error: Bit queue should have returned empty");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
		  while(1);result = 1;
	  }
   if (result == 0)
   {
	   { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Bit Queue test passed\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
   }
	   
	          
				   



    
#if 0

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 4 bit, 50%:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 4;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 4 bit, 0xF000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 4;
    tp.generic.hw_counter = 0;
    vset_pwm(0xF000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 4 bit, 0xFFFF:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 4;
    tp.generic.hw_counter = 0;
    vset_pwm(0xFFFF);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 4 bit, 0x0000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 4;
    tp.generic.hw_counter = 0;
    vset_pwm(0x0000);
    for (i= 0; i < 64; ++i)
    {
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 1 bit, 0x7FFF:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 1;
    tp.generic.hw_counter = 0;
    vset_pwm(0x7FFF);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 4 bit, 0xC000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 4;
    tp.generic.hw_counter = 0;
    vset_pwm(0xC000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 1 bit, 0x8000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 1;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 1 bit, 0x7FFF:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 1;
    tp.generic.hw_counter = 0;
    vset_pwm(0x7FFF);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 2 bit, 0x8000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 2;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 3 bit, 0x8000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 1 bit, 0x7FFF:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 1;
    tp.generic.hw_counter = 0;
    vset_pwm(0x7FFF);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    tp.generic.hw_mode = 3;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 5 bit, 0x8000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 64; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 5;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 64; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 6 bit, 0x8000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 200; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 6;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 200; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\nSoftware PWM test: 7 bit, 0x8000:\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    for (i = 0; i < 512; ++i){{ char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%d",i%10);} //printf ("\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    virtual_pin = 1;
    tp.generic.hw_mode = 7;
    tp.generic.hw_counter = 0;
    vset_pwm(0x8000);
    for (i= 0; i < 512; ++i)
    {
       update_pwm();
       if (vpin_read())
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       else
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,".");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
#endif
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"ascii_to_val  test:  ");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    result = 1; 
    for (i = 0; i <= 9; ++i)
    {
       if (ascii_to_val(i + '0') != i)
       {
	  result = 0;
       }
    }
    for (i = 0; i < 6; ++i)
    {
       if (ascii_to_val(i + 'A') != (i + 10 ))
       {
	  result = 0;
       }
    }
    for (i = 0; i < 6; ++i)
    {
       if (ascii_to_val(i + 'a') != (i + 10 ))
       {
	  result = 0;
       }
    }
    if (result)
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"PASSED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    else
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"FAILED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    while(1);   overall_result = 1;
    }

    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"hex_ascii_to_val16 test: ");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    result = 1;
    test_stage = 2;
    for (i = 0; i <65535 ; ++i)
    {
       sprintf((char*)string,"%lX",i);
       if (hex_ascii_to_val16( string, strlen((char*)string)) != i)
       {
	  result = 0;
       }
    }
    test_stage = 3;
    for (i = 0; i <65535 ; ++i)
    {
       sprintf((char*)string,"%lx",i);
       if (hex_ascii_to_val16( string, strlen((char*)string)) != i)
       {
	  result = 0;
       }
    }
    test_stage = 4;
    for (i = 0; i <65535 ; ++i)
    {
       sprintf((char*)string,"%0lX",i);
       if (hex_ascii_to_val16( string, strlen((char*)string)) != i)
       {
	  result = 0;
       }
    }
    test_stage = 5;
    for (i = 0; i <65535 ; ++i)
    {
       sprintf((char*)string,"%0lx",i);
       if (hex_ascii_to_val16( string, strlen((char*)string)) != i)
       {
	  result = 0;
       }
    }
    if (result)
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"PASSED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    else
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"FAILED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    while(1);   overall_result = 1;
    }

test_stage = 6;
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"hex_ascii_to_val32 test: ");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    result = 1;
    random_number.u = 1;
    for (i = 0; i < 65535 ; ++i)
    {
       j = random();
       j <<=16;
       j += random();

       sprintf((char*)string,"%lX",j);
       uint32_t val = hex_ascii_to_val32( string, strlen((char*)string));
       if ( val != j)
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"hex_ascii_to_val32 failed on 0x%lX",j);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
	while(1);  overall_result = 1;
	  result = 0;
       }
    }
    test_stage = 7;
    for (i = 0; i < 65535 ; ++i)
    {
       j = random();
       j <<=16;
       j += random();

       sprintf((char*)string,"%lx",j);
       if (hex_ascii_to_val32( string, strlen((char*)string)) != j)
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"hex_ascii_to_val32 failed on 0x%lX",j);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
while(1);	  overall_result = 1;
	  result = 0;
       }
    }
    test_stage = 8;
    for (i = 0; i < 65535 ; ++i)
    {
       j = random();
       j <<=16;
       j += random();

       sprintf((char*)string,"%0lX",j);
       if (hex_ascii_to_val32( string, strlen((char*)string)) != j)
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"hex_ascii_to_val32 failed on 0x%lX",j);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
while(1);	  overall_result = 1;
	  result = 0;
       }
    }
    for (i = 0; i < 65535 ; ++i)
    {
       j = random();
       j <<=16;
       j += random();

       sprintf((char*)string,"%0lx",j);
       if (hex_ascii_to_val32( string, strlen((char*)string)) != j)
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"hex_ascii_to_val32 failed on 0x%lX",j);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
while(1);	  overall_result = 1;
	  result = 0;
       }
    }
    if (result)
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"PASSED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    else
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"FAILED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
while(1);       overall_result = 1;
    }




    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"\n\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"dec_ascii_to_val32 test: ");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    result = 1;
    random_number.u = 1;
    for (i = 0; i < 65535 ; ++i)
    {
       j = random();
       j <<=16;
       j += random();

       sprintf((char*)string,"%lu",j);
       if (dec_ascii_to_val32( string, strlen((char*)string)) != j)
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"dec_ascii_to_val32 failed on %lu",j);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
	  overall_result = 1;
	  result = 0;
       }
    }
    for (i = 0; i < 65535 ; ++i)
    {
       j = random();
       j <<=16;
       j += random();

       sprintf((char*)string,"%0lu",j);
       if (dec_ascii_to_val32( string, strlen((char*)string)) != j)
       {
	  { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"dec_ascii_to_val32 failed on %lu",j);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
	  overall_result = 1;
	  result = 0;
       }
    }

    if (result)
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"PASSED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }
    else
    {
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"FAILED\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       overall_result = 1;
    }
#if 0
    { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"Sin wave test\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    sin_data[0].data1 = 0;
    sin_data[0].data2 = 6948;
    sin_data[0].k =29676;
    for (i = 0; i < 1000; ++i)
    {
       temp16 = gen_sin_wave(0); 
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"%4d %5d|",i,temp16);
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       for (j = 0; j < (temp16 >> 10) ; ++j)
       {
           { char tempoutputstring[100]; 
 sprintf(tempoutputstring," ");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
       }
       { char tempoutputstring[100]; 
 sprintf(tempoutputstring,"#\n");
 while(!(UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()));UART1_WriteBuffer((uint8_t*)tempoutputstring,strlen(tempoutputstring)); 
 UART1_Write('\r');
 UART1_Write('\n'); }
    }       
#endif
    return (overall_result);


}
#endif




