/*
 * date.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#ifndef DATE_H_
#define DATE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"
#include "queue.h"

#define NUM_CMDS 3
#define MAX_ARG_LEN 20
#define MAX_NAME_LEN 6
#define MONTH_LEN 3
#define NUM_DATE_ELEMS 3
#define NUM_MONTHS 12
#define FULL_DATE_LEN 14
#define IS_LEAP_YEAR(year) ((year % 4) ? 1 : 0)

typedef struct date_struct
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
} date_struct;

void dateHandler(char *);
int dateCheck(int, char *, int);
void dateInit(void);
void dateSet(char **);
void dateIncrement(void);
void datePrint(void);
int getNumDigit(int *year, int *pos);
char *itoa(int, char*);

#endif /* DATE_H_ */
