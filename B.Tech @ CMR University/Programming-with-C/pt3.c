#include<stdio.h>
void main()
{
	int i=10,*j,**k;
	j=&i;
	k=&j;
	printf(" 1. Address of i = %p\n",&i);
	printf(" 2. Address of i = %p\n",j);
	printf(" 3. Address of i = %p\n",*k);
	printf("\n 4. Address of j = %p\n",&j);
	printf(" 5. Address of j = %p\n",k);
	printf(" 6. Address of k = %p\n",&k);
	printf("\n 7. Value of j=%p\n",j);
	printf(" 8. Value of k=%p\n",k);
	printf(" 9. Value of i=%d\n",i);
	printf("\n 10.Value of i=%d\n",*(&i));
	printf(" 11.Value of i=%d\n",*j);
	printf(" 12.Value of i=%d\n",**k);
}
