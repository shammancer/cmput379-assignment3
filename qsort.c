#include <stdio.h>
#include <stdlib.h>

// void quicksort(int* array, int len);
void printArray(int * arr, int size);

void swap(int * arr, int i, int j) {
	int buff = arr[i];
	arr[i] = arr[j];
	arr[j] = buff;
}

void quicksort(int* array, int len) {
    if (len > 1) {
        int pivot_idx = len/2;
        printf("pivot: %i\n", array[pivot_idx]);
        pivot_idx = partition( array, len, pivot_idx );
        quicksort( array, pivot_idx );
        quicksort( array+pivot_idx+1, len-pivot_idx-1 );
    }  
}

int partition( int* array, int len, int pivot_idx ) {
	swap(array, len-1, pivot_idx);

	int L = 0;
	int R = len-2;

	while(L < R) {
		while(array[L] < array[len-1]) L++;

		while(array[R] > array[len-1]) R--;

		// printf("L: %i R: %i\n", L, R);
		if (L<R) swap(array,L,R);
		// printArray(array, len);
	}

	int i = 0;
	while (array[i] < array[len-1]) {
		i++;
	}
	swap(array, i, len-1);
	return i;
}

void printArray(int * arr, int size) {
	int i = 0;
	for(i=0; i< size ; i++) {
		if(i > 0) {
			printf("\n");
		}
		printf("%i", arr[i]);
	}
	printf("\n");
}

int main() {
	int numbers[20];
	int i = 0;
	for(i = 0; i<20; i++) {
		numbers[i] = rand() % 2000;
		printf("%i ", numbers[i]);
	}

	int pivot = rand() % 8;
	printf("\n");
	// printf("pivot: %i", numbers[pivot]);
	int arr_size = sizeof(numbers)/sizeof(int);

	printf("\n");

	quicksort(numbers, arr_size);
	// partition(numbers, arr_size, 8);

	printArray(numbers, arr_size);
}