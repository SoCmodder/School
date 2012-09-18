// typically this is placed within a separate
// program text file, such as pow.c
// and precompiled into a library ...
// programs wishing to invoke it, 
// link in the library

int pow( int val, int exp )
{
    for ( int res = 1; exp > 0; --exp )
          res = res * val;
    return res;
}

// #include <iostream>
#include <iostream.h>

// necessary if the executable is not included
// within this program text file ...
extern int pow(int,int);

/*****
The Powers of 2
0: 1
1: 2
2: 4
3: 8
4: 16
5: 32
6: 64
7: 128
8: 256
9: 512
10: 1024
11: 2048
12: 4096
13: 8192
14: 16384
15: 32768
*****/

int main()
{
    int val = 2;
    int exp = 15;

    cout << "The Powers of 2\n";
    for ( int cnt=0; cnt <= exp; ++cnt )
          cout << cnt << ": "
               << pow( val, cnt ) << endl;

    return 0;
}
