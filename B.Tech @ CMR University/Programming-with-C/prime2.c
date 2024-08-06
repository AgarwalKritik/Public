#include<stdio.h>
int main()
{
	int n,f=1;
	printf("\n ENTER A NUMBER: ");
	scanf("%d",&n);
	for(int i=2;i<=n/2;i++)
	{
		if(n%i==0)
		{
			f=0;
			break;
		}
	}
	if(n==1)
		printf("\n1 is neither Prime nor Composite\n");
	else if(f==1)
		printf("\n %d is Prime Number\n",n);
	else
		printf("\n %d is Composite Number\n",n);
	return 0;
}
