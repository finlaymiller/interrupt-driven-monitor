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

#include "s2a.h"

#define NUM_ARGS 3
#define MAX_ARG_LEN 20
#define MAX_NAME_LEN 6
#define MONTH_LEN 3
#define NUM_DATE_ELEMS 3
#define NUM_MONTHS 12
#define TRUE 1
#define FALSE 0;

typedef struct date_struct
{
    unsigned int day;
    char month[MONTH_LEN];
    unsigned int year;
} date_struct;

typedef struct date_struct *date_ptr;

int monthCheck(char *month);
date_ptr dateInit(void);
void dateSet(date_ptr date, char **date_str);
void datePrint(date_ptr date);
int dateHandler(char *arg);

#endif /* DATE_H_ */
