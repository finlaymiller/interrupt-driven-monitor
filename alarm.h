/*
 * alarm.h
 *
 *  Created on: Sep 23, 2019
 * Modified on:	Oct 05, 2019
 *      Author: Finlay Miller
 *
 *	Headerfile for the alarm command-related functions.
 */

#ifndef ALARM_H_
#define ALARM_H_

/* required custom file links */
#include "command.h"
#include "time.h"
#include "date.h"
#include "monitor.h"
#include "my_atoi.h"
#include "systick.h"

/* required definitions */
#define NUM_TIME_ELEMS 	4		// hour, minute, second, and tenth
#define	BEL				'\x07'

/* function definitions */
static void alarmClear(void);
int alarmHandler(char *);
static void alarmSet(int alarm_str[NUM_TIME_ELEMS]);
void alarmCheck(void);
static void alarmPrint(void);

#endif /* ALARM_H_ */
