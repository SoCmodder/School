// #include <iostream>
#include <iostream.h>
#include <vector>

/*****
 *****
 ivec[ 0 ] 9 goes to 18
 ivec[ 1 ] 8 goes to 16
 ivec[ 2 ] 7 goes to 14
 ivec[ 3 ] 6 goes to 12
 ivec[ 4 ] 5 goes to 10
 ivec[ 5 ] 4 goes to 8
 ivec[ 6 ] 3 goes to 6
 ivec[ 7 ] 2 goes to 4
 ivec[ 8 ] 1 goes to 2
 ivec[ 9 ] 0 goes to 0
 *****
 *****/

int main()
{
  	int ix, ia[10];
  	for ( ix = 9; ix >= 0; --ix )
       	      ia[ ix ] = 9 - ix;

  	vector<int> ivec( ia, ia+10 );
  	vector<int>::iterator iter = ivec.begin();

  	for ( ix = 0; iter != ivec.end(); ++iter, ++ix )
	{
		cout << "ivec[ " << ix << " ] "
		     << *iter;
        	*iter *= 2;
		cout << " goes to " << *iter << '\n';
	}
}

