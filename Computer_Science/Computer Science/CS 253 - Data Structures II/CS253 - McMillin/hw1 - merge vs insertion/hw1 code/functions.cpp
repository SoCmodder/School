// Programmer: Roberto Murillo
// File: functions.cpp
// Description: This file contains the function definitions for merge
// and insertion sort, as well as the print_results which calculates
// the time taken.

#include "stdafx.h"
#include "functions.h"
#include "assert.h"

#include <iostream>
#include <ctime>
using namespace std;

// Pre: Two integers are passed to the functions.
// Post: Outputs the result.
void print_results( long int start, long int finish )
{
  cout << "Time taken: " << (static_cast<float>(finish) - start)
                             / CLOCKS_PER_SEC 
       << " secs" << endl;
  cout << endl;
}

// Pre: An array and its size are passed to the function.
// Post: The array is fully sorted from smallest to biggest.
void insertSort( int array1[], const int SIZE )
{
  int i = 0, j, key;

  for( j = 1; j < SIZE; j++ )
  {
    // Checks the invariant during Maintenance.
    //for( int b = 1; b < i; b++ )
    //  assert( array1[b] >= array1[b-1] );

    // Sets the j element to key and i to j - 1
    key = array1[j];
    i = j - 1;

    // Compares each i to key, if array[i] is greater than key
    // it shifts i one up, and compares the next element until
    // it finds the correct spot for key.
    while( i >= 0 && array1[i] > key )
    {
      array1[i+1] = array1[i];
      i = i - 1;
    }

    array1[i+1] = key;
  }
  // Checks the invariant at Termination.
  //for( int b = 1; b < i; b++ )
  //    assert( array1[b] >= array1[b-1] );
}

// Pre: An array from begin to finish is passed to the function.
// Post: The array from begin to finish is fully sorted from smallest to 
// biggest.
void mergeSort( int array1[], int begin, int finish )
{
  int middle;

  if( (finish - begin) > 1 )
  {
	  if( begin < finish )
		  middle = (begin+finish)/2;

    // Recursively calls itself for both new arrays until size is 1.
	  mergeSort( array1, begin, middle );
	  mergeSort( array1, middle, finish );
    // Merges all arrays back into one to get the final sorted array.
	  merge( array1, begin, middle, finish );
  }
}

// Pre: The array from begin to middle is sorted within itself and middle 
// to finish is sorted within itself.
// Post: The array is fully sorted from begin to finish.
void merge( int array1[], int begin, int middle, int finish )
{
  int *L, *R;            // arrays to be used for storing
  int i, j, n1, n2;
  n1 = middle - begin;
  n2 = finish - middle;
  L = new int[n1];
  R = new int[n2];

  // Loads the left array all the way up to size n1
  for( i = 0; i < n1; i++ )
    L[i] = array1[begin + i];

  // Loads the right array all the way up to size n2
  for( j = 0; j < n2; j++ )
    R[j] = array1[middle + j];

  // This loop compares elements in the left and right array and stores
  // them back into the main array in sorted order.
  i = 0, j = 0;
  for( int k = begin; k <= finish; k++ )
  {
    /* Checks the invariants. */
    // for( int b = begin; b < k-1; b++ )
    // {
    //   assert( (array1[b] <= array1[b+1]) );
    //   assert( i+j == k-begin );
    // }
    // for( int b = 0; b < n1-1; b++ )
    //   assert( L[b] <= L[b+1] );
    // for( int b = 0; b < n2-1; b++ )
    //   assert( R[b] <= R[b+1] );
    /* End of Checks the invariants. */

    // If both L and R still have elements in the array
    if( i < n1 && j < n2 )
    {
      // If the element in left is less than or equal to, left is stored first.
      if( L[i] <= R[j] )
      {
        array1[k] = L[i];
        i++;
      }

      // Otherwise, the right is stored.
		  else
      {
        array1[k] = R[j];
        j++;
      }
    }
    
    // If only the right array has elements.
    else if( i >= n1 && j < n2 )
    {
      array1[k] = R[j];
      j++;
    }
    
    // If only the left has remaining elements.
    else if( i < n1 && j >= n2 )
    {
      array1[k] = L[i];
      i++;
    }
  }

  delete []L;
  delete []R;
}
