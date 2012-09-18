/*
File Name:     hw8.cpp

Author:        Jennifer Leopold

Email Address: leopoldj@umr.edu

Description:   A program that defines some variables of type Point
               and performs some functions on them.

Date:          4/25/04
*/

#include <iostream>
#include "Point.h"
using namespace std;

int main() {
Point p1, p3;
Point p2(4, 5, "red");
double distance;

  cout << "Entering info for point p1...";
  cin >> p1;

  cout << "\np1: " << p1;
  cout << "\np2: " << p2;

  cout << "\n-p1: " << -p1;

  cout << "\np1 + p2: " << p1 + p2;

  distance = euclidean_distance(p1, p2);
  cout << "\nEuclidean distance between p1 and p2 = " << distance << endl;

  p3.setX(p1.getX() + 100); p3.setY(p2.getY() - 50); p3.setColor("blue");
  cout << "\np3: " << p3;

  p3.setColor(p2.getColor());
  cout << "\np3 with color modified: " << p3 << endl;

  return(0);
}
