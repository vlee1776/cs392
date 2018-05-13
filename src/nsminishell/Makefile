CC=gcc -std=c99 
CFLAGS=-g -Wall -Werror --pedantic
INCLUDES=-I../../include

all:
	$(CC) $(CFLAGS) -o nsminishell nsminishell.c $(INCLUDES) -L../../lib -llist -lncurses -lmy
clean:
	rm nsminishell

fclean:	clean

re: fclean all
