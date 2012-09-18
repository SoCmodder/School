#ifndef LASTLAB_H
#define LASTLAB_H

#include <iostream>
using namespace std;

class team
{
public:
       
       void Average();
       
       team operator+(team t1);
       
       friend void compare(team t1, team t2);  
           
      
      
private:

       short member1[4];
       short member2[4];
       short member3[4];
       short member4[4];
       float average; 
};

#endif



