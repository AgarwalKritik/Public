/*FIND GREATEST OF 3 NUMBERS*/
#include<stdio.h>
int main()
{ int a,b,c;
  printf("\t\tENTER THREE NUMBERS A,B,C : \n");
  scanf("%d%d%d",&a,&b,&c);
  if(a>c)
  { if(a>b)
      printf("\t\tA is greater. \n");
    else
      printf("\t\tB is greater. \n");
  }
  else if(b>c)
      printf("\t\tB is greater. \n");
  else
      printf("\t\tC is greater. \n");
return 0;
}
