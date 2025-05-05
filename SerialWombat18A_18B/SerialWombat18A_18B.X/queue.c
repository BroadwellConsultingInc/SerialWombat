#include "serialWombat.h"
#include <stdint.h>
#include <string.h>


void* queueAddress ;


#ifdef QUEUESIMPLE
typedef struct
{
uint8_t count;
uint8_t size;
uint8_t buffer[1];
}queueByte_t ;
#else

typedef struct
{
uint16_t marker;
uint16_t headIndex; //First byte to come out.
uint16_t tailIndex; //Where to place next byte that comes in.
uint16_t capacity;
uint8_t buffer[1];
}queueByte_t;

#define QUEUE_MARKER_QUEUE_BYTE 0x3D7C
#define QUEUE_MARKER_QUEUE_SHIFT 0xF314

uint16_t QueueOverflowCounter = 0;
uint16_t QueueUnderflowCounter = 0;


#endif


SW_QUEUE_RESULT_t QueueByteInitialize( uint16_t capacity)
{
#ifdef QUEUESIMPLE
	queueByte_t* queue = (queueByte_t*) queueAddress;
	queue->count = 0;
	queue->size = capacity;
#else
	//TODO Future improvement: if (address == 0xFFFF) automatically allocate
    //TODO Add protection to all queue functions
// TODO add checks back in
#ifdef TODO
	if (address + capacity >= SIZE_OF_USER_BUFFER)
	{
		return (QUEUE_RESULT_INSUFFICIENT_USER_SPACE);
	}

	if ((address & 0x01) != 0)
	{
		return (QUEUE_RESULT_UNALIGNED_ADDRESS);
	}

#endif
	queueByte_t* queue = (queueByte_t*) queueAddress;
	queue->marker = QUEUE_MARKER_QUEUE_BYTE;

	queue->headIndex = 0;
	queue->tailIndex = 0;
	queue->capacity = capacity;
#endif 
	return (QUEUE_RESULT_SUCCESS);
}
#ifdef QUEUESIMPLE
#else
SW_QUEUE_RESULT_t QueueByteShiftInitialize(uint16_t capacity)
{
	//TODO  Future improvement: if (address == 0xFFFF) automatically allocate
    //TODO Add protection to all queue functions
#ifdef TODO //Add checks back in
	if (address + capacity >= SIZE_OF_USER_BUFFER)
	{
		return (QUEUE_RESULT_INSUFFICIENT_USER_SPACE);
	}


	if ((address & 0x01) != 0)
	{
		return (QUEUE_RESULT_UNALIGNED_ADDRESS);
	}
#endif
	queueByte_t* queue = (queueByte_t*) queueAddress;
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
#endif

#define QUEUE_FULL_INDEX 0xFFFF
#ifdef QUEUESIMPLE

#else
static uint16_t QueueGetBytesFilledInByteQueue()
{

	queueByte_t* queue = (queueByte_t*)queueAddress;
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

	return 0; //STUB
}
#endif
SW_QUEUE_RESULT_t QueueGetBytesFilledInQueue(uint16_t* bytesInQueue )
{
#ifdef QUEUESIMPLE
	queueByte_t* queue = (queueByte_t*) queueAddress;
	return (queue->count);
#else

#ifdef TODO // Add checks back in
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
#endif
	uint16_t queueMarker = *((uint16_t*)queueAddress);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			 *bytesInQueue = QueueGetBytesFilledInByteQueue();
			 return (QUEUE_RESULT_SUCCESS);
		}
		break;
	}
#endif

	return (QUEUE_RESULT_INVALID_QUEUE);

}

SW_QUEUE_RESULT_t QueueGetBytesFreeInQueue(uint16_t* bytesFreeInQueue )
{
#ifdef QUEUESIMPLE
    queueByte_t* queue = (queueByte_t*) queueAddress;
	*bytesFreeInQueue =  (queue->size - queue->count);
	return (QUEUE_RESULT_SUCCESS);
#else
#ifdef TODO //Add checks back in
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
#endif
	uint16_t queueMarker = *((uint16_t*)queueAddress);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			 *bytesFreeInQueue = ((queueByte_t*)queueAddress)->capacity -  QueueGetBytesFilledInByteQueue();
			 return (QUEUE_RESULT_SUCCESS);
		}
		break;
	}

#endif
	return (QUEUE_RESULT_INVALID_QUEUE);

}

#ifdef QUEUESIMPLE
#else
static SW_QUEUE_RESULT_t QueueByteAddByte(uint8_t data)
{

	queueByte_t* queue =(queueByte_t*) queueAddress;
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
#endif

#ifdef QUEUESIMPLE
#else
static SW_QUEUE_RESULT_t QueueByteAddByteShift(uint8_t data)
{

	queueByte_t* queue =(queueByte_t*) queueAddress;
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
#endif

SW_QUEUE_RESULT_t QueueAddByte(uint8_t data)
{
#ifdef QUEUESIMPLE
    queueByte_t* queue = (queueByte_t*) queueAddress;
	if ( queue->count < queue->size)
	{
		queue->buffer[queue->count] = data;
		++ queue->count;
	return (QUEUE_RESULT_SUCCESS);
	}
	else
	{
		return (QUEUE_RESULT_FULL);
	}
#else
#ifdef TODO //Add checks back in
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
#endif
	uint16_t queueMarker = *((uint16_t*)queueAddress);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			return (QueueByteAddByte( data));
		}
		break;

		case QUEUE_MARKER_QUEUE_SHIFT:
		{
			return (QueueByteAddByteShift(data));
		}
		break;
	}
#endif
	return (QUEUE_RESULT_INVALID_QUEUE);
}
#ifdef QUEUESIMPLE
#else
static SW_QUEUE_RESULT_t QueueByteReadByte(uint8_t* data)
{

	queueByte_t* queue =(queueByte_t*) queueAddress;
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
#endif

#ifdef QUEUESIMPLE
#else
static SW_QUEUE_RESULT_t QueueBytePeekByte(uint8_t* data)
{

	queueByte_t* queue =(queueByte_t*) queueAddress;
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
#endif

SW_QUEUE_RESULT_t QueueReadByte(uint8_t* data)
{
#ifdef QUEUESIMPLE
    queueByte_t* queue = (queueByte_t*) queueAddress;
	if ( queue->count == 0)
	{
		return (QUEUE_RESULT_EMPTY);
	}
	else
	{
	 *data = queue->buffer[0];
	  int i;
	 for (i = 0; i < queue->size-1; ++i)
	 {
		queue->buffer[i] = queue->buffer[i+1];
	 }	
	 --queue->count;
	return (QUEUE_RESULT_SUCCESS);
	}
#else
#ifdef TODO //Add checks back in
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
#endif
	uint16_t queueMarker = *((uint16_t*)queueAddress);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			return (QueueByteReadByte( data));
		}
		break;
	}
	return (QUEUE_RESULT_INVALID_QUEUE);
#endif
}

SW_QUEUE_RESULT_t QueueRead16Word(uint16_t* data)
{
#ifdef QUEUESIMPLE
    queueByte_t* queue = (queueByte_t*) queueAddress;
	if ( queue->count < 2)
	{
		return (QUEUE_RESULT_EMPTY);
	}
	QueueReadByte((uint8_t*)data);
	QueueReadByte(((uint8_t*)data) + 1);
	return (QUEUE_RESULT_SUCCESS);

#else
    #ifdef TODO //Add checks back in
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
#endif
	uint16_t queueMarker = *((uint16_t*)queueAddress);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
            uint8_t dl;
            uint8_t dh;
			SW_QUEUE_RESULT_t result = QueueByteReadByte(  &dl);
            if (result != QUEUE_RESULT_SUCCESS)
            {
                return result;
            }
            result =  QueueByteReadByte(  &dh);
            if (result != QUEUE_RESULT_SUCCESS)
            {
                return result;
            }
            *data = dl;
            *data |= ((uint16_t)dh) <<8;
            
            return result;
		}
		break;
	}
#endif
	return (QUEUE_RESULT_INVALID_QUEUE);
}

SW_QUEUE_RESULT_t QueuePeekByte(uint8_t* data)
{
#ifdef QUEUESIMPLE

    queueByte_t* queue = (queueByte_t*) queueAddress;
	if ( queue->count == 0)
	{
		return (QUEUE_RESULT_EMPTY);
	}
	*data = queue->buffer[0];
	return (QUEUE_RESULT_SUCCESS);
#else
#ifdef TODO // Add back in
	if (address >= (SIZE_OF_USER_BUFFER - sizeof(queueByte_t)))
	{
		return (QUEUE_RESULT_INVALID_QUEUE);
	}
#endif
	uint16_t queueMarker = *((uint16_t*)queueAddress);
	switch (queueMarker)
	{
		case QUEUE_MARKER_QUEUE_BYTE:
		{
			return (QueueBytePeekByte( data));
		}
		break;
	}
#endif
	return (QUEUE_RESULT_INVALID_QUEUE);
}

#ifdef PIC24
SW_QUEUE_RESULT_t QueueCopy(uint16_t dstAddress, uint16_t srcAddress)
{
#ifdef QUEUESIMPLE
#else
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
#endif
	return (QUEUE_RESULT_INVALID_QUEUE);
}
#endif
