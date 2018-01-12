#include <stdio.h>

int rev_num(unsigned int num, unsigned int t);

int main()
{
  int num = 12345;
  int t = 10000;

  printf("%d\n",rev_num(num,t));
  return 0;
  
}

int rev_num(unsigned int num, unsigned int t)
{
  
  if (t == 0)
    return 0;
  
  return (rev_num(num%t,t/10)*10 + num/t);
}
