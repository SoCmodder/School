
//#include "resource.h"
#include "stdafx.h"
#include "food.h"
#include <algorithm>


//Programmer: Patrick Keeven
//Class : CS-153
//File : Food.cpp
//Purpose : The definition of aclass to monitor the amount of Calories
//consumed in a day.



     /* default constructor */
	Pocket::Pocket(int initial_size)
	{
		My_Pocket = new Food_Item[initial_size];
		current_size=initial_size;
		no_used=0;
	}

     /* allocate a new, larger pocket */
	Pocket::Pocket(const Pocket& old_pocket)
	{
		My_Pocket = new Food_Item[old_pocket.current_size];
		current_size=old_pocket.current_size;
		no_used = old_pocket.no_used;
		std::copy(old_pocket.My_Pocket, old_pocket.My_Pocket + no_used, My_Pocket);
	}

	Pocket::~Pocket()
	{
		delete [] My_Pocket;
	}

	void Pocket::reserve(int new_size)
	{
		Food_Item *larger_array;
		if(new_size==current_size)
			return;
		if(new_size<no_used)
			new_size=no_used;

		larger_array=new Food_Item[new_size];
		std::copy(My_Pocket, My_Pocket + no_used, larger_array);
		delete [] My_Pocket;
		My_Pocket=larger_array;
		current_size=new_size;
	}



	
	void Pocket::Insert(CString Food_Name, int Calories)
	{
		if(no_used == current_size)
			reserve(no_used+1);
		My_Pocket[no_used].Food_Name = Food_Name;
		My_Pocket[no_used].Calories = Calories;
		++no_used;
	}

    		
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



	CString Pocket::Max_Cal()
	{
		CString name;
		int max;

		if (no_used==0)
			return "No Food in Pocket";
		else 
		{
			max=My_Pocket[0].Calories;
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

	CString Pocket::Least_Cal()
	{
		CString name;
		int min;

		if (no_used==0)
			return "No Food in Pocket";
		else 
		{
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

	int Pocket::Total_Cal()
	{
		int total=0;
		for(int loop = 0; loop<no_used; loop++)
		{
			total+=My_Pocket[loop].Calories;
		}
		return total;
	}

     
   	Food_Item::Food_Item()
	 {
	 }
	 Food_Item::Food_Item(CString Food_Name, int Calories)
	 {
	 }
	 Food_Item::~Food_Item()
	 {
	 }


