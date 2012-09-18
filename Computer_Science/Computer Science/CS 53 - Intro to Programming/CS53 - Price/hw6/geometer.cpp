/* programmer: robertoMurillo    date: 10/5/05 *
 * file: geometer.cpp                          *
 * purpose: walk-in-geometer script for Bob.   *
 * this file includes the main program.        */
 
#include "geometer.h"
#include <iostream>
using namespace std;

int main()
{
  char choice; // users choice from the menu
  welcome();
  
  do
  {
  choice = displayMenu(); 
  menuCases(choice);
  } while( choice != '6');
  
  exit();

return 0;
}
