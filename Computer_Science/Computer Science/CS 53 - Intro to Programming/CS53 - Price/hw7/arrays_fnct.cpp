/* programmer: robertoMurillo   date: 10/16/05 *
 * file: arrays_fnct.cpp             class: cs53    *
 * purpose: building three arrays to convert a *
 * random number into three characters.        */

#include "arrays.h"
#include <iostream>
#include <ctime>
using namespace std;

/*************** FUNCTION DEFINITIONS ***************/

// prompts user for a seed. if no seed, uses default time clock
// Pre: none
// Post: random # generator seeded and array is given values of
// random numbers
void seeding_function( long array1[ ] )
{
  char choice;
  long seed;

  do
  {
  cout << "Would you like to enter a seed(y/n): ";
  cin >> choice;
  } while( choice != 'Y' && choice != 'y' && choice != 'n'
           && choice != 'N');

  if ( choice == 'y' || choice == 'Y' )
  {
    cout << "Enter the seed: ";
    cin >> seed;
    cout << endl;

    srand(seed); // seeds with user-defined seed
  }

  else
    srand(time(NULL)); // seeds with timeclock if seed not entered

  for ( int i = 0; i < SIZE; i++ )
      array1[i] = rand();

  return;
}

// mods the elements into numbers in the range 97-122
// Pre: array1 must have been filled with random numbers
// Post: values of array1 are modded between 97-122
void modifying_function( long array1[ ] )
{
  for ( int i = 0; i < SIZE; i++ )
    array1[i] = array1[i]%(MAX - MIN + 1) + MIN;

  return;
}

// changes the numbers modded into characters by way of ASCII
// Pre: values in array1 must be between 97-122
// Post: values in array1 are translated to characters
void ascii_translate( long array1[ ], char array2[ ] )
{
  for ( int i = 0; i < SIZE; i++ )
    array2[i] = array1[i];

  return;
}

// searches for all letters in the defined positions
// Pre: array2 must have been given values from array1
// Post: finds three specific locations in array2 and assigns them
// to array3 positions 0 1 and 2. checks for all occurences of the
// three locations in order in array2
void find_positions( char array2[ ], char array3[ ] )
{
  // assigns position 52 22 and 18 to array3
  array3[0] = array2[52];
  array3[1] = array2[22];
  array3[2] = array2[18];

  // finds each occurence of the letters in position 52 22 and 18 and
  // prints it to the screen
  for ( int i = 0; i < (SIZE - 2); i++ )
    if ( array2[i] == array3[0] && array2[i + 1] == array3[1]
         && array2[i + 2] == array3[2] )
    {
      cout << "Found at: " << i << " " << endl;
      cout << "Three letters: " << array3[0] << array3[1] << array3[2]
           << endl;
    }

  return;
}

// checks for any numbers in the array that are prime
// Pre: the number is positive
// Post: returns false if its not prime, else it returns true
bool is_prime( const long number )
{
  bool prime = true;

  for ( int i = 2; i * i < number; i++ )
    if ( number%i == 0 && number != 2 )
      prime = false;

  return prime;
}

//  changes numbers to uppercase
// Pre: array2 must be filled with lowercase characters
// Post: indices in array2 are checked if they are prime or not, if they
//       are, they are made uppercase
void uppercase( char array2[ ] )
{
  for ( int i = 0; i < SIZE; i++ )
    if ( is_prime(i) )
      array2[i] -= 32;

  return;
}

// prints out the uppercase letters in reverse order
// Pre: array2 must be checked for prime indices
// Post: outputs to the screen the values, in reverse, of the prime
//       indices
void reverse_uppercase( char array2[ ] )
{
  for ( int i = SIZE-1; i >= 0; i-- )
  {
    if ( array2[i] < MIN )
      cout << array2[i];
  }
  cout << endl;

  return;
}

// gives the user a quit message
// Pre: none
// Post: prints out to the screen a goodbye message
void quit()
{
  cout << endl;
  cout << "Thanks!" << endl;
}

/*************** FUNCTION DEFINITIONS ***************/
