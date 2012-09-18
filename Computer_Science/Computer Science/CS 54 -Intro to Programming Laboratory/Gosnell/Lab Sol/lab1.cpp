//-----------------------------------------------------------
// Programmer: Your Name Here         Student ID: 999999
// Lab: #1, Lab Basics/Math Ops.      Filename: lab1.cpp
// Date: 09/04/02                     Class: CS 54, Section D
//-----------------------------------------------------------
// Program Description:
//  The program does a few simple math operations so we can verify we're
//  able to get a page, edit it, compile the code, etc.            

//This program is heavily commented to help you understand what all
// of the statements do.  Anything after // in a line is not read
// by the compiler and will not affect the code.

//every program starts with an include section
#include <iostream>
using namespace std; //to use standard namespace cin, cout, endl, ...

//every program will have an int main() section 
int main()
{	//these 'curly-brackets' enclose the int main() function
// 2 numbers entered by user to do math operations on.
   float fFirstNum, fSecondNum;        
   
//output to the user the type of input required
   cout << "Please enter 2 numbers, separated by a blank or 'enter' and"
        << " don't make the second one zero" << endl;

//input the two numbers from the user
   cin >> fFirstNum >> fSecondNum;
  
//compute the standard operations on the two numbers entered
//and output the results
   cout << fFirstNum << " + " << fSecondNum << " = " 
        << fFirstNum + fSecondNum << endl;

   cout << fFirstNum << " - " << fSecondNum << " = " 
        << fFirstNum - fSecondNum << endl;

   cout << fFirstNum << " * " << fSecondNum << " = " 
        << fFirstNum * fSecondNum << endl;

   cout << fFirstNum << " / " << fSecondNum << " = " 
        << fFirstNum / fSecondNum << endl;

//really no point to this output other than letting the user know we've finished
   cout << " Bye " << endl;

//returning 0 lets the operating system (or whatever calls this program)
//  know it finished correctly
   return 0;
}	//these 'curly-brackets' enclose the entire int main() function
