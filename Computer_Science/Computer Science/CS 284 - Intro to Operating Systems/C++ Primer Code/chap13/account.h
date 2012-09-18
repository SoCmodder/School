#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

class Account {
public:
        Account( double amount, const string &owner );

        string owner();
	double dailyReturn();
        static void raiseInterest( double );
        static double interest();

	friend int compareRevenue( Account& , Account* );
private:
        static double  _interestRate;
        double         _amount;
        string         _owner;

	static const int nameSize = 16;
        static const char name[nameSize];
};


inline Account::Account( double amount, const string &owner ) :
  _amount( amount ),
  _owner( owner )
  { /* all the work is done with the member initialization list */ }


inline string Account::owner()
  { return _owner; }

inline double Account::dailyReturn()
  {
    return( _interestRate / 365 * _amount );
  }

inline void Account::raiseInterest( double incr )
  {
    _interestRate += incr;
  }

inline double Account::interest()
  { return _interestRate; }


#endif
