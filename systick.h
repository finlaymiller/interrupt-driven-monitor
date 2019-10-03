/*
 * systick.h
 *
 *  Created on: Oct 2, 2019
 *      Author: finlay
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "uart.h"

typedef struct systick_struct
{
	int ticks;				// times ticked since last reset
	int cmp_val;			// number of ticks to run for
	int countdown_enable;	// T/F whether or not the alarm is running
} systick_struct;

// SysTick Registers
// SysTick Control and Status Register (STCTRL)
#define ST_CTRL_R   (*((volatile unsigned long *)0xE000E010))
// Systick Reload Value Register (STRELOAD)
#define ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))

// SysTick defines
#define ST_CTRL_COUNT   	0x00010000  // Count Flag for STCTRL
#define ST_CTRL_CLK_SRC		0x00000004  // Clock Source for STCTRL
#define ST_CTRL_INTEN   	0x00000002  // Interrupt Enable for STCTRL
#define ST_CTRL_ENABLE  	0x00000001  // Enable for STCTRL

// Maximum period
#define MAX_WAIT        	0x1000000   // 2^24
#define CLK_PERIOD			0x186A00	// 16 000 000
/* Global to signal SysTick interrupt */
//volatile int elapsed;
// global variable to count number of interrupts on PORTF0 (falling edge)
//volatile int count = 0;

// Function Declarations
void SysTickStart(void);
void SysTickStop(void);
void SysTickPeriod(unsigned long);
void SysTickIntEnable(void);
void SysTickIntDisable(void);
void SysTickHandler(void);
void SysTickInit(void);

#endif /* SYSTICK_H_ */
