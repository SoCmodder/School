// Programmer: Roberto Murillo
// File: functions.h
// Description: This file contains the function prototypes for merge
// and insertion sort.

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "stdafx.h"

// Pre: Two integers are passed to the functions.
// Post: Outputs the result.
void print_results( long int start, long int finish);

// Pre: An array and its size are passed to the function.
// Post: The array is fully sorted from smallest to biggest.
void insertSort( int array1[], const int SIZE );

// Pre: An array from begin to finish is passed to the function.
// Post: The array from begin to finish is fully sorted from smallest to 
// biggest.
void mergeSort( int array1[], int begin, int finish );

// Pre: The array from begin to middle is sorted within itself and middle 
// to finish is sorted within itself.
// Post: The array is fully sorted from begin to finish.
void merge( int array1[], int begin, int middle, int finish );

#endif
