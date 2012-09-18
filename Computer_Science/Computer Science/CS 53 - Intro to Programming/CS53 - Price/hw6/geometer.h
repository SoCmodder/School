/* programmer: robertoMurillo    date: 10/5/05 *
 * file: geometer.cpp                          *
 * purpose: walk-in-geometer script for Bob.   *
 * this file includes all prototypes/vars.     */
 
#ifndef GEOMETER_H
#define GEOMETER_H 

/*************** STRUCTS ***************/

struct Point
{
  float m_Xcoord;
  float m_Ycoord;
};

struct Circle
{
	float m_radius;
};
    
/*************** STRUCTS ***************/
    
/*************** PROTOTYPES ***************/

// displays a welcome message
// pre: none
// post: prints welcome message
void welcome();

// displays menu to the user
// pre: none
// post: outputs a menu to user
char displayMenu();

// switch-case that controls options
// pre: choice must be 1-6
// post: the appropriate function is called depending on the users choice
void menuCases(const char choice);  
Point getPoint();  // gets the user's point

// quadrantPoints calculates all points for quadrant rectangle
// pre: point pt does not have 0 in X or Y
// post: points p2, p3, and p4 are given values
void quadrantPoints(const Point pt, Point & p2, Point & p3, Point & p4);

// planePoints calculates all points for plane rectangles
// pre: pt does not have 0 in X or Y
// post: points p2, p3, and p4 are given values
void planePoints(const Point pt, Point & p2, Point & p3, Point & p4);

// displays points in (x,y)
// pre: an X-coordinate and Y-coordinate have been entered
// post: point is returned in the defined format
Point displayPoints(const Point pt);

// calculates the radius squared for the circle equation
// pre: a point has been entered with no 0's in X or  Y
// post: returns the distance squared of the two points
Circle getCircle(const Point & p1);

// prints out the equation of the circle
// pre: a radius has been declared from getCircle
// post: equation is output to the screen in x^2 + y^2 = radius form 
void printCircle(const Circle circle1);

// asks user how far they want to rotate circle
// pre: none
// post: gets the measurement and returns it in radians 
float pointRotateAsk();

// calculates final answer of the rotation
// pre: user must have entered a valid point(x,y)
// post: calculates a new, rotated point and returns it
Point pointRotateFind( const Point & p2, const float angleRotate );

// prints rotated point in (x,y) form
// pre: a new point must have been created in printRotateFind
// post: calls the displayPoints function and outputs the pt to screen
void printRotatePt(const Point & p5);

// quit's out of the program
// pre:none
// post: outputs a quit message and leaves the switch-case
//       function
void quit();

// exit message
// pre: none
// post: outputs an exit message to the user
void exit();

/*************** PROTOTYPES ***************/

#endif
