//ODD NUMBERS
/*
#include<stdio.h>

int main()
{	
	for(int n=1;n<=50;n++)
	{
		if(n%2!=0)
			printf("\n %d \n",n);
	}
	return 0;
}
*/
/*
#include<stdio.h>
int main()
{	
	int n=1;
	while(n<=50)
	{
		if(n%2!=0)
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
		if(n%2!=0)
			printf("\n %d \n",n);
		n++;
	}while(n<=50);
	return 0;
}

