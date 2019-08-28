#include <stdio.h>
#include <string.h>

#define VECTOR_IMPLEMENTATION
#include "vector.h"


void
reverse(char **sp)
{
    char *s = *sp;
    int len = strlen(s);

    for (int i = 0; i < len/2; i++) {
        int c;

        c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }

    sp = &s;
}

int
main(void)
{
    char *s = NULL;
    int c;

    do {
        c = getchar();
        if (vector_push(&s, c)) {
            vector_free(&s);
            return 1;
        }
    } while (c != EOF);

    if (vector_push(&s, '\0')) {
        vector_free(&s);
        return 1;
    }

    reverse(&s);
    puts(s);
    vector_free(&s);

    return 0;
}

