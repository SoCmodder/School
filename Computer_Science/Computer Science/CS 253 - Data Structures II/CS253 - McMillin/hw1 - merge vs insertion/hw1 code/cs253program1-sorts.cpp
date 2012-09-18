// cs253program1-sorts.cpp : Defines the entry point for the console application.
//
// Programmer: Roberto Murillo
// File: cs253program1-sorts.cpp
// Description: This program explores the complexities of merge sort and
// insertion sort.  It is given a size by the user, and sorts an array of
// that size using insertion and merge sort, as well as calculating the 
// time it takes to sort.

#include "stdafx.h"
#include "functions.h"
#include <ctime>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
  int capacity, lowest = 1, highest = 500;
  int *array;
  int *array2;
  long start, finish;
  srand(time(NULL));
  
  // Asks user to enter a size.
  do
  {    
    cout << "How many items would you like to sort: ";
    cin >> capacity;
    cout << endl;

    if( capacity < 2 )
      cout << "Please enter more than a size of 1." << endl;
  }while( capacity < 2 );

  // Creates an array with the user-defined size.
  array = new int[capacity];
  array2 = new int[capacity];

  // Fills the array with random numbers between 1 and 500 and a second copy
  // to make sure insertion and merge are sorting the same random numbers.
  for (int i = 0; i < capacity; i++)
  {
    array[i] = static_cast<int>(rand() % (highest - lowest + 1) + lowest);
    array2[i] = array[i];
  }

  // Counts the time it takes for insertSort to run.
  start = clock();
  insertSort( array, capacity );
  finish = clock();
  print_results( start, finish );

  // Counts the time it takes for mergeSort to run.
  start = clock();
  mergeSort( array2, 0, capacity );
  finish = clock();
  print_results( start, finish );

  // Deletes any used memory
  delete []array;
  delete []array2;

  system( "PAUSE" );

	return 0;
}
