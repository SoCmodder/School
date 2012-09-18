#ifndef FOOD_H
#define FOOD_H

///////////////////////////////////////////////////////////////////////////
//Programmer: Patrick Keeven, Robert Graham
//Class : CS-153
//File : Food.h
//Purpose : A class to monitor the amount of Calories consumed in a day.
///////////////////////////////////////////////////////////////////////////


//Food_Item
//Description: Default Constructor
//PRE: None  
//POST: Food_Item is created
//Food_Item
//Description: Copy Constructor
//PRE: Calories>0
//POST: Item created has Food_Name and Calories
//~Food_Item
//Description: Default Destructor
//PRE: None
//POST: Object is destroyed

int const DEFAULT_CAPACITY=10; 
class Food_Item 
{
public:


     Food_Item();
	 
	 Food_Item(CString Food_Name, int Calories);

	 ~Food_Item();

     CString Food_Name;
     int Calories;

};


//Pocket
//Description: Default constructor 
//Pocket
//Description: Allocate a new, larger pocket 
//~Pocket
//Description: Default destructor, releases dynamic memory
//reserve
//Description: Handles displaying the list box
//Pre: listing is a control variable assigned to a list
//     box on the GUI
//Display
//Description: A food_item s added to pocket
//PRE: none
//POST: A Pocket with name Food_Name, and Calories is aded to the pocket
//Remove
//Description: This function calculates the food with the most calories
//PRE: The Pocket Has food in it
//POST: A string of the name of the food with the most calories is returned 
//Max_Cal
//Description: This function calculates the food with the least calories
//PRE: The Pocket Has food in it
//POST: A string of the name of the food with the least calories is returned
//Least_Cal
//Description: Function calculates total calories
//POST: the total calories are returned

class Pocket
{
public:

     Pocket(int inital_size=DEFAULT_CAPACITY);
     
     Pocket(const Pocket& old_pocket);

     ~Pocket();	

	 void reserve (int new_size);
	  	 
	 void Display(CListBox & listing );

	 void Insert(CString Food_Name, int Calories);

     bool Remove(CString Food_Name);

	 CString Max_Cal();
	 
	 CString Least_Cal();
     
	 int Total_Cal();
	      
private:

	 Food_Item *My_Pocket;
     int no_used; 
     int current_size; 

};

#endif