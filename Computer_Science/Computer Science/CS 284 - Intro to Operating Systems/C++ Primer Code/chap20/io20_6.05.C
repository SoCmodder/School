// #include <fstream>
#include <fstream.h>
#include <string>

/**
 ** requires that these files exist in the directory
 ** this program is executed within
 **
 stanl@john:d.ch20 249 : a.out

 ok: file open: Melville
 ok: file open: Joyce
 ok: file open: Musil
 ok: file open: Proust
 ok: file open: Kafka
 **
 **/


const int fileCnt = 5;
string fileTabl[ fileCnt ] = {
    "Melville", "Joyce", "Musil", "Proust", "Kafka"
};

int main()
{
    ifstream inFile; // not attached to any file

    for ( int ix = 0; ix < fileCnt; ++ix )
    {
          inFile.open( fileTabl[ix].c_str() );
	  if ( ! inFile ) 
	       cerr << "oops! unable to open file: "
		    << fileTabl[ix] << endl;
	  else cerr << "ok: file open: "
		    << fileTabl[ix] << endl;

          // ... process file

          inFile.close();
    }
}
