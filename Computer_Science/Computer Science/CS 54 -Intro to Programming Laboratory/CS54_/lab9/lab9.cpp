/* 
* Author: Elliot Gross
* Date: 3/7/06
* Filename: lab9.cpp
* Instructor: Brian Sea
* Description: This program will take a phrase and apply the caesar
* cipher to the phrase to "encrypt" it
*/
#include <iostream>
#include "lab9Func.h" //includes lab9Func.h
using namespace std;

int main()
{

	greetings(); //calls the function greetings

	do
	{
		// istream getline
		char phrase[257]; //creates an array
		cout << "Enter your phrase: ";
		cin.getline (phrase,256); // gets the entire line
		cin.sync(); //syncs
		cout << "Your original phrase was " << phrase << endl;
		//prints out the original message
		encryptor(phrase); // calls the encryptor function
		cout << "Your encrypted phrase is " <<phrase << endl;
		//prints out the encrypted message
	}while( runAgain() ); //loop that asks if you want to run again


	goodbye();  //calls function goodbye

	return 0;
}
