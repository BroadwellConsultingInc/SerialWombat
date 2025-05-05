#include "swI2cRoutines.h"

swI2cRoutines_t* SWI2C;

#define SWI2C_SDA_High() {if (SWI2C->lastSDA != 1){PinHigh(SWI2C->sdaPin); SWI2C->lastSDA = 1;}}
#define SWI2C_SDA_Low() {if (SWI2C->lastSDA != 0){PinLow(SWI2C->sdaPin); SWI2C->lastSDA = 0;}}
#define SWI2C_SCL_Low() {CurrentPinLow();}
#define SWI2C_SCL_High() {CurrentPinHigh();}

void SWI2C_start()
{
	SWI2C_SDA_High();
	SWI2C_SCL_High();
	SWI2C_SDA_Low();
	SWI2C_SCL_Low();
}

void SWI2C_stop()
{
	SWI2C_SDA_Low();
	SWI2C_SCL_High();
	SWI2C_SDA_High();

}

bool SWI2C_sendDataByte(uint8_t data)
{
	uint8_t i;
	for (i = 0; i < 8; ++i)
	{
		if (data & 0x80)
		{
			SWI2C_SDA_High();
		}
		else
		{
			SWI2C_SDA_Low();
		}
		SWI2C_SCL_High();
		SWI2C_SCL_Low();
		data <<= 1;
	}
	SWI2C_SDA_High();
	SWI2C_SCL_High();

		SWI2C_SCL_High(); // Duplicated to add delay  //TODO  Add delay for ack?
	
	bool ack = !ReadPin(SWI2C->sdaPin);
	SWI2C_SCL_Low();
	return (ack);
}

uint8_t SWI2C_receiveDataByte(bool ack)
{
	uint8_t dat = 0;
	SWI2C_SDA_High();
    uint8_t i;
	for(i =0; i<8; i++)
	{
		dat <<= 1;
		SWI2C_SCL_High();
		if (CurrentPinRead() == 0) { // Clock Stretching
			//Act like a Nak
			//  TODO implement better state machine
		}
		//TODO Delay for read?
		if(ReadPin(SWI2C->sdaPin))
		{
			dat |=1;
		}
		//TODO Delay?
		SWI2C_SCL_Low();
		if (ack)
		{ 
			SWI2C_SDA_Low();
		}	
		else
		{
			SWI2C_SDA_High();	
		}
		SWI2C_SCL_High();
		//TODO dly();
		SWI2C_SCL_Low();
		SWI2C_SDA_High();	
	}
    	return(dat);
}


void SWI2C_beginTransmission(uint8_t address)
{
	SWI2C->address = address;
	SWI2C->startSent = 0;
	SWI2C->txAddressSent = 0;
	SWI2C->rxAddressSent = 0;
    SWI2C->isizeSent = 0;
}

void SWI2C_requestFrom(uint8_t address, uint8_t quantity,  uint8_t sendStop)
{
	SWI2C->readStop = sendStop;
    SWI2C->address = address;
	
	if (quantity > SWI2C_RX_BUFFER_SIZE)
	{
		quantity = SWI2C_RX_BUFFER_SIZE;
	}
    SWI2C->bytesToRx = quantity;
    SWI2C->readStop = sendStop;
}

void SWI2C_writeByte(uint8_t val)
{
	if (SWI2C->bytesToTx < SWI2C_TX_BUFFER_SIZE)
	{
		SWI2C->tx[SWI2C->bytesToTx] = val;
	}
	++ SWI2C->bytesToTx;
}

void SWI2C_writeArray(uint8_t* data, uint8_t length)
{
	uint8_t i;
	for (i = 0; i < length && i < SWI2C_TX_BUFFER_SIZE; ++ i)
	{
		SWI2C_writeByte(data[i]);
	}
}

void SWI2C_endTransmission(uint8_t stop)
{
	SWI2C->writeStop = stop;
}

void SWI2C_executeTransaction( uint8_t bytesPerFrame)
{
	SWI2C->busy = 1;
	SWI2C->bytesPerSWFrame = bytesPerFrame;
	SWI2C->nackResult = 0;
}


void updateSWI2C()
{
	if (!SWI2C->busy)
	{
		return;
	}
	SWI2C->bytesTransferredThisSWFrame = 0;

	while (SWI2C->busy && SWI2C->bytesTransferredThisSWFrame < SWI2C->bytesPerSWFrame)
	{


		if (SWI2C->bytesTransmitted < SWI2C->bytesToTx)
		{
			
			if (!SWI2C->txAddressSent)
			{
                if (!SWI2C->startSent)
			{
				SWI2C_start();
				SWI2C->startSent = 1;
			}
				bool ack = SWI2C_sendDataByte(SWI2C->address <<1);
				if (!ack)
				{
					SWI2C->busy = 0;
					SWI2C->nackResult = 1;
					SWI2C_stop();
					return;
				}
				++SWI2C->bytesTransferredThisSWFrame;
				SWI2C->txAddressSent = 1;
				continue;
			}

			bool ackData;
			ackData = SWI2C_sendDataByte(SWI2C->tx[SWI2C->bytesTransmitted]);
			if (!ackData)
			{
				SWI2C->busy = 0;
				SWI2C->nackResult = 1;
				SWI2C_stop();
				return;
			}
			++ SWI2C->bytesTransmitted;
			++SWI2C->bytesTransferredThisSWFrame;
			if (SWI2C->bytesTransmitted == SWI2C->bytesToTx)
			{
				SWI2C->startSent = 0;
			}
			continue;
		}
		if (SWI2C->isizeSent < SWI2C->isize)
		{
			if (!SWI2C->txAddressSent)
			{
				if (!SWI2C->startSent)
				{
					SWI2C_start();
					SWI2C->startSent = 1;
				}
				bool ack = SWI2C_sendDataByte(SWI2C->address <<1);
				if (!ack)
				{
					SWI2C->busy = 0;
					SWI2C->nackResult = 1;
					SWI2C_stop();
					return;
				}
				++SWI2C->bytesTransferredThisSWFrame;
                
				SWI2C->txAddressSent = 1;
				continue;
			}

			bool ackData;
			ackData = SWI2C_sendDataByte(((uint8_t*)&SWI2C->iaddress)[SWI2C->isizeSent]);
			if (!ackData)
			{
				SWI2C->busy = 0;
				SWI2C->nackResult = 1;
				SWI2C_stop();
				return;
			}
			++ SWI2C->isizeSent;
			++SWI2C->bytesTransferredThisSWFrame;
			if (SWI2C->isize == SWI2C->isizeSent)
			{
				SWI2C->startSent = 0;
			}
			continue;
		}
		if (SWI2C->bytesReceived < SWI2C->bytesToRx)
		{
			if (!SWI2C->rxAddressSent)
			{
				if (!SWI2C->startSent)
				{
					SWI2C_start();
					SWI2C->startSent = 1;
				}
				bool ack = SWI2C_sendDataByte((SWI2C->address <<1)|0x01);
				if (!ack)
				{
					SWI2C->busy = 0;
					SWI2C->nackResult = 1;
					SWI2C_stop();
					return;
				}
				++SWI2C->bytesTransferredThisSWFrame;
				SWI2C->rxAddressSent = 1;
				continue;
			}


			uint8_t data  = SWI2C_receiveDataByte(SWI2C->bytesReceived +1 < SWI2C->bytesToRx);
			SWI2C->rx[SWI2C->bytesReceived] = data;
			++ SWI2C->bytesReceived;
			++SWI2C->bytesTransferredThisSWFrame;
			continue;
		}


		if (SWI2C->bytesTransmitted >= SWI2C->bytesToTx && SWI2C->bytesReceived >= SWI2C->bytesToRx  && SWI2C->isizeSent >= SWI2C->isize)
		{
			if (SWI2C->readStop || SWI2C->writeStop)
			{
				SWI2C_stop();
			}
			SWI2C->busy = 0;
		}
	}
}	

