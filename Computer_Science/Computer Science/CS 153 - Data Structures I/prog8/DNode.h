#ifndef DNODE_H
//Filename: DNode.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #8
//This program will convert a mathmatical infix expression to postfix form. 
//It was also evaluate the answer. 


#define DNODE_H
#include "StdAfx.h"
#include "Bag.h"

class DNode:public Node
{
public:
    CString cs_val;
    
   bool operator==(Node& RHS)
    {
        if(cs_val==((DNode*)&RHS)->cs_val)
        {
            return(TRUE);
        }
        else
        {
            return(FALSE);
        }
    };
    
    bool operator<(Node& RHS)
    {
        if(cs_val<((DNode*)&RHS)->cs_val)
        {
            return(TRUE);
        }
        else
        {
            return(FALSE);
        }
    };
    
    bool operator>(Node& RHS)
    {
        if(cs_val>((DNode*)&RHS)->cs_val)
        {
            return(TRUE);
        }
        else
        {
            return(FALSE);
        }
    };
    
    void operator=(Node& RHS)
    {
        cs_val=((DNode*)&RHS)->cs_val;
    };

    
    DNode()
    {
        cs_val = " ";
    };

};
#endif
