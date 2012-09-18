/* intructor: price              class: cs54d   *
 * file: func.cpp                               *
 * purpose: function file for cstring program.  */

#include <iostream>
#include <cstring>
#include "func.h"
using namespace std;

/*************** FUNCTION DEFINITIONS ***************/

void welcome()
{
  cout << "Welcome to CS 54's C-string lab." << endl;
  cout << endl;
  
  return;
}

void farewell()
{
  cout << endl;
  cout << "Thanks for using the program." << endl;
  
  return;
}

void get_string( char cArray1[ ], const unsigned int SIZE )
{  
  cout << "Enter a string: ";
  cin.getline (cArray1, SIZE);
  
  return;
}

char get_char()
{
  char choice;
  
  cout << "Enter a character: ";
  cin >> choice;
  
  return choice;
}

void capitalize( char cArray2[ ], const unsigned int length, char choice )
{
  for (int i = 0; i < SIZE; i++)
    if ( cArray2[i] == choice )
      cArray2[i] = toupper(cArray2[i]);
      
  return;
}

void display_results( char const cArray1[ ], const char cArray2[ ], 
                      const unsigned int compare )
{
  cout << "\"" << cArray1 << "\" is lexographically less than \"" 
            << cArray2 << "\".";   

  return;
}

/*************** FUNCTION DEFINITIONS ***************/   
