#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int
main(void)
{
    for (int i = 0; i < 10; i++) {
        int sz = 10 * 1024 * 1024;
        void *m = malloc(sz);

        if (m)
            memset(m, 0, sz);
        sleep(1);
    }
    return 0;
}

