#include <iostream>
using namespace std;


void display_initial_array(int Array1[], int Array2[]);
void evaluate(int Array1[], int Array2[], int& array1index, int& array2index, int& array3index, int Array3[]);
void usearray1(int Array1, int& array1index, int& array3index, int Array3[]);
void usearray2(int Array2, int& array2index, int& array3index, int Array3[]);
void finalterm(int Array1[], int Array2[], int Array3[], int& array1index, int& array2index, int& array3index);
void finaldisplay(int Array3[]);

int main()
{
int Array1[10]={5,10,15,20,25,27,30,31,40,50};
int Array2[10]={4,12,13,22,26,28,29,32,39,51};
int Array3[20];
int array1index=0;
int array2index=0;
int array3index=0;
display_initial_array(Array1, Array2); 
do
{
 
 if (array3index==19)
  { 
      finalterm(Array1, Array2, Array3, array1index, array2index, array3index);
  }
 else
   evaluate(Array1, Array2, array1index, array2index, array3index, Array3);
   
 }while(array3index<=19); 
finaldisplay(Array3);

return 0;
}

void finalterm(int Array1[], int Array2[], int Array3[], int& array1index, int& array2index, int& array3index)
{ 
 if (array1index==9)
  {
   Array3[array3index]=Array1[array1index];
   array1index++;
   array3index++;
  } 
 if (array2index==9)
  {
   Array3[array3index]=Array2[array2index];
   array1index++;
   array3index++;
  }
return;
}  


void display_initial_array (int Array1[], int Array2[])
 {
  int iloop;
  cout<<"The Giver arrays are:"<<endl;
  cout<<"Array1: ";
  for(iloop=0;iloop<=8;iloop++)
   { 
    cout<<Array1[iloop]<<",";
    }
   cout<<Array1[9]<<endl<<"Array2: ";
  for(iloop=0;iloop<=8;iloop++)
   {
   cout<<Array2[iloop]<<",";
    }
   cout<<Array2[9]<<endl; 
   return;
  }
 


void evaluate(int Array1[], int Array2[], int& array1index, int& array2index, int& array3index, int Array3[])
{
  
  if (Array1[array1index]<Array2[array2index])
     usearray1(Array1[array1index], array1index, array3index, Array3);
  
  if (Array2[array2index]<Array1[array1index])
      usearray2(Array2[array2index], array2index, array3index, Array3);
  
   return;
}

void usearray1(int Array1, int& array1index, int& array3index, int Array3[])
{
 Array3[array3index]=Array1;
 array1index++;
 array3index++;
  return;
}

void usearray2(int Array2, int& array2index, int& array3index, int Array3[])
{
 Array3[array3index]=Array2;
 array2index++;
 array3index++;
  return;
} 

void finaldisplay(int Array3[])
{
 int iloop;
 cout<<"The merged array is:"<<endl<<endl<<"Array3: ";
 for(iloop=0;iloop<=18;iloop++)
  {
  cout<<Array3[iloop]<<",";
  }
 cout<<Array3[19]<<endl<<endl;
 
 return;
}
 
