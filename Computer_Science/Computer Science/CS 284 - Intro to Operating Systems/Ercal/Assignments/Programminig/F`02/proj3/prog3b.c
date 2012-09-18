/***********************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 3
 * Name:   prog3b.c
 * Author: Joe Wingbermuehle
 * Date:   2002-09-20
 * Description:
 * This is a program to display the arguments sent to it.
 * It is called by prog3.c.
 ***********************************************************************/

#include <stdio.h>

int main(int argc, char *argv[]) {

	int x;

	printf("prog3b: I am executed.\n");

	for(x = 0; x < argc; x++) {
		printf("prog3b: Argument %d: %s\n", x, argv[x]);
	}

	printf("prog3b: I am going to die.\n");

	return 0;
}

