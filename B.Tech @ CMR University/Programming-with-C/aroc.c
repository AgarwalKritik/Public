#include<stdio.h>
#define pi 3.14

int main() 
{
    float r,ar,c;
    printf("\nEnter the radius of Circle : ");
    scanf("%f",&r);
    ar = pi*r*r;
    c=2*pi*r;
    printf("\nArea of Circle : %f", ar);
printf("\nCircumference of Circle : %f \n", c);
    return 0;
}

