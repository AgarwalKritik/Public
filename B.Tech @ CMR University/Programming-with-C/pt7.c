//Call by Reference
#include<stdio.h>

int Add(int *x, int *y)
{	
	int max;
	max= *x + *y;
	return (max);
}

void main()
{
	int a, b, o;
	printf("\nEnter Two Numbers: \n");
	scanf("%d %d",&a,&b);
	printf("\nEntered Value--> a = %d && b = %d\n",a,b);
	o=Add(&a,&b);
	printf("\nSum, ( a + b ) = %d\n",o);
}
