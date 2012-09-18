// #include <iostream>
#include <iostream.h>

/**
 **
 **   note: actual address values will vary
 **   i:   1024       &i:     0x7ffeb59c
 **   *pi: 1024       pi:     0x7ffeb59c
 **                  &pi:     0x7ffeb598
 **/

int main()
{
    int i = 1024;
    int *pi = &i;

    cout << "i:   " << i
         << "\t&i:\t" << &i << '\n';

    cout << "*pi: "      << *pi
         << "\tpi:\t"    << pi  << endl
         << "\t\t&pi:\t" << &pi << endl;
}
