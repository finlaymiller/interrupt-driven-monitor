/*
 * alarm.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "time.h"
#include "date.h"
#include "systick.h"

#define NUM_TIME_ELEMS 4

#define HOURS_TO_TICKS(hours) 		(hours * 36000)
#define MINUTES_TO_TICKS(minutes) 	(minutes * 600)
#define SECONDS_TO_TICKS(seconds) 	(seconds * 10)

void alarmHandler(char *);
void alarmSet(char *alarm_str[NUM_TIME_ELEMS]);
void alarmClear(void);
int timeToTicks(char *time_str[NUM_TIME_ELEMS]);

#endif /* ALARM_H_ */
