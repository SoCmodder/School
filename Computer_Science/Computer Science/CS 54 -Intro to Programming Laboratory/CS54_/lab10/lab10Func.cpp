/* 
* Author: Elliot Gross
* Date: 3/14/06
* Filename: lab10.cpp
* Instructor: Brian Sea
* Description: This program will take a phrase and apply the caesar
* cipher to the phrase to "encrypt" it
*/

#include <iostream>
#include "lab10Func.h" //includes lab9Func.h
using namespace std;



void ntsCopy(char source[], char destination[], int size)
// Function definition for ntsCopy
{
	ntsNCopy(source, destination, size, size);
	//calls ntsNCopy
	return;
}
void ntsNCopy(char source[], char destination[], int n, int size)
// Function definition for ntsNCopy
{
	int i = 0;
	for (i =0; i < size && destination[i] != '\0'; i++)
	{
		destination[i] = source[i];
		//copies each character over
	}
	destination[i] = '\0'; // sets last character to null terminator
	return;
	
}
void ntsCat(char source[], char destination [], int size)
// Function definition for ntsCat
{
	ntsNCat(source, destination, size, size);
	// calls ntsNCat
	return;
}
void ntsNCat(char source[], char destination[], int n, int size)
// Function definition for ntsNCat
{
	int i = 0;
	for (i = 0; i < size && source[i] != '\0'; i++);//counts
	for (int j=0; j<size && source[i] != '\0'; j++)
	{
		destination[i] = source[j];
		//copies each character over
		i++;
	}
	destination [i] = '\0'; // sets last character to null terminator
	return;
	
}
