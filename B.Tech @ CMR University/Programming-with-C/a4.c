#include<stdio.h>
int main()
{
	int r,c;
	printf(" Enter Number of Rows & Columns: ");
	scanf("%d %d",&r,&c);
	int A[r][c],B[r][c],s[r][c];
	printf("\n Enter Values of 1st Matrix \n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
			scanf("%d",&A[i][j]);
	}
	printf("\n Enter Values of 2nd Matrix \n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
			scanf("%d",&B[i][j]);
	}
	printf("\n SUM MATRIX is --> \n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			s[i][j]=A[i][j]+B[i][j];
			printf("  %d  ",s[i][j]);
			if(j<c-1)
				printf(" --> ");
		}
	printf("\n");
	}
	return 0;
}

