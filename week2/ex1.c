#include <stdio.h>
#include <limits.h>
#include <float.h>


int
main(void)
{
    int a;
    float b;
    double c;

    printf("sizeof(a) = %lu\n", sizeof(a));
    printf("sizeof(b) = %lu\n", sizeof(b));
    printf("sizeof(c) = %lu\n", sizeof(c));

    a = INT_MAX;
    b = FLT_MAX;
    c = DBL_MAX;

    printf("INT_MAX = %d\n", a);
    printf("FLT_MAX = %f\n", b);
    printf("DBL_MAX = %lf\n", c);

    return 0;
}

