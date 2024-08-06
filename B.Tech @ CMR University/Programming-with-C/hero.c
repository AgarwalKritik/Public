/*Quadratic Equation*/
#include<stdio.h>
#include<math.h>

void main()
{ long double a,b,c,r1,r2;
  printf("\t ENTER THE VALUE of a: ");
  scanf("%Lf",&a);
  printf("\t ENTER THE VALUE of b: ");
  scanf("%Lf",&b);
  printf("\t ENTER THE VALUE of c: ");
  scanf("%Lf",&c);
  r1=(-b+(sqrt((b*b)-(4*a*c))))/(2*a);
  r2=(-b-(sqrt((b*b)-(4*a*c))))/(2*a);
  printf("\t Roots of the Quadratic  Equation are (%Lf,%Lf)\n",r1,r2);
}
