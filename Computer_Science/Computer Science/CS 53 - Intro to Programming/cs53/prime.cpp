#include <iostream>
using namespace std;





int main()
{
  int thousand[1000];
  int prime[500];
  int i;
  int loop;
  int divide;
  double temp;
  int test;
  int place=0;
  int outp=0;
  int evaluate;
  float result;
  for(i=0;i<=999;i++)
   {
    thousand[i]=(i+1);
   }
   
   for(loop=1;loop<=1000;loop++)
    {
    
    for(divide=loop-1;divide>0;divide--)
     {
      temp=loop/divide;
     evaluate=temp/1;
     result=temp-(evaluate*temp);
     test=0;
     if (result==0)
     {
      test=test+1;
     }
     }
     if (test==1)
      {
      prime[place]=loop;
      place++;
      }
      }
      
     for(outp=0;outp<=500;outp++)
     {
     cout<<prime[outp];
     }
     
     return 0;
     
     }
      
