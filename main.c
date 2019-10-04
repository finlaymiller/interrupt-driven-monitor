/*
 * main.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 *
 *  TODO	Integrate SysTick (verify Hughes' provided functions)
 *  TODO	Fix loss of first char on time/date set full string echo
 */

#include "main.h"

extern volatile char data_rx;
extern volatile int got_data;

void main(void)
{
    /* initialize UART */
    UART0_Init();           // Initialize UART0

    /* initialize tables */
    initCommandTable();
    initCommandString();
    initQTable(NUM_Q);

    /* initialize time and date */
    timeInit();
    dateInit();

    /* initialize SysTick */
    SysTickInit();

    UART0_TXStr("> ");

    while(1)
    {
    	//got_data = FALSE;
    	//while(!got_data);
    	if(!isQEmpty(UART_RX))
    		handleQ(UART_RX);
    	if(!isQEmpty(SYSTICK))
    		handleQ(SYSTICK);
    }
}
