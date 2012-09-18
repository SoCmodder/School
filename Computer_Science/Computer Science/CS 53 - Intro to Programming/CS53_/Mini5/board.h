/* 
* Author: Elliot Gross
* Date: 4/6/06
* Filename: board.h
* Instructor: Brian Sea
* Description: This program simulates a pinball game
*/

#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include "ball.h"

using namespace std;


enum TYPE{empty, bumper, wall, ball};
struct Boardspace
{
	TYPE type;
	int points;
	int cost;
};


class Board
{
	private:
		int width;
		int length;
		int wallPoints;
		Boardspace grid[52][52];
		
	

	public:
		Board(); //default constructor for Board
		void move(DIRECTION &dir, int &ballX, int &ballY, int &life, int cost, int & points);
		//func. prototype for move
		void mkBumper(int x, int y, int points, int cost);
		//func. prototype for mkBumper
		void mkWall(int m, int n);//func. prototype for mkWall
		void setLength(int m);//prototype for setLength
		void setWidth(int n);//prototype for setWidth
		int getWidth() const;//prototype for getWidth
		int getLength() const;//prototype for getLength
		
};


#endif


  
