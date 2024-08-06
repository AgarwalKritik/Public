#include<stdio.h>
void main()
{
	int a=10,*p;
	p=&a;
	printf(" Address of a = %p\n",p);
	printf(" Value of a = %d\n",*p);
	printf(" Address of a = %p\n",&a);
	printf(" Value of a = %d\n",a);
	printf(" Address of p = %p\n",&p);
	printf(" Value of p = %d\n",*(&a));
}
