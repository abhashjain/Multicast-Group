#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

//#define n 4
extern int PER_CLI;
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

int *mergeKArrays(int arr[][PER_CLI], int k)
{
    int *output = (int *)malloc(sizeof(int)*(PER_CLI*k));
    int i;
    int count;
    
    struct MinHeapNode harr[k];
    for (i = 0; i < k; i++)
    {
        harr[i].element = arr[i][0]; // Store the first element
        harr[i].i = i;  // index of array
        harr[i].j = 1;  // Index of next element to be stored from array
    }
    
    struct Heap *hp =  (struct Heap *)createBuildHeap(harr, k); 
 
    for (count = 0; count < PER_CLI*k; count++)
    {
        // Get the minimum element and store it in output
        struct MinHeapNode root = hp->harr[0];
        output[count] = root.element;
       
        if (root.j < PER_CLI)
        {
            root.element = arr[root.i][root.j];
            root.j += 1;
        }
        else root.element =  INT_MAX; 
        
        replaceMin(hp, root);
    }
 
    return output;
}

// A utility function to print array elements
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
       printf("%d ", arr[i]);
}
 
// Driver program to test above functions
/*int main()
{
    // Change n at the top to change number of elements
    // in an array
    int arr[][n] =  {{2, 6, 12, 34},
                     {1, 9, 20, 1000},
                     {23, 34, 90, 2000},
		     {4,7,9,1100}};
    int k = sizeof(arr)/sizeof(arr[0]);
 
    int *output = mergeKArrays(arr, k);
 
    printf("Merged array is ");
    printArray(output, n*k);
 
    return 0;
}*/

