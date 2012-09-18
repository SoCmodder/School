//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 2 Description: This program will implement
// a bag class and will offer some basic forms of data 
// manipulation of the bag.

#pragma once

#include "BagItem.h"
class bag
{
	public:
		bag(void); //default constructor for bag
      bag(const bag& rhs); // Copy Constructor
		~bag(void); //destructor for bag
		typedef float weight_type; //typedef for interchangability
      typedef CString description_type; //typedef for interchangability
		static const float MAX_WEIGHT; //Class Constant
      int CurrentSize; //public class variable
      weight_type CurrentWeight; // public class variable
      BagItem* Item; //public class variable
      int Max_Size; //public class variable
  		void add(const weight_type& weight, const description_type& description);
      //mutator to add an item to the array
      bool erase_one(const description_type& description, const weight_type& weight);
      //mutator to remove one item from the bag
      void erase_all(void);
      //mutator to remove all items from the bag
      void ArrayLarger();
      //mutator that increases array size by 5 when called
      //accessor functions
		int GetSize(void) const; //accessor to get size
      float GetWeight(void) const; //accessor to get weight
      CString GetItem(const int& index) const; //accessor to getItem
      weight_type GetMaxWeight(void) const; //accessor to getMaxWeight
      int GetMaxSize(void) const; //accessor to getMaxSize
};

