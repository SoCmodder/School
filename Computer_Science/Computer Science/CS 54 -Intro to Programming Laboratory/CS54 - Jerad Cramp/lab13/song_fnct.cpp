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

ostream& operator <<( ostream& out, Song song1 )
{
  out <<"  Track: " <<song1.getTrack()<<endl
      <<"  Artist: "<<song1.getArtist()<<endl
      <<"  CD Title: " << song1.getCdTitle() << endl
      <<"  Song Title: " <<  song1.getSongTitle() << endl
      <<"  Genre: " << song1.getGenre() << endl
      <<"  Label: " << song1.getLabel() << endl
      <<"  Duration: " << song1.getDuration() << endl
      <<"  Bitrate: " << song1.getBitrate() << endl;
      
  return out;
}

string Song::getArtist()const
{
  return artist;
}

string Song::getCdTitle()const
{
  return cd_title;
}

string Song::getSongTitle()const
{
  return song_title;
}

string Song::getGenre()const
{
  return genre;
}

string Song::getLabel()const
{
  return label;
}

int Song::getDuration()const
{
  return duration;
}

int Song::getBitrate()const
{
  return bitrate;
}
          
/********** DEFINITIONS **********/
   
