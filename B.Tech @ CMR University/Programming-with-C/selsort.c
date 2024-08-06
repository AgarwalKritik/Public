#include<stdio.h>
int main()
{
	int size,min,tmp=0;
	printf("\n Enter Array Size : ");
	scanf("%d",&size);
	int A[size];
	printf("\nEnter Array Elements:\n");
	for(int i=0;i<size;i++)
		scanf("%d",&A[i]);
	printf("\n Array is...\n");
	for(int i=0;i<size;i++)
		printf("  %d  ",A[i]);
	for(int i=0;i<(size-1);i++)
	{
		min=i;
		for(int j=i+1;j<size;j++)
		{
			if(A[min]>A[j])
				min=j;
		}
		if(min!=i)
		{
			tmp=A[i];
			A[i]=A[min];
			A[min]=tmp;
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
			
