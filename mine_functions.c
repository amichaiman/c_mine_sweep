/*                       amichai mantinband 305663106                      */
/*      program is a game. "mines" are spread randomly on a 2d board.      */
/*     each spot on board has a value- the amount of bomb surrounding it.  */
/*         player  reveals spot by spot, trying not to reveal a mine       */

#include "mine_functions.h"

void empty_matrix(spot **a, int size)
//initializes all spots in matrix
{
  int i,j; //loop indexs
  
  for (i=0; i<size; i++)
    for (j=0; j<size; j++)
    {
      a[i][j].value=0;
      a[i][j].revealed=FALSE; 
      a[i][j].is_mine=FALSE;
      a[i][j].flagged=FALSE;
    }
}

spot **build_matrix(spot **matrix, int size)
//dynamic allocates a 2d array
{
  spot **temp; //temporary matrix array
  int i; //loop index
  if ((matrix = (spot **) malloc (sizeof(spot *))) == NULL)
  {
    printf("could not allocate matrix !!");
    exit(1);
  }
  if ((temp = (spot **) realloc (matrix, size*sizeof(spot *))) == NULL)
  {
    printf("could not allocate temp !!");
    exit(1);
  }
  
  for (i=0; i<size; i++)
    if ((matrix[i] = (spot *) malloc (size*sizeof(spot))) == NULL)
    {
      printf("could not allocate matrix[%d]",i);
      exit(1);
    }
  return matrix; //returns matrix's address
}

void print_matrix(spot **a, int size)
//prints board to screen
{
  int i,j; //loop indexs
  
  printf("\n");
  print_coloum_numbers(size); //prints row number above each coloum
  printf("\n");
  print_line(size); 
  printf("\n");
  for (i=0; i<size; i++)
  {
    printf("%c|",toupper('a'+i)); //prints row letter at beggining of each row
    for (j=0; j<size; j++)
      if (a[i][j].revealed == TRUE) //only prints values if spot is revealed
	if (a[i][j].is_mine == TRUE) //checks if spot is a mine
	  printf(" %c%c |",164,7); //prints a mine character, and makes a beep sound
	else
	  if (a[i][j].value == 0) //if value is 0, no value is printed
	    printf("   |");
	  else
	    if (a[i][j].value == 9) //if player has won
	      printf(" $ |");
	      else
		printf(" %d |",a[i][j].value); //prints spots value
      else
	if (a[i][j].flagged == TRUE)
	  printf("<> |");
	else
	  printf(" # |");	//spot wasn't revealed
    printf("\n");
    print_line(size);
    printf("\n");
  }
}

void print_line(int size)
//prints a line of "-" (used in print matrix function)
{
  int i; //loop index
  printf("  ");
  for (i=0; i<size; i++)
    printf("----");
}

void spread_mines(spot **matrix, int size, int mines)
//randomly places mines across the board 
{
  int i=0; //loop index
  int v,h;//location
  
  while (i<mines)
  {
    v = rand()%size; //number between 0 and size-1
    h = rand()%size;//number between 0 and size-1
    if (matrix[v][h].is_mine == FALSE)
    {
      matrix[v][h].is_mine = TRUE; 
      i++; //mine was planted
      neighbor_value(matrix,size,v,h); //increases neigbhors value by 1
    }
  }
}


void neighbor_value(spot **matrix,int size, int v, int h)
//increases value of spots surrounding mine by one
{
  int neighborv[NUM_NEIGHBORS] = { 1, 1, 1 ,0 ,0,-1,-1,-1}; //8 possible neigbhors
  int neighborh[NUM_NEIGHBORS] = {-1, 0, 1,-1 ,1, -1, 0,1}; //8 possible neigbhors
  int new_h=0, new_v=0; //new h and v
  int i; //loop index
  
  for (i=0; i<NUM_NEIGHBORS; i++)
  {
    new_h = h + neighborh[i];
    new_v = v + neighborv[i];
    if (in_matrix(new_v,new_h,size)) //checks spot is in matrix
      if (matrix[new_v][new_h].is_mine != TRUE) //checks spot is not a mine
	matrix[new_v][new_h].value++; 
  }
}

void move(spot **a, int size,int *revealed, int *flags_left)
//reads coordinates and reveals spot in matrix
{
  char v; //v as verticle character
  int h; //h coordinate
  int n_v; //v as verticle number
  char flag_or_reveal;
  char answer;
  
  scanf ("%c%c",&flag_or_reveal,&flag_or_reveal);
  while (!(tolower(flag_or_reveal) == 'r' || tolower(flag_or_reveal) == 'f'))
  {
    printf("Invalid input. Try again:\n");
    scanf("%c%c",&flag_or_reveal,&flag_or_reveal);
  }
  printf("Enter spot:\n");
  v = getchar();
  while (!isalpha(v))
    v = getchar();
  scanf("%d",&h);
  n_v = tolower(v) - 'a'; //char is converted to int
  while (n_v<0 || n_v>=size || h<0 || h>size)
  {
    printf("Invalid spot. Try again:\n");
    v = getchar();
    while (!isalpha(v))
      v = getchar();
    scanf("%d",&h);
    n_v = tolower(v) - 'a'; //char is converted to int
  }
  if (tolower(flag_or_reveal) == 'r')
  {
    if (a[n_v][h-1].flagged)
    {
      printf("Spot has been flagged, do you wish to reveal it anyway? (y/n):");
      scanf("%c%c",&answer,&answer);
      if (tolower(answer) == 'y')
      {
	*flags_left = *flags_left + 1;
	a[n_v][h-1].flagged = FALSE;
	spot_consequence(a,size,n_v,h-1,revealed);
      }
    }
    else
      spot_consequence(a,size,n_v,h-1,revealed);
  }
  else
  {
    if (*flags_left == 1)
    {
      printf("Do you wish to use your last flag? (y/n):");
      scanf("%c%c",&answer,&answer);
      if (tolower(answer) == 'y')
      {
	a[n_v][h-1].flagged = TRUE;
	*flags_left = *flags_left - 1;
      }
    }
    else
    {
      a[n_v][h-1].flagged = TRUE;
      *flags_left = *flags_left - 1;
    }
  }
}

void print_coloum_numbers(int size)
//prints a number in the begining of each coloum (used in print matrix function)
{
  int i;
  printf("  ");
  for (i=0; i<size; i++)
    i<9 ? printf(" %d  ",i+1) : printf(" %d ",i+1); 
}

void spot_consequence(spot **a,int size,int v,int h,int *revealed)
 //ends game/opens coordinate, depending on the spot
{
  if (a[v][h].is_mine) //spot is a mine
  {
    bomb(a,size); 
    exit(1);
  }
  open_area(a,size,v,h,revealed); //spot is sent to be revealed
}

void open_area(spot **a,int size,int v,int h,int *revealed)
// all neigbhors are revealed recursivly, if value of given coordinate=0, if not, only that spot is revealed
{
  static int nv[NUM_NEIGHBORS] = { 1, 1, 1 ,0 ,0,-1,-1,-1}; //8 possible neigbhors
  static int nh[NUM_NEIGHBORS] = {-1, 0, 1,-1 ,1, -1, 0,1}; //8 possible neigbhors
  
  int new_v, new_h; //new v and h coordinates
  int i; //loop index
  
  if (a[v][h].revealed == TRUE)
    return;
  
  a[v][h].revealed = TRUE; //reveals spot
  *revealed = *revealed+1;
  
  if (a[v][h].value != 0) //spot is not a 0
    return;
  
  for (i=0; i<NUM_NEIGHBORS; i++)
  {
    new_v = v+nv[i];
    new_h = h+nh[i];
    if (in_matrix(new_v,new_h,size)) 
      open_area(a,size,new_v,new_h,revealed);
  }
}
  
int in_matrix(int v, int h, int size)
//checks if coordinate is on matrix
{
  if (h >= 0 && v >= 0 && h < size && v < size) //number is between 0 and size-1
    return 1;
  return 0;
}

void bomb(spot **a, int size)
//when a bomb is revealed all values are changed to 0
{
  int i,j;
  
  for (i=0; i<size; i++)
    for (j=0; j<size; j++)
    {
      a[i][j].value = 0;
      a[i][j].revealed = TRUE; //spot is revealed
    }
    print_matrix(a,size);
    printf("YOU LOSE\n"); //game over motherfucker
}

void winner(spot **a, int size)
//when player wins, all values are changed to 9
{
  int i,j;
  for (i=0; i<size; i++)
    for (j=0; j<size; j++) 
    {
      a[i][j].value = 9;
      a[i][j].revealed = TRUE; //spot is revealed
    }
}

void smiley()
{
  printf("\n -----------------------\n");
  printf("|       |      |        |\n");
  printf("|       |      |        |\n");
  printf("|  \\    |      |    /   |\n");
  printf("|   \\              /    |\n");
  printf("|    \\____________/     |\n");
  printf(" -----------------------");
}

int correct_guesses(spot **a, int size) //counts how many flags were placed on mines
{
  int i,j; //loop indexs
  int correct = 0; //grows when spot has mine & flagged
 
  for (i=0; i<size; i++)
    for (j=0; j<size; j++)
      if (a[i][j].is_mine && a[i][j].flagged)
	correct++;
  return correct;
}
	

