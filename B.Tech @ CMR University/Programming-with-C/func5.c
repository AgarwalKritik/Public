#include<stdio.h>

int sum();
int avg();

void main()
{
	int a,b,c,d,e,x,y;
	printf("ENTER 5 INTEGER VALUES:\n");
	scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
	x=sum(a,b,c,d,e);
	y=avg(x);
	printf("Sum = %d\n",x);
	printf("Average = %d\n",y);
}

int sum(int p,int q,int r,int s,int t)
{
	int sum=0;
	sum=p+q+r+s+t;
	return (sum);
}
int avg(int k)
{
	int avg=0;
	avg=k/5;
	return (avg);
}
