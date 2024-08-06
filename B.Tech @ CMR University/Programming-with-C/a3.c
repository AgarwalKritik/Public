#include<stdio.h>
int main()
{
	int r,c;
	printf(" Enter Number of Rows & Columns: ");
	scanf("%d %d",&r,&c);
	int A[r][c];
	printf("\n Enter Values \n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
			scanf("%d",&A[i][j]);
	}
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			printf("  %d  ",A[i][j]);
			if(j<c-1)
				printf(" --> ");
		}
	printf("\n");
	}
	return 0;
}

