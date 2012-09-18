/* 
* Author: Elliot Gross
* Date: 2/14/06
* Filename: lab6.cpp
* Instructor: Brian Sea
* Description: This program will change lab5 code into code that will do
* the same thing, but will use functions instead
*/

#include <iostream> // allows for input and output
#include <string> // allows for the use of strings

using namespace std;

const int MULT = 8;

    
void greetings();
unsigned int promptPhoneNumber();
bool isValidPhoneNumber(unsigned int phone);
unsigned int sumDigits(unsigned int phone);
void goodbye();
bool runAgain();

int main()
{

unsigned int sum, phone;

	greetings(); //calls the function greetings
	do
	{
	    do
	    {    
			phone = promptPhoneNumber();  // gets the phone number      
		}while( !isValidPhoneNumber(phone)); //checks for 7 digits
		sum = MULT + sumDigits(phone) + sumDigits(phone*MULT);
		// adds MULT, digits of phone and digits of phone * MULT
		cout << "Your first sum is equal to: " << sum << endl;
		// outputs sum
		while (sum > 9) // runs if 2 digits 
		{
			sum = sumDigits(sum); //adds up digits of sum
			cout << "Your second sum is equal to: " << sum << endl;
			// outputs sum
		}        
		cout << "Your final sum is equal to: " << sum << endl;
		//outputs sum
	}while( runAgain() ); //loop that asks if you want to run again
goodbye();  //calls function goodbye
return 0;
}    

void greetings () // function definition of greetings
{
      cout <<"Welcome to the Magic 8 Calculator!\n\n";
}

unsigned int promptPhoneNumber() // function definition
{
      unsigned int phonenum; 
      cout<<"Please enter your 7 digit telephone number: ";
      cin >> phonenum;
      return phonenum;
	  // gets phone number
} 
bool isValidPhoneNumber(unsigned int phone)// function definition
{
    bool rtn= true;
    if ( phone > 9999999 || phone < 1000000)
    {
      cout << "\nERROR: This does not appear to be a valid number!\n\n";
      return rtn = false;
    }
return rtn;

// Checks to see that phone number is 7 digits
}
unsigned int sumDigits(unsigned int num)
{
	unsigned int sum=0;
	while (num !=0) 
	{
		sum += num % 10; //rips off last digit and adds to sum
		num /= 10; // moves to the next digit
	}            
	return sum;
         // Adds digits of num
}
bool runAgain() // function definition of runAgain
{
	bool rtn = true;
	char choice;
			  do
              {
                  cout << "Would you like to enter another phone number? (Y/N)";
                  cin >> choice;
                  
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
	cout << "Thanks for using our Magic 8 calculator!\n";
}
