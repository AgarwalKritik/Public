#include<stdio.h>
int main()
{
	int n;
	printf("ENTER A DIGIT: ");
	scanf("%d",&n);
	for(int i=1;i<=10;i++)
		printf("\n %d * %d = %d",n,i,n*i);
	printf("\n");
	return 0;
}

