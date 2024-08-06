/*EMI Calculator (C program to calculate EMI).*/
 
#include <stdio.h>
#include <math.h>
 
int main() 
{
    float pr, r, t, emi;
    printf("Enter principal,rate,time in year: ");
    scanf("%f %f %f",&pr,&r,&t);
    r=r/(12*100); /*one month interest*/
    t=t*12; /*one month period*/
    emi= (pr*r*pow(1+r,t))/(pow(1+r,t)-1);
    printf("Monthly EMI is= %f\n",emi);
    return 0;
}
