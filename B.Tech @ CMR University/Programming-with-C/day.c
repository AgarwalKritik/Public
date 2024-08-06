//PRINT DAY SWITCH CASE
#include<stdio.h>
int main()
{
	char x;
	printf("Enter a Day Char(M,T,W,t,F,s,S): ");
	scanf("%c",&x);
	switch(x)
	{
		case 'M':
			printf("MONDAY\n");
			break;
		case 'T':
			printf("TUESDAY\n");
			break;
		case 'W':
			printf("WEDNESDAY\n");
			break;
		case 't':
			printf("THURSDAY\n");
			break;
		case 'F':
			printf("FRIDAY\n");
			break;
		case 's':
			printf("SATURDAY\n");
			break;
		case 'S':
			printf("SUNDAY\n");
			break;
		default:
			printf("INVALID INPUT\n");
	}
	return 0;
}