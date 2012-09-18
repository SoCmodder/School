#include <iostream>
using namespace std;

void input_radius(float& radius);//function to input radius size
void compute_area(float radius, float& area, const float pi);//function that computes area
void display(float area);//function that dispalys the area

float radius=0;//the radius
float area=0;//the area
const float pi=3.14159;// the number pi

int main()
{
  input_radius(radius);//calls the function
  compute_area(radius, area, pi);//calls the function
  display(area);//calls the function
  return 0;
}

void input_radius(float& radius)//function to input radius size
{
  cout<<"Please enter the radius of a circle (in cm):";
  cin>>radius;//user inputs radius
  return;
}

void compute_area(float radius, float& area, const float pi)//function to compute area
{
  area=pi*radius*radius;//computes area
  return;
}

void display(float area)//displays area
{
   cout<<"The area of the circle is : "<<area<<endl;
  return;
}
