#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef enum
{
	QUEUE_RESULT_SUCCESS = 0,
	QUEUE_RESULT_INSUFFICIENT_USER_SPACE = 1,
	QUEUE_RESULT_UNALIGNED_ADDRESS = 2,
	QUEUE_RESULT_INVALID_QUEUE = 3,
	QUEUE_RESULT_FULL = 4,
	QUEUE_RESULT_EMPTY = 5,
}SW_QUEUE_RESULT_t;



extern void* queueAddress ;
SW_QUEUE_RESULT_t QueueByteInitialize( uint16_t capacity);
SW_QUEUE_RESULT_t QueueByteShiftInitialize( uint16_t capacity);
SW_QUEUE_RESULT_t QueueBytesInQueue(uint16_t* bytesInQueue );
SW_QUEUE_RESULT_t QueueAddByte( uint8_t data);
SW_QUEUE_RESULT_t QueueAddWord( uint8_t data);
SW_QUEUE_RESULT_t QueueReadByte( uint8_t* data);
SW_QUEUE_RESULT_t QueueRead16Word( uint16_t* data);
SW_QUEUE_RESULT_t QueuePeekByte( uint8_t* data);
SW_QUEUE_RESULT_t QueueGetBytesFilledInQueue( uint16_t* bytesFilledInQueue);
SW_QUEUE_RESULT_t QueueGetBytesFreeInQueue( uint16_t* bytesFreeInQueue);
SW_QUEUE_RESULT_t QueueCopy(uint16_t dstAddress, uint16_t sourceAddress);

void queueCONFIGURE_CHANNEL_MODE_1_transmit(void* rxQueue, void* txQueue);
void queueCONFIGURE_CHANNEL_MODE_2_receive(void* rxQueue);
void queueCONFIGURE_CHANNEL_MODE_3_peekRX(void* rxQueue, void* txQueue);


#endif
