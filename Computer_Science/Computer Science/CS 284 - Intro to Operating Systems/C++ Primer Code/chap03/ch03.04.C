// #include <iostream>
#include <iostream.h>

const char *st = "The expense of spirit\n";

/**
 ** 22: 
 **/

int main()
{
    int len = 0;

    // oops: this advances st until it addresses
    //       the terminating null of the string
    while ( *st++ ) ++len;

    cout << len << ": " << st << endl;

    return 0;
}
