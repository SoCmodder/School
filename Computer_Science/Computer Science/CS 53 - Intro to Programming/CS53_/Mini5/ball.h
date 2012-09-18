/* 
* Author: Elliot Gross
* Date: 4/6/06
* Filename: ball.h
* Instructor: Brian Sea
* Description: This program simulates a pinball game
*/

#ifndef BALL_H
#define BALL_H



#include <iostream>


using namespace std;

enum DIRECTION{LEFT, UP, RIGHT, DOWN};

class Ball
{
	private:
		unsigned int life;
		DIRECTION dir;
		unsigned int points;
		unsigned int ballX;
		unsigned int ballY;
		unsigned int cost;
		bool isAlive;

	public:
		Ball();//default constructor for ball
		DIRECTION getDirection() const;//accessor for direction
		void setDirection(DIRECTION dir1);//prototype for setDirection
		int getPoints() const;//accessor for getPoints
		void setPoints(int p);//prototype for setPoints
		int getLife() const;//accessor for getLife
		void setLife(int l);//prototype for setLife
};


#endif
