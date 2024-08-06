#include<stdio.h>
int main()
{
	int r=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<=i;j++)
		{	r++;
			printf("  %d  ",r);
			
		}
		printf("\n");
	}
	return 0;
}
