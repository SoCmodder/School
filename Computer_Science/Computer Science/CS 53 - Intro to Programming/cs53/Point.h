/*

  File name: Point.h
  Author: Brent Powers
  Date: May 11 2004
  Email: bkp347@umr.edu
  */
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <fstream>
using namespace std;

class Point
{
public:
	Point();//constructor
	Point(const int x1,const int y1, const string color1);//constructor
	string getColor();//member functions
	void setColor(string new_color);
	int getX();
	void setX(int n_X);
	int getY();
	void setY(int n_Y);
	Point operator+(Point p);
	Point operator-();	
	friend ostream& operator<<(ostream &os, Point& p);//friend functions
	friend istream& operator>>(istream &is, Point& p);
	friend double euclidean_distance(Point p1, Point p2);

private:
	int x; //private members
	int y;
	string color;

};
#endif
