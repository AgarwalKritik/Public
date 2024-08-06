//To find if the enetred number is positive,negative or zero.

#include<stdio.h>
void main()
{ int a;
  printf("\t\tENTER a Number : ");
  scanf("%d",&a);
  if(a!=0)
  {
    if(a<0)
	printf("\t\tENTERED VALUE IS NEGATIVE\n");
    else if(a>0)
	printf("\t\tENTERED VALUE IS POSTIVE\n");
  }
  else 
	printf("\t\tENTERED VALUE IS ZERO.\n");
  
}
