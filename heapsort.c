#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "simulation.h"

int lastleaf = 0;

void heapify(int node);

void swap(int i, int j) {
	int buff = get(i);
	put(i,get(j));
	put(j,buff);
}

void sort(size_t len) {
	int size = (int)len;
	lastleaf = size - 1;
	int j = 0;
	for (j = lastleaf/2; j >= 0; j--) {
		heapify(j);
	} 
	int i = 0;
	for (i = lastleaf; i>0; i--) {
		swap(0, i);
		lastleaf = lastleaf - 1;
		heapify(0);
	}
}

void heapify(int node) {
	int left = (node*2) + 1;
	int right = (node*2) + 2;
	int greater = node;
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

void printArray(int size) {
	int i = 0;
	for(i=0; i< size ; i++) {
		if(i > 0) {
			printf("\n");
		}
		printf("%i", get(i));
	}
	printf("\n");
}

void process() {
	int N, i;
	clock_t start, diff;
	double msec;

	//scanf("%d", &N);
	//printf("Sorting %1d keys\n", N);
    init (128, 1000);
    N = 10000;

	for(i=0; i<N; i++) put(i, lrand48 ());
	
	size_t size = N;
	
	start = clock();
	sort(N);
    diff = clock() - start;

	//printf("printing array: \n");
	//printArray(N);
	//printf("doneprinting\n");

    msec = diff * 1000 / CLOCKS_PER_SEC;
    // printf("T1 %f ms\n", msec);
    fflush(stdout);

    done();
}

