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

GroceryItem::GroceryItem()
{
	description = " ";
	price = 0;
}


CString GroceryItem::getDescription()const
{
	return description;
}

double GroceryItem::getPrice()const
{
	return price;
}

void GroceryItem::setDescription( CString desc1 )
{
	description = desc1;
}

void GroceryItem::setPrice( double price1 )
{
	price = price1;
}

CString GroceryItem::toString()const
{
	char buffer[10];

	sprintf( buffer, " $%5.2f", price); // prints to a string
	CString priceAsString = buffer;

	return (description + priceAsString);
}
