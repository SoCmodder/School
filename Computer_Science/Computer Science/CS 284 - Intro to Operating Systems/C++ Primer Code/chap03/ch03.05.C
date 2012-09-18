// #include <iostream>
#include <iostream.h>

const char *st = "The expense of spirit\n";

/**
 ** 22: The expense of spirit
 **/

int main()
{
    int len = 0;

    // don't shift the actual string pointer
    const char *ps = st;

    // count length of string, excluding terminating null
    // the newline (\n), counts as 1 character
    while ( *ps++ ) ++len;

    // ok: display our results
    cout << len << ": " << st << endl;

    return 0;
}
