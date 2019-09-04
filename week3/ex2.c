#include <stdio.h>

void
bubble_sort(int *a, int n)
{
	int swapped;

	do {
		swapped = 0;

		for (int i = 1; i < n; i++) {
			if (a[i-1] > a[i]) {
				int tmp = a[i];
				a[i] = a[i-1];
				a[i-1] = tmp;
				swapped = 1;
			}
		}
	} while (swapped);
}

int
main(void)
{
	int arr[6] = { 3, 2, 1, 4, 10, -1 };

	bubble_sort(arr, 6);

	for (int i = 0; i < 6; i++)
		printf("arr[%d] = %d\n", i, arr[i]);

	return 0;
}
