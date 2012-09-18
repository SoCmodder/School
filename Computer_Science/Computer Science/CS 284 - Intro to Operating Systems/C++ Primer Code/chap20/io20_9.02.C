#include <iostream>

/**
 ** not executed: standard library with boolalpha not available
 **
 **/

int main()
{
    bool illustrate = true;

    cout << "bool object illustrate set to true: "
         // changes state of cout to print bool values
         // using the strings true and false.
         << boolalpha
         << illustrate << endl;
}
