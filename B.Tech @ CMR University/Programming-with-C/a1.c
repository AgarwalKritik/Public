#include<stdio.h>
int main()
{
	int n;
	printf("How many numbers do you want to enter? : ");
	scanf("%d",&n);
	int a[n];
	printf("\nEnter the numbers: \n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("\n Entered Values Are: \n");
	for(int i=0;i<n;i++)
		printf("\n %d \n",a[i]);
	return 0;
}
