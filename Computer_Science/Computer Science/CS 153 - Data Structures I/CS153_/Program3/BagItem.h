//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 2 Description: This program will implement
// a bag class and will offer some basic forms of data 
// manipulation of the bag.
#pragma once

class BagItem
{
	public:
      typedef float weight_type; //typedef for weight type
      typedef CString description_type; //typedef for description _type
      weight_type weight; //instance of weight_type
      description_type description; //instance of description_type
	   BagItem(void); //default constructor
      BagItem(const weight_type& weight, const description_type& description);
      //constructor with non default entries
      BagItem(const BagItem& rhs); // Copy Constructor
	   ~BagItem(void); //destructor
	   //Preconditions: Assumes weight and description are valid
      //PostConditions: Sets an item to the given weight and description
      void SetItem(const description_type& Description, const weight_type& Weight);
      //Preconditions: none
      //PostConditions: Returns the weight of an item
      weight_type GetWeight(void) const;
      //Preconditions: none
      //PostConditions: Returns the description of an item
      description_type GetDescription(void) const;
	   bool operator ==(const BagItem& rhs);
};

