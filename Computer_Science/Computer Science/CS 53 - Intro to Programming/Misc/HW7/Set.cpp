//Matt Ludwikosky  CS53
//11/22/04   7:15PM - 7:55PM
//Set.cpp

#include <iostream>
using namespace std;

#include <string>
#include "Set.h"

//Constructor Set(string elementName)
//Sets Set name and initalizes all elements values to false
Set::Set(string elementName)
{
	name = elementName;
	for(int i = 0; i <= maxElements; i++)
		elements[i] = false;

	cout << "\nConstructor called for Set " << name << endl;
}

//Destructor ~Set()
//Destructs calling set and tells you so :P
Set::~Set()
{
	cout << "\nDestructor called for Set " << name << endl;
}

//***Member function isEmpty()
//***Takes in nothing
//***Returns (bool) of whether calling Set contains any numbers
bool Set::isEmpty()
{
	bool empty = true;
	for(int i = 0; i <= maxElements; i++)
		if(elements[i] == true)
			empty = false;

	return(empty);
}

//***Member function isElementOf()
//***Takes in (int)
//***Returns (bool) of whether calling Set contains passed value
bool Set::isElementOf(int x)
{
	return(elements[x]);
}

//***Member function addElement(int x)
//***Takes in (int)
//***Returns nothing  adds passed value to calling Set
void Set::addElement(int x)
{
	if(x >= 0 && x <= 9)
		elements[x] = true;
}

//***Member function deleteElement(int x)
//***Takes in (int)
//***Returns nothing  delets passed value of calling set (if present)
void Set::deleteElement(int x)
{
	if(x >= 0 && x <= 9)
		elements[x] = false;
}

//***Member function set_union(Set s)
//***Takes in (Set)
//***Returns (Set) of combined Sets of calling Set and passed Set
Set Set::set_union(Set s)
{
	Set b("union_newSet");

	for(int i = 0; i <= maxElements; i++)
		if(elements[i] == true || s.elements[i] == true)
			b.elements[i] = true;

	return(b);
}

//***Member function set_intersection(Set s)
//***Takes in (Set)
//***Returns (Set) of common values between calling Set and passed Set
Set Set::set_intersection(Set s)
{
	Set a("intersection_newSet");

	for(int i = 0; i <= maxElements; i++)
		if(elements[i] == true && s.elements[i] == true)
			a.elements[i] = true;

	return(a);
}

//***Member function print()
//***Takes in nothing
//***Returns nothing  prints values of calling Set
void Set::print()
{
	if(isEmpty() == false)
	{
		cout << "\nElements of Set " << name << ": ";

		for(int i = 0; i <= maxElements; i++)
			if(elements[i] == true)
				cout << i << " ";
	} else
		cout << "\nSet " << name << " is empty -- no elements to print.";

	cout << endl << endl;
}

//***Member function getName()
//***Takes in nothing
//***Returns (string) of calling Sets name
string Set::getName()
{
	return(name);
}

//***Member function setName)
//***Takes in (string)
//***Returns nothing  changes calling Sets name to passed string
void Set::setName(string elementName)
{
	name = elementName;
}