#include <iostream>
#include "lastlab.h"
using namespace std;

void team::Average()
       {
         int sum=0;
         for(int i=0;i<5;i++)
          {
           sum=sum+member1[i];
           }
         for(int i=0;i<5;i++)
          {
           sum=sum+member2[i];
           }
         for(int i=0;i<5;i++)
         {
          sum=sum+member3[i];
          }
         for(int i=0;i<5;i++)
          {
           sum=sum+member4[i];
          }
          average=((sum/400)*100);
        } 
        
team team::operator+(team t1)
    {
      team temp;
      temp.average=(average+t1.average);
      return temp;
    }
    
    
void compare(team t1, team t2)
  {
    if((t1.member1[0]+t1.member1[1]+t1.member1[2]+t1.member1[3])>(t2.member1[0]+t2.member1[1]+t2.member1[2]+t2.member1[3]))
		cout<<endl<<"Team One: "<<(((t1.member1[0]+t1.member1[1]+t1.member1[2]+t1.member1[3])/4)*100)<<"%"<<endl;
	if((t1.member1[0]+t1.member1[1]+t1.member1[2]+t1.member1[3])<(t2.member1[0]+t2.member1[1]+t2.member1[2]+t2.member1[3]))
		cout<<endl<<"Team Two: "<<(((t2.member1[0]+t2.member1[1]+t2.member1[2]+t2.member1[3])/4)*100)<<"%"<<endl;
	if((t1.member2[0]+t1.member2[1]+t1.member2[2]+t1.member2[3])>(t2.member2[0]+t2.member2[1]+t2.member2[2]+t2.member2[3]))
		cout<<endl<<"Team One: "<<(((t1.member2[0]+t1.member2[1]+t1.member2[2]+t1.member2[3])/4)*100)<<"%"<<endl;
	if((t1.member2[0]+t1.member2[1]+t1.member2[2]+t1.member2[3])<(t2.member2[0]+t2.member2[1]+t2.member2[2]+t2.member2[3]))
		cout<<endl<<"Team Two: "<<(((t2.member2[0]+t2.member2[1]+t2.member2[2]+t2.member2[3])/4)*100)<<"%"<<endl;
	if((t1.member3[0]+t1.member3[1]+t1.member3[2]+t1.member3[3])>(t2.member3[0]+t2.member3[1]+t2.member3[2]+t2.member3[3]))
		cout<<endl<<"Team One: "<<(((t1.member3[0]+t1.member3[1]+t1.member3[2]+t1.member3[3])/4)*100)<<"%"<<endl;
	if((t1.member3[0]+t1.member3[1]+t1.member3[2]+t1.member3[3])<(t2.member3[0]+t2.member3[1]+t2.member3[2]+t2.member3[3]))
		cout<<endl<<"Team Two: "<<(((t2.member3[0]+t2.member3[1]+t2.member3[2]+t2.member3[3])/4)*100)<<"%"<<endl;
	if((t1.member4[0]+t1.member4[1]+t1.member4[2]+t1.member4[3])>(t2.member4[0]+t2.member4[1]+t2.member4[2]+t2.member4[3]))
		cout<<endl<<"Team One: "<<(((t1.member4[0]+t1.member4[1]+t1.member4[2]+t1.member4[3])/4)*100)<<"%"<<endl;
	if((t1.member4[0]+t1.member4[1]+t1.member4[2]+t1.member4[3])<(t2.member4[0]+t2.member4[1]+t2.member4[2]+t2.member4[3]))
		cout<<endl<<"Team Two: "<<(((t2.member4[0]+t2.member4[1]+t2.member4[2]+t2.member4[3])/4)*100)<<"%"<<endl;
  }



