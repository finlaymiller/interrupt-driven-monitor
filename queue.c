/*
 * queue.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#include "uart.h"
#include "queue.h"

q_struct q_table[NUM_Q];

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
}

/*
 * Handler which is called when a character is received. Pulls a char off the
 * indicated queue (SHOULD always be UART_RX), sends it to the checker
 * functions, then sends it to be echoed.
 *
 * @param: q_index:	index position in the queue table of the queue that
 * 					received the character
 * 	@returns: None
 */
void handleQ(int q_index)
{
    char data = deQ(q_index);	// dequeue char from buffer
    //if(q_index == UART_TX)
    	UART0_TXChar(data);		// echo char
    checkChar(data);			// process char
}

/*
 * Checks whether or not queue is empty.
 *
 * @param q_index: position of queue in q_table. See queue.h for which queue is
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
 * @param q_index: position of queue in q_table. See queue.h for which queue is
 * referred to by each position.
 * @param head_pos: next position the queue's head will move to
 * @return: 1 if full, 0 otherwise.
 */
int isQFull(int q_index)
{
	q_struct *queue = &q_table[q_index];
	int temp_head = NEXT_PTR(queue->head);

	return temp_head == queue->tail;
}

/*
 * Adds value to next available place in queue, if space is available.
 *
 * @param q_index: position of queue in q_table. See queue.h for which queue is
 * referred to by each position.
 * @param data: value to give to the queue.
 * @return: None
 */
void enQ(int q_index, char data)
{
	q_struct *queue = &q_table[q_index];

    // add character to queue if the queue has room for it
	if(!isQFull(q_index))
	{
		queue->contents[queue->head] = data;
		queue->head = NEXT_PTR(queue->head);
	}
}

/*
 * Removes oldest value at the tail of the queue.
 *
 * @param q_index: position of queue in q_table. See queue.h for which queue is
 * referred to by each position.
 * @return: Data from the tail of the queue.
 */
char deQ(int q_index)
{
	q_struct *queue = &q_table[q_index];
	char data = 0x00;

	if(!isQEmpty(q_index))
	{
	    data = queue->contents[queue->tail];
	    queue->tail = NEXT_PTR(queue->tail);
    }

	return data;
}

/*
 * Prints contents of queue to console.
 *
 * @param q_index: 	position of queue in q_table. See queue.h for which queue is
 * 					referred to by each position.
 * @return: None
 */
void printQ(int q_index)
{
	q_struct *queue = &q_table[q_index];

	char queue_intro_str[] 	= "\nPrinting contents of queue";
	char delim_str[] 		= "\n\t------------\n";
	int i;

	UART0_TXStr(queue_intro_str);

	for(i = 0; i < MAX_Q_LEN; i++)
	{
		UART0_TXStr(delim_str);
		enQ(UART_TX, (char)i);
		enQ(UART_TX, '\t');
		enQ(UART_TX, queue->contents[i]);
	}
	
	UART0_TXStr(delim_str);
}
