#include<stdio.h>
int main()
{
	int n,s,i;
	printf("\nEnter Array Size: ");
	scanf("%d",&n);
	int A[n];
	printf("\nEnter Array Elements: \n");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	printf("\nEnter Value To Search: ");
	scanf("%d",&s);
	for(i=0;i<n;i++)
	{
		if(A[i]==s)
		{
			printf("\nSearch Value Found.\n");
			break;
		}
	}
	if(i==n)
		printf("\nElement Not Found.\n");
	return 0;
}
		
	
