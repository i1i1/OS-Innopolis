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

void
print_realmemusage()
{
    FILE *fp = fopen("/proc/self/statm", "r");
    char buf[BUFSIZ];
    long size, resident, shared, text, _, data;

    if (!fp)
        return;

    fscanf(fp, "%ld %ld %ld %ld %ld %ld %ld", &size,
                                              &resident,
                                              &shared,
                                              &text,
                                              &_,
                                              &data,
                                              &_);

    printf("real_mem_usage: ");
    printf("size - %ld; resident - %ld; shared - %ld; text - %ld, data - %ld\n",
            size, resident, shared, text, data);
}

int
main(void)
{
    for (int i = 0; i < 10; i++) {
        int sz = 100 * 1024 * 1024;
        void *m = malloc(sz);

        if (m)
            memset(m, 0, sz);
        printrusage();
        print_realmemusage();
        sleep(1);
    }
    return 0;
}

