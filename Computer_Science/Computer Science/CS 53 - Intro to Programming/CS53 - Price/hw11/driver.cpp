/* programmer: robertoMurillo
 * date: 11/30/05
 * file: driver.cpp
 * purpose: main function to test the classes created.
 */

#include "shelter.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  shelter shelter1("homeless",0,0); // declares an empty shelter.
  dog dog1("Lucky", 4, 200, false, true, "fruity", 2); // declares a dog.
  cat cat1("Scruffy", 9, 58, false, true, "mauve", 2); // declares a cat.
  ifstream in; // ifstream to read in the input file

  cout << shelter1; // outputs the empty shelter.

  in.open("input.txt"); // opens the input file.
  in >> shelter1; // reads the input file into the shelter.

  shelter1 + dog1; // adds a dog to the shelter.
  shelter1 + cat1; // adds a cat to the shelter.

  shelter1.open_cages(); // let the battle begin!

  return 0;
}



