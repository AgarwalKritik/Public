//Call by Reference
#include<stdio.h>

int Max(int *x, int *y)
{	
	int max;
	if(*x>*y)
		max = *x;
	else
		max = *y;	
	return (max);
}

void main()
{
	int a, b, o;
	printf("\nEnter Two Numbers: \n");
	scanf("%d %d",&a,&b);
	printf("\nEntered Value--> a = %d && b = %d\n",a,b);
	o=Max(&a,&b);
	printf("\nMaximum value is %d\n",o);
}
