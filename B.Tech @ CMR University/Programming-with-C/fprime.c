#include<stdio.h>

int Prime(int x)
{
	int c=1;
	for(int i=2;i<=x/2;i++)
	{
		if(x%i==0)
		{
			c=0; 
			break;
		}
	}	
	return c;
}

void main()
{ 
	int a,o;
  	printf(" ENTER A NUMBER : ");
  	scanf("%d",&a);
	if(a==1)
		printf("It's neither prime nor composite.\n");
	else
  	{
		o=Prime(a);
		(o==1)?printf("Prime Number\n"):printf("Composite Number\n");
	}
}
