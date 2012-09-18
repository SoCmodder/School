#include <iostream>

/**
 ** not executed: standard library with boolalpha not available
 **
 **/

int main()
{
    bool illustrate = true;

    cout << "bool object illustrate: "
         << illustrate << '\n'
         << "with boolalpha applied: "
         << boolalpha 
	 << illustrate << endl;
}

