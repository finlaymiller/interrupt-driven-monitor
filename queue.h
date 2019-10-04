/*
 * queue.h
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

/* define queue properties */
#define MAX_Q_LEN 64	// length of queue
#define NUM_Q 3			// number of queues
#define UART_RX 0
#define UART_TX 1
#define SYSTICK 2

typedef struct q_struct
{
  char contents[MAX_Q_LEN];
  int head;
  int tail;
} q_struct;

/* queue-related macros */
#define NEXT_PTR(ptr) ((ptr + 1) & (MAX_Q_LEN - 1))

/* queue-related functions */
extern void UART0_START(void);

void initQTable(int);
void initQ(q_struct);
void handleQ(int);
void freeQ(int);
int isQEmpty(int);
int isQFull(int);
void enQ(int, char);
char deQ(int);
void printQ(int);

#endif /* QUEUE_H_ */
