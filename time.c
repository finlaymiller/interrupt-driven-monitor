#include "time.h"

time_ptr timeInit(void)
{
	time_ptr time = (time_ptr)malloc(sizeof(time_struct));
	time->hour = 0;
	time->minute = 0;
	time->second = 0;
	time->tenth = 0;

	return time;
}

void timeSet(time_ptr time, char **time_str)
{
	// TODO: catch wrong array length
	int time_num[NUM_TIME_ELEMS];

	// format time
	int i;
	for(i = 0; i < NUM_TIME_ELEMS; i++)
		time_num[i] = atoi(time_str[i]);

	// catch too-large times
	if(time_num[0] >= 24)
		time_num[0] %= 24;
	else if(time_num[1] >= 60)
		time_num[1] %= 60;
	else if(time_num[2] >= 60)
		time_num[2] %= 60;
	else if(time_num[3] >= 10)
		time_num[3] %= 10;

	time->hour = time_num[0];
	time->minute = time_num[1];
	time->second = time_num[2];
	time->tenth = time_num[3];
}

void timePrint(time_ptr time)
{
	printf("\nPrinting time:\t\t");
	printf("HH:MM:SS.T ---> %02d:%02d:%02d.%d", time->hour, time->minute, time->second, time->tenth);
}
