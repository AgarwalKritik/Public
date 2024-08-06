/*FIND GREATEST OF 2 NUMBERS*/
#include<stdio.h>
void main()
{ int a,b;
  printf("\t\tENTER TWO NUMBERS A,B : ");
  scanf("%d%d",&a,&b);
  if(a!=b)
  { if(a>b)
      printf("\t\tA is greater than B\n");
    else
      printf("\t\tB is greater than A\n");
  }
}
