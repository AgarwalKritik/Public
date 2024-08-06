//Call by Reference
#include<stdio.h>

void Swap(int *x, int *y)
{
	int tmp;
	tmp=*x;
	*x=*y;
	*y=tmp;
}

void main()
{
	int a=50, b=100;
	printf("\n Before Swap --> a = %d && b = %d\n",a,b);
	Swap(&a,&b);
	printf("\n After Swap --> a = %d , b = %d\n",a,b);
}
