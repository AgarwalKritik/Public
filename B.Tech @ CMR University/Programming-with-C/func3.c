#include<stdio.h>

int sum(int,int);

int main()
{
	int a,b,c;
	printf("ENTER VALUE OF A & B: \n");
	scanf("%d %d",&a,&b);
	c=sum(a,b);
	printf("Sum = %d\n",c);
}

int sum(int x,int y)
{
	int s;
	s=x+y;
	return s;
}

