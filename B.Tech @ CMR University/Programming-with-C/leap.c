/*Leap Year or Not*/
#include<stdio.h>
int main()
{ int a;
  printf("\t\tENTER A Year : ");
  scanf("%d",&a);
//To Check if its a century year 
  if(a%100==0)
   { //To Check if the year is leap year or not
     if(a%400==0)
      printf("\t\tIts a leap year.\n");
     else
      printf("\t\tIts not a leap year.\n");
   }
//For non-century years
  else if(a%4==0)                                       
   printf("\t\tIts a leap year.\n");
  else
   printf("\t\tIts not a leap year.\n");
  return 0;
}
