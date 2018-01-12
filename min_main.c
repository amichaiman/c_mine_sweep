int main()
{
  int mines;
  spot **matrix;
  int matrix_size;
  int number_of_revealed = 0; //move index
  srand(time(NULL));

  printf("Enter size:\n");
  scanf("%d",&matrix_size);

  matrix = build_matrix(matrix,matrix_size);
  
  empty_matrix(matrix,matrix_size);
  
  print_matrix(matrix,matrix_size);
  
  printf("Enter amount of mines:\n");
  scanf("%d",&mines);
  
  spread_mines(matrix, matrix_size, mines);
  while (number_of_revealed < matrix_size*matrix_size-mines)
  {
    printf("Enter spot:\n");
    move(matrix,matrix_size,&number_of_revealed); 
    printf("revealed: %d\n",number_of_revealed);
    print_matrix(matrix,matrix_size);
  }
  printf("\nWe have a winner!!\n");
  return 0;
}