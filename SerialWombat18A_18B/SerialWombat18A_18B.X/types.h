#if (!defined (_TYPES_H_))
#define _TYPES_H_

#include <stdint.h>
#include <stddef.h>
//#include "processor_specific.h"

#ifdef __18CXX

/// \brief 8-bit unsigned character
///
#define uint8 unsigned char

/// \brief 8-bit signed character
///
#define int8 signed char

/// \brief 16-bit unsigned integer
///
#define uint16 uint16_t

/// \brief 16-bit signed integer
/// 
#define int16 int16_t 

/// \brief 32-bit unsigned integer
/// 

#define uint32 uint32_t

/// \brief 32-bit signed integer
///
#define int32 int32_t

/// \brief 24-bit unsigned integer (C18 extension)
///
/// This type is specific to the C18 compiler.  It does 24 bit math operations.  On other platforms this is defined as 32 bits.
#define uint24 unsigned long short

/// \brief 24-bit signed integer (C18 extension)
///
/// This type is specific to the C18 compiler.  It does 24 bit math operations.  On other platforms this is defined as 32 bits.
#define int24 signed  long short

#define COMPILING_FIRMWARE

#else

#define uint8 unsigned char
#define int8 signed char
#define uint16 unsigned short 
#define int16 signed short 
#define uint32 unsigned int
#define int32 signed int
#define uint24 unsigned long
#define int24 signed long 

#define near
#define far
#define rom


#endif

#ifdef BIG_ENDIAN_WOMBAT
typedef union mixed32_n{
	uint32 u;
	int32 s;
	struct mixed32_uwords_n{ 
		uint16 h;
		uint16 l;
        }uwords;
	struct mixed32_midword_n{ 
		uint8 dummy1 ;
		uint16 u;
		uint8 dummy2;

        }midword;
        struct {
	   uint8 h;
	   uint8 mh;
	   uint8 ml;
	   uint8 l;
	}bytes;
}mixed32_t;

typedef union mixed24_n{
	uint24 u;
	int24 s;
        struct {
#ifndef COMPILING_FIRMWARE
	   uint8 buffer;
#endif
	   uint8 h;
	   uint8 m;
	   uint8 l;
	}bytes;
}mixed24_t;

typedef union mixed16_n{
	uint16 u;
	int16 s;
        struct {
	   uint8 highbyte;
	   uint8 lowbyte;
	}bytes;
}mixed16_t;
#else

/// \brief Union of 32 bit types.  Note that on the 18F a RAM pointer is 16 bits, so it's not included here
typedef union mixed32_n{
	uint32_t u;
	int32_t s;
	struct mixed32_uwords_n{ 
		uint16_t l;
		uint16_t h;
        }uwords;
        struct {
	   uint8_t l;
	   uint8_t ml;
	   uint8_t mh;
	   uint8_t h;
	}bytes;
}mixed32_t;


/// \brief Union of 24 bit types.  Specific to C18 compiler
typedef union mixed24_n{
	uint24 u;
	int24 s;
        struct {
	   uint8 l;
	   uint8 m;
	   uint8 h;
#ifndef COMPILING_FIRMWARE
	   uint8 buffer;
#endif
	}bytes;
}mixed24_t;

/// \brief Union of 16 bit types.  Also includes pointers for the 18F
typedef union mixed16_n{
	uint16 u;
	int16 s;
#ifdef COMPILING_FIRMWARE
	uint16 *u16ptr;
	uint8 *u8ptr;
	rom uint8 *u8romptr;
#endif
        struct {
	   uint8 lowbyte;
	   uint8 highbyte;
	}bytes;
}mixed16_t;
#endif

/// \brief A union representing all the possible pin modes, with meanings for each
///
/// Each pin mode can have up to 8 bytes of context data, plus 2 bytes for public data,
/// a byte for the mode, 4 bytes for software-driven hardware emulation (such as PWM).
/// An additional byte is undefined, for a total of 16 bytes.  This may turn out to be
/// more than 16 bytes on platforms that don't support the proprietary int24 type.
/// The size must remain 16 bytes because of assembly routines that do the copy from
/// the array of pin contexts to the directly accessible tp variable
typedef union _pin_register_t{ 
      uint8_t bytes[32];
      uint16_t uwords[16];

/// \brief A generic descriptor, typically used to access the buffer and mode variables
///
      struct generic_n {
	     uint16_t pin_uwords[14];
	     /// \brief  A 16 bit 'public' variable which is in the same location for every pin.
	     /// 
	     /// One pin mode can read or modify another pin's public data.  
	     uint16_t buffer;

	     /// \brief The mode of the current pin.
	     ///
	     uint16_t mode;     // Do not move


	     } generic;
      struct pulse_output_n
      {
        uint8_t bytes[19];
	uint8_t lastDMA;
	uint16_t highRemaining;
	uint16_t lowRemaining;
	uint16_t highReload;
	uint16_t lowReload;
	uint16_t buffer;
	uint16_t mode;
      } pulse_output;

      struct bitstreamOutput_n
      {
        uint8_t bytes[27]
	uint8_t lastDMA;
	uint16_t buffer;
	uint16_t mode;
      } bitstream_output;

      struct morse_n {
           uint16 queue;
           uint16 dot_time;
           uint8 highstate:2;
	   uint8 lowstate:2;
	   uint8 peek:1;
	   uint8 toggle:1;
	   uint8 togglestate:1;
           uint8 bits_left;
           uint8 pattern;
           uint8 state;
      }morse;
	struct max7219_n {
		uint16_t address;
		uint8_t dout;
		uint8_t clk;
		uint8_t numofsegments;
		uint8_t refresh;
		uint8_t updatesPerCall;
		uint8_t digit;
		uint8_t inverseFIFO;
		uint8_t rows;
		uint8_t columns;
	}max7219;
      struct spi_master_n{
	      // txqueue; generic.buffer
	      uint16 rxqueue;
	      uint8 clock;
	      uint8 trigger:1;
	      uint8 samplebit:1;
	      uint8 ckebit:1;
	      uint8 ckpbit:1;
	      uint8 cspol:1;
	      uint8 sdipin;
	      uint8 sdopin;
	      uint8 clkpin;

      }spi_master;
      


      struct slowpwm_n {  // Active time stored in buffer
	 mixed16_t period;
	 mixed16_t counter;
	 uint16 old_buffer;
	 uint8 lastportbcounter;
	 uint8 activestate:2;
	 uint8 inactivestate:2;
	 uint8 currentstate:1;
	 uint8 use_hw:1;
      }slowpwm;


      struct parallel_8n{
	 uint16 source;
	 uint16 delay;
         uint8 mode;
	 uint8 pin2;
	 uint8 clockpin;
	 uint8 bytesperframe;
       }parallel8;

      struct hd44780_n {
	      uint8 RSpin;
	      uint8 D4pin;
	      uint8 D5pin;
	      uint8 D6pin;
	      uint8 D7pin;
	      uint8 state;
      }hd44780;

      struct pulse_n {
           uint8 activetime;
           uint8 inactivetime;
	   uint8 counter;
           uint8 activestate:2;
	   uint8 inactivestate:2;
	   uint8 toggle:1;
	   uint8 fixedvalue:1;
	   uint8 commandpin;
           uint8 state:2;
           uint8 trigger:3;
	   uint16 lastval;
      }pulse;

      struct datalogger_n{
	      // QUEUE is in data area
	      uint8 sourcepins[4];
	      uint8 counter;
	      uint8 delay;
	      uint8 pinmode:2;
	      uint8 state:2;
	      uint8 fullaction:1;
	      uint8 resolution:2;
	      uint8 active:2;
	      uint8 inactive:2;
      }datalogger;
      

      struct watchdog_n {
         mixed16_t timeoutperiod;
         uint16 resetarrayaddress;
	 uint8 state;
         uint8 initstate:2;
         uint8 timeoutstate:2;
	 uint8 useresetarray:1;
	 uint8 returntoinit:1;
      }watchdog;
      
      struct un4step_n {
         uint8 pin2;
         uint8 pin3;
         uint8 pin4;
         uint8 mode;
         uint8 counter;
         uint8 steptime;
         uint8 active:2; 
         uint8 inactive:2; 
      }un4step;

      struct debounce_n{
	      uint16 debounceframes;
	      uint16 debouncecounter;
	      uint16 previous;
	      uint8 source;
	      uint8 usepublic:1; //0 = read pin, 1 = use public
	      uint8 sourceisvpin:1;
	      uint8 outputmode:2; //0 = none, 1 = digital, 2 = pwm
	      uint8 activemode:2; //0 = none, 1 = digital, 2 = pwm
	      uint8 inactivemode:2; 

      }debounce;

      struct button_counter_n{
	      uint16 counter;
	      uint8 debounceframes;
	      uint8 slow_frame_rate;
	      uint8 fast_frame_rate; 
	      uint8 total_slow_frames;
	      uint8 slow_counter;
	      uint8 state:3; 
	      uint8 active_state:1;
	      uint8 divisor:3;
      }button_counter;

      struct rotary_encn{
              uint16 min;
              uint16 max;
              uint16 increment;
              uint8 second_vpin;
              uint8 last_value;
      }rotary_enc;

      struct keypad16_n{
       uint8 column_pin;
       uint16 queue;
       uint16 current_reading;
       uint16 previous_reading;
       uint8 state;
       } keypad16;


      struct uart_rx_n{
	      uint16 queue;
	      uint8 lastportbcounter;
	      uint8 data;
	      uint8 bitstoskip;
	      uint8 persistentdatacounter:3;
	      uint8 persistentstate:3;
	      uint8 output:1; 
	      uint8 invert:1;
	      uint8 persistentdivisor:4;
      }uart_rx;
      struct uart_tx_n{
	      uint16 queue;
	      uint8 lastportbcounter;
	      uint8 data;
	      uint8 bitstowrite;
	      uint8 current_output:1;
	      uint8 invert:1;
	      uint8 output:1;
	      uint8 persistentdatacounter:4;
	      uint8 persistentdivisor:4;
      }uart_tx;

      struct remote_n{
	      uint16 data;
	      uint16  count;
	      uint8  bittime;
	      uint8 lastportbcounter;
	      uint8 lastvalue:1;
	      uint8 showdevid:1; 
	      uint8 activepolarity:1;
	      uint8 queuedata:1;
	      uint8 queueall:1;
	      uint8 idle:1;
	      uint8 newdata:1;
      }remote;

      struct sevenseg_n {
	      uint8 source;
	      uint8 state:3;
	      uint8 led10k:1;
	      uint8 led1k:1;
	      uint8 led100:1;
	      uint8 led10:1;
	      uint8 led1:1;
	      mixed16_t sample;
	      uint8 pin10;
	      uint8 pin100;
	      uint8 pin1k;
	      uint8 pin10k;
      }sevenseg;


         

       struct hysteresis_n{
	       uint16 lowlimit;
	       uint16 highlimit;
	       uint8 commandpin;
	       uint8 highcommandpin;
	       uint8 lowcommandpin;
	       uint8 lowaction:2;
	       uint8 highaction:2;
	       uint8 mode:2;
	       uint8 defaultaction:1;
	       uint8 currentstate:1;
       }hysteresis;


       struct counter_n{
               uint16_t debouncesamples;
               uint16_t debouncecounter;
               uint16_t max;
	       uint16_t increment;
	       uint8_t lastNextDMA;
	       uint8_t currentState;
	       uint8_t mode;

           }counter;

       struct quadEnc_n{
               uint16_t debouncesamples;
               uint16_t debouncecounter;
               uint16_t max;
               uint16_t min;
	       uint16_t increment;
	       uint8_t lastNextDMA;
	       uint8_t currentState;
	       uint8_t secondPin; 
	       uint8_t readState;

           }quadEnc;
       
       struct servo_n{
	       uint16 fixed;
	       uint16 variable;
	       uint16 lowPeriod;
	       /// Reverse the servo direction
	       /// 
	       /// When reverse is 0 a small commanded position
	       /// will result in the minimum pulse 
	       /// When reverse is 1 a small commanded position
	       /// will result in the maximum pulse 
	       uint8 reverse:1;
	       uint8 polarity:1;
	       uint8 counter;
	       uint8 updateframes;
	       uint8 commandpin;
       } servo;
       struct ping_n{
	  mixed16_t low_time; 
	  uint8 pulsetimeout;
	  uint8 period;
	  uint8 counter;
	  uint8 mode;
       }ping;
       struct diagnostics_n{
           uint8 commandpin;
           uint8 mismatchmax;
           uint8 safestate;
	   uint8 badinc;
	   uint8 gooddec;
           uint8 count;  
           uint8 expectedlow:2;
           uint8 expectedhigh:2;
	   uint8 goodresult:1;
       }diagnostics;

       struct pwm_follow_direct_n{
	       uint16_t sampletime;
	       uint16_t scalar;
	       int16_t offset;
	       uint16_t samplecounter;
	       uint16_t pwmPeriod;
	       uint8_t  commandpin; 
       }pwm_follow_direct;

       struct pwm_queue_fixed_period_n{
	       uint16 queue;
	       uint8 sampletime;
	       uint8 counter;
	       uint8 mode; // 0 idle, 1  8 bit, 2, 16 bit, 3: 4 bit high, 4: 4 bit low
	       uint8 fourbitslow;
	       uint8 emptyaction:2 ; // 0-off 1-on 2-HighZ 3-leave alone
	       uint8 bufferoutput:1 ; // 0 - value 1-counter
	       uint8 queueaction:1 ; // 0 - shift 1-read
	       uint8 updatenow:1;
       }pwm_queue_fixed_period;

       struct pwm_queue_variable_period_n{
	       uint16 queue;
	       uint16 counter;
	       uint8 emptyaction ; // 0-off 1-on 2-input 3-leave alone
	       uint8 bufferoutput ; // 0 - value 1-counter
	       uint8 eightbit; // 0 - 16bit values 1- 8 bit values
               uint8 queueaction;
       }pwm_queue_variable_period;

       struct pwm_sine_n{
	       uint16 sampletime;
	       uint16 counter;
                union {
		       int16  k_signed;
		       uint16  k_unsigned;
	        } k;
	        union {
		       int16  data2_signed;
		       uint16  data2_unsigned;
	        } data2;
	       //data 1 in buffer;
       }pwm_sine;

       struct ad_filter_1st_order_n{
	       uint16 k;
	       uint16 kinv;
	       uint8 sampletime;
	       uint8 counter;
       }ad_filter_1st_order;

       struct ad_average_n{
	       uint32 sum;
	       uint16 count;
	       uint8 samples;
	       uint8 source;
       }ad_average;
       struct min_max_n{
	       mixed16_t min;
	       mixed16_t max;
	       uint8 source;
	       uint8 publicdata; // 0 = min, 1 = max 2= current
       }min_max;

       struct lookup2d_n{
	       uint16 tableaddress;
	       uint8 source;
	       uint8 count;
	       uint8 location:2;
	       uint8 outputpin:1;
	       uint8 interpolate:1;
       }lookup2d;

       struct pid_n{
	       uint16 previousinput;
	       uint16 integrator;
               uint16 ramaddr;
	       uint8 counter;
	       uint8 sampletime;
       }pid;


       struct hw_pulse_width_n{
	   uint8 mode ;
	   mixed24_t oldlow;
	   mixed24_t oldhigh;
	   uint8 last:1;
	   uint8 enabled:1;
       }hw_pulse_width;

                  
} pin_register_t;
           

typedef union _pin_register2_t{

      uint8 bytes[16];

      struct generic2_n {
	     uint8 bytes[8];
             uint16 buffer;
	     uint8 mode;
	     } generic;

      struct servo2_n{
	      mixed32_t temp32;
	      uint24 position;
	      uint8 temp8;
      }servo;

      struct un4step_2n{
         uint16 desiredpos;
         uint8 currentstep;  
         uint8 stepmode;
         uint8 action;
         uint8 time;
	 uint8 zeropin;
	 uint8 zerostate;
      }un4step;

      struct uart_rx_2n{
	      uint8 receivedbit:1;
	      uint8 state;
	      uint8 bitfield;
	      uint8 datacounter;
	      uint8 divisor;
      }uart_rx;

      struct uart_tx_2n{
	      uint8 receivedbit:1;
	      uint8 state;
	      uint8 bitfield;
	      uint8 datacounter;
	      uint8 divisor;
      }uart_tx;

      struct remote_2n{
	      uint8 bitfield;
	      uint8 currentvalue:1;
	      uint8 halfbit;
	      uint8 threshold;
	      uint8 start;
      }remote;

      struct pwm_queue_variable_period2_n{
	      uint16 length;
	      mixed16_t temp16;
	      uint8 temp8;
	      uint8 dataprocessed:1;
      }pwm_queue_variable_period ;
      struct pin_logic2_n{
	 uint16 buffer1;
	 uint16 buffer2;
         uint8 istrue:1;
      }pin_logic;

      struct diagnostics2_n{
	 uint16 temp16;
      }diagnostics;
      struct ping2_n{
	      mixed16_t high_time;
	      uint16 delay_time;
	      mixed16_t temp_time;
	      uint8 rollover:1;
	      uint8 error:1;
      }ping;
      struct hd44780_n2{
	      uint16 offset;
      }hd44780;
      struct pulse_n2 {
	      uint16 bufferval;
      }pulse;
      struct rotary_enc_n{
              uint16 old_value;
              uint16 new_value;
	      uint16 final_value;
	      uint8 action;
	      uint8 pintomodify;
      }rotary_enc;

       struct keypad16_2n{
	uint8 current_button;
	uint8 previous_button;
	uint8 queue_mode:3;
	uint8 buffer_mode:3;
	uint8 testing_button;
	uint8 rows:4;
	uint8 columns:4;
	uint8 current_row;
      }keypad16;


       struct hysteresis{
	       uint16 lowlimit;
	       uint16 highlimit;
	       uint16 input;
	       uint16 temp16;
       }hysteresis;

       struct ad_filter_1st_order_n2{
	       uint32 temp32_1;
	       union {
		       uint32 temp2;
		       uint8 bytes[4];
		       uint16 words[2];
		      }temp32_2;
       }ad_filter_1st_order;

       struct ad_average_temp_n{
	       uint32 temp32;
	       uint16 temp16;

       }ad_average;
       
       struct lookup2d_2n{
	       uint24 temp24;
	       uint8 temp8;
	       uint16 x1;
	       uint16 x2;
	       uint16 y1;
	       uint16 y2;
               mixed32_t temp32;
       }lookup2d;


       struct pwm_follow_direct_n2{
           mixed32_t temp32 ;
           int32 stemp32 ;
       }pwm_follow_direct;


//       struct pid_n2{
//	       uint16 target;
//	       uint16 kp;
//	       uint16 kd;
//	       uint16 ki;
//	       uint8 commandpin;
//	       uint16 input;
//               uint8 outputcenter:1; 
//	}pid;

        struct morse_temp_n{
		uint8 new_val;
		uint8 temp;
	}morse;

      struct parallel_82n{
	 uint8 active:2;
	 uint8 inactive:2;
	 uint8 clockchangedata:2;
	 uint8 clockchangedatadone:2;
         uint8 clockidle:2;
	 uint8 clock;
	 uint8 pin3uparray[6];
	  // counter in pin 2 buffer


       }parallel8;
        struct hw_pulse_width2_n{
	       mixed32_t local_temp32_2;
	       mixed24_t high;
               mixed24_t low;
	       mixed16_t count;
	}hw_pulse_width;

} pin_register2_t;

/// \brief A type which allows multiple boolean variables to be packed into a single byte.  
///
/// This is done to save ram and to improve throughput, as single bit operations are very fast on
/// the 18F series of PIC microcontrollers
/// No operation requires the bits in this variable to be in a particular order, so the ANSI 
/// compiler variation of bit position in a byte doesn't matter.
typedef struct executive_settings_n{
	/// \brief This bit is set by the timer interrupt and cleared when execution begins
	///
	uint8 run_foreground:1;

	/// \brief This bit enables the boot pin to become an output and change states to allow tracking of the foreground task and low priority interrupts with an oscilloscope
	///
	uint8 throughput:1;

	/// \brief This bit tells the pin executive loop that the executed pin code for the current pin made changes in the pin context which need to be saved back to memory.
	///
	uint8 buffer_dirty:1;

	/// \brief This bit tells the executive to go into hardware idle or sleep on completion of pin processing.  This is enabled by the user and is poorly tested at this point.
	///
	uint8 idle_enabled:1;
}   executive_settings_t;

typedef struct communication_settings_n{
	uint8 uart_address_received:1;
	uint8 uart_checksum_received:1;
	uint8 uart_use_checksum:1;
	uint8 processrxbeforeevenpins:1;
	uint8 processrxbeforeoddpins:1;
	uint8 uart_use_cts:1;
	uint8 spi_inprogress:1;
	uint8 spi_enable:1;
}comm_settings_t;

typedef struct queue_flags_bits_n{
        uint8 wasempty:1;
        uint8 wasfull:1;
        uint8 compressing:1;
}queue_flags_bits_t;

typedef union queue_flags_union_n{
         uint8 flagsuint8;
	 queue_flags_bits_t bits;
}queue_flags_t;

typedef	union generic_queue_n{
	struct ram_queue_n{
        uint8 type;
        uint8 addressh;
        uint8 addressl;
	queue_flags_t flags;
        uint8 pad;
        uint16 queuesize;
        uint16 queuelength; 
        uint16 head;
	uint8 bitaccess;
	uint8 reserved[5];
	}__attribute__ ((packed)) ramq;

	struct flash_queue_n{
        uint8 type;
        uint8 addressh;
        uint8 addressl;
	queue_flags_t flags;
        uint8 pad;
        uint16 queuesize;
        uint16 flashaddr; 
        uint16 head;
	uint8 bitaccess;
        uint8 reserved[5];
	} __attribute__ ((packed)) flash;

	struct ram_rle_byte_queue_n{
        uint8 type;
        uint8 addressh;
        uint8 addressl;
	queue_flags_t flags;
	uint8 escapeval;
        uint16 queuesize;
        uint16 queuelength; 
        uint16 head;
	uint16 lastentry;
	uint8 lastval;
	uint8 lastlastval;
	uint8 reserved[2];
	} __attribute__ ((packed)) ram_rle_byte;

	struct ram_rle_word_queue_n{
        uint8 type;
        uint8 addressh;
        uint8 addressl;
	queue_flags_t flags;
	uint8 escapeval;
        uint16 queuesize;
        uint16 queuelength; 
        uint16 head;
	uint16 lastentry;
	uint16 lastval;
	uint16 lastlastval;
	}__attribute__ ((packed))  ram_rle_word;

	struct ram_string_queue_n{
        uint8 type;
        uint8 addressh;
        uint8 addressl;
	queue_flags_t flags;
	uint8 direction:1;  // 0 = left (to lower address)
	uint8 use_leading1:1;
	uint8 use_leading2:1;
	uint8 use_trailing1:1;
	uint8 use_trailing2:1;
	uint8 leading_zero:1;
	uint8 leading_space:1;
        uint16 queuesize;
	uint16 head;
	uint8 leading1;
	uint8 leading2;
	uint8 trailing1;
	uint8 trailing2;
	uint8 mode;
	uint8 reserved[5];
	}__attribute__ ((packed))  ram_string;

}__attribute__ ((packed))  queue_header_t;


typedef struct sin_data_n
{
    int16 k;
    int16 data1;
    int16 data2;
} sin_data_t;

#ifndef COMPILING_FIRMWARE

typedef struct test_data_n{
	pin_register_t tp;
	pin_register2_t tp2;
	uint8 rxbuffer[8];
	uint8 txbuffer[8];
	uint8 virtual_pin;
	uint8 current_physical_pin;
	int init_call_count;
	int update_call_count;
} test_data_t;
#endif  //not COMPILING_FIRMWARE

#endif
