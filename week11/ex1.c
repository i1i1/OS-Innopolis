#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>


int
main(void)
{
	char str[] = "This is a nice day";
	
	char *fn = "ex1.txt";
	struct stat st;
	off_t sz;
	int fd = open(fn, O_RDWR);

	fstat(fd, &st);
	sz = st.st_size;

	void *addr = mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	memcpy(addr, str, sizeof(str));

	return 0;
}

