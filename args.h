/*
 * args.h
 *
 *  Created on: Sep 21, 2019
 *      Author: Finlay Miller
 */

#ifndef ARGS_H_
#define ARGS_H_

#include <stdio.h>
#include <string.h>
#include "buffer.h"

#define NUM_ARGS 3
#define MAX_ARG_LEN 20
#define MAX_NAME_LEN 6

/* Globals */
typedef struct arg
{
    char name[MAX_NAME_LEN];
    int length;
    /*int (*function)(char *arg);*/
} arg_struct;

extern arg_struct arg_table[NUM_ARGS];

#endif /* ARGS_H_ */
