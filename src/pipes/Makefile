CC=gcc -std=c99
CFLAGS=-Wall -Werror --pedantic
INCLUDES=-I../../include

all:
	$(CC) $(CFLAGS) -g -o pipes pipes.c $(INCLUDES) -L../../lib -lmy
clean:
	rm pipes

fclean:	clean

re: fclean all
