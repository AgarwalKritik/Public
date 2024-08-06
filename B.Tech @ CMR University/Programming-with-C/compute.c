/*Compute SI*/
#include<stdio.h>
void main()
{ float p,t,r,s;
  printf("\t Enter values of p,t,r\n");
  scanf("%f%f%f",&p,&t,&r);
  s=(p*t*r)/100;
  printf("\tSimple Interest=%f\n",s);
}
