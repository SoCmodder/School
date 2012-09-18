#include "Query.h"

const vector< location,allocator > *NotQuery::_all_locs = 0;
const vector< int,allocator >      *AndQuery::_max_col  = 0;

void
display_location( const vector<location,allocator>*ploc )
{
	cout << "\ndisplay_location vector: \n";

	vector<location, allocator>::const_iterator 
		iter = ploc->begin(), iter_end = ploc->end();

	for ( ; iter != iter_end; ++iter )  {
		cout << "\tfirst: " << ( *iter ).first;
		cout << "\tsecond: " << ( *iter ).second << endl;
	}
}

set<short,less<short>,allocator>*
Query::
_vec2set( const vector<location,allocator> *pvec )
{
	set<short,less<short>,allocator> 
		*ps = new set<short,less<short>,allocator>;

	vector<location,allocator>::const_iterator 
		iter = pvec->begin(), iter_end = pvec->end();
	
	for ( ; iter != iter_end; ++iter ) 
		ps->insert(( *iter ).first );

	return ps;
}

void
AndQuery::
eval()
{
    // add an exception here
    if ( ! _lop || ! _rop )
    {
	 cerr << "Internal error: AndQuery: \n"
	      << "no "
	      << ( _lop ? "right " : "left " )
	      << "operand -- bailing out... \n";
	 return;
    }

    _lop->eval();
    _rop->eval();

    vector< location, allocator >::const_iterator 
        riter = _rop->locations()->begin(),
        liter = _lop->locations()->begin(),
        riter_end = _rop->locations()->end(),
        liter_end = _lop->locations()->end();

    while ( liter != liter_end &&
	      riter != riter_end )
    {
	// while left line number is greater than right
	while ( (*liter).first > (*riter).first )
	{
		++riter;
		if ( riter == riter_end )
		   	{ 
				display_partial_solution(); 
				display_location( &_loc );
				return; 
		   	}
	}

	// while left line number is less than right
	while ( (*liter).first < (*riter).first )
	{
		if (    ((*liter).first == (*riter).first-1 ) &&
			((*riter).second == 0 ) &&
			((*liter).second == (*_max_col)[ (*liter).first ] ))
		{
			_loc.push_back( *liter );
			_loc.push_back( *riter );
			++riter;
			if ( riter == riter_end )
		   	{ 
				display_partial_solution(); 
				display_location( &_loc );
				return; 
		   	}
		}
		++liter;
		if ( liter == liter_end )
		   { 
			display_partial_solution(); 
			display_location( &_loc );
			return; 
		   }
        }

        // while both are on the same line
        while ( (*liter).first == (*riter).first )
	{
                if ( (*liter).second+1 == ((*riter).second) )
                {
                        _loc.push_back( *liter );
                        _loc.push_back( *riter );
                        ++riter;
                        ++liter;
                }
                else
                if ( (*liter).second <= (*riter).second )
                        ++liter;
                else ++riter;

                if ( liter == liter_end || riter == riter_end )
		   { 
			display_partial_solution(); 
			display_location( &_loc );
			return; 
		   }
        }
    }
}

void
OrQuery::
eval()
{
    // add an exception here
    if ( ! _lop || ! _rop )
    {
	 cerr << "Internal error: OrQuery: \n"
	      << "no "
	      << ( _lop ? "right " : "left " )
	      << "operand -- bailing out... \n";
	 return;
    }

    _lop->eval();
    _rop->eval();

    vector< location, allocator >::const_iterator 
        riter = _rop->locations()->begin(),
        liter = _lop->locations()->begin(),
        riter_end = _rop->locations()->end(),
        liter_end = _lop->locations()->end();

    merge( liter, liter_end, riter, riter_end,
	     inserter( _loc, _loc.begin() ),
	     less_than_pair() );

    display_partial_solution(); 

    display_location( &_loc );

}

void
NotQuery::
eval()
{
    // add an exception here
    if ( ! _op )
    {
         cerr << "Internal error: NotQuery: \n"
              << "no operand -- bailing out... \n";
         return;
    }
 
    _op->eval();

    vector< location, allocator >::const_iterator
            iter = _all_locs->begin(), 
            iter_end = _all_locs->end();

    set<short,less<short>,allocator> *ps = _vec2set( _op->locations() );
    for ( ; iter != iter_end; ++iter ) {
	  if ( ! ps->count( (*iter).first )) {
		 _loc.push_back( *iter );	
	  }
    }

    _solution = _vec2set( &_loc );
    display_partial_solution(); 

    display_location( &_loc );
}

void
NameQuery::
eval()
{
    display_partial_solution(); 

    display_location( &_loc );
}
	
void 
Query::
handle_tab( ostream &os, int tabcnt ) const
{
    while ( tabcnt-- )
	      os << '\t';
}

void 
Query::
display_solution( ostream &os, int tabcnt ) 
{
    for ( int tcnt = tabcnt; tcnt; --tcnt )
          os << '\t'; 

    const set< short, less<short>, allocator > *pset = solution();
    os << "( " << pset->size() << " ) : ";

    set< short, less<short>, allocator >::iterator iter = pset->begin();
    for ( int elem_cnt = 1; iter != pset->end(); 
                            ++iter, ++elem_cnt )
    {
          if ( !( elem_cnt % 10 )) {
               os << endl;      
               elem_cnt = 1;    
               for ( int tcnt = tabcnt; tcnt; --tcnt )
                     os << '\t'; 
          }     
        
          os << *iter+1 << ' ';
    }

    os << endl;
}

Query*
NotQuery::
clone() const
{
        return new NotQuery( *this );
}

Query*
AndQuery::
clone() const
{
        return new AndQuery( *this );
}

Query*
OrQuery::
clone() const
{
        return new OrQuery( *this );
}

void
Query::
print_lparen( short cnt, ostream &os ) const
{
    while ( cnt-- != 0 ) 
            os << "(";

    os << ' ';
}

void
Query::
print_rparen( short cnt, ostream &os ) const
{
    os << ' ';
    while ( cnt-- != 0 ) 
            os << ")";
}
