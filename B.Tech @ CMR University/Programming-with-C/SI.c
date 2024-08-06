//CALCULATE SI FOR 3 TIMES
#include <stdio.h>
 
int main() 
{
    float p, r, t, si;
    for(int i=0;i<3;i++)
    {
    	printf("Enter principal,rate,time in year: ");
    	scanf("%f %f %f",&p,&r,&t);
    	si = (p*r*t)/100;
	printf("\n SI: %f \n",si);
    }
    return 0;
}


