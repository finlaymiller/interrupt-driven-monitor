/*
 * queue->c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#include "uart.h"
#include "queue.h"

q_struct q_table[NUM_Q];
int uart_tx_state;

/*
 * Initializes array of queues filled with 0s
 *
 * @param num_queues: Number of queues to fill array with
 * @return:	None
 */
void initQTable(int num_queues)
{
    int i;
    for(i = 0; i < num_queues; i++)
    {
    	int j;
    	for(j = 0; j < MAX_Q_LEN; j++)
    		q_table[i].contents[j] = 0;
    	q_table[i].head = 0;
    	q_table[i].tail = 0;
    }

    uart_tx_state = 0;
}

/*
 * Checks whether or not queue is empty.
 *
 * @param q_index: position of queue in q_table. See queue->h for which queue is
 * referred to by each position.
 * @return: 1 if empty, 0 otherwise.
 */
int isQEmpty(int q_index)
{
	q_struct *queue = &q_table[q_index];

	return queue->head == queue->tail;
}

/*
 * Checks whether or not queue is full.
 *
 * @param q_index: position of queue in q_table. See queue->h for which queue is
 * referred to by each position.
 * @param head_pos: next position the queue's head will move to
 * @return: 1 if full, 0 otherwise.
 */
int isQFull(int q_index)
{
	q_struct *queue = &q_table[q_index];
	int next_head = (queue->head + 1) & (MAX_Q_LEN - 1);

	return next_head == queue->tail;
}

/*
 * Adds value to next available place in queue, if space is available.
 *
 * @param q_index: position of queue in q_table. See queue->h for which queue is
 * referred to by each position.
 * @param data: value to give to the queue->
 * @return: None
 */
void enQ(int q_index, char data)
{
	q_struct *queue = &q_table[q_index];
    int next_head = (queue->head + 1) & (MAX_Q_LEN - 1);

    // add character to queue if the queue has room for it
	if(!isQFull(q_index))
	{
		queue->contents[queue->head] = data;
		queue->head = next_head;
	}

	if(!getTXState()) UART0_Start();
}

/*
 * Removes oldest value at the tail of the queue->
 *
 * @param q_index: position of queue in q_table. See queue->h for which queue is
 * referred to by each position.
 * @return: Data from the tail of the queue->
 */
char deQ(int q_index)
{
	q_struct *queue = &q_table[q_index];
	char data = 0;

	if(!isQEmpty(q_index))
	{
	    data = queue->contents[queue->tail];
	    queue->tail = (queue->tail + 1) & (MAX_Q_LEN - 1);
    }
	else
	{
		if(q_index == UART_TX)
			setTXState(0);
		return 0;
	}

	return data;
}

/*
 * Prints contents of queue to console. Not for onboard use.
 *
 * @param q_index: position of queue in q_table. See queue->h for which queue is
 * referred to by each position.
 * @return: None
 */
void printQ(int q_index)
{
	q_struct *queue = &q_table[q_index];

	char queue_intro_str[40] = "\nPrinting contents of queue";
	char delim_str[30] = "\n\t------------\n";
	int len_qis = sizeof(queue_intro_str) / sizeof(char);
	int len_des	= sizeof(delim_str) / sizeof(char);
	int i;

	stringTX(queue_intro_str, len_qis);

	for(i = 0; i < MAX_Q_LEN; i++)
	{
		stringTX(delim_str, len_des);
		enQ(UART_TX, (char)i);
		enQ(UART_TX, '\t');
		enQ(UART_TX, queue->contents[i]);
	}
	
	stringTX(delim_str, len_des);
}

/******************************************************************************
 * Setter and Getter methods for the state of UART transmission				  *
 *****************************************************************************/
void setTXState(int state)
{
	uart_tx_state = state;
}

int getTXState(void)
{
	return uart_tx_state;
}
