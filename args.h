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
#include "buffer.h"
#include "time.h"
#include "date.h"
#include "uart.h"


/* required definitions */
#define NUM_ARGS 3
#define NUM_TOKS 2
#define MAX_CMD_LEN 20
#define MAX_NAME_LEN 6
#define KEY_ENTER '\x0d'
#define KEY_EXIT  '\e'
#define KEY_BKSPC '\x7f'

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

void echoRX(char);
void readRX(buffer_ptr);
void pollRX(buffer_ptr);
void handleRX(buffer_ptr);
void checkChar(char);
void parseCommand(void);
void dateHandler(char *);
void timeHandler(char *);
void alarmHandler(char *);

#endif /* ARGS_H_ */
