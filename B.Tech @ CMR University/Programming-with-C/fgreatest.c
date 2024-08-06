#include<stdio.h>

int Greatest(int x,int y)
{
	int c;
	(x>y)?(c=1):(c=0);
	return c;
}

void main()
{ 
	int a,b,o;
  	printf(" ENTER TWO NUMBERS : ");
  	scanf("%d %d",&a,&b);
  	o=Greatest(a,b);
	(o==1)?printf("%d is Greatest\n",a):printf("%d is Greatest\n",b);
}
