/*
 * time.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#ifndef TIME_H_
#define TIME_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "command.h"

#define NUM_TIME_ELEMS 4
#define HOURS_TO_TICKS(hours) 		(hours * 36000)
#define MINUTES_TO_TICKS(minutes) 	(minutes * 600)
#define SECONDS_TO_TICKS(seconds) 	(seconds * 10)

typedef struct time_struct
{
	int hour;
    int minute;
    int second;
    int tenth;
} time_struct;

void timeInit(void);
int timeHandler(char *);
static void timeSet(int time_str[NUM_TIME_ELEMS]);
void timeIncrement(void);
void timePrint(void);
int timeToTicks(int time_str[NUM_TIME_ELEMS]);
time_struct ticksToTime(int);

#endif /* TIME_H_ */
