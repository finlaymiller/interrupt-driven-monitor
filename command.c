/*
 * command.c
 *
 *  Created on: Sep 21, 2019
 * Modified on:	Oct  5, 2019
 *      Author: Finlay Miller
 *
 *	Contains functions related to handling user-input commands. Supported
 *	commands are detailed in the design doc as well as main.c
 */

#include "command.h"

/* globals */
char cmd_rx[MAX_CMD_LEN];		// command string received from UART
int cmd_index;					// number of characters in command string
cmd_struct cmd_table[NUM_CMDS];	// table containing command data
extern volatile char data_rx;	// last character received by UART


/*
 * Creates a table of command structs (see headerfile for command struct def)
 *
 * @param: 	None
 * @return: None
 */
void initCommandTable(void)
{
    strcpy(cmd_table[0].name, "DATE");
    cmd_table[0].length = strlen(cmd_table[0].name);
    cmd_table[0].function = &dateHandler;

    strcpy(cmd_table[1].name, "TIME");
    cmd_table[1].length = strlen(cmd_table[1].name);
    cmd_table[1].function = &timeHandler;

    strcpy(cmd_table[2].name, "ALARM");
    cmd_table[2].length = strlen(cmd_table[2].name);
    cmd_table[2].function = &alarmHandler;
}

/*
 * Initializes the command string to be full of null terminators
 * Initializes the command index to be zero
 *
 * @param: 	None
 * @return: None
 */
void initCommandString(void)
{
	unsigned int i;
	for (i = 0; i < cmd_index; i++)
		cmd_rx[i] = '\0';

	cmd_index = 0;
}

/*
 * Checks what type of character was last received by the UART and handles it
 * accordingly based on the three supported cases: Backspace, Enter, Other.
 *
 * @param data:	The last character received
 * @returns:	1 if character is to be echoed, 0 otherwise
 */
int checkChar(char data)
{
    switch(data)
    {
    	/*	when the backspace key is pressed remove the last character from
    	 * 	the command string if there are any to remove
    	 */
		case (KEY_BKSPC):
			if(cmd_index <= 0)
				return FALSE;
			UART0_TXChar(data);
			cmd_rx[--cmd_index] = 0;
			break;

		/* 	when the enter key is pressed the user has finished entering their
		 * 	command and thus command-parsing can begin
		 */
		case (KEY_ENTER):
			UART0_TXChar(data);
			parseCommand();
			break;

		/*	non-special character received, add it to the command string if
		 * 	there's room
		 */
		default:
			if(cmd_index > MAX_CMD_LEN)		// avoid overruns
				return FALSE;
			UART0_TXChar(data);
			cmd_rx[cmd_index++] = toupper(data);
    }

    return TRUE;
}

/*
 * This function breaks the user input command string into command and argument
 * strings. If the entered command matches with one of the commands in the
 * global table the handler function for that command is called.
 *
 * @param: 		None
 * @returns:	None
 */
void parseCommand(void)
{
	char *command, *argument;
	unsigned int i = 0, command_found = FALSE, handler_success = FALSE;

	/* split command string into command and argument. Argument can be NULL */
	command = strtok(cmd_rx, " ");
	argument = strtok(NULL, " ");

	/* compare first token (command) with entries in command table */
	for(i = 0; i < NUM_CMDS; i++)
	{
		if(!strncmp(command, cmd_table[i].name, cmd_table[i].length))
		{	/* confirm string length */
			if(strlen(command) != cmd_table[i].length)
			{
				command_found = FALSE;
				break;
			}

			/* if a match is found execute the corresponding function */
			handler_success = cmd_table[i].function(argument);
			command_found = TRUE;
			break;
		}
	}

	/* check for successful command and argument parsing */
	if(!(command_found && handler_success))
		UART0_TXStr("?");

	/* reset command string and print new line */
	initCommandString();
	UART0_TXStr("\n> ");
}
