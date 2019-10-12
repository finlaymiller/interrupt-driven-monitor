/*
 * 	alarm.c
 *
 *  Created on: Sep 23, 2019
 * Modified on:	Oct 09, 2019
 *      Author: Finlay Miller
 *
 *	Contains alarm command-related functions including set, clear, print, and
 *	others. More detail on the alarm function can be found in the design docs
 *	and in the program description at the beginning of monitor.c. Note that alarm
 *	data is stored in the global SysTick struct described in systick.c
 */

#include "alarm.h"

/* global monitor struct */
extern Monitor monitor;

/*
 * This function is called when an alarm command is entered. If a time is
 * provided following the format described in main.c the alarm is set to that
 * time. If no argument is set and the alarm is currently active the alarm is
 * cleared.
 *
 * @param arg:	Argument provided by user, NULL if none is provided.
 * @returns:	TRUE if command execution was a success, FALSE otherwise
 *
 */
int alarmHandler(char *arg)
{
	//sys_tick *stptr = &systick;
	char *token;
	int alarm_to_set[NUM_TIME_ELEMS] = {0};
	int number;
	unsigned int i = 0;

    if(arg)
    {	/* tokenize argument and convert to integers */
    	token = strtok(arg, ":.");
    	while(i < NUM_TIME_ELEMS)
    	{
			/* check whether or not token is a number */
			if(my_atoi(token, (int *)&number))
				alarm_to_set[i++] = number;
			else
				return FALSE;

			token = strtok(NULL, ":.");	// get next token
    	}

    	alarmSet(alarm_to_set);
    }
    else if(monitor.systick.enabled)	// if the alarm is enabled and no arguments are
    	alarmClear();		// provided, clear the alarm
    else UART0_TXStr("No alarm to clear");

    return TRUE;
}

/*
 * Set the alarm to the provided time.
 *
 * @param alarm_arr:	Time to set the alarm to
 * @return:				None
 */
static void alarmSet(int alarm_arr[NUM_TIME_ELEMS])
{
	//sys_tick *stptr	= &systick;

	/* value to be counted-down is the user-provided time in
	 * tenths-of-a-second
	 */
	monitor.systick.cmp_val = timeToTicks(alarm_arr);
	monitor.systick.enabled = TRUE;

	alarmPrint();
}

/*
 * Clear the alarm, setting all values to 0 and disabling it.
 *
 * @param	None
 * @returns	None
 */
static void alarmClear(void)
{
	//sys_tick *stptr = &systick;

	monitor.systick.cmp_val = 0;
	monitor.systick.enabled = 0;

	UART0_TXStr("\nAlarm cleared");	// print confirmation
}

/*
 * When a character is detected in the SysTick queue indicating that a tenth of
 * a second has passed, this function is called. If the time remaining on the
 * alarm (systick->cmp_val) is zero, the alarm goes off.
 *
 * @param	None
 * @returns	None
 */
void alarmCheck(void)
{
	//sys_tick *stptr = &systick;

	if(monitor.systick.cmp_val > 0)		// underflow guard
		monitor.systick.cmp_val--;

	if((monitor.systick.cmp_val) <= 0)	// decrement the timer and see if it equals 0
	{
		monitor.systick.enabled = 0;		// disable alarm
		UART0_TXChar(BEL);		// play bell noise
		UART0_TXStr("\nDING DING DING DING");	// alarms should be annoying!
		UART0_TXChar('\n');
		timePrint();
		UART0_TXStr("\n> ");
		initCommandString();	// need to reset command string since alarm
	}							// interrupts typing
}

/*
 * This function prints the confirmation that the alarm has been set.
 * If you know a more efficient/practical/pretty way of doing the actual
 * time-to-string conversion for printing I would love to know how! I tried
 * many things and this was the best I could come up with. It's so formulaic
 * I figure there must be a better way. I run out of memory if I use sprintf.
 *
 * @param	None
 * @returns	None
 */
static void alarmPrint(void)
{
	//sys_time *tptr 		= &time;
	//sys_tick *stptr 	= &systick;
	sys_time alarm 		= ticksToTime(monitor.systick.cmp_val);
	char alarm_string[32] 	= {0};
	unsigned int i = 0;

	/* add alarm time to system time */
	alarm.hour 		+= monitor.time.hour;
	alarm.minute	+= monitor.time.minute;
	alarm.second	+= monitor.time.second;
	alarm.tenth 	+= monitor.time.tenth;

	/* convert time to string */
	alarm_string[i++] = (alarm.hour / 10) + '0';
	alarm_string[i++] = (alarm.hour % 10) + '0';
	alarm_string[i++] = ':';
	alarm_string[i++] = (alarm.minute / 10) + '0';
	alarm_string[i++] = (alarm.minute % 10) + '0';
	alarm_string[i++] = ':';
	alarm_string[i++] = (alarm.second / 10) + '0';
	alarm_string[i++] = (alarm.second % 10) + '0';
	alarm_string[i++] = '.';
	alarm_string[i++] = (alarm.tenth % 10) + '0';
	alarm_string[i]   = '\0';

	UART0_TXStr("Alarm is set for ");
	UART0_TXStr(alarm_string);
}
