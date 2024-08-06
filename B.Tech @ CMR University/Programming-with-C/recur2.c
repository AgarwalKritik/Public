#include<stdio.h>

int fact(int x)
{
	if(x!=1)
		return x*fact(x-1);
	else
		return x;
}
	
int main()
{
	int n,r;
	printf("Enter a value: ");
	scanf("%d",&n);
	r=fact(n);
	printf("Factorial = %d\n",r);
}

