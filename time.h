/*
 * time.h
 *
 *  Created on: Sep 23, 2019
 * Modified on: Oct 09, 2019
 *      Author: Finlay Miller
 */

#ifndef TIME_H_
#define TIME_H_

/* required standard libraries */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* required custom file links */
#include "command.h"

/* define time-related properties */
#define NUM_TIME_ELEMS 4	// hour, minute, second, and tenth

/* time-related macros */
#define HOURS_TO_TICKS(hours) 		(hours * 36000)
#define MINUTES_TO_TICKS(minutes) 	(minutes * 600)
#define SECONDS_TO_TICKS(seconds) 	(seconds * 10)

/* declare time struct */
typedef struct time_struct
{
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int tenth;
} time_struct;

/* function declarations */
void timeInit(void);
int timeHandler(char *);
static void timeSet(int time_str[NUM_TIME_ELEMS]);
void timeIncrement(void);
void timePrint(void);
unsigned int timeToTicks(int time_str[NUM_TIME_ELEMS]);
time_struct ticksToTime(unsigned int);

#endif /* TIME_H_ */
