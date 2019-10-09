/*
 * command.h
 *
 *  Created on: Sep 21, 2019
 * Modified on:	Oct 05, 2019
 *      Author: Finlay Miller
 */

#ifndef COMMAND_H_
#define COMMAND_H_

/* required custom file links */
#include "alarm.h"
#include "date.h"
#include "time.h"
#include "queue.h"
#include "uart.h"

/* define command properties */
#define NUM_CMDS 3			// number of supported commands
#define NUM_TOKS 2			// number of accepted tokens per line
#define MAX_CMD_LEN 20		// maximum length of accepted command. The max
							// length of a VALID command is 16 characters
#define MAX_NAME_LEN 6		// length of longest command "alarm" + 1 for '\0'
#define KEY_ENTER '\x0d'	// key definitions for better readability
#define KEY_BKSPC '\177'

/* command struct setup */
typedef struct cmd
{
    char name[MAX_NAME_LEN];	// actual name of command
    int length;					// number of characters in command
    int (*function)(char *);	// pointer to the handler for that command
} cmd_struct;

extern cmd_struct cmd_table[NUM_CMDS];

/* function definitions */
/* initialization functions */
void initCommandTable(void);
void initCommandString(void);

/* command parsing functions */
int checkChar(char);
void parseCommand(void);

#endif /* COMMAND_H_ */
