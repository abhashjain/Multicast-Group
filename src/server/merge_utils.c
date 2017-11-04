#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include "merge.h"
//#define n 4

void swap(struct MinHeapNode *x, struct MinHeapNode *y)
{
    struct MinHeapNode temp = *x;  
    *x = *y;  
    *y = temp;
}

void minHeapify(struct Heap *hp, int k)
{
    int left, right, smallest;
    smallest = k;
    left = 2*k + 1;
    right = 2*k + 2;
    
    if(left < hp->heapSize && 
        hp->harr[left].element < hp->harr[smallest].element)
    {
        smallest = left;
    }
    
    if(right < hp->heapSize && 
        hp->harr[right].element < hp->harr[smallest].element)
    {
        smallest = right;
    }
    
    if(smallest != k)
    {
        swap(&(hp->harr[k]),&(hp->harr[smallest]));
        minHeapify(hp, smallest);
    }
}

struct Heap *createBuildHeap(struct MinHeapNode *arr, int k)
{
    struct Heap *hp = (struct Heap *)malloc(sizeof(struct Heap));
    hp->heapSize = k;
    hp->harr = arr;
    
    int i;
    i = (hp->heapSize - 2)/2;
    
    while(i >= 0)
    {
        minHeapify(hp, i);
        i--;
    }
    
    return hp;
}

void replaceMin(struct Heap *hp, struct MinHeapNode x) 
{ 
    hp->harr[0] = x;  
    minHeapify(hp, 0); 
}

int *mergeKArrays(int *arr[], int k, int num_elements)
{
    int *output = (int *)malloc(sizeof(int)*(num_elements*k));
    int i,j;
    int count;

    for(i=0;i<k;i++){
	for(j=0;j<num_elements;j++){
		printf("%d ", arr[i][j]);
	}
	printf("\n");
    }
    struct MinHeapNode harr[k];
    for (i = 0; i < k; i++)
    {
        harr[i].element = arr[i][0]; // Store the first element
        harr[i].i = i;  // index of array
        harr[i].j = 1;  // Index of next element to be stored from array
    }
    
    struct Heap *hp =  (struct Heap *)createBuildHeap(harr, k); 
 
    for (count = 0; count < num_elements*k; count++)
    {
        // Get the minimum element and store it in output
        struct MinHeapNode root = hp->harr[0];
        output[count] = root.element;
       
        if (root.j < num_elements)
        {
            root.element = arr[root.i][root.j];
            root.j += 1;
        }
        else root.element =  INT_MAX; 
        
        replaceMin(hp, root);
    }
    printf("\n");
    return output;
}

// A utility function to print array elements
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
    {
       printf("%d ", arr[i]);
    }
    printf("\n");
}

