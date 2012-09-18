/* programmer: robertoMurillo   date: 10/24/05 *
 * file: clock.cpp                             *
 * purpose: main program that runs the timing  *
 *          of the sorts.                      */

#include "clock.h"

#include <ctime>
#include <iostream>
using namespace std;

int main()
{
  int randArray[SIZE];
  float randArray2[SIZE];
  long start, finish;
  srand(time(NULL));

  welcome();

  // loads integer array and uses bubble sort
  loadArray(randArray, SIZE);
  start = clock();
  bubbleSort(randArray, SIZE);
  finish = clock();

  // prints results
  print_results(start, finish);

  // loads integer array and uses select sort
  loadArray(randArray, SIZE);
  start = clock();
  selectSort(randArray, SIZE);
  finish = clock();

  // prints results
  print_results(start, finish);

  // loads float array and uses bubble sort
  loadArray(randArray2, SIZE);
  start = clock();
  bubbleSort(randArray2, SIZE);
  finish = clock();

  // prints results
  print_results(start, finish);

  // loads float array and uses select sort
  loadArray(randArray2, SIZE);
  start = clock();
  selectSort(randArray2, SIZE);
  finish = clock();

  // prints results
  print_results(start, finish);
  farewell();

  return 0;
}
