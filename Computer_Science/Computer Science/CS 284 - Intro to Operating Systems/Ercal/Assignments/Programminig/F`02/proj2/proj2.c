/**************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 2
 * Name:   prog1.c
 * Author: Joe Wingbermuehle
 * Date:   2002-09-10
 * Description:
 * This is a program to demonstrate using arguments passed to main.
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * argc is the number of arguments
 * argv is an array of arguments
 * env is an array of environment variables (null terminated)
 */
int main(int argc, char *argv[], char *env[]) {

	int x;

	for(x = 0; x < argc; x++) {
		printf("argument %d: %s", x, argv[x]);
		if(isdigit(argv[x][0])) {
			printf(" @1st character is digit: %d", atoi(argv[x]));
		}
		printf("\n");
	}

	printf("first env[] string: %s\n", env[0]);

	for(x = 0; env[x]; x++) {
		if(!strncmp(env[x], "HOSTNAME", 8)
			|| !strncmp(env[x], "USER", 4)) {
			printf("%s\n", env[x]);
		}
	}
	printf("last env[] string: %s\n", env[x - 1]);
	printf("total # of env variables: %d\n", x);

}

