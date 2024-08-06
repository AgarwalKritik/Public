#include<stdio.h>
int main()
{
	int n,a=0,b=1,tmp=0;
	printf("Enter a term for the series: ");
	scanf("%d",&n);
	printf("\n");
	for(int i=1;i<=n;i++)
	{	printf(" %d \n",a);
		tmp=a+b;
		a=b;
		b=tmp;
	}
	return 0;
}

		
