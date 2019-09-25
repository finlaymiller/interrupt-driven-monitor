/*
 * queue.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Finlay Miller
 */

#include <queue.h>

char tx_busy;

void set_tx_queue_busy(char busy)
{
    tx_busy = busy;
}

char get_tx_queue_busy(void)
{
    return tx_busy;
}

void initQTable(int num_queues)
{
    int i;
    for(i = 0; i < num_queues; i++)
    {
    	q_table[i] = malloc(sizeof(q_ptr));
    	initQ(q_table[i]);
    }
}

void initQ(q_ptr queue)
{
	queue = malloc(sizeof(q_struct));

	/*
	int i;
	for(i = 0; i < MAX_Q_LEN; i++)
		queue->contents[i] = 0;
		*/
	queue->head = 0;
	queue->tail = 0;
}

q_ptr getQ(int q_index)
{
	return q_table[q_index];
}

void freeQ(int q_index)
{
	q_ptr queue = getQ(q_index);
	free(queue);
}

int isQEmpty(int q_index)
{
	q_ptr queue = getQ(q_index);

	return queue->head == queue->tail;
}

int isQFull(int q_index, int head_pos)
{
	q_ptr queue = getQ(q_index);

	return head_pos != queue->tail;
}

void enQ(int q_index, char data)
{
	q_ptr queue = getQ(q_index);
    int new_head = (queue->head + 1) & (MAX_Q_LEN - 1);

	if(!isQFull(q_index, new_head))
	{
		queue->contents[queue->head] = data;
		queue->head = new_head;
	}
}

char deQ(int q_index)
{
	q_ptr queue = getQ(q_index);
	char data = 0;

	if(isQEmpty(q_index) && (q_index == UART_TX))
	{
	    tx_busy = 0;
	}
	else
    {
	    data = queue->contents[queue->tail];
	    queue->tail = (queue->tail + 1) & (MAX_Q_LEN - 1);
    }

	return data;
}


void printQ(int q_index)
{
	q_ptr queue = getQ(q_index);
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
