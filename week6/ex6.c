#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define xprintf(args...) do { printf(args); fflush(stdout); } while (0)


void
xpipe(int p[2])
{
	if (pipe(p) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t
xfork()
{
	pid_t p;
	if ((p = fork()) == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return p;
}

void
sigstop()
{
	xprintf("Child2: sigstop\n");
	xprintf("Child2: exiting...\n");
	exit(EXIT_SUCCESS);
}

void
child1(int pipefd[2])
{
	pid_t cpid;

	xprintf("Child1: reading pid of the second child\n");
	close(pipefd[1]);
	read(pipefd[0], &cpid, sizeof(cpid));
	close(pipefd[0]);

	xprintf("Child1: sleeping\n");
	sleep(2);
	xprintf("Child1: Sending SIGSTOP to the second child\n");
	kill(cpid, SIGSTOP);

	xprintf("Child1: exiting...\n");
	exit(EXIT_SUCCESS);
}

void
child2()
{
	struct sigaction s;

	memset(&s, 0, sizeof(s));
	s.sa_handler = sigstop;

	xprintf("Child2: setting sigaction handler\n");
	sigaction(SIGSTOP, &s, NULL);

	for (;;) {
		xprintf("Child2: Still alive\n");
		sleep(1);
	}
}

int
main(void)
{
	int pipefd[2], wstatus;
	pid_t cpid;

	xpipe(pipefd);

	xprintf("Parent: Spawning first child\n");
	if (xfork() == 0)
		child1(pipefd);
	xprintf("Parent: Spawning second one\n");
	if ((cpid = xfork()) == 0)
		child2();

	xprintf("Parent: Sending pid of the second child to the first one\n");
	close(pipefd[0]);
	write(pipefd[1], &cpid, sizeof(cpid));
	close(pipefd[1]);

	xprintf("Parent: waiting for changes from the second child\n");
	waitpid(cpid, &wstatus, 0);
	xprintf("Parent: wstatus %d\n", wstatus);
	xprintf("Parent: exiting...\n");
	exit(EXIT_SUCCESS);
}

