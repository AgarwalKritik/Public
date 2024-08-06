#include<stdio.h>
int main()
{
	int n,a,b,s=0;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	a=n;
	while(a!=0)
	{
		b=a%10;
		s+=b*b*b;
		a=a/10;
	}
	(s==n)?printf("\nARMSTRONG NUMBER\n"):printf("\nNOT A ARMSTRONG NUMBER\n");
	return 0;
}
		
