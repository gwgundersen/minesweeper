/*----------------------------------------------------------------------------*
 * board.h                                                                    *
 * Gregory Gundersen                                                          *
 *----------------------------------------------------------------------------*/

#ifndef BOARD_INCLUDED

/* Initialize board with mines placed uniformly at random. */
void Board_init(void);

/* Pretty print board. */
void Board_print(int bShowBombs);

/* Return 1 (TRUE) if move is legal, 0 (FALSE) otherwise. */
int Board_isLegalMove(char cRow, char cCol);

/* Return 1 (TRUE) if square contains bomb, 0 (FALSE) otherwise. */
int Board_isBomb(char cRow, char cCol);

/* Update board state with */
void Board_update(char cRow, char cCol);

/* Return 1 (TRUE) if board is full, 0 (FALSE) otherwise. */
int Board_isFull(void);

#endif
