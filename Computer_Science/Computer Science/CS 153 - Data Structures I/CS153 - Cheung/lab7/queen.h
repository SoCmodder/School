/*
Author: Brent Powers
File: queen.h
Description: class definition for queens class
Date: 3-24-05
*/

#ifndef QUEEN_H
#define QUEEN_H

class queens
{
public:
	queens();//constructor
	~queens();//destructor
	void clearboard();//clear the board
	void displayboard(CListBox& results);//desplay the board
	bool placequeen(int currcolumn);//place the queens
	void setboardsize(int size);//set the boards size
private:
	int boardsize;//the boards size
	int **board;//the chess board
	bool isunderattack(int row, int column);//sees if under attack
}


#endif