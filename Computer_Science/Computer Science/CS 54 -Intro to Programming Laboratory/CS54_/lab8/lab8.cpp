/* 
* Author: Elliot Gross
* Date: 2/28/06
* Filename: lab8.cpp
* Instructor: Brian Sea
* Description: This program will change create a program that recieves 
* two integers as a fraction, and prints out them as a fraction and decimal
*/
#include <iostream>
#include "lab8Func.h" //includes lab8Func.h
using namespace std;

int main()
{
	bool isProper = false;
	fraction fraction1, fraction2, ans;
	float result;
	//send out a greetings
 
	greetings();
	do 
	{
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		//prompt for the fractions to use
		cout << "First Fraction:" << endl;
		fraction1 = getFraction();	// calls getFraction 
		cout << endl << "Second Fraction:" << endl;
		fraction2 = getFraction();
		//perform the multiplication
		isProper = multFraction(fraction1, fraction2, ans);
		multFraction(fraction1, fraction2, result);
		//output the results
		cout << endl << "Results:" << endl;
		cout << fraction1.num << "/" << fraction1.denom << " * "
			<< fraction2.num << "/" << fraction2.denom
			<< " = " << ans.num << "/" << ans.denom;
		if(!isProper)
		cout << " (improper) ";
		else
		cout << " ";
		cout << " = " << result << endl;
		//prompt to run again
	}while(runAgain());
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
	//say your goodbyes
	goodbye();
	return 0;
}


