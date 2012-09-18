/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * bag header file - contains the class definition for a grocery bag
 */

#ifndef BAG_H
#define BAG_H

#include "grocery.h"

class Bag
{
	public:
		Bag(); // constructor
    ~Bag(); // destructor
		int getNumItems()const; // accessor fnct
		GroceryItem getItem()const; // accessor fnct
		void setNumItems( int newNumItems ); // mutator fnct
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


