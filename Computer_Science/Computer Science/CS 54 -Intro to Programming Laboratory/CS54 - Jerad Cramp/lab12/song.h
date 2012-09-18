/* programmer: robertoMurillo   date: 11/9/05 *
 * instructor: price            class: cs54d  *
 * file: song.h                               *
 * purpose: using classes to make a song class*/
 
#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <iostream>
using namespace std;

/********** CLASS **********/

class Song
{
  private:
    string artist;
    string cd_title;
    string song_title;
    string genre;
    string label;
    int track;
    int duration;
    int bitrate;
                                      
  public:  
    // constructors
    Song();
    Song( string artist, string cd_title, string song_title, string genre,
          string label, int track, int duration, int bitrate );
    // accessors
    int getTrack()const;
    // mutators
    void setBitrate( int a );
};
    
/********** CLASS **********/

#endif
