/***********************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 3
 * Name:   prog3.c
 * Author: Joe Wingbermuehle
 * Date:   2002-09-20
 * Description:
 * This is a program to demonstrate using the following functions:
 * fork, system, execl, getpid, getppid, wait, sleep, and ps.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int childPid;

	printf("Parent: My PID is %d.\n", (int)getpid());
	printf("Parent: My parent's PID is %d.\n", (int)getppid()); 

	/* Fork a child process */
	childPid = fork();
	if(!childPid) {

		/* Child process */

		printf("Child: I am a new-born process!\n");
		printf("Child: My PID is %d.\n", (int)getpid());
		printf("Child: My parent's PID is %d.\n", (int)getppid());

		sleep(5);

		printf("Child: I am going to execute program prog3b.\n");

		execl("prog3b", "arg0", "arg1", "arg2", 0);

		printf("Child: execl failed.\n");

		_exit(0);
	}
	if(childPid < 0) {
		printf("Fork failed.\n");
		return 0;
	}

	printf("Parent: I created a child process.\n");
	printf("Parent: My child's PID is %d.\n", childPid);

	system("ps -al");

	wait(0);
	printf("Parent: My child is dead. I am going to leave.\n");

	return 0;
}

