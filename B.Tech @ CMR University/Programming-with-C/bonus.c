#include<stdio.h>
int main()
{
 int sal,ser,doj,yr;
 printf("\nEnter\n Salary: ");
 scanf("%d",&sal);
 printf(" Current Year: ");
 scanf("%d",&yr);
 printf(" Year of Joining: ");
 scanf("%d",&doj);
 ser=yr-doj;
 if(ser>3)
   printf("\t\t SALARY + BONUS: %d\n",sal+3000);
 else
   printf("\t\t SALARY: %d\n",sal);
 return 0;
}
