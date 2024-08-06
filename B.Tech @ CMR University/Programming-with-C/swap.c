/*Swap values*/
#include<stdio.h>
void main()
{ int a,b,tmp=0;
  printf("\tEnter values of a: ");
  scanf("%d",&a);
  printf("\tEnter values of b: ");
  scanf("%d",&b);
  printf("Before Swapping\n a=%d , b=%d \n",a,b);
  tmp=a;a=b;b=tmp;
  printf("After Swapping\n a=%d , b=%d \n",a,b);
}
