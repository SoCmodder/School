#include <iostream>
#include "fraction.h"
using namespace std;

CFraction addfrac(CFraction frac1, CFraction frac2);

int main()
{
  CFraction frac1, frac2, frac3;
  frac1.readIn();
  frac2.readIn();
  frac2.setNumer(5);
  
  cout<<"Fractions 1 = ";
  frac1.print();
  cout<<endl<<"Fraction 2 = ";
  frac2.print();
  frac2=frac2.recipricol();
  cout<<endl<<"Recipricol of Fraction 2 is: "<<endl;
  frac2.print();
  frac3=addfrac(frac1, frac2);
  cout<<endl<<"The sum of the reciprical of the second fraction and the first is: ";
  frac3.print();
  cout<<endl<<"exiting..."<<endl;
  return 0;
 }
 
CFraction addfrac(CFraction frac1, CFraction frac2)
{
 CFraction sumfrac;
 int num, dem;
 sumfrac.setNumer(((frac1.getNumer())*(frac2.getDenom()))+((frac2.getNumer())*(frac1.getDenom())));
 sumfrac.setDenom((frac1.getDenom())*(frac2.getDenom()));
 
 
 return sumfrac;
}
