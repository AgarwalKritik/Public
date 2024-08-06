#include<stdio.h>
int main()
{
	int r1,r2,c1,c2;
	printf(" Enter Number of Rows & Columns of Matrix A: ");
	scanf("%d %d",&r1,&c1);
	printf("\n Enter Number of Rows & Columns of Matrix B: ");
	scanf("%d %d",&r2,&c2);
	int A[r1][c1],B[r2][c2],C[r1][c2];
	if( r1 == c2 )
	{
		printf("\n Enter Values of Matrix A \n");
		for(int i=0;i<r1;i++)
		{
			for(int j=0;j<c1;j++)
				scanf("%d",&A[i][j]);
		}
		printf("\n Enter Values of Matrix B \n");
		for(int i=0;i<r2;i++)
		{
			for(int j=0;j<c2;j++)
				scanf("%d",&B[i][j]);
		}
		for(int i=0;i<r1;i++)
		{
			for(int j=0;j<c2;j++)
			{
				C[i][j]=0;
				for(int k=0;k<c1;k++)
					C[i][j] += A[i][k] * B[k][j];
			}
		}
		printf("\n Multiplied Resultant Matrix is : \n");
		for(int i=0;i<r1;i++)
		{
			for(int j=0;j<c2;j++)
				printf("\t%d\t",C[i][j]);
			printf("\n");
		}
	}
	else
		printf("\n Numbers of Rows of Matrix A must be equal to number of Columns of Matrix B\n Matrix Cannot Be Multiplied. \n"); 
	return 0;
}

	
