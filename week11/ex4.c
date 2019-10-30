#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int
main(void)
{
	int fdin, fdout;
	char *src, *dst;
	struct stat statbuf;

	fdin  = open("ex1.txt", O_RDONLY);
	fdout = open("ex1.memcpy.txt", O_RDWR|O_CREAT|O_TRUNC);

	fstat(fdin, &statbuf);

	src = mmap(0, statbuf.st_size, PROT_READ,            MAP_SHARED, fdin,  0);
	dst = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, 0);

	memcpy (dst, src, statbuf.st_size);

	return 0;
}

