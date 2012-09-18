


//Programmer: Patrick Keeven, Robert Graham
//Class : CS-153
//File : Food.cpp
//Purpose : The definition of a class to monitor the amount of Calories
//          consumed in a day.

#include "stdafx.h"
#include "food.h"
#include <algorithm>   //copy function



//Description: default constructor 
//Pre: initial_size must be an greater than zero
//Post: current_size is set to initial_size
//		an array of type Food_Item is allocated to My_Pocket
	Pocket::Pocket(int initial_size)
	{
		My_Pocket = new Food_Item[initial_size];
		current_size=initial_size;
		no_used=0;
	}

//PRE: old_pocket points to a valid array
//POST: My_Pocket is set to old_pocket with a larger size

	Pocket::Pocket(const Pocket& old_pocket)
	{
		My_Pocket = new Food_Item[old_pocket.current_size];
		current_size=old_pocket.current_size;
		no_used = old_pocket.no_used;
		std::copy(old_pocket.My_Pocket, old_pocket.My_Pocket + no_used, My_Pocket);

	}
//PRE: Default Destructor
//POST: Deallocates memory given to My_Pocket
	Pocket::~Pocket()
	{
		delete [] My_Pocket;
	}
//Description: A function to allocate memory for a dynamic array.
//PRE: none
//POST: My_pocket array is reallocated to the size of newsize
	void Pocket::reserve(int new_size)
	{
		Food_Item *larger_array;
		if(new_size==current_size)//checks to see that array needs to be resized
			return;
		if(new_size<no_used)		//checks to see if new_size is < no_used
			new_size=no_used;

		larger_array=new Food_Item[new_size];
		std::copy(My_Pocket, My_Pocket + no_used, larger_array);
		delete [] My_Pocket;
		My_Pocket=larger_array;
		current_size=new_size;
	}

//Description: A food_item s added to pocket
//PRE: none
//POST: A Pocket with name Food_Name, and Calories is aded to the pocket
	
	void Pocket::Insert(CString Food_Name, int Calories)
	{
		if(no_used == current_size)
			reserve(no_used+1);
		My_Pocket[no_used].Food_Name = Food_Name;
		My_Pocket[no_used].Calories = Calories;
		++no_used;
	}

//Description: Removes a food item with a given name from the pocket
//Pre: Food_Name is a food already int the pocket
//POST: The first item with name Food_Name    		
	bool Pocket::Remove(CString Food_Name)
	{
		int index;

		index = 0;

		while ((index < no_used) && (My_Pocket[index].Food_Name !=Food_Name))
			++index;

		if(index == no_used)
			return false;

		--no_used;
		My_Pocket[index] = My_Pocket[no_used];
		return true;
	}


//Description: This function calculates the food with the most calories
//PRE: The Pocket Has food in it
//POST: A string of the name of the food with the most calories is returned
	CString Pocket::Max_Cal()
	{
		CString name;
		int max;

		if (no_used==0)
			return "No Food in Pocket";
		else 
		{
			max=My_Pocket[0].Calories;
			name=My_Pocket[0].Food_Name;
			for(int loop=0; loop<no_used; loop++)
			{
				if (My_Pocket[loop].Calories > max)
				{
                    name=My_Pocket[loop].Food_Name;
					max=My_Pocket[loop].Calories;
				}
			}
		}
		return name;
	}
//Description: This function calculates the food with the least calories
//PRE: The Pocket Has food in it
//POST: A string of the name of the food with the least calories is returned

	CString Pocket::Least_Cal()
	{
		CString name;
		int min;

		if (no_used==0)
			return "No Food in Pocket";
		else 
		{
			name=My_Pocket[0].Food_Name;
			min=My_Pocket[0].Calories;
			for(int loop=0; loop<no_used; loop++)
			{
				if (My_Pocket[loop].Calories < min)
				{
                    name=My_Pocket[loop].Food_Name;
					min=My_Pocket[loop].Calories;
				}
			}
		}
		return name;
	}

//Description: Function calculates total calories
//POST: the total calories are returned
	int Pocket::Total_Cal()
	{
		int total=0;
		for(int loop = 0; loop<no_used; loop++)
		{
			total+=My_Pocket[loop].Calories;
		}
		return total;
	}

//Description: Handles displaying the list box
//Pre: listing is a control variable assigned to a list
//     box on the GUI
 void Pocket::Display(CListBox & listing ) 
{ 
     char temp[20];                                // used to pass a value to the ListBox 
     listing.ResetContent(); 
	 for( int i = 0; i < no_used; ++i ) 
     { 
		 listing.AddString(My_Pocket[i].Food_Name + " calories, " +itoa(My_Pocket[i].Calories,
			 temp, 10));
		
     } 
} 

//Description: Default Constructor
//PRE: None  POST: Food_Item is created     
   	Food_Item::Food_Item()
	 {
	 }
//Description: Copy Constructor
//PRE: Calories>0
//POST: Item created has Food_Name and Calories
	 Food_Item::Food_Item(CString Food_Name, int Calories)
	 {
	 }
	
//Description: Default Destructor
//PRE: None
//POST: Object is destroyed
	 Food_Item::~Food_Item()
	 {
	 }



