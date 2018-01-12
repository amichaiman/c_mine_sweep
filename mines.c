
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define NUM_NEIGBHORS 8

typedef struct
  { 
    int value; 
    int is_mine;
    int revealed;  
  } spot;

spot **build_matrix(spot **matrix, int size);
void print_matrix(spot **a, int size);
void print_line(int size);
void spread_mines(spot **matrix, int size, int mines);
void neighbor_value(spot **matrix,int size, int v, int h);
void empty_matrix(spot **a, int size);
void print_row_numbers(int size);
void move(spot **a, int size, int *revealed);
void spot_consequence(spot **a,int size,int v,int h, int *revealed);
void open_area(spot **a,int size,int v,int h, int *revealed);
int in_matrix(int v, int h, int size);




