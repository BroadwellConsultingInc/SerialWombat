#include <stdint.h>
#include <stdbool.h>
#include "serialWombat.h"
#include "mcc.h"
#define    FCY    16000000UL
#include <libpic30.h> 
uint8_t CurrentPin;

 bool RunForeground = false;


uint32_t UserBufferBoot[SIZE_OF_USER_BUFFER / 4]; // Force alignment by making uint32_t
uint8_t *UserBufferPtr = UserBufferBoot;

void reset ()
{
	while (1)
	{           
		{ __asm__ volatile (" reset");  }       
	}
}

extern volatile uint32_t System1msCount;
bool StayInBoot = false;
           
void (*voidvoidPtr)();
      
      
// ASCII bytes "87654321"
volatile unsigned short message[] = {0x3738,0x3536,0x3334,0x3132};
volatile unsigned short crcResultCRCCCITT = 0;
void crc()
{

unsigned short* pointer;
unsigned short length;
unsigned short data;
////////////////////////////////////////////////////////////////////////////////
// standard CRC-CCITT
////////////////////////////////////////////////////////////////////////////////
#define CRCCCITT_POLYNOMIAL ((unsigned short)0x1021)
#define CRCCCITT_SEED_VALUE ((unsigned short)0x84CF) // non-direct of 0xffff
CRCCON1 = 0;
CRCCON2 = 0;
CRCCON1bits.CRCEN = 1; // enable CRC
CRCCON1bits.CRCISEL = 0; // interrupt when all shifts are done
CRCCON1bits.LENDIAN = 0; // big endian
CRCCON2bits.DWIDTH = 16-1; // 16-bit data width
CRCCON2bits.PLEN = 16-1; // 16-bit polynomial order
CRCCON1bits.CRCGO = 1; // start CRC calculation
CRCXORL = CRCCCITT_POLYNOMIAL; // set polynomial
CRCXORH = 0;
CRCWDATL = CRCCCITT_SEED_VALUE; // set initial value
CRCWDATH = 0;
pointer = (unsigned short*)message; // calculate CRC
length = sizeof(message)/sizeof(unsigned short);
while(length--)
{
while(CRCCON1bits.CRCFUL); // wait if FIFO is full
data = *pointer++; // load data
asm volatile ("swap %0" : "+r"(data)); // swap bytes for big endian



CRCDATL = data; // 16 bit word access to FIFO
}
while(CRCCON1bits.CRCFUL); // wait if FIFO is full
CRCCON1bits.CRCGO = 0; // suspend CRC calculation to clear interrupt flag
_CRCIF = 0; // clear interrupt flag
CRCDATL = 0; // load dummy data to shift out the CRC result
// data width must be equal to polynomial length
CRCCON1bits.CRCGO = 1; // resume CRC calculation
while(!_CRCIF); // wait until shifts are done
crcResultCRCCCITT = CRCWDATL; // get CRC result (must be 0x9B4D)

}

void crcAppSpace(uint32_t address_w, uint32_t length_w)
{

unsigned short* pointer;
unsigned short length;
unsigned short data;
////////////////////////////////////////////////////////////////////////////////
// standard CRC-CCITT
////////////////////////////////////////////////////////////////////////////////
#define CRCCCITT_POLYNOMIAL ((unsigned short)0x1021)
#define CRCCCITT_SEED_VALUE ((unsigned short)0x84CF) // non-direct of 0xffff
CRCCON1 = 0;
CRCCON2 = 0;
CRCCON1bits.CRCEN = 1; // enable CRC
CRCCON1bits.CRCISEL = 0; // interrupt when all shifts are done
CRCCON1bits.LENDIAN = 0; // big endian
CRCCON2bits.DWIDTH = 16-1; // 16-bit data width
CRCCON2bits.PLEN = 16-1; // 16-bit polynomial order
CRCCON1bits.CRCGO = 1; // start CRC calculation
CRCXORL = CRCCCITT_POLYNOMIAL; // set polynomial
CRCXORH = 0;
CRCWDATL = CRCCCITT_SEED_VALUE; // set initial value
CRCWDATH = 0;
pointer = (unsigned short*)message; // calculate CRC
length = sizeof(message)/sizeof(unsigned short);
uint32_t address;
for (address = address_w; address < address_w + length_w;  address += 2)
{
    
    if (address == 0x4800)
    {
        Nop();
    }
while(CRCCON1bits.CRCFUL); // wait if FIFO is full

 INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                uint8_t tblpag = TBLPAG;
                TBLPAG = address >>16;
                    data = __builtin_tblrdl(address );
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
//data = *pointer++; // load data
asm volatile ("swap %0" : "+r"(data)); // swap bytes for big endian
CRCDATL = data; // 16 bit word access to FIFO

while(CRCCON1bits.CRCFUL); // wait if FIFO is full

 INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                tblpag = TBLPAG;
                TBLPAG = address >>16;
                    data = __builtin_tblrdh(address );
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
//data = *pointer++; // load data
asm volatile ("swap %0" : "+r"(data)); // swap bytes for big endian
CRCDATL = data; // 16 bit word access to FIFO


}
while(CRCCON1bits.CRCFUL); // wait if FIFO is full
CRCCON1bits.CRCGO = 0; // suspend CRC calculation to clear interrupt flag
_CRCIF = 0; // clear interrupt flag
CRCDATL = 0; // load dummy data to shift out the CRC result
// data width must be equal to polynomial length
CRCCON1bits.CRCGO = 1; // resume CRC calculation
while(!_CRCIF); // wait until shifts are done
crcResultCRCCCITT = CRCWDATL; // get CRC result (must be 0x9B4D)

}



uint16_t time = 0;
uint16_t time2 = 0;
int main(void)
{
 
   
	// initialize the device
	SYSTEM_Initialize();
    INTERRUPT_GlobalEnable();
        while (!HLVDCONbits.BGVST); // Wait for Band Gap to stabilize.
   
        uint16_t magicProgrammedNumber;
INTERRUPT_GlobalDisable();  // While we're messing with TBLPAG
                uint8_t tblpag = TBLPAG;
                TBLPAG = 1;
                    magicProgrammedNumber = __builtin_tblrdl(0xF800);      
                    TBLPAG = tblpag;
                    INTERRUPT_GlobalEnable();
 
//#warning STAY IN BOOT FOREVER!
       // while (1)
        //TODO add check for final word write
    while (System1msCount <= 60 || StayInBoot || magicProgrammedNumber != 0xCD23) //Stay in boot for 60 mS  
	{
        LATBbits.LATB6 = 1; //TODO REMOVE
		ProcessRx();
     LATBbits.LATB6 = 0; //TODO REMOVE
	}

     INTERRUPT_GlobalDisable();
     
     I2C2CONL = 0;  //Shut off I2C
     
     
      INTCON2 |= 0x100; // Set Alternate vector table.  Bits in .h file are wrong in INTCON2bits so use bit 'or'
      
      
      // Get the address from the reset vector and jump to the reset routine.
      // Jumping directly into the AVT causes an address trap.
      
      uint32_t high = 0;
      uint16_t low = 0;
       low = __builtin_tblrdl(0x4000);
      voidvoidPtr =(void(*)(void)) low;
      high = __builtin_tblrdl(0x4002);
      high <<= 16;
      voidvoidPtr += high;
      voidvoidPtr();
       
  
	return 1;
}


