//Switch Case
#include<stdio.h>
int main()
{
	char x='a';
	switch(x)
	{
		case 'b':
			printf("Case b\n");
			break;
		case 'a':
			printf("Case a\n");
			break;
		case 'c':
			printf("Case c\n");
			break;
		default:
			printf("NO MATCH\n");
	}
	return 0;
}
