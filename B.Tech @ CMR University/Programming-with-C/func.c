#include<stdio.h>

void msg()
{
	printf(" Message\n");
}

void msg1()
{
	printf(" Message 1\n");
}

void main()
{
	msg1();
	printf(" Main\n");
	msg();
}
