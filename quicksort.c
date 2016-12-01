#include <stdio.h>
#include <stdlib.h>

// void qsort(int* array, int len);
void printArray(int * arr, int size);

void swap(int * arr, int i, int j) {
	int buff = arr[i];
	arr[i] = arr[j];
	arr[j] = buff;
}

// void qsort(int* array, int len) {
//     if (len > 1) {
//         int pivot_idx = pick_pivot(len);
//         pivot_idx = partition( array, len, pivot_idx );
//         qsort( array, pivot_idx );
//         qsort( array+pivot_idx+1, len-pivot_idx-1 );
//     }  
// }

int partition( int* array, int len, int pivot_idx ) {
	// 1. Put away the pivot by swapping it with the last element of 
	//    the array.
	// 2. Search from both ends to out-of-order elements in the subarray 
	//    array[0:len-2] by repeating:
	//    2.1 the low-scanner searches for first high element from 
	//        the beginning of the array but do not go beyond the 
	//        high-scanner's position
	//    2.2 the high-scanner searches for first low element from 
	//        the end of the array but do not go beyond the 
	//        low-scanner's position
	//    2.3 swap if found a pair of eligible elements, move scanners
	// 3. Put the pivot back to its final position, 
	//    return the final position.

	swap(array, len-1, pivot_idx);

	int L = 0;
	int R = len-2;
	
	while(L<R) {
		int i=L;
		while(i<len-1) {
			if(array[i]>array[len-1]) {
				L = i;
				printf("L: %i\n", L);
				break;
			}
			i++;
		}

		int j = R;
		while(j>0) {
			if(array[R]<array[len-1]) {
				// printf("trigger\n");
				R = j;
				// printf("R: %i\n", R);
				break;
			}
			j--;
		}
		// printf("L: %i R: %i\n", L, R);


		swap(array,L,R);
	}
}

void printArray(int * arr, int size) {
	int i = 0;
	for(i=0; i< size ; i++) {
		if(i > 0) {
			printf(", ");
		}
		printf("%i", arr[i]);
	}
	printf("\n");
}

int main() {
	int numbers[10];
	int i = 0;
	for(i = 0; i<10; i++) {
		numbers[i] = rand() % 20;
		printf("%i ", numbers[i]);
	}

	int pivot = rand() % 10;
	printf("\n");
	printf("pivot: %i", numbers[pivot]);
	int arr_size = sizeof(numbers)/sizeof(int);
	printf("\n");

	partition(numbers, arr_size, pivot);

	printArray(numbers, arr_size);
}