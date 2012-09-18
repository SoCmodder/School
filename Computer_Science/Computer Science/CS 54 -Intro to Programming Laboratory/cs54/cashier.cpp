#include<iostream>
using namespace std;
int main()
{
/* Declaration of Variables*/
float price;
float total;
int items;
char yesno;
int count;
float discount;

/* Function that will be used each time*/
do
    {
    total = 0;
    cout<<"Enter total numbe of items purchased:";
    cin>>items;
    
    for(count=1;count<=items;count++)
        {
        cout<<"Enter the proce of item "<<count<<":";
        cin>>price;
        total = total + price;
        }
     
        /*Place to evaluate and award discount*/
     
     if ((total>=200.0)&&(items>=5))
          discount=(total/10);  
     else if((total>=100) && (items>=5))
          discount=(total/20);
     else discount=0;     
     cout<<"Discount given: "<<discount<<endl;
     cout<<"Total Price: "<<total-discount<<endl;
     cout<<"Arethere more customers(y/n): ";
     cin>>yesno;
     } while (yesno == 'y');
 return 0;
} 
      
    
      
