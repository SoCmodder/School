/* 
* Author: Elliot Gross
* Date: 3/7/06
* Filename: lab9Func.cpp
* Instructor: Brian Sea
* Description: This program will take a phrase and apply the caesar
* cipher to the phrase to "encrypt" it
*/
#include "lab9Func.h" //includes lab9Func.h
#include <iostream>
using namespace std;

void greetings () // function definition of greetings
{
      cout <<"Welcome to the Caesar Cipher!\n\n";
}

void encryptor(char phrase[], bool encrypt) 
// function definition of encryptor
{
	for (int i= 0; phrase[i] != '\0'; i++)
	// checks to see if you are at the end of the array
	{
		if (isalpha(phrase[i])) //checks if it's a letter
		{
			if(encrypt == true)//code runs if true
			{
				encryptor(phrase[i]); //calls encryptor
			}
			else
				decryptor(phrase[i]); // calls decryptor
		}
	}
   	
	return;
}

void encryptor(char &a) // fucntion definition of encryptor
{
	if (isupper(a)) //checks if uppercase
	{
		a = (a - 'A' + SHIFT_SIZE) %26 + 'A';
		//turns a into a number adds 4 to it and puts back to letter
		// for uppercase
	}
	else //otherwise runs this code
	{
		a = (a - 'a' + SHIFT_SIZE) %26 + 'a';
		//turns a into a number adds 4 to it and puts back to letter
		// for lower case
	}
	
   	return;
}


void decryptor(char &a)
{
	if (isupper(a))
	{
		a = (a - 'A' - SHIFT_SIZE) %26 + 'A';
		//turns a to a number subtracts 4 to it and puts back to letter
		// for uppercase
	}
	if (islower(a))
	{
		a = (a - 'a' - SHIFT_SIZE) %26 + 'a';
		//turns a to a number subtracts 4 to it and puts back to letter
		// for lower case
	}
	
	return;
}

bool runAgain() // function definition of runAgain
{
	bool rtn = true;
	char choice;
			  do
              {
                  cout << "Would you like to enter another phrase? (Y/N)";
                  cin >> choice;
				  cin.ignore(); //syncs
                  
                  if (choice != 'y' && choice != 'Y' && choice != 'n' &&
                                    choice != 'N')
                  {
                      cout << "\nERROR: Please enter a 'Y' or 'N'.\n\n";
                  }
              }while ( choice != 'y' && choice != 'Y' && choice != 'n' &&
                                    choice != 'N');
			  if (choice == 'y' || choice == 'Y')
			  {
				  return rtn;
			  }
			  else
				  rtn = false;
    return rtn;
	// asks if you want to run program again
}

void goodbye() // function definition of goodbye
{
	cout << "Thanks for using our Caesar Cipher!\n";
}


