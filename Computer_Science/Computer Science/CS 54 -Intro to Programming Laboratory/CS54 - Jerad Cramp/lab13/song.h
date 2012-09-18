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
    friend ostream& operator <<( ostream& out, Song song1 );
    // constructors
    Song();
    Song( string artist, string cd_title, string song_title, string genre,
          string label, int track, int duration, int bitrate );
    // accessors
    string getArtist()const;
    string getCdTitle()const;
    string getSongTitle()const;
    string getGenre()const;
    string getLabel()const;
    int getTrack()const;
    int getDuration()const;
    int getBitrate()const;
    // mutators
    void setBitrate( int a );
};
    
/********** CLASS **********/

#endif
