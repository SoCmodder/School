/* 
* Author: Elliot Gross
* Date: 2/28/06
* Filename: lab8.cpp
* Instructor: Brian Sea
* Description: This program will change create a program that recieves 
* two integers as a fraction, and prints out them as a fraction and decimal
*/
#include "lab8Func.h" //includes lab8Func.h
#include <iostream>
using namespace std;

void greetings()
{
	cout << endl << "Welcome to the fraction multiplier!" << endl << endl;
	return;
}

fraction getFraction()
{
	char junk;
	//do not allow 0 to be entered for the denominator
	fraction fraction1;
	do
	{
		cout << "Enter the fraction in the form of X/Y: ";
		cin >> fraction1.num >> junk >> fraction1.denom;
		if(fraction1.denom == 0)
		cout << "The denominator must be non-zero." << endl;
	}while(fraction1.denom == 0);
	//push the negative sign to the numerator, if necessary
	if(fraction1.denom < 0)
	{
		fraction1.denom *= -1;
		fraction1.num *= -1;
	}
	return fraction1;
}

bool multFraction(const fraction& fraction1, const fraction& fraction2, fraction& ans)
{
	
	bool ret = true; //indicates whether or not the result is proper
	 //perform the multiplication
	ans.num = fraction1.num * fraction2.num;
	ans.denom = fraction1.denom * fraction2.denom;
	//set the flag if the result is improper
	if(ans.num > ans.denom)
	ret = false;
	return ret;
}

bool multFraction(const fraction& fraction1, const fraction& fraction2, float& ans)
{
	bool ret = true; //indicates whether or not the result is proper
	//perform the multiplication
	ans = static_cast<float>(fraction1.num*fraction2.num)/
		(fraction1.denom*fraction2.denom);
	//set the flag if the result is improper
	if(ans > 1 || ans < -1)
	ret = false;
	return ret;
}

bool runAgain()
{
	bool ret = false;
	string ip;
	cout << endl;
	do
	{
		cout << "Would you like to run the program again (y or n)? ";
		cin >> ip;
	}while(ip != "y" && ip != "Y" && ip != "n" && ip != "N");
	if(ip == "y" || ip == "Y")
	ret = true;
	return ret;
}

void goodbye()
{
	cout << endl << "Thanks!" << endl << endl;
	return;
}
