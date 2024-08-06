#include<stdio.h>

int sum(int x)
{
	if(x!=0)
		return x+sum(x-1);
	else
		return x;
}
	
int main()
{
	int n,r;
	printf("Enter a value: ");
	scanf("%d",&n);
	r=sum(n);
	printf("Sum = %d\n",r);
}

