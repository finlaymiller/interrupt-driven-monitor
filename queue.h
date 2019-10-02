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

#include "args.h"

#define MAX_Q_LEN 32
#define NUM_Q 3
#define UART_RX 0
#define UART_TX 1
#define SYSTICK 2

typedef struct q_struct
{
  char contents[MAX_Q_LEN];
  int head;
  int tail;
} q_struct;

/* declare queue-related functions */
extern void UART0_START(void);
void initQTable(int);
void initQ(q_struct);
void freeQ(int);
int isQEmpty(int);
int isQFull(int);
void enQ(int, char);
char deQ(int);
void printQ(int);

/* UART transmission timing related functions */
void setTXState(int);
int getTXState(void);

#endif /* QUEUE_H_ */
