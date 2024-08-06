//CALCULATE SI FOR 3 TIMES
#include <stdio.h>
 
int main() 
{
    int A[3],si=1;
    printf("Enter principal,rate,time in year: ");
    for(int i=0;i<3;i++)
    	scanf("%d",&A[i]);
    for(int i=0;i<3;i++)
	si*=A[i];
    si/=100;
    printf("\n %d \n",si);
    return 0;
}


