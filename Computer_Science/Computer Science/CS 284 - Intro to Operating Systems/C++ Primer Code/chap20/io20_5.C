// #include <iostream>
#include <iostream.h>
#include <vector>

/** 
 **
  stanl@john:d.ch20 225 : a.out < io8.out
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
operator<<( ostream& os, const WordCount& wd ) 
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

istream& 
operator >>( istream &is, WordCount &wd ) 
{
/* format of WordCount object to be read:
 * <2> string
 * <7,3> <12,36> 
 */

    int ch;

    /* read in less-than token. if not present
     * place istream in bad state and exit
     */
    if ((ch = is.get()) != '<' ) 
    {
        // is.setstate( ios_base::badbit );
        return is;
    }

    // read in size value. 
    int occurs;
    is >> occurs;

    // grab >; not checking for error
    while ( is && (ch = is.get()) != '>' ) ;

    is >> wd._word;

    // read in the locations;
    // format of each location: < line, col >
    for ( int ix = 0; ix < occurs; ++ix ) 
    {
        int line, col;

        // extract values
        while (is && (ch = is.get())!= '<' ) ;
        is >> line; 

        while (is && (ch = is.get())!= ',' ) ;
        is >> col; 

        while (is && (ch = is.get())!= '>' ) ;

        wd._occurList.push_back( Location( line, col ));
    }
    return is;
}

int main() 
{
    WordCount readIn;

    // operator>>( cin, readIn )
    cin >> readIn;
 
    if ( !cin ) {
        cerr << "WordCount input error" << endl; 
        return -1;
    }

    // operator<<( cout, readIn )
    cout << readIn << endl;
}


