#include<stdio.h>
int main()
{
	int size,j,c=0,tmp=0;
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
		tmp=A[i];
		for(j=i-1;j>=0;j--)
		{
			if(A[j]>tmp)
			{
				A[j+1]=A[j];
				c=1;
			}
			else
				break;
		}
		if(c)
			A[j+1]=tmp;
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
			
