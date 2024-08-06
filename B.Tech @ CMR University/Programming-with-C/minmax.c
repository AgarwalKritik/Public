#include<stdio.h>
int main()
{
	int size,max=0,min=0;
	printf("\n Enter Array Size : ");
	scanf("%d",&size);
	int A[size];
	printf("\nEnter Array Elements:\n");
	for(int i=0;i<size;i++)
		scanf("%d",&A[i]);
	printf("\n Array is...\n");
	for(int i=0;i<size;i++)
		printf("  %d  ",A[i]);
	min=A[0];
	max=A[size-1];
	for(int i=0;i<size;i++)
	{
			if(A[i]<min)
				min=A[i];
			else if(A[i]>max)
				max=A[i];
			else
				continue;
	}
	printf("\nMAXIMUM = %d \nMINIMUM = %d \n",max,min);
	printf("\n");
	return 0;
}
			
