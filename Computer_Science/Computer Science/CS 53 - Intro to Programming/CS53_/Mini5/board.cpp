/* 
* Author: Elliot Gross
* Date: 4/6/06
* Filename: board.cpp
* Instructor: Brian Sea
* Description: This program simulates a pinball game
*/

#include <iostream>
#include "ball.h" //includes ball.h
#include "board.h" //includes board.h
using namespace std;

Board::Board()//default constructor for board
{
	width=0;
	length=0;
	wallPoints=0;
		
}

int Board::getWidth() const //accessor for getWidth
{
	return width;
}

int Board::getLength() const//accessor for getLength
{
	return length;
}

void Board::move(DIRECTION &dir, int &ballX, int &ballY, int &life, int Wallcost, int & points)
//function definition for move
{
	bool tmp = true;
	
			switch(dir)//switches case based on direction
			{
				case UP:
					life --;//subtracts life
					ballY--;//moves up
					if(grid[ballX][ballY].type == bumper)
					{
						points +=grid[ballX][ballY].points;//adds bumper points
						life -=grid[ballX][ballY].cost;//subtracts life
					}
					if (grid[ballX][ballY].type == wall)
						life -=Wallcost;//subtracts wallcost
					if( grid[ballX][ballY].type == bumper || 
						grid[ballX][ballY].type == wall)
						//moves it back if bumper or wall is in way
						//Also changes direction
					{
						ballY++;
						tmp = false;
						dir = RIGHT;
					}
					
					break;
				case LEFT: 
					life --;//subtracts life
					ballX--;//moves left
					if(grid[ballX][ballY].type == bumper)
						{
						points +=grid[ballX][ballY].points;
						life -=grid[ballX][ballY].cost;
						}
					if (grid[ballX][ballY].type == wall)
						life -=Wallcost;
					if( grid[ballX][ballY].type == bumper || 
						grid[ballX][ballY].type == wall)
					{
						ballX++;
						tmp = false;
						dir = UP;
					}
					break;
				case DOWN:
					life --;
					ballY++;//moves down
					if(grid[ballX][ballY].type == bumper)
						{
						points +=grid[ballX][ballY].points;
						life -=grid[ballX][ballY].cost;
						}
					if (grid[ballX][ballY].type == wall)
						life -=Wallcost;
					if( grid[ballX][ballY].type == bumper || 
						grid[ballX][ballY].type == wall)
					{
						ballY--;
						tmp = false;
						dir = LEFT;
					}
					break;
				case RIGHT:
					life --;
					ballX++;//moves right
					if(grid[ballX][ballY].type == bumper)
						{
						points +=grid[ballX][ballY].points;
						life -=grid[ballX][ballY].cost;
						}
					if (grid[ballX][ballY].type == wall)
						life -=Wallcost;
					if( grid[ballX][ballY].type == bumper || 
						grid[ballX][ballY].type == wall)
					{
						ballX--;
						tmp = false;
						dir = DOWN;
					}
					break;
			}
		
}

void Board::mkBumper(int x, int y, int points, int cost)
//function definition for mkBumper
{
	grid[x][y].type = bumper;
	grid[x][y].cost = cost;
	grid[x][y].points = points;

}
void Board::mkWall(int m, int n)
//function definition for mkWall
{

	for (int i=0; i < n; i++)
	{
		grid[0][i].type = wall;//sets wall 
	}
	for (int i=0; i < m; i++)
	{
		grid[i][0].type = wall;//sets wall
	}
	for (int i=0; i < m; i++)
	{
		grid[m][i].type = wall;//sets wall
	}
	for (int i=0; i < n; i++)
	{
		grid[i][n].type = wall;//sets wall
	}
}
void Board::setLength(int m)//func. def. for setLength
{
	length = m;
}

void Board::setWidth(int n)//func. def. for setWidth
{
	width = n;
}



	

