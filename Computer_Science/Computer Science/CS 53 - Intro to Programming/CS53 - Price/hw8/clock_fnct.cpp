/* programmer: robertoMurillo   date: 10/24/05 *
 * file: clock_fnct.cpp                        *
 * purpose: file has all of the functions for  *
 * the timing sort program.                    */

#include "clock.h"
#include <ctime>
#include <iostream>
using namespace std;

/*************** FUNCTIONS ***************/

// welcome message
// pre: none
// post: outputs welcome message to the screen
void welcome()
{
  cout << "Hello and welcome to the sort timer."  << endl << "If I am"
       << " correct, then selection sort should take less time than "
       << "bubble sort." << endl;
  cout << endl;
  return;
}

// goodbye message
// pre: none
// post: outputs goodbye message to the screen
void farewell()
{
  cout << "Thanks for running the program. As you can see, select sort "
       << "ran quicker than\nbubble sort. Also, the sorts take longer when"
       << " handling floats because floats\nare more complicated." << endl;

  return;
}

// loads the array with random integers
// pre: Array must be defined/declared
// post: array is filled with random integers
void loadArray(int randArray[ ], const int SIZE)
{
  for (int i = 0; i < SIZE; i++)
    randArray[i] = rand();

  return;
}

// loads the array with random floats
// pre: array must be defined/declared
// post: array is filled with random integers
void loadArray(float randArray2[ ], const int SIZE)
{
  for (int i = 0; i < SIZE; i++)
    randArray2[i] = rand() / float(rand());

  return;
}

// prints the timing results
// pre: sorts must've been ran and start and finish must have been
//      given integer values.
// post: outputs the times of the sorts to the screen.
void print_results( long int start, long int finish)
{
  cout << "Time taken = " << (static_cast<float>(finish) - start)
                             / CLOCKS_PER_SEC 
       << " secs" << endl;
  cout << endl;
}

