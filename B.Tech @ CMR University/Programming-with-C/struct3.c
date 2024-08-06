//DATABASE OF 10 STUDENTS
#include<stdio.h>


int main()
{
	
	struct stud
{
	char name[25];
	char rno[10];
	char dept[10];
	char course[25];
	int year;
};
	struct stud b[5];
        void Display(struct stud);
	printf("\n\t\tENTER THE DETAILS: \n");
	for(int i=0;i<5;i++)
	{
		printf("\n\t\tFOR STUDENT %d: ",i+1);
		printf("\n\t\tNAME:");
		scanf("%s",b[i].name);
		printf("\n\t\tREG NO.:");
		scanf("%s",b[i].rno);
		printf("\n\t\tDEPT.:");
		scanf("%s",b[i].dept);
		printf("\n\t\tCOURSE:");
		scanf("%s",b[i].course);
		printf("\n\t\tYEAR OF JOINING:");
		scanf("%d",&b[i].year);
	}
	Display(b);
}
void Display(struct stud b)
{	
	for(int i=0;i<5;i++)
	{
		printf("\n\t\tFOR STUDENT %d: ",i+1);
		printf("\n\tNAME: %s | REG NO: %s | DEPT.: %s | COURSE: %s | YEAR OF JOINING: %d\n",b[i].name,b[i].rno,b[i].dept,b[i].course,b[i].year);
	}	
}
