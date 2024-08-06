// EVEN NUMBERS
/*
#include<stdio.h>

int main()
{	
	for(int n=1;n<=20;n++)
	{
		if(n%2==0)
			printf("\n %d \n",n);
	}
	return 0;
}


#include<stdio.h>
int main()
{	
	int n=1;
	while(n<=20)
	{
		if(n%2==0)
			printf("\n %d \n",n);
		n++;
	}
	return 0;
}
*/	
#include<stdio.h>
int main()
{	
	int n=1;
	do
	{
		if(n%2==0)
			printf("\n %d \n",n);
		n++;
	}while(n<=20);
	return 0;
}

