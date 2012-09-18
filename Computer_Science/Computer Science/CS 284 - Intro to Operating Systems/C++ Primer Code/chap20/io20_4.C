// #include <iostream>
#include <iostream.h>
#include <vector>

/**
 **
 Occurrences: 
 <10> rosebud
 <11,3>  <11,8>  <14,2>  <34,6>  <49,7>  <67,5>  
 <81,2>  <82,3>  <91,4>  <97,8>  
 **
 **/

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

ostream& operator <<( ostream& os, const Location& lc ) 
{ 
    // output of a Loc object:  < 10,37 >
    os << "<" << lc._line 
       << "," << lc._col << "> ";

    return os;
}

ostream& 
operator <<( ostream& os, const WordCount& wd ) 
{
    os << "<" << wd._occurList.size() << "> " 
       << wd._word << endl;

    int cnt = 0, onLine = 6;
    vector<Location>::const_iterator first = wd._occurList.begin();
    vector<Location>::const_iterator last  = wd._occurList.end();

    for ( ; first != last; ++first ) 
    { 
	// os << Location
	os << *first << " ";

	// formatting: 6 to a line
	if ( ++cnt >= onLine )
	   { os << "\n"; cnt = 0;  }

    }
    return os;
}

int main() 
{
    WordCount search( "rosebud" );

    // for simpilicity, hand code 8 occurrences
    search.found(11,3);  search.found(11,8);
    search.found(14,2);  search.found(34,6);
    search.found(49,7);  search.found(67,5);
    search.found(81,2);  search.found(82,3);
    search.found(91,4);  search.found(97,8);

    cout << "Occurrences: " << "\n" 
         << search << endl;

    return 0;
}
