#include<stdio.h>
int main()
{
	int n,s=0,avg=0;
	printf("How many numbers do you want to enter? : ");
	scanf("%d",&n);
	int a[n];
	printf("\nEnter the numbers: \n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("\n Entered Values Are: \n");
	for(int i=0;i<n;i++)
	{
		s+=a[i];
		avg=s/n;
	}
	printf("\n Sum = %d & Avg = %d \n",s,avg);
	return 0;
}
