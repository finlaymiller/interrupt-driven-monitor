/*
 * main.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
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


void InterruptMasterEnable(void)
{
    /* enable CPU interrupts */
    __asm(" cpsie   i");
}

void InterruptMasterDisable(void)
{
	/* disable CPU interrupts */
	    __asm(" cpsid   i");
}


void main(void)
{

    /* Initialize UART */
    UART0_Init();           // Initialize UART0
    InterruptEnable(INT_VEC_UART0);       // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_RX | UART_INT_TX); // Enable Receive and Transmit interrupts
    InterruptMasterEnable();      // Enable Master (CPU) Interrupts

    /* initialize tables */
    initCommandTable();
    initCommandString();
    initQTable(NUM_Q);

    while(1)
    {
    	got_data = FALSE;
    	while(!got_data);	// wait until char is received
    	handleQ(UART_RX);
    	handleQ(UART_TX);
    }
}
