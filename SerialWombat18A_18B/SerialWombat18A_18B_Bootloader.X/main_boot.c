#include <stdint.h>
#include <stdbool.h>
#include "serialWombat.h"
#include "mcc.h"
#define    FCY    16000000UL
#include <libpic30.h> 
uint8_t CurrentPin;

 bool RunForeground = false;


uint8_t user_buffer[SIZE_OF_USER_BUFFER];

void reset ()
{
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
}

extern volatile uint32_t System1msCount;
bool StayInBoot = false;
int main(void)
{
 
   
	// initialize the device
	SYSTEM_Initialize();
    INTERRUPT_GlobalEnable();
        while (!HLVDCONbits.BGVST); // Wait for Band Gap to stabilize.
   

   //TODO debugIntCon2 = GetAddressPinVoltage_mV();
    
   
        // TODO do validation of App?
	while (System1msCount <= 60 || StayInBoot) //Stay in boot for 60 mS
	{

		ProcessRx();

	}

     INTERRUPT_GlobalDisable();
     
     I2C2CONL = 0;  //Shut off I2C
     
     
     INTCON2 |= 0x100; // Set Alternate vector table.  Bits in .h file are wrong in INTCON2bits so use bit or
     asm("goto 0x4000");  // Jump to App
  
	return 1;
}


