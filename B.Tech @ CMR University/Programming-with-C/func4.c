#include<stdio.h>

float prod(int,float);

void main()
{
	int a;
	float b,c;
	printf("ENTER VALUE OF INTEGER: ");
	scanf("%d",&a);
	printf("ENTER VALUE OF FLOAT: ");
	scanf("%f",&b);
	c=prod(a,b);
	printf("Product = %f\n",c);
}

float prod(int x,float y)
{
	float s;
	s=x*y;
	return s;
}

