/****************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 6
 * Name:   prog6.c
 * Author: Matt Walters and Joe Wingbermuehle
 * Date:   2002-10-24
 * Description:
 * Bounded Buffer Problem
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <thread.h>
#include <synch.h>

const int NUMBER_PRODUCERS = 5;
const int NUMBER_CONSUMERS = 2;
const int BUFFER_SIZE = 10;
const int NUMBER_PRODUCTS = 50;

int prod_count = 0, cons_count = 0;		/* Widgets produced/consumed */
int *buffer;									/* Widget buffer */
int buffer_insert = 0, buffer_remove = 0;	/* Insert/remove points in the buffer */
int buffer_used = 0;							/* Count of items in the buffer */

/* Mutexes */
mutex_t mutex_prod, mutex_cons, mutex_buffer;

/* Conditions */
cond_t cond_not_full, cond_not_empty;

typedef enum {PRODUCER, CONSUMER} ThreadType;

typedef struct {
	thread_t id;
	int num;
	ThreadType type;
} SPC;

void *Producer(void *arg);
void *Consumer(void *arg);

/****************************************************************************
 * Main function
 ****************************************************************************/
int main() {

	thread_t *producers;
	thread_t *consumers;
	thread_t tid;
	int *prod_ids;
	int *cons_ids;
	SPC *status;
	int x;

	signal(SIGALRM, SIG_IGN);

	producers = (thread_t*)malloc(sizeof(thread_t) * NUMBER_PRODUCERS);
	consumers = (thread_t*)malloc(sizeof(thread_t) * NUMBER_CONSUMERS);
	prod_ids = (int*)malloc(sizeof(int) * NUMBER_PRODUCERS);
	cons_ids = (int*)malloc(sizeof(int) * NUMBER_CONSUMERS);
	buffer = (int*)malloc(sizeof(int) * BUFFER_SIZE);

	/* Create the producer threads */
	for(x = 0; x < NUMBER_PRODUCERS; x++) {
		prod_ids[x] = x + 1;
		thr_create(NULL, NULL, Producer, &prod_ids[x], 0, &producers[x]);
	}

	/* Create the consumer threads */
	for(x = 0; x < NUMBER_CONSUMERS; x++) {
		cons_ids[x] = x + 1;
		thr_create(NULL, NULL, Consumer, &cons_ids[x], 0, &consumers[x]);
	}

	/* Wait for the threads to finish */
	for(x = 0; x < NUMBER_PRODUCERS + NUMBER_CONSUMERS; x++) {
		thr_join(0, &tid, (void**)&status);
		if(status->type == PRODUCER) {
			printf("main(): PRODUCER-%d joined. %d widgets created.\n",
				status->id, status->num);
		} else {
			printf("main(): CONSUMER-%d joined. %d widgets consumed.\n",
				status->id, status->num);
		}
	}

	free(producers);
	free(consumers);
	free(prod_ids);
	free(cons_ids);
	free(buffer);

	return 0;
}

/****************************************************************************
 * Producer Thread: Produce a widget
 ****************************************************************************/
void *Producer(void *arg) {
	SPC prod;
	int myNumber;

	prod.id = *((int*)arg);
	prod.num = 0;
	prod.type = PRODUCER;
	srand48((long)time(0));

	for(;;) {

		/* Lock producers and check if there are more widgets to produce */
		mutex_lock(&mutex_prod);
		if(prod_count >= NUMBER_PRODUCTS) {
			mutex_unlock(&mutex_prod);
			thr_exit(&prod);
		}
		myNumber = prod_count;
		++prod_count;
		mutex_unlock(&mutex_prod);

		sleep(lrand48() % 5 + 1);

		/* Lock the buffer and produce a widget */
		mutex_lock(&mutex_buffer);
		if(buffer_used >= BUFFER_SIZE) {
			printf("PRODUCER-%d: Buffer full, waiting.\n", prod.id);
			cond_wait(&cond_not_full, &mutex_buffer);
		}

		printf("PRODUCER-%d: I will produce widget %d.\n",
			prod.id, myNumber);

		buffer[buffer_insert] = myNumber;
		buffer_insert = (buffer_insert + 1) % BUFFER_SIZE;
		++buffer_used;
		cond_signal(&cond_not_empty);
		mutex_unlock(&mutex_buffer);

		++prod.num;
	}
}

/****************************************************************************
 * Consumer Thread: Consume a widget
 ****************************************************************************/
void *Consumer(void *arg) {
	SPC cons;
	int widget;
 
	cons.id = *((int*)arg);
	cons.num = 0;
	cons.type = CONSUMER;
	srand48((long)time(0));

	for(;;) {

		/* Lock consumer count and check if there are more widgets to consume */
		mutex_lock(&mutex_cons);
		if(cons_count >= NUMBER_PRODUCTS) {
			mutex_unlock(&mutex_cons);	
			thr_exit(&cons);
		}
		++cons.num;
		++cons_count;
		mutex_unlock(&mutex_cons);

		usleep((lrand48() % 7 + 1) * 100000);

		/* Lock the buffer and consume a widget */
		mutex_lock(&mutex_buffer);
		if(!buffer_used) {
			printf(" CONSUMER-%d: Buffer empty, waiting.\n", cons.id);
			cond_wait(&cond_not_empty, &mutex_buffer);
		}
		widget = buffer[buffer_remove];
		buffer_remove = (buffer_remove + 1) % BUFFER_SIZE;
		--buffer_used;
		cond_signal(&cond_not_full);

		printf(" CONSUMER-%d: I consumed widget %d.\n", cons.id, widget);
		mutex_unlock(&mutex_buffer);

	}
}

