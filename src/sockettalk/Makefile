CC=gcc -std=c99
CFLAGS=-Wall -Werror --pedantic
INCLUDES=-I../../include

all: server client

clean:
	rm server
	rm client

fclean:clean

re: fclean all

server:
	$(CC) $(CFLAGS) -o server server.c -I../../include -L../../lib -llist -lmy
client:
	$(CC) $(CFLAGS) -o client client.c -I../../include -L../../lib -lmy

	
