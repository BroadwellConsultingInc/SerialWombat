/**
  I2C1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1_follower.c

  @Summary
    This is the generated driver implementation file for the I2C1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides implementations for driver APIs for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15214
        Driver Version    :  2.0.1
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above or later
        MPLAB             :  MPLAB X 5.40
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "i2c1_follower.h"
#include <xc.h>
#include "serialWombat.h"
const __at(0x1FFC / 2) uint8_t  I2C1_FOLLOWER_ADDRESS =  0x6C;
#define I2C1_FOLLOWER_MASK         127

typedef enum
{
    I2C1_IDLE,
    I2C1_ADDR_TX,
    I2C1_ADDR_RX,
    I2C1_DATA_TX,
    I2C1_DATA_RX
} i2c1_follower_state_t;

uint8_t WombatRX[8];
uint8_t WombatRXBytesReceived = 0;
/**
 Section: Global Variables
 */
volatile uint8_t i2c1WrData;
volatile uint8_t i2c1RdData;
volatile uint8_t i2c1FollowerAddr;
static volatile i2c1_follower_state_t i2c1FollowerState = I2C1_IDLE;

volatile __bit PacketAvailable;
volatile __bit ResponseAvailable;
volatile __bit ResponsePending;

volatile uint8_t TX_ClockStretching;
volatile uint8_t RX_ClockStretching;
/**
 Section: Functions declaration
 */
static void I2C1_Isr(void);

static void I2C1_FollowerDefAddrInterruptHandler(void);
static void I2C1_FollowerDefBusColInterruptHandler(void);


static void I2C1_FollowerBusColCallBack(void);


volatile uint8_t i2cTxBufferCounter = 0;

void I2C1_Initialize()
{
    SSP1STAT  = 0x00;
    SSP1CON1 |= 0x06;
    SSP1CON2  = 0x00;
    //SSP1CON2bits.SEN = 1; // 20201223
        SSP1CON3bits.PCIE = 1;
    SSP1CON1bits.SSPEN = 0;
    SSP1CON3bits.AHEN = 1;

PacketAvailable = 0;
 ResponseAvailable = 0;
 ResponsePending = 0;
TX_ClockStretching = 0;
RX_ClockStretching = 0;
 
}

void I2C1_Open() 
{
    SSP1STAT  = 0x00;
        SSP1CON1 |= 0x06;
        SSP1CON2  = 0x00;
        SSP1CON1bits.SSPEN = 1;
        SSP1CON1bits.CKP = 1;
         SSP1ADD = (uint8_t) (I2C1_FOLLOWER_ADDRESS << 1);
        
        SSP1MSK = (uint8_t) (I2C1_FOLLOWER_MASK << 1);
  
        i2c1FollowerState = I2C1_IDLE;
    PIE1bits.SSP1IE = 1;//I2C1_FollowerEnableIrq();    
}


volatile uint8_t debugPWrCount = 0;
volatile uint8_t debugPRCount = 0;
void I2C1_Isr() 
{ 
    PIR1bits.SSP1IF = 0;//I2C1_FollowerClearIrq();
    
    if(!(SSP1STATbits.D_nA))//I2C1_FollowerIsAddr())
    {
        if(SSP1STATbits.R_nW)//I2C1_FollowerIsRead())
        {
            i2c1FollowerState = I2C1_ADDR_TX;
        }
        else
        {
            i2c1FollowerState = I2C1_ADDR_RX;
	   
        }
    }
    else
    {
        if(SSP1STATbits.R_nW)//I2C1_FollowerIsRead())
        {
            i2c1FollowerState = I2C1_DATA_TX;
        }
        else
        {
            i2c1FollowerState = I2C1_DATA_RX;
        }
    }
   
    switch(i2c1FollowerState)
    {
        case I2C1_ADDR_TX:
            //I2C1_FollowerAddrCallBack();
        {
            
            
            
   // if (I2C1_FollowerAddrInterruptHandler) {
 

	if (SSP1CON3bits.ACKTIM)
	{
		       i2c1FollowerAddr = SSP1BUF; //I2C1_FollowerAddrInterruptHandler();
                SSP1CON2bits.ACKDT = 0; //12262020
			    SSP1CON2bits.ACKEN = 1; //12262020                           
	}
	else
	{
       		 if (ResponsePending && !ResponseAvailable)
                {
                    TX_ClockStretching = CLOCK_STRETCHING_MAX;
			   
                    return;
                }
       		 else if(!SSP1STATbits.BF)//I2C1_FollowerIsTxBufEmpty())
           	 {
             
                extern uint8_t Txbuffer[];
               
                    SSP1BUF = Txbuffer[0];
              
                i2cTxBufferCounter = 7;
               
                
            	}
	}
	}
            break;
        case I2C1_ADDR_RX:
         {
             
            
             
        i2c1FollowerAddr = SSP1BUF; //I2C1_FollowerAddrInterruptHandler();
        ResponseAvailable = 0; // If we're getting a new Reception, whatever response we had ready is moot.
        if (WombatRXBytesReceived >= 8)
                {
                    RX_ClockStretching = CLOCK_STRETCHING_MAX;
                    
                    return;
                }
        else
        {
            WombatRXBytesReceived = 0;
            ResponsePending = 0;
        }
        }
            break;
        case I2C1_DATA_TX:
            if(!SSP1STATbits.BF)//I2C1_FollowerIsTxBufEmpty())
            {
           
                extern uint8_t Txbuffer[];
               if (i2cTxBufferCounter > 0)
                {

                   SSP1BUF = Txbuffer[8- i2cTxBufferCounter];
                   --i2cTxBufferCounter;
                    ResponseAvailable = 0;  // We sent the response.

                }
                else
                {
                    SSP1BUF = 0x55;
                }
                
                   
                
            }
            break;
        case I2C1_DATA_RX:
            if(SSP1STATbits.BF)//I2C1_FollowerIsRxBufFull())
            {
                if (WombatRXBytesReceived == 0)
                {
               WombatRX[0] = 0x55;
             WombatRX[1] = 0x55;
             WombatRX[2] = 0x55;
             WombatRX[3] = 0x55;
             WombatRX[4] = 0x55;
             WombatRX[5] = 0x55;
             WombatRX[6] = 0x55;
             WombatRX[7] = 0x55;
                }
                if (WombatRXBytesReceived < 8)
                {
                WombatRX[WombatRXBytesReceived] = SSP1BUF;//I2C1_FollowerGetRxData();
                
                ++WombatRXBytesReceived;
                }
               if (WombatRXBytesReceived == 8)
                {
                   ResponsePending = true;
                }
                
                 return;
                
            }
            break;
        default:
            break;
    }
    SSP1CON1bits.CKP = 1;//I2C1_FollowerReleaseClock();
}

