#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int n, *arr;

	scanf("%d", &n);
	arr = malloc(n * sizeof(int));
	if (!arr)
		perror("Malloc");
	for (int i = 0; i < n; i++)
		arr[i] = i;
	for (int i = 0; i < n; i++)
		printf("%d\n", arr[i]);
	free(arr);

	return 0;
}
