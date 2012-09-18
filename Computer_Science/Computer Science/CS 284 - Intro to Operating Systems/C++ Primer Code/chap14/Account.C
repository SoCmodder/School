#include "Account.h"

unsigned int Account::
get_unique_acct_nmbr() const
{
	static unsigned int acct_nmbr = 1000000;
	return ++acct_nmbr;
}

/* init_heap_array(),
 *     declared as a static member function,
 *     provides for allocation and initialization
 *     of heap array of class objects.
 *
 * init_values: initial value pairs for array elements
 * elem_count: number of elements in array
 *             if 0, array is size of init_values vector.
 */
Account* Account::
init_heap_array( vector<value_pair> &init_values,
                 vector<value_pair>::size_type elem_count ) 
{
    vector< value_pair >::size_type 
 	    vec_size = init_values.size();

    if ( vec_size == 0 && elem_count == 0 )
    	 return 0;

    // size of array to allocate is either elem_count
    // or, if elem_count is 0, size of vector ...
    size_t elems = 
	elem_count ? elem_count : vec_size;

    // grab a chunk of raw memory to store array
    char *p = new char[sizeof(Account)*elems];

    // individually initialize each array element 
    int offset = sizeof( Account );
    for ( int ix = 0; ix < elems; ++ix ) 
    {
 	// offset to the ixth element.
 	// if an initial value pair is provided, 
 	//    pass that pair to the constructor;
 	// otherwise, invoke the default constructor
 
 	if ( ix < vec_size )
      	     new( p+offset*ix ) Account( init_values[ix].first,
                                         init_values[ix].second );
 	else new( p+offset*ix ) Account;
    }
    
    // ok: elements allocated and initialized; 
    //     return pointer to first element
    return (Account*)p;
}

void Account::
dealloc_heap_array( Account *ps, size_t elems ) 
{
    	for ( int ix = 0; ix < elems; ++ix ) 
              ps[ix].Account::~Account();
    
    	delete [] reinterpret_cast<char*>(ps);
}
 

