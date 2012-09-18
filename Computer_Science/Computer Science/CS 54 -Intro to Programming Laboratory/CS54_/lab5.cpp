/*
* Author: Elliot Gross
* Date: 2/7/06
* Filename: lab5.cpp
* Instructor: Brian Sea
* Description: This program will take a phone number, apply an algorithm, and print out
* an answer.
*/

#include <iostream> //allows input and output
#include <string> // allows the use of strings

using namespace std;

const int MULT =8; //sets a constant named MULT to 8

int main()
{

  unsigned long phone_number; // Makes a variable phone number unsigned (no negatives)
  char again;
  
  do
  {
    int digit=0, digit2=0, digit3=0;
    int sum=0, sum2=0, sum3=0;
    int bn=0; // Make sure the bariables = 0, so if run twice it works correctlyf
    
    do
    {   
      cout << "Please enter in your phone number without the dash" << endl;
      cin >> phone_number; // asks for a phone number and sets it to a variable
    }while(phone_number < 1000000 || phone_number > 9999999); 
	// the above line error checks for 7 digits 
    
    
    bn = phone_number * MULT; //multiplies the number by 8
    
   
    while(phone_number != 0) //Condition for the while loop
    {
      digit = phone_number % 10; // sets aside the last digit in the phone number
      sum += digit; // sets that number to sum
      phone_number /= 10; //moves the decimal over in bn
    }
  
    sum += MULT; // adds 8
    cout << sum << endl; // Prints out sum
    
    while (bn != 0) //Condition for the while loop
    {
       digit2 = bn%10; //sets aside the last digit of the bn
       sum2 += digit2; // sets that number to sum2
       bn /= 10; //moves the decimal over in bn
       sum += digit2; //sets that to sum
      
	}  
    
    cout << sum << endl; //Prints out the sum
      
    while( sum > 9) // Condition for if the sum has more than 1 digit
    {
      
      while( sum != 0 ) // Condition for the loop that runs when sum is not 0
      {
        digit3 = sum%10; // sets aside the last digit of sum
        sum3  += digit3; // sets that number to sum 3
        sum /= 10;     // moves the decimal over in sum
      }
      sum = sum3; //sets sum 3 to sum
      cout << sum << endl; //Prints out sum
    }
    
    cout << "Solution: " << sum << endl; // Prints out solution    
    cout << "Would you like to do it again? y/n" << endl; // Asks if you want to repeat
    cin >> again; //Sets input to the variable again
  }while(again == 'y'); //Repeats the do while loop if y is pressed

return 0;
}
