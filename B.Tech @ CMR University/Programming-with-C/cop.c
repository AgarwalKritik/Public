#include<stdio.h>
int main()
{
	float bs,ha,da,gs,x,y;
	printf("Enter Basic Salary: ");
	scanf("%f",&bs);
	x=(bs<15000?(ha=(bs*10)/100):(ha=bs+5000));
	y=(bs<15000?(da=(90*bs)/100):(da=(98*bs)/100));
	gs=bs+x+y;
	printf("Gross Salary: %f \n",gs);
	return 0;
}
