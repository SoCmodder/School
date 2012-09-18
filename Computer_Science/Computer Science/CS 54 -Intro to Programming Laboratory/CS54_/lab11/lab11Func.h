/* 
* Author: Elliot Gross
* Date: 3/21/06
* Filename: lab11Func.h
* Instructor: Brian Sea
* Description: This program will read a certain amount 
* of numbers and will output data to an external file
*/

#ifndef LAB11FUNC_H
#define LAB11FUNC_H
#include <iostream>
 

using namespace std;

//function prototypes
void greetings();
void goodbye();
void sum(char filename[], ofstream &fout);
void average(char filename[], ofstream &fout);


#endif


