#ifndef ACCOUNT_H
#define ACCOUNT_H

// #include <new>
// #include <cstddef>
#include <new.h>
#include <stddef.h>

#include <utility>
#include <vector>
#include <string>

typedef pair<string,double> value_pair;
 
class Account {
public:
	Account() :  _balance( 0.0 ), _acct_nmbr( 0 ) {}

	Account( const char*, double=0.0 );
	Account( const string&, double=0.0 );
	Account( const Account &rhs );
	Account& operator=( const Account &rhs );

	string       name()    const { return _name; }
	double       balance() const { return _balance; }
        unsigned int account() const { return _acct_nmbr; }

 	static Account* init_heap_array(
     		vector<value_pair> &init_values,
     		vector<value_pair>::size_type elem_count = 0 );

 	static void dealloc_heap_array( Account*, size_t );

private:
	string       _name;
 	unsigned int _acct_nmbr;
 	double       _balance;

	unsigned int get_unique_acct_nmbr() const;
};

inline Account::
Account( const char* name, double opening_bal )
       : _name( name ), _balance( opening_bal )
{
        _acct_nmbr = get_unique_acct_nmbr();
}

inline Account::
Account( const string &name, double opening_bal )
       : _name( name ), _balance( opening_bal )
{
        _acct_nmbr = get_unique_acct_nmbr();
}

inline Account::
Account( const Account &rhs )
       : _name( rhs._name )
{
        _balance = rhs._balance;
        _acct_nmbr = get_unique_acct_nmbr();
}

inline Account& Account::
operator=( const Account &rhs )
{
        // guard against self-assignment
        if ( this != &rhs )
        {
                // invokes string::operator=(const string& )
                _name = rhs._name;
                _balance = rhs._balance;
        }

        return *this;
}

#endif
