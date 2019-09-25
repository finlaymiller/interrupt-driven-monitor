/*
 * queue->c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#include <queue.h>

/*
char tx_busy;

void set_tx_queue_busy(char busy)
{
    tx_busy = busy;
}

char get_tx_queue_busy(void)
{
    return tx_busy;
}
*/

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

	if(!isQFull(q_index))
	{
		queue->contents[queue->head] = data;
		queue->head = next_head;
	}
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
	printf("Printing contents of queue");

	int i;
	for(i = 0; i < MAX_Q_LEN; i++)
	{
		printf("\n\t------------\n");
		printf("%d\t%c", i, queue->contents[i]);
	}
	
	printf("\n\t------------\n");
}

/* Example usage */
/*
int main(void)
{
	int i;
	for(i = 0; i < NUM_Q; i++)
		q_table[i] = initQ();

	enQ(0, 'a');
	enQ(1, 'b');

	printQ(0);
	printQ(1);

	return 0;
}
*/
