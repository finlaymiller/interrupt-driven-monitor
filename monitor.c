/*
 * 	monitor.c
 *
 *  Created on:	Sep 19, 2019
 * Modified on:	Oct  5, 2019
 *      Author:	Finlay Miller
 *
 *  Monitor mainline. Initializes UART0 for transmission, SysTick for timing,
 *  and the various required tables, queues, and structs. Supported commands
 *  are case-insensitive and listed as follows with optional arguments in
 *  square brackets:
 *
 * 1	TIME [HH:MM:SS.T]	|	Prints the current time in 24 hour format if no
 *  	argument is provided. If an argument is provided in the supported
 *  	format the system time is set to that value. All numbers are
 *  	interpreted to be decimal integers. Negative numbers are not supported
 *  	and will result in undefined behavior. Numbers larger than their
 *  	conventional maximums will be correctly rolled-over into the next time
 *  	unit. It is not necessary to type the leading zeroes, however if some
 *  	numbers are not entered the numbers that ARE entered will be "rolled
 *  	up" to the next largest available unit, with hours > 24 rolling up and
 *  	increasing the day. See the fourth example below. Time is initialized
 *  	to 00:00:00.0.
 *  						HH	MM	SS	T
 *  	Max field values:	23	59	59	9
 *  	Min field values:	00	00	00	0
 *
 *  	e.g.	<time>				will print the current time
 *  	e.g.	<time 13:10:50.4>	will set the time to 13:10:50.4
 *  	e.g.	<time 01:120:0.0>	will set the time to 03:00:00.0
 *  	e.g.	<time ::5.30>		will set the time to 05:30:00.0
 *  	e.g.	<time 5:30>			will set the time to 18:15:00.0
 *
 *
 * 2	DATE [DD-MMM-YYYY]	|	Prints the current date if no argument is
 *  	provided. If an argument is provided in the supported format the system
 *  	date is set to that value. Note that day and year are to be entered as
 *  	decimal integers while month is to be entered as a three character long
 *  	string corresponding to one of the twelve strings shown below:
 *
 *  			JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC
 *
 *  	However the strings are not case-sensitive. Negative numbers are not
 *  	supported and will result in undefined behavior. Too-large numbers are
 *  	not supported and will result in an error. Leap-years are supported. It
 *  	is the responsibility of the user to know the number of days in each
 *  	month. Date is initialized to 01-JAN-0000.
 *  						DD  MMM YYYY
 *  	Max field values:	31* ZZZ 9999	*Max day value varies from 28-31
 *		Min field values	01  AAA 0000	 as is correct for the given month
 *
 *
 * 3	ALARM [HH:MM:SS.T]	|	Clears the current alarm if one is running and
 * 		no argument is provided. If an argument is provided in the supported
 *  	format the system alarm is set to that value. The number provided is a
 *  	delta value and not an absolute time. Otherwise, numbers are processed
 *  	identically to those input to the TIME command. Once the provided time
 *  	has elapsed an alarm message is printed, and a bell sounds.
 *
 *  	e.g.	<alarm>				will clear the current alarm
 *  	e.g.	<alarm 0:0:5.0>		will set an alarm 5 minutes in the future
 *
 *	Commands MUST be separated from their arguments by a space. Only the first
 *	two space-separated strings will be analyzed.
 */

#include "monitor.h"

/* global flag that is set when a character is received */
extern volatile unsigned int got_data;
Monitor monitor;

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
