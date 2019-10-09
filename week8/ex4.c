#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/resource.h>


void
printrusage()
{
    struct rusage ret;

    if (getrusage(RUSAGE_SELF, &ret))
        return;

    printf("rusage: ");
    printf("utime - %ld %ld ", ret.ru_utime.tv_sec, ret.ru_utime.tv_usec);
    printf("stime - %ld %ld ", ret.ru_stime.tv_sec, ret.ru_stime.tv_usec);
    printf("maxrss - %ld ", ret.ru_maxrss);
    printf("minflt - %ld ", ret.ru_minflt);
    printf("majflt - %ld ", ret.ru_majflt);
    printf("nvcsw - %ld ", ret.ru_nvcsw);
    printf("nivcsw - %ld ", ret.ru_nivcsw);
    printf("\n");
}

int
main(void)
{
    for (int i = 0; i < 10; i++) {
        int sz = 10 * 1024 * 1024;
        void *m = malloc(sz);

        if (m)
            memset(m, 0, sz);
        printrusage();
        sleep(1);
    }
    return 0;
}

