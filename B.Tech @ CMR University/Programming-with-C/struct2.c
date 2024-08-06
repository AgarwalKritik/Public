#include<stdio.h>
struct Book
{
	char name;
	int pno;
	float pr;
};
int main()
{
	
	struct Book b[5];
	printf("\n\t\tENTER THE VALUES:\n");
	for(int i=0;i<5;i++)
	{
		printf("\n\t\tFOR BOOK %d: ",i+1);
		scanf(" %c %d %f",&b[i].name,&b[i].pno,&b[i].pr);
	}	
	for(int i=0;i<5;i++)
	{
		printf("\n\t\tFOR BOOK %d: ",i+1);
		printf("\n\t\t%c    %d    %f\n",b[i].name,b[i].pno,b[i].pr);
	}	
	return 0;
}
