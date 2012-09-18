
#ifndef STACK_H
#define STACK_H
#include "stdafx.h"
#include "List.h"
class Stack: public List
{
public:
/* This function adds a value to the top of a stack
PRE: the value being added is a node or and inherited class of node
POST: header now points to the new entry
 *************************************************************************/
	void push (Node *);


/* This function deletes the top of a stack
PRE: NONE
POST: header now points to the next entry
 *************************************************************************/
	Node * pop ();


/* This function returns the top entry in the stack with out effecting it
PRE: NONE
POST: NONE
 *************************************************************************/
	Node * top ();
};

#endif