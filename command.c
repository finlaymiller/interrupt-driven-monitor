/*
 * command.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Finlay Miller
 *
 */

#include <command.h>

/* globals */
char cmd_rx[MAX_CMD_LEN];	// command string received from UART
int cmd_index = 0;			// number of characters in command string

cmd_struct cmd_table[NUM_CMDS];
extern volatile char data_rx;

/*
 * Creates a command table
 *
 * @param: None
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
 *
 * @param: None
 * @return: None
 */
void initCommandString(void)
{
	int i;
	for (i = 0; i < cmd_index; i++)
		cmd_rx[i] = '\x0';

	cmd_index = 0;
}


void checkChar(char data)
{
    switch(data)
    {
    case (KEY_BKSPC):
	{
    	if(cmd_index > 0)
    		cmd_rx[--cmd_index] = 0;
	} break;

    case (KEY_ENTER):
	{
		parseCommand();
	} break;

    case ('*'):
	{
    	timeIncrement();
	} break;

    default:
    {
    	cmd_rx[cmd_index++] = toupper(data);
    } break;
    }
}

void parseCommand(void)
{
	char *command_tokens[NUM_TOKS];
	int i = 0;

	command_tokens[0] = strtok(cmd_rx, " ");
	command_tokens[1] = strtok(NULL, " ");

	for(i = 0; i < NUM_CMDS; i++)
	{
		if(!strncmp(command_tokens[0], cmd_table[i].name, cmd_table[i].length))
		{
			cmd_table[i].function(command_tokens[1]);
			break;
		}
	}

	initCommandString();
	UART0_TXStr("\n> ");
}
