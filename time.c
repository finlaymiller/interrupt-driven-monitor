/*
 * 	time.c
 *
 *  Created on: Sep 23, 2019
 * Modified on:	Oct 09, 2019
 *      Author: Finlay Miller
 *
 *	Contains time command-related functions including set, clear, and print.
 *	More detail on the alarm function can be found in the design documents
 *	and in the program description at the beginning of main.c.
 */

#include "time.h"

/* globals */
time_struct time;


/*
 * This function is called when a time command is entered. If an argument is
 * provided in the format described in main.c and the design document the
 * system time is set to that time. If no argument is provided the current
 * time is printed
 *
 * @param	arg:	Argument provided by the user
 * @returns:		TRUE if command is executed successfully, FALSE otherwise
 */
int timeHandler(char *arg)
{
	char *token;
	int time_to_set[NUM_TIME_ELEMS] = {0};
	int number;
	unsigned int i = 0;

    if(arg)
    {	/* tokenize argument and convert to integers */
    	token = strtok(arg, ":.");
    	while(i < NUM_TIME_ELEMS)
    	{	/* check whether or not token is a number */
			if(my_atoi(token, (int *)&number))
				time_to_set[i++] = number;
			else
				return FALSE;

			token = strtok(NULL, ":.");	// get next token
    	}

        // setup time structure
        timeSet(time_to_set);
    }

    timePrint();

    return TRUE;
}

/*
 * Initialize all time struct components to zero
 *
 * @param:		None
 * @returns: 	None
 */
void timeInit(void)
{
	time_struct *tptr = &time;

	tptr->hour 		= 0;
	tptr->minute 	= 0;
	tptr->second 	= 0;
	tptr->tenth 	= 0;
}

/*
 * Set system time to given values
 *
 * @param	time_elems: Array of times to set in order {H, M, S, T}
 * @returns:			None
 */
static void timeSet(int time_elems[NUM_TIME_ELEMS])
{
	time_struct *tptr = &time;
	// first  column contains time as an integer
	// second column contains number at which rollover occurs
	int time_num[NUM_TIME_ELEMS][2] =
	{
	    {time_elems[0], 24},	// hours
	    {time_elems[1], 60},	// minutes
	    {time_elems[2], 60},	// seconds
	    {time_elems[3], 10}		// tenths
	};
	int time_final[NUM_TIME_ELEMS] = {0};	// time adjusted for rollover
	int i, mod, rem;

	// catch too-large times by working from tenths-of-a-second up to hours
	for(i = (NUM_TIME_ELEMS - 1); i >= 0; i--)
	{
		// modulus is the rolled-over value for that unit of time
		mod = time_num[i][0] % time_num[i][1];
		// remainder is passed on to next-highest time unit
		rem = time_num[i][0] / time_num[i][1];

		time_final[i] 		 = mod;	// store final time
		time_num[i - 1][0]	+= rem;	// pass on remainder
	}

	// set times
	tptr->hour	 = time_final[0];
	tptr->minute = time_final[1];
	tptr->second = time_final[2];
	tptr->tenth	 = time_final[3];

}

/*
 * When a character is detected in the SysTick queue indicating that a tenth of
 * a second has passed, this function is called. If the hour ends up being
 * incremented past 23 then the date increment function is called.
 *
 * @param:		None
 * @returns:	None
 */
void timeIncrement(void)
{
	time_struct *tptr = &time;

	tptr->tenth++;

	if(tptr->tenth >= 10)
	{
		tptr->tenth %= 10;
		tptr->second++;
	}

	if(tptr->second >= 60)
	{
		tptr->second %= 60;
		tptr->minute++;
	}

	if(tptr->minute >= 60)
	{
		tptr->minute %= 60;
		tptr->hour++;
	}

	if(tptr->hour >= 24)
	{
		tptr->hour %= 24;
		dateIncrement();
	}
}

/*
 * This function prints the current time.
 * If you know a more efficient/practical/pretty way of doing the actual
 * time-to-string conversion for printing I would love to know how! I tried
 * many things and this was the best I could come up with.
 *
 * @param	None
 * @returns	None
 */
void timePrint(void)
{
	time_struct *tptr = &time;
	char time_string[32] = {0};
	int i = 0;

	time_string[i++] = (tptr->hour / 10) + '0';
	time_string[i++] = (tptr->hour % 10) + '0';
	time_string[i++] = ':';
	time_string[i++] = (tptr->minute / 10) + '0';
	time_string[i++] = (tptr->minute % 10) + '0';
	time_string[i++] = ':';
	time_string[i++] = (tptr->second / 10) + '0';
	time_string[i++] = (tptr->second % 10) + '0';
	time_string[i++] = '.';
	time_string[i++] = (tptr->tenth % 10) + '0';
	time_string[i++] = '\0';

	UART0_TXStr("Time is ");
	UART0_TXStr(time_string);
}

/*
 * This function takes the time stored in an array and
 * converts it to the equivalent number of tenths-of-seconds.
 *
 * @param time_to_convert: array of format {H, M, S, T}
 * @returns:	ticks: that time in seconds/10
 */
unsigned int timeToTicks(int time_to_convert[NUM_TIME_ELEMS])
{
	unsigned int ticks = 0;

	ticks 	= HOURS_TO_TICKS(time_to_convert[0])
			+ MINUTES_TO_TICKS(time_to_convert[1])
			+ SECONDS_TO_TICKS(time_to_convert[2])
			+ time_to_convert[3];

	return ticks;
}

/*
 * This function takes time in tenths-of-a-second and converts it to a a fully
 * formatted time_struct with hours, minutes, seconds, and tenths.
 *
 * @param 	ticks:	Time in seconds/10
 * @returns time:	Time in time_struct with HH:MM:SS.T
 */
time_struct ticksToTime(unsigned int ticks)
{
	time_struct time;

	time.tenth = ticks;

	time.second = time.tenth / 10;
	time.tenth %= 10;

	time.minute = time.second / 60;
	time.second %= 60;

	time.hour = time.minute / 60;
	time.minute %= 60;

	return time;
}
