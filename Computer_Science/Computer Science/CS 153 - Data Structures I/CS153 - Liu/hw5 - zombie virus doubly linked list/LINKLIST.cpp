/* programmer: roberto murillo
 * instructor: liu
 * date: 2/17/06
 * file: LINKLIST.cpp
 * desc: Contains the functions for the LINKLIST class.
 */

#include "stdafx.h"
#include "LINKLIST.h"
using namespace std;

// Constructor
LINKLIST::LINKLIST()
{
  headPtr = NULL;
  tailPtr = NULL;
}

// Destructor
LINKLIST::~LINKLIST()
{
  clearContents(); // Deletes all nodes.
}

/********* ACCESSORS *********/
NODE* LINKLIST::getHeadPtr()const
{
  return headPtr;
}

NODE* LINKLIST::getTailPtr()const
{
  return tailPtr;
}
/********* ACCESSORS *********/

/********* MUTATORS *********/
void LINKLIST::setHeadPtr( NODE* newHeadPtr )
{
  headPtr = newHeadPtr;
}

void LINKLIST::setTailPtr( NODE* newTailPtr )
{
  tailPtr = newTailPtr;
}
/********* MUTATORS *********/

void LINKLIST::clearContents()
{
  while( headPtr != NULL ) {
    removeHeadNode();
  }
}

// Inserts new NODE at the headPtr.
void LINKLIST::insertAtHead( const PERSON & human1 )
{
  NODE *newNode = new NODE( human1, NULL, NULL );

  if( headPtr != NULL )
  {
    newNode->setNext( headPtr ); // Links the new NODE to what headPtr WAS pointing at.
    headPtr->setPrev( newNode ); // Sets headPtr's prev pointer to newNode
  }

  if( tailPtr == NULL )
    tailPtr = headPtr;

  headPtr = newNode;
}

// Inserts a new NODE at the tail end of the list.
void LINKLIST::insertAtTail( const PERSON & human1 )
{
  NODE *newNode = new NODE( human1, NULL, NULL );

  if( tailPtr != NULL )
  {
    tailPtr->setNext( newNode ); // Sets tailPtr's next link to the newNode
    newNode->setPrev( tailPtr ); // Sets the new node's previous link to the tailPtr
  }

  if( headPtr == NULL )
  {
    headPtr = tailPtr; // If it's the only item in the list, it is also set as headPtr.
  }

  tailPtr = newNode; // Sets the newNode as the tailPtr
}

// Removes the head NODE.
void LINKLIST::removeHeadNode()
{
  if (headPtr != NULL) {
    NODE* temp = headPtr; // Stores information from head NODE into a temp NODE.
    headPtr = headPtr->getNext(); // Sets the headPtr to the next NODE.

    if( headPtr == NULL )
    {
      tailPtr = NULL; // If there is nothing in the list, tailPtr is set to nothing.
    }
    else
    {
      headPtr->setPrev( NULL );
    }

    delete temp; // deletes the original headPtr.
  }
}

// Removes the tail NODE ( NODE at the end of the list ).
void LINKLIST::removeTailNode()
{
  if( tailPtr != NULL )
  {
    NODE* temp = tailPtr;
    tailPtr = tailPtr->getPrev(); // Sets a new tailPtr to the NODE before it.

    if( tailPtr == NULL )
    // If there is nothing in the tailPtr position, it sets headPtr to NULL because there is nothing
    // in the list.
    {
      headPtr = NULL;
    }

    else
    {
      // Otherwise, it sets the next link in the tailPtr to NULL.
      tailPtr->setNext(NULL);
    }

    delete temp; // Deletes the passed NODE.
  }
}

void LINKLIST::removeNode( NODE* nodeToRemove )
{
  // If there is nothing before the NODE, it runs removeHeadNode since it IS the head NODE.
  if( nodeToRemove->getPrev() == NULL )
  {
    removeHeadNode();
  }else if( nodeToRemove->getNext() == NULL )
  {
    removeTailNode();
  }else
  {
    NODE * prevNode = nodeToRemove->getPrev();
    NODE * nextNode = nodeToRemove->getNext();

    // Sets the previous NODE's next link to the NODE after it.
    prevNode->setNext( nextNode );
    // Sets the prev pointer of the NODE after it to the NODE before it.
    nextNode->setPrev( prevNode );

    delete nodeToRemove;
  }
}

// Search function
NODE* LINKLIST::findNodeByIndex( const int index )
{
  NODE *cursor;
  int count = 0;

  for (cursor = headPtr; cursor != NULL; cursor = cursor->getNext())
  {  
    if (count == index)
      return cursor;
    else count++;
  }

  return NULL;
}

void LINKLIST::updateBagContentsDisplay( CListBox & listBoxControl ) 
{ 
     listBoxControl.ResetContent(); 
 
     NODE * temp = NULL; 
 
     for( temp = headPtr; temp != NULL; temp = temp->getNext() ) 
     { 
          // Adds the person to the listbox
          listBoxControl.AddString( temp->getPerson().getName() + " - " + temp->getPerson().getStatus() ); 
     }     
}
