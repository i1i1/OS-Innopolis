#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>


/*
 * For `nproc == 3`:
 * ```
 * ─ex2─┬─ex2─┬─ex2───ex2
 *      │     └─ex2
 *      ├─ex2───ex2
 *      └─ex2
 *
 * ```
 *
 * For `nproc == 5`:
 * ```
 * ─ex2─┬─ex2─┬─ex2─┬─ex2─┬─ex2───ex2
 *      │     │     │     └─ex2
 *      │     │     ├─ex2───ex2
 *      │     │     └─ex2
 *      │     ├─ex2─┬─ex2───ex2
 *      │     │     └─ex2
 *      │     ├─ex2───ex2
 *      │     └─ex2
 *      ├─ex2─┬─ex2─┬─ex2───ex2
 *      │     │     └─ex2
 *      │     ├─ex2───ex2
 *      │     └─ex2
 *      ├─ex2─┬─ex2───ex2
 *      │     └─ex2
 *      ├─ex2───ex2
 *      └─ex2
 * ```
 * 
 * So `fork()` will return `0` how many times it was already called in previous process.
 *
 * It means that such program as below will always have maximum depth of `nproc`
 * and number of processes will be equal to `2 ^ nproc`.
 */
int
main(void)
{
    int nproc = 5;

    for (int i = 0; i < nproc; i++) {
        fork();

    sleep(5);

    return 0;
}

