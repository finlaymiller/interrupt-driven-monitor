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

#include "s2a.h"

#define NUM_TIME_ELEMS 4

typedef struct time_struct
{
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    unsigned int tenth;
} time_struct;

typedef struct time_struct *time_ptr;

time_ptr timeInit(void);
void timeSet(time_ptr time, char **time_str);
void timePrint(time_ptr time);

#endif /* TIME_H_ */
