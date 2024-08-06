/*To Convert Given Number into Years Months & Days*/
#include<stdio.h>
void main()
{ 
  int n,y,m,w,d;
  printf("\tENTER THE NUMBER : ");
  scanf("%d",&n);
  y=n/365;
  m=(n % 365)/30;
  w=((n % 365) % 30)/7;
  d=(((n % 365) % 30) % 7);
  printf("\tYEARS: %d \n\tMONTHS:%d \n\tWEEKS:%d \n\tDAYS:%d \n",y,m,w,d);
}
