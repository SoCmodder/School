#ifndef USER_QUERY_H
#define USER_QUERY_H

#include <string>
#include <vector>
#include <map>
#include <stack>

typedef pair<short,short>           location;
typedef vector<location,allocator>  loc;

#include "Query.h"

class UserQuery {
public:
	UserQuery( vector< string,allocator > *pquery = 0 )
		:  _query( pquery ), _eval( 0 ), _paren( 0 ) {}

	Query *eval();
	void   query( vector< string,allocator > *pq ); 
	void   displayQuery();	

	static void word_map( map<string,loc*,less<string>,allocator> *pwm ) {
		if ( !_word_map ) _word_map = pwm;
	}

private:
	enum QueryType {
		WORD = 1, AND, OR, NOT, RPAREN, LPAREN 
	};

	Query    *eval_query();
	QueryType evalQueryString( const string &query );
	void      evalWord( const string &query );
	void 	  evalAnd();
	void 	  evalOr();
	void 	  evalNot();
	void 	  evalRParen();
	bool 	  integrity_check();
	
	int	                       _paren;
	Query	                      *_eval;
	vector<string,allocator>                *_query;
	stack<Query*, vector<Query*,allocator>, allocator > _query_stack;
	stack<Query*, vector<Query*,allocator>, allocator > _current_op;

        static short _rparenOn;
        static short _lparenOn;
        static map<string,loc*,less<string>,allocator> *_word_map;

};

inline Query*
UserQuery::
eval()
{
	if ( ! _query )
	 	cerr << "Oops! No query string present to evaluate!\n";

	return  !_query 
		?  0
		: ( _eval ? _eval : eval_query() );
}
		
inline void
UserQuery::
evalAnd()
{
cout << "evalAnd() : pop _query_stack, add operand, and push on _current_op\n";

	Query *pop = _query_stack.top(); _query_stack.pop();
	AndQuery *paq = new AndQuery( pop );

	if ( _lparenOn ) { paq->lparen( _lparenOn ); _lparenOn = 0; }
	if ( _rparenOn ) { paq->rparen( _rparenOn ); _rparenOn = 0; }

	_current_op.push( paq );
}

inline void
UserQuery::
evalOr()
{
cout << "evalOr() : pop _query_stack, add operand, and push on _current_op\n";

	Query *pop = _query_stack.top(); _query_stack.pop();
	OrQuery *paq = new OrQuery( pop );

	if ( _lparenOn ) { paq->lparen( _lparenOn ); _lparenOn = 0; }
	if ( _rparenOn ) { paq->rparen( _rparenOn ); _rparenOn = 0; }

	_current_op.push( paq );
}

inline void
UserQuery::
evalNot()
{
cout << "evalNot() : pop push on _current_op\n";

	NotQuery *paq = new NotQuery;
	
	if ( _lparenOn ) { paq->lparen( _lparenOn ); _lparenOn = 0; }
	if ( _rparenOn ) { paq->rparen( _rparenOn ); _rparenOn = 0; }

	_current_op.push( paq );
}

inline void
UserQuery::
evalRParen()
{
cout << "evalRParen() : _paren: " << _paren
	<< " _cuurent_op.size(): " 
	<< _current_op.size() << endl;

	if ( _paren < _current_op.size() )
	{
cout << "\tok: _paren less than _current_op: "
     << "pop _query_stack, get _current_op:\n"
     << "\tadd query to current_op, push on _query_stack"
     << endl;

		Query *poperand = _query_stack.top(); _query_stack.pop();
		Query *pop = _current_op.top(); _current_op.pop();
		pop->add_op( poperand );
		_query_stack.push( pop );
	}
}

inline void
UserQuery::
evalWord( const string &query )
{
cout << "evalWord() : " << query << endl;

	NameQuery *pq; 
	loc       *ploc;
	
	if ( ! _word_map->count( query )) 
		pq = new NameQuery( query );
	else {
	 	ploc = ( *_word_map )[ query ];
		pq = new NameQuery( query, *ploc );	
	}

	if ( _lparenOn ) { pq->lparen( _lparenOn ); _lparenOn = 0; }
	if ( _rparenOn ) { pq->rparen( _rparenOn ); _rparenOn = 0; }

	if ( _current_op.size() <= _paren ) 
	{
cout << "\tok: _current_op.size() : " << _current_op.size()
     << " is less than or equal _paren: " << _paren
     << "\n\tpushing word on _query stack\n";

		_query_stack.push( pq );
	}
	else {
cout << "\tok: _current_op.size() : " << _current_op.size()
     << " is greater than _paren: " << _paren
     << "\n\tpop _current_op, add word, then" 
     << " push op on _query stack\n";

		Query *pop = _current_op.top(); _current_op.pop();
		pop->add_op( pq );
		_query_stack.push( pop );
	}
}

inline void
UserQuery::
query( vector< string, allocator > *pq )
{
        if ( _eval )
           { delete _eval; _eval = 0; }

        _query = pq;
}

#endif
