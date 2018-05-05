#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>   
#include <math.h>

// Selection Sort
void selectionSort(int* a, int size)
{
	for (int i = 2; i < size; i++)
	{
		for (int j = i; j >= 1; j--)
		{
			if (a[j] < a[j - 1])
			{
				int temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
}

// Insertion Sort
void insertionSort(int* a, int size)
{
	for (int i = 1; i < size; i++)
	{
		int x = a[i];
		int j = i;
		while (j > 0 && a[j - 1] > a[j])
		{
			int temporaryVariable = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temporaryVariable;
			j--;
		}
		a[j] = x;
	}
}

// Merge Sort
int *b;
void merge(int* a, int first, int middle, int last)
{
	int j, i0, i1;
	i0 = first;
	i1 = middle;

	// While there are elements in the left or right runs

	for (j = first; j < last; j++) {
		// If left run head exists and is <= existing right run head.
		if (i0 < middle && (i1 >= last || a[i0] <= a[i1])) {
			b[j] = a[i0];
			i0++;
		}
		else {
			b[j] = a[i1];
			i1++;
		}
	}
}

void copyArray(int* a, int* b, int first, int last)
{
	for (int k = first; k < last; k++)
		a[k] = b[k];
}

void split(int* a, int first, int last)
{
	if (last - first < 2)
		return;
	//int middle = floor((first + last) / 2);
	int middle = ((first + last) / 2);
	//cout<<first<<" "<<middle<<" "<<last<<endl;
	split(a, first, middle);
	split(a, middle, last);
	merge(a, first, middle, last);
	copyArray(a, b, first, last);
}

void mergeSort(int *a, int size) {
	split(a, 0, size);
}

// Bubble Sort
void bubbleSort(int* a, int size) {
	int swapped = 1;
	int j = 0;
	int tmp;
	while (swapped) {
		swapped = 0;
		j++;
		for (int i = 0; i < size - j; i++) {
			if (a[i] > a[i + 1]) {
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
				swapped = 1;
			}
		}
	}
}

int* allocateArray(int size)
{
	int *a = (int*)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++)
	{
		a[i] = -1;
	}
	return a;
}

void populateRandomArray(int*a, int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % 50000;
	}
}

void populateSmallToLargeArray(int*a, int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i] = i;
	}
}

void populateLargeToSmallArray(int*a, int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i] = size - i - 1;
	}
}

void randomSwapArray(int*a, int size, int swap_size)
{
	int count = 0;
	while (count < swap_size)
	{
		int idx1 = rand() % size;
		int idx2 = rand() % size;
		int tmp = a[idx1];
		a[idx1] = a[idx2];
		a[idx2] = tmp;
		++count;
	}
}

int enablePrinting = 0;
void printArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (enablePrinting)
			printf("%d ", a[i]);
	}
	if (enablePrinting)
		printf("\n");
}

void sort(int* orig, int size, char* label, void(*func)(int*, int))
{
	int* a = allocateArray(size);
	b = allocateArray(size);

	copyArray(a, orig, 0, size);

	printArray(a, size);
	clock_t tStart = clock();
	func(a, size);
	printf("%s, size %d, time taken: %.2fs\n", label, size, (double)(clock() - tStart) / CLOCKS_PER_SEC);
	printArray(a, size);

	free(a);
	free(b);
}

int main()
{
	srand(0);
	int size = 10000;
	int* orig = allocateArray(size);
	populateRandomArray(orig, size);
	sort(orig, size, "Random input, Selection Sort", selectionSort);
	sort(orig, size, "Random input, Insertion Sort", insertionSort);
	sort(orig, size, "Random input, Merge Sort", mergeSort);
	sort(orig, size, "Random input, Bubble Sort", bubbleSort);

	populateSmallToLargeArray(orig, size);
	sort(orig, size, "Small to large input, Selection Sort", selectionSort);
	sort(orig, size, "Small to large input, Insertion Sort", insertionSort);
	sort(orig, size, "Small to large input, Merge Sort", mergeSort);
	sort(orig, size, "Small to large input, Bubble Sort", bubbleSort);

	randomSwapArray(orig, size, size / 100);
	sort(orig, size, "Small to large input, random swap, Selection Sort", selectionSort);
	sort(orig, size, "Small to large input, random swap, Insertion Sort", insertionSort);
	sort(orig, size, "Small to large input, random swap, Merge Sort", mergeSort);
	sort(orig, size, "Small to large input, random swap, Bubble Sort", bubbleSort);

	populateLargeToSmallArray(orig, size);
	sort(orig, size, "Large to small input, Selection Sort", selectionSort);
	sort(orig, size, "Large to small input, Insertion Sort", insertionSort);
	sort(orig, size, "Large to small input, Merge Sort", mergeSort);
	sort(orig, size, "Large to small input, Bubble Sort", bubbleSort);

	randomSwapArray(orig, size, size / 100);
	sort(orig, size, "Small to large input, random swap, Selection Sort", selectionSort);
	sort(orig, size, "Small to large input, random swap, Insertion Sort", insertionSort);
	sort(orig, size, "Small to large input, random swap, Merge Sort", mergeSort);
	sort(orig, size, "Small to large input, random swap, Bubble Sort", bubbleSort);

	return 0;
}
