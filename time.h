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

#include "command.h"

#define NUM_TIME_ELEMS 4

typedef struct time_struct
{
	int hour;
    int minute;
    int second;
    int tenth;
} time_struct;

void timeHandler(char *);
void timeInit(void);
void timeSet(char *time_str[NUM_TIME_ELEMS]);
void timeInc(void);
void timeIncrement(void);
void timePrint(int);

#endif /* TIME_H_ */
