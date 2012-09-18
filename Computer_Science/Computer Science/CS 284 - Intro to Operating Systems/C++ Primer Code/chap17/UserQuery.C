#include "UserQuery.h"

map<string,loc*,less<string>,allocator> *UserQuery::_word_map = 0;
short UserQuery::_lparenOn = 0;
short UserQuery::_rparenOn = 0;

void 
UserQuery::
displayQuery()
{
	vector< string, allocator >::iterator 
		it = _query->begin(), end_it = _query->end();

	for ( ; it != end_it; ++it )
		cout << *it << " ";

	cout << endl;
}

bool
UserQuery::
integrity_check()
{
	if ( !_current_op.empty() ) {
		cerr << "Oops: internal error: current_op not empty!\n";
		return false;
	}
	
	if ( _query_stack.size() != 1 ) {
		cerr << "Oops: internal error: query_stack: " 
		     << _query_stack.size() 
		     << " -- expecting 1 element\n"; 
		return false;
	}

	return true;
}

Query*
UserQuery::
eval_query()
{
	vector<string,allocator>::iterator  
		it = _query->begin(), end_it = _query->end();

	for ( ; it != end_it; ++it )
	{
		switch( evalQueryString( *it ))
		{
		case WORD:
			evalWord( *it );
			break;
		case AND:
			evalAnd();
			break;
		case OR:
			evalOr();
			break;
		case NOT:
			evalNot();
			break;
		case LPAREN:
			++_paren;
			++_lparenOn;
			break;
		case RPAREN:
			--_paren;
			++_rparenOn;
			evalRParen();
			break;
		}
		cout << " lparenOn: " << _lparenOn << endl;
		cout << " rparenOn: " << _rparenOn << endl;
	}

	if ( integrity_check() ) {
		_eval = _query_stack.top(); _query_stack.pop();

		if ( _rparenOn ) 
		   { _eval->rparen( _rparenOn ); _rparenOn = 0; }

		return _eval;
	}
	else return _eval = 0;
}

UserQuery::QueryType
UserQuery::
evalQueryString( const string &query )
{
	if ( query == "&&" )
		return AND;

	if ( query == "||" )
		return OR;

	if ( query == "!" )
		return NOT;

	if ( query == "(" )
		return LPAREN;

	if ( query == ")" )
		return RPAREN;

	return WORD;
}
