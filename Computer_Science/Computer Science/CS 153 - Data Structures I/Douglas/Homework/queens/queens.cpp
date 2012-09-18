// queens.cpp : Defines the entry point for the console application.
//
#include "Queens.h"
#include "stdafx.h"
#include <iostream.h>

int const size=8;

//Place Queen places a queen into the specified column
//PRE: NONE
//POST: 'Q' is inserted into the first available spot in the given column
//if no spot available, false is returned
bool PlaceQueen (int board[size][size], int column);

//FillBoard handles the main recursive operations of filling the board
//PRE: Board initialized to all blank spaces
//POST: Board is filled with queens in all the correct places
void FillBoard (int board[size][size], int column);

//InitBoard initializes the board
//PRE: None
//POST: the board is initialized to all white spaces
void InitBoard(int board[size][size]);

//Display displays the board to the screen
//PRe: None
//Post: Board is placed in screen output
void Display (int board[size][size]);


int _tmain(int argc, _Tint* argv[])
{
	
	int board[size][size];
	InitBoard(board);
	FillBoard(board,0);
	Display(board);
	
	return 0;
}

bool PlaceQueen (int board[size][size], int column)
{
	int row;
	bool place=false;
	for (row=0; row<size; row++)
	{
		if (board[row][column]==' ')
		{
			board[row][column]='0';
			place=true;
			for(int loop=0; loop<size; loop++) //Fills horizontal and vertical positions
			{
				if(loop!=column)
				{
					board[row][loop]=-1;
				}
				if(loop!=row)
				{
					board[loop][column]=-1;
				}
				{
					board[row-loop][column-loop]=-1;
				}

			}
            

		}
	}
	return place;
}

void FillBoard (int board[size][size], int column)
{
	InitBoard(board);
}

void InitBoard(int board[size][size])
{
	int row = size;
	int column = size;
	{
		for (int i =0; i<row; ++i)
		{
			for(int j =0; j<column; ++j)
				board[i][j]=' ';   //Initializes every space to a blank
		}
}



void Display (int board[size][size])
{
	int row = size;
	int column = size;
	
	for (int i=0; i<row; ++i)
	{			
		for(int j=0; j<column; ++j)
		{
			cout<<board[i][j];  //Displays every place on the screen.
		}
	}
	
}