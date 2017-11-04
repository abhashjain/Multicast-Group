#include<stdio.h>

struct n{
int i;
struct n *N;
};

struct n *arr[3];

struct n *new(int i)
{
	struct n *t;
	t = malloc(sizeof(struct n));
	t->i=i;
	t->N = NULL;
	return t;
}


void main()
{
struct n *R;
R = new(1);
R->N = new(2);
R->N->N = new(3);


arr[0]=R;
arr[1]=R->N;

arr[1]->i=144;

printf("%d  ",arr[0]->N->i);
}




