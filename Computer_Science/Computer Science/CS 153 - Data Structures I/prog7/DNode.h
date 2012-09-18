#ifndef DNODE_H
//Filename: Bag.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #7
//This program will insert, find, get, and remove CStrings from a doubly linked list.  
//Also it will tell if the list is empty or full.

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
