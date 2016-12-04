#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "simulation.h"

void q_sort(int array, size_t size);
// void printArray(int * arr, int size);

void printArray(int array, int size) {
    int i = 0;
    for(i=0; i< size ; i++) {
        if(i > 0) {
            printf("\n");
        }
        printf("%i", get(array + i));
    }
    printf("\n");
}

void swap(int i, int j) {
	int buff = get(i);
	put(i,get(j));
	put(j,buff);
}

int pick_pivot(size_t len) {
	int size = (int)len;
	int random = lrand48() % size;
    printf("pivot idx: %i\n", random);
	return random;
}

void q_sort(int array, size_t size) {
	int len = (int)size;
    if (len > 1) {
        int pivot_idx = pick_pivot(size);
        pivot_idx = partition(array, size, pivot_idx);
        q_sort( array, (size_t)pivot_idx);
        q_sort( array+pivot_idx+1, (size_t)len-pivot_idx-1);
    }  
}

int partition( int array, int len, int pivot_idx ) {
	swap(array + len-1, array + pivot_idx);

	int L = 0;
	int R = len-2;

	while(L < R) {
		while(get(array + L) < get(array + len - 1)) L++;

		while(get(array + R) > get(array + len - 1))R--;

		// printf("L: %i R: %i\n", L, R);
		if (L<R) swap(array + L, array + R);
		// printArray(array, len);
	}

	int i = 0;
	while (get(array + i) < get(array + len - 1)) {
		i++;
	}
	swap(array + i, array + len-1);
	return i;
}

void process() {
	int N, i, j, k, t, min, f;
	clock_t start, diff;
	double msec;

	scanf("%d", &N);
	printf("Sorting %1d keys\n", N);
    init (128, 1000);

    page_map * map = get_map();

	for(i=0; i<N; i++) put(i, lrand48 ());

	size_t size = N;

    start = clock();
    printArray(0, N);
	q_sort(0, size);
    // partition(map->array, size, 20);
    diff = clock() - start;

    printf("printing array: \n");
    printArray(0, N);
    printf("done printing\n");

    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("T1 %f ms\n", msec);
    fflush(stdout);

    done();
}