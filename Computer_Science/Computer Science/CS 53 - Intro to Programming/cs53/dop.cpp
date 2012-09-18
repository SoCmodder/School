/*
Name: Dog Age Converter

Author: Brent Powers

Description: This the first c++ program. We are creating a program thet will
             acuratlly convert dog years to human years and vice versa.

Date: 1-28-2004

*/


#include <iostream>
using namespace std;
int main() 

{
float dogage; //Variable for Dog's age in Dog years
float humanage; //Variable for Dog's age in Human (calander) years 
int dogweight; //Variable for Dog's weight
int increment; //Place for the calculation based on dogs age
char dogorhuman; //Used to help decide what calculation to do

cout<<"Enter H to calculate a dog's age in human years, "
 << "or enter D to calculate how old a dog needs to be "
 << "to equal human age:";
cin>>dogorhuman;//User is asked to chose what type of calculation they would like to performe
cout<<"Enter dog's weight (in pounds):";
cin>>dogweight; //User enters dog's weight so it can be used in determining the dogs Age Increment
if (dogweight >= 0 && dogweight <= 20) 
increment = 4;
else if (dogweight <= 50)
increment = 5;
else if (dogweight <= 90)
increment = 6;
else increment = 7;// the last few lines set the age increment based on weight
if (dogorhuman == 'H')//Following is for calculation of a dog's age in human years
{
cout<<"Enter age (in calendar years):";
cin>>humanage;
dogage = 16+((humanage - 1) * increment);//made the calculation
cout<<"A "<<humanage<<"-year old dog is equivalent to a human who is "<<dogage<<" years old.\n";
}//displayed results
else if (dogorhuman == 'D')//Following is for calculation for converting from human years to dog years
{
cout<<"Enter age (in HUMAN years):";
cin>>dogage;
humanage = (dogage - 16 + increment) / increment;//making calculation
cout<<"to be equivalent to "<<dogage<<" human years, the dog must be "<<humanage<<" years old.\n";
}//desplayed results
return 0;
}


