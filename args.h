/*
 * args.h
 *
 *  Created on: Sep 21, 2019
 *      Author: Finlay Miller
 */

#ifndef ARGS_H_
#define ARGS_H_

/* default libraries */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* my libraries */
#include "alarm.h"
#include "time.h"
#include "date.h"
#include "queue.h"
#include "uart.h"

/* globals */
#define NUM_CMDS 3			// number of supported commands
#define NUM_TOKS 2			// number of accepted tokens per line
#define MAX_CMD_LEN 20		// maximum length of accepted command. The max
							// length of a VALID command is 16 characters
#define MAX_NAME_LEN 6		// length of longest command "alarm" + 1 for '\0'
#define KEY_ENTER '\x0d'
#define KEY_BKSPC '\x08'

/* command struct setup */
typedef struct cmd
{
    char name[MAX_NAME_LEN];	// actual name of command
    int length;					// number of characters in command
    void (*function)(char *);	// pointer to the handler for that command
} cmd_struct;

extern cmd_struct cmd_table[NUM_CMDS];

/* initialization functions */
void initCommandTable(void);
void initCommandString(void);

/* command parsing functions */
void stringTX(char *, int);
void handleBackspace(void);
void handleChar(char);
void handleQ(int);
void checkChar(char);
void parseCommand(void);

#endif /* ARGS_H_ */
