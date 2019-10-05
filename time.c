#include "time.h"

time_struct time;

void timeHandler(char *arg)
{
	// four parts to time: hour, minute, second, tenth
	char *time_to_set[4] = {0};
	int i = 0;

    if(arg)
    {
        // tokenize time components
        time_to_set[i] = strtok(arg, ":.");
        while(time_to_set[i] != NULL)
        		time_to_set[++i] = strtok(NULL, ":.");

        // setup time structure
        timeSet(time_to_set);
    }

    timePrint();
}

void timeInit(void)
{
	time_struct *tptr = &time;

	tptr->hour 		= 0;
	tptr->minute 	= 0;
	tptr->second 	= 0;
	tptr->tenth 	= 0;
}

void timeSet(char *time_str[NUM_TIME_ELEMS])
{
	time_struct *tptr = &time;
	// first  column contains time as an int
	// second column contains number at which rollover occurs
	int time_num[NUM_TIME_ELEMS][2] =
	{
	    {0, 24},	// hours
	    {0, 60},	// minutes
	    {0, 60},	// seconds
	    {0, 10}		// tenths
	};
	int time_final[NUM_TIME_ELEMS] = {0};	// time adjusted for rollover
	int i, mod, rem;

	// convert time to integer
	for(i = 0; i < NUM_TIME_ELEMS; i++)
		time_num[i][0] = atoi(time_str[i]);

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
	tptr->hour		= time_final[0];
	tptr->minute 	= time_final[1];
	tptr->second 	= time_final[2];
	tptr->tenth		= time_final[3];
}

void timeIncrement(void)
{
	time_struct *tptr = &time;

	tptr->tenth++;

	if(tptr->tenth >= 10)
	{
		tptr->tenth = 0;
		tptr->second++;
	}

	if(tptr->second >= 60)
	{
		tptr->second = 0;
		tptr->minute++;
	}

	if(tptr->minute >= 60)
	{
		tptr->minute = 0;
		tptr->hour++;
	}

	if(tptr->hour >= 24)
	{
		tptr->hour = 0;
		dateIncrement();
	}
}

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

int timeToTicks(int time_str[NUM_TIME_ELEMS])
{
	int ticks = 0;

	ticks 	= HOURS_TO_TICKS(time_str[0])
			+ MINUTES_TO_TICKS(time_str[1])
			+ SECONDS_TO_TICKS(time_str[2])
			+ time_str[3];

	return ticks;
}

time_struct ticksToTime(int ticks)
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
