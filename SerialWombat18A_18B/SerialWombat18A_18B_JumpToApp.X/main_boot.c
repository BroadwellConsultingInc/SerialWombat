#include <stdint.h>
#include <stdbool.h>
#include<xc.h>
#define    FCY    16000000UL
#include <libpic30.h> 

void reset ()
{
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
}

// FSEC
#pragma config BWRP = OFF    //Boot Segment Write-Protect bit->Boot Segment may be written //JAB Was OFF
#pragma config BSS = DISABLED    //Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = ON    //Boot Segment Control bit->No Boot Segment  //JAB Was Off
#pragma config GWRP = OFF    //General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    //General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    //Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    //Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = ON    //Alternate Interrupt Vector Table bit->Disabled AIVT
#pragma config BSLIM =  0x1FF6  //Boot Segment Flash Page Address Limit bits
//#pragma config BSLIM = 0x1FFF

//#define CRYSTAL_8MHZ
// FOSCSEL
#ifdef CRYSTAL_8MHZ
#pragma config FNOSC = PRIPLL    //Oscillator Source Selection->FRC
#pragma config POSCMD = XT    //Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config FCKSM = CSECME    //Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled

#else
#pragma config FNOSC = FRC    //Oscillator Source Selection->FRC
#pragma config POSCMD = NONE    //Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config FCKSM = CSECME    //Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled

#endif

#pragma config PLLSS = PLL_FRC    //PLL Secondary Selection Configuration bit->PLL is fed by the on-chip Fast RC (FRC) oscillator
#pragma config PLLMODE = PLL4X    //PLL Mode Selection->4x PLL selected
#pragma config IESO = ON    //Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC


#pragma config OSCIOFCN = ON    //OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config SOSCSEL = OFF    //SOSC Power Selection Configuration bits->Digital (SCLKI) mode
#pragma config IOL1WAY = OFF   //Peripheral pin select configuration bit->Allow only one reconfiguration

// FWDT
#pragma config WDTPS = PS32768    //Watchdog Timer Postscaler bits->1:32768
#pragma config FWPSA = PR128    //Watchdog Timer Prescaler bit->1:128
#pragma config FWDTEN = OFF    //Watchdog Timer Enable bits->WDT and SWDTEN disabled
#pragma config WINDIS = OFF    //Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config WDTWIN = WIN25    //Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config WDTCMX = WDTCLK    //WDT MUX Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config WDTCLK = LPRC    //WDT Clock Source Select bits->WDT uses LPRC

// FPOR
#pragma config BOREN = ON    //Brown Out Enable bit->Brown Out Enable Bit
#pragma config LPCFG = OFF    //Low power regulator control->No Retention Sleep
#pragma config DNVPEN = ENABLE    //Downside Voltage Protection Enable bit->Downside protection enabled using ZPBOR when BOR is inactive

// FICD
#pragma config ICS = PGD1    //ICD Communication Channel Select bits->Communicate on PGEC1 and PGED1
#pragma config JTAGEN = OFF    //JTAG Enable bit->JTAG is disabled

// FDEVOPT1
#pragma config ALTCMPI = DISABLE    //Alternate Comparator Input Enable bit->C1INC, C2INC, and C3INC are on their standard pin locations
#pragma config TMPRPIN = OFF    //Tamper Pin Enable bit->TMPRN pin function is disabled
#pragma config SOSCHP = ON    //SOSC High Power Enable bit (valid only when SOSCSEL = 1->Enable SOSC high power mode (default)
#pragma config ALTI2C1 = ALTI2CEN    //Alternate I2C pin Location->SDA1 and SCL1 on RB9 and RB8
void (*voidvoidPtr)();
int main(void)
{

     I2C2CONL = 0;  //Shut off I2C
     INTCON2 |= 0x100; // Set Alternate vector table.  Bits in .h file are wrong in INTCON2bits so use bit or
// Get the address from the reset vector and jump to the reset routine.
      // Jumping directly into the AVT causes an address trap.
      uint32_t high = 0;
      uint16_t low = 0;
       low = __builtin_tblrdl(0x4000);
      voidvoidPtr = (void*) low;
      high = __builtin_tblrdl(0x4002);
      high <<= 16;
      voidvoidPtr += high;
      voidvoidPtr();
  
	return 1;
}


