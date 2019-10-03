#include "time.h"

static time_struct time;

void timeHandler(char *arg)
{
	// four parts to time: hour, minute, second, tenth
	char *time_to_set[4] = {0};
	int i = 0;

    if(arg)
    {
        //TODO: update SysTick
        // isolate time components
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

	tptr->hour = 0;
	tptr->minute = 0;
	tptr->second = 0;
	tptr->tenth = 0;
}

void timeSet(char *time_str[NUM_TIME_ELEMS])
{
	// TODO: catch wrong array length
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
	char hour[3];
	char minute[3];
	char second[3];
	char tenth[3];

	itoa(tptr->hour, hour, 10);
	itoa(tptr->minute, minute, 10);
	itoa(tptr->second, second, 10);
	itoa(tptr->tenth, tenth, 10);

	stringTX((char *) KEY_ENTER);
	stringTX(hour);
	stringTX(":");
	stringTX(minute);
	stringTX(":");
	stringTX(second);
	stringTX(".");
	stringTX(tenth);

//	enQ(UART_TX, KEY_ENTER);
//	enQ(UART_TX, (tptr->hour / 10) + '0');
//	enQ(UART_TX, (tptr->hour % 10) + '0');
//	enQ(UART_TX, ':');
//	enQ(UART_TX, (tptr->minute / 10) + '0');
//	enQ(UART_TX, (tptr->minute % 10) + '0');
//	enQ(UART_TX, ':');
//	enQ(UART_TX, (tptr->second / 10) + '0');
//	enQ(UART_TX, (tptr->second % 10) + '0');
//	enQ(UART_TX, '.');
//	enQ(UART_TX, (tptr->tenth % 10) + '0');
}
