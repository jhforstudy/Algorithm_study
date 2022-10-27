#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int* list, int n, int* cntPtr)
{
	int min_idx, temp;
	for (int i = 0; i < n - 1; i++)
	{
		min_idx = i;
		(*cntPtr)++;
		for (int j = i + 1; j < n; j++)
		{
			(*cntPtr)++;
			if (list[j] < list[min_idx])
			{
				min_idx = j;
				(*cntPtr)++;
			}
		}
		// swap
		temp = list[i];
		(*cntPtr)++;
		list[i] = list[min_idx];
		(*cntPtr)++;
		list[min_idx] = temp;
		(*cntPtr)++;
	}

}

int main()
{
	int A[100];
	int size = sizeof(A) / sizeof(int);
	int cnt = 0;
	// Assign pointer to access count variable
	int* cntPtr = &cnt;
	srand(time(NULL));

	printf("before sorting\n");
	// #1. Input random integers to list
	for (int i = 0; i < size; i++)
	{
		A[i] = rand() % 1000;
		printf("%d ", A[i]);
	}

	// #2. Already sorted list (best-case)
	/*for (int i = 0; i < size; i++)
	{
		A[i] = i;
		printf("%d ", A[i]);
	}*/

	// #3. Reversely sorted list (worst-case)
	/*for (int i = 0; i < size; i++)
	{
		A[i] = size - i;
		printf("%d ", A[i]);
	}*/

	// Selection sort
	selection_sort(A, size, &cnt);

	printf("\n\nafter sorting\n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", A[i]);
	}

	printf("\n\nnumber of count: %d", cnt);
}