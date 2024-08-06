//SWITCH CASE
#include<stdio.h>
int main()
{
	int a,b,ch;
	printf("Enter Values of a & b: ");
	scanf("%d %d",&a,&b);
	printf("1.ADD\n2.SUB\n3.MUL\n4.DIV\n5.MOD\n");
	printf("\nENTER YOUR CHOICE: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("%d\n",a+b);
			break;
		case 2:
			printf("%d\n",a-b);
			break;
		case 3:
			printf("%d\n",a*b);
			break;
		case 4:
			printf("%d\n",a/b);
			break;
		case 5:
			printf("%d\n",a%b);
			break;
		default:
			printf("INVALID INPUT\n");
	}
	return 0;
}