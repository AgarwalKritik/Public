/*Find the area of a circle*/
#include<stdio.h>
#define pi 3.14
void main()
{ float r,area;
  printf("\tEnter the value of radius\n");
  scanf("\t%f",&r);
  area=pi*r*r;
  printf("\tArea=%f\n",area);
}
