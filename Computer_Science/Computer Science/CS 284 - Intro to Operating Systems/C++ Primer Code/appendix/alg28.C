#include <algorithm>
#include <list>
#include <utility>
#include <iostream.h>
	
class equal_and_odd{
public:
	bool operator()( int ival1, int ival2 )
        {
                 // are the two values equal, and either
                 // both zero, or both odd?

	         return ( ival1 == ival2 && 
		        ( ival1 == 0 || ival1%2 )) 
			  ? true : false;
	}
};
	
int main() 
{
	int ia[] =  { 0,1,1,2,3,5,8,13 };
	int ia2[] = { 0,1,1,2,4,6,10   };
		
	pair<int*,int*> pair_ia = mismatch( ia, ia+7, ia2 );

// generates: first mismatched pair: ia: 3 and ia2: 4

        cout << "first mismatched pair: ia: "
	     << *pair_ia.first << " and ia2: "
             << *pair_ia.second << endl;
		
	list<int,allocator> ilist(  ia,  ia+7  );
	list<int,allocator> ilist2( ia2, ia2+7 );
		
	typedef list<int,allocator>::iterator iter;
	pair<iter,iter> pair_ilist =
		mismatch( ilist.begin(),  ilist.end(),
			  ilist2.begin(), equal_and_odd() );
		
// generates: first mismatched pair either not equal or not odd: 
//                  ilist: 2 and ilist2: 2

        cout << "first mismatched pair either not equal or not odd: \n\tilist: "
	     << *pair_ilist.first << " and ilist2: "
	     << *pair_ilist.second << endl;
		
	return 0;
}
