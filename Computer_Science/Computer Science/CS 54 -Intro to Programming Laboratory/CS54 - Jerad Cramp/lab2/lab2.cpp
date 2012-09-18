// Programmer: robertoMurillo   Date: 083105

// File: lab2.cpp          Class: CS 54 D

// Description: A program for demonstrating some 

//   common programming errors.

//   compile with g++ -W -Wall -s -pedantic-errors lab2.cpp -o lab2

 
 
#include <iostream>
using namespace std; 
int main()
   
{
     // program constant
     
       const float PI = 3.14;
       
    // program variables
          
       float diameter, radius, area;
           
    // print a welcome message
               
       cout << "Welcome to CS 54's Pizza Area Calculation Wizard." << endl;
                                
    // get user input
                     
       cout << "Enter the diameter of your pizza in inches: ";
                       
       cin  >> diameter;
                               
   // do calculations
                            
       radius = diameter / 2;
                              
       area = PI * radius * radius;
                                
   // display output
                                   
   cout << "The area of your " << diameter << "in pizza is "
                                     
        << area << "sq in." << endl;
                                            
   return 0;                                             
}
