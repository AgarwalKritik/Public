#include<stdio.h>
int main()
{
	int a,b,c,d,e,sum,avg;
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

  	if(avg>=90)
  		printf("GRADE : S\n");
  	else if(avg>=80)
  		printf("GRADE : A\n");
  	else if(avg>=70)
  		printf("GRADE : B\n");
  	else if(avg>=60)
  		printf("GRADE : C\n");
  	else
  		printf("FAIL!\n");
  	return 0;
}