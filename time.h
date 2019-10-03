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

#include "args.h"

#define NUM_TIME_ELEMS 4

typedef struct time_struct
{
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    unsigned int tenth;
} time_struct;

void timeHandler(char *);
void timeInit(void);
void timeSet(char *time_str[NUM_TIME_ELEMS]);
void timeInc(void);
void timeIncrement(void);
void timePrint(void);

#endif /* TIME_H_ */
