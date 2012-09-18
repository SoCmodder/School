/* programmer: robertoMurillo    date: 10/26/05 *
 * intructor: price              class: cs54d   *
 * file: driver.cpp                             *
 * purpose: main file for cstring program.      */
 
#include <iostream>
#include <cstring>
#include "func.h"
using namespace std;

int main()
{
  char buf[SIZE];
  char str[SIZE];
  char cVariable;
  unsigned int length;
  unsigned int compare;
  
  welcome();
  
  bzero(buf, SIZE);
  bzero(str, SIZE);
  
  get_string(buf, SIZE);
  cVariable = get_char();
  
  length = strlen(str);
  strncpy(buf, str, length);
  
  capitalize(str, length, cVariable);
  compare = strncmp(buf, str, length);
  
  display_results(buf, str, compare);
  
  farewell();
  
  return 0;
}
 
