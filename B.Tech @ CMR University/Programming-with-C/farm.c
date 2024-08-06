#include<stdio.h>

int Arm(int x)
{
	int c=x,y,s=0;
	while(c!=0)
	{
		y=c%10;
		s+=y*y*y;
		c/=10;
	}		
	return s;
}

void main()
{ 
	int a,o;
  	printf(" ENTER A NUMBER : ");
  	scanf("%d",&a);
	o=Arm(a);
	(o==a)?printf("Armstrong Number\n"):printf("Not Armstrong Number\n");
}
