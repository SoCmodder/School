/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * grocery item header file - contains the class definition for 
 * a grocery item.
 */

#ifndef GROCERY_H
#define GROCERY_H

class GroceryItem
{
	public:
		GroceryItem();
		CString getDescription()const; // accessor fnct
		double getPrice()const;  // accessor fnct
		void setDescription( CString desc1 ); // mutator fnct
		void setPrice( double price1 );  // mutator fnct
		CString toString()const;

	// member variables
		CString description;  // name of item
		double price;         // price of item
};

#endif
