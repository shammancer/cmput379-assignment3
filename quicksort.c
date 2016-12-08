#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "simulation.h"

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

void printArray2(int size) {
	int i = 0;
	for(i=0; i< size ; i++) {
		if(i > 0) {
			printf("\n");
		}
		printf("%i", get(i));
	}
	printf("\n");
}

void swap(int i, int j) {
	int buff = get(i);
	put(i,get(j));
	put(j,buff);
}

void q_sort(int array, int len) {
    if (len > 1) {
        int pivot_idx = (array+len)/2;
        pivot_idx = partition(array, len, pivot_idx);
        q_sort( array, pivot_idx);
        q_sort( array+pivot_idx+1, len-pivot_idx-1);
    }  
}

void q_sort2(int begin, int end) {
	printf("begin: %i end: %i\n", begin, end);
	int pivot = inPlacePartitioning(begin, end);
	q_sort(begin, pivot-1);
	q_sort(pivot+1, end);
}

int partition( int array, int len) {
	int pivot_idx = len/2;
	swap(array + len-1, array + pivot_idx);

	int L = array;
	int R = array + len-2;

	while(L < R) {
		while(get(L) < get(array + len - 1)) L++;

		while(get(R) > get(array + len - 1)) R--;

		// printf("L: %i R: %i\n", L, R);
		if ((L<R) && (L<=array+len-2) && (R>=array)) swap(L, R);
		// printArray(array, len);
	}

	int i = 0;
	while (get(array + i) < get(array + len - 1)) {
		i++;
	}
	swap(array + i, array + len-1);
	return i;
}

int inPlacePartitioning(int begin, int end) {
	printf("partitioning\n");

	int pivotIndex = (begin+end)/2;
	int pivot = get(pivotIndex);
	while(begin <= end) {
		if( (get(begin) >= pivot) && (get(end) < pivot) ) {
			swap(begin, end);
		}
		
		if(get(begin) < pivot) begin++;
		if(get(end) >= pivot) end--;
		
	}
	return begin;
}

void process() {
	int N, i;
	clock_t start, diff;
	double msec;

	// scanf("%d", &N);
	// printf("Sorting %1d keys\n", N);
    init (128, 1000);

    // page_map * map = get_map();
    N = 10000;
	for(i=0; i<N; i++) put(i, lrand48 ());
    start = clock();
    // printArray(0, N);
	q_sort(0, N);
    // partition(0, N);
    diff = clock() - start;

    // printf("printing array: \n");
    // printArray(0,N);
    // printf("done printing\n");

    msec = diff * 1000 / CLOCKS_PER_SEC;
    // printf("T1 %f ms\n", msec);
    fflush(stdout);

    done();
}