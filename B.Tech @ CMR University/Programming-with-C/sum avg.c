/*Arithmetic Operations*/
#include<stdio.h>
void main()
{ int a,b;
  printf("\t\tEnter Values of a & b\n");
  scanf("%d%d",&a,&b);
  printf("\t\tEntered Values\n");
  printf("\t\ta=%d & b=%d\n",a,b);
  printf("\t\tSUM=%d\n",a+b);
  printf("\t\tMultilied Value=%d\n",a*b);
  if(a>b)
  {
  printf("\t\tSUB=%d\n",a-b);
  printf("\t\tDIVIDE=%d\n",a/b);
  printf("\t\tRemainder=%d\n",a%b);
  }
  else
  { 
  printf("\t\tSUB=%d\n",b-a);
  printf("\t\tDIVIDE=%d\n",b/a);
  printf("\t\tRemainder=%d\n",b%a);
  }
}
  
  
