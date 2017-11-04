#include<stdio.h>
#include<stdlib.h>
#include "mem_alloc.h"

void *AllocateMemory(int size)
{
    void *ptr = NULL;

    ptr = malloc(size);

    printf("AllocateMemory() ptr = 0x%x\n",ptr);
    return ptr;
}

void DeAllocateMemory(void *ptr)
{
    free(ptr);
    ptr = NULL;
}
