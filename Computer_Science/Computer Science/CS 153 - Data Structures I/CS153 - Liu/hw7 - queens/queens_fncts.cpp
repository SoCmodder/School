/* Programmer: Roberto Murillo
 * Date: 3/10/06
 * File: queens_fncts.cpp
 * Description: Contains the Queens class functions.
 * Instructor: Liu
 */

#include <iostream>
#include "queens_class.h"
using namespace std;

Queens::Queens( const int size )
{
  // Creates rows.
  board = new int*[ size ];
  setBoardSize( size );

  for( int row = 0; row < size; row++ )
  {
    // Creates columns.
    board[row] = new int[ size ];
  }

  // Fills the board with 0's to signify there is no queen.
  for( int row = 0; row < size; row++ )
  {
    for( int column = 0; column < size; column++ )
    {
      board[row][column] = 0;
    }
  }
}

Queens::~Queens()
{
  clearBoard(); // Deletes everything.
}

void Queens::clearBoard()
{
  int row;

  // Deletes all columns.
  for( row = 0; row < getBoardSize(); row++ )
  {
    delete [] board[row];
  }

  // Deletes rows.
  delete [] board;
}

bool Queens::isUnderAttack( int columnCheck, int rowCheck )
{
  bool underAttack = false;
  int row = 0, column = 0;

  row = rowCheck-1;
  for( column = columnCheck - 1; column >= 0 && !underAttack; column-- )
  {
    // Checks that there is nothing in the horizontal position.
    if( board[rowCheck][column] == 1 )
      underAttack = true;

    // Checks that there is nothing in the upward left diagnol.
    else if( row >= 0 )
    {
      if( board[row][column] == 1 )
      {
        underAttack = true;
      }

      row--;
    }
  }
    
  // Checks that there is nothing in the lower left diagnol.
  column = columnCheck - 1;
  for( row = rowCheck + 1; (row < getBoardSize() && row >= 0) && (column >= 0 && column < getBoardSize() ) && !underAttack; row++ )
  {
    if( board[row][column] == 1 )
      underAttack = true;

    column--;
  }

  return underAttack;
}

void Queens::displayBoard()
{
  int row;
  int column;

  for( row = 0; row < getBoardSize(); row++ )
  {
    for( column = 0; column < getBoardSize(); column++ )
    {
      cout << board[row][column] << " ";
    }
    cout << endl;
  }
}

bool Queens::placeQueens( int currColumn )
{
  bool queenPlaced = false;
  
  // If the currColumn is = to BoardSize, then we have placed all queens.
  if( currColumn == getBoardSize() )
    queenPlaced = true;

  // Otherwise, keep placing queens.
  else
  {
    int row = 0;

    while( !queenPlaced && (row < getBoardSize()) )
    {
      // If the current position is under attack, move to the next row.
      if( isUnderAttack( currColumn, row ) )
        row++;

      else
      {
        // Otherwise, place a queen there and call the function again.
        board[row][currColumn] = 1;
        queenPlaced = placeQueens( currColumn + 1 );

        // If there was no queen placed in the column after the current one,
        // we set the current one back to 0, and find the next unattacked spot.
        if( !queenPlaced )
        {
          board[row][currColumn] = 0;
        }  
        
        // But if the next spot is off the board, then we cant place a queen.
        if( row++ >= getBoardSize() )
        {
          queenPlaced = false;
        }
        // Otherwise, try the next row.
        else
          row++;
      }
    }
  }

  return queenPlaced;
}