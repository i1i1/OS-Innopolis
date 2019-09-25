#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void
sigint()
{
	printf("Cntrl+c was pressed\n");
	printf("Exiting...\n");
	exit(0);
}

int
main(int argc, char **argv)
{
	struct sigaction sint = {
		.sa_handler = sigint,
	};
	
	sigaction(SIGINT, &sint, NULL);

	for (;;);
}
