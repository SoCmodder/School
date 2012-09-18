//Filename: CS234prog1.cpp
//Programmer: Derek Buchheit
//This program asks for the user to input measurements in feet and inches. It then displays
//the total of all the inputs in yards, feet, and inches. Note that the user enters 0 for 
//both feet and inches when they are finished putting in measurements. 
#include <iostream.h>

int main()
{
	int in_feet, in_inches, total_inches(0), total_feet(0), total_yards(0); 
	//in_feet and in_inches store the inputed values
	//tot_inches, tot_feet, tot_yards store the total values
	
	cout << "When finished, enter 0 for feet and 0 for inches\n";
	do
	{
		cout << "Enter the number of feet: ";
		cin >> in_feet;
		cout << "Enter the number of inches: ";
		cin >> in_inches;
		//Adds number of inches just inputted to total inches
		total_inches = total_inches + in_inches; 
		//Adds inches from just inputted feet to total inches
		total_inches = total_inches + (12 * in_feet); 

	} while(in_feet != 0 || in_inches != 0);

	//Computes the values that we will output
	total_feet = total_inches / 12;
	total_inches = total_inches % 12;
	total_yards = total_feet / 3;
	total_feet = total_feet % 3;
	cout << "Total Distance: "<< total_yards << " yards, " << total_feet << " feet, "
	     << total_inches << " inches\n";

	return 0;
}