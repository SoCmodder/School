/* 
* Author: Elliot Gross
* Date: 4/6/06
* Filename: ball.cpp
* Instructor: Brian Sea
* Description: This program simulates a pinball game
*/

#include <iostream>
#include "ball.h" //includes ball.h
using namespace std;



Ball::Ball() //default constructor for a ball
{
	life = 10;
	dir = RIGHT;
	points = 0;
	ballX = 0;
	ballY =0;
	cost = 0;
	isAlive = true;


}


DIRECTION Ball::getDirection() const // accessor for direction
{
	return dir;
}

int Ball::getPoints() const //accessor for points
{
	return points;
}

void Ball::setPoints(int p)//function def. for setPoints
{
	points = p;
}

int Ball::getLife() const//accessor for life
{
	return life;
}

void Ball::setLife(int l)//func. def. for setLife
{
	life = l;
	return;
}

void Ball::setDirection(DIRECTION dir1)//func. def. for setDirection
{
	dir = dir1;
}
