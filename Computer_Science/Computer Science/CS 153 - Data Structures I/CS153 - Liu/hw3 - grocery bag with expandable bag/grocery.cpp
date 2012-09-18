/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * grocery item function file - contains all function definitions for
 * the grocery item class.
 */

#include "stdafx.h"
#include "grocery.h"
#include <iostream>
using namespace std;


// Constructor
// Pre: None.
// Post: The description is set to " " and the price is set to 0.
GroceryItem::GroceryItem()
{
	description = " ";
	price = 0;
}

/********* ACCESSOR FUNCTIONS *********/
// getDescription() simply returns the description.
// Pre: Description has been declared.
// Post: Description is returned to the calling item.
CString GroceryItem::getDescription()const
{
	return description;
}

// getPrice() gets the price.
// Pre: Price has been declared.
// Post: Price is returned to the calling item.
double GroceryItem::getPrice()const
{
	return price;
}
/********* ACCESSOR FUNCTIONS *********/

/********* MUTATOR FUNCTIONS *********/
// setDescription sets the description.
// Pre: None.
// Post: Assigns the description passed to the description variable.
void GroceryItem::setDescription( CString desc1 )
{
	description = desc1;
}

// setPrice sets a price.
// Pre: The double passed must be a non-negative number because you
//      cannot have a negative price.
// Post: Assigns the price passed to the price variable.
void GroceryItem::setPrice( double price1 )
{
	price = price1;
}
/********* MUTATOR FUNCTIONS *********/

// Converts the price to a CString.
// Pre: Price that it is converting to a CString must be a non-negative number.
//      You cannot have a negative price.
// Post: Convers and the price to a string and concatinates it with the description.
//       Then it returns the concatination.
CString GroceryItem::toString()const
{
	char buffer[10];

	sprintf( buffer, " $%5.2f", price); // prints to a string
	CString priceAsString = buffer;

	return (description + priceAsString);
}
