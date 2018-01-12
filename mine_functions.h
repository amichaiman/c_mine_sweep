/*                       amichai mantinband 305663106                      */
#ifndef _MINE_H_
#define _MINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define NUM_NEIGHBORS 8 //each spot has 8 spots surrounding it
#define MAX_BOARD_SIZE 26 // 26 letter in alphabet

typedef struct
{ 
  int value; //numbers of mines around spot
  int is_mine; //gets 1 value if is a mine, 0 otherwise
  int revealed;  //gets 1 value if spot was revealed, 0 otherwise
  int flagged; //gets 1 value if flagged as bomb, 0 otherwise
} spot;

spot **build_matrix(spot **matrix, int size); //dynamic allocates a 2d array
void print_matrix(spot **a, int size); //prints board to screen
void print_line(int size); //prints a line of "-" (used in print matrix function)
void spread_mines(spot **matrix, int size, int mines); //randomly places mines across the board 
void neighbor_value(spot **matrix,int size, int v, int h); //increases value of spots surrounding mine by one
void empty_matrix(spot **a, int size); //initializes all spots in matrix
void print_coloum_numbers(int size); //prints a number in the begining of each coloum (used in print matrix function)
void move(spot **a, int size, int *revealed, int *flagged); //reads coordinates and reveals spot in matrix
void spot_consequence(spot **a,int size,int v,int h, int *revealed); //ends game/opens coordinate, depending on the spot
void open_area(spot **a,int size,int v,int h, int *revealed);// all neigbhors are revealed recursivly, if value of given coordinate=0,  
int in_matrix(int v, int h, int size);//checks if coordinate is on matrix
void bomb(spot **a,int size);//when a bomb is revealed all values are changed to 0
void winner(spot **a, int size); //when player wins, all values are changed to 9
void smiley();//prints a smiley to screen
int correct_guesses(spot **a, int size); //counts how many flags were placed on mines
#endif


