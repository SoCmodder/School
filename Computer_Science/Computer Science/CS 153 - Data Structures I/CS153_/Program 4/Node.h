//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.

#ifndef Node_H
#define Node_H

template <typename T>
class Node
{
public:
   Node(); //default constructor for Node
   Node(const T& Data,const Node*Next);
   //constructor with non-default parameters
   ~Node();//destructor
   Node* GetNext(); //accessor to get the Next Node
   T GetData() const; //accessor to get Data
   void SetNext(Node*Next);//mutator to set Next
   void SetData(const T&Data);//mutator to set Data

private:
   Node* Next_; //Next pointer
   T Data_; //Data of the Node
};

#include "Node.hpp"
#endif