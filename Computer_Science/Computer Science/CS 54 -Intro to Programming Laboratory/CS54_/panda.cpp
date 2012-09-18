\
/*
* Author: Elliot Gross
* Date: 1/17/06
* Filename: panda.cpp
* Instructor: Brian Sea
* Description: This program allows you to create a brand new panda!
*/

#include <iostream> //input/output
#include <string> // using strings

using namespace std;

// The number of lemmings that the panda hurt
const int NUM_LEMMINGS = 3;

int main()
{
  //The specs of the panda
  int age, weight;
  string name;
  
  cout << "Welcome to the Great Panda Generator!\n";
  
  // Getting the pandas specs
  cout << "Please enter the Panda\'s name: ";
  cin >> name;
  
  cout << "Please enter the Panda\'s age: ";
  cin >> age;
  
  cout << "Please enter the Panda\'s weight: ";
  cin >> weight;
  
  // Output the panda's specs
  cout << "You have created a panda by the name of " << name
  << " with an age of " << age  << " and a weight of "
  << weight << endl;
  
  cout <<  "It hurt "  << NUM_LEMMINGS << " lemmings. BAD PANDA! BAD!\n";
  
  cout << "Goodbye.\n";
  return 0;
}
