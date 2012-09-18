
/*
* Author: Elliot Gross
* Date: 1/24/06
* Filename: lab3.cpp
* Instructor: Brian Sea
* Description: This program will help Bill practice his rounding and divisability
*/

#include <iostream> //input/output
#include <string> //allows the use of strings

using namespace std;

int main()
{
  float round_number, answer, round_place;
  int check;
  cout << "Welcome to the Miarculous Rounder!\n" ;
  cout << "What number would you like to round? \n" ;//input for number
  cin >> round_number; // makes the input the round_number
  cout << "To what place would you like to round? \n"; // asks user for input
  cin >> round_place; // puts that input to the variable round_place
  cout << "What number would you like to check divisibility with?";
  cin >> check;
 
  answer = round_number/round_place; //moves the decimal over
  answer = answer + .5; // adds .5 to round
  answer = static_cast <int> (answer); // Truncates answer to an int
  answer = answer * round_place; //moves the decimal back
  cout <<"Your rounded number is " << answer << endl; //outputs answer    
  cout <<"Your modded number is "<< static_cast<int>(answer)%check << endl;
  //mods answer by check
  cout <<"Thank you for using the bestest rounder in the world!"<< endl;
  return 0;
}  
  
