//to find sum of n numbers
#include<stdio.h>

int main()
{	
	int n,sum=0;
	printf("Enter Number: ");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		sum+=i;
	printf("\n SUM: %d \n",sum);
	return 0;
}
	
