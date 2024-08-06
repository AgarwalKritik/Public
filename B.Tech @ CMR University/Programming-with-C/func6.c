#include<stdio.h>

int OddEve();

void main()
{ 
	int a,o;
  	printf(" ENTER A NUMBER : ");
  	scanf("%d",&a);
  	o=OddEve(a);
	(o==1)?printf("Even\n"):printf("Odd\n");
}

int OddEve(int x)
{
	int c=0;
	if(x%2==0)
   		c=1;
  	else
  		c=0;
	return c;
}
