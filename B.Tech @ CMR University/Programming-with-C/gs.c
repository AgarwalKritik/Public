/*gross salary*/
#include<stdio.h>

int main()
{
float bs,ha,da,gs;
printf("Enter Basic Salary: ");
scanf("%f",&bs);
ha=(bs*20)/100;
da=(bs*40)/100;
gs=bs+ha+da;
printf("Gross Salary: %f \n",gs);
return 0;
}

