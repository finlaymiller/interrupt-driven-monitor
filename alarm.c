/*
 * alarm.c
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#include "alarm.h"

extern systick_struct systick;

void alarmHandler(char *arg)
{
	// four parts to time: hour, minute, second, tenth
	systick_struct *stptr = &systick;
	char *alarm_to_set[4] = {0};
	int i = 0;

    if(arg)
    {
        // tokenize alarm components
        alarm_to_set[i] = strtok(arg, ":.");
        while(alarm_to_set[i] != NULL)
        		alarm_to_set[++i] = strtok(NULL, ":.");

        // setup time structure
        alarmSet(alarm_to_set);
    }
    else
    	if(stptr->enable)
    		alarmClear();

    timePrint(1);
}

void alarmSet(char *alarm_str[NUM_TIME_ELEMS])
{
	systick_struct *stptr = &systick;
	int time_to_run = timeToTicks(alarm_str);

	stptr->cmp_val = time_to_run;
	stptr->enable = 1;

}

void alarmClear(void)
{
	systick_struct *stptr = &systick;

	stptr->cmp_val = 0;
	stptr->enable = 0;
	UART0_TXStr("\nAlarm cleared.");
}

int timeToTicks(char *time_str[NUM_TIME_ELEMS])
{
	int time[4] = {0};
	int ticks = 0;
	int i;

	// convert time to integer
	for(i = 0; i < NUM_TIME_ELEMS; i++)
		time[i] = atoi(time_str[i]);

	ticks 	= HOURS_TO_TICKS(time[0])
			+ MINUTES_TO_TICKS(time[1])
			+ SECONDS_TO_TICKS(time[2])
			+ time[3];

	return ticks;
}
