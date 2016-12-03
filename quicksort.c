#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "simulation.h"

void q_sort(page** array, size_t size);
// void printArray(int * arr, int size);

void swap(unsigned int i, unsigned int j) {
	// int buff = arr[i];
	// arr[i] = arr[j];
	// arr[j] = buff;
	int buff = get(i);
	put(i,get(j));
	put(j,buff);
}

int pick_pivot(size_t len) {
	int size = (int)len;
	int random = rand() % size;
	return random;
}

void q_sort(page** array, size_t size) {
	int len = (int)size;
    if (len > 1) {
        int pivot_idx = pick_pivot(len);
        pivot_idx = partition(len, pivot_idx);
        q_sort( array, (size_t)pivot_idx);
        q_sort( array+pivot_idx+1, (size_t)len-pivot_idx-1);
    }  
}

int partition(page** array, size_t size, int pivot_idx ) {
	int len = (int)size;
	swap(len-1, pivot_idx);

	unsigned int L = 0;
	unsigned int R = len-2;

	while(L < R) {
		while(get(L) < get(len-1)) L++;

		while(get(R) > get(len-1)) R--;

		// printf("L: %i R: %i\n", L, R);
		if (L<R) swap(L,R);
		// printArray(array, len);
	}

	int i = 0;
	while (get(i) < get(len-1)) {
		i++;
	}
	swap(i, len-1);
	return i;
}

// void printArray(page** arr, int size) {
// 	int i = 0;
// 	for(i=0; i< size ; i++) {
// 		if(i > 0) {
// 			printf("\n");
// 		}
// 		printf("%i", get(i));
// 	}
// 	printf("\n");
// }

void process() {
	int N, i, j, k, t, min, f;
	clock_t start, diff;
	double msec;

	scanf("%d", &N);
	printf("Sorting %1d keys\n", N);
    init (128, 1000);

	for(i=0; i<N; i++) put(i, lrand48 ());

	printf("done loop\n");

	start = clock();
    page_map * map = get_map();
	size_t size = map->array_size;
	printf("size: %i", (int)map->array_size);

	q_sort(map->array, size);

    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("T1 %f ms\n", msec);
    fflush(stdout);

    done();
}