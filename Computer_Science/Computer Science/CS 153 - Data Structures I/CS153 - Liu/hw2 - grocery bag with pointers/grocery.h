/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * bag header file
 */

#ifndef GROCERY_H
#define GROCERY_H

// Constructor
// Pre: None.
// Post: The description is set to " " and the price is set to 0.

/********* ACCESSOR FUNCTIONS *********/
// getDescription() simply returns the description.
// Pre: Description has been declared.
// Post: Description is returned to the calling item.

// getPrice() gets the price.
// Pre: Price has been declared.
// Post: Price is returned to the calling item.
/********* ACCESSOR FUNCTIONS *********/

/********* MUTATOR FUNCTIONS *********/
// setDescription sets the description.
// Pre: Must be passed a cstring.
// Post: Assigns the description passed to the description variable.

// setPrice sets a price.
// Pre: A price must be passed to the function.
// Post: Assigns the price passed to the price variable.
/********* MUTATOR FUNCTIONS *********/

// Converts the price to a CString.
// Pre: Price that it is converting to a CString must be a non-negative number.
// Post: Convers and the price to a string and concatinates it with the description.
//       Then it returns the concatination.

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
