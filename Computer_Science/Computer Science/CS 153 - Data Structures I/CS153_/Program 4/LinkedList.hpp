//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 4 Description: This program will implement
// a LinkedList class and will offer some basic forms of data 
// manipulation of the LinkedList using the GUI for functions 
// to simulate a car lot with various functionality.

#include "StdAfx.h"

//Preconditions: none
//PostConditions: Will create a default templated LinkedList
template <typename T>
LinkedList<T>::LinkedList(void)
{
   Head_=NULL;
   Tail_=NULL;
   IterReset();
   NumOfNodes_= 0;
}

//Preconditions: none
//PostConditions: Will properly free memory
template <typename T>
LinkedList<T>::~LinkedList(void)
{
   Clear();
}

//Preconditions: Pass in required parameters
//PostConditions: Will create a copy of a linked list
template <typename T>
LinkedList<T>::LinkedList(const LinkedList&rhs)
{
   Head_=rhs.Head_;
   Tail_=rhs.Tail_;
   IterNode_=rhs.IterNode_;
   NumOfNodes_=rhs.NumOfNodes_;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will add a node to the head of the linked list
template <typename T>
void LinkedList<T>::AddToHead(const T& Data)
{
   IterNode_= NULL;
   IterNode_= new Node<T>;
   IterNode_->SetData(Data);
   if(!Head_)
   {
      IterNode_->SetNext(NULL);
      Tail_ = IterNode_;
   } 
   else
   {
      IterNode_->SetNext(Head_);
   }
   Head_= IterNode_;
   NumOfNodes_++;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will add a node to the tail of the linked list
template <typename T>
void LinkedList<T>::AddToTail(const T& Data)
{
   IterNode_=NULL;
   IterNode_=new Node<T>;
   IterNode_->SetData(Data);
   IterNode_->SetNext(NULL);
   if(!Tail_)
      Head_=IterNode_;
   else
      Tail_->SetNext(IterNode_);
   Tail_=IterNode_;
   NumOfNodes_++; 
}

//Preconditions: none
//PostConditions: Will return the current number of nodes
// in the linked list
template <typename T>
int LinkedList<T>::GetNumOfNodes()const
{
   return NumOfNodes_;
}

//Preconditions: none
//PostConditions: Will return the next number in the linked list
template <typename T>
T LinkedList<T>::GetNextData()
{
   T tmp(IterNode_->GetData());
   IterNode_ = IterNode_->GetNext();
   return tmp;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will search the linked list for the Automobile
template <typename T>
bool LinkedList<T>::FindData(const T& Data)
{
   bool tmp = false;
   IterReset();
   for (int i=0; i<NumOfNodes_ && !tmp; i++)
   {
      if(IterNode_->GetData()==Data)
      {
         tmp= true;
      }
      else
      {
         IterNode_=IterNode_->GetNext();
      }
   }
   return tmp;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will remove the Automobile specified 
template <typename T> 
bool LinkedList<T>::Remove(const T&Data) 
{ 
   bool tmp = false; 
   IterReset(); 
   if(FindData(Data)) 
   { 
      // Remove Head
      if (IterNode_==Head_) 
      { 
         IterNode_ = (IterNode_->GetNext()); 
         delete Head_; 
         Head_ = IterNode_; 
         //Removing Only element 
         if(!Head_) 
            Tail_= IterNode_; 
      } 
      // Remove other
      else 
      { 
         Node<T>* Temp=NULL; 
         Temp=IterNode_; 
         IterReset(); 
         while(IterNode_->GetNext()!=Temp) 
         {
            IterNode_=IterNode_->GetNext(); 
         }
         IterNode_->SetNext(Temp->GetNext()); 
         //Remove tail 
         if(!Temp->GetNext()) 
         { 
            Tail_=IterNode_; 
         } 
         delete Temp; 
      } 
       
      this->NumOfNodes_--; 
      tmp=true; 
   } 
   return tmp; 
}


//Preconditions: none
//PostConditions: WWill reset the IterNode_ to be pointing to 
// the beginning of the linked list
template <typename T>
void LinkedList<T>::IterReset()
{
   IterNode_=Head_;
}

//Preconditions: none
//PostConditions: Will clear the entire linked list
template <typename T>
void LinkedList<T>::Clear()
{
   IterReset();
   while(IterNode_)
   {
      IterNode_ = IterNode_->GetNext();
      delete Head_;
      Head_= IterNode_;
   }
   Head_= NULL;
   Tail_= NULL;
   IterNode_=NULL;
   NumOfNodes_=0;
}

//Preconditions: Pass in the required parameters
//PostConditions: Will search the linked list for the 
// specified data, and the print out the results in the 
// listbox in the GUI
template <typename T>
int LinkedList<T>::Search(const T& Data)
{
   int counter = 0;
   IterReset();
   for(int i = 0; i < NumOfNodes_; i++)
   {
      if(IterNode_->GetData() == Data)
      {
         counter++;
         
      }
   IterNode_=IterNode_->GetNext();
   }
   return counter;
}



