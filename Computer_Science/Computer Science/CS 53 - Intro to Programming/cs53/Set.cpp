/*
 * File: Set.cpp
 * Description: implementation of Set.h
 */

#include "Set.h"
#include <string>
#include <iostream>

using namespace std;

/****************************************************************
Function name: Set

Description: empteys the set to nothing

Parameters: string c_name

Returns: none
****************************************************************/

Set::Set(string c_name)
{
	int i;
	name=c_name;
	for(i=0;i<10;i++)
	{
		elements[i]=false;
	}
	cout<<"Set "<<name<<" has been set to all false values"<<endl;
}
/******************************************************************
Function name: ~Set

Description: The destructor for the set

Parameters: none

Returns: nothing
*******************************************************************/

Set::~Set( )
{
	cout<<"Destructor called for Set "<<name<<endl;
}
/********************************************************************
Function name: isEmpty

Description: Lets user know if the value is part of the set

Parameters: none

Returns: bool found
*********************************************************************/


bool Set::isEmpty() const
{
	int i=0;
	bool found=true;
	while((i<10)&&(found==true))
	{
		if(elements[i]==true)
			found=false;
		else
			i++;
	}
	return found;
}
/**********************************************************************
Function name: isElementof

Description: returns true if element is part of set

Parameters: int x

Returns: bool
***********************************************************************/

bool Set::isElementOf(const int x) const
{
	bool found=false;
	if (elements[x]==true)
		found=true;
	return found;
}

/***********************************************************************
Function name: addElement

Description: Add's an element to the set by changing it's value to true

Parameters: int x

Returns: none
***********************************************************************/

void Set::addElement(const int x)
{
	if ((x>=0)&&(x<10))
		elements[x]=true;
	return;
}
/*************************************************************************
Function name: deleteElement

Description: Deletes an element from the set by changing it's value to false

Parameters: int x

Returns: Nothing
**************************************************************************/

void Set::deleteElement(const int x)
{
	if ((x>=0)&&(x<10))
		elements[x]=false;
	return;
}
/*************************************************************************
Function name: getName

Description: lets the user retreave the set's name

Parameters: none

Returns: string name
**************************************************************************/

string Set::getName() const
{
	return name;
}
/***************************************************************************
Function name: setName

Descrpition: Sets the value of the private member of the set

Parameters: string sName

Returns:    Nothing
****************************************************************************/

void Set::setName(const string sName)
{
	name=sName;
	return;
}

/****************************************************************************
Function name: print

Description:   Outputs information (name and elements) of a Set. 

Parameters:    None.

Returns:       Nothing.
****************************************************************************/
void Set::print() const 
{
  if (! isEmpty()) 
  {
	cout << "\nElements of Set " << name << ": ";
	for (int i = 0; i < maxElements; i++)
      if (elements[i]) cout << i << " ";
	cout << endl;
  }
  else cout << "\nSet " << name 
	        << " is empty -- no elements to print.\n";
  cout << endl;
}

/****************************************************************************
Function name: set_union

Description:   Take the union of this Set and another Set.

Parameters:    Set s.

Returns:       A Set that is the union of this Set and Set s.
****************************************************************************/
Set Set::set_union(const Set s) const 
{
	Set newSet("union_newSet");
	int i=0;
	while (i<10)
	{
		if((s.elements[i]==true)||(elements[i]==true))
			newSet.elements[i]=true;
		i++;
	}

  // Put element i in newSet if it is in this set
  // OR it is in set s

  return(newSet);
}

/****************************************************************************
Function name: set_intersection

Description:   Take the intersection of this Set and another Set.

Parameters:    Set s.

Returns:       A Set that is the intersection of this Set and Set s.
****************************************************************************/
Set Set::set_intersection(const Set s) const
{
	Set newSet("intersection_newSet");
	int i=0;
	while(i<10)
	{
		if((s.elements[i]==true)&&(elements[i]==true))
		newSet.elements[i]=true;
		i++;
	}

  // Put element i in newSet if it is in this set
  // AND in set s

  return(newSet);
}