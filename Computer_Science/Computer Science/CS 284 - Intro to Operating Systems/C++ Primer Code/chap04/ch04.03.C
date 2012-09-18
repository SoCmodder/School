// #include <iostream>
#include <iostream.h>

/*****
  The larger value of 10 and 20 is 20
  The value of 10 is even.
  The larger value of 10, 20 and 30 is 30
*****/

int main()
{
    int i = 10, j = 20, k = 30;

    cout << "The larger value of "
         << i << " and " << j << " is "
         << ( i > j ? i : j ) << endl;

    cout << "The value of " << i << " is"
         << ( i % 2  ? " odd." : " even." )
         << endl;

    /* the conditional operator can be nested,
     * but a deep nesting is difficult to read
     * in this example,
     * max is set to the largest of 3 variables
     */

    int max = ( (i > j)
        ? (( i > k) ? i : k)
        : ( j > k ) ? j : k);

    cout << "The larger value of "
         << i << ", " << j << " and " << k
         << " is " << max << endl;
}
