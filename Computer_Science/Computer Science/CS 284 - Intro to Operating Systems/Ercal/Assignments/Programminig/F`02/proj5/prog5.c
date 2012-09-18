/****************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 5
 * Name:   prog5.c
 * Author: Joe Wingbermuehle
 * Date:   2002-10-09
 * Description:
 * This is a program to demonstrate using threads in Solaris.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <thread.h>

/* Number of threads to create */
const int NUM_THREADS = 20;

void *Foo(void *data);	/* Thread function */

/****************************************************************************
 * Main function.
 * Start the threads and wait for them to end.
 ****************************************************************************/
int main() {

	long *delay;
	thread_t *threads;
	thread_t depart;
	void **status;
	int x;

	signal(SIGALRM, SIG_IGN);		/* Ignore alarm signals */

	srand48(time(0));		/* Seed the random number generator */

	delay = (long*)malloc(NUM_THREADS * sizeof(long));
	threads = (thread_t*)malloc(NUM_THREADS * sizeof(thread_t));

	printf("main(): I will create %02d threads.\n", NUM_THREADS);

	/* Create the threads */
	for(x = 0; x < NUM_THREADS; x++) {
		delay[x] = (lrand48() % 3000000) + 1;
		thr_create(NULL, NULL, Foo, &delay[x], 0, &threads[x]);
	} 

	/* Wait for all the threads to exit */
	for(x = 0; x < NUM_THREADS; x++) {
		if(!thr_join(0, &depart, status)) {
			printf("main(): joined with thread %02d. Return value: %ld\n",
				depart, *((long*)*status));
		} else {
			printf("main(): error waiting for join\n");
		}
	}

	free(delay);
	free(threads);

	return 0;
}

/****************************************************************************
 * Thread function.
 * Announce the thread number and the delay and then sleep before exiting.
 * Input: data is a pointer to a long, which is the delay in microseconds.
 * Output: returns the delay.
 ****************************************************************************/
void *Foo(void *data) {
	long delay = *((long*)data);
	printf("THREAD %02d: I have been created. I will sleep for %ld us.\n",
		thr_self(), delay);
	usleep(delay);
	thr_exit(data);
}

