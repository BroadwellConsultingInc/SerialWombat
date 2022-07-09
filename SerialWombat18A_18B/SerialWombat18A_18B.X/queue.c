#include "serialWombat.h"
#include <stdint.h>
#include <string.h>

typedef struct
{
uint16_t marker;
uint16_t headIndex; //First byte to come out.
uint16_t tailIndex; //Where to place next byte that comes in.
uint16_t capacity;
uint8_t buffer[1];
}queueByte_t;

uint16_t QueueOverflowCounter = 0;
uint16_t QueueUnderflowCounter = 0;

#define QUEUE_MARKER_QUEUE_BYTE 0x3D7C
#define QUEUE_MARKER_QUEUE_SHIFT 0xF314
SW_QUEUE_RESULT_t QueueByteInitialize(uint16_t address, uint16_t capacity)
{
	//TODO Future improvement: if (address == 0xFFFF) automatically allocate
    //TODO Add protection to all queue functions
	if (address + capacity >= SIZE_OF_USER_BUFFER)
	{
		return (QUEUE_RESULT_INSUFFICIENT_USER_SPACE);
	}

	if ((address & 0x01) != 0)
	{
		return (QUEUE_RESULT_UNALIGNED_ADDRESS);
	}

	queueByte_t* queue = (queueByte_t*) &UserBuffer[address];
	queue->marker = QUEUE_MARKER_QUEUE_BYTE;

	queue->headIndex = 0;
	queue->tailIndex = 0;
	queue->capacity = capacity;
    
	return (QUEUE_RESULT_SUCCESS);
}
SW_QUEUE_RESULT_t QueueByteShiftInitialize(uint16_t address, uint16_t capacity)
{
	//TODO  Future improvement: if (address == 0xFFFF) automatically allocate
    //TODO Add protection to all queue functions
	if (address + capacity >= SIZE_OF_USER_BUFFER)
	{
		return (QUEUE_RESULT_INSUFFICIENT_USER_SPACE);
	}

	if ((address & 0x01) != 0)
	{
		return (QUEUE_RESULT_UNALIGNED_ADDRESS);
	}

	queueByte_t* queue = (queueByte_t*) &UserBuffer[address];
	queue->marker = QUEUE_MARKER_QUEUE_SHIFT;

	queue->headIndex = 0;
	queue->tailIndex = 0;
	queue->capacity = capacity;
    uint16_t i;
    for (i = 0; i < capacity; ++i)
    {
        queue->buffer[i] = ' ';
    }
	return (QUEUE_RESULT_SUCCESS);
}

#define QUEUE_FULL_INDEX 0xFFFF
static uint16_t QueueGetBytesFilledInByteQueue(uint16_t address)
{
	queueByte_t* queue = (queueByte_t*)&UserBuffer[address];
	if (queue->headIndex == queue->tailIndex)
	{
		return (0);
	}
	else if (queue->tailIndex == QUEUE_FULL_INDEX)
	{
		return (queue->capacity);
	}
	else if (queue->tailIndex > queue->headIndex)
	{
		return (queue->tailIndex - queue->headIndex);
	}
	else
	{
		return (queue->capacity - queue->headIndex + queue->tailIndex);
	}
}

SW_QUEUE_RESULT_t QueueGetBytesFilledInQueue(uint16_t address,uint16_t* bytesInQueue )
{
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
	uint16_t queueMarker = *((uint16_t*)&UserBuffer[address]);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			 *bytesInQueue = QueueGetBytesFilledInByteQueue(address);
			 return (QUEUE_RESULT_SUCCESS);
		}
		break;
	}

	return (QUEUE_RESULT_INVALID_QUEUE);

}

SW_QUEUE_RESULT_t QueueGetBytesFreeInQueue(uint16_t address,uint16_t* bytesFreeInQueue )
{
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
	uint16_t queueMarker = *((uint16_t*)&UserBuffer[address]);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			 *bytesFreeInQueue = ((queueByte_t*)&UserBuffer[address])->capacity -  QueueGetBytesFilledInByteQueue(address);
			 return (QUEUE_RESULT_SUCCESS);
		}
		break;
	}

	return (QUEUE_RESULT_INVALID_QUEUE);

}

static SW_QUEUE_RESULT_t QueueByteAddByte(uint16_t address, uint8_t data)
{
	queueByte_t* queue =(queueByte_t*) &UserBuffer[address];
	if (queue->tailIndex == QUEUE_FULL_INDEX)
	{
		++QueueOverflowCounter;
		return (QUEUE_RESULT_FULL);
	}
	queue->buffer[queue->tailIndex ] = data;
	++ queue->tailIndex;
	if (queue->tailIndex == queue->capacity)
	{
		queue->tailIndex = 0;
	}
	if (queue->tailIndex == queue->headIndex)
	{
		queue->tailIndex = QUEUE_FULL_INDEX;
	}
	return (QUEUE_RESULT_SUCCESS);

}

static SW_QUEUE_RESULT_t QueueByteAddByteShift(uint16_t address, uint8_t data)
{
	queueByte_t* queue =(queueByte_t*) &UserBuffer[address];
    uint16_t i;
    if (queue->headIndex < queue->capacity)
    {
        queue->buffer[queue->headIndex] = data;
        ++ queue->headIndex;
    }
    else
    {
	for ( i = 1; i < queue->capacity; ++i)
	{
		queue->buffer[i-1] = queue->buffer[i];
	}
	queue->buffer[queue->capacity -1] = data;
    }
	return (QUEUE_RESULT_SUCCESS);

}

SW_QUEUE_RESULT_t QueueAddByte(uint16_t address, uint8_t data)
{
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
    
	uint16_t queueMarker = *((uint16_t*)&UserBuffer[address]);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			return (QueueByteAddByte( address,  data));
		}
		break;

		case QUEUE_MARKER_QUEUE_SHIFT:
		{
			return (QueueByteAddByteShift(address,data));
		}
		break;
	}
	return (QUEUE_RESULT_INVALID_QUEUE);
}

static SW_QUEUE_RESULT_t QueueByteReadByte(uint16_t address, uint8_t* data)
{
	queueByte_t* queue =(queueByte_t*) &UserBuffer[address];
	if (queue->tailIndex == queue->headIndex)
	{
		*data = 0;
		++QueueUnderflowCounter;
		return (QUEUE_RESULT_EMPTY);
	}
	if (queue->tailIndex == QUEUE_FULL_INDEX)
	{
		queue->tailIndex = queue->headIndex;
	}
	*data = queue->buffer[queue->headIndex ];
	++ queue->headIndex;
	if (queue->headIndex == queue->capacity)
	{
		queue->headIndex = 0;
	}
	return (QUEUE_RESULT_SUCCESS);
}

static SW_QUEUE_RESULT_t QueueBytePeekByte(uint16_t address, uint8_t* data)
{
	queueByte_t* queue =(queueByte_t*) &UserBuffer[address];
	if (queue->tailIndex == queue->headIndex)
	{
		*data = 0;
		return (QUEUE_RESULT_EMPTY);
	}
	if (queue->tailIndex == QUEUE_FULL_INDEX)
	{
		queue->tailIndex = queue->headIndex;
	}
	*data = queue->buffer[queue->headIndex ];
	return (QUEUE_RESULT_SUCCESS);
}

SW_QUEUE_RESULT_t QueueReadByte(uint16_t address, uint8_t* data)
{
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
	uint16_t queueMarker = *((uint16_t*)&UserBuffer[address]);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			return (QueueByteReadByte( address,  data));
		}
		break;
	}
	return (QUEUE_RESULT_INVALID_QUEUE);
}

SW_QUEUE_RESULT_t QueuePeekByte(uint16_t address, uint8_t* data)
{
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
	uint16_t queueMarker = *((uint16_t*)&UserBuffer[address]);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			return (QueueBytePeekByte( address,  data));
		}
		break;
	}
	return (QUEUE_RESULT_INVALID_QUEUE);
}

SW_QUEUE_RESULT_t QueueCopy(uint16_t dstAddress, uint16_t srcAddress)
{
    if (srcAddress >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
     if (dstAddress >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t) - 
             ((queueByte_t*) &UserBuffer[srcAddress])->capacity)
             )
	{
		return (SW_ERROR_QUEUE_RESULT_INSUFFICIENT_USER_SPACE);
	}
	uint16_t queueMarker = *((uint16_t*)&UserBuffer[srcAddress]);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
        case QUEUE_MARKER_QUEUE_SHIFT:
		{
            memcpy(&UserBuffer[dstAddress], & UserBuffer[srcAddress], 8 + ((queueByte_t*) &UserBuffer[srcAddress])->capacity);
			return (QUEUE_RESULT_SUCCESS);
		}
		break;
        

	}
	return (QUEUE_RESULT_INVALID_QUEUE);
}