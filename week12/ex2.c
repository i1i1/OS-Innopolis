#include <stdio.h>

int main(int argc, char **argv) {
    int c;
    int flag_a = 0;

    argc--;
    argv++;

    if (argc > 0 &&
        argv[0][0] == '-' &&
        argv[0][1] == 'a' &&
        argv[0][2] == '\0') {

        argc--;
        argv++;
        flag_a = 1;
    }

    FILE *fa[argc];

    for (int i = 0; i < argc; i++)
        fa[i] = fopen(argv[i], flag_a ? "a" : "w");

    while ((c = fgetc(stdin)) != EOF) {
        fputc(c, stdout);
        for (int i = 0; i < argc; i++)
            fputc(c, fa[i]);
    }

    for (int i = 0; i < argc; i++)
        fclose(fa[i]);

    return 0;
}
