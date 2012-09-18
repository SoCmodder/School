/* 
* Author: Elliot Gross
* Date: 3/14/06
* Filename: lab10Func.h
* Instructor: Brian Sea
* Description: This program will take a phrase and apply the caesar
* cipher to the phrase to "encrypt" it
*/

#ifndef LAB10FUNC_H
#define LAB10FUNC_H
#include <iostream>
 

using namespace std;

void ntsCopy(char source[], char destination[], int size);
// function prototype for ntsCopy
void ntsNCopy(char source[], char destination[], int n, int size);
// function prototype for ntsNCopy
void ntsCat(char source[], char destination [], int size);
// function prototype for ntsCat
void ntsNCat(char source[], char destination[], int n, int size);
// function prototype for ntsNCat


#endif
