#include <iostream>
using namespace std;

void reverse(char s1[]); //function that reverse the string
void search(char s1[], int& indexOfNull);//function that finds the null

int main()
{
  char s1[10];//the string 
  char anothertime;
  do
  {
  cout<<endl<<endl<<"Please input the first string: ";
  cin>>s1;
  reverse(s1);//calls the reverst function
  cout<<endl<<"The reverse string is: "<<s1<<endl;
  cout<<"Do you what to continue again(y/n): ";
  cin>>anothertime;//user decides to go another time
  }while((anothertime=='y')||(anothertime=='Y'));

  return 0;
}

void reverse(char s1[])//function to reverse string
{
  char temp;
  int indexOfNull=-1;//number for where the null can be found
  search(s1, indexOfNull);//calls the search for null string
  cout<<indexOfNull;
  indexOfNull=indexOfNull-1;
 for(int i=0;i<=((indexOfNull)/2);i++)//for loop to swap the values of string
   {
    temp=s1[indexOfNull-i];
    s1[indexOfNull-i]=s1[i];
    s1[i]=temp;
   }
  
return;
}

void search(char s1[], int& indexOfNull)//finds the null
{
  int i=0;
  bool found=false;
  while((found==false)&&(i<10))//repeats for all values or until finds it
   {
    if (s1[i]=='\0')
     found=true;
    else
     i++;
    }
   indexOfNull=i;
  return;
} 
  
   

