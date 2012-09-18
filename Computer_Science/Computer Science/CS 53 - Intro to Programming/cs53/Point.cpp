/*
File Name: Point.cpp
Author: Brent Powers
Date May 11 2004
Email: bkp347@umr.edu

  */

#include <iostream>
#include <fstream>
#include "Point.h"
#include <cmath>
#include <string>
using namespace std;

/*
Function name: Point
Parameters: none
Returns: none
Description: default constructor for the Point class
*/

Point::Point()
{
	color="Black";
	x=0;
	y=0;
}

/*
Function name: Point
Parameters: int x1, int y1, string color1
returns: none
Description: constructor that sets Point to user chosen values
*/
Point::Point(const int x1,const int y1, const string color1)
{
	color=color1;
	x=x1;
	y=y1;
}

/*
Function: getColor
Parameters: none
Returns: string color
Description: accessor function for the member variable color
*/
string Point::getColor()
{
	return color;
}

/*
Function: setColor
Parameters: string new_color
returns: nothing
Description: sets the member variable color to what user passes
*/
void Point::setColor(string new_color)
{
	color=new_color;
	return;
}

/*
Function: getX
Parameters: none
Returns: int x
Description: accesser function for member variable x
*/
int Point::getX()
{
	return x;
}

/*
Function: setX
Parameters:int n_X
Returns: none
Description: Setter function for member variable x
*/
void Point::setX(int n_X)
{
	x=n_X;
	return;
}

/*
Function: getY
Parameters: none
Returns: int y
Description: getter function for member variable y
*/
int Point::getY()
{
	return y;
}
/*
Function: setY
Parameters: int n-Y
Returns: none
Description: setter function for member variable y
*/
void Point::setY(int n_Y)
{
	y=n_Y;
	return;
}
/*
Function: operator<<
Parameters: ostream os, Point p
Returns: ostream os
Description: overload the << operator to print a Points in specific ways
*/

ostream& operator<<(ostream &os, Point& p)
{
	os<<" has a color of "<<p.getColor()<<" and is located at ("<<p.getX()<<","<<p.getY()<<")"<<endl;
	return os;
}
/*
Function: operator>>
Parameters: istream is, Point p
Returns: istream is
Description: overload the >> operator to modify the way points are entered
*/
istream& operator>>(istream &is, Point& p)
{
	string color;
	int x;
	int y;
	cout<<endl<<"Please enter the string's color: ";
	getline(is,color);
	cout<<endl<<"Please enter the x cordinate: ";
	cin>>x;
	cout<<endl<<"Please enter the y cordinate: ";
	cin>>y;
	return is;
}
/*
Function: operator +
Parameters: Point p
Returns: Point newpoint
Description: overload the operator + to add two Points together by adding there x and y points and setting the color to black
*/
Point Point::operator +(Point p)
{
	Point newpoint;
	newpoint.setX(x+p.getX());
	newpoint.setY(y+p.getY());
	newpoint.setColor("black");
	return newpoint;
}
/*
Function: operator -
Parameters: none
Returns: negative
Description: takes the values of the x and y point and changes them to their negatives
*/
Point Point::operator -()
{
	Point negative;
	negative.setX(0-x);
	negative.setY(0-y);
	negative.setColor(color);
	return negative;
}
/*
Function: euclidean_distance
Parameters: Point p1, Point p2
Returns: double distance
Description: calculates and returns the linear distance between a point
*/
double euclidean_distance(Point p1, Point p2)
{
	double distance;
	distance=sqrt(pow((p2.getX()-p1.getX()),2)+pow((p2.getY()-p1.getY()),2));
	return distance;
}
