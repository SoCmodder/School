//Matt Ludwikosky  CS53
//HW1 09/07/04
//Purpose: Input 3 specs and run them through formulas to compute answers

#include <iostream>
using namespace std;

int main()
{
   //Initalize variables
   int height, weight, age, tenYearsOver;
   float hatSize, jacketSize, waistSize;

   //Output and input specifications
   cout << "Enter height (in inches): ";
   cin >> height;
   cout << endl << "Enter weight (in pounds): ";
   cin >> weight;
   cout << endl << "Enter age (in years): ";
   cin >> age;

   //Compute hat size
   hatSize = (weight/height) * 2.9;

   //Compute waist size
   waistSize = (weight/5.7);
   
   //Preliminary jacket size computation
   jacketSize = (height * weight)/288;

   // For every 10 years over the age of 30, add 1/8 inch.
   if (age < 30) 
      tenYearsOver = (age - 30)/10;
   else
      tenYearsOver = 0;

   //Jacket size modification
   jacketSize = jacketSize - (tenYearsOver * (1/8));

   //Output of answers
   cout << endl << "Your jacket size is: ";
   cout << jacketSize;

   cout << endl << "Your hat size is: ";
   cout << hatSize;

   cout << endl << "Your waist size is: ";
   cout << waistSize << endl;

   return 0;
}
