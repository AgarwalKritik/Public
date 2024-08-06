#include<stdio.h>
int main()
{
	int id,pw;
	printf("\n ENTER USER ID: ");
	scanf("%d",&id);
	switch(id)
	{
		case 10:
			printf("\nENTER PASSWORD: ");
			scanf("%d",&pw);
			switch(pw)
				{	

				case 000:
				printf("\nUSER VERIFIED OK!\n");
				break;
				default:
				printf("\nWRONG PASSWORD\n");
			}
			break;
		default:
			printf("\nINVALID USER!\n");
	}
	return 0;
}
