#include<stdio.h>
int main()
{
	int serv;
	char gen,Q;
	printf("\tENTER GENDER, YEAR OF SERVICE, QUALIFICATION(P/U): ");
	scanf("%c %d %c",&gen,&serv,&Q);
	printf("Gender: %c \n Sevice: %d \n Q: %c",gen,serv,Q);
	if(serv>=15)
	{	
		if(Q=='P')
		{
			if(gen=='M')
				printf("\tSalary: 50000\n");
			else if(gen=='F')
				printf("\tSalary: 40000\n");
		}
		else if(Q=='U')
		{
			if(gen=='M')
				printf("\tSalary: 30000\n");
			else if(gen=='F')
				printf("\tSalary: 35000\n");
		}
	}
	else if(serv<10)
	{	if(Q=='P')
		{
			if(gen=='M')
					printf("\tSalary: 20000\n");
			else if(gen=='F')
					printf("\tSalary: 25000\n");
		}
		else if(Q=='U')
		{
			if(gen=='M')
				printf("\tSalary: 10000\n");
			else if(gen=='F')
				printf("\tSalary: 15000\n");
		}
	}
	return 0;
}