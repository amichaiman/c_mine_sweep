#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

typedef enum {black, white} color;
typedef struct {
  color c;	 //color
  int x;   	//x coordinate
  int y;   	//y coordinate
} peice;

void start_board(peice *a[][SIZE]);
int is_even(int num);

int main()
{
  peice *a[SIZE][SIZE];
  peice b;
  
  start_board(a);
  
  scanf("%d%d",&b.x,&b.y);
  move_peice(a,b,2,1);
  
  return 0;
}

void start_board(peice *a[][SIZE])
{
  int i,j;
  for (i=0; i<SIZE; i++)
  {
    if (!i)
      for (j=0; j<SIZE; j++)
	if (!is_even(j))
	{
	  a[i][j] = (peice *) malloc (sizeof(peice));
	  a[i][j]->c = black;
	  a[i][j]->x = i;
	  a[i][j]->y = j;
	}
    else
      if (i==7)
	for (j=0; j<SIZE; j++)
	  if (is_even(j))
	  {
	    a[i][j] = (peice *) malloc (sizeof(peice));
	    a[i][j]->c = white;
	    a[i][j]->x = i;
	    a[i][j]->y = j;
	  }
      else
	a[i][j] = NULL;
  }
}

int is_even(int num)
{
  return !num%2? 1 : 0;
}

int move_peice(peice *a[][SIZE], peice loc,to_i,to_j)
{
  
  if (to_i > SIZE || to_j > SIZE)
    return 0;
  
  if (a[loc.x][loc.y] == NULL)
    return 0;
  
  if (a[loc.x][loc.y].c == black)
    if (a[loc.x][loc.y].x + 1 != )
      
  a[to_i][to_j] = a[loc.x][loc.y];
  a[loc.x][loc.y] = 
  
}









