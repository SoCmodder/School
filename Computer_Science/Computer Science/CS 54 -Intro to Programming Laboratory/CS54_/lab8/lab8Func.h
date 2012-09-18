/* 
* Author: Elliot Gross
* Date: 2/28/06
* Filename: lab8.cpp
* Instructor: Brian Sea
* Description: This program will change create a program that recieves 
* two integers as a fraction, and prints out them as a fraction and decimal
*/
#ifndef LAB8FUNC_H
#define LAB8FUNC_H
#include <iostream>
using namespace std;

struct fraction //sets the struct
{
	int num;
	int denom;
	int wholePart;
	bool isProper;
};
void greetings(); 
fraction getFraction();
bool multFraction(const fraction& fraction1, const fraction& fraction2, fraction& ans);
bool multFraction(const fraction& fraction1, const fraction& fraction2, float& ans);
bool runAgain();
void goodbye();


#endif
