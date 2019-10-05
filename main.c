/*
 * main.c
 *
 *  Created on:	Sep 19, 2019
 * Modified on:	Oct  5, 2019
 *      Author:	Finlay Miller
 *
 *  Monitor mainline. Initializes UART0 for transmission, SysTick for timing,
 *  and the various required tables, queues, and structs. Supported commands
 *  are case-insensitive and listed as follows:
 *
 *  	TIME [HH:MM:SS.T]	|	Prints the current time if no argument is
 *  	provided. If an argument is provided in the supported format the system
 *  	time is set to that value. Negative numbers are not supported and will
 *  	result in undefined behavior. Numbers larger than their conventional
 *  	maximums will be correctly rolled-over into the next time unit and it
 *  	is not necessary to type the leading zeroes.
 *  	e.g.	<time 0:120:0.0>	will set the time to 02:00:00.0
 *
 *
 */

#include "main.h"

/* global flag that is set when a character is received */
extern volatile int got_data;

void main(void)
{
    /* initialize UART */
    UART0_Init();

    /* initialize tables */
    initCommandTable();
    initCommandString();
    initQTable(NUM_Q);

    /* initialize time and date */
    timeInit();
    dateInit();

    /* initialize SysTick */
    SysTickInit();

    /* print startup message */
    UART0_TXStr("\n------ REBOOT ------");
    UART0_TXStr("\n> ");

    while(1)
    {
    	/* idle until data is received from SYSTICK or UART_RX */
    	got_data = FALSE;
    	while(!got_data);

    	/* check their queues and handle the received character */
    	if(!isQEmpty(SYSTICK))
			handleQ(SYSTICK);
    	if(!isQEmpty(UART_RX))
    		handleQ(UART_RX);
    }
}
