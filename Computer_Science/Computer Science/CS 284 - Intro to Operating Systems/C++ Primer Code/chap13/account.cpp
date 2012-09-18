#include "account.h"

double Account::_interestRate = 0.0589;

const int Account::nameSize;
const char Account::name[nameSize] = "Savings Account";

int compareRevenue( Account &ac1, Account *ac2 )
{
        double ret1, ret2;
        ret1 = ac1._interestRate * ac1._amount;
        ret2 = ac2->_interestRate * ac2->_amount;
        return ret1-ret2; 
}

