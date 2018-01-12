/*                       amichai mantinband 305663106                      */
#include "mine_functions.h"

int main()
{
  int mines; //numbers of mines (input dependent)
  spot **matrix = NULL; //board
  int matrix_size = 0; //board size(input dependent)
  int number_of_revealed = 0; //move index
  int number_of_flags = 0; //number of mines not yet flagged
  srand(time(NULL)); //seed

  printf("Enter board size:\n");
  scanf("%d",&matrix_size);
  if (matrix_size > MAX_BOARD_SIZE) //cant exceed 26
  {
    printf("board size was changed to: %d\n",MAX_BOARD_SIZE);
    matrix_size = MAX_BOARD_SIZE;
  }
  matrix = build_matrix(matrix,matrix_size);
  
  empty_matrix(matrix,matrix_size);
  
  printf("Enter number of mines:\n");
  scanf("%d",&mines);
  if (mines > (matrix_size*matrix_size)) //cant exceed matrix size^2
  {
    mines = matrix_size*matrix_size;
    printf("number of mines was changed to: %d\n",mines);
  }
  number_of_flags = mines;
  print_matrix(matrix,matrix_size);
  spread_mines(matrix, matrix_size, mines);
  while (number_of_revealed < matrix_size*matrix_size-mines) //stops when all spot that arent a bomb are revealed
  {
    printf("flag coordinate, or reveal? (f/r):");
    move(matrix,matrix_size,&number_of_revealed, &number_of_flags); 
    printf("mines left: %d\n",number_of_flags);
    printf("spots revealed: %d\n",number_of_revealed);
    if (number_of_flags == 0)
    {
      if (correct_guesses(matrix,matrix_size) == mines)
	break;
      else
      {
	bomb(matrix,matrix_size);
	exit(1);
      }
    }
    print_matrix(matrix,matrix_size);
  }
  winner(matrix,matrix_size);
  print_matrix(matrix,matrix_size);
  smiley();
  printf("\nWe have a winner!!\n");
  return 0;
}