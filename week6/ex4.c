#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void
sigkill()
{
	printf("sigkill\n");
	exit(0);
}

void
sigstop()
{
	printf("sigstop\n");
	exit(0);
}

void
sigusr1()
{
	printf("sigusr1\n");
	exit(0);
}

int
main(int argc, char **argv)
{
	struct {
		int sign;
		struct sigaction sa;
	} signals[] = {
		{ .sign = SIGKILL, .sa = { .sa_handler = sigkill } },
		{ .sign = SIGSTOP, .sa = { .sa_handler = sigstop } },
		{ .sign = SIGUSR1, .sa = { .sa_handler = sigusr1 } },
	};

	for (int i = 0; i < sizeof(signals)/sizeof(signals[0]); i++) {
		sigaction(signals[i].sign, &signals[i].sa, NULL);
	}

	for (;;);
}
