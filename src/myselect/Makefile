CC=gcc -std=c99 
CFLAGS=-g -Wall -Werror --pedantic
INCLUDES=-I../../include

all:
	$(CC) $(CFLAGS) -o myselect myselect.c $(INCLUDES) -L../../lib -llist -lncurses -lmy
clean:
	rm myselect

fclean:	clean

re: fclean all
