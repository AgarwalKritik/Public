#include<stdio.h>

int main()
{
int n, a, b, c, d, r1, r2, r3, r4;
printf("Enter any five digit number: ") ;
scanf("%d",&n) ;
printf("\nBefore Reversing:: %d\n",n);
a = n/10 ;    
r1 = n % 10 ;
b = a/10 ;    
r2 = a % 10 ;
c = b/10 ;     
r3 = b % 10 ;
d = c/10 ;    
r4 = c % 10 ;
printf("\nAfter Reversing:: %d%d%d%d%d \n",r1,r2,r3,r4,d);
return 0;
}

