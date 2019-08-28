#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void
half(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            putchar('*');
        putchar('\n');
    }
}

void
arrow(int n)
{
    half(n/2+1);

    for (int i = n/2-1; i >= 0; i--) {
        for (int j = 0; j <= i; j++)
            putchar('*');
        putchar('\n');
    }
}

void
square(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            putchar('*');
        putchar('\n');
    }
}

struct {
    char *s;
    void (*f)(int);
} figures[] = {
#define FIG(f) {#f, f},
    FIG(arrow)
    FIG(half)
    FIG(square)
    FIG(triangle)
#undef FIG
};

int
main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    for (int i = 0; i < (int)(sizeof(figures)/sizeof(figures[0])); i++) {
        if (strcmp(figures[i].s, argv[1]) == 0) {
            figures[i].f(atoi(argv[2]));
            return 0;
        }
    }

    return 1;
}

