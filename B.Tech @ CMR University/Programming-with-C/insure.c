#include<stdio.h>
int main()
{
	int age; 
	char gen,stat;
	printf("\tMARITAL STATUS(Y/N) ,AGE & GENDER(M/F): ");
	scanf("%c %d %c",&stat,&age,&gen);
	if(stat=='Y')
		printf("\tELIGIBLE FOR INSURANCE\n");
	else if(gen=='M' && age>=30 )
		printf("\tELIGIBLE FOR INSURANCE\n");
	else if(gen=='F' && age>=25)
		printf("\tELIGIBLE FOR INSURANCE\n");
	else
		printf("\tYOU ARE INELIGIBLE FOR INSURANCE\n");
	return 0;
}
