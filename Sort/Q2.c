#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int merge_sort(int list[], int left, int right, int* cntPtr)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		(*cntPtr)++;
		merge_sort(list, left, mid, cntPtr);
		merge_sort(list, mid + 1, right, cntPtr);
		merge(list, left, mid, right, cntPtr);
	}

}

int merge(int list[], int left, int mid, int right, int* cntPtr)
{
	int i, j, k, l;
	int sorted_list[100];

	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right)
	{
		if (list[i] >= list[j])
		{
			sorted_list[k++] = list[j++];
			(*cntPtr)++;
		}
		else
		{
			sorted_list[k++] = list[i++];
			(*cntPtr)++;
		}
	}

	if (i > mid)
	// Add remained right list to sorted_list
	{
		for (l = j; l <= right; l++)
		{
			sorted_list[k++] = list[l];
			(*cntPtr)++;
		}
	}
	else
	// Add remained left list to sorted_list
	{
		for (l = i; i <= mid; i++)
		{
			sorted_list[k++] = list[i];
			(*cntPtr)++;
		}
	}

	// Change list to sorted_list
	for (l = left; l <= right; l++)
	{
		list[l] = sorted_list[l];
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
	/*for (int i = 0; i < size; i++)
	{
		A[i] = rand() % 1000;
		printf("%d ", A[i]);
	}*/

	// #2. Already sorted list (best-case)
	/*for (int i = 0; i < size; i++)
	{
		A[i] = i;
		printf("%d ", A[i]);
	}*/

	// #3. Reversely sorted list (worst-case)
	for (int i = 0; i < size; i++)
	{
		A[i] = size - i;
		printf("%d ", A[i]);
	}

	// Selection sort
	merge_sort(A, 0, size - 1, &cnt);

	printf("\n\nafter sorting\n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", A[i]);
	}

	printf("\n\nnumber of count: %d", cnt);
}