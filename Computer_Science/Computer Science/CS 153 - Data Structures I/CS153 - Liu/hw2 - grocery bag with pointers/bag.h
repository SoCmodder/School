/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * bag header file
 */

#ifndef BAG_H
#define BAG_H

#include "grocery.h"

//Constructor
// Pre: None.
// Post: numItems is set to 0.

/********* ACCESSORS *********/
// getNumItems()const
// Pre: numItems is declared.
// Post: numItems is returned.

// getItem()const
// Pre: The items[] array must be declared.
// Post: The selected item is returned to the calling function.
/********* ACCESSORS *********/

/********* MUTATORS *********/
// setNumItems
// Pre: Must be passed an integer.
// Post: numItems is set to the integer passed.
/********* MUTATORS *********/

// isFull() checks to see if the bag is full or not.
// Pre: None.
// Post: Checks to see if there are 10 items; if so, bagFull is returned as true.
//       If the bag has less than 10 items, than bagFull returns false.

// add Adds a grocery item to the grocery bag.
// Pre: A grocery item must be passed to the function.
// Post: If the bag is not full, it adds the new grocery item to the array and returns true.

// removeOne Removes one desired item from the grocery bag.
// Pre: The grocery item to be removed must be passed to the function.
// Post: Searches the array for the first item it finds that matches the description and price.  It
//       then removes the item and shifts everything in the array down one index and returns itemRemoved
//       true.

// removeAll Removes all such items desired from the grocery bag.
// Pre: The grocery item to be removed must be passed to the function.
// Post: Runs the removeOne function until all items that matched the description and price are gone
//       and also sets itemsRemoved to true.

// Display(ListBox) Displays and refreshes the items in the listbox.
// Pre: A list box is declared and passed to the function.
// Post: Adds all of the items in the array to the list box and displays them to the GUI.

// clearContents() Clears the entire bag.
// Pre: None.
// Post: Runs the setNumItems function with an int of 0.  This clears the array.

class Bag
{
	public:
		Bag();
    ~Bag();
		int getNumItems()const;
		GroceryItem getItem()const;
		void setNumItems( int newNumItems );
		bool isFull();
		bool add( const GroceryItem& addedItem );
		bool removeOne( const GroceryItem& removedItem );
		bool removeAll( const GroceryItem& removedItem );
		void Display( CListBox& ListBox);
		void clearContents();
    void increaseSize();

	private:
		int numItems;  // number of items in the bag
    int capacity;  // max items that the bag can hold
		GroceryItem *items; // list of the items in the bag
};

#endif


