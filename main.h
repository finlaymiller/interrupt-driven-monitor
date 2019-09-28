/*
 * main.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Finlay Miller
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "args.h"
#include "date.h"
#include "queue.h"
#include "time.h"
#include "s2a.h"
#include "uart.h"

#define NUM_CMDS 3
#define MAX_ARG_LEN 20
#define MAX_NAME_LEN 6
#define MONTH_LEN 3
#define NUM_DATE_ELEMS 3

void InterruptEnable(unsigned long InterruptIndex);
void InterruptMasterEnable(void);
void InterruptMasterDisable(void);

#endif /* MAIN_H_ */
