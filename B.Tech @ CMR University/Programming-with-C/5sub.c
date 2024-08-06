/*avg of 5 sub*/
#include<stdio.h>
void main()
{ int a,b,c,d,e,sum,avg;
  printf("\tENTER MARKS OF SUB 1(Total 100) : ");
  scanf("%d",&a);
  printf("\tENTER MARKS OF SUB 2(Total 100) : ");
  scanf("%d",&b);
  printf("\tENTER MARKS OF SUB 3(Total 100) : ");
  scanf("%d",&c);
  printf("\tENTER MARKS OF SUB 4(Total 100) : ");
  scanf("%d",&d);
  printf("\tENTER MARKS OF SUB 5(Total 100) : ");
  scanf("%d",&e);
  sum=a+b+c+d+e;
  avg=sum/5;
  printf("\tSUM OF THE MARKS OBTAINED = %d \n",sum);
  printf("\tAVERAGE OF THE MARKS OBTAINED = %d \n",avg);
}
