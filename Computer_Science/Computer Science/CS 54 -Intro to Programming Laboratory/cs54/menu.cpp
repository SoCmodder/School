#include<iostream>
using namespace std;
int main ()
{
char choice;//variable for the users choice
float numberone;//a number used in calculations
float numbertwo;//another numbet used in calculations
float counter;//the counter for the factorial
float output;//the variable for the calculation

do //keeps program running until user wants to quit
{

cout<<"1) Perform addition of two integers read from the user."<<endl;
cout<<"2) Perform multiplication of two integers read from user."<<endl;
cout<<"3) Find factorial of a number input by the user."<<endl;
cout<<"4) Quit the program."<<endl;
cout<<"Input your choice: ";
cin>>choice;//user enters what they want to do
  
   switch (choice)
   {
      case '1': //the addition function
        cout<<"Please input your first number: "; 
        cin>>numberone;
        cout<<"Please input your second number: ";
        cin>>numbertwo;
        output=numberone+numbertwo;
        cout<<"The sum of your numbers are: "<<output<<endl;
      break;
      
      case '2'://the multiplication function
        cout<<"Please input your first numbet:";
        cin>>numberone;
        cout<<"Please input your second numbet:";
        cin>>numbertwo;
        output=numberone*numbertwo;
        cout<<"The product of your number is: "<<output<<endl;
      break;
      
      case '3' ://the factorial function
        cout<<"Please input your number:";
        cin>>numberone;
           output=1;
           for(counter=numberone;counter>0;counter--)
             {
              output=output*counter;//computes factorial
              }
            cout<<"The factorial for your number is: "<<output<<endl;
      break;
     case '4' : 
                 //blank case so if 4 is entered it won't go to the default
      break;
    
      default:
        cout<<"Please enter a number 1-4: ";
   }     
 } 
while (choice!='4');//keeps user in loop untill they enter 4
cout<<"Thank you for using the program."<<endl;
return 0;
}             
