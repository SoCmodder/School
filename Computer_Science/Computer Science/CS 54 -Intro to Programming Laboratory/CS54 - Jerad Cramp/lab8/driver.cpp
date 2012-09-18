// Programmer: Jerad Cramp       Date: 10.08.04
// File: driver.cpp              Class: CS 54
// Instructor: N/A
// Description: Driver file for lab8, using structs
//   to manipulate complex numbers.

#include <iostream>
#include "complex.h"
#include "func.h"

using namespace std;

int main()
{
   // program variables
   complex com1;
   complex com2;

   // welcome the user
   welcome();

   do {
      // initialize the variables
      complex_read( com1 );
      complex_read( com2 );

      // display the comlex numbers
      complex_print( "complex number 1: ", com1 );
      complex_print( "complex number 2: ", com2 );

      // dislay the results of the mathematical operations
      complex_print( "addition equals: ", complex_add( com1, com2 ) );
      complex_print( "subtraction equals: ", complex_sub( com1, com2 ) );
      complex_print( "multiplication equals: ", complex_mul( com1, com2 ) );
   } while( again() == 'Y' );

   // display the farewell
   farewell();

   return 0;
}
