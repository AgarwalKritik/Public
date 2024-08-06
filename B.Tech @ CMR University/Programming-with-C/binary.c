#include<stdio.h>
int main()
{
	int n,s,mid,low=0,high=0;
	printf("\nEnter Array Size: ");
	scanf("%d",&n);
	int A[n];
	printf("\nEnter Array Elements: \n");
	for(int i=0;i<n;i++)
		scanf("%d",&A[i]);
	high=n-1;
	mid=(low+high)/2;
	printf("\nEnter Value To Search: ");
	scanf("%d",&s);
	while(low<=high)
	{
		if(A[mid]==s)
		{
			printf("\nSearch Value Found.\n");
			break;
		}
		else if(A[mid]>s)
			low=mid+1;
		else if(A[mid]<s)
			high=mid-1;
		mid=(low+high)/2;
	}
	return 0;
}
		
	
