//To find if the enetred number is positive,negative or zero.

#include<stdio.h>
void main()
{ int a;
  printf("\t\tENTER a Number : ");
  scanf("%d",&a);
  if(a<0)
   printf("\t\t -- Negative Number -- \n");
  else if(a>0)
   printf("\t\t ++ Positive Number ++ \n");
  else
   printf("\t\t !! ZERO !! \n");
}
