/* Programmer: Roberto Murillo
 * Date: 3/13/06
 * File: main.cpp
 * Description: Contains the complete program, including the creation of
 * the board and the allocation of the queens.
 * Instructor: Liu
 */

#include <iostream>
#include "queens_class.h"
using namespace std;

int main( int argc, char * argv[] )
{
  // Checks to make sure a size was entered.
  if( argc < 2 )
  {
    cout << "You forgot the board size." << endl;
    exit(1);
  }

  // Convers the size to an actual, useable integer.
  int SIZE = atoi( argv[1] );

  // Creates the queens problem.
  Queens newGame( SIZE );
  
  // Passes the first column in order to set off the recursion that is the 
  // placeQueens function.
  if( newGame.placeQueens( 0 ) )
    newGame.displayBoard();
  
  // If the placeQueens function is not successful, there is no solution.
  else
    cout << "There is no feasible solution." << endl;

  return 0;
}