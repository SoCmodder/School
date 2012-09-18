/* programmer: robertoMurillo   date: 10/24/05 *
 * file: clock.h                               *
 * purpose: file has protocols and templates   *
 *          for the program.                   */

#ifndef CLOCK_H
#define CLOCK_H

/*************** CONSTANTS ***************/

const int SIZE = 20000;

/*************** PROTOTYPES ***************/


// welcome message
// pre: none
// post: outputs welcome message to the screen
void welcome();

// goodbye message
// pre: none
// post: outputs goodbye message to the screen
void farewell();

// loads the array with random integers
// pre: Array must be defined/declared
// post: array is filled with random integers
void loadArray(int randArray[ ], const int SIZE);

// loads the array with random floats
// pre: array must be defined/declared
// post: array is filled with random integers
void loadArray(float randArray2[ ], const int SIZE);

// swaps two given integers
// pre: two integers must be declared and passed to the function
// post: flips the integers positions
template <typename T>
void swapFunc( T & a, T & b );

// part of the select sort function
// pre: an array, its beginning index, and size must be declared and
//      passed to the function
// post: the index of the smaller number is returned
template <typename T>
short smallestIndex( const T array[], const short startindex,
                     const short endindex );

// sorts an array using bubble sort
// pre: an array along with its size must be declared and passed to fnctn
// post: goes through entire array and sorts it in order from least to
//       greatest
template <typename T>
void bubbleSort(T array[], int SiZE);

// sorts integers/floats in the array in order
// pre: an array and its size must be defined and passed to the fnctn
// post: all of the integers/floats are sorted from least to greatest
template <typename T>
void selectSort( T array[], const int SIZE);

// prints the timing results
// pre: sorts must've been ran and start and finish must have been
//      given integer values.
// post: outputs the times of the sorts to the screen.
void print_results(long int start, long int finish);

/*************** PROTOTYPES ***************/

/*************** BUBBLE SORT ***************/

// sorts an array using bubble sort
// pre: an array along with its size must be declared and passed to fnctn
// post: goes through entire array and sorts it in order from least to
//       greatest
template <typename T>
void bubbleSort(T array[], const int datasize)
{
  for (int i = (datasize - 1); i >= 0; i--)
  {
    for ( int j = 0; j < i; j++)
      if ( array[j] > array[j + 1] )
        swapFunc( array[j], array[j + 1] );
  }
                        
  return;
}

/*************** BUBBLE SORT ***************/

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

