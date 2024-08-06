/*Factorial of N Numbers*/
#include<stdio.h>
void main()
{ 
  double n,m=1;
  printf("\tENTER A NUMBER : ");
  scanf("%lf",&n);
  for(int i=1;i<=n;i++)
  	m*=i;
  printf("\tFACTORIAL OF %lf IS %lf \n",n,m);
}
