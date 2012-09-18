/****************************************************************************
 * CS 284 Operation Systems
 * Programming Assignment 4
 * Name:   prog4.c
 * Author: Joe Wingbermuehle
 * Date:   2002-09-30
 * Description:
 * This is a program to demonstrate using the following functions:
 * signal and kill
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* Number of times left to run the associated signal handlers */
static int intCount, quitCount;

void InterruptHandler(int n);		/* Handler for SIGINT */
void QuitHandler(int n);			/* Handler for SIGQUIT */

/****************************************************************************
 * Main function
 * argv[1] = Number of times to intercept SIGINT
 * argv[2] = Number of times to intercept SIGQUIT
 ****************************************************************************/
int main(int argc, char *argv[]) {

	if(argc != 3) {
		printf("usage: %s <SIGINT #> <SIGQUIT #>\n", argv[0]);
		exit(0);
	}

	intCount = atoi(argv[1]);
	quitCount = atoi(argv[2]);

	if(intCount < 0 || quitCount < 0) {
		exit(0);
	}

	if(intCount) {
		signal(SIGINT, InterruptHandler);
		kill(getpid(), SIGINT);
	} else if(quitCount) {
		signal(SIGQUIT, QuitHandler);
	}

	for(;;) {
		sleep(1);
	}

	return 0;
}

/****************************************************************************
 * Signal handler for SIGINT
 ****************************************************************************/
void InterruptHandler(int n) {
	if(intCount) {
		signal(SIGINT, InterruptHandler);
		if(intCount == 1) {
			printf("You have 1 chance");
		} else {
			printf("You have %d chances", intCount);
		}
		printf(" to press Ctrl-C before printing the date.\n");
		--intCount;
		printf("I am waiting for your interrupt signal.\n");
	} else {
		--quitCount;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, QuitHandler);
		printf("Next time you press Ctrl-\\, we will run the second\n"
			"handler which will print the date.\n");
	}
}
/****************************************************************************
 * Signal handler for SIGQUIT
 ****************************************************************************/
void QuitHandler(int n) {
	system("date");
	if(quitCount) {
		signal(SIGQUIT, QuitHandler);
		if(quitCount == 1) {
			printf("You have 1 chance");
		} else {
			printf("You have %d chances", quitCount);
		}
		printf(" to print date by pressing Ctrl-\\ w/o termination.\n");
		--quitCount;
	} else {
		signal(SIGQUIT, SIG_DFL);
		printf("Press Ctrl-\\ to terminate me.\n");
	}
}

