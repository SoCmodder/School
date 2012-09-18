/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * bag header file
 */

#include "stdafx.h"
#include "bag.h"
#include <iostream>
using namespace std;

// Constructor
// Pre: None.
// Post: numItems is set to 0.
Bag::Bag()
{
	numItems = 0;
  capacity = 10;
  items = new GroceryItem[capacity];
}

// Destructor
Bag::~Bag()
{
  delete []items;
}

/********* ACCESSORS *********/
// Pre: numItems is declared.
// Post: numItems is returned.
int Bag::getNumItems()const
{
	return numItems;
}

// Pre: The items[] array must be declared.
// Post: The selected item is returned to the calling function.
GroceryItem Bag::getItem()const
{
	return ( items[numItems - 1] );
}
/********* ACCESSORS *********/

/********* MUTATORS *********/
// Pre: Must be passed an integer.
// Post: numItems is set to the integer passed.
void Bag::setNumItems( int newNumItems )
{
	numItems = newNumItems;
}
/********* MUTATORS *********/

// Checks to see if the bag is full or not.
// Pre: None.
// Post: Checks to see if there are 10 items; if so, bagFull is returned as true.
//       If the bag has less than 10 items, than bagFull returns false.
bool Bag::isFull()
{
	bool bagFull = true;

	if ( getNumItems() < 10 ) // checks to see if there are less than 10 items.
	{
		bagFull = false;
  } 
  
  else 
  {
    increaseSize();
    bagFull = false;
  }

	return bagFull;
}

// Adds a grocery item to the grocery bag.
// Pre: A grocery item must be passed to the function.
// Post: If the bag is not full, it adds the new grocery item to the array and returns true.
bool Bag::add( const GroceryItem& addedItem )
{
	bool itemAdded = false;
	
	if ( !isFull() ) // if the bag isnt full, it adds an item and increases numItems by 1.
	{
    items[ getNumItems() ] = addedItem;
    setNumItems( getNumItems() + 1 );
		itemAdded = true;
	}

	return itemAdded;
}

// Removes one desired item from the grocery bag.
// Pre: The grocery item to be removed must be passed to the function.
// Post: Searches the array for the first item it finds that matches the description and price.  It
//       then removes the item and shifts everything in the array down one index and returns itemRemoved
//       true.
bool Bag::removeOne( const GroceryItem& removedItem )
{
	bool itemRemoved = false;

	// Shifts all items down in the array and reports true if the item was removed successfully.
  // First, it searches for the matching item and removes it.
	for( int i = 0; i < getNumItems() && !itemRemoved; i++ )
	{
		if( items[i].description == removedItem.getDescription() && items[i].price == removedItem.getPrice() )
		{
            for( int j = i + 1; j < getNumItems(); j++ )
			{			
				items[i] = items[j];
				i++;
			}
			
			itemRemoved = true;
			setNumItems( getNumItems() - 1 );
		}
	}

	return itemRemoved;
}

// Removes all such items desired from the grocery bag.
// Pre: The grocery item to be removed must be passed to the function.
// Post: Runs the removeOne function until all items that matched the description and price are gone
//       and also sets itemsRemoved to true.
bool Bag::removeAll( const GroceryItem& removedItem )
{
	bool itemsRemoved = false;
	
	while( removeOne( removedItem ) ) // runs the removeOne function until all matching items are gone.
	{
		itemsRemoved = true;
	}

	return itemsRemoved;
}

// Displays and refreshes the items in the listbox.
// Pre: A list box is declared and passed to the function.
// Post: Adds all of the items in the array to the list box and displays them to the GUI.
void Bag::Display( CListBox& ListBox )
{
	ListBox.ResetContent();
	for( int i = 0; i < numItems; i++ )
		// Adds the newly concatinated string of price and description of each item to the listbox.
		ListBox.AddString(items[i].toString());

	return;
}

// Clears the entire bag.
// Pre: None.
// Post: Runs the setNumItems function with an int of 0.  This clears the array.
void Bag::clearContents()
{
	setNumItems(0);

	return;
}

void Bag::increaseSize()
{
  GroceryItem *p = new GroceryItem[capacity]; // creates pointer.
  capacity+=5; // increases capacity by five

  for (int i = 0; i < getNumItems(); i++ )
  {
    p[i] = items[i]; // moves all items to the array being pointed to.
  }

  delete []items; // deletes old array

  items = new GroceryItem[capacity]; // recreates the old array

  for (int i = 0; i < getNumItems(); i++ )
  {
    items[i] = p[i]; // all items are dumped back into the newly increased array.
  }

  delete []p; // extra memory is deleted.

  return;
}

  