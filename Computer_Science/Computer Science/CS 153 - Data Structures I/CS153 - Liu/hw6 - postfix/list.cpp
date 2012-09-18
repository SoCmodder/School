/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: list.cpp
 * desc: contains the functions for the link list class.
 */

#include "stdafx.h"
#include "list.h"
using namespace std;

// Constructor
LINKLIST::LINKLIST()
{
  headPtr = NULL;
}

// Destructor
LINKLIST::~LINKLIST()
{
  clearContents(); // Deletes all nodes.
}

NODE* LINKLIST::getHeadPtr()const
{
  return headPtr;
}

void LINKLIST::clearContents()
{
  NODE* temp;
  
  /* While there are still NODES left, it deletes the NODE in the headPtr
   * and moves onto the next NODE and proceeds to delete it. 
   */
  while( headPtr != NULL ) {
    temp = headPtr;
    headPtr = headPtr -> getLink(); // Moves to the next NODE.
    delete temp; // Deletes old node.
  }
}

bool LINKLIST::isEmpty()
{
  bool empty = false;

  if (headPtr == NULL)
    empty = true;

  return empty;
}

// Inserts new NODE at the headPtr.
void LINKLIST::insertAtHead( const char & data1 )
{
  NODE *newNode = new NODE( data1, NULL );
  newNode->setLink( headPtr ); // Links the new NODE to what headPtr WAS 
                               // pointing at.
  headPtr = newNode;
}

// Removes the head NODE.
void LINKLIST::removeHeadNode()
{
  if (headPtr != NULL) {
    NODE* temp = headPtr; // Stores information from head NODE into a temp 
                          // NODE.
    headPtr = headPtr->getLink(); // Sets the headPtr to the next NODE.
    delete temp; // deletes the original headPtr.
  }
}

void LINKLIST::removeNode( NODE* ptrToPrevNode )
{
  if( ptrToPrevNode != NULL) {
    NODE* temp = ptrToPrevNode->getLink(); // Sets temp = to the node you 
                                           // want to delete.
    ptrToPrevNode->setLink(temp->getLink()); // Sets temp's link to the node
                                             // after you want to delete.
    delete temp; // Removes node you want to delete.
  }

  else removeHeadNode();
}

// Search function
NODE* LINKLIST::findNodeByIndex( const int index )
{
  NODE *cursor;
  int count = 0;

  for (cursor = headPtr; cursor != NULL; cursor = cursor->getLink())
  {  
    if (count == index)
      return cursor;
    else count++;
  }

  return NULL;
}