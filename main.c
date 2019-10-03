/*
 * main.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 *
 *  TODO	Integrate SysTick (verify Hughes' provided functions)
 *  TODO	Fix loss of first char on time/date set full string echo
 *  TODO	Add time->date rollover on new day
 */

#include "main.h"

extern volatile char data_rx;
extern volatile int got_data;

void InterruptEnable(unsigned long InterruptIndex)
{
    /* Indicate to CPU which device is to interrupt */
    if(InterruptIndex < 32)
        NVIC_EN0_R = 1 << InterruptIndex;       // Enable the interrupt in the EN0 Register
    else
        NVIC_EN1_R = 1 << (InterruptIndex - 32);    // Enable the interrupt in the EN1 Register
}

void main(void)
{

    /* initialize UART */
    UART0_Init();           // Initialize UART0
    InterruptEnable(INT_VEC_UART0);       // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_RX | UART_INT_TX); // Enable Receive and Transmit interrupts
    INTERRUPT_MASTER_ENABLE();      // Enable Master (CPU) Interrupts

    /* initialize SysTick */
    //SysTickInit();

    /* initialize tables */
    initCommandTable();
    initCommandString();
    initQTable(NUM_Q);

    /* initialize time and date */
    timeInit();
    dateInit();

    stringTX(NEW_LINE);

    while(1)
    {
    	got_data = FALSE;
    	while(!got_data);	// wait until char is received
    	handleQ(UART_RX);
    }
}
