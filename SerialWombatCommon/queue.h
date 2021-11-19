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

typedef enum
{
	QUEUE_TYPE_RAM_BYTE = 0, ///< Queues one byte at a time in ram
}SW_QUEUE_TYPE_t;

SW_QUEUE_RESULT_t QueueByteInitialize(uint16_t address, uint16_t capacity);
SW_QUEUE_RESULT_t QueueBytesInQueue(uint16_t address,uint16_t* bytesInQueue );
SW_QUEUE_RESULT_t QueueAddByte(uint16_t address, uint8_t data);
SW_QUEUE_RESULT_t QueueReadByte(uint16_t address, uint8_t* data);
SW_QUEUE_RESULT_t QueuePeekByte(uint16_t address, uint8_t* data);
SW_QUEUE_RESULT_t QueueGetBytesFilledInQueue(uint16_t address, uint16_t* bytesFilledInQueue);
SW_QUEUE_RESULT_t QueueGetBytesFreeInQueue(uint16_t address, uint16_t* bytesFreeInQueue);

#endif
