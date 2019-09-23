/*
 * buffer.h
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#define MAX_BUFFER_LEN 20
#define getName(var_name) #var_name

typedef struct buffer
{
    char contents[MAX_BUFFER_LEN];
    int size;
} buffer;

typedef struct buffer *buffer_ptr;

// declare buffer-related functions
void bufferReset(buffer_ptr buff);
buffer_ptr bufferInit(void);
void bufferFree(buffer_ptr buff);
int isBufferFull(buffer_ptr buff);
int isBufferEmpty(buffer_ptr buff);
void bufferGive(buffer_ptr buff, int data);
int bufferTake(buffer_ptr buff);
void bufferPrint(buffer_ptr buff);
void bufferTest(void);

#endif /* BUFFER_H_ */
