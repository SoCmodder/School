/*
File: poll.cpp
Name: Brent Powers
Date: 2-17-2004
Email: bkp347@umr.edu
*/
/* 
Program used to compute an exit poll for the recent demecrat primaries
*/

#include<iostream>
using namespace std;

int main( )
{

char candidate;//variable for user to enter which canidate they voted for
char choice;//variable for user to decide if they want to continue or not
int counter;//counter to keep track of the 4 votes at each site
float kerry=0; //tally for kerry votes
float edwards=0; //tally for edwards votes
float dean=0; //tally for dean votes
float other=0; //tally for other votes


do  //loop for each polling site if user enters yes kept in loop 
    {
   
    for(counter=1;counter<=4;counter++) //loop that will poll 4 people at each site 
        {
         cout<<"Which candidate did you vote for:"<<endl;
         cout<<"1. John Kerry"<<endl;
         cout<<"2. John Edwards"<<endl;
         cout<<"3. Howard Dean"<<endl;
         cout<<"4. Other"<<endl;
         cin>>candidate;
         
              switch (candidate)// switch to deferintiate one candidate vote to another
                {
                
                case '1' :
                    kerry=kerry+1;//person voted for kerry
                    break;
                case '2' :
                    edwards=edwards+1;//person voted for edwards
                    break;
                case '3' :
                    dean=dean+1;//person voted for dean
                    break;
                case '4' :
                    other=other+1;//person voted for other
                    break;
                default ://if person entered something else than an expected answer
                    cout<<"Invalid entry. Please enter 1-4:"<<endl;
                    counter=counter-1;//prevents the bad user input being counted as a valid input
                 }
          }
       cout<<"Should I go to another voting place? (Y/N)"<<endl;
       cin>>choice;//user inpute weither they want to go to other site    
     } while((choice=='Y') || (choice=='y'));
     
cout<<"Here are the results of polling "<<(kerry + edwards + dean + other)<<" people:"<<endl;//shows voting results
cout<<"John Kerry got " << kerry << " votes (";
cout.precision(4);
cout.setf(ios::showpoint);//changes the persion and places the decimal point
cout<<((kerry/(kerry+edwards+dean+other))*100.0)<<"%)"<<endl;
cout.precision(0);
cout.unsetf(ios::showpoint);//resets the changed setting to their initial 
cout<<"John Edwards got "<<edwards<<" votes (";
cout.precision(4);
cout.setf(ios::showpoint);
cout<<((edwards/(kerry+edwards+dean+other))*100.0)<<"%)"<<endl;
cout.precision(0);
cout.unsetf(ios::showpoint);
cout<<"Howard Dean got "<<dean<<" votes (";
cout.precision(3);
cout.setf(ios::showpoint);
cout<<((dean/(kerry+edwards+dean+other))*100.0)<<"%)"<<endl;

return 0;
}            
                    
                      
        
        
        
        
        
        
        
