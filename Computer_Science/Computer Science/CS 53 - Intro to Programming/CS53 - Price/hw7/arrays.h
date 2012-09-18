/* programmer: robertoMurillo   date: 10/16/05 *
 * file: arrays.h             class: cs53      *
 * purpose: building three arrays to convert a *
 * random number into three characters.        */

#ifndef ARRAYS_H
#define ARRAYS_H


/*************** GLOBAL CONSTANTS ***************/

const int SIZE = 500;
const int MAX = 122;
const int MIN = 97;

/*************** GLOBAL CONSTANTS ***************/

/*************** PROTOTYPES ***************/

// prompts user for a seed. if no seed, uses default time clock
// Pre: none
// Post: random # generator seeded and array is given values of
// random numbers
void seeding_function( long array1[ ] );

// mods the elements into numbers in the range 97-122
// Pre: array1 must have been filled with random numbers
// Post: values of array1 are modded between 97-122
void modifying_function( long array1[ ] );

// changes the numbers modded into characters by ASCII
// Pre: values in array1 must be between 97-122
// Post: values in array1 are translated to characters
void ascii_translate( long array1[ ], char array2[ ] );

// searches for all letters in the defined positions
// Pre: array2 must have been given values from array1
// Post: finds three specific locations in array2 and assigns them
// to array3 positions 0 1 and 2. checks for all occurences of the
// three locations in order in array2
void find_positions( char array2[ ], char array3[ ] );

// checks for any numbers in the array that are prime
// Pre: the number is positive
// Post: returns false if its not prime, else it returns true
bool is_prime( const long number );

//  changes numbers to uppercase
// Pre: array2 must be filled with lowercase characters
// Post: indices in array2 are checked if they are prime or not, if they
//       are, they are made uppercase
void uppercase( char array2[ ] );

// prints out the uppercase letters in reverse order
// Pre: array2 must be checked for prime indices
// Post: outputs to the screen the values, in reverse, of the prime
//       indices
void reverse_uppercase( char array2[ ] );

// gives the user a quit message
// Pre: none
// Post: prints out to the screen a goodbye message
void quit();

/*************** PROTOTYPES ***************/

#endif
