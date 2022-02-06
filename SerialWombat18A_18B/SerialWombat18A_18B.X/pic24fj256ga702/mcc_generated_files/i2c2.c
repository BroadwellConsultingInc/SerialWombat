
/**
  I2C2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.c

  @Summary
    This is the generated header file for the i2c2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for i2c2.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC24FJ256GA702

    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include "i2c2.h"
#include <stdbool.h>
#include "SerialWombat.h"


//#define I2C_DEBUG_OUTPUT
#ifdef I2C_DEBUG_OUTPUT
#define OUTPUT_I2C_DEBUG(_value) {LATB = (_value <<11);  LATBbits.LATB10= 1;Nop();Nop();Nop();Nop(); LATBbits.LATB10 = 0;}
#warning I2C_DEBUG_OUTPUT ENABLED!   PORT B DMA Disabled!
#else
#define OUTPUT_I2C_DEBUG(_value){}
/*
uint8_t I2CDebugQueue[15] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
#define OUTPUT_I2C_DEBUG(_value){  \
	I2CDebugQueue[ 0] = I2CDebugQueue[ 1];\
	I2CDebugQueue[ 1] = I2CDebugQueue[ 2];\
	I2CDebugQueue[ 2] = I2CDebugQueue[ 3];\
	I2CDebugQueue[ 3] = I2CDebugQueue[ 4];\
	I2CDebugQueue[ 4] = I2CDebugQueue[ 5];\
	I2CDebugQueue[ 5] = I2CDebugQueue[ 6];\
	I2CDebugQueue[ 6] = I2CDebugQueue[ 7];\
	I2CDebugQueue[ 7] = I2CDebugQueue[ 8];\
	I2CDebugQueue[ 8] = I2CDebugQueue[ 9];\
	I2CDebugQueue[ 9] = I2CDebugQueue[10];\
	I2CDebugQueue[10] = I2CDebugQueue[11];\
	I2CDebugQueue[11] = I2CDebugQueue[12];\
	I2CDebugQueue[12] = I2CDebugQueue[13];\
	I2CDebugQueue[13] = I2CDebugQueue[14];\
 I2CDebugQueue[14] = _value;}
 */
#endif
/**
 Section: Data Types
 */

/**
  I2C Periph Driver State Enumeration

  @Summary
    Defines the different states of the i2c periph.

  @Description
    This defines the different states that the i2c periph
    used to process transactions on the i2c bus.
 */
typedef enum {
    S_PERIPH_IDLE,
    S_PERIPH_RECEIVE_MODE,
    S_PERIPH_TRANSMIT_MODE,
    S_PERIPH_LOW_BYTE_ADDRESS_DETECT,

} I2C_PERIPH_STATES;

/**
 Section: Macro Definitions
 */
/* defined for I2C2 */
#define I2C2_TRANSMIT_REG                       I2C2TRN	// Defines the transmit register used to send data.
#define I2C2_RECEIVE_REG                        I2C2RCV	// Defines the receive register used to receive data.

#define I2C2_MASK_REG                           I2C2MSK	// Defines the address mask register.
#define I2C2_ADDRESS_REG                        I2C2ADD	// Defines the address register. 

// The following control bits are used in the I2C state machine to manage
// the I2C module and determine next states.
#define I2C2_GENERAL_CALL_ENABLE_BIT            I2C2CONLbits.GCEN	// I2C General Call enable control bit.
#define I2C2_10_BIT_ADDRESS_ENABLE_BIT          I2C2CONLbits.A10M	// I2C Address Mode (7 or 10 bit address) control bit.
#define I2C2_RELEASE_SCL_CLOCK_CONTROL_BIT      I2C2CONLbits.SCLREL	// I2C clock stretch/release control bit.

// The following status bits are used in the I2C state machine to determine
// the next states.

#define I2C2_READ_NOT_WRITE_STATUS_BIT          I2C2STATbits.R_W    // I2C current transaction read/write status bit.
#define I2C2_DATA_NOT_ADDRESS_STATUS_BIT        I2C2STATbits.D_A    // I2C last byte receive was data/address status bit.
#define I2C2_RECEIVE_OVERFLOW_STATUS_BIT        I2C2STATbits.I2COV	// I2C receive buffer overflow status bit.
#define I2C2_GENERAL_CALL_ADDRESS_STATUS_BIT    I2C2STATbits.GCSTAT	// I2C General Call status bit.
#define I2C2_ACKNOWLEDGE_STATUS_BIT             I2C2STATbits.ACKSTAT	// I2C ACK status bit.

#define EMULATE_EEPROM_SIZE                     64
/**
 Section: Local Functions
 */

inline void __attribute__((always_inline)) I2C2_TransmitProcess(void);
inline void __attribute__((always_inline)) I2C2_ReceiveProcess(void);

/**
 Section: Local Variables
 */

I2C_PERIPH_STATES i2c2_periph_state;

/**
  Prototype:        void I2C2_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C2_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C2_Initialize();
 */

extern volatile bool ResponsePending;
extern volatile bool ResponseAvailable;
extern volatile uint8_t TX_ClockStretching;
extern volatile uint8_t RX_ClockStretching;

volatile uint8_t DebugLastPoint = 0;

  extern uint8_t SW_I2CAddress;

void I2C2_Initialize(void) {

    // initialize the hardware
    // ACKEN disabled; STRICT disabled; STREN disabled; GCEN disabled; SMEN disabled; DISSLW enabled; I2CSIDL disabled; ACKDT Sends ACK; SCLREL Holds; RSEN disabled; A10M 7 Bit; PEN disabled; RCEN disabled; SEN disabled; I2CEN enabled; 
    I2C2CONL = 0x8000;

    I2C2CONHbits.AHEN = 1; 
    I2C2CONHbits.PCIE = 1; //JABSTOP  enable stop interrupt
    // BCL disabled; D_nA disabled; R_nW disabled; P disabled; S disabled; I2COV disabled; IWCOL disabled; 
    I2C2STAT = 0x00;
    // ADD 49; 
  
    I2C2_PeriphAddressSet(SW_I2CAddress);
    // MSK 0; 
    I2C2_PeriphAddressMaskSet(0x00);

    // make sure this is set first
    i2c2_periph_state = S_PERIPH_IDLE;


    /* SI2C2 - I2C2 Periph Events */
    // clear the master interrupt flag
    IFS3bits.SI2C2IF = 0;
    // enable the master interrupt
    IEC3bits.SI2C2IE = 1;
    
#ifdef I2C_DEBUG_OUTPUT
    TRISB &= 0x03FF;
    DMACH1bits.CHEN = 0;
    OUTPUT_I2C_DEBUG(0);
#endif

}

volatile uint8_t wombatI2CRxData[8];
volatile uint8_t wombatI2CRxDataCount = 0;
volatile uint8_t wombatI2CTxDataCount = 0;
volatile uint8_t wombatI2CTxData[8];
volatile bool nextInterruptAddress = false;
volatile bool discardI2CData = false;

volatile uint32_t I2CInterruptCount = 0;
void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) 
{

	static bool prior_address_match = false;
	static bool not_busy = true;
	uint8_t dummy;

	// NOTE: The periph driver will always acknowledge 
	//       any address match.
	DebugLastPoint = 99;
	OUTPUT_I2C_DEBUG(0x01);
	IFS3bits.SI2C2IF = 0;
    ++I2CInterruptCount;
	if (I2C2STATbits.P)
	{
        if (wombatI2CRxDataCount < 8)
        {
            //Short frame.  Discard it.
            wombatI2CRxDataCount = 0;
        }
		return;

	}
	switch (i2c2_periph_state) {
		case S_PERIPH_IDLE:
		case S_PERIPH_RECEIVE_MODE:

			/* When at S_PERIPH_RECEIVE_MODE this mode there
			   will be two types of incoming transactions:
			   1. Data sent by master
			   2. A restart or start detection

			   But from the point of view of the firmware, there is
			   no difference between S_PERIPH_IDLE and S_PERIPH_RECEIVE_MODE
			   states, since the types of incoming transactions will be
			   the same so we share the code here.
			   */
			//LATBbits.LATB12 = I2C2_DATA_NOT_ADDRESS_STATUS_BIT;
			if (( (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 0))// case of 7-bit address detected
					||
					(((I2C2_GENERAL_CALL_ENABLE_BIT == 1) && (I2C2_GENERAL_CALL_ADDRESS_STATUS_BIT == 1)) || nextInterruptAddress ))  // case of general address call detected
			{
				if (I2C2_READ_NOT_WRITE_STATUS_BIT == 0) 
				{
					//Input to this chip.
					DebugLastPoint = 1;
					OUTPUT_I2C_DEBUG(0x02);
					//I2C2_StatusCallback(I2C2_PERIPH_RECEIVE_REQUEST_DETECTED);

					// Receive the data if valid
					if (I2C2STATbits.ACKTIM) 
					{
						nextInterruptAddress = true;
						//LATBbits.LATB10 = 1;
						DebugLastPoint = 11;
						OUTPUT_I2C_DEBUG(0x03);
						OUTPUT_I2C_DEBUG(wombatI2CRxDataCount);
						dummy = I2C2_RECEIVE_REG; 

						I2C2CONLbits.ACKDT = 0; 

						if (ResponsePending && !ResponseAvailable) 
						{ 

							RX_ClockStretching = CLOCK_STRETCHING_MAX;
							DebugLastPoint = 12;
							OUTPUT_I2C_DEBUG(0x04);

						}
						else
						{
							I2C2_RELEASE_SCL_CLOCK_CONTROL_BIT = 1;
							DebugLastPoint = 13;
							OUTPUT_I2C_DEBUG(0x05);
						}

						wombatI2CTxDataCount = 0;
						// LATBbits.LATB10 = 0;
					} else 
					{
						nextInterruptAddress = false;
						//LATBbits.LATB13 = 1;
						dummy = I2C2_RECEIVE_REG; 
						i2c2_periph_state = S_PERIPH_RECEIVE_MODE;

						DebugLastPoint = 3;
						OUTPUT_I2C_DEBUG(0x06);
						// LATBbits.LATB13 = 0;
						if (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 1)
						{
							discardI2CData = true;
							OUTPUT_I2C_DEBUG(0x07);
						}
					}
				} 
				else   // implied if(I2C2_READ_NOT_WRITE_STATUS_BIT == 1) 
				{
					DebugLastPoint = 53;
					OUTPUT_I2C_DEBUG(0x08);
					if (I2C2STATbits.ACKTIM) 
					{
						nextInterruptAddress = true;
						DebugLastPoint = 5;
						OUTPUT_I2C_DEBUG(0x09);
						dummy = I2C2_RECEIVE_REG;
						I2C2CONLbits.ACKDT = 0; 
						wombatI2CTxDataCount= 0;
						if (ResponsePending && !ResponseAvailable) 
						{ 
							TX_ClockStretching = CLOCK_STRETCHING_MAX;
							DebugLastPoint = 51;
							OUTPUT_I2C_DEBUG(0x0A);
							return;
						}
						else
						{
							I2C2_RELEASE_SCL_CLOCK_CONTROL_BIT = 1;
							DebugLastPoint = 52;
							OUTPUT_I2C_DEBUG(0x0B);
						}
					} 
					else 
					{
						DebugLastPoint = 6;
						OUTPUT_I2C_DEBUG(12);
						// read the receive register only when
						// we are ready for the next transaction.
						// this one is a dummy read

						// it is a read, go to transmit mode
						dummy = I2C2_RECEIVE_REG;

						// during this portion, the master is expecting the
						// periph for a reply. So the returned status of
						// the callback at this point cannot be used to 
						// delay the reply if needed.
						// In other words, the periph has to reply to the master.
						// Therefore, the transmit will be performed.

						I2C2_TransmitProcess();
						i2c2_periph_state = S_PERIPH_TRANSMIT_MODE;
					}
				}
			}
			else
			{
				DebugLastPoint = 100;
				OUTPUT_I2C_DEBUG(18);
			}

			// this if statement is to make sure we only save incoming
			// data when we are truly in receiving mode
			if (i2c2_periph_state == S_PERIPH_RECEIVE_MODE) 
			{
				DebugLastPoint = 12;
				OUTPUT_I2C_DEBUG(0x13);
				// case of data received
				if (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 1 ) 
				{
					DebugLastPoint = 13;
					OUTPUT_I2C_DEBUG(0x14);

					if (I2C2_RECEIVE_OVERFLOW_STATUS_BIT != 1) // check if we are overflowing the receive buffer
					{
						DebugLastPoint = 14;
						OUTPUT_I2C_DEBUG(0x15);
						I2C2_ReceiveProcess();
					} 
					else 
					{
						// overflow detected!
						// read the buffer to reset the buffer full flag
						// and clear the overflow bit
						// then do nothing so the master
						// will resend the data
						dummy = I2C2_RECEIVE_REG;
						I2C2_RECEIVE_OVERFLOW_STATUS_BIT = 0;
						DebugLastPoint = 15;
						OUTPUT_I2C_DEBUG(0x16);
					}
				}
			}

			break;

		case S_PERIPH_LOW_BYTE_ADDRESS_DETECT:
			// Note that this state will only get
			// executed when 10-bit address is set

			// we send receive request but we do not actually know
			// if the next one is a data from master since the 
			// next one can be a restart with a transmit request.
			// When that happens, the next state will take care of it.
			// This is just the nature of i2c bus protocol.

			DebugLastPoint = 18;
			OUTPUT_I2C_DEBUG(23);
			// set this flag to indicate we have
			// full 10-bit address detection
			prior_address_match = true;

			if (not_busy) 
			{
				DebugLastPoint = 19;
				OUTPUT_I2C_DEBUG(24);
				// dummy read is needed
				dummy = I2C2_RECEIVE_REG;
			}

			i2c2_periph_state = S_PERIPH_RECEIVE_MODE;

			break;

		case S_PERIPH_TRANSMIT_MODE:

			// this is the state where an ACK or NACK is expected
			// to occur after the periph has placed data to the
			// transmit register.

			// if the transaction was ACK'ed, more data needs to be sent
			// if the transaction was NACK'ed then we don't need to send
			// more data
			if (I2C2_ACKNOWLEDGE_STATUS_BIT == 0) 
			{
				// transmit more data
				I2C2_TransmitProcess();
				DebugLastPoint = 16;
				OUTPUT_I2C_DEBUG(25);

			} 
			else //if (I2C2_ACKNOWLEDGE_STATUS_BIT == 1)
			{
				// no more data to be sent so we go to idle state
				i2c2_periph_state = S_PERIPH_IDLE;
				if (wombatI2CTxDataCount < 8)
				{
					DebugLastPoint = 17;
					OUTPUT_I2C_DEBUG(26);
				}
				else
				{
					DebugLastPoint = 177;
					OUTPUT_I2C_DEBUG(27);
				}
			}
			break;


		default:
			// should never happen, if we ever get here reset
			reset();
			break;
	}
}


void I2C2_PeriphAddressMaskSet(
        uint16_t mask) {
    I2C2_MASK_REG = mask;
}

void I2C2_PeriphAddressSet(
        uint16_t address) {
    if (address > 0x7F) {
        // use 10 bit address
        I2C2_10_BIT_ADDRESS_ENABLE_BIT = true;
    } else {
        // use 7 bit address
        I2C2_10_BIT_ADDRESS_ENABLE_BIT = false;
    }
    i2c2_periph_state = S_PERIPH_IDLE;
    I2C2_ADDRESS_REG = address;
}

inline void __attribute__((always_inline)) I2C2_TransmitProcess(void) {
    
    I2C2CONLbits.ACKDT = 0;
    I2C2_TRANSMIT_REG = wombatI2CTxData[ wombatI2CTxDataCount ];
    if (wombatI2CTxDataCount < 7) {
        ++wombatI2CTxDataCount;
    }
     ResponseAvailable = false;
    // set the SCL clock to be released
    I2C2_RELEASE_SCL_CLOCK_CONTROL_BIT = 1;

}

inline void __attribute__((always_inline)) I2C2_ReceiveProcess(void) {
OUTPUT_I2C_DEBUG(wombatI2CRxDataCount);
if (discardI2CData || nextInterruptAddress)
{
    OUTPUT_I2C_DEBUG(31);
    OUTPUT_I2C_DEBUG(31);
    OUTPUT_I2C_DEBUG(31);
    discardI2CData = false;
}
else if (wombatI2CRxDataCount < 8) 
{
        I2C2CONLbits.ACKDT = 0;
        uint8_t rxByte = I2C2_RECEIVE_REG;
        OUTPUT_I2C_DEBUG(rxByte);
        wombatI2CRxData[wombatI2CRxDataCount] = rxByte ;
        ++wombatI2CRxDataCount;
        if (wombatI2CRxDataCount == 8) {
            ResponsePending = true;
        } else {
            ResponsePending = false;
        }
    }
    else
    {
        uint8_t dummy;
                  dummy = I2C2_RECEIVE_REG; 
    }


}



uint32_t lastI2CInterruptCount = 0x80000000;
uint16_t i2cHealthMonitorSuspicionSCL = 0;
uint16_t i2cHealthMonitorSuspicionSDA = 0;
void i2cHealthMonitor()
{
    if (SW_I2CAddress != 0)
    {
        if (lastI2CInterruptCount == I2CInterruptCount)
        {
            if (PORTBbits.RB3 == 0)
            {
                ++i2cHealthMonitorSuspicionSCL;
            }
            else
            {
                i2cHealthMonitorSuspicionSCL = 0;
            }
             if (PORTBbits.RB2 == 0)
            {
                ++i2cHealthMonitorSuspicionSDA;
            }
            else
            {
                i2cHealthMonitorSuspicionSDA = 0;
            }
        }
        else
        {
            i2cHealthMonitorSuspicionSCL = 0;
            i2cHealthMonitorSuspicionSDA = 0;
            lastI2CInterruptCount = I2CInterruptCount;
        }
        
        if (i2cHealthMonitorSuspicionSCL > 100)
        {
            i2cHealthMonitorSuspicionSCL = 0;
            I2C2CONL = 0x1000;
            I2C2CONH = 0;
            I2C2_Initialize();
        }
        if (i2cHealthMonitorSuspicionSDA > 1000)
        {
            i2cHealthMonitorSuspicionSDA = 0;
            I2C2CONL = 0x1000;
            I2C2CONH = 0;
            I2C2_Initialize();
        }
    }
}
