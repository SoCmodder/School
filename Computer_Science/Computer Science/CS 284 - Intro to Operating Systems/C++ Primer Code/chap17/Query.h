#ifndef QUERY_H_
#define QUERY_H_

#include <vector>
#include <iostream.h>
#include <set>
#include <string>
#include <utility>

typedef pair< short, short > location;

class Query {
public:
	virtual ~Query(){ delete _solution; }

	virtual void eval() = 0;
	virtual Query *clone() const = 0;
	virtual ostream& print( ostream &os ) const = 0;
	virtual bool add_op( Query* ) { return true; }
	virtual void display_solution( ostream &os = cout, int tabcnt = 0 );
	
	Query& operator=( const Query& );
	void  handle_tab( ostream &os, int tabcnt ) const;
	const set< short,less<short>,allocator >    *solution();
	const vector< location, allocator > *locations() const { return &_loc; }

	void lparen( short lp ) { _lparen = lp; }
	void rparen( short rp ) { _rparen = rp; }

	short lparen() { return _lparen; }
	short rparen() { return _rparen; }

	void print_lparen( short cnt, ostream& os ) const;
	void print_rparen( short cnt, ostream& os ) const;

	void display_partial_solution();

protected:
	// copy constructor and copy assignment operator?
	Query() : _lparen( 0 ), _rparen( 0 ), _solution( 0 ) {}
	Query( const Query &rhs )
		: _loc( rhs._loc ), _solution( 0 ),
		  _lparen( rhs._lparen ), _rparen( rhs._rparen )
	{}

	Query( const vector<location, allocator> &loc )
		: _loc( loc ), _solution( 0 ), 
		  _lparen( 0 ), _rparen( 0 ) 
	{}

	set<short,less<short>,allocator>* 
		_vec2set( const vector<location,allocator>* );

	short                             _lparen;
	short                             _rparen;

	vector<location,allocator>        _loc; 
	set<short,less<short>,allocator> *_solution;
};

inline ostream&
operator<<( ostream &os, const Query &q ) { return q.print( os ); }

class NameQuery : public Query {
public:
	NameQuery( string name ) :  _name( name ) {}
	NameQuery( string name, const vector<location, allocator> &loc )
		 : Query( loc ), _name( name ) {}

	virtual void eval(); 
	virtual ostream& print( ostream &os ) const;
	virtual void display_solution( ostream &os = cout, int tabcnt = 0 );
	virtual Query *clone() const
		{ return new NameQuery( *this ); }
	
	string name() const { return _name; }
protected:
	string _name;
};

class NotQuery : public Query {
public:
	NotQuery( Query *op = 0 ) : _op( op ) {}
	NotQuery( const NotQuery& );
	~NotQuery() { delete _op; }

	virtual void eval(); 
	virtual ostream& print( ostream &os ) const;
	virtual bool add_op( Query* );
	virtual void display_solution( ostream &os = cout, int tabcnt = 0 );
	virtual Query *clone() const;
	
	NotQuery &operator=( const NotQuery& );
	const Query *op() const { return _op; }
	static void all_locs( const vector< location, allocator > *ploc ) 
		        { if ( !_all_locs ) _all_locs = ploc; }
protected:
	Query *_op;
	static const vector< location, allocator > *_all_locs;
};

class OrQuery : public Query {
public:
	OrQuery( Query *lop = 0, Query *rop = 0 ) 
		: _lop( lop ), _rop( rop ) {}

	OrQuery( const OrQuery& );
	~OrQuery() { delete _lop; delete _rop; }

	OrQuery& operator=( const OrQuery& );

	virtual void eval(); 
	virtual ostream& print( ostream &os ) const;
	virtual bool add_op( Query* );
	virtual void display_solution( ostream &os=cout, int tabcnt=0 );
	virtual Query* clone() const;
	
	const Query *rop() const { return _rop; }
	const Query *lop() const { return _lop; }

protected:
	Query *_lop;
	Query *_rop;
};

class AndQuery : public Query {
public:
	AndQuery( Query *lop = 0, Query *rop = 0 ) 
		: _lop( lop ), _rop( rop ) {}
	~AndQuery() { delete _lop; delete _rop; }

	AndQuery( const AndQuery& );
	AndQuery& operator=( const AndQuery& );

	virtual void eval(); 
	virtual ostream& print( ostream &os ) const;
	virtual bool add_op( Query* );
	virtual void display_solution( ostream &os=cout, int tabcnt=0 );
	virtual Query* clone() const;
	
	const Query *rop() const { return _rop; }
	const Query *lop() const { return _lop; }

	static void max_col( const vector< int, allocator > *pcol )
			{ if ( !_max_col ) _max_col = pcol; }

protected:
	Query *_lop;
	Query *_rop;
	static const vector< int, allocator > *_max_col;
};

class less_than_pair {
public:
	bool operator()( location loc1, location loc2 )
	{
		return (( loc1.first < loc2.first ) ||
			( loc1.first == loc2.first ) &&
			( loc1.second < loc2.second ));
	}
};

inline Query&
Query::
operator=( const Query &rhs )
{
        if ( &rhs != this )
        {
                _lparen = rhs._lparen;
                _rparen = rhs._rparen;
                _loc = rhs._loc;

                delete _solution;

                _solution = 0;
        }

        return *this;
};

inline 
const set< short, less<short>,allocator >*
Query::
solution() 
{
	if ( !_solution ) 
		_solution = _vec2set( &_loc );
	return _solution;
}

inline void 
Query::
display_partial_solution() 
{
	cout << "\t"  << *this
	     << " ( " << solution()->size() 
	     << " ) lines match" << endl;
}

inline NotQuery&
NotQuery:: 
operator=( const NotQuery &rhs )
{
	if ( &rhs != this )
	{
		this->Query::operator=( rhs );
		// delete _op;
		_op = rhs._op->clone();
	}

	return *this;
};

inline NotQuery::
NotQuery( const NotQuery &rhs )
	: Query( rhs )
{
	_op = rhs._op->clone();
};

inline AndQuery&
AndQuery::
operator=( const AndQuery &rhs )
{
        if ( &rhs != this )
        {
                this->Query::operator=( rhs );
                _lop = rhs._lop->clone();
                _rop = rhs._rop->clone();
        }

        return *this;
};

inline
AndQuery::
AndQuery( const AndQuery &rhs )
        : Query( rhs )
{
        _lop = rhs._lop->clone();
        _rop = rhs._rop->clone();
};

inline OrQuery&
OrQuery::
operator=( const OrQuery &rhs )
{
        if ( &rhs != this )
        {
                this->Query::operator=( rhs );
                _lop = rhs._lop->clone();
                _rop = rhs._rop->clone();
        }

        return *this;
};

inline OrQuery::
OrQuery( const OrQuery &rhs )
        : Query( rhs )
{
        _lop = rhs._lop->clone();
        _rop = rhs._rop->clone();
};

inline bool
AndQuery::
add_op( Query *op )
{
	bool status = false;
	if ( !_lop ) {
		_lop = op; status = true;
	}
	else
	if ( ! _rop ) {
		_rop = op; status = true; 
	}
	return status;
}

inline bool
OrQuery::
add_op( Query *op )
{
	bool status = false;
	if ( !_lop ) {
		_lop = op; status = true;
	}
	else
	if ( ! _rop ) {
		_rop = op; status = true; 
	}
	return status;
}

inline bool
NotQuery::
add_op( Query *op )
{
	bool status = false;
	if ( !_op ) {
		_op = op; status = true;
	}
	return status;
}

inline void
AndQuery::
display_solution( ostream &os, int tabcnt )
{
	handle_tab( os, tabcnt );
	os << "&& solution line set: ";
	Query::display_solution( os, 0 );
	_lop->display_solution( os, tabcnt+1 );
	_rop->display_solution( os, tabcnt+1 );
}

inline void
OrQuery::
display_solution( ostream &os, int tabcnt )
{
	handle_tab( os, tabcnt );
	os << "|| solution line set: ";
	Query::display_solution( os, 0 );
	_lop->display_solution( os, tabcnt+1 );
	_rop->display_solution( os, tabcnt+1 );
}

inline void
NotQuery::
display_solution( ostream &os, int tabcnt )
{
	handle_tab( os, tabcnt );
	os << "! solution line set: ";
	Query::display_solution( os, 0 );
	_op->display_solution( os, tabcnt+1 );
}

inline void
NameQuery::
display_solution( ostream &os, int tabcnt )
{
	handle_tab( os, tabcnt );
	os << _name << " solution line set: ";
	Query::display_solution( os, 0 );
}

inline ostream&
AndQuery::
print( ostream &os ) const
{
	if ( _lparen ) 
	     print_lparen( _lparen, os );

	_lop->print( os );
	os << " && ";
	_rop->print( os );

	if ( _rparen ) 
	     print_rparen( _rparen, os );

	return os;
}

inline ostream&
OrQuery::
print( ostream &os ) const
{
        if ( _lparen )
             print_lparen( _lparen, os );

	_lop->print( os );
	os << " || ";
	_rop->print( os );

        if ( _rparen )
             print_rparen( _rparen, os );

	return os;
}

inline ostream&
NotQuery::
print( ostream &os ) const
{
	os << " ! ";

        if ( _lparen )
             print_lparen( _lparen, os );

	_op->print( os );

        if ( _rparen )
             print_rparen( _rparen, os );

	return os;
}

inline ostream&
NameQuery::
print( ostream &os ) const
{
        if ( _lparen )
             print_lparen( _lparen, os );

	os << _name;

        if ( _rparen )
             print_rparen( _rparen, os );

	return os;
}

#endif
