// #include <iostream>
#include <iostream.h>

/**
 ** The address of pstr is: vermeer
 **
 **/

const char *str = "vermeer";
int main()
{
    // oops: does not treat char* as an address

    const char *pstr = str;

    cout << "The address of pstr is: "
         << pstr << endl;
}
