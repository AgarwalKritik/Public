// PRIME NUMBERS

#include<stdio.h>

int main()
{	int a,prime;
	printf("ENTER A NUMBER: ");
	scanf("%d",&a);
	for(int i=1;i<=a;i++)
	{	
		if(a==2 || a==3)
		{
		printf("\nPrime\n");
		break;
		}
		else if(a%2!=0 && a%3!=0)
		{
		printf("\nPrime\n");
		break;
		}
		else
		{
		printf("\nNOT PRIME\n");
		break;
		}
	}
	return 0;
}

