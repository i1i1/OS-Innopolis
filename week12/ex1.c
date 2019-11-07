#include <stdio.h>
#include <ctype.h>
int main(void) {
    FILE *fp = fopen("/dev/urandom", "r");
    FILE *out = fopen("ex1.txt", "w");
    for (int i = 0; i < 20; i++) {
        int c;
        while (!isprint(c = getc(fp)));
        putc(c, out);
    }
    fclose(fp);
    fclose(out);
    return 0;
}
