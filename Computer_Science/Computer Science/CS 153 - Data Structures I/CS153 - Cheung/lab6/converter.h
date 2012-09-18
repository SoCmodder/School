/*
File: converter.h
Author: Brent Powers
Description: Header file for stack class
Date:3-10-05
*/
#ifndef CONVERTER_H
#define CONVERTER_H

class stack
{
public:
	stack();//constructor
	~stack();//destructor
	char pop();//pops the top of the array off 
	void push(char input);//adds a value to the top of the array
	char top();//returns what is on the top of the array
	void empty();//resets the array
private:
	int capacity1;//size of the array
	int count1;//how many spots in the array are used
	char *stack1;//array
	
};



#endif

