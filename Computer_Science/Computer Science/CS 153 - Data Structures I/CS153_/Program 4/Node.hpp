//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.

#include "StdAfx.h"

//Preconditions: none
//PostConditions: Will create a default node 
template <typename T>
Node<T>::Node(void)
{
   Next_ = NULL;
}
//Preconditions: none
//PostConditions: none
template <typename T>
Node<T>::~Node(void)
{

}

//Preconditions: Pass in the required parameters
//PostConditions: Will create a non default node
template <typename T>
Node<T>::Node(const T& Data,const Node*Next)
{
   SetData(Data);
   SetNext(Next);
}

//Preconditions: none
//PostConditions: Will return the Next_ pointer
template <typename T>
Node<T>* Node<T>::GetNext() 
{
   return Next_;
}

//Preconditions: none
//PostConditions: Will return Data_
template <typename T>
T Node<T>::GetData() const
{
   return Data_;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will set Next_ 
template <typename T>
void Node<T>::SetNext(Node*Next)
{
   Next_= Next;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will set Data_
template <typename T>
void Node<T>::SetData(const T&Data)
{
   Data_=Data;
}