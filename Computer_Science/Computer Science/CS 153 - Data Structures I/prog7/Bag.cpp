//Filename: Bag.cpp
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #7
//This program will insert, find, get, and remove CStrings from a doubly linked list.  
//Also it will tell if the list is empty or full.

#include "stdafx.h"
#include "Bag.h"
#include "DNode.h"
#include <assert.h>


CBag::CBag()
{
    test = false;
    head = NULL;
    tail = NULL;
    current = NULL;
}

bool CBag::InsertHead(Node * p_input)
{
    if(head == NULL) //Does this if it is the first integer to be placed in the bag.
    {
        head = p_input;
        tail = p_input;
    }
    else //Does this if it is not the first integer to be placed in the bag.
    {
        head->prev=p_input;
        p_input->next=head;
        head=p_input;
        return(true);
    }
  
    return (!isFull());
}

bool CBag::InsertTail(Node* p_input)
{
    if(head == NULL) //Does this if it is the first integer to be placed in the bag.
    {
        head = p_input;
        tail = p_input;
    }
    else //Does this if it is not the first integer to be placed in the bag.
    {
        tail->next=p_input;
        p_input->prev=tail;
        tail=p_input;
        return(true);
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

CString CBag::RemoveHead()
{
    if (head && (head != tail)) //Does this if there is more than 1 number in bag
    {
        CString cTemp;
        DNode * temp;
        current = NULL;
        temp = (DNode*)head;
        head = head -> next;
        head -> prev = NULL;
        cTemp = temp ->cs_val;
        delete temp;
        return cTemp;
    }
    else if (head && (head == tail)) //Does this if there is 1 number in bag
    {
        CString cTemp;
        cTemp = ((DNode*)head)-> cs_val;
        delete head;
        head = tail = current = NULL;
        return cTemp;
    }
    else
    {
        return "false";
    }
}

CString CBag::RemoveTail()
{
    if (tail && (tail != head)) //Does this if there is more than 1 number in bag
    {
        CString cTemp;
        DNode * temp;
        current = NULL;
        temp = (DNode*) tail;
        tail = tail -> prev;
        tail -> next = NULL;
        cTemp = temp -> cs_val;
        delete temp;
        return cTemp;
    }
    else if (tail && (tail == head)) //Does this if there is 1 number in bag
    {
        CString cTemp;
        cTemp = ((DNode*) tail) -> cs_val;
        delete ((DNode*) tail);
        head = tail = current = NULL;
        return cTemp;
    }
    else 
        return "false";
}

bool CBag::Find(Node *p_input)
{
    Node * temp_node = head;
    while (temp_node)
    {
        if (*temp_node == *p_input)
        {
            return(true);
        }
        temp_node = temp_node -> next;
    }
    return(false);
}
bool CBag::isEmpty()
{
    return(head==NULL);
}


bool CBag::isFull()
{
    Node * temp;
    temp=new DNode;
    delete temp;
    return(temp==NULL);
}

Node* CBag::GetHead()
{
    if(head != NULL)
    {
        current = head;
        return head;
    }
    else
        return 0;
}

Node* CBag::GetTail()
{
    if(tail != NULL)
    {   
        current = tail;
        return tail;
    }
    else
        return 0;
}

Node * CBag::GetNext()
{
    if (head)
    {
        if (current == NULL)
        {
            current = head;
            return head;
        }
        else
        {
            if (current -> next != NULL)
                current = current -> next;
            return current;
        }
    }
    else
        return 0;
}

CString CBag::Remove(Node * p_input)
{
    CString cTemp;
	cTemp = "Not Removed ";
	if(head)
    {
        Node * temp;    //Stores the address of the node that is being searched. 
        Node * previous;    //Stores the address of the node that is before temp. 
        temp = head;    //Makes temp start at beginning of the list.  
		previous=NULL;
        while ((temp)&&(((DNode*)temp)->cs_val!=((DNode*)p_input)->cs_val))    
									//Searches through through the loop to 
        {                                   //check if the input matches any of the
            previous=temp;                      //numbers in the list.  
            temp=temp->next;
        }

        if(temp==head)      //Deletes node if it is first in the list
        {
            RemoveHead();
			cTemp = "Removed ";
        }
        
        else if(temp==tail) //Deletes node if last in list
        {
            RemoveTail();
			cTemp = "Removed ";
        }
        
        else if(temp)   //Deletes the node if it is not the first or              
        {               //last in the list
            previous->next=temp->next;
            current = temp->next;
			current->prev=temp->prev;
			delete (DNode*)temp;
            delete p_input;
			temp = NULL;
			p_input = NULL;
			cTemp = "Removed ";
        }
    }
    return(cTemp); 
}

CBag::~CBag()
{
    while(head)
    {
        RemoveHead();   //Calls the remove function to remove each element 
                        //from the linked list. 
    }                           
}
