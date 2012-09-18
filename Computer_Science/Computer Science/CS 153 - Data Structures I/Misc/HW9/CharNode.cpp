#include "stdafx.h"
#include "CharNode.h"



CharNode::CharNode ()
{
	oper = NULL;
}

CharNode::CharNode (char * temp)
{
	oper = temp;
}

bool CharNode::operator== (Node &arg)
{
	CharNode * temp = (CharNode *) &arg;
	CString temp2 = temp -> oper;
	if (!strcmp(temp2,oper))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}