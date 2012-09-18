/*
File: converter.cpp
Author: Brent Powers
Description: Function definitions for stack class
Date: 3-10-05

*/
#include "stdafx.h"
#include "converter.h"
using namespace std;

/*
Function: stack
Description: the default constructor for the stack class
PreCondition: none
PostCondition: count1 initialized to 0, capacity set to 10, and the pointer stack1 refering
to the memory location of the array
*/

stack::stack()
{
	count1=0;//count to zero
	capacity1=10;//capacity to 10
	stack1=new char[capacity1];//array set up	
}
/*
Function: ~stack
Description: Default destructor for the stack
PreCondition: stack1 points to a valid memory 
PostCondition: memory is freed up
*/
stack::~stack()
{
	delete []stack1;// memory returned to heap
	
}
/*
Function: void push(char input)
Description: puts a new char on the top of the array, agguments the array if more room is needed, increases the count of char in the array
PreCondition: valid char for the input, valid array,, good values for capacity and count
PostCondition: the array may or may not be increased in size, the inputted char will be at the top of the array and the count will be one larger

*/

void stack::push(char input)
{
	if (count1>=capacity1)//if not enough room
	{
		capacity1=capacity1+5;//more capacity
		char *stack2;
		stack2=new char[capacity1];//new stack
		for(int i=0;i<count1;i++)
		{
			stack2[i]=stack1[i];//transfers data from first array to second
		}
		delete []stack1;// removes first array
		stack1=stack2;//makes the second one the first
	}
	stack1[count1]=input;// add the value
	count1++;//up the count
}
/*
Function: char pop()
Description: returns the top most value in the array and then lessens the count
PreCondition: array in tact and count good
PostCondition: Top value is returned and the array's count is lessened by one

*/

char stack::pop()
{
	char temp;//temp value
    temp=stack1[count1-1];//transfer top value
	stack1[count1-1]=0;//delete that value in the array
	count1--;//lessen the count
	return temp;//return that top value
}
/*
Function: void empty()
Description: empties out the entire array
PreCondition: notta
PostCondition: fresh count and capacity and the stack is new too
*/
void stack::empty()
{
	count1=0;//zero count
	capacity1=10;//reset capacity
	delete []stack1;
	stack1=new char[capacity1];//good to go array
}

/*
Function: char top()
Description: returns the top value of the array with out deleteing it
PreCondition: array in tact, with a good couter number
PostCondition: the value of the top part of the array is returned

*/
char stack::top()
{
	char temp;
	temp=stack1[count1-1];//top value
	return temp;//return that bitch
}


