// #include <iostream>
#ifndef WordCount_H
#define WordCount_H

#include <iostream.h>
#include <vector>

class Location {
    friend ostream& operator<<( ostream&, const Location& );
public:
    Location( int line, int col ) 
			: _line( line ), _col( col ) {}
private:
    short _line;
    short _col;
};

class WordCount {
    friend ostream& operator<<( ostream&, const WordCount& );
    friend istream& operator>>( istream&, WordCount& );

public:
        WordCount() {}
	WordCount( string word ) : _word( word ) {}
        WordCount( string word, int ln, int col )
                : _word( word ){ insert_location( ln, col ); }

        string word()   const { return _word; }
        int    occurs() const { return _occurList.size(); }
        void   found( int ln, int col )
                    { insert_location( ln, col ); }

private:
        void insert_location( int ln, int col )
                { _occurList.push_back( Location( ln, col )); }

        string             _word;
        vector< Location > _occurList;
};

#endif

