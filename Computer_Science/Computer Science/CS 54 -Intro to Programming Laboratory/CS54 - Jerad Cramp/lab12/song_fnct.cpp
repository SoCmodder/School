/* programmer: robertoMurillo   date: 11/9/05 *
 * instructor: price            class: cs54d  *
 * file: song_fnct.cpp                        *
 * purpose: using classes to make a song class*/

#include <iostream>
#include <string>
#include "song.h"
using namespace std;

/********** DEFINITIONS **********/

int Song::getTrack()const
{
  return track;
}

void Song::setBitrate( int quality )
{
  bitrate = quality;
}

Song::Song()
{
  artist = "none";
  cd_title = "where";
  song_title = "noclass";
  genre = "none";
  label = "who";
  track = 0;
  duration = 5;
  bitrate = 128;
}

Song::Song(string singer, string cdName, string songName, string category,
           string publisher, int numTrack, int songLength, int quality)
{
  artist = singer;
  cd_title = cdName;
  song_title = songName;
  genre = category;
  label = publisher;
  track = numTrack;
  duration = songLength;
  bitrate = quality;
}
          
/********** DEFINITIONS **********/
   
