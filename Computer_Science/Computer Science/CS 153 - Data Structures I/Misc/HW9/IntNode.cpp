#include "stdafx.h"
#include "IntNode.h"



IntNode::IntNode ()
{
	num = 0;
}

IntNode::IntNode (int temp)
{
	num = temp;
}

bool IntNode::operator== (Node &arg)
{
	IntNode * temp = (IntNode *) &arg;
	
	if (temp->num == num)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}