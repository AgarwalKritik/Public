#include<stdio.h>

int sum(int,int);

int main()
{
	int a,b;
	printf("ENTER VALUE OF A & B: \n");
	scanf("%d %d",&a,&b);
	sum(a,b);
}

int sum(int x,int y)
{
	printf("Sum = %d\n",x+y);
}

