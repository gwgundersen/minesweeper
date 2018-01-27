/*----------------------------------------------------------------------------*
 * board.c                                                                    *
 * Gregory Gundersen                                                          *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

/*----------------------------------------------------------------------------*/

/* The number of rows and columns in the board. */
enum { N_ROWS = 9 };
enum { N_COLS = 9 };

/* An empty square is one that has not been clicked yet. */
static const char EMPTY_SQUARE = '.';
/* A cleared square is one that has been clicked and contained no bomb. */
static const char CLEARED_SQUARE = ' ';
/* A bomb square is one that contains a bomb. */
static const char BOMB_SQUARE = '*';

/* Minesweeper board. */
static char board[N_ROWS][N_COLS];

/*----------------------------------------------------------------------------*/

/* Convert a row label to an integer indexing the 2-D board, e.g. 'B' to 1. */
static int Board_row2idx(char cRow)
{
     return (int) cRow - '1';
}

/*----------------------------------------------------------------------------*/

/* Convert a column label to an integer indexing the 2-D board, e.g. '3' to 2.
 */
static int Board_col2idx(char cCol)
{
     return (int) cCol - 'A';
}

/*----------------------------------------------------------------------------*/

/* Return the number of bombs in neighboring squares. */
static int Board_numNearbyBombs(int iRow, int iCol)
{
     int count = 0;
     if (iRow > 0) {
          if (board[iRow-1][iCol] == BOMB_SQUARE)
               count++;
          if (iCol > 0 && board[iRow-1][iCol-1] == BOMB_SQUARE)
               count++;
          if (iCol < N_COLS-1 && board[iRow-1][iCol+1] == BOMB_SQUARE)
               count++;
     }
     if (iRow < N_ROWS-1) {
          if (board[iRow+1][iCol] == BOMB_SQUARE)
               count++;
          if (iCol > 0 && board[iRow+1][iCol-1] == BOMB_SQUARE)
               count++;
          if (iCol < N_COLS-1 && board[iRow+1][iCol+1] == BOMB_SQUARE)
               count++;
          
     }
     if (iCol > 0 && board[iRow][iCol-1] == BOMB_SQUARE)
          count++;
     if (iCol < N_COLS-1 && board[iRow][iCol+1] == BOMB_SQUARE)
          count++;

     return count;
}

/*----------------------------------------------------------------------------*/

/* If square contains bomb, do not clear it because this shows the bomb to the
 * player. If square does not contain bomb, show the number of bombs on nearby
 * squares.
 */
static void Board_clearSquare(int iRow, int iCol)
{
     if (board[iRow][iCol] == BOMB_SQUARE)
          return;
     int iCount = Board_numNearbyBombs(iRow, iCol);
     board[iRow][iCol] = iCount + '0';
}

/*----------------------------------------------------------------------------*/

/* Given a newly clicked square, uniformly at random clear its neighbors.
 */
static void Board_clearRandomNeighbors(int iRow, int iCol)
{
     srand(time(NULL));
     int i;
     int j;
     int r;

     if (iRow > 0 && rand() % 2) {
          Board_clearSquare(iRow - 1, iCol);
     }
     if (iRow < N_ROWS-1 && rand() % 2) {
          Board_clearSquare(iRow + 1, iCol);
     }
     if (iCol > 0 && rand() % 2) {
          Board_clearSquare(iRow, iCol - 1);          
     }
     if (iCol < N_COLS-1 && rand() % 2) {
          Board_clearSquare(iRow, iCol + 1);
     }
}

/*----------------------------------------------------------------------------*/

void Board_init()
{
     srand(time(NULL));
     int i;
     int j;
     int r;

     for (i = 0; i < N_ROWS; i++) {
          for (j = 0; j < N_COLS; j++) {
               r = rand() % 5;             
               if (r == 0) 
                    board[i][j] = BOMB_SQUARE;
               else
                    board[i][j] = EMPTY_SQUARE;
          }
     }
}

/*----------------------------------------------------------------------------*/

void Board_print(int bShowBombs)
{
     int i;
     int j;
     char c;

     c = 'A';
     putchar(' ');
     for (j = 0; j < N_COLS; j++) {
          printf(" %c", c);
          c++;
     }
     c = '1';
     putchar('\n');
     for (i = 0; i < N_ROWS; i++) {
          for (j = 0; j < N_COLS+1; j++) {
               if (j == 0) {
                    printf("%c", c);
                    c++;
               } else {
                    if (board[i][j-1] == BOMB_SQUARE && !bShowBombs) {
                         printf(" %c", EMPTY_SQUARE);                         
                    } else {
                         printf(" %c", board[i][j-1]);
                    }
               }
          }
          putchar('\n');
     }
}

/*----------------------------------------------------------------------------*/

int Board_isLegalMove(char cRow, char cCol)
{
     int iRow;
     int iCol;

     iRow = Board_row2idx(cRow);
     iCol = Board_col2idx(cCol);

     if (iRow < 0 || iRow >= N_ROWS)
          return 0;
     if (iCol < 0 || iCol >= N_COLS)
          return 0;
     /* Cannot play on cleared square or square with flag. */
     if (board[iRow][iCol] == CLEARED_SQUARE)
          return 0;
     return 1;
}

/*----------------------------------------------------------------------------*/

int Board_isBomb(char cRow, char cCol)
{
     int iRow;
     int iCol;

     iRow = Board_row2idx(cRow);
     iCol = Board_col2idx(cCol);
    
     return board[iRow][iCol] == BOMB_SQUARE;
}

/*----------------------------------------------------------------------------*/

void Board_update(char cRow, char cCol)
{
     int iRow;
     int iCol;
     int iCount;

     iRow = Board_row2idx(cRow);
     iCol = Board_col2idx(cCol);

     iCount = Board_numNearbyBombs(iRow, iCol);
     board[iRow][iCol] = iCount + '0';
     Board_clearRandomNeighbors(iRow, iCol);
}

/*----------------------------------------------------------------------------*/

int Board_isFull(void)
{
     int i;
     int j;

     for (i = 0; i < N_ROWS; i++) {
          for (j = 0; j < N_COLS; j++) {
               if (board[i][j] == '.') {
                    return 0;
               }
          }
     }
     return 1;
}
