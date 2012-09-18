/* programmer: robertoMurillo         date: 11/26/05                  *
 * file: sort.h                                                       *
 * purpose: this file contains the sort function for the shelter's    *
 *          fight function.                                           */

#ifndef SORT_H
#define SORT_H

/*************** SELECT SORT ***************/

// part of the select sort function
// pre: an array, its beginning index, and size must be declared and
//      passed to the function
// post: the index of the smaller number is returned
template <typename T>
short smallestIndex( const T array[], const short startindex,
                     const short endindex )
{
  short index, index_of_min = startindex;
  T min = array[startindex];

  for(index = startindex + 1; index < endindex; index++)
  {
    if (array[index] < min)
    {
      min = array[index];
      index_of_min = index;
    }
  }

  return index_of_min;
}

// swaps two given integers
// pre: two integers must be declared and passed to the function
// post: flips the integers positions
template <typename T>
void swapFunc( T & a, T & b )
{
  T temp = a;

  a = b;
  b = temp;

  return;
}

// sorts integers/floats in the array in order
// pre: an array and its size must be defined and passed to the fnctn
// post: all of the integers/floats are sorted from least to greatest
template <typename T>
void selectSort(T array[], const int SIZE)
{
  int index, nextsmallest;
  for(index = 0; index < SIZE-1; index++)
  {
    nextsmallest = smallestIndex(array, index, SIZE);
    swapFunc( array[index], array[nextsmallest]);
  }

  return;
}

/*************** SELECT SORT ***************/

#endif

