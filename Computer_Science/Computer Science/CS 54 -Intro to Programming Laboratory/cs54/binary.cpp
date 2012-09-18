#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
 double x1,x2,x3,dec;
 ifstream input;
 ofstream output;
 input.open("input.txt");//opens input
 output.open("numbers.txt");//opens output file
 if (input.fail())//checks for fail open
  {
   cout<<"input.txt did not open";
   exit(1);
  }
 if (output.fail())
  {
   cout<<"numbers.txt did not open";
   exit(1);
  }
 while(!input.eof())
 {
   input>>x1>>x2>>x3;//inputs values
   dec=((x1*pow(2.0,2.0))+(x2*pow(2.0,1.0))+x3);//converts to number
   if(!input.eof())
   output<<dec<<endl;
 }
 input.close( );//closes
 output.close( );
 return 0;
}
