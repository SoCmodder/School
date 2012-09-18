/* programmer: robertoMurillo   date: 11/9/05 *
 * instructor: price            class: cs54d  *
 * file: driver.cpp                           *
 * purpose: using classes to make a song class*/
   
#include <iostream>
#include <string>
#include "song.h"
using namespace std;

int main()
{
  Song song1( "michael jackson", "Number Ones", "Billie Jean", "Pop/Rock",
              "Island", 4, 300, 192 );
  Song song2;
              
  cout << song1.getTrack() << endl;
  
  song1.setBitrate(192);
  
  return 0;
}
