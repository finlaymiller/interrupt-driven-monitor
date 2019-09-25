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

typedef q_struct *q_ptr;
q_ptr q_table[NUM_Q];

// declare queue-related functions
void initQTable(int);
void initQ(q_ptr);
void freeQ(int);
int isQEmpty(int);
int isQFull(int, int);
void enQ(int, char);
char deQ(int);
void printQ(int);

void set_tx_queue_busy(char busy);
char get_tx_queue_busy(void);

#endif /* QUEUE_H_ */
