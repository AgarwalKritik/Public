#include<stdio.h>
int main()
{
	double m=1,s=0;
	for(int i=1;i<=7;i++)
	{
		m*=i;
		printf("\n %d / %lf = %lf \n",i,m,i/m);
		s+=i/m;
	}
	printf("\n Sum of the series is %lf\n",s);
	return 0;
}

