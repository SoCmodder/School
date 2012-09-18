// #include <iostream>
#include <iostream.h>

/**
 ** note: the actual address value will vary 
 ** The address of pstr is: 0x10012110
 **
 **/

const char *str = "vermeer";
int main()
{
    // ok: force treatment of pstr as an address

    const char *pstr = str;

    cout << "The address of pstr is: "
         << static_cast<void*>(const_cast<char*>(pstr)) << endl;
}
