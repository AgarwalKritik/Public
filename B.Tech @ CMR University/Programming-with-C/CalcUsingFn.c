#include<stdio.h>

int Add(int x,int y)
{
	int z;
	z=x+y;
	return z;
}

int Sub(int x,int y)
{
	int k;
	k=x-y;
	return k;
}

int Div(int x,int y)
{
	int d;
	d=x/y;
	return d;
}

int Mult(int x,int y)
{
	int m;
	m=x*y;
	return m;
}

int Mod(int x,int y)
{
	int p;
	p=x%y;
	return p;
}

void main()
{
	int a,t,b,r=0;
	printf("\n\t\tCALCULATOR");
	printf("\n\t\t----------");
	printf("\n\t\tENTER FIRST INTEGER VALUE");
	scanf("%d",&a);
	printf("\n\t\tTYPE OF CALCULATION?");
	printf("\n\t\t1. ADDITION");
	printf("\n\t\t2. SUBTRACTION");
	printf("\n\t\t3. DIVISION");
	printf("\n\t\t4. MULTIPLICATION");
	printf("\n\t\t5. MOD ( REMAINDER ) ");
	printf("\n\n\tENTER YOUR CHOICE: ");
	scanf("%d",&t);
	printf("\n\t\tENTER SECOND INTEGER VALUE");
	scanf("%d",&b);
	switch(t)
	{
		case 1:
			r=Add(a,b);
			break;
		case 2:
			r=Sub(a,b);
			break;
		case 3:
			r=Div(a,b);
			break;
		case 4:
			r=Mult(a,b);
			break;
		case 5:
			r=Mod(a,b);
			break;
		default:
			printf("\n\t\tWrong Choice!!\n");
	}
	printf("\n\t\t Result = %d\n",r);
}

