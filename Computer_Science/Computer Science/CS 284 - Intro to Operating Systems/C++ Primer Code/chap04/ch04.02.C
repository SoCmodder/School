// #include <iostream>
// #include <cassert>

#include <vector>
#include <iostream.h>
#include <assert.h>

/**
 ** !!ok: executed with no errors!
 **/

int main()
{
	int ia[ 10 ] = { 0,1,2,3,4,5,6,7,8,9 };
	vector< int > ivec( 10 );

	int ix_vec = 0, ix_ia = 9;
	while ( ix_vec < 10 )
   	        ivec[ ix_vec++ ] = ia[ ix_ia-- ];

	int *pia = &ia[9];
	int error_cnt = 0;

	vector< bool > status_vec( 10 );
	vector< int >::iterator iter = ivec.begin();

	int ix = 0;
	while ( iter != ivec.end() )
	{
   		if( *iter++ != *pia-- ) {
		     ++error_cnt;
		     status_vec[ ix ] = false;
		} else status_vec[ ix ] = true;
		++ix;
	}

	if ( ! error_cnt )
		cout << "!!ok: executed with no errors!\n";
	else {
		cout << "?? oops: " << error_cnt << "errors: ";
		vector<bool>::iterator biter = status_vec.begin();
		for ( int ix = 0; biter != status_vec.end(); ++biter, ++ix )
			if ( ! *biter )
			     cout << '#' << ix << ' ';
		cout << endl;
	}
}

