
/*
* Author: Elliot Gross
* Date: 1/31/06
* Filename: lab4.cpp
* Instructor: Brian Sea
* Description: This program will help Bill practice his rounding and divisability
*/

#include <iostream> //input/output
#include <string> //allows the use of strings

using namespace std;


int main()
{
  bool p1=false;
  int check, choice;
  float round_number, round_place, answer;  
  cout << "Welcome to the Miarculous Rounder!\n" << endl;

do
{
  cout << "1. Enter a number for rounding or division" << endl;
  cout << "2. Round number" << endl;
  cout << "3. Perform division" << endl;
  cout << "4. Quit" << endl;
  cout << "What selection would you like to choose?";
  cin >> choice;
  
  if (choice ==1)
  {
      
      cout << "What number would you like to round? \n" ;//input for number
      cin >> round_number; // makes the input the round_number
      p1 = true;
  }
  else if (choice ==2)
  {
    if (p1 == false)
     {
     cout << "No number to round! Please enter in a number to round" << endl;
     }   
    else
    {
        cout << "To what place would you like to round? \n"; 
        // asks user for input
        cin >> round_place; // puts that input to the variable round_place
        answer = round_number/round_place; //moves the decimal over
       if (answer >= 0)
       { 
        answer = answer + .5; // adds .5 to round
        answer = static_cast <int> (answer); // Truncates answer to an int
        answer = answer * round_place; //moves the decimal back
        cout <<"Your rounded number is " << answer << endl << endl; 
        //outputs answer
       }
       else
       {
       answer = answer - .5;
       answer = static_cast <int> (answer);
       answer = answer * round_place;
       cout << "Your rounded number is" << answer << endl << endl;
       }
     }    
  }
  else if (choice==3)
  {
     if (p1 == false)
     {
      cout << "No number to divide! Please enter a number to divide." << endl;
     }
     else
     {
      cout << "What number would you like to check divisibility with?";
      cin >> check;
      cout <<"Your modded number is "<< static_cast<int>(answer)%check << endl;
      cout << endl;
      //mods answer by check
     }
  }
  else if (choice !=4)
  {
    cout << "Please enter in a valid choice"<< endl;
  }
} while (choice !=4);
   
  cout <<"Thank you for using the bestest rounder in the world!"<< endl;
  return 0;
}  
  
