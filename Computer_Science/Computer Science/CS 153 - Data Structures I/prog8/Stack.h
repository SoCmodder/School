//Filename: Bag.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #8
//This program will convert a mathmatical infix expression to postfix form. 
//It was also evaluate the answer. 

#ifndef STACK_H
#define STACK_H

#include "StdAfx.h"
#include "bag.h"
#include "DNode.h"

class Stack: private CBag
{
public:
    Stack() {};
    ~Stack() {};
    void Push(CString input)
    {
        DNode * temp;
        temp = new DNode;
        temp ->cs_val = input;
        InsertHead(temp);
    };
    CString Pop()
    {
        return(RemoveHead());
    };
    CString Top()
    {
        return(GetHead());
    };
    CBag::isEmpty;
    CBag::isFull;
};

#endif