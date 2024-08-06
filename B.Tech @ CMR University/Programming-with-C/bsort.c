#include<stdio.h>
int main()
{
	int size,tmp=0;
	printf("\n Enter Array Size : ");
	scanf("%d",&size);
	int A[size];
	printf("\nEnter Array Elements:\n");
	for(int i=0;i<size;i++)
		scanf("%d",&A[i]);
	printf("\n Array is...\n");
	for(int i=0;i<size;i++)
		printf("  %d  ",A[i]);
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<(size-i-1);j++)
		{
			if(A[j]>A[j+1])
			{
				tmp=A[j];
				A[j]=A[j+1];
				A[j+1]=tmp;
			}
		}
	}
	printf("\nSORTED ARRAY IS.....\n");
	for(int i=0;i<size;i++)
	{		
		printf("%d",A[i]);
		if(i<size-1)
			printf("  <  ");
	}
	printf("\n");
	return 0;
}
			
