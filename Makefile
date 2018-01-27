#-------------------------------------------------------------------------------
# Makefile
# Gregory Gundersen
#-------------------------------------------------------------------------------

CC = gcc
CFLAGS = -D NDEBUG

all: minesweeper

clean:
	rm -f minesweeper
	rm -f *.o

#-------------------------------------------------------------------------------

minesweeper: minesweeper.o board.o
	$(CC) $(CFLAGS) minesweeper.o board.o -o minesweeper

minesweeper.o: minesweeper.c
	$(CC) $(CFLAGS) -c minesweeper.c

board.o: board.c
	$(CC) $(CFLAGS) -c board.c
