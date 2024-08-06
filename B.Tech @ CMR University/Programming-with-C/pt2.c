#include<stdio.h>
void main()
{
	int a[5]={10,20,30,40,50},*p;
	p=a;
	for(int i=0;i<5;i++)
	{
		printf(" Address of a = %p\n",p);
		printf(" Value of a = %d\n",*p);
		p++;
	}
}
