//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.

#ifndef LinkedList_H
#define LinkedList_H
#include "Node.h"

template <typename T>
class LinkedList
{
   public:
      LinkedList(); //Default constructor for the linked list
      LinkedList(const LinkedList&rhs); //copy constructor
      ~LinkedList(); //destructor
      void AddToHead(const T& Data);//mutator to add Head
      void AddToTail(const T& Data);//mutator to add Tail
      bool FindData(const T& Data);//function to tell if a 
      //specific node was found
      bool Remove(const T&Data);//mutator that removes the 
      //specified data
      void IterReset();//mutator to reset IterNode_
      void Clear(); // mutator to clear all data
      const LinkedList& operator=(const LinkedList&rhs);
      //overloaded = operator
      int GetNumOfNodes()const;//accessor to get Number of Nodes
      T GetNextData(); //Function to get the next node
      int Search(const T& Data);//function that returns number of 
      //specified cars in the linked list

   private:
      //private member variables
      Node<T>* Head_;
      Node<T>* Tail_;
      Node<T>* IterNode_;
      int NumOfNodes_;
};

#include "LinkedList.hpp"
#endif

