#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    for( i = 0; i < 5; i++ )
    {
        sleep(1);
        printf("TEST %d\n", i );
    }

    return 0;
}
