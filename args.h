/*
 * args.h
 *
 *  Created on: Sep 21, 2019
 *      Author: Finlay Miller
 */

#ifndef ARGS_H_
#define ARGS_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "alarm.h"
#include "time.h"
#include "date.h"
#include "queue.h"
#include "uart.h"


/* required definitions */
#define NUM_ARGS 3
#define NUM_TOKS 2
#define MAX_CMD_LEN 20
#define MAX_NAME_LEN 6
#define KEY_ENTER '\x0d'
#define KEY_EXIT  '\e'
#define KEY_BKSPC '\x08'

/* Globals */
typedef struct arg
{
    char name[MAX_NAME_LEN];
    int length;
    void (*function)(char *);
} arg_struct;

extern arg_struct arg_table[NUM_ARGS];

void initCommandTable(void);
void initCommandString(void);
void fill_tx_queue(char *, char);

void echoRX(char);
void pollQ(int);
void handleRX(int);
void checkChar(char);
void parseCommand(void);
void dateHandler(char *);
void timeHandler(char *);
void alarmHandler(char *);

#endif /* ARGS_H_ */
