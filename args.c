/*
 * args.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Finlay Miller
 *
 *  TODO Handle special chars on input e.g. RETURN
 */

#include "args.h"

char cmd_rx[MAX_CMD_LEN];
int cmd_index = 0;

void alarmHandler(char *arg);
void dateHandler(char *arg);
void timeHandler(char *arg);

arg_struct arg_table[NUM_ARGS];

void initCommandTable(void)
{
    strcpy(arg_table[0].name, "date");
    arg_table[0].length = 4;
    arg_table[0].function = &dateHandler;

    strcpy(arg_table[1].name, "time");
    arg_table[1].length = 4;
    arg_table[1].function = &timeHandler;

    strcpy(arg_table[2].name, "alarm");
    arg_table[2].length = 5;
    arg_table[2].function = &alarmHandler;
}

void initCommandString(void)
{
	int i;
	for (i = 0; i < cmd_index; i++)
	{
		cmd_rx[i] = 0;
	}

	cmd_index = 0;
}

void echoRX(char data)
{
    //if(data != KEY_EXIT)
        UART_Echo(data);
}

void pollQ(int q_index)
{
    //if(!isQEmpty(q_index))
        handleRX(q_index);
}

void handleRX(int q_index)
{
    char data = deQ(UART_RX);
    checkChar(data);
    echoRX(data);

}

/*
 * IF char == backspace
 *      IF len(current_command) > 0
 *          current_command_index --
 *          current_command[current_command_index] = 0
 *      END IF
 *  ELSE IF char == enter
 *  	send newline char to UART
 *  	parse command
 *  ELSE
 *  	currend_command[current_command_index++] = char
 */
void checkChar(char data)
{
    if((data == KEY_BKSPC) && (cmd_index > 0))
    {
    	cmd_rx[--cmd_index] = 0;
    }
    else if(data == KEY_ENTER)
    {
    	parseCommand();
    }
    else if (cmd_index < MAX_CMD_LEN)
    {
    	cmd_rx[cmd_index++] = tolower(data);
    }
    else printf("How did I get here?");
}

void parseCommand(void)
{
	char **command_tokens = strToArray(cmd_rx, " ", 2);
	int i;

	for(i = 0; i < NUM_ARGS; i++)
	{
		if(!strncmp(command_tokens[0], arg_table[i].name, arg_table[i].length))
		{
			arg_table[i].function(command_tokens[1]);
			break;
		}
	}

	initCommandString();
}


/* Command Handlers */

void dateHandler(char *arg)
{
    if(arg == NULL)
    {
        // TODO: print current date
    }
    else
    {
        //TODO: update SysTick
        // isolate date components
        char **date_to_set = strToArray(arg, "-", NUM_DATE_ELEMS);

        // setup date structure
        date_ptr d_ptr = dateInit();
        dateSet(d_ptr, date_to_set);
        datePrint(d_ptr);
    }
}

void timeHandler(char *arg)
{
    if(arg == NULL)
    {
        // TODO: print current time
    }
    else
    {
        //TODO: update SysTick
        // isolate time components
        char **time_to_set = strToArray(arg, ":.", NUM_TIME_ELEMS);

        // setup time structure
        time_ptr t_ptr = timeInit();
        timeSet(t_ptr, time_to_set);
        timePrint(t_ptr);
    }
}

void alarmHandler(char *arg)
{

}

/* Derek's Functions */
void fill_tx_queue(char *message, char length)
{
    char i;
    /* Fill the transmit queue with all but last character */
    for(i=0; i<length; i++){
        enQ(UART_TX, message[i]);
    }

    if(!get_tx_queue_busy()){
        /* If UART not busy, force character into UART and set to busy */
        UART_force_start();
    }
}
