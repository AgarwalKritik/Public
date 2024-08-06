/*CALCULATE LOSS/PROFIT OF A SELLER*/
#include<stdio.h>

int main()
{
	int sp,cp,pro,ls;
	printf("ENTER COST PRICE & SELLING PRICE: ");
	scanf("%d %d",&cp,&sp);
	if(cp>sp)
		printf("\tLOSS INCURRED: %d \n",cp-sp);
	else
		printf("PROFIT INCURRED: %d \n",sp-cp);
	return 0;
}