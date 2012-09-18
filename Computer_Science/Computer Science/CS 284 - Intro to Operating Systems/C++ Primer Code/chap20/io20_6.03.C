// #include <fstream>
#include <fstream.h>
#include <string>

/**
 **

 stanl@john:d.ch20 243 : cat copy.out
 23 109 45 89 6 34 12 90 34 23 56 23 8 89 23

 stanl@john:d.ch20 244 : a.out

 filename: copy.out
 23 109 45 89 6 34 12 90 34 23 56 23 8 89 23

 **
 **/

int main()
{

    string file_name;
    cout << "filename: "; cin >> file_name;

    ifstream inFile( file_name.c_str() );
    if ( !inFile ) {
         cerr << "unable to open input file: "
              << file_name << " -- bailing out!\n";
         return -1;
    }

    char ch;
    while ( inFile.get( ch ))
            cout.put( ch );
}
