/*
 * args.c
 *
 *  Created on: Sep 21, 2019
 *      Author: finlay
 *
 *  TODO:
 *  1. Handle special chars on input e.g. RETURN
 */

#include "args.h"

arg_struct arg_table[NUM_ARGS] =
{
 { .name = "date",  .length = 4/*, .function = dateHandler(char *)*/},
 { .name = "time",  .length = 4/*, .function = timeHandler(char *)*/},
 { .name = "alarm", .length = 5/*, .function = alarmHandler(char *)*/}
};

void readRX(buffer_ptr buff)
{
    printf("Buffer holds ");
    int i;
    for(i = 0; i < MAX_BUFFER_LEN; i++)
    {
        printf("%c", buff->contents[i]);
    }
}
