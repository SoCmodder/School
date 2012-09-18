//Filename: Bag.cpp
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #5
//This program will insert, find, get, and remove integers from a doubly linked list.  
//Also it will tell if the list is empty or full.

#include "stdafx.h"
#include "bag.h"
#include <assert.h>


CBag::CBag()
{
    test = false;
    head = NULL;
    tail = NULL;
    current = NULL;
}

bool CBag::InsertHead(int input)
{
    if(head && tail) //Does this if it is not the first integer to be placed in the bag.
    {
        Node * temp = NULL;
        temp = head;
        head = NULL;
        head = new Node;
        head -> data = input;
        head -> prev = NULL;
        head -> next = temp;
        temp -> prev = head;
        current = head;
        return(true);
    }
    else //Does this if it is the first integer to be placed in the bag.
    {
        head = new Node;
        head -> data = input;
        tail = head;
        current = head;
    }
    return (!isFull());
}

bool CBag::InsertTail(int input)
{
    if(head && tail) //Does this if it is not the first integer to be placed in the bag.
    {
        Node * temp;
        temp = tail;
        tail = NULL;
        tail = new Node;
        tail -> data = input;
        tail -> prev = temp;
        temp ->next = tail;
        tail -> next = NULL;
        current = tail;
    }
    else //Does this if it is the first integer to be placed in the bag.
    {
        head = new Node;
        head -> data = input;
        tail = head;
        current = head;
    }
    return (!isFull());
}

void CBag::reset()
{
    current = NULL;
}

bool CBag::EOC()
{
    return (current == tail);
}

int CBag::RemoveHead()
{
    if (head && (head != tail)) //Does this if there is more than 1 number in bag
    {
        int iTemp;
        Node * temp;
        temp = head;
        current = NULL;
        head = head -> next;
        head -> prev = NULL;
        iTemp= temp -> data;
        delete temp;
        return iTemp;
    }
    else if (head && (head == tail)) //Does this if there is 1 number in bag
    {
        int iTemp;
        iTemp = head -> data;
        delete head; 
        head = tail = current = NULL;
        return iTemp;
    }
    else 
    {
        return 0;
    }
}

int CBag::RemoveTail()
{
    if (tail && (tail != head)) //Does this if there is more than 1 number in bag
    {
        int iTemp;
        Node * temp;
        current = NULL;
        temp = tail;
        tail = tail -> prev;
        tail -> next = NULL;
        iTemp = temp -> data;
        delete temp;
        return iTemp;
    }
    else if (tail && (tail == head)) //Does this if there is 1 number in bag
    {
        int iTemp;
        iTemp = tail -> data;
        delete tail;
        head = tail = current = NULL;
        return iTemp;
    }
    else 
        return 0;
}

bool CBag::Find(int input)
{
    current = head;
    while (current && current -> data != input)
    {
        current = current -> next;
    }
    return (current != NULL);
}

bool CBag::isEmpty()
{
    return(head==NULL);
}


bool CBag::isFull()
{
    Node * temp;
    temp=new Node;
    delete temp;
    return(temp==NULL);
}

int CBag::GetHead()
{
    if(head != NULL)
    {
        current = head;
        return head -> data;
    }
    else
        return 0;
}

int CBag::GetTail()
{
    if(tail != NULL)
    {   
        current = tail;
        return tail -> data;
    }
    else
        return 0;
}

int CBag::GetNext()
{
    if (head)
    {
        if (current == NULL)
        {
            current = head;
            return head -> data;
        }
        else
        {
            if (current -> next != NULL)
                current = current -> next;
            return current -> data;
        }
    }
    else
        return 0;
}

CBag::~CBag()
{
    while(head)
    {
        RemoveHead();   //Calls the remove function to remove each element 
    }                           //from the linked list. 
}
