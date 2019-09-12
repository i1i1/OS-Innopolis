#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>


int
main(void)
{
    int n = fork();

    /*
     * Fork will always return 0 for a child process.
     */
    printf((n == 0) ?
           "Hello from parent [PID - %d]\n" :
           "Hello from child  [PID - %d]\n", getpid()
        );

    return 0;
}

