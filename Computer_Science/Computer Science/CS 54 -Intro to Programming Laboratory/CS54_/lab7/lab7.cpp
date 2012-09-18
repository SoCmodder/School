/* 
* Author: Elliot Gross
* Date: 2/21/06
* Filename: lab7.cpp
* Instructor: Brian Sea
* Description: This program will change create a program that recieves 
* two integers as a fraction, and prints out them as a fraction and decimal
*/

#include <iostream> // allows for input and output
#include <string> // allows for the use of strings

using namespace std;

void goodbye();
bool runAgain();
void greetings();
void getFraction(int& numer, int& denom);
bool multFraction(int n1, int d1,int n2, int d2,int &numer ,int &denom);
bool multFraction (int n1, int d1, int n2, int d2, float answer);

int main ()
{
	int n1 =0, d1 =0, n2=0, d2=0;
	int numer=0, denom =0;
	float answer;

	greetings(); //calls the function greetings
	do
	{
		
		getFraction(n1, d1); //calls the overloaded function getFraction
		getFraction(n2, d2); //calls the overloaded function getFraction
		multFraction(n1, d1, n2, d2, numer, denom); // calls multFraction
		multFraction(n1, d1, n2, d2, answer); //calls multFraction again


	}while( runAgain() ); //loop that asks if you want to run again
	goodbye();  //calls function goodbye
	return 0;
}


void greetings () // function definition of greetings
{
      cout <<"Welcome to the Magic Fraction Calculator!\n\n";
}

void getFraction (int &numer, int &denom)
//function definition for getFraction
{
	char slash = '/'; 
	
	do
	{
		cout <<"Please enter a fraction in the form of "
			 <<"X/Y where x and y are integers." << endl;
		cin >> numer >> slash >> denom; //parses up the fraction that was inputed
		if (denom == 0) //error checks for a 0 in denominator
		{
			cout << "ERROR: 0 in the denominator!" << endl;
		}

		if (denom < 0) //error checks for negative in the denominator
		{
			numer *= -1;
			denom *= -1;
		}
		if (numer > denom) // error checks for improper fractions
		{
			cout << "ERROR: Improper fraction!" << endl;
		}
	

    }while (denom == 0 || numer > denom); 
	//loops while fraction is not proper
	
	

}
bool multFraction (int n1, int d1,int n2, int d2,int &numer ,int &denom)
// funtion definition of multFraction
{
	bool rtn = true;

	numer = n1 * n2; //multiplies numerators
	denom = d1 * d2; // multiplies denominators
	cout <<"Your multiplied fraction is " 
		 << numer << "/" << denom << endl;
	if ( numer < denom && denom != 0) //checks if proper
		return rtn;
	else //runs if improper
		rtn = false;
	
	return rtn;


}
bool multFraction (int n1, int d1, int n2, int d2, float answer)
// function definition for multFraction
{
	bool rtn = true;
	float numer = static_cast <float> (n1*n2); //static cast to float
	answer = numer /(d1*d2); //returns float because of data promotion
	cout <<"Your multiplied fraction in decimal form is "
		 << answer << endl;

	return rtn;

}
bool runAgain() // function definition of runAgain
{
	bool rtn = true;
	char choice;
			  do
              {
                  cout << "Would you like to enter another fraction? (Y/N)";
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
	cout << "Thanks for using our Magic Fraction calculator!\n";
}
