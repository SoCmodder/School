//Filename: prog1comment.cpp
//Programmer: Derek Buchheit
//This file describes how we will turn our C++ into assembly language

#include <iostream.h>

int main()
{
	int in_feet, in_inches, total_inches(0), total_feet(0), total_yards(0); 
	//The variable will be represented by the following registers:
	//in_feet = $t0, in_inches = $t1, total_inches = $t2
	//total_feet = $t1 (reused because no longer needed)
	//total_yards = $t3
	
	cout << "When finished, enter 0 for feet and 0 for inches\n";
	do //will make loop called in_loop starting here
	{
		cout << "Enter the number of feet: ";
		cin >> in_feet; //Will get input, then move to $t0
		cout << "Enter the number of inches: ";
		cin >> in_inches; //Will get input, then move to $t1
		//Adds number of inches just inputted to total inches
		total_inches = total_inches + in_inches; 
		//Adds inches from just inputted feet to total inches
		//Here we must 12 * $t0, then add $t0 to $t2
		total_inches = total_inches + (12 * in_feet); 

	} while(in_feet != 0 || in_inches != 0); 
	//Will use 2 bne calls in order to check both do while conditions

	//Computes the values that we will output
	total_feet = total_inches / 12; //load 12 to a temp register, we reuse
	//$t0, then use div to find total_feet
	total_inches = total_inches % 12; //Use rem to find this, store in $t2
	total_yards = total_feet / 3;//load 3 to a temp register $t3, then
	//use div to find total_feet
	total_feet = total_feet % 3; //Use rem to find this, store in $t1
	
	//To output our results we will move our output to $a0, then do our li and syscall
	//Must be done separate for all variables
	cout << "Total Distance: "<< total_yards << " yards, " << total_feet << " feet, "
	     << total_inches << " inches\n";

	return 0;
}