#include <stdio.h>
#include <ctype.h>

int main()
{
  char ran;
  
  printf("Enter a tav:\n");
  
  ran = getchar();   //scanf("%c",&ran)
  
  putchar(ran);	     //printf("%d",ran);
  
  putchar('\n');
  
  
  return 0;
}