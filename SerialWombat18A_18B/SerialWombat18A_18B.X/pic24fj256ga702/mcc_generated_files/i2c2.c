
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


#define I2C_DEBUG_OUTPUT
#ifdef I2C_DEBUG_OUTPUT
#define OUTPUT_I2C_DEBUG(_value) {LATB = (_value <<11);  LATBbits.LATB10= 1;Nop();Nop();Nop();Nop(); LATBbits.LATB10 = 0;}
#warning I2C_DEBUG_OUTPUT ENABLED!   PORT B DMA Disabled!
#else
#define OUTPUT_I2C_DEBUG(_value){}
#endif
/**
 Section: Data Types
 */

/**
  I2C Slave Driver State Enumeration

  @Summary
    Defines the different states of the i2c slave.

  @Description
    This defines the different states that the i2c slave
    used to process transactions on the i2c bus.
 */
typedef enum {
    S_SLAVE_IDLE,
    S_SLAVE_RECEIVE_MODE,
    S_SLAVE_TRANSMIT_MODE,
    S_SLAVE_LOW_BYTE_ADDRESS_DETECT,

} I2C_SLAVE_STATES;

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

I2C_SLAVE_STATES i2c2_slave_state;
static uint8_t *p_i2c2_write_pointer;
static uint8_t *p_i2c2_read_pointer;

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

void I2C2_Initialize(void) {

    // initialize the hardware
    // ACKEN disabled; STRICT disabled; STREN disabled; GCEN disabled; SMEN disabled; DISSLW enabled; I2CSIDL disabled; ACKDT Sends ACK; SCLREL Holds; RSEN disabled; A10M 7 Bit; PEN disabled; RCEN disabled; SEN disabled; I2CEN enabled; 
    I2C2CONL = 0x8000;

    I2C2CONHbits.AHEN = 1; //JAB_STRETCH
    // BCL disabled; D_nA disabled; R_nW disabled; P disabled; S disabled; I2COV disabled; IWCOL disabled; 
    I2C2STAT = 0x00;
    // ADD 49; 
    extern uint8_t SW_I2CAddress;
    I2C2_SlaveAddressSet(SW_I2CAddress);
    // MSK 0; 
    I2C2_SlaveAddressMaskSet(0x00);

    // make sure this is set first
    i2c2_slave_state = S_SLAVE_IDLE;

    I2C2_ReadPointerSet(NULL);
    I2C2_WritePointerSet(NULL);

    /* SI2C2 - I2C2 Slave Events */
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
//void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) {
void __attribute__((interrupt, no_auto_psv)) _SI2C2Interrupt(void) {

    static bool prior_address_match = false;
    static bool not_busy = true;
    uint8_t dummy;

    // NOTE: The slave driver will always acknowledge 
    //       any address match.
    DebugLastPoint = 99;
    OUTPUT_I2C_DEBUG(1);
        IFS3bits.SI2C2IF = 0;
       // LATBbits.LATB11 = 1;
    switch (i2c2_slave_state) {
        case S_SLAVE_IDLE:
        case S_SLAVE_RECEIVE_MODE:

            /* When at S_SLAVE_RECEIVE_MODE this mode there
               will be two types of incoming transactions:
               1. Data sent by master
               2. A restart or start detection

               But from the point of view of the firmware, there is
               no difference between S_SLAVE_IDLE and S_SLAVE_RECEIVE_MODE
               states, since the types of incoming transactions will be
               the same so we share the code here.
             */
            //LATBbits.LATB12 = I2C2_DATA_NOT_ADDRESS_STATUS_BIT;
            if (
                    // case of 7-bit address detected
                    (((I2C2_10_BIT_ADDRESS_ENABLE_BIT == 0) &&
                    (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 0))
                    )
                    ||
                    // case of general address call detected
                    (((I2C2_GENERAL_CALL_ENABLE_BIT == 1) &&
                    (I2C2_GENERAL_CALL_ADDRESS_STATUS_BIT == 1)) ||
                    nextInterruptAddress
                    )
                    ) {
            
                if (I2C2_READ_NOT_WRITE_STATUS_BIT == 0) {
                    //Input to this chip.
DebugLastPoint = 1;
                        OUTPUT_I2C_DEBUG(2);
                    //I2C2_StatusCallback(I2C2_SLAVE_RECEIVE_REQUEST_DETECTED);

                    // Receive the data if valid
                    if (I2C2STATbits.ACKTIM) {
                        nextInterruptAddress = true;
                        //LATBbits.LATB10 = 1;
                        DebugLastPoint = 11;
                        OUTPUT_I2C_DEBUG(3);
                        dummy = I2C2_RECEIVE_REG; //JAB

                        I2C2CONLbits.ACKDT = 0; //JAB_STRECTH
                       // I2C2CONLbits.ACKEN = 1; //JAB_STRECTH
                          
                         if (ResponsePending && !ResponseAvailable) 
                            { 
                                    
                            RX_ClockStretching = CLOCK_STRETCHING_MAX;
                                   DebugLastPoint = 12;
                                   OUTPUT_I2C_DEBUG(4);
                                       
                            }
                            else
                            {
                                     I2C2_RELEASE_SCL_CLOCK_CONTROL_BIT = 1;
                                            DebugLastPoint = 13;
                                            OUTPUT_I2C_DEBUG(5);
                            }
                         
                        wombatI2CTxDataCount = 0;
                       // LATBbits.LATB10 = 0;
                    } else {
                        nextInterruptAddress = false;
                        //LATBbits.LATB13 = 1;
                         dummy = I2C2_RECEIVE_REG; //JAB
                         i2c2_slave_state = S_SLAVE_RECEIVE_MODE;
                         
                            DebugLastPoint = 3;
                            OUTPUT_I2C_DEBUG(6);
                           // LATBbits.LATB13 = 0;
                            if (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 1)
                            {
                                discardI2CData = true;
                                OUTPUT_I2C_DEBUG(7);
                            }
                           /* if (!I2C2STATbits.TBF) {
                                I2C2_TransmitProcess();
                                DebugLastPoint = 4;
                            }
                            */
                        }
                    

                } else {
                    DebugLastPoint = 53;
                    OUTPUT_I2C_DEBUG(8);
                    if (I2C2STATbits.ACKTIM) {
                           nextInterruptAddress = true;
                        DebugLastPoint = 5;
                        OUTPUT_I2C_DEBUG(9);
                        dummy = I2C2_RECEIVE_REG;
                      //  i2c2_slave_state = S_SLAVE_TRANSMIT_MODE;
                        I2C2CONLbits.ACKDT = 0; //JAB_STRECTH
                       // I2C2CONLbits.ACKEN = 1; //JAB_STRECTH
                        wombatI2CTxDataCount= 0;
                         if (ResponsePending && !ResponseAvailable) 
                            { 
                            // LATBbits.LATB15 = 1;
                              TX_ClockStretching = CLOCK_STRETCHING_MAX;
                              DebugLastPoint = 51;
                              OUTPUT_I2C_DEBUG(10);
                      // LATBbits.LATB15 = 0;

                              return;
                         }
                         else
                         {
                             I2C2_RELEASE_SCL_CLOCK_CONTROL_BIT = 1;
                             DebugLastPoint = 52;
                             OUTPUT_I2C_DEBUG(11);
                         }
               
                    } else {
                        DebugLastPoint = 6;
                        OUTPUT_I2C_DEBUG(12);
                        // read the receive register only when
                        // we are ready for the next transaction.
                        // this one is a dummy read
                             
                        // it is a read, go to transmit mode
                        dummy = I2C2_RECEIVE_REG;
                        I2C2_StatusCallback(I2C2_SLAVE_TRANSMIT_REQUEST_DETECTED);

                        // during this portion, the master is expecting the
                        // slave for a reply. So the returned status of
                        // the callback at this point cannot be used to 
                        // delay the reply if needed.
                        // In other words, the slave has to reply to the master.
                        // Therefore, the transmit will be performed.

                        I2C2_TransmitProcess();
                        i2c2_slave_state = S_SLAVE_TRANSMIT_MODE;
                    }
                }
                             


            }
            else if
                (

                    // case of 10-bit high address detected
                    ((I2C2_10_BIT_ADDRESS_ENABLE_BIT == 1) &&
                    (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 0)
                    )
                    ) {
                             DebugLastPoint = 7;
                             OUTPUT_I2C_DEBUG(13);
                if (I2C2_READ_NOT_WRITE_STATUS_BIT == 0) {
                                 DebugLastPoint = 8;
                                 OUTPUT_I2C_DEBUG(14);
                    // it is the detection of high byte address of 
                    // 10-bit address, go to detection of low byte address
                    prior_address_match = false;
                    i2c2_slave_state = S_SLAVE_LOW_BYTE_ADDRESS_DETECT;

                } else // if (I2C2_READ_NOT_WRITE_STATUS_BIT == 1)
                {
                                 DebugLastPoint = 9;
                                 OUTPUT_I2C_DEBUG(15);
                    if (prior_address_match == true) {
                                     DebugLastPoint = 10;
                                     OUTPUT_I2C_DEBUG(16);
                        // it is the detection of high byte
                        // address of 10-bit address, but the next
                        // transaction is read transaction (so it
                        // is a restart).
                        // set the transmit register with the data
                        // to transmit then go to transmit mode

                        I2C2_StatusCallback(I2C2_SLAVE_TRANSMIT_REQUEST_DETECTED);

                        // during this portion, the master is expecting the
                        // slave for a reply. So the returned status of
                        // the callback at this point cannot be used to
                        // delay the reply if needed.
                        // In other words, the slave has to reply to the master.
                        // Therefore, the transmit will be performed.

                        I2C2_TransmitProcess();
                        i2c2_slave_state = S_SLAVE_TRANSMIT_MODE;
                    } else {
                                     DebugLastPoint = 11;
                                     OUTPUT_I2C_DEBUG(17);
                        // it is the detection of high byte address of
                        // 10-bit address, but next transaction is a write.
                        // go to detection of low byte address
                        prior_address_match = false;
                        i2c2_slave_state = S_SLAVE_LOW_BYTE_ADDRESS_DETECT;

                    }
                }

                // dummy read is needed
                dummy = I2C2_RECEIVE_REG;
            }
            else
            {
                DebugLastPoint = 100;
                OUTPUT_I2C_DEBUG(18);
            }

            // this if statement is to make sure we only save incoming
            // data when we are truly in receiving mode
            if (i2c2_slave_state == S_SLAVE_RECEIVE_MODE) {
                             DebugLastPoint = 12;
                             OUTPUT_I2C_DEBUG(19);
                // case of data received
                if (I2C2_DATA_NOT_ADDRESS_STATUS_BIT == 1) {
                                 DebugLastPoint = 13;
                                 OUTPUT_I2C_DEBUG(20);
                    // check if we are overflowing the receive buffer
                    if (I2C2_RECEIVE_OVERFLOW_STATUS_BIT != 1) {
                                     DebugLastPoint = 14;
                                     OUTPUT_I2C_DEBUG(21);

                        I2C2_ReceiveProcess();
                                  
                        // not_busy = I2C2_StatusCallback(I2C2_SLAVE_RECEIVED_DATA_DETECTED);
                    } else {
                        // overflow detected!
                        // read the buffer to reset the buffer full flag
                        // and clear the overflow bit
                        // then do nothing so the master
                        // will resend the data
                        dummy = I2C2_RECEIVE_REG;
                        I2C2_RECEIVE_OVERFLOW_STATUS_BIT = 0;
                                     DebugLastPoint = 15;
                                     OUTPUT_I2C_DEBUG(22);
                    }
                }
            }

            break;

        case S_SLAVE_LOW_BYTE_ADDRESS_DETECT:
            // Note that this state will only get
            // executed when 10-bit address is set

            // we send receive request but we do not actually know
            // if the next one is a data from master since the 
            // next one can be a restart with a transmit request.
            // When that happens, the next state will take care of it.
            // This is just the nature of i2c bus protocol.
            not_busy = I2C2_StatusCallback(I2C2_SLAVE_10BIT_RECEIVE_REQUEST_DETECTED);
       DebugLastPoint = 18;
            OUTPUT_I2C_DEBUG(23);
            // set this flag to indicate we have
            // full 10-bit address detection
            prior_address_match = true;

            if (not_busy) {
                       DebugLastPoint = 19;
                       OUTPUT_I2C_DEBUG(24);
                // dummy read is needed
                dummy = I2C2_RECEIVE_REG;
            }

            i2c2_slave_state = S_SLAVE_RECEIVE_MODE;

            break;

        case S_SLAVE_TRANSMIT_MODE:

            // this is the state where an ACK or NACK is expected
            // to occur after the slave has placed data to the
            // transmit register.

            // if the transaction was ACK'ed, more data needs to be sent
            // if the transaction was NACK'ed then we don't need to send
            // more data
            if (I2C2_ACKNOWLEDGE_STATUS_BIT == 0) {
                // prepare next data
                I2C2_StatusCallback(I2C2_SLAVE_TRANSMIT_REQUEST_DETECTED);

                // transmit more data
                I2C2_TransmitProcess();
                                    DebugLastPoint = 16;
                                    OUTPUT_I2C_DEBUG(25);

            } else //if (I2C2_ACKNOWLEDGE_STATUS_BIT == 1)
            {
                // no more data to be sent so we go to idle state
                i2c2_slave_state = S_SLAVE_IDLE;
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
            // should never happen, if we ever get here stay here forever
            while (1);
            break;
    }


    // clear the slave interrupt flag
    //LATBbits.LATB11 = 0;
}

void I2C2_ReadPointerSet(uint8_t *p) {
    p_i2c2_read_pointer = p;
}

void I2C2_WritePointerSet(uint8_t *p) {
    p_i2c2_write_pointer = p;
}

uint8_t *I2C2_ReadPointerGet(void) {
    return (p_i2c2_read_pointer);
}

uint8_t *I2C2_WritePointerGet(void) {
    return (p_i2c2_write_pointer);
}

void I2C2_SlaveAddressMaskSet(
        uint16_t mask) {
    I2C2_MASK_REG = mask;
}

void I2C2_SlaveAddressSet(
        uint16_t address) {
    if (address > 0x7F) {
        // use 10 bit address
        I2C2_10_BIT_ADDRESS_ENABLE_BIT = true;
    } else {
        // use 7 bit address
        I2C2_10_BIT_ADDRESS_ENABLE_BIT = false;
    }
    i2c2_slave_state = S_SLAVE_IDLE;
    I2C2_ADDRESS_REG = address;

}

inline void __attribute__((always_inline)) I2C2_TransmitProcess(void) {
    /*JAB
    // get the data to be transmitted
    
    // sanity check (to avoid stress)
    if (p_i2c2_read_pointer == NULL)
        return;

    I2C2_TRANSMIT_REG = *p_i2c2_read_pointer;

     */
    
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
    // store the received data 

    /*JAB
    // sanity check (to avoid stress)
    if (p_i2c2_write_pointer == NULL)
        return;

     *p_i2c2_write_pointer = I2C2_RECEIVE_REG;
     */
OUTPUT_I2C_DEBUG(wombatI2CRxDataCount);
if (discardI2CData)
{
    OUTPUT_I2C_DEBUG(31);
    OUTPUT_I2C_DEBUG(31);
    OUTPUT_I2C_DEBUG(31);
    discardI2CData = false;
}
else if (wombatI2CRxDataCount < 8) {
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
                  dummy = I2C2_RECEIVE_REG; //JAB
    }


}

/* Note: This is an example of the I2C2_StatusCallback()
         implementation. This is an emulated EEPROM Memory
         configured to act as a I2C Slave Device.
         For specific slave device implementation, remove
         or modify this function to the specific slave device
         behavior.
 */

static uint8_t i2c2_slaveWriteData = 0xAA;

bool I2C2_StatusCallback(I2C2_SLAVE_DRIVER_STATUS status) {

    // this emulates the slave device memory where data written to slave
    // is placed and data read from slave is taken
    /*
     Emulate EEPORM default memory size is 64bytes
 
     Emulate EEPORM Read/Write Instruction:
     --------------------------------------     
     Byte Write Instruction:
     |Start|slave Addr + w|Ack|AddrHighByte|Ack|AddrLowByte|Ack|data|Nack|Stop|
     
     Page Write Instruction:
     |Start|slave Addr + w|Ack|AddrHighByte|Ack|AddrLowByte|Ack|dataByte n|Ack|...|data Byte n+x|Nack|Stop|
     
     Byte Read Instruction:
     |Start|slave Addr + r|Ack|AddrHighByte|Ack|AddrLowByte|Ack|data|Nack|Stop|

     Page Read Instruction:
     |Start|slave Addr + r|Ack|AddrHighByte|Ack|AddrLowByte|Ack|dataByte n|Ack|...|dataByte n+x|Nack|Stop|
     */

    static uint8_t EMULATE_EEPROM_Memory[EMULATE_EEPROM_SIZE] ={
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };

    static uint16_t address, addrByteCount;
    static bool addressState = true;

    switch (status) {
        case I2C2_SLAVE_TRANSMIT_REQUEST_DETECTED:
            // set up the slave driver buffer transmit pointer
            I2C2_ReadPointerSet(&EMULATE_EEPROM_Memory[address++]);
            if (address >= EMULATE_EEPROM_SIZE) {
                address = 0;
            }
            break;

        case I2C2_SLAVE_RECEIVE_REQUEST_DETECTED:

            addrByteCount = 0;
            addressState = true;

            // set up the slave driver buffer receive pointer
            I2C2_WritePointerSet(&i2c2_slaveWriteData);
            break;

        case I2C2_SLAVE_RECEIVED_DATA_DETECTED:

            if (addressState == true) {
                // get the address of the memory being written
                if (addrByteCount == 0) {
                    address = (i2c2_slaveWriteData << 8) & 0xFF00;
                    addrByteCount++;
                } else if (addrByteCount == 1) {
                    address = address | i2c2_slaveWriteData;
                    addrByteCount = 0;
                    addressState = false;
                }

                if (address >= EMULATE_EEPROM_SIZE) {
                    address = EMULATE_EEPROM_SIZE;
                }
            } else // if (addressState == false)
            {
                // set the memory with the received data
                EMULATE_EEPROM_Memory[address++] = i2c2_slaveWriteData;
                if (address >= EMULATE_EEPROM_SIZE) {
                    address = 0;
                }
            }

            break;

        case I2C2_SLAVE_10BIT_RECEIVE_REQUEST_DETECTED:

            // do something here when 10-bit address is detected

            // 10-bit address is detected

            break;

        default:
            break;

    }

    return true;
}




