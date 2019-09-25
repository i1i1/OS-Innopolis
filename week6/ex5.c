#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>


pid_t
child()
{
	pid_t p = fork();

	if (p == -1)
		perror("Fork error");
	else if (p != 0)
		return p;

	for (;;) {
		printf("I'm alive!\n");
		fflush(stdout);
		sleep(1);
	}
}

int
main(int argc, char **argv)
{
	pid_t chld = child();
	sleep(10);
	kill(chld, SIGKILL);
	return 0;
}
