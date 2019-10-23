#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define VECTOR_IMPLEMENTATION
#include "../vector.h"

struct file {
	ino_t ino;
	char ** fns;
};

int
main(void)
{
	char *dname = "tmp/";
	DIR *dir;
	struct dirent *dent;
	struct file *files = NULL;

	if (!(dir = opendir(dname)))
		return 1;

	while (dent = readdir(dir)) {
		unsigned i;

		for (i = 0; i < vector_nmemb(files); i++) {
			if (files[i].ino == dent->d_ino)
				break;
		}

		if (i == vector_nmemb(files)) {
			struct file f = { dent->d_ino, NULL };
			vector_push(files, f);
		}

		vector_push(files[i].fns, strdup(dent->d_name));
	}
	closedir(dir);

	for (unsigned i = 0; i < vector_nmemb(files); i++) {
		if (vector_nmemb(files[i].fns) < 2)
			continue;
		printf("%p:", (void *)files[i].ino);
		for (unsigned j = 0; j < vector_nmemb(files[i].fns); j++)
			printf(" %s", files[i].fns[j]);
		printf("\n");
	}

	return 0;
}

