#include<stdio.h>
int main()
{
  int qt,ppu,d,te;
  printf("\t\tEnter Quantity: "); scanf("%d",&qt);
  printf("\t\tEnter Price per unit: "); scanf("%d",&ppu);
  te=qt*ppu;
  if(te>1500)
  {
    d=(te*20)/100;
    te-=d;
  }
  printf("\t\tTotal Expenses: %d \n",te);
  return 0;
}
