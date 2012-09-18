/* programmer: robertoMurillo    date: 09/28/05 *
 * file: hw5.cpp              instructor: price *
 * purpose: creating functions for points and   *
 *          lines.                              */
 
#include <iostream>
#include <cmath>
using namespace std;

/*************** STRUCTS ***************/

struct Point
{
  float m_Xcoord;
  float m_Ycoord;
};

struct Line
{
  float m_a;
  float m_b;
  float m_c;
};

/*************** STRUCTS ***************/

/*************** FUNCTION PROTOTYPES ***************/

Point getPoints();   // gets the points from the user
Line getLine(const Point p1, const Point p2); // creates line from points
double getDistance(const Point p1, const Point p2); // calculates distance
void displayPoints(const Point pt); // displays points in (x,y) form
void displayLine(const Line line1); // displays line in Ax + By - C = 0
void displayDistance(const double distance1); // displays distance

/*************** FUNCTION PROTOTYPES ***************/


int main()
{

  /*************** VARIABLE DECLARATIONS ***************/
  
  char cChoice;         // user's choice for the menu
  Point p1, p2;         // both of the user's desired points
  Line line1;           
  double distance1;
  bool numEntered = false;

  /*************** VARIABLE DECLARATIONS ***************/
  
  /*************** MAIN PROGRAM ***************/
  
  do 
  {
    cout << endl;
    cout << "What would you like to do: " << endl
         << endl
         << "1. Enter in two points." << endl
         << "2. Display the distance between the two points." << endl
         << "3. Calculate equation of the line through the two points."
         << endl
         << "4. Quit" << endl
         << endl
         << "Your choice: ";
  
    cin >> cChoice;
    cout << endl;
  
    switch(cChoice)
    {
      case '1':
        p1 = getPoints();
        p2 = getPoints();
      
        displayPoints(p1);
        displayPoints(p2);
        numEntered = true;
        break;
      
      case '2':
        if ( numEntered )
        {
          distance1 = getDistance(p1, p2);
      
          displayDistance(distance1);
        }
        
        else
        {
          cout << "You must enter points first."
               << endl;
        }
        break;
    
      case '3':
        if ( numEntered )
        {
          line1 = getLine(p1, p2);
      
          displayLine(line1);
        }
        
        else
        {
          cout << "You must enter points first."
               << endl;
        }
        break;

      case '4':
        cout << "Thanks for running the program!" << endl << endl;
        break;
    
      default:
        cout << "Error: Not a choice!" << endl << endl;
        break;
    }
  } while (cChoice != '4');

  /*************** MAIN PROGRAM ***************/

}

/*************** FUNCTION DEFINITIONS ***************/

Point getPoints()  // gets points from user
{
  Point p1;
  
  cout << "Point:" << endl
       << "Please enter in X: ";
  cin >> p1.m_Xcoord;
  cout << "Please enter in Y: ";
  cin >> p1.m_Ycoord;
return p1;
}

double getDistance(const Point p1, const Point p2) // calculates ditance
{
  double distance1 = sqrt((p1.m_Xcoord - p2.m_Xcoord)*(p1.m_Xcoord - 
                           p2.m_Xcoord) + (p1.m_Ycoord - p2.m_Ycoord)
                           *(p1.m_Ycoord - p2.m_Ycoord));
return distance1;
}

Line getLine(const Point p1, const Point p2)  // creates line from distance
{
  Line line1;
  
  line1.m_a = (p1.m_Ycoord - p2.m_Ycoord);
  line1.m_b = (p2.m_Xcoord - p1.m_Xcoord);
  line1.m_c = (-line1.m_a*p1.m_Xcoord) - (line1.m_b*p1.m_Ycoord);
  
return line1;
}

void displayPoints(const Point pt) // displays points in (x,y) form
{
  cout << "(" << pt.m_Xcoord << "," << pt.m_Ycoord << ")"
       << endl;

return;
}

void displayLine(const Line line1)  // displays line in Ax + By - C form
{
  if ( line1.m_a == 0 && line1.m_b == 0 )
      cout << "No line."
           << endl;
             
  else if ( line1.m_b == 0 )
    cout << "The equation is " << line1.m_a << "x + " << line1.m_c 
         << " = 0"
         << endl;
  
  else if ( line1.m_a == 0 )
    cout << "The equation is " << line1.m_b << "y + " << line1.m_c
         << " = 0"
         << endl;
  
  else if ( line1.m_a != 0 && line1.m_b != 0 )
    cout << "The equation is " << line1.m_a << "x + " << line1.m_b 
         << "y + " << line1.m_c << " = 0"
         << endl;

return;
}

void displayDistance(const double distance1) // displays distance
{
  cout << "The distance is " << distance1 << "."
       << endl;

return;
}

/*************** FUNCTION DEFINITIONS ***************/
