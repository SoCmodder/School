#ifndef FOOD_H
#define FOOD_H

///////////////////////////////////////////////////////////////////////////
//Programmer: A model student
//Class : CS-153
//File : Food.h
//Purpose : A class to monitor the amount of Calories consumed in a day.
///////////////////////////////////////////////////////////////////////////
int DEFAULT_CAPACITY=10; 
class Food_Item 
{
public:

     Food_Item();
     Food_Item(CString Food_Name, int Calories);
     ~Food_Item();

//private:

     CString Food_Name;
     int Calories;

};
class Pocket
{
public:

     /* default constructor */
     Pocket(int inital_size=DEFAULT_CAPACITY);

     /* allocate a new, larger pocket */
     Pocket(const Pocket& old_pocket);

     ~Pocket();	//default destructor, releases dynamic memory

	 void reserve (int new_size);

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