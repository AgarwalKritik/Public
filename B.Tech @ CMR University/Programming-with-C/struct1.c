#include<stdio.h>

int main()
{
	struct Book
{
	char name;
	int pno;
	float pr;
};
	struct Book b1,b2,b3;
	printf("\n\t\tENTER THE VALUES:\n");
	printf("\n\t\tFOR BOOK 1: ");
	scanf(" %c %d %f",&b1.name,&b1.pno,&b1.pr);
	printf("\n\t\tFOR BOOK 2: ");
	scanf(" %c %d %f",&b2.name,&b2.pno,&b2.pr);
	printf("\n\t\tFOR BOOK 3: ");
	scanf(" %c %d %f",&b3.name,&b3.pno,&b3.pr);
	printf("\n\n\t\tTHE VALUES ARE: \n");
	printf("\n\t\t\t\tName\tPage No.\tPrice\n");
	printf("\n\t\tFOR BOOK 1: ");
	printf("\t%c %d %f",b1.name,b1.pno,b1.pr);
	printf("\n\t\tFOR BOOK 2: ");
	printf("\t%c %d %f",b2.name,b2.pno,b2.pr);
	printf("\n\t\tFOR BOOK 3: ");
	printf("\t%c %d %f\n",b3.name,b3.pno,b3.pr);
	return 0;
}
