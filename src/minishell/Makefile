CC=gcc  
CFLAGS=-g -Wall -Werror --pedantic
INCLUDES=-I../../include

all:
	$(CC) -g -o minishell minishell.c $(INCLUDES) -L../../lib -lmy
clean:
	rm minishell

fclean:	clean

re: fclean all
