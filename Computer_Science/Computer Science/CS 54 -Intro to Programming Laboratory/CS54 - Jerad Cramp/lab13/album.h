/* programmer: robertoMurillo   date: 11/16/05 *
 * instructor: price            class: cs54d   *
 * file: album.h                               *
 * purpose: class file for Album.              */
 
#ifndef ALBUM_H
#define ALBUM_H

#include "song.h"
#include <iostream>
using namespace std;

/********** CLASS **********/

class Album
{
  public:               
    Album();
    Album( string title1, int year1 );
    void addTrack( Song song1 );
    // accessors
    string getTitle()const;
    int getRelYr()const;    
    int getNumTracks()const;
    // mutators
    void setTitle( string title1 );
    void setRelYr( int year );
    friend ostream& operator <<( ostream& out, Album album1 );
      
  private:
    string title; // name of the album
    int relYr; // the year the album was released
    int numTracks; // the number of tracks on the album
    Song track[30]; // the tracks included in the album
};

/********** CLASS **********/

#endif
