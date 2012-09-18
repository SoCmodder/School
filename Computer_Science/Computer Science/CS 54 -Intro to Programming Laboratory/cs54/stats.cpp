#include<iostream>
#include<cmath>
using namespace std;

int factorial (int n);
float probability(int Fact_n, int Fact_x, int FactDiff_nx, float p, int n, int x);
void Display(float prob); 
/* The main function that get user inputs and calls functions and then displays output*/
int main()
{
  int n, x, Fact_n, Fact_x, FactDiff_nx ;
  float prob, p;
  cout << "please enter the sample size (n) :";
  cin >> n;
  cout << "Please enter # of items of a certain characteristic to be chosen from the sample(x) : ";
  cin >> x;
  cout << "Please enter the probability of the characteristic in the sampl size : ";
  cin >> p;
  Fact_n = factorial(n);//computes value to be used in probability function
  Fact_x = factorial (x);//computes value to be used in probability function
  FactDiff_nx = factorial(n-x);
  prob = probability(Fact_n, Fact_x, FactDiff_nx, p, n, x);//calls probability function
  Display(prob);//out puts answer for user
  return 0;
 }

/* The function that will compute the factorial to be entered in to main function*/ 
int factorial (int n)
{
  int fact=1;
  for (int iloop=1;iloop<=n;iloop++)
      {
      fact=fact*iloop;
      }
      return fact;
}
/* The function that will compute the probability for the main function*/
float probability(int Fact_n, int Fact_x, int FactDiff_nx, float p, int n, int x)      	
{ 
 return((Fact_n/(Fact_x * FactDiff_nx)) * pow(p,x) * pow(1-p,n-x));
}
/* Outputs nothing if called*/
void Display(float prob)
{
cout <<prob<< endl;
return;
}
