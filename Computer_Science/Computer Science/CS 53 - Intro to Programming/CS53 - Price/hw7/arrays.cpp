/* programmer: robertoMurillo   date: 10/16/05 *
 * file: arrays.cpp             class: cs53    *
 * purpose: building three arrays to convert a *
 * random number into three characters.        */

#include "arrays.h"
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
  // declares all arrays used
  long array_random[SIZE];
  char array_ascii[SIZE];
  char array_find[3];

  // program is seeded, modded between 97-122 and then translated to chars
  seeding_function( array_random );
  modifying_function ( array_random );
  ascii_translate( array_random, array_ascii );

  // locates positions 52 22 and 18 in second array, assigns them to
  // positions 0 1 and 2 respectively in the third array. then, after
  // it has checked for prime indices, it prints out in reverse order
  // the values of the prime indeces
  find_positions( array_ascii, array_find );
  uppercase( array_ascii );
  reverse_uppercase ( array_ascii );

  // quit message
  quit();

 return 0;
}




