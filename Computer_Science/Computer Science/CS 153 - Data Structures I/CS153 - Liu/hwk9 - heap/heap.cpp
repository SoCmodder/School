/* programmer: roberto murillo
 * instructor: liu
 * date: 4/18/06
 * file: heap.cpp
 * desc: contains the function definitions for the heap.
 */

#include "stdafx.h"
#include "heap.h"

HEAP::HEAP()
{
  // All variables are initialized.
  numPatients = 0;
  capacity = 10;
  patients = new PATIENT[capacity];
}

HEAP::HEAP( HEAP& heapToCopy )
{
  // Pulls the information from the passed heap
  numPatients = heapToCopy.getNumPatients();
  capacity = heapToCopy.getCapacity();
  // Creates a new array for the heap being formed.
  patients = new PATIENT[capacity];
  
  // Loads everything from the passed heap's array to the new array.
  for( int i = 0; i < numPatients; i++ )
    patients[ i ] = heapToCopy.getPatient( i );
}

HEAP::~HEAP()
{
  // Clears any used memory.
  delete []patients;
}

int HEAP::getCapacity()const
{
  return capacity;
}

int HEAP::getNumPatients()const
{
  return numPatients;
}

PATIENT HEAP::getPatient( int numPat )const
{
  return patients[ numPat ];
}

void HEAP::setNumPatients( int newNum )
{
  numPatients = newNum;
}

void HEAP::clear()
{
  // If the number of patients is zero, the display is clear.
  setNumPatients( 0 );
}

bool HEAP::isFull()
{
  bool full = true;

  if( getNumPatients() < capacity )
    full = false;

  return full;
}

bool HEAP::insert( PATIENT patToBeAdded )
{
  bool inserted = false;

  if( !isFull() )
  {
    // Increases the number of patients.
    setNumPatients( getNumPatients() + 1 );
    // Sets the patient in the last position.
    patients[ getNumPatients() - 1 ] = patToBeAdded;
    inserted = true;

    // The last patient's index.
    int i = getNumPatients() - 1;
    // While it is greater than it's parent, it is switched with its parent.
    while( i >= 0 && patients[ i ].getPriority() > 
           patients[ (i - 1)/2 ].getPriority() )
    {
      // Stores current patient's info in a temp node.
      PATIENT temp = patients[i];
  
      // Swaps the current patient with its parent
      patients[i] = patients[ (i - 1)/2 ];
      patients[ (i - 1)/2 ] = temp;
      // Sets the new index to the parent's index.
      i = (i-1)/2;
    }
  }

  else
  {
    // Otherwise, if the room is full, it is increased.
    increaseRoom();
    // Then the patient is inserted.
    inserted = insert( patToBeAdded );
  }

  return inserted;
}

void HEAP::increaseRoom()
{
  PATIENT *p = new PATIENT[capacity]; // Creates pointer array.
  capacity+=5; // Increases capacity by five

  for (int i = 0; i < getNumPatients(); i++ )
    p[i] = patients[i]; // Moves all items to the array being pointed to.

  delete []patients; // Deletes old array

  patients = new PATIENT[capacity]; // Recreates the old array

  for (int i = 0; i < getNumPatients(); i++ )
  {
    // All items are dumped back into the newly increased array.
    patients[i] = p[i]; 
  }

  delete []p; // Extra memory is deleted.
}

bool HEAP::removeRoot()
{
	//the max node is the root of the tree, data[0]
	PATIENT maxNode = patients[0];
  bool removed = false;

	if( getNumPatients() == 0 )
		return false;

  PATIENT temp;

	// Puts last node in as the root.
	patients[0] = patients[ getNumPatients() - 1 ];
	// Clears last node.
	patients[ getNumPatients() - 1 ].setDesc("");
	patients[ getNumPatients() - 1 ].setPriority(-1);

  // Decreases the number of patients.
	setNumPatients( getNumPatients() - 1 );

  // i is the root node, and the leftchild and rightchild are set to their
  // respective indexes.
  int i = 0;
  int leftchild = (2*i) + 1;
	int rightchild = (2*i) + 2;

	// While the parent has children and the childen have higher priority, swap
  // with whichever child has the higher priority.
	while( (rightchild <= getNumPatients()&& leftchild <= getNumPatients() ) && 
          patients[ leftchild ].getPriority() > patients[ i ].getPriority() ||
	        patients[ rightchild ].getPriority() > patients[ i ].getPriority() )
	{
    // If the leftchild's priority is greater, than swap with left child.
		if( patients[ leftchild ].getPriority() > patients[ rightchild ].getPriority() )
		{
			// Swaps.
			temp = patients[ i ];
			patients[ i ] = patients[ leftchild ];
			patients[ leftchild ] = temp;

      // Updates indexes.
			i = leftchild; 
			leftchild = (2*i) + 1;
			rightchild = (2*i) + 2;
		}else
		{
			// Swaps.
			temp = patients[ i ];
			patients[ i ] = patients[ rightchild ];
			patients[ rightchild ] = temp;

			i = rightchild;
			rightchild = (2*i) + 1;
			leftchild = (2*i) + 2;
		}
	} 

  return true;
}
