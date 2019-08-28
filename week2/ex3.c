#include <stdio.h>
#include <stdlib.h>


void
triangle_row(int spaces, int stars)
{
    for (int i = 0; i < spaces; i++)
        putchar(' ');
    for (int i = 0; i < stars; i++)
        putchar('*');
    putchar('\n');
}

void
triangle(int n)
{
    for (int i = 1; i <= n; i++)
        triangle_row(n-i, i*2-1);
}

int
main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    triangle(atoi(argv[1]));

    return 0;
}

