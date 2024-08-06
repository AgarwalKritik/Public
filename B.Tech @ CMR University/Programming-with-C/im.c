#include<stdio.h>
int main()
{
	double m=1,s=0;
	for(int i=1;i<=7;i++)
	{
		m*=i;
		printf(" %d / %lf = %lf \n",i,m,i/m);
		s+=i/m;
	}
	printf("\nSUM OF THE SERIES is %lf ",s);
}
		
