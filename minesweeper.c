/*----------------------------------------------------------------------------*
 * minesweeper.c                                                              *
 * Gregory Gundersen                                                          *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "board.h"

/*----------------------------------------------------------------------------*/

/* Print horizontal line of either thick or normal weight.
 */
static void printLine(int bThick)
{
     if (bThick) {
          printf("============================================================="
                 "===================\n");
     } else {
          printf("-------------------------------------------------------------"
                 "-------------------\n");                 
     }
}
/*----------------------------------------------------------------------------*/

/* Plays a game of minesweeper.
 *
 * While there are legal moves available, reads in a move from stdin, updates
 * the state of the, and prints out the board. Notifies user of illegal move via
 * stdout. Return 0.
 */
int main(void)
{
     char cRow;     
     char cCol;
     int bIsLegal;
     int bIsBomb;
     int bIsFull;

     printLine(1);
     printf("Minesweeper\n");
     printLine(1);

     printf("Please input moves, e.g. 5D, until game is over.\n");

     printLine(0);
     Board_init();
     Board_print(0);
     putchar('\n');
    
     for (;;) {
          scanf(" %c%c", &cRow, &cCol);
          bIsLegal = Board_isLegalMove(cRow, cCol);
          bIsBomb = Board_isBomb(cRow, cCol);
          if (bIsLegal && bIsBomb) {
               printLine(1);
               Board_print(1);
               printf("\nGame over!\n\n");
               return 0;
          } else if (bIsLegal) {
               printLine(0);
               Board_update(cRow, cCol);
               Board_print(0);
               putchar('\n');
          } else {
               printf("Please enter a legal move.\n");
          }
          
          if (Board_isFull()) {
               printLine(1);
               printf("Congrats! You win!\n");
               return 0;
          }
     }
     return 0;
}
