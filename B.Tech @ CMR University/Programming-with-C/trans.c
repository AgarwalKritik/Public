#include<stdio.h>
int main()
{
	int r,c;
	printf(" Enter Number of Rows & Columns : ");
	scanf("%d %d",&r,&c);
	int A[r][c],B[c][r];
	printf("\n Enter Values of the Matrix \n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
			scanf("%d",&A[i][j]);
	}
	printf("\n Given Matrix : \n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
			printf("\t%d\t",A[i][j]);
		printf("\n");
	}
	
	for(int i=0;i<c;i++)
	{
		for(int j=0;j<r;j++)
			B[i][j]=A[j][i];
	}
	printf("\nTranspose of given Matrix : \n");
	for(int i=0;i<c;i++)
	{
		for(int j=0;j<r;j++)
			printf("\t%d\t",B[i][j]);
		printf("\n");
	}
	return 0;
}

	
