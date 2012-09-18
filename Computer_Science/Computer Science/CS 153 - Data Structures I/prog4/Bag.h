#ifndef BAG_H
//Filename: Bag.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #4
//This program will insert, find, and remove integers from a linked list.  
//Also it will tell if the list is empty or full.

#define BAG_H
#include "StdAfx.h"

struct Node
{
    int data;
    Node * next;
    Node(){data=0; next=NULL;}
};

class CBag
{
public:
    CBag();
    bool Insert(int input);
    //Precondition: Bag cannot be full and integer must be passed to it.
    //Postcondition: The integer that is passed in is placed into the bag.
    //Returns true if successful and false if not.
    bool Find(int input);
    //Precondition: You must pass in an integer value.
    //Postcondition: Searches through the bag of integers and returns true
    //if found, and false if not.
    bool Remove(int input);
    //Precondition: An integer must be passed into the function.
    //Postcondition: Returns true if an integer is found and removed, and
    //false if not. If two instances of the same number exist, then only
    //one be removed.  
    bool isEmpty();
    //Precondition: m_size is set to the size of the bag.
    //Postcondition: returns true if bag is empty and false if not.
    bool isFull();
    //Precondition: m_size is set to the size of the bag.
    //Postcondition: returns true if bag is full and false if not.
    void Display(CListBox &);
    //Precondition: stdafx is included.
    //Postconditions: The list box is outputted. 
    ~CBag();
    //Precondition: None
    //Postcondition: Memory used by the list is returned to the heap
private:
    bool test; //used as to store the return value for functions
    Node * head;
};

#endif
