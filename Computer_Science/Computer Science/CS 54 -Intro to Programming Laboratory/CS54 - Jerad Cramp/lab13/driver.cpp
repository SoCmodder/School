/* programmer: robertoMurillo   date: 11/16/05 *
 * instructor: price            class: cs54d   *
 * file: driver.cpp                            *
 * purpose: class file for Album.              */
   
#include <iostream>
#include "song.h"
#include "album.h"
using namespace std;

int main()
{
  // creates album
  Album album1( "Rumors", 1977 );
  // creates songs
  Song  song1("Lindsay Buckingham", "Rumors", "Second Hand News", "Rock",
         "unknown", 1, 200, 192), song2("Fleetwood Mac", "Rumors", 
         "Don't Stop", "Rock", "unknown", 2, 192, 192); 
  
  // adds both songs to the track array
  album1.addTrack(song1);
  album1.addTrack(song2);
  
  // displays everything
  cout << album1 << endl;
  
  return 0;
}
