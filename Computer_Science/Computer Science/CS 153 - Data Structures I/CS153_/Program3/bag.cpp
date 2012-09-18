//Programmer: Elliot Gross
//Class: CS153
//Teacher: Matt Johnson
//Program 2 Description: This program will implement
// a bag class and will offer some basic forms of data 
// manipulation of the bag.

#include "StdAfx.h"
#include ".\bag.h"


const float bag::MAX_WEIGHT(30);
typedef CString description_type;
typedef float weight_type;


//Preconditions: none
//PostConditions: Will create a default bag
bag::bag(void)
{
   //initializes the public class variables
	CurrentSize = 0;
	CurrentWeight = 0;
   Max_Size = 10;
   Item = new BagItem[Max_Size];
}

//Preconditions: none
//PostConditions: Will create a copy of the bag
bag::bag(const bag& rhs)
{
   CurrentSize = rhs.CurrentSize;
   CurrentWeight = rhs.CurrentWeight;

}


//Preconditions: There was dynamic memory used in the program
//PostConditions: Releases memory that was allocated for
// the dynamic memory. Sets the pointer to Null.
bag::~bag(void)
{
   delete []Item;
   Item = NULL;
   
}

//Preconditions: none
//PostConditions: will return an int for Current size of bag
int bag::GetSize(void) const
{
   return CurrentSize;
}

//Preconditions: none
//PostConditions: will return a float representing the CurrentWeight
float bag::GetWeight(void) const
{
   return CurrentWeight;
}

//Preconditions: pass in a constant index
//PostConditions: Will retreive the item from that index
CString bag::GetItem(const int& index) const
{
  char buffer[50];
  gcvt(Item[index].GetWeight(),4,buffer);
  CString Description = Item[index].GetDescription();
  CString WeightAsString=buffer;
  Description += " " +WeightAsString;
  return(Description);
}

//Preconditions: none
//PostConditions: will return the max_weight of the bag
weight_type bag::GetMaxWeight(void) const
{
   return MAX_WEIGHT;
}

//Preconditions: none
//PostConditions: Will return the CAPACITY
int bag::GetMaxSize(void) const
{
   return Max_Size;
}

//Preconditions: Must pass in a non-negative weight, and description
//PostConditions: Will gather the data and put it into the bag, and properly
//                adjust the CurrentSize and Weight
void bag::add(const weight_type& weight, const description_type& description)
{
	Item[CurrentSize].SetItem(description, weight);
   CurrentSize++;
   CurrentWeight += weight;
}

//Preconditions: none
//PostConditions: Will erase all data in the bag
void bag::erase_all(void)
{
	CurrentSize = 0;
   CurrentWeight = 0;

}
//Preconditions: Pass in a valid description
//PostConditions: Will search the bag and if found delete the first instance
//                of that description, and move the last entry in the bag to 
//                deleted spot
bool bag::erase_one(const description_type& description, const weight_type& weight)
{
	bool test = false;
   BagItem tmp(weight, description);
	for (int i = 0; (i < CurrentSize)&&(!test); i++)
	{
		if(tmp ==Item[i])
      {
         test = true;
      }
   
      if(test)
      {
         CurrentWeight -= Item[i].GetWeight();
         Item[i] = Item[CurrentSize-1];
         CurrentSize--;
      }
      
   }
 return test;
}

//Preconditions: none
//PostConditions: 
void bag::ArrayLarger()
{
   BagItem* Temp = new BagItem[Max_Size+=5];
   if(Temp == NULL)
   {
      MessageBox(NULL,"Sorry, creating larger array failed", "ERROR!",MB_OK);
   }
   else
   {
      for ( int i = 0; i < Max_Size-5; i++)
      {
         Temp[i] = Item[i];
      }
      delete []Item;
      Item = Temp;
      Temp = NULL;
   }  
}


