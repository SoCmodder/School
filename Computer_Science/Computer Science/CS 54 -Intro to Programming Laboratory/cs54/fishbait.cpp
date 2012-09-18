#include <iostream>
using namespace std;

int main()
{
char speed; //variable for river speed 
int temp;  //variable for river temperature
cout<<"Enter the temperature to the nearest degree in Fahrenheit:";
cin>>temp; //user inputs river's temp
cout<<"Please enter the speed of the river (fast: f, slow: s):";
cin>>speed; //user inputs river's speed
if (temp <= 40)
{
if (speed == 'f')
cout<<"Try using lures"<<endl;
else
cout<<"Try using Live bait"<<endl;
}
else
 if (temp < 60 && temp >40)
{
if (speed == 'f')
cout<<"Try using Lures or Live bait"<<endl;
else
cout<<"Try using Dry flies or Live bait"<<endl;
}
if (temp >= 60)
{
if (speed == 'f')
cout<<"Try using Lures"<<endl;
else
cout<<"Try using dry flies"<<endl;
}
return 0;
}
