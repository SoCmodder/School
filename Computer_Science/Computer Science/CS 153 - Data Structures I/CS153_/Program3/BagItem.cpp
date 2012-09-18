//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 2 Description: This program will implement
// a bag class and will offer some basic forms of data 
// manipulation of the bag.

#include "StdAfx.h"
#include ".\bagitem.h"


typedef float weight_type;
typedef CString description_type;


//Preconditions: none
//PostConditions: Will create a default BagItem with 
//weight of 1 and no description
BagItem::BagItem(void)
{
   weight = 1;
   description = "none";
}

//Preconditions: none
//PostConditions: Will make a copy of a BagItem
BagItem::BagItem(const BagItem& rhs)
{
   description = rhs.description;
   weight = rhs.weight;
}


BagItem::BagItem(const weight_type& weight, const description_type& description)
{
   SetItem(description,weight);
}

//Preconditions: none
//PostConditions: none
BagItem::~BagItem(void)
{
}

//Preconditions: Must receive valid values passed in
//PostConditions: Will set the weight and description to values to be easily used
void BagItem::SetItem(const description_type& Description, const weight_type& Weight)
{
	weight = Weight;
	description = Description;

}
//Preconditions: none
//PostConditions: Will return the weight
weight_type BagItem::GetWeight(void) const
{
   return weight;
}

//Preconditions: none
//PostConditions: Will return the description
description_type BagItem::GetDescription(void) const
{
   return description;
}

bool BagItem::operator==(const BagItem& rhs)
{
	bool tmp = false;
	if ((description ==rhs.description) && (weight == rhs.weight))
	{
		tmp = true; 
	}
		return tmp;
}

