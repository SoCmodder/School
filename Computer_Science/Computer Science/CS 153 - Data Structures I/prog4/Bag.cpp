//Filename: Bag.cpp
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #4
//This program will insert, find, and remove integers from a linked list.  
//Also it will tell if the list is empty or full.

#include "stdafx.h"
#include "bag.h"


CBag::CBag()
{
    test = false;
    head=NULL;
}

bool CBag::Insert(int input)
{
    if (isFull())
    {
        return(false);
    }
    else
    {
        Node * temp;    //Stores the address of the node being created. 
        temp=new Node;
        temp->data=input;   //Changes the value of the new node to be the inputted
        temp->next=head;    //value. Makes the newly created node point to the next node. 
        head=temp;          //Sets head to point to the newly created node.  
        return(true);
    }
}

bool CBag::Find(int input)
{
    Node * temp;    //Stores the address of the node that is being searched. 
    temp = head;    //Makes temp start at the beginning of the list. 
    while(temp && (temp->data!=input))  //If input is found, exits loop
    {
        temp=temp->next;
    }
    return (temp!=NULL); //Temp will equal NULL if the number is not found. 
}                        //Thus resulting in the function returning false.  

bool CBag::Remove(int input)
{
    if(head)
    {
        Node * temp;    //Stores the address of the node that is being searched. 
        Node * prev;    //Stores the address of the node that is before temp. 
        temp = head;    //Makes temp start at beginning of the list.  
        prev=NULL;
        test = false;
        while(temp&&(temp->data!=input))    //Searches through through the loop to 
        {                                   //check if the input matches any of the
            prev=temp;                      //numbers in the list.  
            temp=temp->next;
        }

        if(temp==head)      //Deletes node if it is first in the list
        {
            head=head->next;
            delete temp;
            temp = NULL;
            test= true;
        }
        else if(temp)   //Deletes the node if it is not the first in the list
        {
            test = true;
            prev->next=temp->next;
            delete temp;
            temp = NULL;
        }
    }
    return(test); 
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

void CBag::Display(CListBox &listing)
{
    
    char tempchar[20];  //Stores the value that will be entered into the list box. 
    listing.ResetContent();
    Node * temp;    //Stores the node that will be converted
    temp=head;
    while(temp)    
    {
        itoa(temp->data,tempchar,10);   //Converts the integers in the linked list
        listing.AddString(tempchar);    //to a character array.  Then outputs them
        temp=temp->next;                //to the list box. 
    }
}

CBag::~CBag()
{
    while(head)
    {
        Remove(head -> data);   //Calls the remove function to remove each element 
    }                           //from the linked list. 
}
000