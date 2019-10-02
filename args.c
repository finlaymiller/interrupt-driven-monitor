/*
 * args.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Finlay Miller
 *
 */

#include "args.h"

/* globals */
char cmd_rx[MAX_CMD_LEN];	// command string received from UART
int cmd_index = 0;			// number of characters in command string
unsigned int DEBUG_LOC = 0;

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
    strcpy(cmd_table[0].name, "date");		// add support for accepting the
    cmd_table[0].length = 4;				// date command
    cmd_table[0].function = &dateHandler;

    strcpy(cmd_table[1].name, "time");		// add support for accepting the
    cmd_table[1].length = 4;				// time command
    cmd_table[1].function = &timeHandler;

    strcpy(cmd_table[2].name, "alarm");		// add support for accepting the
    cmd_table[2].length = 5;				// alarm command
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
		cmd_rx[i] = '\0';

	cmd_index = 0;
}

/*
 * Handler which is called when a character is received. Pulls a char off the
 * indicated queue (SHOULD always be UART_RX), sends it to the checker
 * functions, then sends it to be echoed.
 *
 * @param: q_index->index position in the queue table of the queue that
 * 					received the character
 * 	@returns: None
 */
void handleQ(int q_index)
{
    char data = deQ(q_index);	// dequeue char from buffer
    if(q_index == UART_RX)		// check char if it's just been received
    	checkChar(data);
    echo(data);					// echo it
}

void checkChar(char data)
{
    if((data == KEY_BKSPC) && (cmd_index > 0))	// delete last char
    {
    	handleBackspace();
    }
    else if(data == KEY_ENTER)					// start processing command
    {
    	parseCommand();
    }
    else if (cmd_index < MAX_CMD_LEN)
    {
    	handleChar(data);								// add char to command string
    }
    else
    {
    	// character entered when command string is at max length.
    	// backspace then add last char to end of command
    	DEBUG_LOC = 1;
    	handleBackspace();
    	handleChar(data);
    }
}

void handleBackspace(void)
{
	cmd_rx[--cmd_index] = 0;
}

void handleChar(char data)
{
	cmd_rx[cmd_index++] = tolower(data);
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
	stringTX(NEW_LINE, 3);
}

void stringTX(char *string, int len)
{
	int i;
	for(i = 0; i < len; i++)
		enQ(UART_TX, string[i]);

	if(!getTXState())
		UART0_Start();
}
