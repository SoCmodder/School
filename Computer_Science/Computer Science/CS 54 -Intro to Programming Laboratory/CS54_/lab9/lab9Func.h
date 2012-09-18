/* 
* Author: Elliot Gross
* Date: 3/7/06
* Filename: Lab9Func.h
* Instructor: Brian Sea
* Description: This program will take a phrase and apply the caesar
* cipher to the phrase to "encrypt" it
*/
#ifndef LAB9FUNC_H
#define LAB9FUNC_H
#include <iostream>

using namespace std;

const int SHIFT_SIZE =4;

void greetings();
void goodbye();
bool runAgain();
void encryptor(char &a);
void encryptor(char phrase[], bool encrypt = true);
void decryptor(char &a);

#endif


