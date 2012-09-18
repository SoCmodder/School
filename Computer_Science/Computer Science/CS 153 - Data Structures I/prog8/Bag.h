#ifndef BAG_H
//Filename: Bag.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #8
//This program will convert a mathmatical infix expression to postfix form. 
//It was also evaluate the answer. 

#define BAG_H
#include "StdAfx.h"

class Node
{
public:
    Node * next;
    Node * prev;
    Node() {next = NULL; prev = NULL;};
    virtual ~Node() {};
    virtual bool operator==(Node& RHS)=0;
    virtual bool operator>(Node& RHS)=0;
    virtual bool operator<(Node& RHS)=0;
    virtual void operator=(Node& RHS)=0;
};

class CBag
{
public:
   
    CBag();
    //Precondition: None
    //Postcondition: Head, Tail, and Current are set to NULL, test is set to false.
    bool InsertHead(Node * p_input);
    //Precondition: Bag cannot be full and integer must be passed to it.
    //Postcondition: The integer that is passed in is placed into the top of the bag.
    //Returns true if successful and false if not.
    bool InsertTail(Node * p_input);
    //Precondition: Bag cannot be full and an integer must be passed to it.
    //Postcondition: The integer that is passed in is placed at the bottom of the bag.
    //Returns true if successful and false if not. 
    CString RemoveHead();
    //Precondition: The bag is not empty. 
    //Postcondition: The first node is removed from the bag.  The number that the
    //node contained is returned.  If bag is empty then 0 is returned.  
    CString RemoveTail();
    //Precondition: The bag is not empty. 
    //Postcondition: The last node is removed from the bag.  The number that the
    //node contained is returned.  If bag is empty then 0 is returned.  
    bool Find(Node *p_input);
    //Precondition: You must pass in an integer value.
    //Postcondition: Searches and through the bag of integers and returns true
    //if found, and false if not.
    CString GetHead();
    //Precondition: Bag is not empty. 
    //Postcondition: Returns value stored in first node. 
    Node* GetTail();
    //Precondition: Bag is not empty. 
    //Postcondition: Returns value stored in last node. Returns 0 if bag is empty. 
    Node* GetNext();
    //Precondition: Bag is not empty, and current is not at the End Of Container
    //Postcondition: Returns the next value in the list, and advances current 
    //pointer 1 node. Returns 0 if bag is empty. 
    void reset();
    //Precondtion: None
    //Postcondition: Resets current pointer to NULL. 
    bool EOC();
    //Precondition: None
    //Postcondition: Returns true if current pointer has reached the end of the bag.
    bool isEmpty();
    //Precondition: None
    //Postcondition: returns true if bag is empty and false if not.
    bool isFull();
    //Precondition: None
    //Postcondition: returns true if bag is full and false if not.
    CString Remove(Node * p_input);
    //Precondition: The bag is not empty
    //Postcondition: Inputted node is deleted.  If the input does not
    //exist in the list false is returned
    void ClearList();
    ~CBag();
    //Precondition: None
    //Postcondition: Memory used by the list is returned to the heap
    
private:
    bool test; //used as to store the return value for functions
    Node * head;
    Node * tail;
    Node * current;
};

#endif
