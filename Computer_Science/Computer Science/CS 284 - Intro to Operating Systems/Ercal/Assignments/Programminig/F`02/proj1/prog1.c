/**************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 1
 * Name:   prog1.c
 * Author: Joe Wingbermuehle
 * Date:   2002-09-04
 * Description:
 * This is a program to demonstrate using scanf and printf.
 **************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[]) {

	const int MAX_COUNT = 20;

	int i;
	char c;
	float f;
	char str[101];
	int array[MAX_COUNT];
	int count, x;

	scanf(" %d", &i);
	scanf(" %c", &c);
	scanf(" %f", &f);
	scanf(" %s", &str);

	for(count = 0;
		count < MAX_COUNT && scanf(" %d", &array[count]) == 1;
		count++);

	printf("int: %d\n", i);
	printf("char: %c\n", c);
	printf("float: %f\n", f);
	printf("string: %s\n", str);
	printf("int[%d]: ", count);
	for(x = 0; x < count; x++) {
		printf("%d ", array[x]);
	}
	printf("\n");

	return 0;

}

