#include <stdio.h>
#include <stdlib.h>

int lastleaf = 0;

void sort(int * numbers) {
	lastleaf = size(numbers) - 1;
	int j = 0;
	for (j = lastleaf/2; j >= 0; j--) {
		heapify(numbers,j);
	} 
	int i = 0
	for (i = lastleaf; i>0; i--) {
		swap(numbers, 0, i);
		lastleaf = lastleaf - 1;
		heapify(numbers, 0);
	}
}

void heapify(int * arr, int node) {
	int left = node * 2 + 1;
	int right = node * 2 + 2;
	int greater = node;
	if(left<=lastleaf) {
		if(arr[left]>arr[greater]) {
			swap(arr, left, node);
			heapify(arr,left);
		}
	}
	if(right<=lastleaf) {
		if(arr[right]>arr[greater]) {
			swap(arr, right, node);
			heapify(arr, right);
		}
	}
}

void swap(int * arr, int i, int j) {
	int buff = arr[i];
	arr[i] = arr[j];
	arr[j] = buff;
}

void printArray(int * arr) {
	int i = 0;
	for(i=0; i<size(array); i++) {
		if(i > 0) {
			printf(", ");
		}
		print("%i", arr[i]);
	}
	printf("\n");
}

int main() {
	int numbers[10];
	int i = 0;
	for(int i = 0; i<10; i++) {
		numbers[i] = rand() % 20;
		printf("%i ", numbers[i]);
	}
	printf("\n");

	sort(numbers);

	printArray(numbers);
}