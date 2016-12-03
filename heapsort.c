#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "simulation.h"

int lastleaf = 0;

void heapify(unsigned int node);

void swap(unsigned int i, unsigned int j) {
	// int buff = arr[i];
	// arr[i] = arr[j];
	// arr[j] = buff;
	unsigned int buff = get(i);
	put(i,get(j));
	put(j,buff);
}

void sort(size_t len) {
	unsigned int size = (unsigned int)len;
	printf("size (in sort): %i\n", size);
	lastleaf = size - 1;
	unsigned int j = 0;
	for (j = lastleaf/2; j >= 0; j--) {
		heapify(j);
	} 
	unsigned int i = 0;
	for (i = lastleaf; i>0; i--) {
		swap(0, i);
		lastleaf = lastleaf - 1;
		heapify(0);
	}
}

void heapify(unsigned int node) {
	unsigned int left = (node*2) + 1;
	unsigned int right = (node*2) + 2;
	unsigned int greater = node;
	if(left<=lastleaf) {
		if(get(left)>get(greater)) {
			swap(left, node);
			heapify(left);
		}
	}
	if(right<=lastleaf) {
		if(get(right)>get(greater)) {
			swap(right, node);
			heapify(right);
		}
	}
}

// void printArray(int * arr, int size) {
// 	int i = 0;
// 	for(i=0; i< size ; i++) {
// 		if(i > 0) {
// 			printf("\n");
// 		}
// 		printf("%i", arr[i]);
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

    page_map * map = get_map();

	for(i=0; i<N; i++) put(i, lrand48 ());

	printf("done loop\n");

	start = clock();
	// size_t size = map->array_size;
	size_t size = N;

	printf("size: %i\n", (int)map->array_size);

	sort(size);

    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("T1 %f ms\n", msec);
    fflush(stdout);

    done();
}