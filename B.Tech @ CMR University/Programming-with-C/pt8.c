
#include<stdio.h>

void main()
{
	int a, b, *p,*k;
	printf("\nEnter Two Numbers: \n");
	scanf("%d %d",&a,&b);
	p=&a;
	k=&b;
	printf("\nEntered Value--> a = %d && b = %d\n",*p,*k);
	printf("\nSum, ( a + b ) = %d\n",(*p + *k));
}
