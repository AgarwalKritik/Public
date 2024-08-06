/*CHECK IF A TRIANGLE IS VALID OR NOT*/
#include<stdio.h>
int main()
{
	int a,b,c,sum;
	printf("ENTER THE 3 SIDES OF A TRIANGLE: ");
	scanf("%d %d %d",&a,&b,&c);
	sum=a+b+c;
	if(sum==180)
		printf("TRIANGLE IS VALID.\n");
	else
		printf("Invalid Sides Entered, Hence Triangle is Invalid.\n");
	return 0;
}