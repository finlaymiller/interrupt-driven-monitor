/*
 * alarm.c
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#include "alarm.h"

extern systick_struct systick;
extern time_struct time;

void alarmHandler(char *arg)
{
	// four parts to time: hour, minute, second, tenth
	systick_struct *stptr = &systick;
	int alarm_elems[NUM_TIME_ELEMS] = {0};
	int i = 0;

    if(arg)
    {
    	alarm_elems[i] = atoi(strtok(arg, ":."));
    	while( i < NUM_TIME_ELEMS)
    			alarm_elems[++i] = atoi(strtok(NULL, ":."));

        // setup time structure
        alarmSet(alarm_elems);
    }
    else if(stptr->enable)
    {
    	alarmClear();
    }
}

void alarmSet(int alarm_arr[NUM_TIME_ELEMS])
{
	systick_struct *stptr	= &systick;

	stptr->cmp_val = timeToTicks(alarm_arr);
	stptr->enable = 1;

	alarmPrint();
}

void alarmClear(void)
{
	systick_struct *stptr = &systick;

	stptr->cmp_val = 0;
	stptr->enable = 0;
	UART0_TXStr("Alarm cleared.");
}

void alarmCheck(void)
{
	systick_struct *stptr = &systick;

	if(!(--stptr->cmp_val))
	{
		stptr->enable = 0;
		UART0_TXChar(BEL);
		UART0_TXStr("\nDING DING DING DING");	// alarms should be annoying
		UART0_TXStr("\n> ");
		initCommandString();	// need to reset command string since alarm
								// interrupts typing
	}

}

void alarmPrint(void)
{
	time_struct time_cpy = time;
	systick_struct *stptr = &systick;
	time_struct alarm = ticksToTime(stptr->cmp_val);
	char alarm_string[32] = {0};
	int i = 0;

	alarm.hour 		+= time_cpy.hour;
	alarm.minute	+= time_cpy.minute;
	alarm.second	+= time_cpy.second;
	alarm.tenth 	+= time_cpy.tenth;

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
	alarm_string[i++] = '\0';

	UART0_TXStr("Alarm is set for ");
	UART0_TXStr(alarm_string);
}
