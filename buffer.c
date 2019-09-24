/*
 * buffer.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

void bufferReset(buffer_ptr buff)
{
	// clear contents of buffer
    int i;
	for(i = 0; i < MAX_BUFFER_LEN; i++)
	{
		buff->contents[i] = 0;
	}

	// check to make sure it worked
	for(i = 0; i < MAX_BUFFER_LEN; i++)
	{
		int buff_val = buff->contents[i];
		if (buff_val != 0)
		{
			printf("Unable to clear buffer. Value at position %d retained value %d", i, buff_val);
		}
	}
}

buffer_ptr bufferInit(void)
{
	// allocate required memory
    buffer_ptr buff = (buffer_ptr)malloc(sizeof(buffer));   // Do i need to cast this?
	// clear buffer contents
	bufferReset(buff);

    buff->size = 0;

    return buff;
}

void bufferFree(buffer_ptr buff)
{
    free(buff);
}

int isBufferFull(buffer_ptr buff)
{
	return buff->size >= MAX_BUFFER_LEN;
}

int isBufferEmpty(buffer_ptr buff)
{
	return buff->size <= 0;
}

void bufferGive(buffer_ptr buff, int data)
{
	// check to see if buffer is full
	if (isBufferFull(buff))
	{
		printf("Tried to write to full buffer %s.\n", getName(buff));
		exit(1);
	}
	
	// place data on next available buffer slot
	buff->contents[buff->size] = data;
	buff->size++;
}

int bufferTake(buffer_ptr buff)
{
	int data;
	
	// check to see if buffer is empty
	if(isBufferEmpty(buff))
	{
		printf("Tried to remove from empty buffer %s.\n", getName(buff));
		exit(-1);
	}
	
	// get oldest data in buffer
	data = buff->contents[0];
	
	// move data down the queue
	int i;
	for(i = 0; i < buff->size; i++)
	{
		buff->contents[i] = buff->contents[i+1];
	}
	
	buff->size--;
	
	return data;
}

void bufferPrint(buffer_ptr buff)
{
	printf("Printing contents of buffer");

	int i;
	for(i = 0; i < MAX_BUFFER_LEN; i++)
	{
		printf("\n\t------------\n");
		printf("%d\t%c", i, buff->contents[i]);
	}
	
	printf("\n\t------------");
}

void bufferTest(void)
{
	// data to work with
    int fib[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    int fiblen = sizeof(fib) / sizeof(fib[0]);

    buffer_ptr bptr = bufferInit();
    
    // test loading buffer
    int i;
    for(i = 0; i < fiblen; i++)
    {
        bufferGive(bptr, fib[i]);
    }

    bufferPrint(bptr);

    // test removing from buffer
    int ret_val;
    printf("\n");
    for(i = 0; i < 4; i++)
    {
        ret_val = bufferTake(bptr);
        printf("Received val %c from buffer.\n", ret_val);
    }

    bufferPrint(bptr);
}
