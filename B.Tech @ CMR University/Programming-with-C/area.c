/*Area of Triangle*/
#include<stdio.h>
#include<math.h>

void main()
{ 
  float a,b,c,s,ar;
  printf("\t ENTER THE SIDES OF THE TRIANGLE a,b,c: ");
  scanf("%f%f%f",&a,&b,&c);
  s=(a+b+c)/2;
  ar = sqrt(s*(s-a)*(s-b)*(s-c));
  printf("\t Area of the triangle is %f\n",ar);
}
