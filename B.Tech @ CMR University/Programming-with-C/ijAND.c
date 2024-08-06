/*i & j values from 1 to 5
#include<stdio.h>
int main()
{
	for(int i=1,j=1;i<6 && j<6;i++,j++)
	{
		printf("\n %d \t %d \n",i,j);
	}
	return 0;
}
*/
/*
#include<stdio.h>
int main()
{
	int i=1,j=1;
	while(i<6 && j<6)
	{
		printf("\n %d \t %d \n",i,j);
		i++;
		j++;
	}
	return 0;
}
*/

#include<stdio.h>
int main()
{
	int i=1,j=1;
	do
	{
		printf("\n %d \t %d \n",i,j);
		i++;
		j++;
	}while(i<6 && j<6);
	return 0;
}
