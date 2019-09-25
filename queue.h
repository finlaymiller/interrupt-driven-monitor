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

#define MAX_Q_LEN 32
#define NUM_Q 2

typedef struct q_struct
{
  char contents[MAX_Q_LEN];
  int head;
  int tail;
} q_struct;

typedef struct q_struct *q_ptr;
q_ptr q_table[NUM_Q];

// declare queue-related functions
q_ptr initQ(void);
void freeQ(int);
int isQEmpty(int);
int isQFull(int);
void enQ(int, char);
char deQ(int);
void printQ(int);

#endif /* QUEUE_H_ */
