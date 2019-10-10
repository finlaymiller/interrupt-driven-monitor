/*
 * date.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#ifndef DATE_H_
#define DATE_H_

/* required custom file links */
#include "command.h"
#include "my_atoi.h"
#include "queue.h"

/* define date properties */
#define MONTH_LEN 3			// month names are stored in 3 character strings
#define NUM_DATE_ELEMS 3
#define NUM_MONTHS 12

/* leap year macro */
#define IS_LEAP_YEAR(year) ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))

/* date struct setup */
typedef struct date_struct
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
} date_struct;

/* function definitions */
void dateInit(void);
int dateHandler(char *);
int dateCheck(int, char *, int);
static int dateSet(char **);
void dateIncrement(void);
static void datePrint(void);
int getNumDigit(int *, int *);

#endif /* DATE_H_ */
