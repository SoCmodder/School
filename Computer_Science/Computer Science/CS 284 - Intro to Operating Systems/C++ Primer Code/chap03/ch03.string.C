// #include <iostream>
#include <iostream.h>

/*******
 *******
Alice Emma has long flowing red hair. Her Daddy says when the 
wind blows through her hair, it looks almost alive, like a fiery 
bird in flight. A beautiful fiery bird, he tells her, magical but 
untamed. "Daddy, shush, there is no such thing," she tells him, at 
the same time wanting him to tell her more. Shyly, she asks, 
"I mean, Daddy, is there?" 

Words read: 65

the/The: 2
it/It: 1

non-vowels read: 190

a: 22
e: 30
i: 24
o: 10
u: 7
 *******
 *******/


class String;
istream& operator>>( istream&, const String& );
ostream& operator<<( ostream&, const String& );

class String {
public:
	String( const char* = 0 );
	String( const String& );
	~String();

	String& operator=( const String& );
	String& operator=( const char* );

	bool operator==( const char* );
	bool operator==( const String& );

	char& operator[]( int );
	int size() { return _size; };
	char * c_str() { return _string; }

private:
	int   _size;
	char *_string;
};

#include <string.h>

inline bool			
String::operator==(const String &s)		
{
    if ( _size != s._size ) 
	 return false;

    return strcmp( _string, s._string ) ? false : true; 
}

inline bool String::operator==(const char *s)
{
    return strcmp( _string, s ) ? false : true; 
}

// default constructor
inline String::String( const char *str ) 
{
	if ( ! str ) {
	     _size = 0; 
	     _string = 0;
	}
	else {
		_size = strlen( str );
		_string = new char[ _size + 1 ];
		strcpy( _string, str );
	}
}

// copy constructor
inline String::String( const String &rhs )
{
	_size = rhs._size;
	if ( ! rhs._string )
	     _string = 0;
	else 
	{
		_string = new char[ _size + 1 ];
		strcpy( _string, rhs._string );
	}
}

inline String::~String() { delete [] _string; }

inline String& String::operator=( const char *s )
{
    if ( ! s ) 
    { 
	   _size = 0; 
	   delete [] _string;
	   _string = 0; 
    }
    else 
    {
   	_size = strlen( s );
   	delete [] _string;
   	_string = new char[ _size + 1 ];
   	strcpy( _string, s );
    }

    return *this;
}

inline String& String::operator=( const String &rhs )
{
	if ( this != &rhs ) 
	{
    		delete [] _string;
    		_size = rhs._size;
    		if ( ! rhs._string ) 
			_string = 0; 
    		else 
		{
			_string = new char[ _size + 1 ];
			strcpy( _string, rhs._string );
    		}
    	}
    
	return *this;
}

#include <assert.h>

inline char& String::operator[]( int elem )
{
    	assert( elem >= 0 && elem < _size );
    	return _string[ elem ];
}

#include <iomanip.h>

inline istream& operator>>( istream &io, String &s )
{
    	// artificial limit of 4096 characters read
    	const int limit_string_size = 4096;
    
    	char inBuf[ limit_string_size ];
    
    	// setw is part of iostream library
    	// limits characters read to value-1
    	io >> setw( limit_string_size ) >> inBuf;

    	s = inBuf; // String::operator=( const char* );
    	return io;
}

inline ostream& operator<<( ostream& os, String& s )
{
    	return os << s.c_str();
}

int main()
{
    int aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0,
        theCnt = 0, itCnt = 0, wdCnt = 0, notVowel = 0;

    // invokes String( const char* = 0 )
    String buf, the( "the" ), it( "it" );

    // invokes operator>>( ostream&, String& )
    while ( cin >> buf ) {
        ++wdCnt;

        // invokes operator<<( ostream&, const String& )
        cout << buf << " ";
    
        if ( wdCnt % 12 == 0 )
	     cout << endl;

        // invokes String::operator=(const String&) and
        //         String::operator=( const char* );
        if ( buf == the || buf == "The" )
                 ++theCnt;
        else
        if ( buf == it || buf == "It" )
                 ++itCnt;

        // invokes String::size()
        for ( int ix = 0; ix < buf.size(); ++ix )
        {
            // invokes String::operator[](int)
            switch( buf[ ix ] )
            {
                    case 'a': case 'A': ++aCnt; break;
                    case 'e': case 'E': ++eCnt; break;
                    case 'i': case 'I': ++iCnt; break;
                    case 'o': case 'O': ++oCnt; break;
                    case 'u': case 'U': ++uCnt; break;
                    default: ++notVowel; break;
            }
        }
    }

    cout << "\n\n"
         << "Words read: " << wdCnt << "\n\n"
         << "the/The: " << theCnt << "\n"
         << "it/It: " << itCnt << "\n\n"
         << "non-vowels read: " << notVowel << "\n\n"
         << "a: " << aCnt << "\n"
         << "e: " << eCnt << "\n"
         << "i: " << iCnt << "\n"
         << "o: " << oCnt << "\n"
         << "u: " << uCnt << endl;
}

