
#include<stdio.h>
void main()
{ int a,b;
  printf("ENTER TWO POINTS: ");
  scanf("%d%d",&a,&b);
  if(a>b)
       printf("\n DISTANCE BETWEEN THE POINTS %d,%d is %d\n",a,b,a-b);
  else
       printf("\n DISTANCE BETWEEN THE POINTS %d,%d is %d\n",a,b,b-a);
}
