/*
Author: Brent Powers
File: queen.cpp
Date: 3-24-05
Description: Function definitions for the queens class
*/
#include "stdafx.h"
#include "queen.h"

;using namespace std;
/*
Function: queens()
Description: default constructor for queens class; sets the board size to zero
Precondition: NONE
Postcondition: NONE
*/
queens::queens()
{
	boardsize=0;//the size of the board to zero
	
}
/*
Function: ~queens()
Description: default destructor for the queens class
Precondition: NONE
Postcondition: NONE
*/
queens::~queens(){}

/*
Function: setboardsize(int size)
Description: takes the passed variable and sets the member
			variable boardsize to it
Precondition: boardsize is declared and size is a valid int
Postcondition: boardsize is set to size
*/
void queens::setboardsize(int size)
{
	boardsize=size;//sets boardsize
	board=new int*[boardsize];
	for(int i=0;i<boardsize;i++)
	{
		board[i]=new int[boardsize];
	}
}
/*
Function: placequeen(int curr_column)
Description: this function uses a recursive algorythim to 
			place queens of a chess board so that none of
			the queens can possably attack each other.
Precondition: the board is declared and all values are set
			to zero. row and curr_column are set to zero
			at the first time it is called.
Postcondition: There will be n placed queens on the board
				such that none of them could possable 
				attack another queen.
*/

bool queens::placequeen(int curr_column)
{
	if(curr_column==boardsize)//if the board is completely full
		return TRUE;
	else
	{
		bool queensplaced=FALSE;//evaluation variable
		int row=0;
		while(!queensplaced&&(row<boardsize))//while we haven't 
		{									//placed a queen or
											//filled all rows
			if(isunderattack(row, curr_column))//checks to see
				row++;			//if the spot could be attacked 
			else
			{
				board[row][curr_column]=1;//place a queen 
				curr_column++;//next column
				queensplaced=placequeen(curr_column);//recursive
				if(!queensplaced)//can't place any queens in 
				{				//this column
					if(boardsize>3)
					{
						curr_column--;//go back to other column
					}
					board[row][curr_column]=0;//remove the queen
					row++;//work on the next row
				}
			}
		}
	return queensplaced;
	}
}
/*
Function: isunderattack(int row, int column)
Description: Checks to see if that spot could be attacked
			by any other queen
Precondition: Board is correctly laided out and has no 
				invalid data spots
Postcondition: Returns true if there is a queen that could
				attack that spot, or false if there isn't
*/

bool queens::isunderattack(int row, int column)
{
	bool attack = FALSE;//evaluation valiable
	for(int i=0;i<boardsize;i++)//column check
	{
		if(board[row][i]==1)//check
			attack=TRUE;
	}
	for(int i=0;i<boardsize;i++)//row check
	{
		if(board[i][column]==1)//check
			attack=TRUE;
	}
	for(int i=0;((column+i)<boardsize)&&((row+i)<boardsize);i++)//down right check
	{
		if(board[row+i][column+i]==1)//check
			attack=TRUE;
	}
	for(int i=0;((column-i)>=0)&&((row-i)>=0);i++)//up left check
	{
		if(board[row-i][column-i]==1)//check
			attack=TRUE;
	}
	for(int i=0;((column+i)<boardsize)&&((row-i)>=0);i++)//up right check
	{
		if(board[row-i][column+i]==1)//check
			attack=TRUE;
	}
	for(int i=0;((column-i)>=0)&&((row+i)<boardsize);i++)//down left check
	{
		if(board[row+i][column-i]==1)//check
			attack=TRUE;
	}
    return attack;
}
/*
Function: displayboard(CListBox &results)
Description: Displays the cordinates of the queens on the
			board
Precondition: The board is accuratly filled with valid
				data members
Postcondtion: The cordinated of the queens will be sent
				to the listbox for display
*/
void queens::displayboard(CListBox &results)
{
	results.ResetContent();//clear the box
	for(int j=0;j<boardsize;j++)//for all of the columns
	{
		for(int i=0;i<boardsize;i++)//for all rows in column
		{
			if(board[j][i]==1)//if there is a queen
			{
				char temp1[6]="";
				char temp2[3]="";
				_itoa(j+1, temp2, 10);
				_itoa(i+1, temp1, 10);
				strncat(temp1,",",1);
				strncat(temp1,temp2,3);
				results.AddString(temp1);//print cordinates
			}
		}
	}

}
/*
Function: clearboard()
Description: Removes all queens from the board
Precondition: None
Postcondition: All board spaces are set to empty
*/

void queens::clearboard()
{
	for(int i=0;i<boardsize;i++)//for all columns
	{
		for(int j=0;j<boardsize;j++)//for all rows in column
		{
			board[i][j]=0;//empty out queens
		}
	}
}
