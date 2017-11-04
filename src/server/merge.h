#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

struct MinHeapNode
{
	int element; // The element to be stored
	int i; // index of the array from which the element is taken
	int j; // index of the next element to be picked from array
};

struct Heap
{
	struct MinHeapNode *harr; 
	int heapSize; 
};

void swap(struct MinHeapNode *x, struct MinHeapNode *y);

void minHeapify(struct Heap *hp, int k);

struct Heap *createBuildHeap(struct MinHeapNode *arr, int k);

void replaceMin(struct Heap *hp, struct MinHeapNode x);

int *mergeKArrays(int *arr[], int k,int num_elements);

// A utility function to print array elements
void printArray(int arr[], int size);
