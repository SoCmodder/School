/* intructor: price              class: cs54d   *
 * file: func.h                                 *
 * purpose: header file for cstring program.    */

#ifndef FUNC_H
#define FUNC_H

/*************** CONSTANTS ***************/

const int SIZE = 256;

/*************** CONSTANTS ***************/

/*************** PROTOTYPES ***************/

void welcome(); // welcome message

void farewell(); // goodbye message

// collects string from user
void get_string( char cArray1[ ], const unsigned int SIZE );

// asks user to input a character
char get_char();

// capitalizes all instances of the character user input
void capitalize( char cArray2[ ], const unsigned int length, char choice );

// displays difference of two arrays
void display_results( char const cArray1[ ], const char cArray2[ ],
                      const unsigned int compare );

/*************** PROTOTYPES ***************/   

#endif
